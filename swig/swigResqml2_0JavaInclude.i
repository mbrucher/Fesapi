%pragma(java) jniclasscode=%{
  public static com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject resqml2_0_instantiateConcreteObject(long cPtr, boolean owner)
  {
    com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject ret = null;
    if (cPtr == 0) {
      return ret;
    }
	
    ret = resqml2_0_instantiateWellboreFrameRepresentationObject(cPtr, owner);
    if (ret != null) {
		return ret;
    }
	
	ret = resqml2_0_instantiateConcreteLocal3dCrs(cPtr, owner);
	if (ret != null) {
		return ret;
	}
	
    String type = resqml2_0_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject(cPtr, false));
    if (type.equals("BoundaryFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.BoundaryFeature(cPtr, owner);
    }
    else if (type.equals("BoundaryFeatureInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.BoundaryFeatureInterpretation(cPtr, owner);
    }
    else if (type.equals("CategoricalProperty"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.CategoricalProperty(cPtr, owner);
    }
    else if (type.equals("CommentProperty"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.CommentProperty(cPtr, owner);
    }
    else if (type.equals("ContinuousProperty"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.ContinuousProperty(cPtr, owner);
    }
    else if (type.equals("DiscreteProperty"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.DiscreteProperty(cPtr, owner);
    }
    else if (type.equals("EarthModelInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.EarthModelInterpretation(cPtr, owner);
    }
    else if (type.equals("EpcExternalPartReference"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.HdfProxy(cPtr, owner);
    }
    else if (type.equals("FaultInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.FaultInterpretation(cPtr, owner);
    }
    else if (type.equals("FrontierFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.FrontierFeature(cPtr, owner);
    }
    else if (type.equals("GenericFeatureInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.GenericFeatureInterpretation(cPtr, owner);
    }
    else if (type.equals("GeneticBoundaryFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.Horizon(cPtr, owner);
    }
    else if (type.equals("GeologicUnitFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.GeologicUnitFeature(cPtr, owner);
    }
    else if (type.equals("Grid2dRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation(cPtr, owner);
    }
    else if (type.equals("Grid2dSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation(cPtr, owner);
    }
    else if (type.equals("GridConnectionSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.GridConnectionSetRepresentation(cPtr, owner);
    }
    else if (type.equals("HorizonInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation(cPtr, owner);
    }
    else if (type.equals("IjkGridRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.IjkGridRepresentation(cPtr, owner);
    }
    else if (type.equals("MdDatum"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.MdDatum(cPtr, owner);
    }
    else if (type.equals("NonSealedSurfaceFrameworkRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
    }
    else if (type.equals("OrganizationFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.OrganizationFeature(cPtr, owner);
    }
    else if (type.equals("PlaneSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.PlaneSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PointSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.PointSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PolylineRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.PolylineRepresentation(cPtr, owner);
    }
    else if (type.equals("PolylineSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation(cPtr, owner);
    }
    else if (type.equals("PropertyKind"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.PropertyKind(cPtr, owner);
    }
    else if (type.equals("RepresentationSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.RepresentationSetRepresentation(cPtr, owner);
    }
    else if (type.equals("SeismicLatticeFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.SeismicLatticeFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLineFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature(cPtr, owner);
    }
    else if (type.equals("SeismicLineSetFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.SeismicLineSetFeature(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumn"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumn(cPtr, owner);
    }
    else if (type.equals("StratigraphicColumnRankInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicOccurrenceInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type.equals("StratigraphicUnitFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicUnitFeature(cPtr, owner);
    }
    else if (type.equals("StratigraphicUnitInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StratigraphicUnitInterpretation(cPtr, owner);
    }
    else if (type.equals("StringTableLookup"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StringTableLookup(cPtr, owner);
    }
    else if (type.equals("StructuralOrganizationInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.StructuralOrganizationInterpretation(cPtr, owner);
    }
    else if (type.equals("SubRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.SubRepresentation(cPtr, owner);
    }
    else if (type.equals("TectonicBoundaryFeature"))
    {
		com.f2i.energisticsStandardsApi.resqml2_0.TectonicBoundaryFeature tmp = new com.f2i.energisticsStandardsApi.resqml2_0.TectonicBoundaryFeature(cPtr, owner);
		if (tmp.isAFracture() == true)
			ret = new com.f2i.energisticsStandardsApi.resqml2_0.Fracture(cPtr, owner);
		else
			ret = new com.f2i.energisticsStandardsApi.resqml2_0.Fault(cPtr, owner);
    }
    else if (type.equals("TimeSeries"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.TimeSeries(cPtr, owner);
    }
    else if (type.equals("TriangulatedSetRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation(cPtr, owner);
    }
    else if (type.equals("UnstructuredGridRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.UnstructuredGridRepresentation(cPtr, owner);
    }
    else if (type.equals("WellboreFeature"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.WellboreFeature(cPtr, owner);
    }
    else if (type.equals("WellboreInterpretation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.WellboreInterpretation(cPtr, owner);
    }
    else if (type.equals("WellboreTrajectoryRepresentation"))
    {
        ret = new com.f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation(cPtr, owner);
    }
    else
    {
		throw new IllegalArgumentException("Encountered type " + type + " that is not known to be a Resqml concrete class");
    }
    return ret;
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject resqml2_0_instantiateWellboreFrameRepresentationObject(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = resqml2_0_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject(cPtr, false));
	if (type.equals("WellboreFrameRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0.WellboreFrameRepresentation(cPtr, owner);
    }
    else if (type.equals("WellboreMarkerFrameRepresentation"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0.WellboreMarkerFrameRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject resqml2_0_instantiateConcreteLocal3dCrs(long cPtr, boolean owner)
  {
    if (cPtr == 0) {
      return null;
    }
    String type = resqml2_0_AbstractObject_getXmlTag(cPtr, new com.f2i.energisticsStandardsApi.resqml2_0.AbstractObject(cPtr, false));
	
    if (type.equals("LocalDepth3dCrs"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0.LocalDepth3dCrs(cPtr, owner);
    }
    else if (type.equals("LocalTime3dCrs"))
    {
        return new com.f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs(cPtr, owner);
    }
	else
		return null;
	}
%}

namespace resqml2_0
{	
	%typemap(javaout) AbstractObject*, AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractValuesProperty*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) energisticsApiJNI.resqml2_0_instantiateConcreteObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) WellboreFrameRepresentation*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) energisticsApiJNI.resqml2_0_instantiateWellboreFrameRepresentationObject(cPtr, $owner);
		return ret;
	}
	
	%typemap(javaout) AbstractLocal3dCrs*  {
		long cPtr = $jnicall;
		$javaclassname ret = ($javaclassname) energisticsApiJNI.resqml2_0_instantiateConcreteLocal3dCrs(cPtr, $owner);
		return ret;
	}

	%typemap(javaimports) SWIGTYPE %{
		import com.f2i.energisticsStandardsApi.*;
	%}
}
