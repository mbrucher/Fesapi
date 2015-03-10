/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class SeismicLatticeFeature extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractTechnicalFeature {
  private long swigCPtr;

  public SeismicLatticeFeature(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_SeismicLatticeFeature_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SeismicLatticeFeature obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_SeismicLatticeFeature(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public int getCrosslineIncrement() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_SeismicLatticeFeature_getCrosslineIncrement(swigCPtr, this);
  }

  public int getInlineIncrement() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_SeismicLatticeFeature_getInlineIncrement(swigCPtr, this);
  }

  public int getOriginCrossline() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_SeismicLatticeFeature_getOriginCrossline(swigCPtr, this);
  }

  public int getOriginInline() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_SeismicLatticeFeature_getOriginInline(swigCPtr, this);
  }

}
