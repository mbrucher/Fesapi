/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class RepresentationSetRepresentation extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation {
  private long swigCPtr;

  public RepresentationSetRepresentation(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_RepresentationSetRepresentation_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(RepresentationSetRepresentation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_RepresentationSetRepresentation(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

}
