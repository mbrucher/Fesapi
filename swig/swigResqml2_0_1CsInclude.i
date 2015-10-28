/**********************************************************************
This file add special SWIG management of the C++ polymorphic datatype.
Basically this file add methods resqml2_0_instantiate* which will create the right C# instance according to what it is exactly.
**********************************************************************/

%pragma(csharp) imclasscode=%{
  public static f2i.energisticsStandardsApi.resqml2_0_1.AbstractObject resqml2_0_1_instantiateConcreteObject(global::System.IntPtr cPtr, bool owner)
  {
    f2i.energisticsStandardsApi.resqml2_0_1.AbstractObject ret = null;
    if (cPtr == global::System.IntPtr.Zero) {
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
	
    string type = $modulePINVOKE.resqml2_0_1_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "Activity")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.Activity(cPtr, owner);
    }
	else if (type == "ActivityTemplate")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.ActivityTemplate(cPtr, owner);
    }
	else if (type == "BoundaryFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.BoundaryFeature(cPtr, owner);
    }
    else if (type == "BoundaryFeatureInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.BoundaryFeatureInterpretation(cPtr, owner);
    }
    else if (type == "EarthModelInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.EarthModelInterpretation(cPtr, owner);
    }
    else if (type == "EpcExternalPartReference")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.HdfProxy(cPtr, owner);
    }
    else if (type == "FaultInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.FaultInterpretation(cPtr, owner);
    }
    else if (type == "FluidBoundaryFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.FluidBoundaryFeature(cPtr, owner);
    }
    else if (type == "FrontierFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.FrontierFeature(cPtr, owner);
    }
    else if (type == "GenericFeatureInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.GenericFeatureInterpretation(cPtr, owner);
    }
    else if (type == "GeneticBoundaryFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.Horizon(cPtr, owner);
    }
    else if (type == "GeologicUnitFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.GeologicUnitFeature(cPtr, owner);
    }
    else if (type == "Grid2dRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.Grid2dRepresentation(cPtr, owner);
    }
    else if (type == "Grid2dSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.Grid2dSetRepresentation(cPtr, owner);
    }
    else if (type == "GridConnectionSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.GridConnectionSetRepresentation(cPtr, owner);
    }
    else if (type == "HorizonInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.HorizonInterpretation(cPtr, owner);
    }
    else if (type == "IjkGridRepresentation")
    {
		ret = resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, owner);
    }
    else if (type == "MdDatum")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.MdDatum(cPtr, owner);
    }
    else if (type == "NonSealedSurfaceFrameworkRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.NonSealedSurfaceFrameworkRepresentation(cPtr, owner);
    }
    else if (type == "OrganizationFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.OrganizationFeature(cPtr, owner);
    }
    else if (type == "PlaneSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.PlaneSetRepresentation(cPtr, owner);
    }
    else if (type == "PointSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.PointSetRepresentation(cPtr, owner);
    }
    else if (type == "PolylineRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.PolylineRepresentation(cPtr, owner);
    }
    else if (type == "PolylineSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.PolylineSetRepresentation(cPtr, owner);
    }
    else if (type == "PropertyKind")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.PropertyKind(cPtr, owner);
    }
    else if (type == "RepresentationSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.RepresentationSetRepresentation(cPtr, owner);
    }
    else if (type == "SeismicLatticeFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.SeismicLatticeFeature(cPtr, owner);
    }
    else if (type == "SeismicLineFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.SeismicLineFeature(cPtr, owner);
    }
    else if (type == "SeismicLineSetFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.SeismicLineSetFeature(cPtr, owner);
    }
    else if (type == "StratigraphicColumn")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicColumn(cPtr, owner);
    }
    else if (type == "StratigraphicColumnRankInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicColumnRankInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicOccurrenceInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicOccurrenceInterpretation(cPtr, owner);
    }
    else if (type == "StratigraphicUnitFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicUnitFeature(cPtr, owner);
    }
    else if (type == "StratigraphicUnitInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StratigraphicUnitInterpretation(cPtr, owner);
    }
    else if (type == "StringTableLookup")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StringTableLookup(cPtr, owner);
    }
    else if (type == "StructuralOrganizationInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.StructuralOrganizationInterpretation(cPtr, owner);
    }
    else if (type == "SubRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.SubRepresentation(cPtr, owner);
    }
    else if (type == "TectonicBoundaryFeature")
    {
		f2i.energisticsStandardsApi.resqml2_0_1.TectonicBoundaryFeature tmp = new f2i.energisticsStandardsApi.resqml2_0_1.TectonicBoundaryFeature(cPtr, owner);
		if (tmp.isAFracture() == true)
			ret = new f2i.energisticsStandardsApi.resqml2_0_1.Fracture(cPtr, owner);
		else
			ret = new f2i.energisticsStandardsApi.resqml2_0_1.Fault(cPtr, owner);
    }
    else if (type == "TimeSeries")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.TimeSeries(cPtr, owner);
    }
    else if (type == "TriangulatedSetRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.TriangulatedSetRepresentation(cPtr, owner);
    }
    else if (type == "UnstructuredGridRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.UnstructuredGridRepresentation(cPtr, owner);
    }
    else if (type == "WellboreFeature")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.WellboreFeature(cPtr, owner);
    }
    else if (type == "WellboreInterpretation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.WellboreInterpretation(cPtr, owner);
    }
    else if (type == "WellboreTrajectoryRepresentation")
    {
        ret = new f2i.energisticsStandardsApi.resqml2_0_1.WellboreTrajectoryRepresentation(cPtr, owner);
    }
	else
	{
		throw new System.ArgumentException(string.Format("Encountered type '{0}' that is not known to be a Resqml concrete class", type.ToString()));
	}
	
	return ret;
  }
  
  public static f2i.energisticsStandardsApi.resqml2_0_1.AbstractObject resqml2_0_1_instantiateConcreteProperty(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.resqml2_0_1_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "CategoricalProperty")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.CategoricalProperty(cPtr, owner);
    }
	else if (type == "CategoricalPropertySeries")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.CategoricalPropertySeries(cPtr, owner);
    }
    else if (type == "CommentProperty")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.CommentProperty(cPtr, owner);
    }
    else if (type == "ContinuousProperty")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.ContinuousProperty(cPtr, owner);
    }
    else if (type == "ContinuousPropertySeries")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.ContinuousPropertySeries(cPtr, owner);
    }
    else if (type == "DiscreteProperty")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.DiscreteProperty(cPtr, owner);
    }
	else if (type == "DiscretePropertySeries")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.DiscretePropertySeries(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.resqml2_0_1.AbstractObject resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.resqml2_0_1_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	if (type == "WellboreFrameRepresentation")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.WellboreFrameRepresentation(cPtr, owner);
    }
    else if (type == "WellboreMarkerFrameRepresentation")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.WellboreMarkerFrameRepresentation(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.resqml2_0_1.AbstractObject resqml2_0_1_instantiateConcreteLocal3dCrs(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    string type = $modulePINVOKE.resqml2_0_1_AbstractObject_getXmlTag(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));
	
    if (type == "LocalDepth3dCrs")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.LocalDepth3dCrs(cPtr, owner);
    }
    else if (type == "LocalTime3dCrs")
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.LocalTime3dCrs(cPtr, owner);
    }
	else
		return null;
  }
  
  public static f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation resqml2_0_1_instantiateConcreteIjkGridRepresentation(global::System.IntPtr cPtr, bool owner)
  {
    if (cPtr == global::System.IntPtr.Zero) {
      return null;
    }
    int type = fesapiPINVOKE.resqml2_0_1_AbstractIjkGridRepresentation_getGeometryKind(new global::System.Runtime.InteropServices.HandleRef(null, cPtr));

    if (type == (int)f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind.EXPLICIT)
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.IjkGridExplicitRepresentation(cPtr, owner);
    }
    else if (type == (int)f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind.PARAMETRIC)
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.IjkGridParametricRepresentation(cPtr, owner);
    }
    else if (type == (int)f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation.geometryKind.LATTICE)
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.IjkGridLatticeRepresentation(cPtr, owner);
    }
    else // TODO : see if it is possible to return the object itself instead of a copy.
    {
        return new f2i.energisticsStandardsApi.resqml2_0_1.AbstractIjkGridRepresentation(cPtr, owner);
    }
  }
%}

namespace resqml2_0_1
{	
	%typemap(csout, excode=SWIGEXCODE) AbstractObject*, AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_1_instantiateConcreteObject(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) WellboreFrameRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_1_instantiateConcreteWellboreFrameRepresentation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractLocal3dCrs*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_1_instantiateConcreteLocal3dCrs(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractIjkGridRepresentation*  {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_1_instantiateConcreteIjkGridRepresentation(cPtr, $owner);$excode
		return ret;
	}
	
	%typemap(csout, excode=SWIGEXCODE) AbstractProperty*, AbstractValuesProperty*   {
		global::System.IntPtr cPtr = $imcall;
		$csclassname ret = ($csclassname) $modulePINVOKE.resqml2_0_1_instantiateConcreteProperty(cPtr, $owner);$excode
		return ret;
	}
}
