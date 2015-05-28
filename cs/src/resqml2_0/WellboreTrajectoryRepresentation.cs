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

public class WellboreTrajectoryRepresentation : f2i.energisticsStandardsApi.resqml2_0.AbstractRepresentation {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal WellboreTrajectoryRepresentation(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(WellboreTrajectoryRepresentation obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~WellboreTrajectoryRepresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_resqml2_0_WellboreTrajectoryRepresentation(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public uint getWellboreFrameRepresentationCount() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getWellboreFrameRepresentationCount(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.WellboreFrameRepresentation getWellboreFrameRepresentation(uint index) {
		global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getWellboreFrameRepresentation(swigCPtr, index);
		f2i.energisticsStandardsApi.resqml2_0.WellboreFrameRepresentation ret = (f2i.energisticsStandardsApi.resqml2_0.WellboreFrameRepresentation) fesapiPINVOKE.resqml2_0_instantiateWellboreFrameRepresentationObject(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
		return ret;
	}

  public string getMdDatumUuid() {
    string ret = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getMdDatumUuid(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.resqml2_0.MdDatum getMdDatum() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getMdDatum(swigCPtr);
    f2i.energisticsStandardsApi.resqml2_0.MdDatum ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.MdDatum(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setGeometry(SWIGTYPE_p_double controlPoints, SWIGTYPE_p_double controlPointParameters, uint controlPointCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_setGeometry__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPoints), SWIGTYPE_p_double.getCPtr(controlPointParameters), controlPointCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setGeometry(SWIGTYPE_p_double controlPoints, SWIGTYPE_p_double tangentVectors, SWIGTYPE_p_double controlPointParameters, uint controlPointCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy proxy) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_setGeometry__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(controlPoints), SWIGTYPE_p_double.getCPtr(tangentVectors), SWIGTYPE_p_double.getCPtr(controlPointParameters), controlPointCount, f2i.energisticsStandardsApi.resqml2_0.HdfProxy.getCPtr(proxy));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void addParentTrajectory(double kickoffMd, double parentMd, f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation parentTrajRep) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_addParentTrajectory(swigCPtr, kickoffMd, parentMd, f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation.getCPtr(parentTrajRep));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getTangentVectors(SWIGTYPE_p_double tangentVectors) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getTangentVectors(swigCPtr, SWIGTYPE_p_double.getCPtr(tangentVectors));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void getMdValues(SWIGTYPE_p_double values) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getMdValues(swigCPtr, SWIGTYPE_p_double.getCPtr(values));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setWitsmlTrajectory(f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory witsmlTraj) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_setWitsmlTrajectory(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory.getCPtr(witsmlTraj));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory getWitsmlTrajectory() {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.resqml2_0_WellboreTrajectoryRepresentation_getWitsmlTrajectory(swigCPtr);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Trajectory(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
