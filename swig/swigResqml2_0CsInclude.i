/**********************************************************************
This file add special SWIG management of the C++ polymorphic datatype.
Basically this file add a method resqml2_0_instantiateConcreteObject which will create the right C# instance according to what it is exactly.
**********************************************************************/

%pragma(csharp) imclasscode=%{
  public static f2i.energisticsStandardsApi.resqml2_0.AbstractObject resqml2_0_instantiateConcreteObject(global::System.IntPtr cPtr, bool owner)
  {
    f2i.energisticsStandardsApi.resqml2_0.AbstractObject ret = null;
    if (cPtr == global::System.IntPtr.Zero) {
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
	
    string type = $modulePINVOKE.resqml2_0_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "BoundaryFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.BoundaryFeature(cPtr, owner);
    }
    else if (type == "BoundaryFeatureInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.BoundaryFeatureInterpretation(cPtr, owner);
    }
    else if (type == "CategoricalProperty")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.CategoricalProperty(cPtr, owner);
    }
    else if (type == "CommentProperty")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.CommentProperty(cPtr, owner);
    }
    else if (type == "ContinuousProperty")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.ContinuousProperty(cPtr, owner);
    }
    else if (type == "DiscreteProperty")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.DiscreteProperty(cPtr, owner);
    }
    else if (type == "EarthModelInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.EarthModelInterpretation(cPtr, owner);
    }
    else if (type == "EpcExternalPartReference")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.HdfProxy(cPtr, owner);
    }
    else if (type == "FaultInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.FaultInterpretation(cPtr, owner);
    }
    else if (type == "FluidBoundaryFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.FluidBoundaryFeature(cPtr, owner);
    }
    else if (type == "FrontierFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.FrontierFeature(cPtr, owner);
    }
    else if (type == "GenericFeatureInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.GenericFeatureInterpretation(cPtr, owner);
    }
    else if (type == "GeneticBoundaryFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.Horizon(cPtr, owner);
    }
    else if (type == "GeologicUnitFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.GeologicUnitFeature(cPtr, owner);
    }
    else if (type == "Grid2dRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.Grid2dRepresentation(cPtr, owner);
    }
    else if (type == "Grid2dSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation(cPtr, owner);
    }
    else if (type == "GridConnectionSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.GridConnectionSetRepresentation(cPtr, owner);
    }
    else if (type == "HorizonInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.HorizonInterpretation(cPtr, owner);
    }
    else if (type == "IjkGridRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.IjkGridRepresentation(cPtr, owner);
    }
    else if (type == "MdDatum")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.MdDatum(cPtr, owner);
    }
    else if (type == "NonSealedSurfaceFrameworkRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
    }
    else if (type == "OrganizationFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.OrganizationFeature(cPtr, owner);
    }
    else if (type == "PlaneSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.PlaneSetRepresentation(cPtr, owner);
    }
    else if (type == "PointSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.PointSetRepresentation(cPtr, owner);
    }
    else if (type == "PolylineRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.PolylineRepresentation(cPtr, owner);
    }
    else if (type == "PolylineSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.PolylineSetRepresentation(cPtr, owner);
    }
    else if (type == "PropertyKind")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.PropertyKind(cPtr, owner);
    }
    else if (type == "RepresentationSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.RepresentationSetRepresentation(cPtr, owner);
    }
    else if (type == "SeismicLatticeFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.SeismicLatticeFeature(cPtr, owner);
    }
    else if (type == "SeismicLineFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature(cPtr, owner);
    }
    else if (type == "SeismicLineSetFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.SeismicLineSetFeature(cPtr, owner);
    }
    else if (type == "StratigraphicColumn")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumn(cPtr, owner);
    }
    else if (type == "StratigraphicColumnRankInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicOccurrenceInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicUnitFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StratigraphicUnitFeature(cPtr, owner);
    }
    else if (type == "StratigraphicUnitInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StratigraphicUnitInterpretation(cPtr, owner);
    }
    else if (type == "StringTableLookup")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StringTableLookup(cPtr, owner);
    }
    else if (type == "StructuralOrganizationInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.StructuralOrganizationInterpretation(cPtr, owner);
    }
    else if (type == "SubRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.SubRepresentation(cPtr, owner);
    }
    else if (type == "TectonicBoundaryFeature")
    {
		f2i.energisticsStandardsApi.resqml2_0.TectonicBoundaryFeature tmp = new f2i.energisticsStandardsApi.resqml2_0.TectonicBoundaryFeature(cPtr, owner);
		if (tmp.isAFracture() == true)
			ret = new f2i.energisticsStandardsApi.resqml2_0.Fracture(cPtr, owner);
		else
			ret = new f2i.energisticsStandardsApi.resqml2_0.Fault(cPtr, owner);
    }
    else if (type == "TimeSeries")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.TimeSeries(cPtr, owner);
    }
    else if (type == "TriangulatedSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.TriangulatedSetRepresentation(cPtr, owner);
    }
    else if (type == "UnstructuredGridRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.UnstructuredGridRepresentation(cPtr, owner);
    }
    else if (type == "WellboreFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.WellboreFeature(cPtr, owner);
    }
    else if (type == "WellboreInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.WellboreInterpretation(cPtr, owner);
    }
    else if (type == "WellboreTrajectoryRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0.WellboreTrajectoryRepresentation(cPtr, owner);
    }
	else
	{
		throw new System.ArgumentException(string.Format("Encountered type '{0}' that is not known to be a Resqml concrete class", type.ToString()));
	}
	
	return ret;
  }
  
  public static f2i.energisticsStandardsApi.resqml2_0.AbstractObject resqml2_0_instantiateWellboreFrameRepresentationObject(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.resqml2_0_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "WellboreFrameRepresentation")
    {
        return new f2i.energisticsStandardsApi.resqml2_0.WellboreFrameRepresentation(cPtr, owner);
    }
    else if (type == "WellboreMarkerFrameRepresentation")
    {
        return new f2i.energisticsStandardsApi.resqml2_0.WellboreMarkerFrameRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.resqml2_0.AbstractObject resqml2_0_instantiateConcreteLocal3dCrs(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.resqml2_0_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	
    if (type == "LocalDepth3dCrs")
    {
        return new f2i.energisticsStandardsApi.resqml2_0.LocalDepth3dCrs(cPtr, owner);
    }
    else if (type == "LocalTime3dCrs")
    {
        return new f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs(cPtr, owner);
    }
	else
		return null;
  }
%}

namespace resqml2_0
{	
	%typemap(csout, excode=SWIGEXCODE) AbstractObject*, AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractValuesProperty*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) WellboreFrameRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_instantiateWellboreFrameRepresentationObject(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractLocal3dCrs*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_instantiateConcreteLocal3dCrs(cPtr, $owner);$excode
		return ret;
	}
}
