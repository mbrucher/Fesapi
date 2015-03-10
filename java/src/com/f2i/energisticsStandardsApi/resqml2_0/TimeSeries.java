/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class TimeSeries extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractResqmlDataObject {
  private long swigCPtr;

  public TimeSeries(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_TimeSeries_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(TimeSeries obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_TimeSeries(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public void pushBackTimestamp(long timestamp) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_TimeSeries_pushBackTimestamp(swigCPtr, this, timestamp);
  }

  public long getTimestampIndex(long timestamp) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_TimeSeries_getTimestampIndex(swigCPtr, this, timestamp);
  }

  public long getTimestampCount() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_TimeSeries_getTimestampCount(swigCPtr, this);
  }

  public long getTimestamp(long index) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_TimeSeries_getTimestamp(swigCPtr, this, index);
  }

}
