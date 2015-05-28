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

public class SubRepresentation : f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal SubRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(SubRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~SubRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_resqml2_0_SubRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public void pushBackSubRepresentationPatch(resqml2__IndexableElements elementKind, uint elementCount, SWIGTYPE_p_unsigned_int elementIndices, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_pushBackSubRepresentationPatch__SWIG_0(swigCPtr, (int)elementKind, elementCount, SWIGTYPE_p_unsigned_int.getCPtr(elementIndices), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackSubRepresentationPatch(resqml2__IndexableElements elementKind0, resqml2__IndexableElements elementKind1, uint elementCount, SWIGTYPE_p_unsigned_int elementIndices0, SWIGTYPE_p_unsigned_int elementIndices1, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_pushBackSubRepresentationPatch__SWIG_1(swigCPtr, (int)elementKind0, (int)elementKind1, elementCount, SWIGTYPE_p_unsigned_int.getCPtr(elementIndices0), SWIGTYPE_p_unsigned_int.getCPtr(elementIndices1), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool isElementPairBased(uint patchIndex) {
    bool ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_isElementPairBased(swigCPtr, patchIndex);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public resqml2__IndexableElements getElementKindOfPatch(uint patchIndex, uint elementIndicesIndex) {
    resqml2__IndexableElements ret = (resqml2__IndexableElements)f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_getElementKindOfPatch(swigCPtr, patchIndex, elementIndicesIndex);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getElementCountOfPatch(uint patchIndex) {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_getElementCountOfPatch(swigCPtr, patchIndex);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getElementIndicesOfPatch(uint patchIndex, uint elementIndicesIndex, SWIGTYPE_p_unsigned_int elementIndices) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_SubRepresentation_getElementIndicesOfPatch(swigCPtr, patchIndex, elementIndicesIndex, SWIGTYPE_p_unsigned_int.getCPtr(elementIndices));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
