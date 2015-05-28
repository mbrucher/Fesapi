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

public class AbstractRepresentation : f2i.energisticsStandardsApi.resqml2_0.AbstractResqmlDataObject {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal AbstractRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(AbstractRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~AbstractRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_resqml2_0_AbstractRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public f2i.energisticsStandardsApi.resqml2_0.AbstractFeatureInterpretation getInterpretation() {
		global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getInterpretation(swigCPtr);
		f2i.energisticsStandardsApi.resqml2_0.AbstractFeatureInterpretation ret = (f2i.energisticsStandardsApi.resqml2_0.AbstractFeatureInterpretation) fesapiPINVOKE.resqml2_0_instantiateConcreteObject(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
		return ret;
	}

  public string getInterpretationUuid() {
    string ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getInterpretationUuid(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.AbstractLocal3dCrs getLocalCrs() {
		global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getLocalCrs(swigCPtr);
		f2i.energisticsStandardsApi.resqml2_0.AbstractLocal3dCrs ret = (f2i.energisticsStandardsApi.resqml2_0.AbstractLocal3dCrs) fesapiPINVOKE.resqml2_0_instantiateConcreteLocal3dCrs(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
		return ret;
	}

  public string getLocalCrsUuid() {
    string ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getLocalCrsUuid(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.HdfProxy getHdfProxy() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getHdfProxy(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.HdfProxy ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.HdfProxy(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getHdfProxyUuid() {
    string ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getHdfProxyUuid(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getValuesPropertyCount() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getValuesPropertyCount(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.AbstractValuesProperty getValuesProperty(uint index) {
		global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getValuesProperty(swigCPtr, index);
		f2i.energisticsStandardsApi.resqml2_0.AbstractValuesProperty ret = (f2i.energisticsStandardsApi.resqml2_0.AbstractValuesProperty) fesapiPINVOKE.resqml2_0_instantiateConcreteObject(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
		return ret;
	}

  public uint getSubRepresentationCount() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getSubRepresentationCount(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.SubRepresentation getSubRepresentation(uint index) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getSubRepresentation(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.SubRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.SubRepresentation(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getFaultSubRepresentationCount() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getFaultSubRepresentationCount(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.SubRepresentation getFaultSubRepresentation(uint index) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getFaultSubRepresentation(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.SubRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.SubRepresentation(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual uint getXyzPointCountOfPatch(uint patchIndex) {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getXyzPointCountOfPatch(swigCPtr, patchIndex);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint getXyzPointCountOfAllPatches() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getXyzPointCountOfAllPatches(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void getXyzPointsOfPatch(uint patchIndex, SWIGTYPE_p_double xyzPoints) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getXyzPointsOfPatch(swigCPtr, patchIndex, SWIGTYPE_p_double.getCPtr(xyzPoints));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getXyzPointsOfPatchInGlobalCrs(uint patchIndex, SWIGTYPE_p_double xyzPoints) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getXyzPointsOfPatchInGlobalCrs(swigCPtr, patchIndex, SWIGTYPE_p_double.getCPtr(xyzPoints));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getXyzPointsOfAllPatches(SWIGTYPE_p_double xyzPoints) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getXyzPointsOfAllPatches(swigCPtr, SWIGTYPE_p_double.getCPtr(xyzPoints));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getXyzPointsOfAllPatchesInGlobalCrs(SWIGTYPE_p_double xyzPoints) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getXyzPointsOfAllPatchesInGlobalCrs(swigCPtr, SWIGTYPE_p_double.getCPtr(xyzPoints));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual uint getPatchCount() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getPatchCount(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation getSeismicSupportOfPatch(uint patchIndex) {
		global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getSeismicSupportOfPatch(swigCPtr, patchIndex);
		f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation ret = (f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation) fesapiPINVOKE.resqml2_0_instantiateConcreteObject(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
		return ret;
	}

  public void getSeismicLineAbscissaOfPointsOfPatch(uint patchIndex, SWIGTYPE_p_double values) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_getSeismicLineAbscissaOfPointsOfPatch(swigCPtr, patchIndex, SWIGTYPE_p_double.getCPtr(values));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void addSeismic2dCoordinatesToPatch(uint patchIndex, SWIGTYPE_p_double lineAbscissa, uint pointCount, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation seismicSupport, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_addSeismic2dCoordinatesToPatch(swigCPtr, patchIndex, SWIGTYPE_p_double.getCPtr(lineAbscissa), pointCount, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation.getCPtr(seismicSupport), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void addSeismic3dCoordinatesToPatch(uint patchIndex, SWIGTYPE_p_double inlines, SWIGTYPE_p_double crosslines, uint pointCount, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation seismicSupport, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_addSeismic3dCoordinatesToPatch__SWIG_0(swigCPtr, patchIndex, SWIGTYPE_p_double.getCPtr(inlines), SWIGTYPE_p_double.getCPtr(crosslines), pointCount, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation.getCPtr(seismicSupport), f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void addSeismic3dCoordinatesToPatch(uint patchIndex, double startInline, double incrInline, uint countInline, double startCrossline, double incrCrossline, uint countCrossline, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation seismicSupport) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_addSeismic3dCoordinatesToPatch__SWIG_1(swigCPtr, patchIndex, startInline, incrInline, countInline, startCrossline, incrCrossline, countCrossline, f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation.getCPtr(seismicSupport));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackIntoRepresentationSet(f2i.energisticsStandardsApi.resqml2_0.RepresentationSetRepresentation repSet) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_AbstractRepresentation_pushBackIntoRepresentationSet(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.RepresentationSetRepresentation.getCPtr(repSet));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
