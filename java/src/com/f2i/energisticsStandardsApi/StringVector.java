/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class StringVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public StringVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(StringVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_StringVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public StringVector() {
    this(energisticsApiJNI.new_StringVector__SWIG_0(), true);
  }

  public StringVector(long n) {
    this(energisticsApiJNI.new_StringVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.StringVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.StringVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.StringVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.StringVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.StringVector_clear(swigCPtr, this);
  }

  public void add(String x) {
    energisticsApiJNI.StringVector_add(swigCPtr, this, x);
  }

  public String get(int i) {
    return energisticsApiJNI.StringVector_get(swigCPtr, this, i);
  }

  public void set(int i, String val) {
    energisticsApiJNI.StringVector_set(swigCPtr, this, i, val);
  }

}
