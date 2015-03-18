/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class PolylineSetRepresentationVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public PolylineSetRepresentationVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(PolylineSetRepresentationVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_PolylineSetRepresentationVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public PolylineSetRepresentationVector() {
    this(energisticsApiJNI.new_PolylineSetRepresentationVector__SWIG_0(), true);
  }

  public PolylineSetRepresentationVector(long n) {
    this(energisticsApiJNI.new_PolylineSetRepresentationVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.PolylineSetRepresentationVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.PolylineSetRepresentationVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.PolylineSetRepresentationVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.PolylineSetRepresentationVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.PolylineSetRepresentationVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation x) {
    energisticsApiJNI.PolylineSetRepresentationVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation get(int i) {
    long cPtr = energisticsApiJNI.PolylineSetRepresentationVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation val) {
    energisticsApiJNI.PolylineSetRepresentationVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation.getCPtr(val), val);
  }

}