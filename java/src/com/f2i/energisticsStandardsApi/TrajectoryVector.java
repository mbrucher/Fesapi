/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

		import com.f2i.energisticsStandardsApi.*;
	
public class TrajectoryVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public TrajectoryVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(TrajectoryVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        energisticsApiJNI.delete_TrajectoryVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public TrajectoryVector() {
    this(energisticsApiJNI.new_TrajectoryVector__SWIG_0(), true);
  }

  public TrajectoryVector(long n) {
    this(energisticsApiJNI.new_TrajectoryVector__SWIG_1(n), true);
  }

  public long size() {
    return energisticsApiJNI.TrajectoryVector_size(swigCPtr, this);
  }

  public long capacity() {
    return energisticsApiJNI.TrajectoryVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    energisticsApiJNI.TrajectoryVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return energisticsApiJNI.TrajectoryVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    energisticsApiJNI.TrajectoryVector_clear(swigCPtr, this);
  }

  public void add(com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory x) {
    energisticsApiJNI.TrajectoryVector_add(swigCPtr, this, com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory.getCPtr(x), x);
  }

  public com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory get(int i) {
    long cPtr = energisticsApiJNI.TrajectoryVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory(cPtr, false);
  }

  public void set(int i, com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory val) {
    energisticsApiJNI.TrajectoryVector_set(swigCPtr, this, i, com.f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory.getCPtr(val), val);
  }

}