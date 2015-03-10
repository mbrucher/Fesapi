/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class TriangulatedSetRepresentationVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public TriangulatedSetRepresentationVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(TriangulatedSetRepresentationVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_TriangulatedSetRepresentationVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public TriangulatedSetRepresentationVector() {
    this(energisticsApiJNI.new_TriangulatedSetRepresentationVector__SWIG_0(), true);
  }

  public TriangulatedSetRepresentationVector(long n) {
    this(energisticsApiJNI.new_TriangulatedSetRepresentationVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.TriangulatedSetRepresentationVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.TriangulatedSetRepresentationVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.TriangulatedSetRepresentationVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.TriangulatedSetRepresentationVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.TriangulatedSetRepresentationVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation x) {
    energisticsApiJNI.TriangulatedSetRepresentationVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation get(int i) {
    long cPtr = energisticsApiJNI.TriangulatedSetRepresentationVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation val) {
    energisticsApiJNI.TriangulatedSetRepresentationVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation.getCPtr(val), val);
  }

}
