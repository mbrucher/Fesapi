/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class HorizonInterpretationVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public HorizonInterpretationVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(HorizonInterpretationVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_HorizonInterpretationVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public HorizonInterpretationVector() {
    this(energisticsApiJNI.new_HorizonInterpretationVector__SWIG_0(), true);
  }

  public HorizonInterpretationVector(long n) {
    this(energisticsApiJNI.new_HorizonInterpretationVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.HorizonInterpretationVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.HorizonInterpretationVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.HorizonInterpretationVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.HorizonInterpretationVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.HorizonInterpretationVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation x) {
    energisticsApiJNI.HorizonInterpretationVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation get(int i) {
    long cPtr = energisticsApiJNI.HorizonInterpretationVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation val) {
    energisticsApiJNI.HorizonInterpretationVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation.getCPtr(val), val);
  }

}
