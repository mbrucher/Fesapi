/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2016)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "EpcDocument.h"

#include <sstream>
#include <stdexcept>

#include "epc/Relationship.h"
#include "epc/FilePart.h"

#include "resqml2_0_1/PropertyKindMapper.h"

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/FluidBoundaryFeature.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include "resqml2_0_1/FrontierFeature.h"
#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/PolylineSetRepresentation.h"
#include "resqml2_0_1/PointSetRepresentation.h"
#include "resqml2_0_1/PlaneSetRepresentation.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/Grid2dSetRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/MdDatum.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/TimeSeries.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/CategoricalProperty.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/CommentProperty.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "resqml2_0_1/SeismicLineFeature.h"
#include "resqml2_0_1/SeismicLineSetFeature.h"
#include "resqml2_0_1/OrganizationFeature.h"

#include "resqml2_0_1/BlockedWellboreRepresentation.h"

#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/NonSealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/SealedVolumeFrameworkRepresentation.h"

#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2_0_1/IjkGridNoGeometryRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"

#include "resqml2_0_1/Activity.h"
#include "resqml2_0_1/ActivityTemplate.h"
#include "resqml2_0_1/ContinuousPropertySeries.h"
#include "resqml2_0_1/CategoricalPropertySeries.h"
#include "resqml2_0_1/DiscretePropertySeries.h"

#include "witsml1_4_1_1/CoordinateReferenceSystem.h"
#include "witsml1_4_1_1/Well.h"

using namespace std;
using namespace epc;
using namespace gsoap_resqml2_0_1;
using namespace common;
using namespace resqml2_0_1;
using namespace witsml1_4_1_1;

const char* EpcDocument::DOCUMENT_EXTENSION = ".epc";

#define GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className)\
	gsoap_resqml2_0_1::_resqml2__##className* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORE##className(s, 1);\
	soap_read_resqml2__obj_USCORE##className(s, read);


#define GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className)\
	GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className)\
	wrapper = new className(read);

#define CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className)\
	(resqmlContentType.compare(className::XML_TAG) == 0)\
	{\
		GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className);\
	}

// Create a fesapi partial wrappe based on a content type
#define CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(className)\
	(resqmlContentType.compare(className::XML_TAG) == 0)\
	{\
		return createPartial<className>(dor->UUID, dor->Title);\
	}


namespace // anonymous namespace. Use only in that file.
{
	resqml2::AbstractHdfProxy* default_builder(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
	{
	  return new resqml2_0_1::HdfProxy(soapContext, guid, title, packageDirAbsolutePath, externalFilePath);
	}

	resqml2::AbstractHdfProxy* default_builder(gsoap_resqml2_0_1::_eml__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
	{
		return new resqml2::HdfProxy(fromGsoap, packageDirAbsolutePath, externalFilePath);
	}

#ifdef WITH_RESQML2_1
	resqml2::AbstractHdfProxy* default_builder(gsoap_resqml2_1::_eml__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
	{
		return new resqml2::HdfProxy(fromGsoap, packageDirAbsolutePath, externalFilePath);
	}
#endif
}

EpcDocument::EpcDocument(const string & fileName, const openingMode & hdf5PermissionAccess) :
	package(nullptr), s(nullptr), propertyKindMapper(nullptr), make_hdf_proxy(&default_builder), make_hdf_proxy_from_gsoap_proxy_2_0_1(&default_builder)
#ifdef WITH_RESQML2_1
	, make_hdf_proxy_from_gsoap_proxy_2_1(&default_builder)
#endif
{
	open(fileName, hdf5PermissionAccess);
}

EpcDocument::EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory, const openingMode & hdf5PermissionAccess) :
	package(nullptr), s(nullptr), make_hdf_proxy(&default_builder), make_hdf_proxy_from_gsoap_proxy_2_0_1(&default_builder)
#ifdef WITH_RESQML2_1
	, make_hdf_proxy_from_gsoap_proxy_2_1(&default_builder)
#endif
{
	open(fileName, hdf5PermissionAccess);

	// Load property kind mapping files
	propertyKindMapper = new PropertyKindMapper(this);
	string error = propertyKindMapper->loadMappingFilesFromDirectory(propertyKindMappingFilesDirectory);
	if (error.size() != 0)
	{
		throw invalid_argument("Could not import property kind mappers : " + error);
		delete propertyKindMapper;
		propertyKindMapper = nullptr;
	}
}

const EpcDocument::openingMode & EpcDocument::getHdf5PermissionAccess() const
{
	return hdf5PermissionAccess;
}

soap* EpcDocument::getGsoapContext() const { return s; }

PropertyKindMapper* EpcDocument::getPropertyKindMapper() const { return propertyKindMapper; }

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
const std::unordered_map< std::string, resqml2::AbstractObject* > & EpcDocument::getResqmlAbstractObjectSet() const { return resqmlAbstractObjectSet; }
#else
const std::tr1::unordered_map< std::string, resqml2::AbstractObject* > & EpcDocument::getResqmlAbstractObjectSet() const { return resqmlAbstractObjectSet; }
#endif

const std::vector<resqml2_0_1::LocalDepth3dCrs*> & EpcDocument::getLocalDepth3dCrsSet() const { return localDepth3dCrsSet; }

const std::vector<resqml2_0_1::LocalTime3dCrs*> & EpcDocument::getLocalTime3dCrsSet() const { return localTime3dCrsSet; }

const std::vector<resqml2_0_1::StratigraphicColumn*> & EpcDocument::getStratigraphicColumnSet() const { return stratigraphicColumnSet; }

const std::vector<resqml2_0_1::Horizon*> & EpcDocument::getHorizonSet() const { return horizonSet; }

const std::vector<resqml2_0_1::TectonicBoundaryFeature*> & EpcDocument::getFaultSet() const { return faultSet; }

const std::vector<resqml2_0_1::TectonicBoundaryFeature*> & EpcDocument::getFractureSet() const { return fractureSet; }

const std::vector<resqml2_0_1::TriangulatedSetRepresentation*> & EpcDocument::getAllTriangulatedSetRepSet() const { return triangulatedSetRepresentationSet; }

const std::vector<resqml2_0_1::SeismicLineFeature*> & EpcDocument::getSeismicLineSet() const { return seismicLineSet; }

const std::vector<resqml2_0_1::WellboreFeature*> & EpcDocument::getWellboreSet() const { return wellboreSet; }

std::vector<resqml2_0_1::PolylineRepresentation*> EpcDocument::getPolylineRepresentationSet() const { return polylineRepresentationSet; }

const std::vector<resqml2_0_1::AbstractIjkGridRepresentation*> & EpcDocument::getIjkGridRepresentationSet() const { return ijkGridRepresentationSet; }
unsigned int EpcDocument::getIjkGridRepresentationCount() const { return ijkGridRepresentationSet.size(); }
resqml2_0_1::AbstractIjkGridRepresentation* EpcDocument::getIjkGridRepresentation(const unsigned int & i) const
{
	if (i >= getIjkGridRepresentationCount()) {
		throw out_of_range("The ijk grid index is out of range.");
	}

	return ijkGridRepresentationSet[i];
}

const std::vector<resqml2_0_1::UnstructuredGridRepresentation*> & EpcDocument::getUnstructuredGridRepresentationSet() const { return unstructuredGridRepresentationSet; }

const std::vector<resqml2_0_1::FrontierFeature*> & EpcDocument::getFrontierSet() const { return frontierSet; }

const std::vector<resqml2_0_1::OrganizationFeature*> & EpcDocument::getOrganizationSet() const { return organizationSet; }

const std::vector<resqml2::TimeSeries*> & EpcDocument::getTimeSeriesSet() const { return timeSeriesSet; }

const std::vector<resqml2::SubRepresentation*> & EpcDocument::getSubRepresentationSet() const { return subRepresentationSet; }
unsigned int EpcDocument::getSubRepresentationCount() const { return subRepresentationSet.size(); }
resqml2::SubRepresentation* EpcDocument::getSubRepresentation(const unsigned int & index) const
{
	if (index >= getSubRepresentationCount()) {
		throw out_of_range("The subrepresentation index is out of range.");
	}

	return subRepresentationSet[index];
}

const std::vector<resqml2_0_1::PointSetRepresentation*> & EpcDocument::getPointSetRepresentationSet() const { return pointSetRepresentationSet; }
unsigned int EpcDocument::getPointSetRepresentationCount() const { return pointSetRepresentationSet.size(); }
resqml2_0_1::PointSetRepresentation* EpcDocument::getPointSetRepresentation(const unsigned int & index) const
{
	if (index >= getPointSetRepresentationCount()) {
		throw out_of_range("The point set representation index is out of range.");
	}

	return pointSetRepresentationSet[index];
}

const std::vector<resqml2::AbstractHdfProxy*> & EpcDocument::getHdfProxySet() const { return hdfProxySet; }
unsigned int EpcDocument::getHdfProxyCount() const { return hdfProxySet.size(); }

std::vector<witsml1_4_1_1::Trajectory*> EpcDocument::getWitsmlTrajectorySet() const { return witsmlTrajectorySet; }

void EpcDocument::addWarning(const std::string & warning) { warnings.push_back(warning); }
const std::vector<std::string> & EpcDocument::getWarnings() const { return warnings; }

void  EpcDocument::open(const std::string & fileName, const openingMode & hdf5PermissionAccess)
{
	if (s != nullptr || package != nullptr) {
		throw invalid_argument("The epc document must be closed before to be opened again.");
	}

	this->hdf5PermissionAccess = hdf5PermissionAccess;
	setFilePath(fileName);

	s = soap_new2(SOAP_XML_STRICT | SOAP_C_UTFSTRING, SOAP_XML_TREE | SOAP_XML_INDENT | SOAP_XML_CANONICAL | SOAP_C_UTFSTRING); // new context with option

	package = new Package();
}

void EpcDocument::close()
{
	if (propertyKindMapper != nullptr) {
		delete propertyKindMapper;
		propertyKindMapper = nullptr;
	}

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	for (std::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.begin(); it != resqmlAbstractObjectSet.end(); ++it)
#else
	for (std::tr1::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.begin(); it != resqmlAbstractObjectSet.end(); ++it)
#endif
	{
	  delete it->second;
	}
	resqmlAbstractObjectSet.clear();

#if (defined(_WIN32) && _MSC_VER >= 1600)|| defined(__APPLE__)
	for (std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.begin(); it != witsmlAbstractObjectSet.end(); ++it)
#else
	for (std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.begin(); it != witsmlAbstractObjectSet.end(); ++it)
#endif
	{
	  delete it->second;
	}
	witsmlAbstractObjectSet.clear();

	if (package != nullptr) {
		delete package;
		package = nullptr;
	}

	if (s != nullptr) {
		soap_destroy(s); // remove deserialized C++ objects
		soap_end(s); // remove deserialized data
		soap_done(s); // finalize last use of the context
		soap_free(s); // Free the context
		s = nullptr;
	}

	filePath = "";
	localDepth3dCrsSet.clear();
	localTime3dCrsSet.clear();
	faultSet.clear();
	fractureSet.clear();
	horizonSet.clear();
	seismicLineSet.clear();
	hdfProxySet.clear();
	wellboreSet.clear();
	representationSetRepresentationSet.clear();
	witsmlTrajectorySet.clear();
	triangulatedSetRepresentationSet.clear();
	polylineRepresentationSet.clear();
	ijkGridRepresentationSet.clear();
	unstructuredGridRepresentationSet.clear();
	stratigraphicColumnSet.clear();
	frontierSet.clear();
}

void EpcDocument::setFilePath(const std::string & filePath)
{
	this->filePath = filePath;

	// Add .epc extension if it is not already done in parameter
	size_t dotPos = this->filePath.find_last_of('.');
	if (dotPos != string::npos) {
		if (this->filePath.substr(dotPos) != DOCUMENT_EXTENSION) {
			this->filePath += DOCUMENT_EXTENSION;
		}
	}
	else {
		this->filePath += DOCUMENT_EXTENSION;
	}
}

std::string EpcDocument::getEnergisticsPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind) const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlPropertyKind2s(s, energisticsPropertyKind);
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind EpcDocument::getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const
{
	gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind result;
	if (soap_s2resqml2__ResqmlPropertyKind(s, energisticsPropertyKindName.c_str(), &result) == SOAP_OK)
		return result;
	else
		return resqml2__ResqmlPropertyKind__RESQML_x0020root_x0020property;
}

std::string EpcDocument::getEnergisticsUnitOfMeasureName(const gsoap_resqml2_0_1::resqml2__ResqmlUom & energisticsUom) const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlUom2s(s, energisticsUom);
}

gsoap_resqml2_0_1::resqml2__ResqmlUom EpcDocument::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const
{
	gsoap_resqml2_0_1::resqml2__ResqmlUom result;
	if (soap_s2resqml2__ResqmlUom(s, energisticsUomName.c_str(), &result) == SOAP_OK)
		return result;
	else
		return resqml2__ResqmlUom__Euc;
}

std::string EpcDocument::getFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet) const
{
	return gsoap_resqml2_0_1::soap_resqml2__Facet2s(s, facet);
}

gsoap_resqml2_0_1::resqml2__Facet EpcDocument::getFacet(const std::string & facet) const
{
	gsoap_resqml2_0_1::resqml2__Facet result;
	if (soap_s2resqml2__Facet(s, facet.c_str(), &result) == SOAP_OK)
		return result;
	else
		return resqml2__Facet__what;
}

std::string EpcDocument::getWitsmlLengthUom(const gsoap_witsml1_4_1_1::witsml1__LengthUom & witsmlUom) const
{
	return gsoap_witsml1_4_1_1::soap_witsml1__LengthUom2s(s, witsmlUom);
}

std::string EpcDocument::getWitsmlWellVerticalCoordinateUom(const gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom & witsmlUom) const
{
	return gsoap_witsml1_4_1_1::soap_witsml1__WellVerticalCoordinateUom2s(s, witsmlUom);
}

std::string EpcDocument::getWitsmlMeasuredDepthUom(const gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom & witsmlUom) const
{
	return gsoap_witsml1_4_1_1::soap_witsml1__MeasuredDepthUom2s(s, witsmlUom);
}

std::string EpcDocument::getWitsmlPlaneAngleUom(const gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom & witsmlUom) const
{
	return gsoap_witsml1_4_1_1::soap_witsml1__PlaneAngleUom2s(s, witsmlUom);
}

void EpcDocument::addGsoapProxy(resqml2::AbstractObject* proxy)
{
	string xmlTag = proxy->getXmlTag();
	if (xmlTag.compare(TectonicBoundaryFeature::XML_TAG) == 0) {
		if (!static_cast<const TectonicBoundaryFeature* const>(proxy)->isAFracture()) {
			faultSet.push_back(static_cast<TectonicBoundaryFeature* const>(proxy));
		}
		else {
			fractureSet.push_back(static_cast<TectonicBoundaryFeature* const>(proxy));
		}
	}
	else if (xmlTag.compare(GeneticBoundaryFeature::XML_TAG) == 0) {
		if (static_cast<const GeneticBoundaryFeature* const>(proxy)->isAnHorizon()) {
			horizonSet.push_back(static_cast<Horizon* const>(proxy));
		}
	}
	else if (xmlTag.compare(SeismicLineFeature::XML_TAG) == 0) {
		seismicLineSet.push_back(static_cast<SeismicLineFeature* const>(proxy));
	}
	else if (xmlTag.compare(resqml2::EpcExternalPartReference::XML_TAG) == 0) {
		hdfProxySet.push_back(static_cast<resqml2::AbstractHdfProxy* const>(proxy));
	}
	else if (xmlTag.compare(WellboreFeature::XML_TAG) == 0) {
		wellboreSet.push_back(static_cast<WellboreFeature* const>(proxy));
	}
	else if (xmlTag.compare(PolylineRepresentation::XML_TAG) == 0) {
		polylineRepresentationSet.push_back(static_cast<PolylineRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(AbstractIjkGridRepresentation::XML_TAG) == 0 || xmlTag.compare(AbstractIjkGridRepresentation::XML_TAG_TRUNCATED) == 0) {
		ijkGridRepresentationSet.push_back(static_cast<AbstractIjkGridRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(UnstructuredGridRepresentation::XML_TAG) == 0) {
		unstructuredGridRepresentationSet.push_back(static_cast<UnstructuredGridRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(LocalDepth3dCrs::XML_TAG) == 0) {
		localDepth3dCrsSet.push_back(static_cast<LocalDepth3dCrs* const>(proxy));
	}
	else if (xmlTag.compare(LocalTime3dCrs::XML_TAG) == 0) {
		localTime3dCrsSet.push_back(static_cast<LocalTime3dCrs* const>(proxy));
	}
	else if (xmlTag.compare(StratigraphicColumn::XML_TAG) == 0) {
		stratigraphicColumnSet.push_back(static_cast<StratigraphicColumn* const>(proxy));
	}
	else if (xmlTag.compare(TriangulatedSetRepresentation::XML_TAG) == 0) {
		triangulatedSetRepresentationSet.push_back(static_cast<TriangulatedSetRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(FrontierFeature::XML_TAG) == 0) {
		frontierSet.push_back(static_cast<FrontierFeature* const>(proxy));
	}
	else if (xmlTag.compare(OrganizationFeature::XML_TAG) == 0) {
		organizationSet.push_back(static_cast<OrganizationFeature* const>(proxy));
	}
	else if (xmlTag.compare(RepresentationSetRepresentation::XML_TAG) == 0) {
		representationSetRepresentationSet.push_back(static_cast<RepresentationSetRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(NonSealedSurfaceFrameworkRepresentation::XML_TAG) == 0) {
		representationSetRepresentationSet.push_back(static_cast<NonSealedSurfaceFrameworkRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(SealedSurfaceFrameworkRepresentation::XML_TAG) == 0) {
		representationSetRepresentationSet.push_back(static_cast<SealedSurfaceFrameworkRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(SealedVolumeFrameworkRepresentation::XML_TAG) == 0) {
		representationSetRepresentationSet.push_back(static_cast<SealedVolumeFrameworkRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(TimeSeries::XML_TAG) == 0) {
		timeSeriesSet.push_back(static_cast<TimeSeries*>(proxy));
	}
	else if (xmlTag.compare(SubRepresentation::XML_TAG) == 0) {
		subRepresentationSet.push_back(static_cast<SubRepresentation* const>(proxy));
	}
	else if (xmlTag.compare(PointSetRepresentation::XML_TAG) == 0) {
		pointSetRepresentationSet.push_back(static_cast<PointSetRepresentation* const>(proxy));
	}

	if (getResqmlAbstractObjectByUuid(proxy->getUuid()) == nullptr) {
		resqmlAbstractObjectSet[proxy->getUuid()] = proxy;
	}
	else {
		throw invalid_argument("You cannot have twice the same UUID " + proxy->getUuid() + " for two different Resqml objects in an EPC document");
	}
	proxy->epcDocument = this;
}

void EpcDocument::addFesapiWrapperAndDeleteItIfException(resqml2::AbstractObject* proxy)
{
	try {
		addGsoapProxy(proxy);
	}
	catch (const exception & e)
	{
		std::cerr << e.what() << endl;
		std::cerr << "The proxy is going to be deleted but deletion is not yet guaranteed. You should close your application." << endl;
		addWarning("The proxy is going to be deleted but deletion is not yet guaranteed. You should close your application.");
		delete proxy;
		throw;
	}
}

void EpcDocument::addGsoapProxy(witsml1_4_1_1::AbstractObject* proxy)
{
	switch (proxy->getGsoapType())
	{
	case SOAP_TYPE_gsoap_witsml1_4_1_1_witsml1__obj_USCOREtrajectorys :
		witsmlTrajectorySet.push_back(static_cast<Trajectory*>(proxy)); break;
	}

	if (witsmlAbstractObjectSet.find(proxy->getUuid()) == witsmlAbstractObjectSet.end())
	{
		witsmlAbstractObjectSet[proxy->getUuid()] = proxy;
	}
	else
	{
		throw invalid_argument("You cannot have twice the same UUID " + proxy->getUuid() + " for two different Resqml objects in an EPC document");
	}
	proxy->epcDocument = this;
}

void EpcDocument::addFesapiWrapperAndDeleteItIfException(witsml1_4_1_1::AbstractObject* proxy)
{
	try {
		addGsoapProxy(proxy);
	}
	catch (const exception & e)
	{
		std::cerr << e.what() << endl;
		std::cerr << "The proxy is going to be deleted but deletion is not yet guaranteed. You should close your application." << endl;
		addWarning("The proxy is going to be deleted but deletion is not yet guaranteed. You should close your application.");
		delete proxy;
		throw;
	}
}

void EpcDocument::serialize(bool useZip64)
{
	warnings.clear();

	package->openForWriting(filePath, useZip64);
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	for (std::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.begin(); it != resqmlAbstractObjectSet.end(); ++it)
#else
	for (std::tr1::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.begin(); it != resqmlAbstractObjectSet.end(); ++it)
#endif
	{
		if (it->second->isPartial() == false)
		{
			string str = it->second->serializeIntoString();

			epc::FilePart* fp = package->createPart(str, it->second->getPartNameInEpcDocument());
			std::vector<epc::Relationship> relSet = it->second->getAllEpcRelationships();
			for (size_t relIndex = 0; relIndex < relSet.size(); relIndex++)
				fp->addRelationship(relSet[relIndex]);

			epc::ContentType contentType(false, it->second->getContentType(), it->second->getPartNameInEpcDocument());
			package->addContentType(contentType);
		}
	}

	
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	for (std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.begin(); it != witsmlAbstractObjectSet.end(); ++it)
#else
	for (std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.begin(); it != witsmlAbstractObjectSet.end(); ++it)
#endif
	{
		string str = it->second->serializeIntoString();

		epc::FilePart* fp = package->createPart(str, it->second->getPartNameInEpcDocument());
		std::vector<epc::Relationship> relSet = it->second->getAllEpcRelationships();
		for (size_t relIndex = 0; relIndex < relSet.size(); relIndex++)
			fp->addRelationship(relSet[relIndex]);

		epc::ContentType contentType(false, it->second->getContentType(), it->second->getPartNameInEpcDocument());
		package->addContentType(contentType);
	}

	package->writePackage();
}

string EpcDocument::deserialize()
{
	string result;
	warnings.clear();
	package->openForReading(filePath);

	// Read all Resqml objects
	FileContentType::ContentTypeMap contentTypes = package->getFileContentType().getAllContentType();
	for(FileContentType::ContentTypeMap::const_iterator it=contentTypes.begin(); it != contentTypes.end(); ++it)
	{
		if (it->second.getContentTypeString().find("application/x-resqml+xml;version=2.0;type=") == 0 ||
			it->second.getContentTypeString().find("application/x-resqml+xml;version=2.0.1;type=") == 0)
		{
			const string fileStr = package->extractFile(it->second.getExtensionOrPartName().substr(1));
			if (fileStr.empty()) {
				throw invalid_argument("The EPC document contains the file " + it->second.getExtensionOrPartName().substr(1) + " in its contentType file which cannot be found or cannot be unzipped or is empty.");
			}
			istringstream iss(fileStr);
			setGsoapStream(&iss);
			resqml2::AbstractObject* wrapper = nullptr;
			const size_t lastEqualCharPos = it->second.getContentTypeString().find_last_of('_'); // The XML tag is after "obj_"
			const string resqmlContentType = it->second.getContentTypeString().substr(lastEqualCharPos+1);
			if (resqmlContentType.compare(resqml2::EpcExternalPartReference::XML_TAG) == 0)
			{
				// Look for the relative path of the HDF file
				string relFilePath = "";
				const size_t slashPos = it->second.getExtensionOrPartName().substr(1).find_last_of("/\\");
				if (slashPos != string::npos) {
					relFilePath = it->second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
				}
				relFilePath += "_rels" + it->second.getExtensionOrPartName().substr(it->second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
				FileRelationship relFile;
				relFile.readFromString(package->extractFile(relFilePath));
				const vector<Relationship> allRels = relFile.getAllRelationship();
				string hdfRelativeFilePath;
				for (size_t relIndex = 0; relIndex < allRels.size(); relIndex++) {
					if (allRels[relIndex].getType().compare("http://schemas.energistics.org/package/2012/relationships/externalResource") == 0) {
						hdfRelativeFilePath = allRels[relIndex].getTarget();
						break;
					}
				}

				// Common initialization
				gsoap_resqml2_0_1::_eml__EpcExternalPartReference* read = getEpcExternalPartReferenceGsoapProxyFromGsoapContext();
				wrapper = make_hdf_proxy_from_gsoap_proxy_2_0_1(read, getStorageDirectory(), hdfRelativeFilePath);
			}
			else {
				wrapper = getResqml2_0_1WrapperFromGsoapContext(resqmlContentType);
			}
			
			if (wrapper != nullptr) {
				if (s->error != SOAP_OK) {
					ostringstream oss;
					soap_stream_fault(s, oss);
					result += oss.str() + " IN " + it->second.getExtensionOrPartName() + "\n";
					delete wrapper;
				}
				else {
					addFesapiWrapperAndDeleteItIfException(wrapper);
				}
			}
			else {
				warnings.push_back("The content type " + resqmlContentType + "could not be wrapped by fesapi. The related instance will be ignored.");
			}
		}
		else if (it->second.getContentTypeString().find("application/x-witsml+xml;version=1.4.1.1;type=") == 0)
		{
			string fileStr = package->extractFile(it->second.getExtensionOrPartName().substr(1));
			if (fileStr.empty()) {
				throw invalid_argument("The EPC document contains the file " + it->second.getExtensionOrPartName().substr(1) + " in its contentType file which cannot be found or cannot be unzipped or is empty.");
			}
			istringstream iss(fileStr);
			setGsoapStream(&iss);
			witsml1_4_1_1::AbstractObject* wrapper = nullptr;
			string resqmlContentType = "";
			resqmlContentType = it->second.getContentTypeString().substr(50);
			if (resqmlContentType.compare(Well::XML_TAG) == 0)
			{
				gsoap_witsml1_4_1_1::_witsml1__wells* read = gsoap_witsml1_4_1_1::soap_new_witsml1__obj_USCOREwells(s, 1);
				soap_read_witsml1__obj_USCOREwells(s, read);
				wrapper = new Well(read);
			}
			else if (resqmlContentType.compare(Wellbore::XML_TAG) == 0)
			{
				gsoap_witsml1_4_1_1::_witsml1__wellbores* read = gsoap_witsml1_4_1_1::soap_new_witsml1__obj_USCOREwellbores(s, 1);
				soap_read_witsml1__obj_USCOREwellbores(s, read);
				wrapper = new Wellbore(read);
			}
			else if (resqmlContentType.compare(Trajectory::XML_TAG) == 0)
			{
				gsoap_witsml1_4_1_1::_witsml1__trajectorys* read = gsoap_witsml1_4_1_1::soap_new_witsml1__obj_USCOREtrajectorys(s, 1);
				soap_read_witsml1__obj_USCOREtrajectorys(s, read);
				wrapper = new Trajectory(read);
			}
			else if (resqmlContentType.compare(Log::XML_TAG) == 0)
			{
				gsoap_witsml1_4_1_1::_witsml1__logs* read = gsoap_witsml1_4_1_1::soap_new_witsml1__obj_USCORElogs(s, 1);
				soap_read_witsml1__obj_USCORElogs(s, read);
				wrapper = new Log(read);
			}
			else if (resqmlContentType.compare(FormationMarker::XML_TAG) == 0)
			{
				gsoap_witsml1_4_1_1::_witsml1__formationMarkers* read = gsoap_witsml1_4_1_1::soap_new_witsml1__obj_USCOREformationMarkers(s, 1);
				soap_read_witsml1__obj_USCOREformationMarkers(s, read);
				wrapper = new FormationMarker(read);
			}
			else if (resqmlContentType.compare(CoordinateReferenceSystem::XML_TAG) == 0)
			{
				gsoap_witsml1_4_1_1::_witsml1__coordinateReferenceSystems* read = gsoap_witsml1_4_1_1::soap_new_witsml1__obj_USCOREcoordinateReferenceSystems(s, 1);
				soap_read_witsml1__obj_USCOREcoordinateReferenceSystems(s, read);
				wrapper = new CoordinateReferenceSystem(read);
			}
			
			if (wrapper != nullptr)
			{
				if (s->error != SOAP_OK) {
					ostringstream oss;
					soap_stream_fault(s, oss);
					result += oss.str() + " IN " + it->second.getExtensionOrPartName() + "\n";
					delete wrapper;
				}
				else {
					addFesapiWrapperAndDeleteItIfException(wrapper);
				}
			}
		}
	}

	updateAllRelationships();

	return result;
}

resqml2::AbstractObject* EpcDocument::getResqml2_0_1WrapperFromGsoapContext(const std::string & resqmlContentType)
{
	resqml2::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(MdDatum)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(Activity)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ActivityTemplate)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicLatticeFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicLineFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicLineSetFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(FrontierFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(LocalDepth3dCrs)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(LocalTime3dCrs)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(TectonicBoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GeneticBoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(BoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicUnitFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicColumn)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GenericFeatureInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(BoundaryFeatureInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(FaultInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(HorizonInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicUnitInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicColumnRankInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicOccurrenceInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreFrameRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreMarkerFrameRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreTrajectoryRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PolylineSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PointSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PlaneSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PolylineRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(Grid2dSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(Grid2dRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(TriangulatedSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(BlockedWellboreRepresentation)
	else if (resqmlContentType.compare(AbstractIjkGridRepresentation::XML_TAG) == 0)
	{
		GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(IjkGridRepresentation)

		if (read->Geometry != nullptr) {
			switch (read->Geometry->Points->soap_type()) {
			case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array:
				wrapper = new IjkGridExplicitRepresentation(read); break;
			case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray:
				wrapper = new IjkGridParametricRepresentation(read); break;
			case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray:
				wrapper = new IjkGridLatticeRepresentation(read); break;
			}
		}
		else {
			wrapper = new IjkGridNoGeometryRepresentation(read);
		}
	}
	else if (resqmlContentType.compare(AbstractIjkGridRepresentation::XML_TAG_TRUNCATED) == 0)
	{
		GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(TruncatedIjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array:
					wrapper = new IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray:
					wrapper = new IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray:
					wrapper = new IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new IjkGridNoGeometryRepresentation(read);
			}
	}
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(UnstructuredGridRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PropertyKind)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousPropertySeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CategoricalProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CategoricalPropertySeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscreteProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscretePropertySeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CommentProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StringTableLookup)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(EarthModelInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(OrganizationFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StructuralOrganizationInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(FluidBoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SubRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GridConnectionSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(TimeSeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(RepresentationSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SealedSurfaceFrameworkRepresentation)
	else if (resqmlContentType.compare(resqml2::EpcExternalPartReference::XML_TAG) == 0)
	{
		throw invalid_argument("Please handle this type outside this method since it is not only XML related.");
	}

	return wrapper;
}

resqml2::AbstractObject* EpcDocument::getResqmlAbstractObjectByUuid(const std::string & uuid, int & gsoapType) const
{
	resqml2::AbstractObject* result = getResqmlAbstractObjectByUuid(uuid);
	if (result != nullptr)
	{
		gsoapType = result->getGsoapType();
	}
	return result;
}

resqml2::AbstractObject* EpcDocument::getResqmlAbstractObjectByUuid(const string & uuid) const
{
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	std::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.find(uuid);
#else
	std::tr1::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.find(uuid);
#endif
	return it == resqmlAbstractObjectSet.end() ? nullptr : it->second;
}

witsml1_4_1_1::AbstractObject* EpcDocument::getWitsmlAbstractObjectByUuid(const string & uuid) const
{
	
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.find(uuid);
#else
	std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.find(uuid);
#endif
	return it == witsmlAbstractObjectSet.end() ? nullptr : it->second;
}

vector<PolylineSetRepresentation*> EpcDocument::getFaultPolylineSetRepSet() const
{
	vector<PolylineSetRepresentation*> result;

	vector<TectonicBoundaryFeature*> faultSet = getFaultSet();
	for (size_t featureIndex = 0; featureIndex < faultSet.size(); featureIndex++)
	{
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = faultSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineSetRepresentation)
				{
					result.push_back(static_cast<PolylineSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<PolylineSetRepresentation*> EpcDocument::getFracturePolylineSetRepSet() const
{
	vector<PolylineSetRepresentation*> result;

	vector<TectonicBoundaryFeature*> fractureSet = getFractureSet();
	for (size_t featureIndex = 0; featureIndex < fractureSet.size(); featureIndex++)
	{
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = fractureSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineSetRepresentation)
				{
					result.push_back(static_cast<PolylineSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<PolylineSetRepresentation*> EpcDocument::getFrontierPolylineSetRepSet() const
{
	vector<PolylineSetRepresentation*> result;

	vector<FrontierFeature*> frontierSet = getFrontierSet();
	for (size_t featureIndex = 0; featureIndex < frontierSet.size(); featureIndex++)
	{
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = frontierSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineSetRepresentation)
				{
					result.push_back(static_cast<PolylineSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<TriangulatedSetRepresentation*> EpcDocument::getFaultTriangulatedSetRepSet() const
{
	vector<TriangulatedSetRepresentation*> result;

	vector<TectonicBoundaryFeature*> faultSet = getFaultSet();
	for (size_t featureIndex = 0; featureIndex < faultSet.size(); featureIndex++)
	{
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = faultSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORETriangulatedSetRepresentation)
				{
					result.push_back(static_cast<TriangulatedSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<TriangulatedSetRepresentation*> EpcDocument::getFractureTriangulatedSetRepSet() const
{
	vector<TriangulatedSetRepresentation*> result;

	vector<TectonicBoundaryFeature*> fractureSet = getFractureSet();
	for (size_t featureIndex = 0; featureIndex < fractureSet.size(); featureIndex++)
	{
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = fractureSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORETriangulatedSetRepresentation)
				{
					result.push_back(static_cast<TriangulatedSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<Grid2dSetRepresentation*> EpcDocument::getHorizonGrid2dSetRepSet() const
{
	vector<Grid2dSetRepresentation*> result;

	vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREGrid2dSetRepresentation) {
					result.push_back(static_cast<Grid2dSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<Grid2dRepresentation*> EpcDocument::getHorizonGrid2dRepSet() const
{
	vector<Grid2dRepresentation*> result;

	vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREGrid2dRepresentation) {
					result.push_back(static_cast<Grid2dRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<PolylineRepresentation*> EpcDocument::getHorizonPolylineRepSet() const
{
	vector<PolylineRepresentation*> result;

	vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineRepresentation) {
					result.push_back(static_cast<PolylineRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<PolylineSetRepresentation*> EpcDocument::getHorizonPolylineSetRepSet() const
{
	vector<PolylineSetRepresentation*> result;

	vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineSetRepresentation) {
					result.push_back(static_cast<PolylineSetRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<TriangulatedSetRepresentation*> EpcDocument::getHorizonTriangulatedSetRepSet() const
{
	vector<TriangulatedSetRepresentation*> result;

	vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORETriangulatedSetRepresentation) {
					TriangulatedSetRepresentation* rep = static_cast<TriangulatedSetRepresentation*>(repSet[repIndex]);
					result.push_back(rep);
				}
			}
		}
	}

	return result;
}

std::vector<resqml2_0_1::TriangulatedSetRepresentation*> EpcDocument::getUnclassifiedTriangulatedSetRepSet() const
{
	vector<TriangulatedSetRepresentation*> result;

	for (size_t triRepIndex = 0; triRepIndex < triangulatedSetRepresentationSet.size(); ++triRepIndex) {
		resqml2::AbstractFeatureInterpretation* interp = triangulatedSetRepresentationSet[triRepIndex]->getInterpretation();
		if (interp == nullptr) {
			result.push_back(triangulatedSetRepresentationSet[triRepIndex]);
		}
		else {
			if (!interp->isPartial()) {
				const int soapType = interp->getGsoapType();
				if (soapType != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREFaultInterpretation &&
					soapType != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREHorizonInterpretation) {
					result.push_back(triangulatedSetRepresentationSet[triRepIndex]);
				}
			}
			else {
				const std::string contentType = triangulatedSetRepresentationSet[triRepIndex]->getInterpretationContentType();
				if (contentType.find("Horizon") == string::npos &&
					contentType.find("Fault") == string::npos) {
					result.push_back(triangulatedSetRepresentationSet[triRepIndex]);
				}
			}
		}
	}

	return result;
}

vector<WellboreTrajectoryRepresentation*> EpcDocument::getWellboreCubicParamLineTrajRepSet() const
{
	vector<WellboreTrajectoryRepresentation*> result;

	for (size_t featureIndex = 0; featureIndex < wellboreSet.size(); ++featureIndex) {
		vector<resqml2::AbstractFeatureInterpretation*> interpSet = wellboreSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			vector<resqml2::AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREWellboreTrajectoryRepresentation) {
					result.push_back(static_cast<WellboreTrajectoryRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

const std::vector<resqml2::RepresentationSetRepresentation*> & EpcDocument::getRepresentationSetRepresentationSet() const
{
	return representationSetRepresentationSet;
}

unsigned int EpcDocument::getRepresentationSetRepresentationCount() const
{
	return representationSetRepresentationSet.size();
}

resqml2::RepresentationSetRepresentation* EpcDocument::getRepresentationSetRepresentation(const unsigned int & index) const
{
	if (index >= getRepresentationSetRepresentationCount()) {
		throw range_error("The index of the representation set representaiton is out of range");
	}

	return representationSetRepresentationSet[index];
}

vector<IjkGridParametricRepresentation*> EpcDocument::getIjkGridParametricRepresentationSet() const
{
	vector<AbstractIjkGridRepresentation*> allgrids = getIjkGridRepresentationSet();
	vector<IjkGridParametricRepresentation*> result;
	
	for (size_t i = 0; i < allgrids.size(); ++i) {
		IjkGridParametricRepresentation* ijkGridParamRep = dynamic_cast<IjkGridParametricRepresentation*>(allgrids[i]);
		if (ijkGridParamRep != nullptr) {
			result.push_back(ijkGridParamRep);
		}
	}
	
	return result;
}

vector<IjkGridExplicitRepresentation*> EpcDocument::getIjkGridExplicitRepresentationSet() const
{
	vector<AbstractIjkGridRepresentation*> allgrids = getIjkGridRepresentationSet();
	vector<IjkGridExplicitRepresentation*> result;
	
	for (size_t i = 0; i < allgrids.size(); ++i)
	{
		IjkGridExplicitRepresentation* ijkGridParamRep = dynamic_cast<IjkGridExplicitRepresentation*>(allgrids[i]);
		if (ijkGridParamRep != nullptr) {
			result.push_back(ijkGridParamRep);
		}
	}
	
	return result;
}

std::vector<PolylineRepresentation*> EpcDocument::getSeismicLinePolylineRepSet() const
{
	vector<PolylineRepresentation*> result;
	vector<PolylineRepresentation*> polylineRepSet = getPolylineRepresentationSet();

	for (size_t i = 0; i < polylineRepSet.size(); ++i) {
		if (polylineRepSet[i]->isASeismicLine() || polylineRepSet[i]->isAFaciesLine()) {
			result.push_back(polylineRepSet[i]);
		}
	}

	return result;
}

vector<IjkGridLatticeRepresentation*> EpcDocument::getIjkSeismicCubeGridRepresentationSet() const
{
	vector<AbstractIjkGridRepresentation*> allgrids = getIjkGridRepresentationSet();
	vector<IjkGridLatticeRepresentation*> result;
	
	for (size_t i = 0; i < allgrids.size(); ++i) {
		IjkGridLatticeRepresentation* ijkGridLatticeRep = dynamic_cast<IjkGridLatticeRepresentation*>(allgrids[i]);
		if (ijkGridLatticeRep != nullptr && (ijkGridLatticeRep->isASeismicCube() || ijkGridLatticeRep->isAFaciesCube())) {
			result.push_back(ijkGridLatticeRep);
		}
	}
	
	return result;
}

resqml2::AbstractHdfProxy* EpcDocument::getHdfProxy(const unsigned int & index) const
{
	if (index >= hdfProxySet.size()) {
		throw range_error("The index of the requested hdf proxy is out of range");
	}

	return hdfProxySet[index];
}

string EpcDocument::getStorageDirectory() const
{
	size_t slashPos = filePath.find_last_of("/\\");
	if (slashPos != string::npos) {
		return filePath.substr(0, slashPos + 1);
	}

	return string();
}

string EpcDocument::getName() const
{
	size_t slashPos = filePath.find_last_of("/\\");
	if (slashPos == string::npos) {
		return string();
	}

	// Remove the extension
	string nameSuffixed = filePath.substr(slashPos+1, filePath.size());
	return nameSuffixed.substr(0, nameSuffixed.size() - strlen(DOCUMENT_EXTENSION));
}

void EpcDocument::updateAllRelationships()
{
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	for (std::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.begin(); it != resqmlAbstractObjectSet.end(); ++it)
#else
	for (std::tr1::unordered_map< std::string, resqml2::AbstractObject* >::const_iterator it = resqmlAbstractObjectSet.begin(); it != resqmlAbstractObjectSet.end(); ++it)
#endif
	{
		if (!it->second->isPartial()) {
			it->second->importRelationshipSetFromEpc(this);
		}
	}


#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	for (std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.begin(); it != witsmlAbstractObjectSet.end(); ++it)
#else
	for (std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.begin(); it != witsmlAbstractObjectSet.end(); ++it)
#endif
	{
		it->second->importRelationshipSetFromEpc(this);
	}
}

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
unordered_map< string, string > & EpcDocument::getExtendedCoreProperty()
#else
tr1::unordered_map< string, string > & EpcDocument::getExtendedCoreProperty()
#endif
{
	return package->getExtendedCoreProperty();
}

void EpcDocument::setExtendedCoreProperty(const std::string & key, const std::string & value)
{
	(package->getExtendedCoreProperty())[key] = value;
}

std::string EpcDocument::getExtendedCoreProperty(const std::string & key)
{
	if (package->getExtendedCoreProperty().find(key) != package->getExtendedCoreProperty().end()) {
		return (package->getExtendedCoreProperty())[key];
	}

	return string();
}

resqml2::AbstractObject* EpcDocument::createPartial(gsoap_resqml2_0_1::eml__DataObjectReference* dor)
{
	const size_t lastEqualCharPos = dor->ContentType.find_last_of('_'); // The XML tag is after "obj_"
	const string resqmlContentType = dor->ContentType.substr(lastEqualCharPos + 1);

	if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(MdDatum)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(Activity)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(ActivityTemplate)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(SeismicLatticeFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(SeismicLineFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(SeismicLineSetFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(FrontierFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(LocalDepth3dCrs)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(LocalTime3dCrs)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(TectonicBoundaryFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(GeneticBoundaryFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(BoundaryFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(WellboreFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StratigraphicUnitFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StratigraphicColumn)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(GenericFeatureInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(BoundaryFeatureInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(WellboreInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(FaultInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(HorizonInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StratigraphicUnitInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StratigraphicColumnRankInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StratigraphicOccurrenceInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(WellboreFrameRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(WellboreMarkerFrameRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(WellboreTrajectoryRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(PolylineSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(PointSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(PlaneSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(PolylineRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(Grid2dSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(Grid2dRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(TriangulatedSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(BlockedWellboreRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(AbstractIjkGridRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(UnstructuredGridRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(PropertyKind)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(ContinuousProperty)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(ContinuousPropertySeries)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(CategoricalProperty)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(CategoricalPropertySeries)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(DiscreteProperty)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(DiscretePropertySeries)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(CommentProperty)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StringTableLookup)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(EarthModelInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(OrganizationFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(StructuralOrganizationInterpretation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(FluidBoundaryFeature)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(SubRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(GridConnectionSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(TimeSeries)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(RepresentationSetRepresentation)
	else if CREATE_RESQML_2_0_1_FESAPI_PARTIAL_WRAPPER(SealedSurfaceFrameworkRepresentation)
	else if (dor->ContentType.compare(resqml2::EpcExternalPartReference::XML_TAG) == 0)
	{
		throw invalid_argument("Please handle this type outside this method since it is not only XML related.");
	}
}

//************************************
//************ HDF *******************
//************************************

resqml2::AbstractHdfProxy* EpcDocument::createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
{
	resqml2::AbstractHdfProxy* result = make_hdf_proxy(getGsoapContext(), guid, title, packageDirAbsolutePath, externalFilePath);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

//************************************
//************ CRS *******************
//************************************

LocalDepth3dCrs* EpcDocument::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	LocalDepth3dCrs* result = new LocalDepth3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedEpsgCode,
			verticalUom, verticalEpsgCode, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::LocalDepth3dCrs* EpcDocument::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	LocalDepth3dCrs* result = new LocalDepth3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedUnknownReason,
			verticalUom, verticalUnknownReason, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::LocalDepth3dCrs* EpcDocument::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	LocalDepth3dCrs* result = new LocalDepth3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedEpsgCode,
			verticalUom, verticalUnknownReason, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::LocalDepth3dCrs* EpcDocument::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	LocalDepth3dCrs* result = new LocalDepth3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedUnknownReason,
			verticalUom, verticalEpsgCode, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

LocalTime3dCrs* EpcDocument::createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	LocalTime3dCrs* result = new LocalTime3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedEpsgCode,
			timeUom,
			verticalUom, verticalEpsgCode, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

LocalTime3dCrs* EpcDocument::createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	LocalTime3dCrs* result = new LocalTime3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedUnknownReason,
			timeUom,
			verticalUom, verticalUnknownReason, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

LocalTime3dCrs* EpcDocument::createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	LocalTime3dCrs* result = new LocalTime3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedEpsgCode,
			timeUom,
			verticalUom, verticalUnknownReason, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

LocalTime3dCrs* EpcDocument::createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	LocalTime3dCrs* result = new LocalTime3dCrs(getGsoapContext(), guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
			projectedUom, projectedUnknownReason,
			timeUom,
			verticalUom, verticalEpsgCode, isUpOriented);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::MdDatum* EpcDocument::createMdDatum(const std::string & guid, const std::string & title,
			resqml2::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3)
{
	MdDatum* result = new MdDatum(getGsoapContext(), guid, title, locCrs, originKind, referenceLocationOrdinal1, referenceLocationOrdinal2, referenceLocationOrdinal3);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
//************************************
//************ FEATURE ***************
//************************************

BoundaryFeature* EpcDocument::createBoundaryFeature(const std::string & guid, const std::string & title)
{
	BoundaryFeature* result = new BoundaryFeature(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

Horizon* EpcDocument::createHorizon(const std::string & guid, const std::string & title)
{
	Horizon* result = new Horizon(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

TectonicBoundaryFeature* EpcDocument::createFault(const std::string & guid, const std::string & title)
{
	TectonicBoundaryFeature* result = new TectonicBoundaryFeature(getGsoapContext(), guid, title, false);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

TectonicBoundaryFeature* EpcDocument::createFracture(const std::string & guid, const std::string & title)
{
	TectonicBoundaryFeature* result = new TectonicBoundaryFeature(getGsoapContext(), guid, title, true);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

WellboreFeature* EpcDocument::createWellboreFeature(const std::string & guid, const std::string & title)
{
	WellboreFeature* result = new WellboreFeature(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

SeismicLatticeFeature* EpcDocument::createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount)
{
	SeismicLatticeFeature* result = new SeismicLatticeFeature(getGsoapContext(), guid, title, inlineIncrement, crosslineIncrement, originInline, originCrossline, inlineCount, crosslineCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

SeismicLineFeature* EpcDocument::createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount)
{
	SeismicLineFeature* result = new SeismicLineFeature(getGsoapContext(), guid, title, traceIndexIncrement, firstTraceIndex, traceCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

SeismicLineSetFeature* EpcDocument::createSeismicLineSet(const std::string & guid, const std::string & title)
{
	SeismicLineSetFeature* result = new SeismicLineSetFeature(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

FrontierFeature* EpcDocument::createFrontier(const std::string & guid, const std::string & title)
{
	FrontierFeature* result = new FrontierFeature(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicUnitFeature* EpcDocument::createStratigraphicUnit(const std::string & guid, const std::string & title)
{
	StratigraphicUnitFeature* result = new StratigraphicUnitFeature(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

OrganizationFeature* EpcDocument::createStructuralModel(const std::string & guid, const std::string & title)
{
	OrganizationFeature* result = new OrganizationFeature(getGsoapContext(), guid, title, resqml2__OrganizationKind__structural);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

OrganizationFeature* EpcDocument::createStratigraphicModel(const std::string & guid, const std::string & title)
{
	OrganizationFeature* result = new OrganizationFeature(getGsoapContext(), guid, title, resqml2__OrganizationKind__stratigraphic);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

OrganizationFeature* EpcDocument::createEarthModel(const std::string & guid, const std::string & title)
{
	OrganizationFeature* result = new OrganizationFeature(getGsoapContext(), guid, title, resqml2__OrganizationKind__earth_x0020model);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

FluidBoundaryFeature* EpcDocument::createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact)
{
	FluidBoundaryFeature* result = new FluidBoundaryFeature(getGsoapContext(), guid, title, fluidContact);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

//************************************
//************ INTERPRETATION ********
//************************************

GenericFeatureInterpretation* EpcDocument::createGenericFeatureInterpretation(resqml2::AbstractFeature * feature, const std::string & guid, const std::string & title)
{
	GenericFeatureInterpretation* result = new GenericFeatureInterpretation(feature, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

BoundaryFeatureInterpretation* EpcDocument::createBoundaryFeatureInterpretation(resqml2_0_1::BoundaryFeature * feature, const std::string & guid, const std::string & title)
{
	BoundaryFeatureInterpretation* result = new BoundaryFeatureInterpretation(feature, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

HorizonInterpretation* EpcDocument::createPartialHorizonInterpretation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	HorizonInterpretation* result = new HorizonInterpretation(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

HorizonInterpretation* EpcDocument::createHorizonInterpretation(Horizon * horizon, const std::string & guid, const std::string & title)
{
	HorizonInterpretation* result = new HorizonInterpretation(horizon, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

FaultInterpretation* EpcDocument::createFaultInterpretation(TectonicBoundaryFeature * fault, const std::string & guid, const std::string & title)
{
	FaultInterpretation* result = new FaultInterpretation(fault, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

WellboreInterpretation* EpcDocument::createWellboreInterpretation(WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled)
{
	WellboreInterpretation* result = new WellboreInterpretation(wellbore, guid, title, isDrilled);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

EarthModelInterpretation* EpcDocument::createEarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	EarthModelInterpretation* result = new EarthModelInterpretation(orgFeat, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StructuralOrganizationInterpretation* EpcDocument::createStructuralOrganizationInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StructuralOrganizationInterpretation* result = new StructuralOrganizationInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__age);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StructuralOrganizationInterpretation* EpcDocument::createStructuralOrganizationInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StructuralOrganizationInterpretation* result = new StructuralOrganizationInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__apparent_x0020depth);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StructuralOrganizationInterpretation* EpcDocument::createStructuralOrganizationInterpretationInMeasuredDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StructuralOrganizationInterpretation* result = new StructuralOrganizationInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__measured_x0020depth);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicColumn* EpcDocument::createStratigraphicColumn(const std::string & guid, const std::string & title)
{
	StratigraphicColumn* result = new StratigraphicColumn(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicUnitInterpretation* EpcDocument::createStratigraphicUnitInterpretation(StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title)
{
	StratigraphicUnitInterpretation* result = new StratigraphicUnitInterpretation(stratiUnitFeature, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicColumnRankInterpretation* EpcDocument::createStratigraphicColumnRankInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank)
{
	StratigraphicColumnRankInterpretation* result = new StratigraphicColumnRankInterpretation(orgFeat, guid, title, rank, resqml2__OrderingCriteria__age);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicColumnRankInterpretation* EpcDocument::createStratigraphicColumnRankInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank)
{
	StratigraphicColumnRankInterpretation* result = new StratigraphicColumnRankInterpretation(orgFeat, guid, title, rank, resqml2__OrderingCriteria__apparent_x0020depth);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicOccurrenceInterpretation* EpcDocument::createStratigraphicOccurrenceInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StratigraphicOccurrenceInterpretation* result = new StratigraphicOccurrenceInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__age);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StratigraphicOccurrenceInterpretation* EpcDocument::createStratigraphicOccurrenceInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StratigraphicOccurrenceInterpretation* result = new StratigraphicOccurrenceInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__apparent_x0020depth);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

//************************************
//************ REPRESENTATION ********
//************************************

TriangulatedSetRepresentation* EpcDocument::createTriangulatedSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	TriangulatedSetRepresentation* result = new TriangulatedSetRepresentation(interp, crs, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PolylineSetRepresentation* EpcDocument::createPolylineSetRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PolylineSetRepresentation* result = new PolylineSetRepresentation(crs, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PolylineSetRepresentation* EpcDocument::createPolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PolylineSetRepresentation* result = new PolylineSetRepresentation(interp, crs, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PolylineSetRepresentation* EpcDocument::createPolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind)
{
	PolylineSetRepresentation* result = new PolylineSetRepresentation(interp, crs, guid, title, roleKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PointSetRepresentation* EpcDocument::createPointSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PointSetRepresentation* result = new PointSetRepresentation(interp, crs, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PlaneSetRepresentation* EpcDocument::createPlaneSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PlaneSetRepresentation* result = new PlaneSetRepresentation(interp, crs, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PolylineRepresentation* EpcDocument::createPolylineRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed)
{
	PolylineRepresentation* result = new PolylineRepresentation(crs, guid, title, isClosed);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PolylineRepresentation* EpcDocument::createPolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed)
{
	PolylineRepresentation* result = new PolylineRepresentation(interp, crs, guid, title, isClosed);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

PolylineRepresentation* EpcDocument::createPolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind, bool isClosed)
{
	PolylineRepresentation* result = new PolylineRepresentation(interp, crs, guid, title, roleKind, isClosed);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

Grid2dRepresentation* EpcDocument::createGrid2dRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	Grid2dRepresentation* result = new Grid2dRepresentation(interp, crs, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

WellboreTrajectoryRepresentation* EpcDocument::createWellboreTrajectoryRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2::MdDatum * mdInfo)
{
	WellboreTrajectoryRepresentation* result = new WellboreTrajectoryRepresentation(interp, guid, title, mdInfo);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

WellboreFrameRepresentation* EpcDocument::createWellboreFrameRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	WellboreFrameRepresentation* result = new WellboreFrameRepresentation(interp, guid, title, traj);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

WellboreMarkerFrameRepresentation* EpcDocument::createWellboreMarkerFrameRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	WellboreMarkerFrameRepresentation* result = new WellboreMarkerFrameRepresentation(interp, guid, title, traj);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

BlockedWellboreRepresentation* EpcDocument::createBlockedWellboreRepresentation(WellboreInterpretation* interp,
	const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	BlockedWellboreRepresentation* result = new BlockedWellboreRepresentation(interp, guid, title, traj);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::RepresentationSetRepresentation* EpcDocument::createRepresentationSetRepresentation(
        AbstractOrganizationInterpretation* interp,
        const std::string & guid,
        const std::string & title)
{
	RepresentationSetRepresentation* result = new RepresentationSetRepresentation(interp, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::RepresentationSetRepresentation* EpcDocument::createRepresentationSetRepresentation(
	const std::string & guid,
	const std::string & title)
{
	RepresentationSetRepresentation* result = new RepresentationSetRepresentation(this, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::RepresentationSetRepresentation* EpcDocument::createPartialRepresentationSetRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	resqml2::RepresentationSetRepresentation* result = new resqml2::RepresentationSetRepresentation(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

NonSealedSurfaceFrameworkRepresentation* EpcDocument::createNonSealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp, 
        const std::string & guid,
        const std::string & title,
        const bool & isSealed)
{
	NonSealedSurfaceFrameworkRepresentation* result = new NonSealedSurfaceFrameworkRepresentation(interp, guid, title, isSealed);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

SealedSurfaceFrameworkRepresentation* EpcDocument::createSealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp,
        const std::string & guid,
        const std::string & title)
{
	SealedSurfaceFrameworkRepresentation* result = new SealedSurfaceFrameworkRepresentation(interp, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

AbstractIjkGridRepresentation* EpcDocument::createPartialIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	AbstractIjkGridRepresentation* result = new AbstractIjkGridRepresentation(dor, false);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

AbstractIjkGridRepresentation* EpcDocument::createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	AbstractIjkGridRepresentation* result = new AbstractIjkGridRepresentation(dor, true);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

IjkGridExplicitRepresentation* EpcDocument::createIjkGridExplicitRepresentation(resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridExplicitRepresentation* result = new IjkGridExplicitRepresentation(getGsoapContext(), crs, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

IjkGridExplicitRepresentation* EpcDocument::createIjkGridExplicitRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridExplicitRepresentation* result = new IjkGridExplicitRepresentation(interp, crs, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

IjkGridParametricRepresentation* EpcDocument::createIjkGridParametricRepresentation(resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridParametricRepresentation* result = new IjkGridParametricRepresentation(getGsoapContext(), crs, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

IjkGridParametricRepresentation* EpcDocument::createIjkGridParametricRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridParametricRepresentation* result = new IjkGridParametricRepresentation(interp, crs, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

IjkGridLatticeRepresentation* EpcDocument::createIjkGridLatticeRepresentation(resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridLatticeRepresentation* result = new IjkGridLatticeRepresentation(getGsoapContext(), crs, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

IjkGridLatticeRepresentation* EpcDocument::createIjkGridLatticeRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridLatticeRepresentation* result = new IjkGridLatticeRepresentation(interp, crs, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::IjkGridNoGeometryRepresentation* EpcDocument::createIjkGridNoGeometryRepresentation(
	const std::string & guid, const std::string & title,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridNoGeometryRepresentation* result = new IjkGridNoGeometryRepresentation(getGsoapContext(), guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::IjkGridNoGeometryRepresentation* EpcDocument::createIjkGridNoGeometryRepresentation(resqml2::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridNoGeometryRepresentation* result = new IjkGridNoGeometryRepresentation(interp, guid, title, iCount, jCount, kCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

UnstructuredGridRepresentation* EpcDocument::createPartialUnstructuredGridRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	UnstructuredGridRepresentation* result = new UnstructuredGridRepresentation(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

UnstructuredGridRepresentation* EpcDocument::createUnstructuredGridRepresentation(resqml2::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const ULONG64 & cellCount)
{
	UnstructuredGridRepresentation* result = new UnstructuredGridRepresentation(getGsoapContext(), crs, guid, title, cellCount);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::SubRepresentation* EpcDocument::createPartialSubRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	resqml2::SubRepresentation* result = new SubRepresentation(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::SubRepresentation* EpcDocument::createSubRepresentation(const std::string & guid, const std::string & title)
{
	resqml2::SubRepresentation* result = new SubRepresentation(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::SubRepresentation* EpcDocument::createSubRepresentation(resqml2::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title)
{
	resqml2::SubRepresentation* result = new SubRepresentation(interp, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::GridConnectionSetRepresentation* EpcDocument::createPartialGridConnectionSetRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	resqml2::GridConnectionSetRepresentation* result = new GridConnectionSetRepresentation(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::GridConnectionSetRepresentation* EpcDocument::createGridConnectionSetRepresentation(const std::string & guid, const std::string & title)
{
	resqml2::GridConnectionSetRepresentation* result = new GridConnectionSetRepresentation(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::GridConnectionSetRepresentation* EpcDocument::createGridConnectionSetRepresentation(resqml2::AbstractFeatureInterpretation* interp,
        const std::string & guid, const std::string & title)
{
	resqml2::GridConnectionSetRepresentation* result = new GridConnectionSetRepresentation(interp, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

//************************************
//************* PROPERTIES ***********
//************************************

resqml2::TimeSeries* EpcDocument::createTimeSeries(const std::string & guid, const std::string & title)
{
	resqml2::TimeSeries* result = new resqml2_0_1::TimeSeries(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::TimeSeries* EpcDocument::createPartialTimeSeries(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	resqml2::TimeSeries* result = new resqml2_0_1::TimeSeries(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

StringTableLookup* EpcDocument::createStringTableLookup(const std::string & guid, const std::string & title)
{
	StringTableLookup* result = new StringTableLookup(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::PropertyKind* EpcDocument::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	resqml2::PropertyKind* result = new resqml2_0_1::PropertyKind(getGsoapContext(), guid, title, namingSystem, uom, parentEnergisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::PropertyKind* EpcDocument::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * parentPropType)
{
	resqml2::PropertyKind* result = new resqml2_0_1::PropertyKind(getGsoapContext(), guid, title, namingSystem, uom, parentPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::PropertyKind* EpcDocument::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	resqml2::PropertyKind* result = new resqml2_0_1::PropertyKind(getGsoapContext(), guid, title, namingSystem, nonStandardUom, parentEnergisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::PropertyKind* EpcDocument::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const std::string & nonStandardUom, resqml2::PropertyKind * parentPropType)
{
	resqml2::PropertyKind* result = new resqml2_0_1::PropertyKind(getGsoapContext(), guid, title, namingSystem, nonStandardUom, parentPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

resqml2::PropertyKind* EpcDocument::createPartialPropertyKind(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	resqml2::PropertyKind* result = new resqml2_0_1::PropertyKind(dor);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

CommentProperty* EpcDocument::createCommentProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	CommentProperty* result = new CommentProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

CommentProperty* EpcDocument::createCommentProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropType)
{
	CommentProperty* result = new CommentProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
	
ContinuousProperty* EpcDocument::createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	ContinuousProperty* result = new ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

ContinuousProperty* EpcDocument::createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropType)
{
	ContinuousProperty* result = new ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, localPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

ContinuousProperty* EpcDocument::createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	ContinuousProperty* result = new ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, energisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

ContinuousProperty* EpcDocument::createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, resqml2::PropertyKind * localPropType)
{
	ContinuousProperty* result = new ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, localPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

ContinuousPropertySeries* EpcDocument::createContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	ContinuousPropertySeries* result = new ContinuousPropertySeries(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind, ts, useInterval);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

ContinuousPropertySeries* EpcDocument::createContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropType,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	ContinuousPropertySeries* result = new ContinuousPropertySeries(rep, guid, title, dimension, attachmentKind, uom, localPropType, ts, useInterval);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
	
	DiscreteProperty* EpcDocument::createDiscreteProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	DiscreteProperty* result = new DiscreteProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

DiscreteProperty* EpcDocument::createDiscreteProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropType)
{
	DiscreteProperty* result = new DiscreteProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
	
DiscretePropertySeries* EpcDocument::createDiscretePropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	DiscretePropertySeries* result = new DiscretePropertySeries(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind, ts, useInterval);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

DiscretePropertySeries* EpcDocument::createDiscretePropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropType,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	DiscretePropertySeries* result = new DiscretePropertySeries(rep, guid, title, dimension, attachmentKind, localPropType, ts, useInterval);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

CategoricalProperty* EpcDocument::createCategoricalProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	CategoricalProperty* result = new CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
	
CategoricalProperty* EpcDocument::createCategoricalProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, resqml2::PropertyKind * localPropType)
{
	CategoricalProperty* result = new CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, localPropType);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

CategoricalPropertySeries* EpcDocument::createCategoricalPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	CategoricalPropertySeries* result = new CategoricalPropertySeries(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind, ts, useInterval);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

CategoricalPropertySeries* EpcDocument::createCategoricalPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, resqml2::PropertyKind * localPropType,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	CategoricalPropertySeries* result = new CategoricalPropertySeries(rep, guid, title, dimension, attachmentKind, strLookup, localPropType, ts, useInterval);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

//************************************
//************* ACTIVITIES ***********
//************************************

resqml2::ActivityTemplate* EpcDocument::createActivityTemplate(const std::string & guid, const std::string & title)
{
	ActivityTemplate* result = new ActivityTemplate(getGsoapContext(), guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
		
resqml2::Activity* EpcDocument::createActivity(resqml2::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title)
{
	Activity* result = new Activity(activityTemplate, guid, title);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}
		
//************************************
//*************** WITSML *************
//************************************

Well* EpcDocument::createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone)
{
	Well* result = new Well(getGsoapContext(), guid, title, timeZone);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

Well* EpcDocument::createWell(
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
			const std::string & comments)
{
	Well* result = new Well(getGsoapContext(), guid, title, timeZone, operator_, statusWell, purposeWell, fluidWell, directionWell, dTimSpud, sourceName, dTimCreation, dTimLastChange, comments);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

CoordinateReferenceSystem* EpcDocument::createCoordinateReferenceSystem(
			const std::string & guid,
			const std::string & title,
			const std::string & namingSystem,
			const std::string & code,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments)
{
	CoordinateReferenceSystem* result = new CoordinateReferenceSystem(getGsoapContext(), guid, title, namingSystem, code, sourceName, dTimCreation, dTimLastChange, comments);
	addFesapiWrapperAndDeleteItIfException(result);
	return result;
}

void common::EpcDocument::set_hdf_proxy_builder(HdfProxyBuilder builder)
{
  make_hdf_proxy = builder;
}

void common::EpcDocument::set_hdf_proxy_builder(HdfProxyBuilderFromGsoapProxy2_0_1 builder)
{
	make_hdf_proxy_from_gsoap_proxy_2_0_1 = builder;
}

#ifdef WITH_RESQML2_1
void common::EpcDocument::set_hdf_proxy_builder(HdfProxyBuilderFromGsoapProxy2_1 builder)
{
	make_hdf_proxy_from_gsoap_proxy_2_1 = builder;
}
#endif

int EpcDocument::getGsoapErrorCode() const
{
	return s->error;
}

std::string EpcDocument::getGsoapErrorMessage() const
{
	ostringstream oss;
	soap_stream_fault(s, oss);
	return oss.str();
}

void EpcDocument::setGsoapStream(std::istream * inputStream)
{
	s->is = inputStream;
}

gsoap_resqml2_0_1::_eml__EpcExternalPartReference* EpcDocument::getEpcExternalPartReferenceGsoapProxyFromGsoapContext()
{
	gsoap_resqml2_0_1::_eml__EpcExternalPartReference* read = gsoap_resqml2_0_1::soap_new_eml__obj_USCOREEpcExternalPartReference(s, 1);
	soap_read_eml__obj_USCOREEpcExternalPartReference(s, read);
	return read;
}
