/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.5
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.f2i.energisticsStandardsApi;

public final class resqml2__MdReference {
  public final static resqml2__MdReference resqml2__MdReference__ground_x0020level = new resqml2__MdReference("resqml2__MdReference__ground_x0020level", energisticsApiJNI.resqml2__MdReference__ground_x0020level_get());
  public final static resqml2__MdReference resqml2__MdReference__kelly_x0020bushing = new resqml2__MdReference("resqml2__MdReference__kelly_x0020bushing", energisticsApiJNI.resqml2__MdReference__kelly_x0020bushing_get());
  public final static resqml2__MdReference resqml2__MdReference__mean_x0020sea_x0020level = new resqml2__MdReference("resqml2__MdReference__mean_x0020sea_x0020level", energisticsApiJNI.resqml2__MdReference__mean_x0020sea_x0020level_get());
  public final static resqml2__MdReference resqml2__MdReference__derrick_x0020floor = new resqml2__MdReference("resqml2__MdReference__derrick_x0020floor", energisticsApiJNI.resqml2__MdReference__derrick_x0020floor_get());
  public final static resqml2__MdReference resqml2__MdReference__casing_x0020flange = new resqml2__MdReference("resqml2__MdReference__casing_x0020flange", energisticsApiJNI.resqml2__MdReference__casing_x0020flange_get());
  public final static resqml2__MdReference resqml2__MdReference__arbitrary_x0020point = new resqml2__MdReference("resqml2__MdReference__arbitrary_x0020point", energisticsApiJNI.resqml2__MdReference__arbitrary_x0020point_get());
  public final static resqml2__MdReference resqml2__MdReference__crown_x0020valve = new resqml2__MdReference("resqml2__MdReference__crown_x0020valve", energisticsApiJNI.resqml2__MdReference__crown_x0020valve_get());
  public final static resqml2__MdReference resqml2__MdReference__rotary_x0020bushing = new resqml2__MdReference("resqml2__MdReference__rotary_x0020bushing", energisticsApiJNI.resqml2__MdReference__rotary_x0020bushing_get());
  public final static resqml2__MdReference resqml2__MdReference__rotary_x0020table = new resqml2__MdReference("resqml2__MdReference__rotary_x0020table", energisticsApiJNI.resqml2__MdReference__rotary_x0020table_get());
  public final static resqml2__MdReference resqml2__MdReference__sea_x0020floor = new resqml2__MdReference("resqml2__MdReference__sea_x0020floor", energisticsApiJNI.resqml2__MdReference__sea_x0020floor_get());
  public final static resqml2__MdReference resqml2__MdReference__lowest_x0020astronomical_x0020tide = new resqml2__MdReference("resqml2__MdReference__lowest_x0020astronomical_x0020tide", energisticsApiJNI.resqml2__MdReference__lowest_x0020astronomical_x0020tide_get());
  public final static resqml2__MdReference resqml2__MdReference__mean_x0020higher_x0020high_x0020water = new resqml2__MdReference("resqml2__MdReference__mean_x0020higher_x0020high_x0020water", energisticsApiJNI.resqml2__MdReference__mean_x0020higher_x0020high_x0020water_get());
  public final static resqml2__MdReference resqml2__MdReference__mean_x0020high_x0020water = new resqml2__MdReference("resqml2__MdReference__mean_x0020high_x0020water", energisticsApiJNI.resqml2__MdReference__mean_x0020high_x0020water_get());
  public final static resqml2__MdReference resqml2__MdReference__mean_x0020lower_x0020low_x0020water = new resqml2__MdReference("resqml2__MdReference__mean_x0020lower_x0020low_x0020water", energisticsApiJNI.resqml2__MdReference__mean_x0020lower_x0020low_x0020water_get());
  public final static resqml2__MdReference resqml2__MdReference__mean_x0020low_x0020water = new resqml2__MdReference("resqml2__MdReference__mean_x0020low_x0020water", energisticsApiJNI.resqml2__MdReference__mean_x0020low_x0020water_get());
  public final static resqml2__MdReference resqml2__MdReference__mean_x0020tide_x0020level = new resqml2__MdReference("resqml2__MdReference__mean_x0020tide_x0020level", energisticsApiJNI.resqml2__MdReference__mean_x0020tide_x0020level_get());
  public final static resqml2__MdReference resqml2__MdReference__kickoff_x0020point = new resqml2__MdReference("resqml2__MdReference__kickoff_x0020point", energisticsApiJNI.resqml2__MdReference__kickoff_x0020point_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static resqml2__MdReference swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + resqml2__MdReference.class + " with value " + swigValue);
  }

  private resqml2__MdReference(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private resqml2__MdReference(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private resqml2__MdReference(String swigName, resqml2__MdReference swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static resqml2__MdReference[] swigValues = { resqml2__MdReference__ground_x0020level, resqml2__MdReference__kelly_x0020bushing, resqml2__MdReference__mean_x0020sea_x0020level, resqml2__MdReference__derrick_x0020floor, resqml2__MdReference__casing_x0020flange, resqml2__MdReference__arbitrary_x0020point, resqml2__MdReference__crown_x0020valve, resqml2__MdReference__rotary_x0020bushing, resqml2__MdReference__rotary_x0020table, resqml2__MdReference__sea_x0020floor, resqml2__MdReference__lowest_x0020astronomical_x0020tide, resqml2__MdReference__mean_x0020higher_x0020high_x0020water, resqml2__MdReference__mean_x0020high_x0020water, resqml2__MdReference__mean_x0020lower_x0020low_x0020water, resqml2__MdReference__mean_x0020low_x0020water, resqml2__MdReference__mean_x0020tide_x0020level, resqml2__MdReference__kickoff_x0020point };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

