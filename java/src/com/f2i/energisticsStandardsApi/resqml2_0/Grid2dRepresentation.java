/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.resqml2_0;

		import com.f2i.energisticsStandardsApi.*;
	
public class Grid2dRepresentation extends com.f2i.energisticsStandardsApi.resqml2_0.AbstractSurfaceRepresentation {
  private long swigCPtr;

  public Grid2dRepresentation(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Grid2dRepresentation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_resqml2_0_Grid2dRepresentation(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public long getNodeCountAlongIAxis() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getNodeCountAlongIAxis(swigCPtr, this);
  }

  public long getNodeCountAlongJAxis() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getNodeCountAlongJAxis(swigCPtr, this);
  }

  public double getXOrigin() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getXOrigin(swigCPtr, this);
  }

  public double getYOrigin() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getYOrigin(swigCPtr, this);
  }

  public double getXOriginInGlobalCrs() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getXOriginInGlobalCrs(swigCPtr, this);
  }

  public double getYOriginInGlobalCrs() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getYOriginInGlobalCrs(swigCPtr, this);
  }

  public double getXJOffset() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getXJOffset(swigCPtr, this);
  }

  public double getYJOffset() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getYJOffset(swigCPtr, this);
  }

  public double getXJOffsetInGlobalCrs() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getXJOffsetInGlobalCrs(swigCPtr, this);
  }

  public double getYJOffsetInGlobalCrs() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getYJOffsetInGlobalCrs(swigCPtr, this);
  }

  public double getXIOffset() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getXIOffset(swigCPtr, this);
  }

  public double getYIOffset() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getYIOffset(swigCPtr, this);
  }

  public double getXIOffsetInGlobalCrs() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getXIOffsetInGlobalCrs(swigCPtr, this);
  }

  public double getYIOffsetInGlobalCrs() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getYIOffsetInGlobalCrs(swigCPtr, this);
  }

  public double getJSpacing() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getJSpacing(swigCPtr, this);
  }

  public double getISpacing() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getISpacing(swigCPtr, this);
  }

  public void getZValues(SWIGTYPE_p_double values) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getZValues(swigCPtr, this, SWIGTYPE_p_double.getCPtr(values));
  }

  public void getZValuesInGlobalCrs(SWIGTYPE_p_double values) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getZValuesInGlobalCrs(swigCPtr, this, SWIGTYPE_p_double.getCPtr(values));
  }

  public int getIndexOriginOnSupportingRepresentation() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getIndexOriginOnSupportingRepresentation__SWIG_0(swigCPtr, this);
  }

  public int getIndexOriginOnSupportingRepresentation(long dimension) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getIndexOriginOnSupportingRepresentation__SWIG_1(swigCPtr, this, dimension);
  }

  public int getNodeCountOnSupportingRepresentation(long dimension) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getNodeCountOnSupportingRepresentation(swigCPtr, this, dimension);
  }

  public int getIndexOffsetOnSupportingRepresentation(long dimension) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getIndexOffsetOnSupportingRepresentation(swigCPtr, this, dimension);
  }

  public void setGeometryAsArray2dOfLatticePoints3d(long numPointsInFastestDirection, long numPointsInSlowestDirection, double xOrigin, double yOrigin, double zOrigin, double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection, double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection, double spacingInFastestDirection, double spacingInSlowestDirection) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfLatticePoints3d(swigCPtr, this, numPointsInFastestDirection, numPointsInSlowestDirection, xOrigin, yOrigin, zOrigin, xOffsetInFastestDirection, yOffsetInFastestDirection, zOffsetInFastestDirection, xOffsetInSlowestDirection, yOffsetInSlowestDirection, zOffsetInSlowestDirection, spacingInFastestDirection, spacingInSlowestDirection);
  }

  public void setGeometryAsArray2dOfExplicitZ(SWIGTYPE_p_double zValues, long numI, long numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation supportingGrid2dRepresentation, long startIndexI, long startIndexJ, int indexIncrementI, int indexIncrementJ) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfExplicitZ__SWIG_0(swigCPtr, this, SWIGTYPE_p_double.getCPtr(zValues), numI, numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation.getCPtr(supportingGrid2dRepresentation), supportingGrid2dRepresentation, startIndexI, startIndexJ, indexIncrementI, indexIncrementJ);
  }

  public void setGeometryAsArray2dOfExplicitZ(SWIGTYPE_p_double zValues, long numI, long numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation supportingGrid2dRepresentation, long startIndexI, long startIndexJ, int indexIncrementI) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfExplicitZ__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(zValues), numI, numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation.getCPtr(supportingGrid2dRepresentation), supportingGrid2dRepresentation, startIndexI, startIndexJ, indexIncrementI);
  }

  public void setGeometryAsArray2dOfExplicitZ(SWIGTYPE_p_double zValues, long numI, long numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation supportingGrid2dRepresentation, long startIndexI, long startIndexJ) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfExplicitZ__SWIG_2(swigCPtr, this, SWIGTYPE_p_double.getCPtr(zValues), numI, numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation.getCPtr(supportingGrid2dRepresentation), supportingGrid2dRepresentation, startIndexI, startIndexJ);
  }

  public void setGeometryAsArray2dOfExplicitZ(SWIGTYPE_p_double zValues, long numI, long numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation supportingGrid2dRepresentation, long startIndexI) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfExplicitZ__SWIG_3(swigCPtr, this, SWIGTYPE_p_double.getCPtr(zValues), numI, numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation.getCPtr(supportingGrid2dRepresentation), supportingGrid2dRepresentation, startIndexI);
  }

  public void setGeometryAsArray2dOfExplicitZ(SWIGTYPE_p_double zValues, long numI, long numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation supportingGrid2dRepresentation) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfExplicitZ__SWIG_4(swigCPtr, this, SWIGTYPE_p_double.getCPtr(zValues), numI, numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy, com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation.getCPtr(supportingGrid2dRepresentation), supportingGrid2dRepresentation);
  }

  public void setGeometryAsArray2dOfExplicitZ(SWIGTYPE_p_double zValues, long numI, long numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double originX, double originY, double originZ, double offsetIX, double offsetIY, double offsetIZ, double spacingI, double offsetJX, double offsetJY, double offsetJZ, double spacingJ) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_setGeometryAsArray2dOfExplicitZ__SWIG_5(swigCPtr, this, SWIGTYPE_p_double.getCPtr(zValues), numI, numJ, com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), proxy, originX, originY, originZ, offsetIX, offsetIY, offsetIZ, spacingI, offsetJX, offsetJY, offsetJZ, spacingJ);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation getSupportingRepresentation() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getSupportingRepresentation(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation(cPtr, false);
  }

  public String getSupportingRepresentationUuid() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.resqml2_0_Grid2dRepresentation_getSupportingRepresentationUuid(swigCPtr, this);
  }

}