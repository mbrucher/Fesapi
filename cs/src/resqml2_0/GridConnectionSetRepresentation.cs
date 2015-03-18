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

public class GridConnectionSetRepresentation : f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal GridConnectionSetRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(GridConnectionSetRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~GridConnectionSetRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_GridConnectionSetRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public uint getCellIndexPairCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getCellIndexPairCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getCellIndexPairCountFromFaultIndex(uint faultIndex) {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getCellIndexPairCountFromFaultIndex(swigCPtr, faultIndex);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getCellIndexPair(SWIGTYPE_p_unsigned_int cellIndexPair) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getCellIndexPair(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(cellIndexPair));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getCellIndexPairFromFaultIndex(SWIGTYPE_p_unsigned_int cellIndexPair, uint faultIndex) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getCellIndexPairFromFaultIndex(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(cellIndexPair), faultIndex);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setCellIndexPairs(uint cellIndexPairCount, SWIGTYPE_p_unsigned_int cellIndexPair, uint nullValue, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_setCellIndexPairs(swigCPtr, cellIndexPairCount, SWIGTYPE_p_unsigned_int.getCPtr(cellIndexPair), nullValue, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setLocalFacePerCellIndexPairs(uint cellIndexPairCount, SWIGTYPE_p_unsigned_int LocalFacePerCellIndexPair, uint nullValue, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_setLocalFacePerCellIndexPairs(swigCPtr, cellIndexPairCount, SWIGTYPE_p_unsigned_int.getCPtr(LocalFacePerCellIndexPair), nullValue, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setConnectionFaultNames(SWIGTYPE_p_unsigned_int faultIndices, uint faultIndiceCount, uint nullValue, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_setConnectionFaultNames(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(faultIndices), faultIndiceCount, nullValue, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public string getFaultInterpretationUuidFromFaultIndex(uint faultIndex) {
    string ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getFaultInterpretationUuidFromFaultIndex(swigCPtr, faultIndex);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.FaultInterpretation getFaultInterpretationFromFaultIndex(uint faultIndex) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getFaultInterpretationFromFaultIndex(swigCPtr, faultIndex);
    f2i.energisticsStandardsApi.resqml2_0.FaultInterpretation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.FaultInterpretation(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getFaultInterpretationCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getFaultInterpretationCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getSupportingGridRepresentationCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getSupportingGridRepresentationCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.AbstractGridRepresentation getSupportingGridRepresentation() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getSupportingGridRepresentation(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.AbstractGridRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.AbstractGridRepresentation(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getSupportingGridRepresentationUuid() {
    string ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_GridConnectionSetRepresentation_getSupportingGridRepresentationUuid(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}