/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.morlunk.jumble.audio.speex;

public class JitterBuffer {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected JitterBuffer(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(JitterBuffer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        SpeexJNI.delete_JitterBuffer(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public JitterBuffer() {
    this(SpeexJNI.new_JitterBuffer(), true);
  }

}