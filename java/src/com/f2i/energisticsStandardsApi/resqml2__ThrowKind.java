/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class resqml2__ThrowKind {
  public final static resqml2__ThrowKind resqml2__ThrowKind__reverse = new resqml2__ThrowKind("resqml2__ThrowKind__reverse", energisticsApiJNI.resqml2__ThrowKind__reverse_get());
  public final static resqml2__ThrowKind resqml2__ThrowKind__normal = new resqml2__ThrowKind("resqml2__ThrowKind__normal", energisticsApiJNI.resqml2__ThrowKind__normal_get());
  public final static resqml2__ThrowKind resqml2__ThrowKind__thrust = new resqml2__ThrowKind("resqml2__ThrowKind__thrust", energisticsApiJNI.resqml2__ThrowKind__thrust_get());
  public final static resqml2__ThrowKind resqml2__ThrowKind__strike_x0020and_x0020slip = new resqml2__ThrowKind("resqml2__ThrowKind__strike_x0020and_x0020slip", energisticsApiJNI.resqml2__ThrowKind__strike_x0020and_x0020slip_get());
  public final static resqml2__ThrowKind resqml2__ThrowKind__scissor = new resqml2__ThrowKind("resqml2__ThrowKind__scissor", energisticsApiJNI.resqml2__ThrowKind__scissor_get());
  public final static resqml2__ThrowKind resqml2__ThrowKind__variable = new resqml2__ThrowKind("resqml2__ThrowKind__variable", energisticsApiJNI.resqml2__ThrowKind__variable_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static resqml2__ThrowKind swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + resqml2__ThrowKind.class + " with value " + swigValue);
  }

  private resqml2__ThrowKind(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private resqml2__ThrowKind(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private resqml2__ThrowKind(String swigName, resqml2__ThrowKind swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static resqml2__ThrowKind[] swigValues = { resqml2__ThrowKind__reverse, resqml2__ThrowKind__normal, resqml2__ThrowKind__thrust, resqml2__ThrowKind__strike_x0020and_x0020slip, resqml2__ThrowKind__scissor, resqml2__ThrowKind__variable };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
