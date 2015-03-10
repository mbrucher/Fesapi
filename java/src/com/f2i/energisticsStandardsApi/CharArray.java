/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class CharArray {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public CharArray(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(CharArray obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_CharArray(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public CharArray(int nelements) {
    this(energisticsApiJNI.new_CharArray(nelements), true);
  }

  public char getitem(int index) {
    return energisticsApiJNI.CharArray_getitem(swigCPtr, this, index);
  }

  public void setitem(int index, char value) {
    energisticsApiJNI.CharArray_setitem(swigCPtr, this, index, value);
  }

  public String cast() {
    return energisticsApiJNI.CharArray_cast(swigCPtr, this);
  }

  public static CharArray frompointer(String t) {
    long cPtr = energisticsApiJNI.CharArray_frompointer(t);
    return (cPtr == 0) ? null : new CharArray(cPtr, false);
  }

}
