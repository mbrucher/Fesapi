//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.5
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace f2i.energisticsStandardsApi.witsml1_4_1_1 {

public class Well : f2i.energisticsStandardsApi.witsml1_4_1_1.AbstractObject {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal Well(global::System.IntPtr cPtr, bool cMemoryOwn) : base(f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Well obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Well() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          f2i.energisticsStandardsApi.fesapiPINVOKE.delete_witsml1_4_1_1_Well(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public WellboreVector getWellbores() {
    WellboreVector ret = new WellboreVector(f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_getWellbores(swigCPtr), false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore createWellbore(string guid, string title) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_createWellbore__SWIG_0(swigCPtr, guid, title);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore createWellbore(string guid, string title, witsml1__WellStatus statusWellbore, bool isActive, witsml1__WellPurpose purposeWellbore, witsml1__WellboreType typeWellbore, bool achievedTD, string sourceName, long dTimCreation, long dTimLastChange, string comments) {
    global::System.IntPtr cPtr = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_createWellbore__SWIG_1(swigCPtr, guid, title, (int)statusWellbore, isActive, (int)purposeWellbore, (int)typeWellbore, achievedTD, sourceName, dTimCreation, dTimLastChange, comments);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Wellbore(cPtr, false);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setOperator(string operator_) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_setOperator(swigCPtr, operator_);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public double getWellHeadEastingLocationValue() {
    double ret = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_getWellHeadEastingLocationValue(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__LengthUom getWellHeadEastingLocationUom() {
    witsml1__LengthUom ret = (witsml1__LengthUom)f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_getWellHeadEastingLocationUom(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public double getWellHeadNorthingLocationValue() {
    double ret = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_getWellHeadNorthingLocationValue(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public witsml1__LengthUom getWellHeadNorthingLocationUom() {
    witsml1__LengthUom ret = (witsml1__LengthUom)f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_getWellHeadNorthingLocationUom(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setEastingNorthingLocation(witsml1__LengthUom uom, double easting, double northing, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_setEastingNorthingLocation(swigCPtr, (int)uom, easting, northing, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setWestingSouthingLocation(witsml1__LengthUom uom, double westing, double southing, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_setWestingSouthingLocation(swigCPtr, (int)uom, westing, southing, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setProjectedXProjectedYLocation(witsml1__LengthUom uom, double projectedX, double projectedY, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem wellCrs) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_setProjectedXProjectedYLocation(swigCPtr, (int)uom, projectedX, projectedY, f2i.energisticsStandardsApi.witsml1_4_1_1.CoordinateReferenceSystem.getCPtr(wellCrs));
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDatum(string guid, string title, witsml1__ElevCodeEnum code, uint datumIndex, witsml1__WellVerticalCoordinateUom elevationUnit, double elevation) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_pushBackDatum__SWIG_0(swigCPtr, guid, title, (int)code, datumIndex, (int)elevationUnit, elevation);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void pushBackDatum(string guid, string title, witsml1__ElevCodeEnum code, string refNamingSystem, string refCode, string refName) {
    f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_pushBackDatum__SWIG_1(swigCPtr, guid, title, (int)code, refNamingSystem, refCode, refName);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint getDatumCount() {
    uint ret = f2i.energisticsStandardsApi.fesapiPINVOKE.witsml1_4_1_1_Well_getDatumCount(swigCPtr);
    if (f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Pending) throw f2i.energisticsStandardsApi.fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
