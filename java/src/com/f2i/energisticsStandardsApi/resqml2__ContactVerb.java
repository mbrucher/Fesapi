/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class resqml2__ContactVerb {
  public final static resqml2__ContactVerb resqml2__ContactVerb__splits = new resqml2__ContactVerb("resqml2__ContactVerb__splits", energisticsApiJNI.resqml2__ContactVerb__splits_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__interrupts = new resqml2__ContactVerb("resqml2__ContactVerb__interrupts", energisticsApiJNI.resqml2__ContactVerb__interrupts_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__contains = new resqml2__ContactVerb("resqml2__ContactVerb__contains", energisticsApiJNI.resqml2__ContactVerb__contains_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__conforms = new resqml2__ContactVerb("resqml2__ContactVerb__conforms", energisticsApiJNI.resqml2__ContactVerb__conforms_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__erodes = new resqml2__ContactVerb("resqml2__ContactVerb__erodes", energisticsApiJNI.resqml2__ContactVerb__erodes_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__stops_x0020at = new resqml2__ContactVerb("resqml2__ContactVerb__stops_x0020at", energisticsApiJNI.resqml2__ContactVerb__stops_x0020at_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__crosses = new resqml2__ContactVerb("resqml2__ContactVerb__crosses", energisticsApiJNI.resqml2__ContactVerb__crosses_get());
  public final static resqml2__ContactVerb resqml2__ContactVerb__includes = new resqml2__ContactVerb("resqml2__ContactVerb__includes", energisticsApiJNI.resqml2__ContactVerb__includes_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static resqml2__ContactVerb swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + resqml2__ContactVerb.class + " with value " + swigValue);
  }

  private resqml2__ContactVerb(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private resqml2__ContactVerb(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private resqml2__ContactVerb(String swigName, resqml2__ContactVerb swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static resqml2__ContactVerb[] swigValues = { resqml2__ContactVerb__splits, resqml2__ContactVerb__interrupts, resqml2__ContactVerb__contains, resqml2__ContactVerb__conforms, resqml2__ContactVerb__erodes, resqml2__ContactVerb__stops_x0020at, resqml2__ContactVerb__crosses, resqml2__ContactVerb__includes };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

