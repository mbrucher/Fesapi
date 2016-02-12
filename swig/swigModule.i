%module fesapi


#ifdef SWIGJAVA
/*
 When using multiple modules or the nspace feature it is common to invoke SWIG with a different -package command line option for each module.
 However, by default the generated code may not compile if generated classes in one package use generated classes in another package.
 The visibility of the getCPtr() and pointer constructor generated from the javabody typemaps needs changing.
 The default visibility is protected but it needs to be public for access from a different package. Just changing 'protected' to 'public' in the typemap achieves this.
 Two macros are available in java.swg to make this easier and using them is the preferred approach over simply copying the typemaps and modifying as this is forward compatible with any changes in the javabody typemap in future versions of SWIG.
 The macros are for the proxy and typewrapper classes and can respectively be used to to make the method and constructor public:
  SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
  SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
*/
// Notice you must not compile the C++ API with an optimisation superior to -O1 with gcc 4.4.7 in order SWIG to work
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
#endif

//************************
// STD STRING
//************************

#ifdef SWIGCSHARP
	%include "csharp/std_string_utf8.i"
#else
	%include "std_string.i"
#endif

//************************
// POD C ARRAYS
//************************
%include "carrays.i"
%array_class(unsigned long long, ULongLongArray);
%array_class(unsigned long, ULongArray);
%array_class(unsigned int, UIntArray);
%array_class(int, IntArray);
%array_class(long long, LongLongArray);
%array_class(long, LongArray);
%array_class(float, FloatArray);
%array_class(double, DoubleArray);
%array_class(short, ShortArray);
%array_class(unsigned short, UShortArray);
%array_class(char, CharArray);
%array_class(unsigned char, UCharArray);
%array_class(bool, BoolArray);

//************************
// EXCEPTIONS
//************************

%include "exception.i"
%exception {
    try {
        $action
    }
    catch (std::invalid_argument & e) {
        SWIG_exception(SWIG_TypeError,const_cast<char*>(e.what()));
    } 
    catch (std::out_of_range& e) {
        SWIG_exception(SWIG_IndexError,const_cast<char*>(e.what()));
    }
    catch (std::logic_error & e) {
        SWIG_exception(SWIG_SyntaxError,const_cast<char*>(e.what()));
    } 
    catch(...) {
        SWIG_exception(SWIG_RuntimeError,"Unknown exception at F2I C++ API level");
    }
}

%include "swigResqml2_0_1Include.i"
%include "swigWitsml1_4_1_1Include.i"

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace common::EpcDocument;
#endif

namespace common
{
	class EpcDocument
	{
	public:
		EpcDocument(const std::string & fileName, bool overwriteH5File = false);
		EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory, bool overwriteH5File = false);
		
		void setFilePath(const std::string & filePath);

		void serialize();
		std::string deserialize();
		void close();
		std::string getStorageDirectory() const;
		std::string getName() const;
		
		resqml2_0_1::PropertyKindMapper* getPropertyKindMapper() const;
		
		std::string getEnergisticsPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind) const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;
		std::string getEnergisticsUnitOfMeasureName(const gsoap_resqml2_0_1::resqml2__ResqmlUom & energisticsUom) const;
		gsoap_resqml2_0_1::resqml2__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;
		std::string getFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet) const;
		gsoap_resqml2_0_1::resqml2__Facet getFacet(const std::string & facet) const;
		std::string getWitsmlLengthUom(const gsoap_witsml1_4_1_1::witsml1__LengthUom & witsmlUom) const;
		std::string getWitsmlWellVerticalCoordinateUom(const gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom & witsmlUom) const;
		std::string getWitsmlMeasuredDepthUom(const gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom & witsmlUom) const;

		std::string getWitsmlPlaneAngleUom(const gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom & witsmlUom) const;
		
		const std::vector<resqml2_0_1::LocalDepth3dCrs*> & getLocalDepth3dCrsSet() const;
		const std::vector<resqml2_0_1::LocalTime3dCrs*> & getLocalTime3dCrsSet() const;
		
		const std::vector<resqml2_0_1::StratigraphicColumn*> & getStratigraphicColumnSet() const;
		
		const std::vector<resqml2_0_1::Fault*> & getFaultSet() const;
		const std::vector<resqml2_0_1::Fracture*> & getFractureSet() const {return fractureSet;}
		const std::vector<resqml2_0_1::FrontierFeature*> & getFrontierSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFaultPolylineSetRepSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFracturePolylineSetRepSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFrontierPolylineSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFaultTriangulatedSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFractureTriangulatedSetRepSet() const;
		
		const std::vector<resqml2_0_1::Horizon*> & getHorizonSet() const;
		std::vector<resqml2_0_1::Grid2dSetRepresentation*> getHorizonGrid2dSetRepSet() const;
		std::vector<resqml2_0_1::Grid2dRepresentation*> getHorizonGrid2dRepSet() const;
		std::vector<resqml2_0_1::PolylineRepresentation*> getHorizonPolylineRepSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getHorizonPolylineSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getHorizonTriangulatedSetRepSet() const;
		const std::vector<resqml2_0_1::TriangulatedSetRepresentation*> & getAllTriangulatedSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;
		
		std::vector<resqml2_0_1::SeismicLineFeature*> getSeismicLineSet() const;
		
		std::vector<resqml2_0_1::WellboreFeature*> getWellboreSet() const;
		std::vector<resqml2_0_1::WellboreTrajectoryRepresentation*> getWellboreCubicParamLineTrajRepSet() const;
		
		unsigned int getRepresentationSetRepresentationCount() const;
		resqml2_0_1::RepresentationSetRepresentation* getRepresentationSetRepresentation(const unsigned int & index) const;
		
		unsigned int getHdfProxyCount() const;
		resqml2_0_1::AbstractHdfProxy* getHdfProxy(const unsigned int & index) const;
		
		unsigned int getIjkGridRepresentationCount() const;
		resqml2_0_1::AbstractIjkGridRepresentation* getIjkGridRepresentation(const unsigned int & i) const;
		std::vector<resqml2_0_1::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;
		std::vector<resqml2_0_1::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		std::vector<resqml2_0_1::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;
		std::vector<resqml2_0_1::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;
		
		std::vector<resqml2_0_1::UnstructuredGridRepresentation*> getUnstructuredGridRepresentationSet() const;
		
		void setExtendedCoreProperty(const std::string & key, const std::string & value);
		std::string getExtendedCoreProperty(const std::string & key);

		resqml2_0_1::AbstractObject* getResqmlAbstractObjectByUuid(const std::string & uuid) const;
		witsml1_4_1_1::AbstractObject* getWitsmlAbstractObjectByUuid(const std::string & uuid) const;

		//************************************
		//************ HDF *******************
		//************************************

		resqml2_0_1::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		//************************************
		//************ CRS *******************
		//************************************

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
	
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
			
		resqml2_0_1::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			resqml2_0_1::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************************************
		//************ FEATURE ***************
		//************************************

		resqml2_0_1::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::Horizon* createHorizon(const std::string & guid, const std::string & title);

		resqml2_0_1::TectonicBoundaryFeature* createTectonicBoundaryFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::Fault* createFault(const std::string & guid, const std::string & title);
		
		resqml2_0_1::Fracture* createFracture(const std::string & guid, const std::string & title);
		
		resqml2_0_1::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);
		
		resqml2_0_1::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount);

		resqml2_0_1::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount);
			
		resqml2_0_1::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		resqml2_0_1::FrontierFeature* createFrontier(const std::string & guid, const std::string & title);
			
		resqml2_0_1::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);
		
		resqml2_0_1::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);
		
		resqml2_0_1::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

        resqml2_0_1::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);
		
		resqml2_0_1::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact);
		
		//************************************
		//************ INTERPRETATION ********
		//************************************

		resqml2_0_1::GenericFeatureInterpretation* createGenericFeatureInterpretation(resqml2_0_1::AbstractFeature * feature, const std::string & guid, const std::string & title);
		
		resqml2_0_1::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(resqml2_0_1::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		resqml2_0_1::HorizonInterpretation* createHorizonInterpretation(resqml2_0_1::Horizon * horizon, const std::string & guid, const std::string & title);

		resqml2_0_1::FaultInterpretation* createFaultInterpretation(resqml2_0_1::Fault * fault, const std::string & guid, const std::string & title);
		
		resqml2_0_1::WellboreInterpretation* createWellboreInterpretation(resqml2_0_1::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);
		
		resqml2_0_1::EarthModelInterpretation* createEarthModelInterpretation(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);	
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);		
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		resqml2_0_1::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(resqml2_0_1::StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		resqml2_0_1::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		resqml2_0_1::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		//************************************
		//************ REPRESENTATION ********
		//************************************

		resqml2_0_1::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);
		
		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);
			
		resqml2_0_1::PointSetRepresentation* createPointSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,	const std::string & guid, const std::string & title);

		resqml2_0_1::PlaneSetRepresentation* createPlaneSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);
		
		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, bool isClosed = false);
		
		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, bool isClosed = false);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind, bool isClosed = false);

		resqml2_0_1::Grid2dRepresentation* createGrid2dRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		resqml2_0_1::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::MdDatum * mdInfo);

		resqml2_0_1::WellboreFrameRepresentation* createWellboreFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

		resqml2_0_1::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);
			
		resqml2_0_1::RepresentationSetRepresentation* createRepresentationSetRepresentation(
                resqml2_0_1::AbstractOrganizationInterpretation* interp,
                const std::string & guid,
				const std::string & title);

		resqml2_0_1::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

		resqml2_0_1::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
		        resqml2_0_1::StructuralOrganizationInterpretation* interp,
		        const std::string & guid,
		        const std::string & title);
				
		resqml2_0_1::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string & guid, const std::string & title);
    	        
		resqml2_0_1::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);
			
		resqml2_0_1::UnstructuredGridRepresentation* createPartialUnstructuredGridRepresentation(const std::string & guid, const std::string & title);

		resqml2_0_1::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		resqml2_0_1::SubRepresentation* createPartialSubRepresentation(const std::string & guid, const std::string & title);
			
		resqml2_0_1::SubRepresentation* createSubRepresentation(
                const std::string & guid, const std::string & title,
				resqml2_0_1::AbstractRepresentation * supportingRep);
			
		resqml2_0_1::SubRepresentation* createSubRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			resqml2_0_1::AbstractRepresentation * supportingRep);
		
		resqml2_0_1::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, const std::string & guid, const std::string & title,
			resqml2_0_1::AbstractGridRepresentation * supportingGridRep);

		//************************************
		//************* PROPERTIES ***********
		//************************************

		resqml2_0_1::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		resqml2_0_1::TimeSeries* createPartialTimeSeries(const std::string & guid, const std::string & title);
		
		resqml2_0_1::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);
		
		resqml2_0_1::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		resqml2_0_1::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2_0_1::PropertyKind * parentPropType);

		resqml2_0_1::PropertyKind* createPartialPropertyKind(const std::string & guid, const std::string & title);

		resqml2_0_1::CommentProperty* createCommentProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::CommentProperty* createCommentProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2_0_1::PropertyKind * localPropType);
	
		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2_0_1::PropertyKind * localPropType);

		resqml2_0_1::ContinuousPropertySeries* createContinuousPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::ContinuousPropertySeries* createContinuousPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2_0_1::PropertyKind * localPropType,
			resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);
	
		resqml2_0_1::DiscreteProperty* createDiscreteProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::DiscreteProperty* createDiscreteProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2_0_1::PropertyKind * localPropType);
	
		resqml2_0_1::DiscretePropertySeries* createDiscretePropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::DiscretePropertySeries* createDiscretePropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2_0_1::PropertyKind * localPropType,
			resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::CategoricalProperty* createCategoricalProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);
	
		resqml2_0_1::CategoricalProperty* createCategoricalProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, resqml2_0_1::PropertyKind * localPropType);

		resqml2_0_1::CategoricalPropertySeries* createCategoricalPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::CategoricalPropertySeries* createCategoricalPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, resqml2_0_1::PropertyKind * localPropType,
			resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		//************************************
		//************* ACTIVITIES ***********
		//************************************

		resqml2_0_1::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);
		
		resqml2_0_1::Activity* createActivity(resqml2_0_1::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);
			

		//************************************
		//************ WITSML ****************
		//************************************
		
		std::vector<witsml1_4_1_1::Trajectory*> getWitsmlTrajectorySet() const;
		
		witsml1_4_1_1::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone);

		witsml1_4_1_1::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone,
			const std::string & operator_,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWell,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWell,
			gsoap_witsml1_4_1_1::witsml1__WellFluid fluidWell,
			gsoap_witsml1_4_1_1::witsml1__WellDirection directionWell,
			const time_t & dTimSpud,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		witsml1_4_1_1::CoordinateReferenceSystem* createCoordinateReferenceSystem(
			const std::string & guid,
			const std::string & title,
			const std::string & namingSystem,
			const std::string & code,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);
	};
}
