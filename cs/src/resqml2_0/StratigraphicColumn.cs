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

public class StratigraphicColumn : f2i.energisticsStandardsApi.resqml2_0.AbstractResqmlDataObject {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal StratigraphicColumn(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_StratigraphicColumn_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(StratigraphicColumn obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~StratigraphicColumn() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_StratigraphicColumn(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public void pushBackStratiColumnRank(f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation stratiColumnRank) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_StratigraphicColumn_pushBackStratiColumnRank(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation.getCPtr(stratiColumnRank));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public StratigraphicColumnRankInterpretationVector getStratigraphicColumnRankInterpretationSet() {
    StratigraphicColumnRankInterpretationVector ret = new StratigraphicColumnRankInterpretationVector(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_StratigraphicColumn_getStratigraphicColumnRankInterpretationSet(swigCPtr), true);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
