/**********************************************************************
This file add special SWIG management of the C++ polymorphic datatype.
Basically this file add methods resqml2_0_instantiate* which will create the right Java instance according to what it is exactly.
**********************************************************************/

%pragma(java) jniclasscode=%{
  public static com.f2i.energisticsStandardsApi.resqml2.AbstractObject resqml2_instantiateConcreteObject(long cPtr, boolean owner)
  {
	com.f2i.energisticsStandardsApi.resqml2.AbstractObject ret = null;
	if (cPtr == 0) {
		return ret;
	}
	
	ret = resqml2_0_1_instantiateConcreteProperty(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_0_1_instantiateConcreteLocal3dCrs(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
	ret = resqml2_0_1_instantiateConcreteStratigraphicOrganizationInterpretation(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
    String type = resqml2_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2.AbstractObject(cPtr, false));
    if (type.equals("Activity"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.Activity(cPtr, owner);
    }
    else if (type.equals("ActivityTemplate"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.ActivityTemplate(cPtr, owner);
    }
    else if (type.equals("BoundaryFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.BoundaryFeature(cPtr, owner);
    }
    else if (type.equals("BoundaryFeatureInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.BoundaryFeatureInterpretation(cPtr, owner);
    }
    else if (type.equals("EarthModelInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.EarthModelInterpretation(cPtr, owner);
    }
    else if (type.equals("EpcExternalPartReference"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2.HdfProxy(cPtr, owner);
    }
    else if (type.equals("FaultInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.FaultInterpretation(cPtr, owner);
    }
    else if (type.equals("FrontierFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.FrontierFeature(cPtr, owner);
    }
    else if (type.equals("GenericFeatureInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.GenericFeatureInterpretation(cPtr, owner);
    }
    else if (type.equals("GeneticBoundaryFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.Horizon(cPtr, owner);
    }
    else if (type.equals("GeologicUnitFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.GeologicUnitFeature(cPtr, owner);
    }
    else if (type.equals("Grid2dRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.Grid2dRepresentation(cPtr, owner);
    }
    else if (type.equals("Grid2dSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.Grid2dSetRepresentation(cPtr, owner);
    }
    else if (type.equals("GridConnectionSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.GridConnectionSetRepresentation(cPtr, owner);
    }
    else if (type.equals("HorizonInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.HorizonInterpretation(cPtr, owner);
    }
    else if (type.equals("IjkGridRepresentation"))
    {
		ret = resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, owner);
    }
    else if (type.equals("MdDatum"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.MdDatum(cPtr, owner);
    }
    else if (type.equals("NonSealedSurfaceFrameworkRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
    }
    else if (type.equals("OrganizationFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.OrganizationFeature(cPtr, owner);
    }
    else if (type.equals("PlaneSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.PlaneSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PointSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.PointSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PolylineRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.PolylineRepresentation(cPtr, owner);
    }
    else if (type.equals("PolylineSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.PolylineSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PropertyKind"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.PropertyKind(cPtr, owner);
    }
    else if (type.equals("RepresentationSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.RepresentationSetRepresentation(cPtr, owner);
    }
    else if (type.equals("SeismicLatticeFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.SeismicLatticeFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLineFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.SeismicLineFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLineSetFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.SeismicLineSetFeature(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumn"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicColumn(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumnRankInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicOccurrenceInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicUnitFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicUnitFeature(cPtr, owner);
    }
    else if (type.equals("StratigraphicUnitInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicUnitInterpretation(cPtr, owner);
    }
    else if (type.equals("StringTableLookup"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StringTableLookup(cPtr, owner);
    }
    else if (type.equals("StructuralOrganizationInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.StructuralOrganizationInterpretation(cPtr, owner);
    }
    else if (type.equals("SubRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.SubRepresentation(cPtr, owner);
    }
    else if (type.equals("TectonicBoundaryFeature"))
    {
		com.f2i.energisticsStandardsApi.resqml2_0_1.TectonicBoundaryFeature tmp = new com.f2i.energisticsStandardsApi.resqml2_0_1.TectonicBoundaryFeature(cPtr, owner);
		if (tmp.isAFracture() == true)
			ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.Fracture(cPtr, owner);
		else
			ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.Fault(cPtr, owner);
    }
    else if (type.equals("TimeSeries"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.TimeSeries(cPtr, owner);
    }
    else if (type.equals("TriangulatedSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.TriangulatedSetRepresentation(cPtr, owner);
    }
    else if (type.equals("UnstructuredGridRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.UnstructuredGridRepresentation(cPtr, owner);
    }
    else if (type.equals("WellboreFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.WellboreFeature(cPtr, owner);
    }
    else if (type.equals("WellboreInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.WellboreInterpretation(cPtr, owner);
    }
    else if (type.equals("WellboreTrajectoryRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0_1.WellboreTrajectoryRepresentation(cPtr, owner);
    }
    else
    {
		throw new IllegalArgumentException("Encountered type " + type + " that is not known to be a Resqml concrete class");
    }
    return ret;
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2.AbstractObject resqml2_0_1_instantiateConcreteProperty(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = resqml2_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2.AbstractObject(cPtr, false));
	if (type.equals("CategoricalProperty"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.CategoricalProperty(cPtr, owner);
    }
	else if (type.equals("CategoricalPropertySeries"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.CategoricalPropertySeries(cPtr, owner);
    }
    else if (type.equals("CommentProperty"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.CommentProperty(cPtr, owner);
    }
    else if (type.equals("ContinuousProperty"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.ContinuousProperty(cPtr, owner);
    }
    else if (type.equals("ContinuousPropertySeries"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.ContinuousPropertySeries(cPtr, owner);
    }
    else if (type.equals("DiscreteProperty"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.DiscreteProperty(cPtr, owner);
    }
	else if (type.equals("DiscretePropertySeries"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.DiscretePropertySeries(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2.AbstractObject resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = resqml2_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2.AbstractObject(cPtr, false));
	if (type.equals("WellboreFrameRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.WellboreFrameRepresentation(cPtr, owner);
    }
    else if (type.equals("WellboreMarkerFrameRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.WellboreMarkerFrameRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2.AbstractObject resqml2_0_1_instantiateConcreteLocal3dCrs(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = resqml2_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2.AbstractObject(cPtr, false));
	
    if (type.equals("LocalDepth3dCrs"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.LocalDepth3dCrs(cPtr, owner);
    }
    else if (type.equals("LocalTime3dCrs"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.LocalTime3dCrs(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation resqml2_0_1_instantiateConcreteIjkGridRepresentation(long cPtr, boolean owner)
  {
    if (cPtr == 0) { return null; }
    com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind type = com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind
        .swigToEnum(resqml2_0_1_AbstractIjkGridRepresentation_getGeometryKind(cPtr, new com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation(cPtr, false)));

    if (type == com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind.EXPLICIT) {
      return new com.f2i.energisticsStandardsApi.resqml2_0_1.IjkGridExplicitRepresentation(cPtr, owner);
    }
    else if (type == com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC) {
      return new com.f2i.energisticsStandardsApi.resqml2_0_1.IjkGridParametricRepresentation(cPtr, owner);
    }
    else if (type == com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind.LATTICE) {
      return new com.f2i.energisticsStandardsApi.resqml2_0_1.IjkGridLatticeRepresentation(cPtr, owner);
    }
    else // TODO : see if it is possible to return the object itself instead of a copy.
    {
      return new com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation(cPtr, owner);
    }
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2_0_1.AbstractStratigraphicOrganizationInterpretation resqml2_0_1_instantiateConcreteStratigraphicOrganizationInterpretation(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = resqml2_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2.AbstractObject(cPtr, false));
	
    if (type.equals("StratigraphicOccurrenceInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumnRankInterpretation"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
	else
		return null;
  }
%}

namespace resqml2
{	
	%typemap(javaout) AbstractObject*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}

namespace resqml2_0_1
{	
	%typemap(javaout) AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractValuesProperty*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) WellboreFrameRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractLocal3dCrs*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_0_1_instantiateConcreteLocal3dCrs(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractIjkGridRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractProperty*, AbstractValuesProperty*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_0_1_instantiateConcreteProperty(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractStratigraphicOrganizationInterpretation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) fesapiJNI.resqml2_0_1_instantiateConcreteStratigraphicOrganizationInterpretation(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}
