/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class resqml2__ContactSide {
  public final static resqml2__ContactSide resqml2__ContactSide__footwall = new resqml2__ContactSide("resqml2__ContactSide__footwall", energisticsApiJNI.resqml2__ContactSide__footwall_get());
  public final static resqml2__ContactSide resqml2__ContactSide__hanging_x0020wall = new resqml2__ContactSide("resqml2__ContactSide__hanging_x0020wall", energisticsApiJNI.resqml2__ContactSide__hanging_x0020wall_get());
  public final static resqml2__ContactSide resqml2__ContactSide__north = new resqml2__ContactSide("resqml2__ContactSide__north", energisticsApiJNI.resqml2__ContactSide__north_get());
  public final static resqml2__ContactSide resqml2__ContactSide__south = new resqml2__ContactSide("resqml2__ContactSide__south", energisticsApiJNI.resqml2__ContactSide__south_get());
  public final static resqml2__ContactSide resqml2__ContactSide__east = new resqml2__ContactSide("resqml2__ContactSide__east", energisticsApiJNI.resqml2__ContactSide__east_get());
  public final static resqml2__ContactSide resqml2__ContactSide__west = new resqml2__ContactSide("resqml2__ContactSide__west", energisticsApiJNI.resqml2__ContactSide__west_get());
  public final static resqml2__ContactSide resqml2__ContactSide__younger = new resqml2__ContactSide("resqml2__ContactSide__younger", energisticsApiJNI.resqml2__ContactSide__younger_get());
  public final static resqml2__ContactSide resqml2__ContactSide__older = new resqml2__ContactSide("resqml2__ContactSide__older", energisticsApiJNI.resqml2__ContactSide__older_get());
  public final static resqml2__ContactSide resqml2__ContactSide__both = new resqml2__ContactSide("resqml2__ContactSide__both", energisticsApiJNI.resqml2__ContactSide__both_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static resqml2__ContactSide swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + resqml2__ContactSide.class + " with value " + swigValue);
  }

  private resqml2__ContactSide(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private resqml2__ContactSide(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private resqml2__ContactSide(String swigName, resqml2__ContactSide swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static resqml2__ContactSide[] swigValues = { resqml2__ContactSide__footwall, resqml2__ContactSide__hanging_x0020wall, resqml2__ContactSide__north, resqml2__ContactSide__south, resqml2__ContactSide__east, resqml2__ContactSide__west, resqml2__ContactSide__younger, resqml2__ContactSide__older, resqml2__ContactSide__both };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

