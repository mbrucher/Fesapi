/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public class WellboreTrajectoryRepresentationVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public WellboreTrajectoryRepresentationVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(WellboreTrajectoryRepresentationVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_WellboreTrajectoryRepresentationVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public WellboreTrajectoryRepresentationVector() {
    this(energisticsApiJNI.new_WellboreTrajectoryRepresentationVector__SWIG_0(), true);
  }

  public WellboreTrajectoryRepresentationVector(long n) {
    this(energisticsApiJNI.new_WellboreTrajectoryRepresentationVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.WellboreTrajectoryRepresentationVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.WellboreTrajectoryRepresentationVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.WellboreTrajectoryRepresentationVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.WellboreTrajectoryRepresentationVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.WellboreTrajectoryRepresentationVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation x) {
    energisticsApiJNI.WellboreTrajectoryRepresentationVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation get(int i) {
    long cPtr = energisticsApiJNI.WellboreTrajectoryRepresentationVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation val) {
    energisticsApiJNI.WellboreTrajectoryRepresentationVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation.getCPtr(val), val);
  }

}