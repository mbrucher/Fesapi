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

public class NonSealedSurfaceFrameworkRepresentation : f2i.energisticsStandardsApi.resqml2_0.RepresentationSetRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal NonSealedSurfaceFrameworkRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_NonSealedSurfaceFrameworkRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(NonSealedSurfaceFrameworkRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~NonSealedSurfaceFrameworkRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_resqml2_0_NonSealedSurfaceFrameworkRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public void pushBackNonSealedContactRepresentation(uint pointCount, SWIGTYPE_p_double points, f2i.energisticsStandardsApi.resqml2_0.AbstractLocal3dCrs localCrs, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_NonSealedSurfaceFrameworkRepresentation_pushBackNonSealedContactRepresentation(swigCPtr, pointCount, SWIGTYPE_p_double.getCPtr(points), f2i.energisticsStandardsApi.resqml2_0.AbstractLocal3dCrs.getCPtr(localCrs), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
