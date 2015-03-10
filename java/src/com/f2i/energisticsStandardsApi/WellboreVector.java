/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

		import com.f2i.energisticsStandardsApi.*;
	
public class WellboreVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public WellboreVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(WellboreVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_WellboreVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public WellboreVector() {
    this(energisticsApiJNI.new_WellboreVector__SWIG_0(), true);
  }

  public WellboreVector(long n) {
    this(energisticsApiJNI.new_WellboreVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.WellboreVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.WellboreVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.WellboreVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.WellboreVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.WellboreVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore x) {
    energisticsApiJNI.WellboreVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore get(int i) {
    long cPtr = energisticsApiJNI.WellboreVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore val) {
    energisticsApiJNI.WellboreVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore.getCPtr(val), val);
  }

}
