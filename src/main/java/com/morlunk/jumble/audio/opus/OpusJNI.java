/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.morlunk.jumble.audio.opus;

public class OpusJNI {

  static {
      System.loadLibrary("opus");
  }

  public final static native int OPUS_OK_get();
  public final static native int OPUS_BAD_ARG_get();
  public final static native int OPUS_BUFFER_TOO_SMALL_get();
  public final static native int OPUS_INTERNAL_ERROR_get();
  public final static native int OPUS_INVALID_PACKET_get();
  public final static native int OPUS_UNIMPLEMENTED_get();
  public final static native int OPUS_INVALID_STATE_get();
  public final static native int OPUS_ALLOC_FAIL_get();
  public final static native int OPUS_SET_APPLICATION_REQUEST_get();
  public final static native int OPUS_GET_APPLICATION_REQUEST_get();
  public final static native int OPUS_SET_BITRATE_REQUEST_get();
  public final static native int OPUS_GET_BITRATE_REQUEST_get();
  public final static native int OPUS_SET_MAX_BANDWIDTH_REQUEST_get();
  public final static native int OPUS_GET_MAX_BANDWIDTH_REQUEST_get();
  public final static native int OPUS_SET_VBR_REQUEST_get();
  public final static native int OPUS_GET_VBR_REQUEST_get();
  public final static native int OPUS_SET_BANDWIDTH_REQUEST_get();
  public final static native int OPUS_GET_BANDWIDTH_REQUEST_get();
  public final static native int OPUS_SET_COMPLEXITY_REQUEST_get();
  public final static native int OPUS_GET_COMPLEXITY_REQUEST_get();
  public final static native int OPUS_SET_INBAND_FEC_REQUEST_get();
  public final static native int OPUS_GET_INBAND_FEC_REQUEST_get();
  public final static native int OPUS_SET_PACKET_LOSS_PERC_REQUEST_get();
  public final static native int OPUS_GET_PACKET_LOSS_PERC_REQUEST_get();
  public final static native int OPUS_SET_DTX_REQUEST_get();
  public final static native int OPUS_GET_DTX_REQUEST_get();
  public final static native int OPUS_SET_VBR_CONSTRAINT_REQUEST_get();
  public final static native int OPUS_GET_VBR_CONSTRAINT_REQUEST_get();
  public final static native int OPUS_SET_FORCE_CHANNELS_REQUEST_get();
  public final static native int OPUS_GET_FORCE_CHANNELS_REQUEST_get();
  public final static native int OPUS_SET_SIGNAL_REQUEST_get();
  public final static native int OPUS_GET_SIGNAL_REQUEST_get();
  public final static native int OPUS_GET_LOOKAHEAD_REQUEST_get();
  public final static native int OPUS_GET_SAMPLE_RATE_REQUEST_get();
  public final static native int OPUS_GET_FINAL_RANGE_REQUEST_get();
  public final static native int OPUS_GET_PITCH_REQUEST_get();
  public final static native int OPUS_SET_GAIN_REQUEST_get();
  public final static native int OPUS_GET_GAIN_REQUEST_get();
  public final static native int OPUS_SET_LSB_DEPTH_REQUEST_get();
  public final static native int OPUS_GET_LSB_DEPTH_REQUEST_get();
  public final static native int OPUS_GET_LAST_PACKET_DURATION_REQUEST_get();
  public final static native int OPUS_SET_EXPERT_FRAME_DURATION_REQUEST_get();
  public final static native int OPUS_GET_EXPERT_FRAME_DURATION_REQUEST_get();
  public final static native int OPUS_AUTO_get();
  public final static native int OPUS_BITRATE_MAX_get();
  public final static native int OPUS_APPLICATION_VOIP_get();
  public final static native int OPUS_APPLICATION_AUDIO_get();
  public final static native int OPUS_APPLICATION_RESTRICTED_LOWDELAY_get();
  public final static native int OPUS_SIGNAL_VOICE_get();
  public final static native int OPUS_SIGNAL_MUSIC_get();
  public final static native int OPUS_BANDWIDTH_NARROWBAND_get();
  public final static native int OPUS_BANDWIDTH_MEDIUMBAND_get();
  public final static native int OPUS_BANDWIDTH_WIDEBAND_get();
  public final static native int OPUS_BANDWIDTH_SUPERWIDEBAND_get();
  public final static native int OPUS_BANDWIDTH_FULLBAND_get();
  public final static native int OPUS_FRAMESIZE_ARG_get();
  public final static native int OPUS_FRAMESIZE_2_5_MS_get();
  public final static native int OPUS_FRAMESIZE_5_MS_get();
  public final static native int OPUS_FRAMESIZE_10_MS_get();
  public final static native int OPUS_FRAMESIZE_20_MS_get();
  public final static native int OPUS_FRAMESIZE_40_MS_get();
  public final static native int OPUS_FRAMESIZE_60_MS_get();
  public final static native int OPUS_FRAMESIZE_VARIABLE_get();
  public final static native int OPUS_RESET_STATE_get();
  public final static native byte[] opus_strerror(int jarg1);
  public final static native byte[] opus_get_version_string();
  public final static native int opus_encoder_get_size(int jarg1);
  public final static native long opus_encoder_create(int jarg1, int jarg2, int jarg3, int[] jarg4);
  public final static native int opus_encoder_init(long jarg1, int jarg2, int jarg3, int jarg4);
  public final static native int opus_encode(long jarg1, short[] jarg2, int jarg3, byte[] jarg4, int jarg5);
  public final static native int opus_encode_float(long jarg1, float[] jarg2, int jarg3, byte[] jarg4, int jarg5);
  public final static native void opus_encoder_destroy(long jarg1);
  public final static native int opus_encoder_ctl(long jarg1, int jarg2, int[] jarg3);
  public final static native int opus_decoder_get_size(int jarg1);
  public final static native long opus_decoder_create(int jarg1, int jarg2, int[] jarg3);
  public final static native int opus_decoder_init(long jarg1, int jarg2, int jarg3);
  public final static native int opus_decode(long jarg1, byte[] jarg2, int jarg3, short[] jarg4, int jarg5, int jarg6);
  public final static native int opus_decode_float(long jarg1, byte[] jarg2, int jarg3, float[] jarg4, int jarg5, int jarg6);
  public final static native int opus_decoder_ctl(long jarg1, int jarg2);
  public final static native void opus_decoder_destroy(long jarg1);
  public final static native int opus_packet_parse(byte[] jarg1, int jarg2, byte[] jarg3, long jarg4, long jarg5, int[] jarg6);
  public final static native int opus_packet_get_bandwidth(byte[] jarg1);
  public final static native int opus_packet_get_samples_per_frame(byte[] jarg1, int jarg2);
  public final static native int opus_packet_get_nb_channels(byte[] jarg1);
  public final static native int opus_packet_get_nb_frames(byte[] jarg1, int jarg2);
  public final static native int opus_packet_get_nb_samples(byte[] jarg1, int jarg2, int jarg3);
  public final static native int opus_decoder_get_nb_samples(long jarg1, byte[] jarg2, int jarg3);
  public final static native void opus_pcm_soft_clip(float[] jarg1, int jarg2, int jarg3, float[] jarg4);
  public final static native int opus_repacketizer_get_size();
  public final static native long opus_repacketizer_init(long jarg1);
  public final static native long opus_repacketizer_create();
  public final static native void opus_repacketizer_destroy(long jarg1);
  public final static native int opus_repacketizer_cat(long jarg1, byte[] jarg2, int jarg3);
  public final static native int opus_repacketizer_out_range(long jarg1, int jarg2, int jarg3, byte[] jarg4, int jarg5);
  public final static native int opus_repacketizer_get_nb_frames(long jarg1);
  public final static native int opus_repacketizer_out(long jarg1, byte[] jarg2, int jarg3);
}
