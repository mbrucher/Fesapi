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

public class HorizonInterpretation : f2i.energisticsStandardsApi.resqml2_0.BoundaryFeatureInterpretation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal HorizonInterpretation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_HorizonInterpretation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(HorizonInterpretation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~HorizonInterpretation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_resqml2_0_HorizonInterpretation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

}

}
