//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.5
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace f2i.energisticsStandardsApi.resqml2_0 {

public class WellboreMarkerFrameRepresentation : f2i.energisticsStandardsApi.resqml2_0.WellboreFrameRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal WellboreMarkerFrameRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_WellboreMarkerFrameRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(WellboreMarkerFrameRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~WellboreMarkerFrameRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_WellboreMarkerFrameRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public f2i.energisticsStandardsApi.resqml2_0.WellboreMarker pushBackNewWellboreMarker(string guid, string title) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_WellboreMarkerFrameRepresentation_pushBackNewWellboreMarker__SWIG_0(swigCPtr, guid, title);
    f2i.energisticsStandardsApi.resqml2_0.WellboreMarker ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.WellboreMarker(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.WellboreMarker pushBackNewWellboreMarker(string guid, string title, resqml2__GeologicBoundaryKind geologicBoundaryKind) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_WellboreMarkerFrameRepresentation_pushBackNewWellboreMarker__SWIG_1(swigCPtr, guid, title, (int)geologicBoundaryKind);
    f2i.energisticsStandardsApi.resqml2_0.WellboreMarker ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.WellboreMarker(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getWellboreMarkerCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_WellboreMarkerFrameRepresentation_getWellboreMarkerCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public WellboreMarkerVector getWellboreMarkerSet() {
    WellboreMarkerVector ret = new WellboreMarkerVector(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_WellboreMarkerFrameRepresentation_getWellboreMarkerSet(swigCPtr), false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setWitsmlFormationMarker(uint resqmlMarkerIndex, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker witsmlFormationMarker) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_WellboreMarkerFrameRepresentation_setWitsmlFormationMarker(swigCPtr, resqmlMarkerIndex, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(witsmlFormationMarker));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
