/*
 * Copyright (C) 2013 Andrew Comminos
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.morlunk.jumble.net;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.util.Log;

import com.google.protobuf.ByteString;
import com.google.protobuf.InvalidProtocolBufferException;
import com.google.protobuf.Message;
import com.morlunk.jumble.Constants;
import com.morlunk.jumble.JumbleParams;
import com.morlunk.jumble.protobuf.Mumble;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpParams;

import javax.net.ssl.SSLSocket;
import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.security.*;
import java.security.cert.CertificateException;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class JumbleConnection {
    public interface JumbleConnectionListener {
        public void onConnectionEstablished();
        public void onConnectionDisconnected();
        public void onConnectionError(JumbleConnectionException e);
        public void onConnectionWarning(String warning);
    }

    private Context mContext;
    private JumbleConnectionListener mListener;
    private JumbleParams mParams;

    // Authentication
    private JumbleSSLSocketFactory mSocketFactory;

    // Threading
    private ExecutorService mExecutorService;
    private ScheduledExecutorService mPingExecutorService;
    private Handler mMainHandler;

    // Networking
    private InetAddress mHost;
    private JumbleTCP mTCP;
    private JumbleUDP mUDP;
    private boolean mUsingUDP = true;
    private boolean mConnected;
    private CryptState mCryptState = new CryptState();
    private long mStartTimestamp; // Time that the connection was initiated in nanoseconds

    // Server
    private int mServerVersion;
    private String mServerRelease;
    private String mServerOSName;
    private String mServerOSVersion;

    // Session
    private int mSession;

    // Message handlers
    private ConcurrentLinkedQueue<JumbleMessageHandler> mHandlers = new ConcurrentLinkedQueue<JumbleMessageHandler>();

    /**
     * Handles packets received that are critical to the connection state.
     */
    private JumbleMessageHandler mConnectionMessageHandler = new JumbleMessageHandler.Stub() {

        @Override
        public void messageServerSync(Mumble.ServerSync msg) {
            // Protocol says we're supposed to send a dummy UDPTunnel packet here to let the server know we don't like UDP.
            if(mParams.forceTcp) {
                try {
                    byte[] buffer = new byte[3];
                    mTCP.sendMessage(buffer, JumbleTCPMessageType.UDPTunnel);
                } catch (IOException e) {
                    Log.e(Constants.TAG, "Couldn't send dummy UDPTunnel packet.");
                }
            }

            // Start TCP/UDP ping thread. FIXME is this the right place?
            mPingExecutorService.scheduleAtFixedRate(mPingRunnable, 0, 5, TimeUnit.SECONDS);

            mSession = msg.getSession();

            mMainHandler.post(new Runnable() {
                @Override
                public void run() {
                    mListener.onConnectionEstablished();
                }
            });

        }

        @Override
        public void messageReject(final Mumble.Reject msg) {
            if(mListener != null) {
                mMainHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        mListener.onConnectionError(new JumbleConnectionException(msg));
                    }
                });
            }
            disconnect();
        }

        @Override
        public void messageUserRemove(final Mumble.UserRemove msg) {
            if(msg.getActor() == mSession) {
                if(mListener != null) {
                    mMainHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            mListener.onConnectionError(new JumbleConnectionException(msg));
                        }
                    });
                }
                disconnect();
            }
        }

        @Override
        public void messageCryptSetup(Mumble.CryptSetup msg) {
            try {
                if(msg.hasKey() && msg.hasClientNonce() && msg.hasServerNonce()) {
                    ByteString key = msg.getKey();
                    ByteString clientNonce = msg.getClientNonce();
                    ByteString serverNonce = msg.getServerNonce();

                    if(key.size() == CryptState.AES_BLOCK_SIZE &&
                            clientNonce.size() == CryptState.AES_BLOCK_SIZE &&
                            serverNonce.size() == CryptState.AES_BLOCK_SIZE)
                        mCryptState.setKey(key.toByteArray(), clientNonce.toByteArray(), serverNonce.toByteArray());
                } else if(msg.hasServerNonce()) {
                    ByteString serverNonce = msg.getServerNonce();
                    if(serverNonce.size() == CryptState.AES_BLOCK_SIZE) {
                        mCryptState.mUiResync++;
                        mCryptState.mDecryptIV = serverNonce.toByteArray();
                    }
                } else {
                    Mumble.CryptSetup.Builder csb = Mumble.CryptSetup.newBuilder();
                    csb.setClientNonce(ByteString.copyFrom(mCryptState.getEncryptIV()));
                    sendTCPMessage(csb.build(), JumbleTCPMessageType.CryptSetup);
                }
            } catch (InvalidKeyException e) {
                handleFatalException(new JumbleConnectionException("Received invalid cryptographic nonce from server", e, true));
            } catch (IOException e) {
                handleFatalException(new JumbleConnectionException("Could not resync crypt state with server", e, true));
            }
        }

        @Override
        public void messageVersion(Mumble.Version msg) {
            mServerVersion = msg.getVersion();
            mServerRelease = msg.getRelease();
            mServerOSName = msg.getOs();
            mServerOSVersion = msg.getOsVersion();
        }

        @Override
        public void messagePing(Mumble.Ping msg) {
            mCryptState.mUiRemoteGood = msg.getGood();
            mCryptState.mUiRemoteLate = msg.getLate();
            mCryptState.mUiRemoteLost = msg.getLost();
            mCryptState.mUiRemoteResync = msg.getResync();

            // In microseconds
            long elapsed = getElapsed();

            if(((mCryptState.mUiRemoteGood == 0) || (mCryptState.mUiGood == 0)) && mUsingUDP && elapsed > 20000000) {
                mUsingUDP = false;
                if(!mParams.forceTcp && mListener != null) {
                    if((mCryptState.mUiRemoteGood == 0) && (mCryptState.mUiGood == 0))
                        mListener.onConnectionWarning("UDP packets cannot be sent to or received from the server. Switching to TCP mode.");
                    else if(mCryptState.mUiRemoteGood == 0)
                        mListener.onConnectionWarning("UDP packets cannot be sent to the server. Switching to TCP mode.");
                    else
                        mListener.onConnectionWarning("UDP packets cannot be received from the server. Switching to TCP mode.");
                }
            } else if (!mUsingUDP && (mCryptState.mUiRemoteGood > 3) && (mCryptState.mUiGood > 3)) {
                mUsingUDP = true;
                if (!mParams.forceTcp && mListener != null)
                    mListener.onConnectionWarning("UDP packets can be sent to and received from the server. Switching back to UDP mode.");
            }
        }

        @Override
        public void messageUDPPing(byte[] data) {
            byte[] timedata = new byte[8];
            System.arraycopy(data, 1, timedata, 0, 8);
            ByteBuffer buffer = ByteBuffer.allocate(8);
            buffer.put(timedata);
            buffer.flip();

            long timestamp = buffer.getLong();
            // TODO refresh UDP?
        }
    };

    private Runnable mPingRunnable = new Runnable() {
        @Override
        public void run() {

            // In microseconds
            long t = getElapsed();

            if(!mParams.forceTcp) {
                byte[] buffer = new byte[256];
                buffer[0] = (byte) (JumbleUDPMessageType.UDPPing.ordinal() << 5);
                byte[] data = new byte[255];
                PacketDataStream dataStream = new PacketDataStream(data, 255);
                dataStream.writeLong(t);
                System.arraycopy(data, 0, buffer, 1, 255);
                try {
                    sendUDPMessage(buffer, JumbleUDPMessageType.UDPPing, true);
                } catch (IOException e) {
                    Log.e(Constants.TAG, "Failed to send UDP ping");
                }
            }

            Mumble.Ping.Builder pb = Mumble.Ping.newBuilder();
            pb.setTimestamp(t);
            pb.setGood(mCryptState.mUiGood);
            pb.setLate(mCryptState.mUiLate);
            pb.setLost(mCryptState.mUiLost);
            pb.setResync(mCryptState.mUiResync);

            try {
                sendTCPMessage(pb.build(), JumbleTCPMessageType.Ping);
            } catch (IOException e) {
                handleFatalException(new JumbleConnectionException("Failed to ping remote server.", e, true));
            }
        }
    };

    /**
     * Creates a new JumbleConnection object to facilitate server connections.
     * @param context An Android context.
     * @param params Jumble parameters for connection.
     * @throws CertificateException if an exception occurred parsing the p12 file.
     * @throws IOException if there was an error reading the p12 file.
     */
    public JumbleConnection(Context context,
                            JumbleConnectionListener listener,
                            JumbleParams params) throws JumbleConnectionException {
        try {
            mHost = InetAddress.getByName(params.server.getHost());
        } catch (UnknownHostException e) {
            throw new JumbleConnectionException("Could not resolve host", e, true);
        }

        mContext = context;
        mListener = listener;
        mParams = params;
        mMainHandler = new Handler(context.getMainLooper());
        mHandlers.add(mConnectionMessageHandler);
        setupSocketFactory(mParams.certificatePath, mParams.certificatePassword);
    }

    public void connect() {
        mConnected = false;
        mUsingUDP = !mParams.forceTcp;
        mStartTimestamp = System.nanoTime();

        mExecutorService = Executors.newFixedThreadPool(mParams.forceTcp ? 1 : 2); // One TCP thread, one UDP thread (if not forcing TCP).
        mPingExecutorService = Executors.newSingleThreadScheduledExecutor();

        mTCP = new JumbleTCP();
        mExecutorService.submit(mTCP);
        // We'll start UDP thread after TCP is established. FIXME?
    }

    public boolean isConnected() {
        return mConnected;
    }

    public long getElapsed() {
        return (System.nanoTime()-mStartTimestamp)/1000;
    }

    public void addMessageHandler(JumbleMessageHandler handler) {
        mHandlers.add(handler);
    }

    public void removeMessageHandler(JumbleMessageHandler handler) {
        mHandlers.remove(handler);
    }

    /**
     * Gracefully shuts down all networking.
     */
    public void disconnect() {
        mConnected = false;
        try {
            mTCP.disconnect();
            if(mUDP != null) mUDP.disconnect();
        } catch (IOException e) {
            e.printStackTrace();
        }
        mTCP = null;
        mUDP = null;
        mExecutorService.shutdown();
        mPingExecutorService.shutdown();
    }

    /**
     * Immediately shuts down all network threads.
     */
    public void forceDisconnect() {
        mConnected = false;
        mExecutorService.shutdownNow();
        mPingExecutorService.shutdownNow();
        mTCP = null;
        mUDP = null;
    }

    /**
     * Handles an exception that would cause termination of the connection.
     * @param e The exception that caused termination.
     */
    private void handleFatalException(final JumbleConnectionException e) {
        forceDisconnect();
        if(mListener != null) {
            mMainHandler.post(new Runnable() {
                @Override
                public void run() {
                    mListener.onConnectionError(e);
                }
            });
        }
    }

    /**
     * Attempts to load the PKCS12 certificate from the specified stream, and sets up an SSL socket factory.
     * You must call this method before establishing a TCP connection.
     * @param certificateStream The input stream of a PKCS12 (.p12) certificate. May be null.
     * @param certificatePassword The password to decrypt the key store. May be null.
     */
    protected void setupSocketFactory(InputStream certificateStream, String certificatePassword) throws JumbleConnectionException {
        try {
            KeyStore keyStore = null;
            if(certificateStream != null) {
                keyStore = KeyStore.getInstance("PKCS12");
                keyStore.load(certificateStream, certificatePassword != null ? certificatePassword.toCharArray() : new char[0]);
            }
            mSocketFactory = new JumbleSSLSocketFactory(keyStore, certificatePassword);
        } catch (KeyManagementException e) {
            throw new JumbleConnectionException("Could not recover keys from certificate", e, false);
        } catch (KeyStoreException e) {
            throw new JumbleConnectionException("Could not recover keys from certificate", e, false);
        } catch (UnrecoverableKeyException e) {
            throw new JumbleConnectionException("Could not recover keys from certificate", e, false);
        } catch (IOException e) {
            throw new JumbleConnectionException("Could not read certificate file", e, false);
        } catch (CertificateException e) {
            e.printStackTrace();
        }catch (NoSuchProviderException e) {
                /*
                 * This will actually NEVER occur.
                 * We use Spongy Castle to provide the algorithm and provider implementations.
                 * There's no platform dependency.
                 */
            throw new RuntimeException("We use Spongy Castle- what? ", e);
        } catch (NoSuchAlgorithmException e) {
                /*
                 * This will actually NEVER occur.
                 * We use Spongy Castle to provide the algorithm and provider implementations.
                 * There's no platform dependency.
                 */
            throw new RuntimeException("We use Spongy Castle- what? ", e);
        }
    }

    /**
     * Wrapper to load a P12 into a socket factory via a path..
     * @param certificateFile
     * @param certificatePassword
     * @throws JumbleConnectionException
     */
    protected void setupSocketFactory(String certificateFile, String certificatePassword) throws JumbleConnectionException {
        try {
            setupSocketFactory(certificateFile != null ? new FileInputStream(certificateFile) : null, certificatePassword);
        } catch (FileNotFoundException e) {
            throw new JumbleConnectionException("Could not find certificate file", e, false);
        }
    }

    public void sendTCPMessage(Message message, JumbleTCPMessageType messageType) throws IOException {
        mTCP.sendMessage(message, messageType);
    }

    public void sendUDPMessage(byte[] data, JumbleUDPMessageType messageType, boolean force) throws IOException {
        mUDP.sendMessage(data, data.length, messageType, force);
    }

    private final void handleTCPMessage(byte[] data, int length, JumbleTCPMessageType messageType) {
        Log.v(Constants.TAG, "IN: "+messageType);

        if(messageType == JumbleTCPMessageType.UDPTunnel) {
            handleUDPMessage(data);
            return;
        }

        try {
            Message message = getProtobufMessage(data, messageType);
            for(JumbleMessageHandler handler : mHandlers) {
                broadcastTCPMessage(handler, message, messageType);
            }
        } catch (InvalidProtocolBufferException e) {
            e.printStackTrace();
        }
    }

    private final void handleUDPMessage(byte[] data) {
        final JumbleUDPMessageType dataType = JumbleUDPMessageType.values()[data[0] >> 5 & 0x7];
        for(JumbleMessageHandler handler : mHandlers) {
            broadcastUDPMessage(handler, data, dataType);
        }
    }

    /**
     * Gets the protobuf message from the passed TCP data.
     * We isolate this so we can first parse the message and then inform all handlers. Saves processing power.
     * @param data Raw protobuf TCP data.
     * @param messageType Type of the message.
     * @return The parsed protobuf message.
     * @throws InvalidProtocolBufferException Called if the messageType does not match the data.
     */
    public static final Message getProtobufMessage(byte[] data, JumbleTCPMessageType messageType) throws InvalidProtocolBufferException {
        switch (messageType) {
            case Authenticate:
                return Mumble.Authenticate.parseFrom(data);
            case BanList:
                return Mumble.BanList.parseFrom(data);
            case Reject:
                return Mumble.Reject.parseFrom(data);
            case ServerSync:
                return Mumble.ServerSync.parseFrom(data);
            case ServerConfig:
                return Mumble.ServerConfig.parseFrom(data);
            case PermissionDenied:
                return Mumble.PermissionDenied.parseFrom(data);
            case UDPTunnel:
                return Mumble.UDPTunnel.parseFrom(data);
            case UserState:
                return Mumble.UserState.parseFrom(data);
            case UserRemove:
                return Mumble.UserRemove.parseFrom(data);
            case ChannelState:
                return Mumble.ChannelState.parseFrom(data);
            case ChannelRemove:
                return Mumble.ChannelRemove.parseFrom(data);
            case TextMessage:
                return Mumble.TextMessage.parseFrom(data);
            case ACL:
                return Mumble.ACL.parseFrom(data);
            case QueryUsers:
                return Mumble.QueryUsers.parseFrom(data);
            case Ping:
                return Mumble.Ping.parseFrom(data);
            case CryptSetup:
                return Mumble.CryptSetup.parseFrom(data);
            case ContextAction:
                return Mumble.ContextAction.parseFrom(data);
            case ContextActionModify:
                return Mumble.ContextActionModify.parseFrom(data);
            case Version:
                return Mumble.Version.parseFrom(data);
            case UserList:
                return Mumble.UserList.parseFrom(data);
            case PermissionQuery:
                return Mumble.PermissionQuery.parseFrom(data);
            case CodecVersion:
                return Mumble.CodecVersion.parseFrom(data);
            case UserStats:
                return Mumble.UserStats.parseFrom(data);
            case RequestBlob:
                return Mumble.RequestBlob.parseFrom(data);
            case SuggestConfig:
                return Mumble.SuggestConfig.parseFrom(data);
            default:
                throw new InvalidProtocolBufferException("Unknown TCP data passed.");
        }
    }


    /**
     * Reroutes TCP messages into the various responder methods of the handler.
     * @param handler Handler.
     * @param msg Protobuf message.
     * @param messageType The type of the message.
     */
    public final void broadcastTCPMessage(JumbleMessageHandler handler, Message msg, JumbleTCPMessageType messageType) {
        switch (messageType) {
            case Authenticate:
                handler.messageAuthenticate((Mumble.Authenticate) msg);
                break;
            case BanList:
                handler.messageBanList((Mumble.BanList) msg);
                break;
            case Reject:
                handler.messageReject((Mumble.Reject) msg);
                break;
            case ServerSync:
                handler.messageServerSync((Mumble.ServerSync) msg);
                break;
            case ServerConfig:
                handler.messageServerConfig((Mumble.ServerConfig) msg);
                break;
            case PermissionDenied:
                handler.messagePermissionDenied((Mumble.PermissionDenied) msg);
                break;
            case UDPTunnel:
                handler.messageUDPTunnel((Mumble.UDPTunnel) msg);
                break;
            case UserState:
                handler.messageUserState((Mumble.UserState) msg);
                break;
            case UserRemove:
                handler.messageUserRemove((Mumble.UserRemove) msg);
                break;
            case ChannelState:
                handler.messageChannelState((Mumble.ChannelState) msg);
                break;
            case ChannelRemove:
                handler.messageChannelRemove((Mumble.ChannelRemove) msg);
                break;
            case TextMessage:
                handler.messageTextMessage((Mumble.TextMessage) msg);
                break;
            case ACL:
                handler.messageACL((Mumble.ACL) msg);
                break;
            case QueryUsers:
                handler.messageQueryUsers((Mumble.QueryUsers) msg);
                break;
            case Ping:
                handler.messagePing((Mumble.Ping) msg);
                break;
            case CryptSetup:
                handler.messageCryptSetup((Mumble.CryptSetup) msg);
                break;
            case ContextAction:
                handler.messageContextAction((Mumble.ContextAction) msg);
                break;
            case ContextActionModify:
                Mumble.ContextActionModify actionModify = (Mumble.ContextActionModify) msg;
                if (actionModify.getOperation() == Mumble.ContextActionModify.Operation.Add)
                    handler.messageContextActionModify(actionModify);
                else if (actionModify.getOperation() == Mumble.ContextActionModify.Operation.Remove)
                    handler.messageRemoveContextAction(actionModify);
                break;
            case Version:
                handler.messageVersion((Mumble.Version) msg);
                break;
            case UserList:
                handler.messageUserList((Mumble.UserList) msg);
                break;
            case PermissionQuery:
                handler.messagePermissionQuery((Mumble.PermissionQuery) msg);
                break;
            case CodecVersion:
                handler.messageCodecVersion((Mumble.CodecVersion) msg);
                break;
            case UserStats:
                handler.messageUserStats((Mumble.UserStats) msg);
                break;
            case RequestBlob:
                handler.messageRequestBlob((Mumble.RequestBlob) msg);
                break;
            case SuggestConfig:
                handler.messageSuggestConfig((Mumble.SuggestConfig) msg);
                break;
            case VoiceTarget:
                handler.messageVoiceTarget((Mumble.VoiceTarget) msg);
                break;
        }
    }

    /**
     * Reroutes UDP messages into the various responder methods of the passed handler.
     * @param handler Handler to notify.
     * @param data Raw UDP data of the message.
     * @param messageType The type of the message.
     */
    public final void broadcastUDPMessage(JumbleMessageHandler handler, byte[] data, JumbleUDPMessageType messageType) {
        switch (messageType) {
            case UDPVoiceCELTAlpha:
                handler.messageUDPCELTAlpha(data);
                break;
            case UDPPing:
                handler.messageUDPPing(data);
                break;
            case UDPVoiceSpeex:
                handler.messageUDPSpeex(data);
                break;
            case UDPVoiceCELTBeta:
                handler.messageUDPCELTBeta(data);
                break;
            case UDPVoiceOpus:
                handler.messageUDPOpus(data);
                break;
        }
    }

    /**
     * Class to maintain and interface with the TCP connection to a Mumble server.
     */
    private class JumbleTCP implements Runnable {
        private SSLSocket mTCPSocket;
        private DataInputStream mDataInput;
        private DataOutputStream mDataOutput;

        /**
         * Attempts to disconnect gracefully.
         * @throws IOException if the socket couldn't close as expected.
         */
        public void disconnect() throws IOException {
            mDataOutput.close();
            mDataInput.close();
            mTCPSocket.close();
        }

        public void run() {
            try {
                mTCPSocket = (SSLSocket)mSocketFactory.createSocket();
                mTCPSocket.setKeepAlive(true);
                mTCPSocket.setEnabledProtocols(new String[] {"TLSv1"});
                mTCPSocket.setUseClientMode(true);

                HttpParams httpParams = new BasicHttpParams();
                mSocketFactory.connectSocket(mTCPSocket, mParams.server.getHost(), mParams.server.getPort(), null, 0, httpParams);

                mTCPSocket.startHandshake();

                Log.v(Constants.TAG, "Started handshake");

                mDataInput = new DataInputStream(mTCPSocket.getInputStream());
                mDataOutput = new DataOutputStream(mTCPSocket.getOutputStream());

                // Send version information and authenticate.
                final Mumble.Version.Builder version = Mumble.Version.newBuilder();
                version.setRelease(mParams.clientName);
                version.setVersion(Constants.PROTOCOL_VERSION);
                version.setOs("Android");
                version.setOsVersion(Build.VERSION.RELEASE);

                final Mumble.Authenticate.Builder auth = Mumble.Authenticate.newBuilder();
                auth.setUsername(mParams.server.getUsername());
                auth.setPassword(mParams.server.getPassword());
                auth.addCeltVersions(Constants.CELT_VERSION);
                auth.setOpus(mParams.useOpus);

                sendTCPMessage(version.build(), JumbleTCPMessageType.Version);
                sendTCPMessage(auth.build(), JumbleTCPMessageType.Authenticate);
            } catch (SocketException e) {
                handleFatalException(new JumbleConnectionException("Could not open a connection to the host", e, false));
                return;
            } catch (IOException e) {
                handleFatalException(new JumbleConnectionException("An error occurred when communicating with the host", e, false));
                return;
            }

            mConnected = true;

            Log.v(Constants.TAG, "Started listening");

            if(!mParams.forceTcp) {
                mUDP = new JumbleUDP();
                mExecutorService.submit(mUDP);
            }

            while(mConnected) {
                try {
                    final short messageType = mDataInput.readShort();
                    int messageLength = mDataInput.readInt();
                    final byte[] data = new byte[messageLength];
                    mDataInput.readFully(data);

                    JumbleTCPMessageType tcpMessageType = JumbleTCPMessageType.values()[messageType];
                    handleTCPMessage(data, messageLength, tcpMessageType);
                } catch (IOException e) {
                    if(!mConnected) // Only handle unexpected exceptions here. This could be the result of a clean disconnect like a Reject or UserRemove.
                        handleFatalException(new JumbleConnectionException("Lost connection to server", e, true));
                    break;
                }
            }

            mConnected = false;

            if(mListener != null) {
                mMainHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        mListener.onConnectionDisconnected();
                    }
                });
            }
        }

        /**
         * Attempts to send a protobuf message over TCP.
         * @param message The message to send.
         * @param messageType The type of the message to send.
         * @throws IOException if we can't write the message to the server.
         */
        public void sendMessage(Message message, JumbleTCPMessageType messageType) throws IOException {
            Log.v(Constants.TAG, "OUT: "+messageType);
            mDataOutput.writeShort(messageType.ordinal());
            mDataOutput.writeInt(message.getSerializedSize());
            message.writeTo(mDataOutput);
        }
        /**
         * Attempts to send a protobuf message over TCP.
         * @param message The data to send.
         * @param messageType The type of the message to send.
         * @throws IOException if we can't write the message to the server.
         */
        public void sendMessage(byte[] message, JumbleTCPMessageType messageType) throws IOException {
            Log.v(Constants.TAG, "OUT: "+messageType);
            mDataOutput.writeShort(messageType.ordinal());
            mDataOutput.writeInt(message.length);
            mDataOutput.write(message);
        }

        public void sendData(byte[] data) throws  IOException {
            mDataOutput.write(data);
        }
    }

    /**
     * Class to maintain and receive packets from the UDP connection to a Mumble server.
     */
    private class JumbleUDP implements Runnable {
        private static final int BUFFER_SIZE = 2048;
        private DatagramSocket mUDPSocket;

        public void disconnect() {
            mUDPSocket.disconnect();
        }

        @Override
        public void run() {
            try {
                mUDPSocket = new DatagramSocket();
                mUDPSocket.connect(mHost, mParams.server.getPort());
            } catch (SocketException e) {
                handleFatalException(new JumbleConnectionException("Could not open a connection to the host", e, false));
            }

            DatagramPacket packet = new DatagramPacket(new byte[BUFFER_SIZE], BUFFER_SIZE);

            Log.v(Constants.TAG, "Created UDP socket");

            while(mConnected) {
                try {
                    mUDPSocket.receive(packet);
                    // Decrypt UDP packet using OCB-AES128
                    final byte[] decryptedData = new byte[packet.getLength()];
                    if(!mCryptState.decrypt(packet.getData(), decryptedData, packet.getLength()) &&
                            mCryptState.getLastGoodElapsed() > 5000000 &&
                            mCryptState.getLastRequestElapsed() > 5000000) {
                        // If decryption fails, request resync
                        mCryptState.mLastRequestStart = System.nanoTime();
                        Mumble.CryptSetup.Builder csb = Mumble.CryptSetup.newBuilder();
                        mTCP.sendMessage(csb.build(), JumbleTCPMessageType.CryptSetup);
                    }
                    handleUDPMessage(decryptedData);
                } catch (IOException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }

        public void sendMessage(byte[] data, int length, JumbleUDPMessageType messageType, boolean force) throws IOException {
            if(!mCryptState.isValid())
                return;

            if(!force && (mParams.forceTcp || !mUsingUDP)) {
                ByteBuffer bb = ByteBuffer.allocate(length + 6);
                bb.putShort((short) JumbleUDPMessageType.UDPPing.ordinal());
                bb.putInt(length);
                bb.put(data);
                mTCP.sendData(bb.array());
            } else {
                byte[] encryptedData = new byte[length];
                mCryptState.encrypt(data, encryptedData, length);
                DatagramPacket packet = new DatagramPacket(encryptedData, length);
                packet.setAddress(mHost);
                packet.setPort(mParams.server.getPort());
                mUDPSocket.send(packet);
            }
        }
    }
}
