/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class witsml1__WellDirection {
  public final static witsml1__WellDirection witsml1__WellDirection__huff_n_puff = new witsml1__WellDirection("witsml1__WellDirection__huff_n_puff", energisticsApiJNI.witsml1__WellDirection__huff_n_puff_get());
  public final static witsml1__WellDirection witsml1__WellDirection__injector = new witsml1__WellDirection("witsml1__WellDirection__injector", energisticsApiJNI.witsml1__WellDirection__injector_get());
  public final static witsml1__WellDirection witsml1__WellDirection__producer = new witsml1__WellDirection("witsml1__WellDirection__producer", energisticsApiJNI.witsml1__WellDirection__producer_get());
  public final static witsml1__WellDirection witsml1__WellDirection__uncertain = new witsml1__WellDirection("witsml1__WellDirection__uncertain", energisticsApiJNI.witsml1__WellDirection__uncertain_get());
  public final static witsml1__WellDirection witsml1__WellDirection__unknown = new witsml1__WellDirection("witsml1__WellDirection__unknown", energisticsApiJNI.witsml1__WellDirection__unknown_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static witsml1__WellDirection swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + witsml1__WellDirection.class + " with value " + swigValue);
  }

  private witsml1__WellDirection(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private witsml1__WellDirection(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private witsml1__WellDirection(String swigName, witsml1__WellDirection swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static witsml1__WellDirection[] swigValues = { witsml1__WellDirection__huff_n_puff, witsml1__WellDirection__injector, witsml1__WellDirection__producer, witsml1__WellDirection__uncertain, witsml1__WellDirection__unknown };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
