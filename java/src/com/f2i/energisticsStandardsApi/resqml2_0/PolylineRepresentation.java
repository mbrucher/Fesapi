/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class PolylineRepresentation extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation {
  private long swigCPtr;

  public PolylineRepresentation(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_PolylineRepresentation_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(PolylineRepresentation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_PolylineRepresentation(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public void setGeometry(SWIGTYPE_p_double points, long pointCount, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_PolylineRepresentation_setGeometry(swigCPtr, this, SWIGTYPE_p_double.getCPtr(points), pointCount, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy);
  }

  public boolean isclosed() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_PolylineRepresentation_isclosed(swigCPtr, this);
  }

}
