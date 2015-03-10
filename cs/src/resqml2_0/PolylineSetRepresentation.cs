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

public class PolylineSetRepresentation : f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal PolylineSetRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(PolylineSetRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~PolylineSetRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_PolylineSetRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public uint getPolylineCountOfPatch(uint patchIndex) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_getPolylineCountOfPatch(swigCPtr, patchIndex);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getPolylineCountOfAllPatches() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_getPolylineCountOfAllPatches(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getNodeCountPerPolylineInPatch(uint patchIndex, SWIGTYPE_p_unsigned_int nodeCountPerPolyline) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_getNodeCountPerPolylineInPatch(swigCPtr, patchIndex, SWIGTYPE_p_unsigned_int.getCPtr(nodeCountPerPolyline));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getNodeCountPerPolylineOfAllPatches(SWIGTYPE_p_unsigned_int nodeCountPerPolyline) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_getNodeCountPerPolylineOfAllPatches(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(nodeCountPerPolyline));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackGeometryPatch(SWIGTYPE_p_unsigned_int NodeCountPerPolyline, SWIGTYPE_p_double nodes, uint polylineCount, bool allPolylinesClosedFlag, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_pushBackGeometryPatch__SWIG_0(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(NodeCountPerPolyline), SWIGTYPE_p_double.getCPtr(nodes), polylineCount, allPolylinesClosedFlag, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackGeometryPatch(SWIGTYPE_p_unsigned_int NodeCountPerPolyline, SWIGTYPE_p_double nodes, uint polylineCount, SWIGTYPE_p_bool polylineClosedFlags, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_pushBackGeometryPatch__SWIG_1(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(NodeCountPerPolyline), SWIGTYPE_p_double.getCPtr(nodes), polylineCount, SWIGTYPE_p_bool.getCPtr(polylineClosedFlags), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool areAllPolylinesClosedOfPatch(uint patchIndex) {
    bool ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_areAllPolylinesClosedOfPatch(swigCPtr, patchIndex);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool areAllPolylinesClosedOfAllPatches() {
    bool ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_areAllPolylinesClosedOfAllPatches(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool areAllPolylinesNonClosedOfPatch(uint patchIndex) {
    bool ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_areAllPolylinesNonClosedOfPatch(swigCPtr, patchIndex);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool areAllPolylinesNonClosedOfAllPatches() {
    bool ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_areAllPolylinesNonClosedOfAllPatches(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getClosedFlagPerPolylineOfPatch(uint patchIndex, SWIGTYPE_p_bool closedFlagPerPolyline) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_getClosedFlagPerPolylineOfPatch(swigCPtr, patchIndex, SWIGTYPE_p_bool.getCPtr(closedFlagPerPolyline));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getClosedFlagPerPolylineOfAllPatches(SWIGTYPE_p_bool closedFlagPerPolyline) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_PolylineSetRepresentation_getClosedFlagPerPolylineOfAllPatches(swigCPtr, SWIGTYPE_p_bool.getCPtr(closedFlagPerPolyline));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
