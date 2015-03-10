/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class AbstractProperty extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractResqmlDataObject {
  private long swigCPtr;

  public AbstractProperty(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(AbstractProperty obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_AbstractProperty(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public String getRepresentationUuid() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getRepresentationUuid(swigCPtr, this);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation getRepresentation() {
		long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getRepresentation(swigCPtr, this);
		com.f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation ret = (com.f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation) energisticsApiJNI.resqml2_0_instantiateConcreteObject(cPtr, false);
		return ret;
	}

  public String getHdfProxyUuid() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getHdfProxyUuid(swigCPtr, this);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy getHdfProxy() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getHdfProxy(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy(cPtr, false);
  }

  public String getPropertyKindUomAsString() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getPropertyKindUomAsString(swigCPtr, this);
  }

  public String getPropertyKindDescription() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getPropertyKindDescription(swigCPtr, this);
  }

  public String getPropertyKindAsString() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getPropertyKindAsString(swigCPtr, this);
  }

  public String getPropertyKindParentAsString() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getPropertyKindParentAsString(swigCPtr, this);
  }

  public boolean isAssociatedToOneStandardEnergisticsPropertyKind() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_isAssociatedToOneStandardEnergisticsPropertyKind(swigCPtr, this);
  }

  public resqml2__ResqmlPropertyKind getEnergisticsPropertyKind() {
    return resqml2__ResqmlPropertyKind.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getEnergisticsPropertyKind(swigCPtr, this));
  }

  public String getLocalPropertyKindUuid() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getLocalPropertyKindUuid(swigCPtr, this);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.PropertyKind getLocalPropertyKind() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getLocalPropertyKind(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.PropertyKind(cPtr, false);
  }

  public long getElementCountPerValue() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getElementCountPerValue(swigCPtr, this);
  }

  public resqml2__IndexableElements getAttachmentKind() {
    return resqml2__IndexableElements.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getAttachmentKind(swigCPtr, this));
  }

  public void setTimeIndex(long timeIndex, com.f2i.energisticsStandardsApi.resqml2_0.TimeSeries ts) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_setTimeIndex(swigCPtr, this, timeIndex, com.f2i.energisticsStandardsApi.resqml2_0.TimeSeries.getCPtr(ts), ts);
  }

  public void setTimeStep(long timeStep) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_setTimeStep(swigCPtr, this, timeStep);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.TimeSeries getTimeSeries() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getTimeSeries(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.TimeSeries(cPtr, false);
  }

  public long getTimestamp() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_AbstractProperty_getTimestamp(swigCPtr, this);
  }

}
