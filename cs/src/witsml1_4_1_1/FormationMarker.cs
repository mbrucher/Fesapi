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

public class FormationMarker : f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal FormationMarker(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_FormationMarker_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(FormationMarker obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~FormationMarker() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_witsml1_4_1_1_FormationMarker(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore getWellbore() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_FormationMarker_getWellbore(swigCPtr);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.WellboreMarkerFrameRepresentation getResqmlWellboreMarkerFrameRepresentation() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.witsml1_4_1_1_FormationMarker_getResqmlWellboreMarkerFrameRepresentation(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.WellboreMarkerFrameRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.WellboreMarkerFrameRepresentation(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}