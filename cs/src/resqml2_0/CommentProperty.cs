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

public class CommentProperty : f2i.energisticsStandardsApi.resqml2_0.AbstractValuesProperty {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal CommentProperty(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CommentProperty_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(CommentProperty obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CommentProperty() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_CommentProperty(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public void pushBackStringHdf5ArrayOfValues(StringVector values, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CommentProperty_pushBackStringHdf5ArrayOfValues(swigCPtr, StringVector.getCPtr(values), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public StringVector getStringValuesOfPatch(uint patchIndex) {
    StringVector ret = new StringVector(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CommentProperty_getStringValuesOfPatch(swigCPtr, patchIndex), true);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}