/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class StratigraphicColumnRankInterpretationVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public StratigraphicColumnRankInterpretationVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(StratigraphicColumnRankInterpretationVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_StratigraphicColumnRankInterpretationVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public StratigraphicColumnRankInterpretationVector() {
    this(energisticsApiJNI.new_StratigraphicColumnRankInterpretationVector__SWIG_0(), true);
  }

  public StratigraphicColumnRankInterpretationVector(long n) {
    this(energisticsApiJNI.new_StratigraphicColumnRankInterpretationVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.StratigraphicColumnRankInterpretationVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.StratigraphicColumnRankInterpretationVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.StratigraphicColumnRankInterpretationVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.StratigraphicColumnRankInterpretationVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.StratigraphicColumnRankInterpretationVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation x) {
    energisticsApiJNI.StratigraphicColumnRankInterpretationVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation get(int i) {
    long cPtr = energisticsApiJNI.StratigraphicColumnRankInterpretationVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation val) {
    energisticsApiJNI.StratigraphicColumnRankInterpretationVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation.getCPtr(val), val);
  }

}
