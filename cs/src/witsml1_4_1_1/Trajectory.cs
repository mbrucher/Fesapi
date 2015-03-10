//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.5
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace f2i.energisticsStandardsApi.witsml1_4_1_1 {

public class Trajectory : f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal Trajectory(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Trajectory obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Trajectory() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_witsml1_4_1_1_Trajectory(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public double getMdDatumElevation() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getMdDatumElevation(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__WellVerticalCoordinateUom getMdDatumElevationUom() {
    witsml1__WellVerticalCoordinateUom ret = (witsml1__WellVerticalCoordinateUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getMdDatumElevationUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getMdDatumName() {
    string ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getMdDatumName(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getTrajectoryStationCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getTrajectoryStationCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getMds(SWIGTYPE_p_double mds) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getMds(swigCPtr, SWIGTYPE_p_double.getCPtr(mds));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public witsml1__MeasuredDepthUom getMdUom() {
    witsml1__MeasuredDepthUom ret = (witsml1__MeasuredDepthUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getMdUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getInclinometries(SWIGTYPE_p_double incls) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getInclinometries(swigCPtr, SWIGTYPE_p_double.getCPtr(incls));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__PlaneAngleUom getInclinometryUom() {
    witsml1__PlaneAngleUom ret = (witsml1__PlaneAngleUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getInclinometryUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getAzimuths(SWIGTYPE_p_double azims) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getAzimuths(swigCPtr, SWIGTYPE_p_double.getCPtr(azims));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__PlaneAngleUom getAzimuthUom() {
    witsml1__PlaneAngleUom ret = (witsml1__PlaneAngleUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getAzimuthUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__AziRef getAzimuthReference() {
    witsml1__AziRef ret = (witsml1__AziRef)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getAzimuthReference(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getEastings(SWIGTYPE_p_double eastings) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getEastings(swigCPtr, SWIGTYPE_p_double.getCPtr(eastings));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__LengthUom getEastingUom() {
    witsml1__LengthUom ret = (witsml1__LengthUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getEastingUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getNorthings(SWIGTYPE_p_double northings) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getNorthings(swigCPtr, SWIGTYPE_p_double.getCPtr(northings));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__LengthUom getNorthingUom() {
    witsml1__LengthUom ret = (witsml1__LengthUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getNorthingUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getTvds(SWIGTYPE_p_double tvds) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getTvds(swigCPtr, SWIGTYPE_p_double.getCPtr(tvds));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__WellVerticalCoordinateUom getTvdUom() {
    witsml1__WellVerticalCoordinateUom ret = (witsml1__WellVerticalCoordinateUom)f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getTvdUom(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setTrajectoryStations(uint trajectoryStationCount, uint mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_setTrajectoryStations(swigCPtr, trajectoryStationCount, mdDatumIndex, (int)mDUom, SWIGTYPE_p_double.getCPtr(mDSet), (int)angleUom, SWIGTYPE_p_double.getCPtr(inclSet), (int)aziRef, SWIGTYPE_p_double.getCPtr(aziSet));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setEastingNorthingTrajectoryStations(uint trajectoryStationCount, uint mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, uint tvdDatumIndex, witsml1__WellVerticalCoordinateUom tVDUom, SWIGTYPE_p_double tVDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet, witsml1__LengthUom locationUom, SWIGTYPE_p_double locationEastingSet, SWIGTYPE_p_double locationNorthingSet, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_setEastingNorthingTrajectoryStations(swigCPtr, trajectoryStationCount, mdDatumIndex, (int)mDUom, SWIGTYPE_p_double.getCPtr(mDSet), tvdDatumIndex, (int)tVDUom, SWIGTYPE_p_double.getCPtr(tVDSet), (int)angleUom, SWIGTYPE_p_double.getCPtr(inclSet), (int)aziRef, SWIGTYPE_p_double.getCPtr(aziSet), (int)locationUom, SWIGTYPE_p_double.getCPtr(locationEastingSet), SWIGTYPE_p_double.getCPtr(locationNorthingSet), f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setWestingSouthingTrajectoryStations(uint trajectoryStationCount, uint mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, uint tvdDatumIndex, witsml1__WellVerticalCoordinateUom tVDUom, SWIGTYPE_p_double tVDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet, witsml1__LengthUom locationUom, SWIGTYPE_p_double locationWestingSet, SWIGTYPE_p_double locationSouthingSet, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_setWestingSouthingTrajectoryStations(swigCPtr, trajectoryStationCount, mdDatumIndex, (int)mDUom, SWIGTYPE_p_double.getCPtr(mDSet), tvdDatumIndex, (int)tVDUom, SWIGTYPE_p_double.getCPtr(tVDSet), (int)angleUom, SWIGTYPE_p_double.getCPtr(inclSet), (int)aziRef, SWIGTYPE_p_double.getCPtr(aziSet), (int)locationUom, SWIGTYPE_p_double.getCPtr(locationWestingSet), SWIGTYPE_p_double.getCPtr(locationSouthingSet), f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setProjectedXProjectedYTrajectoryStations(uint trajectoryStationCount, uint mdDatumIndex, witsml1__MeasuredDepthUom mDUom, SWIGTYPE_p_double mDSet, uint tvdDatumIndex, witsml1__WellVerticalCoordinateUom tVDUom, SWIGTYPE_p_double tVDSet, witsml1__PlaneAngleUom angleUom, SWIGTYPE_p_double inclSet, witsml1__AziRef aziRef, SWIGTYPE_p_double aziSet, witsml1__LengthUom locationUom, SWIGTYPE_p_double locationProjectedXSet, SWIGTYPE_p_double locationProjectedYSet, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_setProjectedXProjectedYTrajectoryStations(swigCPtr, trajectoryStationCount, mdDatumIndex, (int)mDUom, SWIGTYPE_p_double.getCPtr(mDSet), tvdDatumIndex, (int)tVDUom, SWIGTYPE_p_double.getCPtr(tVDSet), (int)angleUom, SWIGTYPE_p_double.getCPtr(inclSet), (int)aziRef, SWIGTYPE_p_double.getCPtr(aziSet), (int)locationUom, SWIGTYPE_p_double.getCPtr(locationProjectedXSet), SWIGTYPE_p_double.getCPtr(locationProjectedYSet), f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore getWellbore() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getWellbore(swigCPtr);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation getResqmlWellboreTrajectoryRepresentation() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_Trajectory_getResqmlWellboreTrajectoryRepresentation(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
