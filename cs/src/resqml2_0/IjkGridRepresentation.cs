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

public class IjkGridRepresentation : f2i.energisticsStandardsApi.resqml2_0.AbstractColumnLayerGridRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal IjkGridRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(IjkGridRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IjkGridRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.energisticsApiPINVOKE.delete_resqml2_0_IjkGridRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public bool isRightHanded() {
    bool ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_isRightHanded(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getICount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getICount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setICount(uint iCount) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setICount(swigCPtr, iCount);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint getJCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getJCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setJCount(uint jCount) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setJCount(swigCPtr, jCount);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint getSplitCoordinateLineCount() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getSplitCoordinateLineCount(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getPillarsOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int pillarIndices, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getPillarsOfSplitCoordinateLines__SWIG_0(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(pillarIndices), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getPillarsOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int pillarIndices, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getPillarsOfSplitCoordinateLines__SWIG_1(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(pillarIndices), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getPillarsOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int pillarIndices) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getPillarsOfSplitCoordinateLines__SWIG_2(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(pillarIndices));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getColumnsOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int columnIndices, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getColumnsOfSplitCoordinateLines__SWIG_0(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(columnIndices), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getColumnsOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int columnIndices, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getColumnsOfSplitCoordinateLines__SWIG_1(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(columnIndices), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getColumnsOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int columnIndices) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getColumnsOfSplitCoordinateLines__SWIG_2(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(columnIndices));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getColumnCountOfSplitCoordinateLines(SWIGTYPE_p_unsigned_int columnIndexCountPerSplitCoordinateLine) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getColumnCountOfSplitCoordinateLines(swigCPtr, SWIGTYPE_p_unsigned_int.getCPtr(columnIndexCountPerSplitCoordinateLine));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint getControlPointMaxCountPerPillar() {
    uint ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPointMaxCountPerPillar(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getControlPoints(SWIGTYPE_p_double controlPoints, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPoints__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPoints), reverseIAxis, reverseJAxis, reverseKAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getControlPoints(SWIGTYPE_p_double controlPoints, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPoints__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPoints), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getControlPoints(SWIGTYPE_p_double controlPoints, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPoints__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPoints), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getControlPoints(SWIGTYPE_p_double controlPoints) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPoints__SWIG_3(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPoints));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool hasControlPointParameters() {
    bool ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_hasControlPointParameters(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getControlPointParameters(SWIGTYPE_p_double controlPointParameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPointParameters__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPointParameters), reverseIAxis, reverseJAxis, reverseKAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getControlPointParameters(SWIGTYPE_p_double controlPointParameters, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPointParameters__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPointParameters), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getControlPointParameters(SWIGTYPE_p_double controlPointParameters, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPointParameters__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPointParameters), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getControlPointParameters(SWIGTYPE_p_double controlPointParameters) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getControlPointParameters__SWIG_3(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPointParameters));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametricLineKind(SWIGTYPE_p_short pillarKind, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametricLineKind__SWIG_0(swigCPtr, SWIGTYPE_p_short.getCPtr(pillarKind), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametricLineKind(SWIGTYPE_p_short pillarKind, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametricLineKind__SWIG_1(swigCPtr, SWIGTYPE_p_short.getCPtr(pillarKind), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametricLineKind(SWIGTYPE_p_short pillarKind) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametricLineKind__SWIG_2(swigCPtr, SWIGTYPE_p_short.getCPtr(pillarKind));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametersOfNodes(SWIGTYPE_p_double parameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametersOfNodes__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(parameters), reverseIAxis, reverseJAxis, reverseKAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametersOfNodes(SWIGTYPE_p_double parameters, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametersOfNodes__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(parameters), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametersOfNodes(SWIGTYPE_p_double parameters, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametersOfNodes__SWIG_2(swigCPtr, SWIGTYPE_p_double.getCPtr(parameters), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getParametersOfNodes(SWIGTYPE_p_double parameters) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getParametersOfNodes__SWIG_3(swigCPtr, SWIGTYPE_p_double.getCPtr(parameters));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getCellGeometryIsDefined(SWIGTYPE_p_bool cellGeometryIsDefined, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCellGeometryIsDefined__SWIG_0(swigCPtr, SWIGTYPE_p_bool.getCPtr(cellGeometryIsDefined), reverseIAxis, reverseJAxis, reverseKAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getCellGeometryIsDefined(SWIGTYPE_p_bool cellGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCellGeometryIsDefined__SWIG_1(swigCPtr, SWIGTYPE_p_bool.getCPtr(cellGeometryIsDefined), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getCellGeometryIsDefined(SWIGTYPE_p_bool cellGeometryIsDefined, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCellGeometryIsDefined__SWIG_2(swigCPtr, SWIGTYPE_p_bool.getCPtr(cellGeometryIsDefined), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getCellGeometryIsDefined(SWIGTYPE_p_bool cellGeometryIsDefined) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCellGeometryIsDefined__SWIG_3(swigCPtr, SWIGTYPE_p_bool.getCPtr(cellGeometryIsDefined));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getPillarGeometryIsDefined(SWIGTYPE_p_bool pillarGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getPillarGeometryIsDefined__SWIG_0(swigCPtr, SWIGTYPE_p_bool.getCPtr(pillarGeometryIsDefined), reverseIAxis, reverseJAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getPillarGeometryIsDefined(SWIGTYPE_p_bool pillarGeometryIsDefined, bool reverseIAxis) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getPillarGeometryIsDefined__SWIG_1(swigCPtr, SWIGTYPE_p_bool.getCPtr(pillarGeometryIsDefined), reverseIAxis);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getPillarGeometryIsDefined(SWIGTYPE_p_bool pillarGeometryIsDefined) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getPillarGeometryIsDefined__SWIG_2(swigCPtr, SWIGTYPE_p_bool.getCPtr(pillarGeometryIsDefined));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsCoordinateLineNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double points, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, uint splitCoordinateLineCount, SWIGTYPE_p_unsigned_int pillarOfCoordinateLine, SWIGTYPE_p_unsigned_int splitCoordinateLineColumnCumulativeCount, SWIGTYPE_p_unsigned_int splitCoordinateLineColumns) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsCoordinateLineNodes__SWIG_0(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(points), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), splitCoordinateLineCount, SWIGTYPE_p_unsigned_int.getCPtr(pillarOfCoordinateLine), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumnCumulativeCount), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumns));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsCoordinateLineNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double points, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, uint splitCoordinateLineCount, SWIGTYPE_p_unsigned_int pillarOfCoordinateLine, SWIGTYPE_p_unsigned_int splitCoordinateLineColumnCumulativeCount) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsCoordinateLineNodes__SWIG_1(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(points), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), splitCoordinateLineCount, SWIGTYPE_p_unsigned_int.getCPtr(pillarOfCoordinateLine), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumnCumulativeCount));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsCoordinateLineNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double points, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, uint splitCoordinateLineCount, SWIGTYPE_p_unsigned_int pillarOfCoordinateLine) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsCoordinateLineNodes__SWIG_2(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(points), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), splitCoordinateLineCount, SWIGTYPE_p_unsigned_int.getCPtr(pillarOfCoordinateLine));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsCoordinateLineNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double points, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, uint splitCoordinateLineCount) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsCoordinateLineNodes__SWIG_3(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(points), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), splitCoordinateLineCount);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsCoordinateLineNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double points, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsCoordinateLineNodes__SWIG_4(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(points), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsParametricNonSplittedPillarNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double parameters, SWIGTYPE_p_double controlPoints, SWIGTYPE_p_double controlPointParameters, uint controlPointMaxCountPerPillar, SWIGTYPE_p_short pillarKind, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, SWIGTYPE_p_unsigned_char cellGeomIsDefined) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsParametricNonSplittedPillarNodes__SWIG_0(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(parameters), SWIGTYPE_p_double.getCPtr(controlPoints), SWIGTYPE_p_double.getCPtr(controlPointParameters), controlPointMaxCountPerPillar, SWIGTYPE_p_short.getCPtr(pillarKind), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), SWIGTYPE_p_unsigned_char.getCPtr(cellGeomIsDefined));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsParametricNonSplittedPillarNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double parameters, SWIGTYPE_p_double controlPoints, SWIGTYPE_p_double controlPointParameters, uint controlPointMaxCountPerPillar, SWIGTYPE_p_short pillarKind, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsParametricNonSplittedPillarNodes__SWIG_1(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(parameters), SWIGTYPE_p_double.getCPtr(controlPoints), SWIGTYPE_p_double.getCPtr(controlPointParameters), controlPointMaxCountPerPillar, SWIGTYPE_p_short.getCPtr(pillarKind), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsParametricSplittedPillarNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double parameters, SWIGTYPE_p_double controlPoints, SWIGTYPE_p_double controlPointParameters, uint controlPointMaxCountPerPillar, SWIGTYPE_p_short pillarKind, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, uint splitCoordinateLineCount, SWIGTYPE_p_unsigned_int pillarOfCoordinateLine, SWIGTYPE_p_unsigned_int splitCoordinateLineColumnCumulativeCount, SWIGTYPE_p_unsigned_int splitCoordinateLineColumns, SWIGTYPE_p_unsigned_char cellGeomIsDefined) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsParametricSplittedPillarNodes__SWIG_0(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(parameters), SWIGTYPE_p_double.getCPtr(controlPoints), SWIGTYPE_p_double.getCPtr(controlPointParameters), controlPointMaxCountPerPillar, SWIGTYPE_p_short.getCPtr(pillarKind), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), splitCoordinateLineCount, SWIGTYPE_p_unsigned_int.getCPtr(pillarOfCoordinateLine), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumnCumulativeCount), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumns), SWIGTYPE_p_unsigned_char.getCPtr(cellGeomIsDefined));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsParametricSplittedPillarNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, SWIGTYPE_p_double parameters, SWIGTYPE_p_double controlPoints, SWIGTYPE_p_double controlPointParameters, uint controlPointMaxCountPerPillar, SWIGTYPE_p_short pillarKind, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy, uint splitCoordinateLineCount, SWIGTYPE_p_unsigned_int pillarOfCoordinateLine, SWIGTYPE_p_unsigned_int splitCoordinateLineColumnCumulativeCount, SWIGTYPE_p_unsigned_int splitCoordinateLineColumns) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsParametricSplittedPillarNodes__SWIG_1(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, SWIGTYPE_p_double.getCPtr(parameters), SWIGTYPE_p_double.getCPtr(controlPoints), SWIGTYPE_p_double.getCPtr(controlPointParameters), controlPointMaxCountPerPillar, SWIGTYPE_p_short.getCPtr(pillarKind), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy), splitCoordinateLineCount, SWIGTYPE_p_unsigned_int.getCPtr(pillarOfCoordinateLine), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumnCumulativeCount), SWIGTYPE_p_unsigned_int.getCPtr(splitCoordinateLineColumns));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometryAsCoordinateLineNodes(resqml2__PillarShape mostComplexPillarGeometry, resqml2__KDirection kDirectionKind, bool isRightHanded, double originX, double originY, double originZ, double directionIX, double directionIY, double directionIZ, double spacingI, double directionJX, double directionJY, double directionJZ, double spacingJ, double directionKX, double directionKY, double directionKZ, double spacingK) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_setGeometryAsCoordinateLineNodes__SWIG_5(swigCPtr, (int)mostComplexPillarGeometry, (int)kDirectionKind, isRightHanded, originX, originY, originZ, directionIX, directionIY, directionIZ, spacingI, directionJX, directionJY, directionJZ, spacingJ, directionKX, directionKY, directionKZ, spacingK);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void addSeismic3dCoordinatesToPatch(uint patchIndex, double startInline, double incrInline, uint countInline, double startCrossline, double incrCrossline, uint countCrossline, uint countSample, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation seismicSupport) {
    f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_addSeismic3dCoordinatesToPatch(swigCPtr, patchIndex, startInline, incrInline, countInline, startCrossline, incrCrossline, countCrossline, countSample, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation.getCPtr(seismicSupport));
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public double getXOrigin() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getXOrigin(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getYOrigin() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getYOrigin(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getZOrigin() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getZOrigin(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getXOriginInGlobalCrs() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getXOriginInGlobalCrs(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getYOriginInGlobalCrs() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getYOriginInGlobalCrs(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getZOriginInGlobalCrs() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getZOriginInGlobalCrs(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getXIOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getXIOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getYIOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getYIOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getZIOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getZIOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getXJOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getXJOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getYJOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getYJOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getZJOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getZJOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getXKOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getXKOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getYKOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getYKOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getZKOffset() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getZKOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getISpacing() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getISpacing(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getJSpacing() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getJSpacing(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getKSpacing() {
    double ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getKSpacing(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getOriginInline() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getOriginInline(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getOriginCrossline() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getOriginCrossline(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getInlineIOffset() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getInlineIOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getInlineJOffset() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getInlineJOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getInlineKOffset() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getInlineKOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getCrosslineIOffset() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCrosslineIOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getCrosslineJOffset() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCrosslineJOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getCrosslineKOffset() {
    int ret = f2i.energisticsStandardsApi.energisticsApiPINVOKE.resqml2_0_IjkGridRepresentation_getCrosslineKOffset(swigCPtr);
    if (f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}