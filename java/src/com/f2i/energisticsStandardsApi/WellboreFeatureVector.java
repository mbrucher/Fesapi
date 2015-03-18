/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class WellboreFeatureVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public WellboreFeatureVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(WellboreFeatureVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_WellboreFeatureVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public WellboreFeatureVector() {
    this(energisticsApiJNI.new_WellboreFeatureVector__SWIG_0(), true);
  }

  public WellboreFeatureVector(long n) {
    this(energisticsApiJNI.new_WellboreFeatureVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.WellboreFeatureVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.WellboreFeatureVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.WellboreFeatureVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.WellboreFeatureVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.WellboreFeatureVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature x) {
    energisticsApiJNI.WellboreFeatureVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature get(int i) {
    long cPtr = energisticsApiJNI.WellboreFeatureVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature val) {
    energisticsApiJNI.WellboreFeatureVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature.getCPtr(val), val);
  }

}