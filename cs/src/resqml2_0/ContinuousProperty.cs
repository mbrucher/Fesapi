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

public class ContinuousProperty : f2i.energisticsStandardsApi.resqml2_0.AbstractValuesProperty {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal ContinuousProperty(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(ContinuousProperty obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~ContinuousProperty() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_resqml2_0_ContinuousProperty(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public resqml2__ResqmlUom getUom() {
    resqml2__ResqmlUom ret = (resqml2__ResqmlUom)f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_getUom(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getUomAsString() {
    string ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_getUomAsString(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void pushBackDoubleHdf5Array1dOfValues(SWIGTYPE_p_double values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue, double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array1dOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue, maximumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array1dOfValues(SWIGTYPE_p_double values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array1dOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array1dOfValues(SWIGTYPE_p_double values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array1dOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array2dOfValues(SWIGTYPE_p_double values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue, double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array2dOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue, maximumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array2dOfValues(SWIGTYPE_p_double values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array2dOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array2dOfValues(SWIGTYPE_p_double values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array2dOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array3dOfValues(SWIGTYPE_p_double values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue, double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array3dOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue, maximumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array3dOfValues(SWIGTYPE_p_double values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array3dOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5Array3dOfValues(SWIGTYPE_p_double values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5Array3dOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5ArrayOfValues(SWIGTYPE_p_double values, SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, SWIGTYPE_p_double minimumValue, SWIGTYPE_p_double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5ArrayOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), SWIGTYPE_p_double.getCPtr(minimumValue), SWIGTYPE_p_double.getCPtr(maximumValue));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5ArrayOfValues(SWIGTYPE_p_double values, SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, SWIGTYPE_p_double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5ArrayOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), SWIGTYPE_p_double.getCPtr(minimumValue));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDoubleHdf5ArrayOfValues(SWIGTYPE_p_double values, SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackDoubleHdf5ArrayOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array1dOfValues(SWIGTYPE_p_float values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue, double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array1dOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue, maximumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array1dOfValues(SWIGTYPE_p_float values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array1dOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array1dOfValues(SWIGTYPE_p_float values, uint valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array1dOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array2dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue, double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array2dOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue, maximumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array2dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array2dOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array2dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array2dOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array3dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue, double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array3dOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue, maximumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array3dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array3dOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), minimumValue);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5Array3dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5Array3dOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5ArrayOfValues(SWIGTYPE_p_float values, SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, SWIGTYPE_p_double minimumValue, SWIGTYPE_p_double maximumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5ArrayOfValues__SWIG_0(swigCPtr, SWIGTYPE_p_float.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), SWIGTYPE_p_double.getCPtr(minimumValue), SWIGTYPE_p_double.getCPtr(maximumValue));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5ArrayOfValues(SWIGTYPE_p_float values, SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, SWIGTYPE_p_double minimumValue) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5ArrayOfValues__SWIG_1(swigCPtr, SWIGTYPE_p_float.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), SWIGTYPE_p_double.getCPtr(minimumValue));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5ArrayOfValues(SWIGTYPE_p_float values, SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5ArrayOfValues__SWIG_2(swigCPtr, SWIGTYPE_p_float.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getDoubleValuesOfPatch(uint patchIndex, SWIGTYPE_p_double values) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_getDoubleValuesOfPatch(swigCPtr, patchIndex, SWIGTYPE_p_double.getCPtr(values));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getFloatValuesOfPatch(uint patchIndex, SWIGTYPE_p_float values) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_getFloatValuesOfPatch__SWIG_0(swigCPtr, patchIndex, SWIGTYPE_p_float.getCPtr(values));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void createFloatHdf5ArrayOfValues(SWIGTYPE_p_unsigned_long_long numValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_createFloatHdf5ArrayOfValues(swigCPtr, SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void createFloatHdf5Array3dOfValues(uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_createFloatHdf5Array3dOfValues(swigCPtr, valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5SlabArray3dOfValues(SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, uint offsetInFastestDim, uint offsetInMiddleDim, uint offsetInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5SlabArray3dOfValues(swigCPtr, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackFloatHdf5SlabArrayOfValues(SWIGTYPE_p_float values, SWIGTYPE_p_unsigned_long_long numValues, SWIGTYPE_p_unsigned_long_long offsetValues, uint numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_pushBackFloatHdf5SlabArrayOfValues(swigCPtr, SWIGTYPE_p_float.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValues), SWIGTYPE_p_unsigned_long_long.getCPtr(offsetValues), numArrayDimensions, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getFloatValuesOfPatch(uint patchIndex, SWIGTYPE_p_float values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, uint numArrayDimensions) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_getFloatValuesOfPatch__SWIG_1(swigCPtr, patchIndex, SWIGTYPE_p_float.getCPtr(values), SWIGTYPE_p_unsigned_long_long.getCPtr(numValuesInEachDimension), SWIGTYPE_p_unsigned_long_long.getCPtr(offsetInEachDimension), numArrayDimensions);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getFloatValuesOf3dPatch(uint patchIndex, SWIGTYPE_p_float values, uint valueCountInFastestDim, uint valueCountInMiddleDim, uint valueCountInSlowestDim, uint offsetInFastestDim, uint offsetInMiddleDim, uint offsetInSlowestDim) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_ContinuousProperty_getFloatValuesOf3dPatch(swigCPtr, patchIndex, SWIGTYPE_p_float.getCPtr(values), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
