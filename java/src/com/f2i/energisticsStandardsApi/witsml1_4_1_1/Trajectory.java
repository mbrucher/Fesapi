/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi.witsml1_4_1_1;

		import com.f2i.energisticsStandardsApi.*;
	
public class Trajectory extends com.f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject {
  private long swigCPtr;

  public Trajectory(long cPtr, boolean cMemoryOwn) {
    super(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Trajectory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        com.f2i.energisticsStandardsApi.energisticsApiJNI.delete_witsml1_4_1_1_Trajectory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public double getMdDatumElevation() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getMdDatumElevation(swigCPtr, this);
  }

  public witsml1__WellVerticalCoordinateUom getMdDatumElevationUom() {
    return witsml1__WellVerticalCoordinateUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getMdDatumElevationUom(swigCPtr, this));
  }

  public String getMdDatumName() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getMdDatumName(swigCPtr, this);
  }

  public long getTrajectoryStationCount() {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getTrajectoryStationCount(swigCPtr, this);
  }

  public void getMds(SWIGTYPE_p_double mds) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getMds(swigCPtr, this, SWIGTYPE_p_double.getCPtr(mds));
  }

  public witsml1__MeasuredDepthUom getMdUom() {
    return witsml1__MeasuredDepthUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getMdUom(swigCPtr, this));
  }

  public long getInclinometries(SWIGTYPE_p_double incls) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getInclinometries(swigCPtr, this, SWIGTYPE_p_double.getCPtr(incls));
  }

  public witsml1__PlaneAngleUom getInclinometryUom() {
    return witsml1__PlaneAngleUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getInclinometryUom(swigCPtr, this));
  }

  public long getAzimuths(SWIGTYPE_p_double azims) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getAzimuths(swigCPtr, this, SWIGTYPE_p_double.getCPtr(azims));
  }

  public witsml1__PlaneAngleUom getAzimuthUom() {
    return witsml1__PlaneAngleUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getAzimuthUom(swigCPtr, this));
  }

  public witsml1__AziRef getAzimuthReference() {
    return witsml1__AziRef.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getAzimuthReference(swigCPtr, this));
  }

  public long getEastings(SWIGTYPE_p_double eastings) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getEastings(swigCPtr, this, SWIGTYPE_p_double.getCPtr(eastings));
  }

  public witsml1__LengthUom getEastingUom() {
    return witsml1__LengthUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getEastingUom(swigCPtr, this));
  }

  public long getNorthings(SWIGTYPE_p_double northings) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getNorthings(swigCPtr, this, SWIGTYPE_p_double.getCPtr(northings));
  }

  public witsml1__LengthUom getNorthingUom() {
    return witsml1__LengthUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getNorthingUom(swigCPtr, this));
  }

  public long getTvds(SWIGTYPE_p_double tvds) {
    return com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getTvds(swigCPtr, this, SWIGTYPE_p_double.getCPtr(tvds));
  }

  public witsml1__WellVerticalCoordinateUom getTvdUom() {
    return witsml1__WellVerticalCoordinateUom.swigToEnum(com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getTvdUom(swigCPtr, this));
  }

  public void setTrajectoryStations(long trajectoryStationCount, long mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_setTrajectoryStations(swigCPtr, this, trajectoryStationCount, mdDatumIndex, mDUom.swigValue(), SWIGTYPE_p_double.getCPtr(mDSet), angleUom.swigValue(), SWIGTYPE_p_double.getCPtr(inclSet), aziRef.swigValue(), SWIGTYPE_p_double.getCPtr(aziSet));
  }

  public void setEastingNorthingTrajectoryStations(long trajectoryStationCount, long mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, long tvdDatumIndex, witsml1__WellVerticalCoordinateUom tVDUom, SWIGTYPE_p_double tVDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet, witsml1__LengthUom locationUom, SWIGTYPE_p_double locationEastingSet, SWIGTYPE_p_double locationNorthingSet, com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_setEastingNorthingTrajectoryStations(swigCPtr, this, trajectoryStationCount, mdDatumIndex, mDUom.swigValue(), SWIGTYPE_p_double.getCPtr(mDSet), tvdDatumIndex, tVDUom.swigValue(), SWIGTYPE_p_double.getCPtr(tVDSet), angleUom.swigValue(), SWIGTYPE_p_double.getCPtr(inclSet), aziRef.swigValue(), SWIGTYPE_p_double.getCPtr(aziSet), locationUom.swigValue(), SWIGTYPE_p_double.getCPtr(locationEastingSet), SWIGTYPE_p_double.getCPtr(locationNorthingSet), com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs), wellCrs);
  }

  public void setWestingSouthingTrajectoryStations(long trajectoryStationCount, long mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, long tvdDatumIndex, witsml1__WellVerticalCoordinateUom tVDUom, SWIGTYPE_p_double tVDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet, witsml1__LengthUom locationUom, SWIGTYPE_p_double locationWestingSet, SWIGTYPE_p_double locationSouthingSet, com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_setWestingSouthingTrajectoryStations(swigCPtr, this, trajectoryStationCount, mdDatumIndex, mDUom.swigValue(), SWIGTYPE_p_double.getCPtr(mDSet), tvdDatumIndex, tVDUom.swigValue(), SWIGTYPE_p_double.getCPtr(tVDSet), angleUom.swigValue(), SWIGTYPE_p_double.getCPtr(inclSet), aziRef.swigValue(), SWIGTYPE_p_double.getCPtr(aziSet), locationUom.swigValue(), SWIGTYPE_p_double.getCPtr(locationWestingSet), SWIGTYPE_p_double.getCPtr(locationSouthingSet), com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs), wellCrs);
  }

  public void setProjectedXProjectedYTrajectoryStations(long trajectoryStationCount, long mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, long tvdDatumIndex, witsml1__WellVerticalCoordinateUom tVDUom, SWIGTYPE_p_double tVDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet, witsml1__LengthUom locationUom, SWIGTYPE_p_double locationProjectedXSet, SWIGTYPE_p_double locationProjectedYSet, com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_setProjectedXProjectedYTrajectoryStations(swigCPtr, this, trajectoryStationCount, mdDatumIndex, mDUom.swigValue(), SWIGTYPE_p_double.getCPtr(mDSet), tvdDatumIndex, tVDUom.swigValue(), SWIGTYPE_p_double.getCPtr(tVDSet), angleUom.swigValue(), SWIGTYPE_p_double.getCPtr(inclSet), aziRef.swigValue(), SWIGTYPE_p_double.getCPtr(aziSet), locationUom.swigValue(), SWIGTYPE_p_double.getCPtr(locationProjectedXSet), SWIGTYPE_p_double.getCPtr(locationProjectedYSet), com.f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs), wellCrs);
  }

  public com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore getWellbore() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getWellbore(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, false);
  }

  public com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation getResqmlWellboreTrajectoryRepresentation() {
    long cPtr = com.f2i.energisticsStandardsApi.energisticsApiJNI.witsml1_4_1_1_Trajectory_getResqmlWellboreTrajectoryRepresentation(swigCPtr, this);
    return (cPtr == 0) ? null : new com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation(cPtr, false);
  }

}
