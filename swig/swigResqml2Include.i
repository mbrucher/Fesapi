%{
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping

#include "resqml2/ActivityTemplate.h"
#include "resqml2/HdfProxy.h"

%}
typedef long long					LONG64;

#ifdef SWIGJAVA
typedef long long					ULONG64; // We don't want o use BigInteger in java.
#else
typedef unsigned long long	ULONG64;
#endif

typedef long long 				time_t;


//************************
// STD::VECTOR DEFINITIONS
//************************

namespace resqml2 {
	class Activity;
}

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
%include "std_vector.i"
namespace std {
   %template(ActivityVector) vector<resqml2::Activity*>;
}

#ifdef SWIGPYTHON
namespace resqml2
{
	%typemap(out) AbstractObject*, AbstractFeature*, AbstractFeatureInterpretation*,  AbstractHdfProxy*,  AbstractLocal3dCrs*, AbstractProperty*, AbstractValuesProperty*,AbstractRepresentation* {
		// Check potential downcasting
		swig_type_info * const outtype = SWIG_TypeQuery(("resqml2::" + result->getXmlTag() + " *").c_str());
		resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), outtype, 0);
	}
}
#endif
#ifdef SWIGJAVA
	%include "swigResqml2JavaInclude.i"
#endif
#ifdef SWIGCSHARP
	%include "swigResqml2CsInclude.i"
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace resqml2::AbstractObject;
	%nspace resqml2::AbstractFeature;
	%nspace resqml2::AbstractFeatureInterpretation;
	%nspace resqml2::AbstractHdfProxy;
	%nspace resqml2::AbstractLocal3dCrs;
	%nspace resqml2::AbstractProperty;
	%nspace resqml2::AbstractRepresentation;
	%nspace resqml2::AbstractValuesProperty;
	%nspace resqml2::Activity;
	%nspace resqml2::ActivityTemplate;
	%nspace resqml2::EpcExternalPartReference;
	%nspace resqml2::GridConnectionSetRepresentation;
	%nspace resqml2::HdfProxy;
	%nspace resqml2::MdDatum;
	%nspace resqml2::PropertyKind;
	%nspace resqml2::RepresentationSetRepresentation;
	%nspace resqml2::SubRepresentation;
	%nspace resqml2::TimeSeries;
#endif

namespace resqml2
{
	%nodefaultctor; // Disable creation of default constructors
		
	class Activity;
#ifdef SWIGPYTHON
	%rename(Resqml2AbstractObject) AbstractObject;
#endif
	class AbstractObject
	{
	public:
		common::EpcDocument* getEpcDocument() const;
	
		bool isPartial() const;
	
		std::string getUuid() const;
		std::string getTitle() const;
		std::string getEditor() const;
		time_t getCreation() const;
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;
		
		void setMetadata(const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);
		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);
				
		std::string getXmlTag() const;
		
		void addAlias(const std::string & authority, const std::string & title);
		unsigned int getAliasCount() const;
		std::string getAliasAuthorityAtIndex(const unsigned int & index) const;
		std::string getAliasTitleAtIndex(const unsigned int & index) const;
		
		void addOrSetExtraMetadata(const std::string & key, const std::string & value);
		std::string getExtraMetadata(const std::string & key);
		
		unsigned int getExtraMetadataCount() const;
		std::string getExtraMetadataKeyAtIndex(const unsigned int & index) const;
		std::string getExtraMetadataStringValueAtIndex(const unsigned int & index) const;
		
		const std::vector<resqml2::Activity*> & getActivitySet() const;
	};
	
	//************************************
	//************ HDF *******************
	//************************************
	class EpcExternalPartReference : public AbstractObject
	{
	};
	
	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:
		virtual bool isOpened() = 0;
		virtual void close() = 0;
	};
	
	class HdfProxy : public AbstractHdfProxy
	{
	public:
		void setCompressionLevel(const unsigned int & newCompressionLevel);
	};
	
	//************************************
	//************ Activity **************
	//************************************

	class ActivityTemplate : public AbstractObject
	{
	public:
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType);
		bool isAnExistingParameter(const std::string & paramTitle) const;
		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(const unsigned int & index) const;
		const bool & getParameterIsInput(const unsigned int & index) const;
		const bool & getParameterIsInput(const std::string & paramTitle) const;
		const bool & getParameterIsOutput(const unsigned int & index) const;
		const bool & getParameterIsOutput(const std::string & paramTitle) const;
		const LONG64 getParameterMinOccurences(const unsigned int & index) const;
		const LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		const LONG64 getParameterMaxOccurences(const unsigned int & index) const;
		const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;
	};

	class Activity : public AbstractObject
	{
	public:
		void pushBackParameter(const std::string title,
			const std::string & value);
		void pushBackParameter(const std::string title,
			const LONG64 & value);
		void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(const unsigned int & index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(const unsigned int & index) const;
		double getFloatingPointQuantityParameterValue(const unsigned int & index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(const unsigned int & index) const;
		LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(const unsigned int & index) const;
		const std::string & getStringParameterValue(const unsigned int & index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		bool isAResqmlObjectParameter(const unsigned int & index) const;
		AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const;

		void setActivityTemplate(ActivityTemplate* activityTemplate);
		ActivityTemplate* getActivityTemplate() const;
	};
	
	//************************************
	//************ CRS *******************
	//************************************
	
	class AbstractLocal3dCrs : public resqml2::AbstractObject
	{
	public:
		double getOriginOrdinal1() const;
		double getOriginOrdinal2() const;
		double getOriginDepthOrElevation() const;
		double getArealRotation() const;
		bool isDepthOriented() const;
		
		bool isProjectedCrsDefinedWithEpsg() const;
		bool isProjectedCrsUnknown() const;
		const std::string & getProjectedCrsUnknownReason() const;
		unsigned long long getProjectedCrsEpsgCode() const;
		
		bool isVerticalCrsDefinedWithEpsg() const;
		bool isVerticalCrsUnknown() const;
		const std::string & getVerticalCrsUnknownReason() const;
		unsigned long long getVerticalCrsEpsgCode() const;

		gsoap_resqml2_0_1::eml__LengthUom getProjectedCrsUnit() const;
		std::string getProjectedCrsUnitAsString() const;
		gsoap_resqml2_0_1::eml__LengthUom getVerticalCrsUnit() const;
		std::string getVerticalCrsUnitAsString() const;
		gsoap_resqml2_0_1::eml__AxisOrder2d getAxisOrder() const;
	};
	
	class MdDatum : public resqml2::AbstractObject
	{
	public:
		AbstractLocal3dCrs * getLocalCrs() const;
		virtual std::string getLocalCrsUuid() const = 0;


		virtual double getX() const = 0;
		virtual double getXInGlobalCrs() const = 0;
		virtual double getY() const = 0;
		virtual double getYInGlobalCrs() const = 0;
		virtual double getZ() const = 0;
		virtual double getZInGlobalCrs() const = 0;
	};
	
	//************************************
	//************ FEATURE ***************
	//************************************

	class AbstractFeatureInterpretation;
	class AbstractFeature : public AbstractObject
	{
	public:
		unsigned int getInterpretationCount() const;
		AbstractFeatureInterpretation* getInterpretation(const unsigned int & index) const;
	};
	
	//************************************
	//************ INTERPRETATION ********
	//************************************

	class AbstractRepresentation;
	class AbstractFeatureInterpretation : public resqml2::AbstractObject
	{
	public:
		unsigned int						getRepresentationCount() const;
		AbstractFeature*				getInterpretedFeature();
		AbstractRepresentation* 	getRepresentation(const unsigned int & index) const;
		std::string 						getInterpretedFeatureUuid() const;
	};

	//************************************
	//************ REPRESENTATION ********
	//************************************
	
	class AbstractValuesProperty;
	class SubRepresentation;
	class RepresentationSetRepresentation;
	class AbstractRepresentation : public resqml2::AbstractObject
	{
	public:

		enum indexableElement { NODE = 0, EDGE = 1, FACE = 2, VOLUME = 3, PILLAR = 4 };
		
		AbstractFeatureInterpretation* getInterpretation() const;
		std::string getInterpretationUuid() const;
		AbstractLocal3dCrs * getLocalCrs();
		std::string getLocalCrsUuid() const;
		AbstractHdfProxy * getHdfProxy();
		std::string getHdfProxyUuid() const;
		unsigned int getValuesPropertyCount() const;
		AbstractValuesProperty* getValuesProperty(const unsigned int & index) const;
		
		unsigned int getSubRepresentationCount() const;
		class SubRepresentation* getSubRepresentation(const unsigned int & index) const;
		unsigned int getFaultSubRepresentationCount() const;
		SubRepresentation* getFaultSubRepresentation(const unsigned int & index) const;

		virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const = 0;
		ULONG64 getXyzPointCountOfAllPatches() const;
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;
		void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;
		void getXyzPointsOfAllPatches(double * xyzPoints) const;
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;
		virtual unsigned int getPatchCount() const;
		
		AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex);
		void getSeismicLineAbscissaOfPointsOfPatch(const unsigned int & patchIndex, double* values);
		void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, resqml2::AbstractHdfProxy * proxy);
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, resqml2::AbstractHdfProxy * proxy);
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			AbstractRepresentation * seismicSupport);

		void pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet);
	};
	
	class RepresentationSetRepresentation : public resqml2::AbstractRepresentation
	{
	public:
		bool isHomogeneous() const;
		unsigned int 						getRepresentationCount() const;
		AbstractRepresentation*				getRepresentation(const unsigned int & index) const;
	};
	
	class SubRepresentation : public resqml2::AbstractRepresentation
	{
	public:
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & originIndex, 
			const unsigned int & elementCountInSlowestDimension,
			const unsigned int & elementCountInMiddleDimension,
			const unsigned int & elementCountInFastestDimension);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, unsigned int * elementIndices, resqml2::AbstractHdfProxy * proxy);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			unsigned int * elementIndices0, unsigned int * elementIndices1,
			resqml2::AbstractHdfProxy * proxy);
		
		bool areElementIndicesPairwise(const unsigned int & patchIndex) const;
		bool areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;

		LONG64 getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		unsigned int getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		LONG64 getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		ULONG64 getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		
		AbstractRepresentation::indexableElement getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const;
		ULONG64 getElementCountOfPatch(const unsigned int & patchIndex) const;
		void getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, unsigned int * elementIndices) const;
		
		AbstractRepresentation* getSupportingRepresentation() const;
	};
	
	class GridConnectionSetRepresentation : public resqml2::AbstractRepresentation
	{
	public:
		bool isAssociatedToInterpretations() const;
		void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const;
		void getInterpretationIndices(unsigned int * interpretationIndices) const;
		LONG64 getInterpretationIndexNullValue() const;
	
		ULONG64 getCellIndexPairCount() const;
		unsigned int getCellIndexPairCountFromInterpretationIndex(const unsigned int & interpretationIndex) const;
		
		ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const;
		void getGridConnectionSetInformationFromInterpretationIndex(unsigned int * cellIndexPairs, unsigned int * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const;
		bool hasLocalFacePerCell() const;
		void getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;
		bool isBasedOnMultiGrids() const;
		void getGridIndexPairs(unsigned int * gridIndexPairs) const;
		
		void pushBackSupportingGridRepresentation(resqml2_0_1::AbstractGridRepresentation * supportingGridRep);
		
		void setCellIndexPairs(const unsigned int & cellIndexPairCount, ULONG64 * cellIndexPair, const ULONG64 & nullValue, resqml2::AbstractHdfProxy * proxy);
		void setLocalFacePerCellIndexPairs(const unsigned int & cellIndexPairCount, int * localFacePerCellIndexPair, resqml2::AbstractHdfProxy * proxy);
		void setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const ULONG64 & nullValue, resqml2::AbstractHdfProxy * proxy);
		void pushBackInterpretation(AbstractFeatureInterpretation* interp);
		
		std::string getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const;
		AbstractFeatureInterpretation * getInterpretationFromIndex(const unsigned int & interpretationIndex) const;
		unsigned int getInterpretationCount() const;
		
		unsigned int getSupportingGridRepresentationCount() const;
		resqml2_0_1::AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index);
		std::string getSupportingGridRepresentationUuid(unsigned int index) const;
	};

	//************************************
	//************** PROPERTY ************
	//************************************
	
	class PropertyKind : public resqml2::AbstractObject
	{
	public:
		const std::string & getNamingSystem() const;
		
		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;
		std::string getUomAsString() const;
	};
	
	class TimeSeries : public resqml2::AbstractObject
	{
	public:
		void pushBackTimestamp(const time_t & timestamp);
		unsigned int getTimestampIndex(const time_t & timestamp) const;
		unsigned int getTimestampCount() const;
		time_t getTimestamp(const unsigned int & index) const;
	};
	
	class AbstractProperty: public resqml2::AbstractObject
	{
	public:
		std::string getRepresentationUuid() const;
		AbstractRepresentation* getRepresentation();
		
		std::string getHdfProxyUuid() const;
		resqml2::AbstractHdfProxy* getHdfProxy();
		
		std::string getPropertyKindDescription() const;
		std::string getPropertyKindAsString() const;
		std::string getPropertyKindParentAsString() const;
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind() const;
		
		std::string getLocalPropertyKindUuid() const;
		PropertyKind* getLocalPropertyKind() const;
		
		unsigned int getElementCountPerValue() const;
		
		gsoap_resqml2_0_1::resqml2__IndexableElements getAttachmentKind() const;
		
		void setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts);
		void setTimeStep(const unsigned int & timeStep);
		TimeSeries* getTimeSeries() const;
		time_t getTimestamp() const;
	};
	
	class AbstractValuesProperty : public resqml2::AbstractProperty
	{
	public:
		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG = 3, ULONG = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};
		AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;
		
		long getNullValueOfPatch(const unsigned int & patchIndex);
		long getLongValuesOfPatch(const unsigned int & patchIndex, long * values);
		unsigned long getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values);
		int getIntValuesOfPatch(const unsigned int & patchIndex, int * values);
		unsigned int getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values);
		short getShortValuesOfPatch(const unsigned int & patchIndex, short * values);
		unsigned short getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values);
		char getCharValuesOfPatch(const unsigned int & patchIndex, char * values);
		unsigned char getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values);
		
		unsigned int getValuesCountOfPatch (const unsigned int & patchIndex);
		unsigned int getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex);
		unsigned int getDimensionsCountOfPatch(const unsigned int & patchIndex);
		
		void pushBackFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet, const std::string & facetValue);
		unsigned int getFacetCount() const;
		gsoap_resqml2_0_1::resqml2__Facet getFacet(const unsigned int & index) const;
		std::string getFacetValue(const unsigned int & index) const;
		
		void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			const unsigned int& numArrayDimensions, 
			resqml2::AbstractHdfProxy* proxy
		);
		void createLongHdf5Array3dOfValues(
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			resqml2::AbstractHdfProxy * proxy
		);
		void pushBackLongHdf5SlabArray3dOfValues(
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim, 
			resqml2::AbstractHdfProxy* proxy
		);
		void pushBackLongHdf5SlabArrayOfValues(
			long * values, 
			unsigned long long * numValues, 
			unsigned long long * offsetValues, 
			const unsigned int & numArrayDimensions, 
			resqml2::AbstractHdfProxy * proxy
		);
		void getLongValuesOfPatch(
			const unsigned int& patchIndex, 
			long* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension, 
			const unsigned int& numArrayDimensions
		);
		void getLongValuesOf3dPatch(
			const unsigned int& patchIndex, 
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim
		);
		
	};
	
}
