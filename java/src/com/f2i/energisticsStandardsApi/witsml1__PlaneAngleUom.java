/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class witsml1__PlaneAngleUom {
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__rad = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__rad", energisticsApiJNI.witsml1__PlaneAngleUom__rad_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__c = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__c", energisticsApiJNI.witsml1__PlaneAngleUom__c_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__ccgr = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__ccgr", energisticsApiJNI.witsml1__PlaneAngleUom__ccgr_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__cgr = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__cgr", energisticsApiJNI.witsml1__PlaneAngleUom__cgr_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__dega = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__dega", energisticsApiJNI.witsml1__PlaneAngleUom__dega_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__gon = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__gon", energisticsApiJNI.witsml1__PlaneAngleUom__gon_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__gr = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__gr", energisticsApiJNI.witsml1__PlaneAngleUom__gr_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__Grad = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__Grad", energisticsApiJNI.witsml1__PlaneAngleUom__Grad_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__krad = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__krad", energisticsApiJNI.witsml1__PlaneAngleUom__krad_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__mila = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__mila", energisticsApiJNI.witsml1__PlaneAngleUom__mila_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__mina = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__mina", energisticsApiJNI.witsml1__PlaneAngleUom__mina_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__mrad = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__mrad", energisticsApiJNI.witsml1__PlaneAngleUom__mrad_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__Mrad = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__Mrad", energisticsApiJNI.witsml1__PlaneAngleUom__Mrad_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__mseca = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__mseca", energisticsApiJNI.witsml1__PlaneAngleUom__mseca_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__seca = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__seca", energisticsApiJNI.witsml1__PlaneAngleUom__seca_get());
  public final static witsml1__PlaneAngleUom witsml1__PlaneAngleUom__urad = new witsml1__PlaneAngleUom("witsml1__PlaneAngleUom__urad", energisticsApiJNI.witsml1__PlaneAngleUom__urad_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static witsml1__PlaneAngleUom swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + witsml1__PlaneAngleUom.class + " with value " + swigValue);
  }

  private witsml1__PlaneAngleUom(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private witsml1__PlaneAngleUom(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private witsml1__PlaneAngleUom(String swigName, witsml1__PlaneAngleUom swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static witsml1__PlaneAngleUom[] swigValues = { witsml1__PlaneAngleUom__rad, witsml1__PlaneAngleUom__c, witsml1__PlaneAngleUom__ccgr, witsml1__PlaneAngleUom__cgr, witsml1__PlaneAngleUom__dega, witsml1__PlaneAngleUom__gon, witsml1__PlaneAngleUom__gr, witsml1__PlaneAngleUom__Grad, witsml1__PlaneAngleUom__krad, witsml1__PlaneAngleUom__mila, witsml1__PlaneAngleUom__mina, witsml1__PlaneAngleUom__mrad, witsml1__PlaneAngleUom__Mrad, witsml1__PlaneAngleUom__mseca, witsml1__PlaneAngleUom__seca, witsml1__PlaneAngleUom__urad };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

