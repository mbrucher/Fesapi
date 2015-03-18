/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class WellboreMarker extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractResqmlDataObject {
  private long swigCPtr;

  public WellboreMarker(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_WellboreMarker_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(WellboreMarker obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_WellboreMarker(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public boolean hasAGeologicBoundaryKind() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_WellboreMarker_hasAGeologicBoundaryKind(swigCPtr, this);
  }

  public resqml2__GeologicBoundaryKind getGeologicBoundaryKind() {
    return resqml2__GeologicBoundaryKind.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_WellboreMarker_getGeologicBoundaryKind(swigCPtr, this));
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation getHorizonInterpretation() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_WellboreMarker_getHorizonInterpretation(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation(cPtr, false);
  }

  public String getHorizonInterpretationUuid() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_WellboreMarker_getHorizonInterpretationUuid(swigCPtr, this);
  }

  public void setHorizonInterpretation(com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation interp) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_WellboreMarker_setHorizonInterpretation(swigCPtr, this, com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation.getCPtr(interp), interp);
  }

}