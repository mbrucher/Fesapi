/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class witsml1__AziRef {
  public final static witsml1__AziRef witsml1__AziRef__magnetic_x0020north = new witsml1__AziRef("witsml1__AziRef__magnetic_x0020north", energisticsApiJNI.witsml1__AziRef__magnetic_x0020north_get());
  public final static witsml1__AziRef witsml1__AziRef__grid_x0020north = new witsml1__AziRef("witsml1__AziRef__grid_x0020north", energisticsApiJNI.witsml1__AziRef__grid_x0020north_get());
  public final static witsml1__AziRef witsml1__AziRef__true_x0020north = new witsml1__AziRef("witsml1__AziRef__true_x0020north", energisticsApiJNI.witsml1__AziRef__true_x0020north_get());
  public final static witsml1__AziRef witsml1__AziRef__unknown = new witsml1__AziRef("witsml1__AziRef__unknown", energisticsApiJNI.witsml1__AziRef__unknown_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static witsml1__AziRef swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + witsml1__AziRef.class + " with value " + swigValue);
  }

  private witsml1__AziRef(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private witsml1__AziRef(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private witsml1__AziRef(String swigName, witsml1__AziRef swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static witsml1__AziRef[] swigValues = { witsml1__AziRef__magnetic_x0020north, witsml1__AziRef__grid_x0020north, witsml1__AziRef__true_x0020north, witsml1__AziRef__unknown };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

