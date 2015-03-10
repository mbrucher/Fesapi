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

public class CategoricalProperty : f2i.energisticsStandardsApi.resqml2_0.AbstractValuesProperty {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal CategoricalProperty(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(CategoricalProperty obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CategoricalProperty() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_CategoricalProperty(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public string getStringLookupUuid() {
    string ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_getStringLookupUuid(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.StringTableLookup getStringLookup() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_getStringLookup(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.StringTableLookup ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.StringTableLookup(cPtr, false);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void pushBackLongHdf5Array1dOfValues(SWIGTYPE_p_long values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, int nullValue) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_pushBackLongHdf5Array1dOfValues(swigCPtr, SWIGTYPE_p_long.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), nullValue);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackLongHdf5Array2dOfValues(SWIGTYPE_p_long values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, int nullValue) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_pushBackLongHdf5Array2dOfValues(swigCPtr, SWIGTYPE_p_long.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), nullValue);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackLongHdf5Array3dOfValues(SWIGTYPE_p_long values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, int nullValue) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_pushBackLongHdf5Array3dOfValues(swigCPtr, SWIGTYPE_p_long.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), nullValue);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackLongHdf5ArrayOfValues(SWIGTYPE_p_long values, SWIGTYPE_p_unsigned_long_long numValues, uint numDimensionsInArray, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, int nullValue) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_CategoricalProperty_pushBackLongHdf5ArrayOfValues(swigCPtr, SWIGTYPE_p_long.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numDimensionsInArray, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), nullValue);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
