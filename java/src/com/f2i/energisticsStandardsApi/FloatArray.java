/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class FloatArray {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public FloatArray(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(FloatArray obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_FloatArray(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public FloatArray(int nelements) {
    this(energisticsApiJNI.new_FloatArray(nelements), true);
  }

  public float getitem(int index) {
    return energisticsApiJNI.FloatArray_getitem(swigCPtr, this, index);
  }

  public void setitem(int index, float value) {
    energisticsApiJNI.FloatArray_setitem(swigCPtr, this, index, value);
  }

  public SWIGTYPE_p_float cast() {
    long cPtr = energisticsApiJNI.FloatArray_cast(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_float(cPtr, false);
  }

  public static FloatArray frompointer(SWIGTYPE_p_float t) {
    long cPtr = energisticsApiJNI.FloatArray_frompointer(SWIGTYPE_p_float.getCPtr(t));
    return (cPtr == 0) ? null : new FloatArray(cPtr, false);
  }

}