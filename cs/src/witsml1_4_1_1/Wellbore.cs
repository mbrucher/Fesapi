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

public class Wellbore : f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal Wellbore(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Wellbore obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Wellbore() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_witsml1_4_1_1_Wellbore(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory createTrajectory(string guid, string title) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_createTrajectory__SWIG_0(swigCPtr, guid, title);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory createTrajectory(string guid, string title, string sourceName, long dTimCreation, long dTimLastChange, string comments) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_createTrajectory__SWIG_1(swigCPtr, guid, title, sourceName, dTimCreation, dTimLastChange, comments);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Log createLog(string guid, string title, witsml1__LogIndexType indexType, string indexCurve) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_createLog__SWIG_0(swigCPtr, guid, title, (int)indexType, indexCurve);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Log ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Log(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Log createLog(string guid, string title, witsml1__LogIndexType indexType, string indexCurve, string sourceName, long dTimCreation, long dTimLastChange, string comments) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_createLog__SWIG_1(swigCPtr, guid, title, (int)indexType, indexCurve, sourceName, dTimCreation, dTimLastChange, comments);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Log ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Log(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker createFormationMarker(string guid, string title, uint mdDatumIndex, witsml1__MeasuredDepthUom mdUom, double mdTopSample) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_createFormationMarker__SWIG_0(swigCPtr, guid, title, mdDatumIndex, (int)mdUom, mdTopSample);
    f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker createFormationMarker(string guid, string title, uint mdDatumIndex, witsml1__MeasuredDepthUom mdUom, double mdTopSample, uint tvdDatumIndex, witsml1__WellVerticalCoordinateUom tvdUom, double tvdTopSample, witsml1__PlaneAngleUom dipUom, double dip, witsml1__PlaneAngleUom dipDirectionUom, double dipDirection, string sourceName, long dTimCreation, long dTimLastChange, string comments) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_createFormationMarker__SWIG_1(swigCPtr, guid, title, mdDatumIndex, (int)mdUom, mdTopSample, tvdDatumIndex, (int)tvdUom, tvdTopSample, (int)dipUom, dip, (int)dipDirectionUom, dipDirection, sourceName, dTimCreation, dTimLastChange, comments);
    f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Well getWell() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_getWell(swigCPtr);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Well ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Well(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.WellboreFeature getResqmlWellboreFeature() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_getResqmlWellboreFeature(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.WellboreFeature ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.WellboreFeature(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public TrajectoryVector getTrajectories() {
    TrajectoryVector ret = new TrajectoryVector(f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_getTrajectories(swigCPtr), false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public LogVector getLogs() {
    LogVector ret = new LogVector(f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_getLogs(swigCPtr), false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public FormationMarkerVector getFormationMarkers() {
    FormationMarkerVector ret = new FormationMarkerVector(f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_getFormationMarkers(swigCPtr), false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setShape(witsml1__WellboreShape shape) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Wellbore_setShape(swigCPtr, (int)shape);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
