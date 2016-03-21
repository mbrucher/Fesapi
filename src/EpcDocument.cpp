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
#include "resqml2_0_1/Fault.h"
#include "resqml2_0_1/Fracture.h"
#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/FluidBoundaryFeature.h"
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

namespace // anonymous namespace. Use only in that file.
{
	resqml2_0_1::AbstractHdfProxy* default_builder(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
  {
	  return new HdfProxy(soapContext, guid, title, packageDirAbsolutePath, externalFilePath);
  }
  resqml2_0_1::AbstractHdfProxy* default_builder(gsoap_resqml2_0_1::_eml__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
  {
    return new HdfProxy(fromGsoap, packageDirAbsolutePath, externalFilePath);
  }
}

EpcDocument::EpcDocument(const string & fileName, bool overwriteH5File) :
	overwriteH5File(overwriteH5File), package(nullptr), s(nullptr), propertyKindMapper(nullptr), make_hdf_proxy(&default_builder), make_hdf_proxy_from_soap(&default_builder)
{
	open(fileName);
}

EpcDocument::EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory, bool overwriteH5File) :
	overwriteH5File(overwriteH5File), package(nullptr), s(nullptr), make_hdf_proxy(&default_builder), make_hdf_proxy_from_soap(&default_builder)
{
	open(fileName);

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

EpcDocument::~EpcDocument()
{
	close();
}

bool EpcDocument::isOverwritingH5FileIfNeeded() const { return overwriteH5File; }

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

const std::vector<resqml2_0_1::Fault*> & EpcDocument::getFaultSet() const { return faultSet; }

const std::vector<resqml2_0_1::Fracture*> & EpcDocument::getFractureSet() const { return fractureSet; }

const std::vector<resqml2_0_1::TriangulatedSetRepresentation*> & EpcDocument::getAllTriangulatedSetRepSet() const { return triangulatedSetRepresentationSet; }

std::vector<resqml2_0_1::SeismicLineFeature*> EpcDocument::getSeismicLineSet() const { return seismicLineSet; }

std::vector<resqml2_0_1::WellboreFeature*> EpcDocument::getWellboreSet() const { return wellboreSet; }

std::vector<resqml2_0_1::PolylineRepresentation*> EpcDocument::getPolylineRepresentationSet() const { return polylineRepresentationSet; }

std::vector<resqml2_0_1::AbstractIjkGridRepresentation*> EpcDocument::getIjkGridRepresentationSet() const { return ijkGridRepresentationSet; }
unsigned int EpcDocument::getIjkGridRepresentationCount() const { return ijkGridRepresentationSet.size(); }
resqml2_0_1::AbstractIjkGridRepresentation* EpcDocument::getIjkGridRepresentation(const unsigned int & i) const
{
	if (i >= getIjkGridRepresentationCount())
		throw out_of_range("The ijk grid index is out of range.");
	else
		return ijkGridRepresentationSet[i];
}

std::vector<resqml2_0_1::UnstructuredGridRepresentation*> EpcDocument::getUnstructuredGridRepresentationSet() const { return unstructuredGridRepresentationSet; }

const std::vector<resqml2_0_1::FrontierFeature*> & EpcDocument::getFrontierSet() const { return frontierSet; }

const std::vector<resqml2_0_1::OrganizationFeature*> & EpcDocument::getOrganizationSet() const { return organizationSet; }

const std::vector<resqml2_0_1::TimeSeries*> & EpcDocument::getTimeSeriesSet() const { return timeSeriesSet; }

std::vector<resqml2_0_1::AbstractHdfProxy*> EpcDocument::getHdfProxySet() const { return hdfProxySet; }
unsigned int EpcDocument::getHdfProxyCount() const { return hdfProxySet.size(); }

std::vector<witsml1_4_1_1::Trajectory*> EpcDocument::getWitsmlTrajectorySet() const { return witsmlTrajectorySet; }

void EpcDocument::addWarning(const std::string & warning) { warnings.push_back(warning); }
const std::vector<std::string> & EpcDocument::getWarnings() const { return warnings; }

bool EpcDocument::open(const std::string & fileName)
{
	if (s != nullptr || package != nullptr)
		return false;

	setFilePath(fileName);

	s = soap_new2(SOAP_XML_STRICT | SOAP_C_UTFSTRING, SOAP_XML_GRAPH | SOAP_XML_INDENT | SOAP_XML_CANONICAL | SOAP_C_UTFSTRING); // new context with option

	package = new Package();

	return true;
}

void EpcDocument::close()
{
	if (propertyKindMapper != nullptr)
	{
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

	if (package != nullptr)
	{
		delete package;
		package = nullptr;
	}

	if (s != nullptr)
	{
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
	if (dotPos != string::npos)
	{
		if (this->filePath.substr(dotPos) != DOCUMENT_EXTENSION)
		{
			this->filePath += DOCUMENT_EXTENSION;
		}
	}
	else
	{
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
	if (proxy->getXmlTag().compare(TectonicBoundaryFeature::XML_TAG) == 0)
	{
		if (!static_cast<TectonicBoundaryFeature*>(proxy)->isAFracture())
			faultSet.push_back(static_cast<Fault*>(proxy));
		else
			fractureSet.push_back(static_cast<Fracture*>(proxy));
	}
	else if (proxy->getXmlTag().compare(GeneticBoundaryFeature::XML_TAG) == 0)
	{
		if (static_cast<GeneticBoundaryFeature*>(proxy)->isAnHorizon())
			horizonSet.push_back(static_cast<Horizon*>(proxy));
	}
	else if (proxy->getXmlTag().compare(SeismicLineFeature::XML_TAG) == 0)
	{
		seismicLineSet.push_back(static_cast<SeismicLineFeature*>(proxy));
	}
	else if (proxy->getXmlTag().compare(EpcExternalPartReference::XML_TAG) == 0)
	{
		hdfProxySet.push_back(static_cast<AbstractHdfProxy*>(proxy));
	}
	else if (proxy->getXmlTag().compare(WellboreFeature::XML_TAG) == 0)
	{
		wellboreSet.push_back(static_cast<WellboreFeature*>(proxy));
	}
	else if (proxy->getXmlTag().compare(PolylineRepresentation::XML_TAG) == 0)
	{
		polylineRepresentationSet.push_back(static_cast<PolylineRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(AbstractIjkGridRepresentation::XML_TAG) == 0)
	{
		ijkGridRepresentationSet.push_back(static_cast<AbstractIjkGridRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(UnstructuredGridRepresentation::XML_TAG) == 0)
	{
		unstructuredGridRepresentationSet.push_back(static_cast<UnstructuredGridRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(LocalDepth3dCrs::XML_TAG) == 0)
	{
		localDepth3dCrsSet.push_back(static_cast<LocalDepth3dCrs*>(proxy));
	}
	else if (proxy->getXmlTag().compare(LocalTime3dCrs::XML_TAG) == 0)
	{
		localTime3dCrsSet.push_back(static_cast<LocalTime3dCrs*>(proxy));
	}
	else if (proxy->getXmlTag().compare(StratigraphicColumn::XML_TAG) == 0)
	{
		stratigraphicColumnSet.push_back(static_cast<StratigraphicColumn*>(proxy));
	}
	else if (proxy->getXmlTag().compare(TriangulatedSetRepresentation::XML_TAG) == 0)
	{
		triangulatedSetRepresentationSet.push_back(static_cast<TriangulatedSetRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(FrontierFeature::XML_TAG) == 0)
	{
		frontierSet.push_back(static_cast<FrontierFeature*>(proxy));
	}
	else if (proxy->getXmlTag().compare(OrganizationFeature::XML_TAG) == 0)
	{
		organizationSet.push_back(static_cast<OrganizationFeature*>(proxy));
	}
	else if (proxy->getXmlTag().compare(RepresentationSetRepresentation::XML_TAG) == 0)
	{
		representationSetRepresentationSet.push_back(static_cast<RepresentationSetRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(NonSealedSurfaceFrameworkRepresentation::XML_TAG) == 0)
	{
		representationSetRepresentationSet.push_back(static_cast<NonSealedSurfaceFrameworkRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(SealedSurfaceFrameworkRepresentation::XML_TAG) == 0)
	{
		representationSetRepresentationSet.push_back(static_cast<SealedSurfaceFrameworkRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(SealedVolumeFrameworkRepresentation::XML_TAG) == 0)
	{
		representationSetRepresentationSet.push_back(static_cast<SealedVolumeFrameworkRepresentation*>(proxy));
	}
	else if (proxy->getXmlTag().compare(TimeSeries::XML_TAG) == 0)
	{
		timeSeriesSet.push_back(static_cast<TimeSeries*>(proxy));
	}

	if (getResqmlAbstractObjectByUuid(proxy->getUuid()) == nullptr)
	{
		resqmlAbstractObjectSet[proxy->getUuid()] = proxy;
	}
	else
	{
		throw invalid_argument("You cannot have twice the same UUID " + proxy->getUuid() + " for two different Resqml objects in an EPC document");
	}
	proxy->epcDocument = this;
}

void EpcDocument::addGsoapProxyAndDeleteItIfException(resqml2::AbstractObject* proxy)
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

void EpcDocument::addGsoapProxyAndDeleteItIfException(witsml1_4_1_1::AbstractObject* proxy)
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
			for (unsigned int relIndex = 0; relIndex < relSet.size(); relIndex++)
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
		for (unsigned int relIndex = 0; relIndex < relSet.size(); relIndex++)
			fp->addRelationship(relSet[relIndex]);

		epc::ContentType contentType(false, it->second->getContentType(), it->second->getPartNameInEpcDocument());
		package->addContentType(contentType);
	}

	package->writePackage();
}

string EpcDocument::deserialize()
{
	warnings.clear();
	package->openForReading(filePath);

	// Read all Resqml objects
	FileContentType::ContentTypeMap contentTypes = package->getFileContentType().getAllContentType();
	for(FileContentType::ContentTypeMap::const_iterator it=contentTypes.begin(); it != contentTypes.end(); ++it)
	{
		if (it->second.getContentTypeString().find("application/x-resqml+xml;version=2.0;type=") == 0 ||
			it->second.getContentTypeString().find("application/x-resqml+xml;version=2.0.1;type=") == 0)
		{
			string fileStr = package->extractFile(it->second.getExtensionOrPartName().substr(1));
			if (fileStr.empty() == true)
				throw invalid_argument("The EPC document contains the file " + it->second.getExtensionOrPartName().substr(1) + " in its contentType file which cannot be found or cannot be unzipped or is empty.");
			istringstream iss(fileStr);
			s->is = &iss;
			resqml2::AbstractObject* wrapper = nullptr;
			size_t lastEqualCharPos = it->second.getContentTypeString().find_last_of('_'); // The XML tag is after "obj_"
			string resqmlContentType = it->second.getContentTypeString().substr(lastEqualCharPos+1);
			if (resqmlContentType.compare(MdDatum::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__MdDatum* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREMdDatum(s, 1);
				soap_read_resqml2__obj_USCOREMdDatum(s, read);
				wrapper = new MdDatum(read);
			}
			else if (resqmlContentType.compare(Activity::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__Activity* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREActivity(s, 1);
				soap_read_resqml2__obj_USCOREActivity(s, read);
				wrapper = new Activity(read);
			}
			else if (resqmlContentType.compare(ActivityTemplate::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__ActivityTemplate* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREActivityTemplate(s, 1);
				soap_read_resqml2__obj_USCOREActivityTemplate(s, read);
				wrapper = new ActivityTemplate(read);
			}
			else if (resqmlContentType.compare(SeismicLatticeFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__SeismicLatticeFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORESeismicLatticeFeature(s, 1);
				soap_read_resqml2__obj_USCORESeismicLatticeFeature(s, read);
				wrapper = new SeismicLatticeFeature(read);
			}
			else if (resqmlContentType.compare(SeismicLineFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__SeismicLineFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORESeismicLineFeature(s, 1);
				soap_read_resqml2__obj_USCORESeismicLineFeature(s, read);
				wrapper = new SeismicLineFeature(read);
			}
			else if (resqmlContentType.compare(SeismicLineSetFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__SeismicLineSetFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORESeismicLineSetFeature(s, 1);
				soap_read_resqml2__obj_USCORESeismicLineSetFeature(s, read);
				wrapper = new SeismicLineSetFeature(read);
			}
			else if (resqmlContentType.compare(FrontierFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__FrontierFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREFrontierFeature(s, 1);
				soap_read_resqml2__obj_USCOREFrontierFeature(s, read);
				wrapper = new FrontierFeature(read);
			}
			else if (resqmlContentType.compare(LocalDepth3dCrs::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__LocalDepth3dCrs* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORELocalDepth3dCrs(s, 1);
				soap_read_resqml2__obj_USCORELocalDepth3dCrs(s, read);
				wrapper = new LocalDepth3dCrs(read);
			}
			else if (resqmlContentType.compare(LocalTime3dCrs::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__LocalTime3dCrs* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORELocalTime3dCrs(s, 1);
				soap_read_resqml2__obj_USCORELocalTime3dCrs(s, read);
				wrapper = new LocalTime3dCrs(read);
			}
			else if (resqmlContentType.compare(TectonicBoundaryFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__TectonicBoundaryFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORETectonicBoundaryFeature(s, 1);
				soap_read_resqml2__obj_USCORETectonicBoundaryFeature(s, read);
				if (read->TectonicBoundaryKind == gsoap_resqml2_0_1::resqml2__TectonicBoundaryKind__fault)
					wrapper = new Fault(read);
				else if (read->TectonicBoundaryKind == gsoap_resqml2_0_1::resqml2__TectonicBoundaryKind__fracture)
					wrapper = new Fracture(read);
			}
			else if (resqmlContentType.compare(GeneticBoundaryFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREGeneticBoundaryFeature(s, 1);
				soap_read_resqml2__obj_USCOREGeneticBoundaryFeature(s, read);
				wrapper = new Horizon(read);
			}
			else if (resqmlContentType.compare(BoundaryFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__BoundaryFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREBoundaryFeature(s, 1);
				soap_read_resqml2__obj_USCOREBoundaryFeature(s, read);
				wrapper = new BoundaryFeature(read);
			}
			else if (resqmlContentType.compare(WellboreFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__WellboreFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREWellboreFeature(s, 1);
				soap_read_resqml2__obj_USCOREWellboreFeature(s, read);
				wrapper = new WellboreFeature(read);
			}
			else if (resqmlContentType.compare(StratigraphicUnitFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StratigraphicUnitFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStratigraphicUnitFeature(s, 1);
				soap_read_resqml2__obj_USCOREStratigraphicUnitFeature(s, read);
				wrapper = new StratigraphicUnitFeature(read);
			}
			else if (resqmlContentType.compare(StratigraphicColumn::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StratigraphicColumn* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStratigraphicColumn(s, 1);
				soap_read_resqml2__obj_USCOREStratigraphicColumn(s, read);
				wrapper = new StratigraphicColumn(read);
			}
			else if (resqmlContentType.compare(GenericFeatureInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__GenericFeatureInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREGenericFeatureInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREGenericFeatureInterpretation(s, read);
				wrapper = new GenericFeatureInterpretation(read);
			}
			else if (resqmlContentType.compare(BoundaryFeatureInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__BoundaryFeatureInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREBoundaryFeatureInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREBoundaryFeatureInterpretation(s, read);
				wrapper = new BoundaryFeatureInterpretation(read);
			}
			else if (resqmlContentType.compare(WellboreInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__WellboreInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREWellboreInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREWellboreInterpretation(s, read);
				wrapper = new WellboreInterpretation(read);
			}
			else if (resqmlContentType.compare(FaultInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__FaultInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREFaultInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREFaultInterpretation(s, read);
				wrapper = new FaultInterpretation(read);
			}
			else if (resqmlContentType.compare(HorizonInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__HorizonInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREHorizonInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREHorizonInterpretation(s, read);
				wrapper = new HorizonInterpretation(read);
			}
			else if (resqmlContentType.compare(StratigraphicUnitInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StratigraphicUnitInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStratigraphicUnitInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREStratigraphicUnitInterpretation(s, read);
				wrapper = new StratigraphicUnitInterpretation(read);
			}
			else if (resqmlContentType.compare(StratigraphicColumnRankInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StratigraphicColumnRankInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStratigraphicColumnRankInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREStratigraphicColumnRankInterpretation(s, read);
				wrapper = new StratigraphicColumnRankInterpretation(read);
			}
			else if (resqmlContentType.compare(StratigraphicOccurrenceInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StratigraphicOccurrenceInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStratigraphicOccurrenceInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREStratigraphicOccurrenceInterpretation(s, read);
				wrapper = new StratigraphicOccurrenceInterpretation(read);
			}
			else if (resqmlContentType.compare(WellboreFrameRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__WellboreFrameRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREWellboreFrameRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREWellboreFrameRepresentation(s, read);
				wrapper = new WellboreFrameRepresentation(read);
			}
			else if (resqmlContentType.compare(WellboreMarkerFrameRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__WellboreMarkerFrameRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREWellboreMarkerFrameRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREWellboreMarkerFrameRepresentation(s, read);
				wrapper = new WellboreMarkerFrameRepresentation(read);
			}
			else if (resqmlContentType.compare(WellboreTrajectoryRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__WellboreTrajectoryRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREWellboreTrajectoryRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREWellboreTrajectoryRepresentation(s, read);
				wrapper = new WellboreTrajectoryRepresentation(read);
			}
			else if (resqmlContentType.compare(PolylineSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__PolylineSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREPolylineSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREPolylineSetRepresentation(s, read);
				wrapper = new PolylineSetRepresentation(read);
			}
			else if (resqmlContentType.compare(PointSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__PointSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREPointSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREPointSetRepresentation(s, read);
				wrapper = new PointSetRepresentation(read);
			}
			else if (resqmlContentType.compare(PlaneSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__PlaneSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREPlaneSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREPlaneSetRepresentation(s, read);
				wrapper = new PlaneSetRepresentation(read);
			}
			else if (resqmlContentType.compare(PolylineRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__PolylineRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREPolylineRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREPolylineRepresentation(s, read);
				wrapper = new PolylineRepresentation(read);
			}
			else if (resqmlContentType.compare(Grid2dSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__Grid2dSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREGrid2dSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREGrid2dSetRepresentation(s, read);
				wrapper = new Grid2dSetRepresentation(read);
			}
			else if (resqmlContentType.compare(Grid2dRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__Grid2dRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREGrid2dRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREGrid2dRepresentation(s, read);
				wrapper = new Grid2dRepresentation(read);
			}
			else if (resqmlContentType.compare(TriangulatedSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__TriangulatedSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORETriangulatedSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCORETriangulatedSetRepresentation(s, read);
				wrapper = new TriangulatedSetRepresentation(read);
			}
			else if (resqmlContentType.compare(BlockedWellboreRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__BlockedWellboreRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREBlockedWellboreRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREBlockedWellboreRepresentation(s, read);
				wrapper = new BlockedWellboreRepresentation(read);
			}
			else if (resqmlContentType.compare(AbstractIjkGridRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREIjkGridRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREIjkGridRepresentation(s, read);
				
				if (read->Geometry != nullptr)
				{
					switch (read->Geometry->Points->soap_type())
					{
					case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array :
						wrapper = new IjkGridExplicitRepresentation(read); break;
					case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray :
						wrapper = new IjkGridParametricRepresentation(read); break;
					case SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray :
						wrapper = new IjkGridLatticeRepresentation(read); break;
					}
				}
				else
					wrapper = new IjkGridNoGeometryRepresentation(read);
			}
			else if (resqmlContentType.compare(UnstructuredGridRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__UnstructuredGridRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREUnstructuredGridRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREUnstructuredGridRepresentation(s, read);
				wrapper = new UnstructuredGridRepresentation(read);
			}
			else if (resqmlContentType.compare(PropertyKind::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__PropertyKind* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREPropertyKind(s, 1);
				soap_read_resqml2__obj_USCOREPropertyKind(s, read);
				wrapper = new PropertyKind(read);
			}
			else if (resqmlContentType.compare(ContinuousProperty::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__ContinuousProperty* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREContinuousProperty(s, 1);
				soap_read_resqml2__obj_USCOREContinuousProperty(s, read);
				wrapper = new ContinuousProperty(read);
			}
			else if (resqmlContentType.compare(ContinuousPropertySeries::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREContinuousPropertySeries(s, 1);
				soap_read_resqml2__obj_USCOREContinuousPropertySeries(s, read);
				wrapper = new ContinuousPropertySeries(read);
			}
			else if (resqmlContentType.compare(CategoricalProperty::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__CategoricalProperty* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORECategoricalProperty(s, 1);
				soap_read_resqml2__obj_USCORECategoricalProperty(s, read);
				wrapper = new CategoricalProperty(read);
			}
			else if (resqmlContentType.compare(CategoricalPropertySeries::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORECategoricalPropertySeries(s, 1);
				soap_read_resqml2__obj_USCORECategoricalPropertySeries(s, read);
				wrapper = new CategoricalPropertySeries(read);
			}
			else if (resqmlContentType.compare(DiscreteProperty::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__DiscreteProperty* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREDiscreteProperty(s, 1);
				soap_read_resqml2__obj_USCOREDiscreteProperty(s, read);
				wrapper = new DiscreteProperty(read);
			}
			else if (resqmlContentType.compare(DiscretePropertySeries::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREDiscretePropertySeries(s, 1);
				soap_read_resqml2__obj_USCOREDiscretePropertySeries(s, read);
				wrapper = new DiscretePropertySeries(read);
			}
			else if (resqmlContentType.compare(CommentProperty::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__CommentProperty* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORECommentProperty(s, 1);
				soap_read_resqml2__obj_USCORECommentProperty(s, read);
				wrapper = new CommentProperty(read);
			}
			else if (resqmlContentType.compare(StringTableLookup::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StringTableLookup* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStringTableLookup(s, 1);
				soap_read_resqml2__obj_USCOREStringTableLookup(s, read);
				wrapper = new StringTableLookup(read);
			}
			else if (resqmlContentType.compare(EarthModelInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__EarthModelInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREEarthModelInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREEarthModelInterpretation(s, read);
				wrapper = new EarthModelInterpretation(read);
			}
			else if (resqmlContentType.compare(OrganizationFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__OrganizationFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREOrganizationFeature(s, 1);
				soap_read_resqml2__obj_USCOREOrganizationFeature(s, read);
				wrapper = new OrganizationFeature(read);
			}
			else if (resqmlContentType.compare(StructuralOrganizationInterpretation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__StructuralOrganizationInterpretation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREStructuralOrganizationInterpretation(s, 1);
				soap_read_resqml2__obj_USCOREStructuralOrganizationInterpretation(s, read);
				wrapper = new StructuralOrganizationInterpretation(read);
			}
			else if (resqmlContentType.compare(FluidBoundaryFeature::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__FluidBoundaryFeature* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREFluidBoundaryFeature(s, 1);
				soap_read_resqml2__obj_USCOREFluidBoundaryFeature(s, read);
				wrapper = new FluidBoundaryFeature(read);
			}
			else if (resqmlContentType.compare(SubRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__SubRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORESubRepresentation(s, 1);
				soap_read_resqml2__obj_USCORESubRepresentation(s, read);
				wrapper = new SubRepresentation(read);
			}
			else if (resqmlContentType.compare(GridConnectionSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__GridConnectionSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREGridConnectionSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCOREGridConnectionSetRepresentation(s, read);
				wrapper = new GridConnectionSetRepresentation(read);
			}
			else if (resqmlContentType.compare(TimeSeries::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__TimeSeries* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORETimeSeries(s, 1);
				soap_read_resqml2__obj_USCORETimeSeries(s, read);
				wrapper = new TimeSeries(read);
			}
			else if (resqmlContentType.compare(RepresentationSetRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORERepresentationSetRepresentation(s, 1);
				soap_read_resqml2__obj_USCORERepresentationSetRepresentation(s, read);
				wrapper = new RepresentationSetRepresentation(read);
			}
			else if (resqmlContentType.compare(SealedSurfaceFrameworkRepresentation::XML_TAG) == 0)
			{
				gsoap_resqml2_0_1::_resqml2__SealedSurfaceFrameworkRepresentation* read = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCORESealedSurfaceFrameworkRepresentation(s, 1);
				soap_read_resqml2__obj_USCORESealedSurfaceFrameworkRepresentation(s, read);
				wrapper = new SealedSurfaceFrameworkRepresentation(read);
			}
			else if (resqmlContentType.compare(EpcExternalPartReference::XML_TAG) == 0)
			{
				// Look for the relative path of the HDF file
				string relFilePath = "";
				size_t slashPos = it->second.getExtensionOrPartName().substr(1).find_last_of("/\\");
				if (slashPos != string::npos)
					relFilePath = it->second.getExtensionOrPartName().substr(1).substr(0, slashPos+1);
				relFilePath += "_rels" + it->second.getExtensionOrPartName().substr(
						it->second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
				FileRelationship relFile;
				relFile.readFromString(package->extractFile(relFilePath));
				vector<Relationship> allRels = relFile.getAllRelationship();
				string hdfRelativeFilePath;
				for (unsigned int relIndex = 0 ; relIndex < allRels.size(); relIndex++)
				{
					if (allRels[relIndex].getType().compare("http://schemas.energistics.org/package/2012/relationships/externalResource") == 0)
					{
						hdfRelativeFilePath = allRels[relIndex].getTarget();
						break;
					}
				}

				// Common initialization
				gsoap_resqml2_0_1::_eml__EpcExternalPartReference* read = gsoap_resqml2_0_1::soap_new_eml__obj_USCOREEpcExternalPartReference(s, 1);
				soap_read_eml__obj_USCOREEpcExternalPartReference(s, read);
				wrapper = make_hdf_proxy_from_soap(read, getStorageDirectory(), hdfRelativeFilePath);
			}
			
			if (wrapper)
			{
				addGsoapProxyAndDeleteItIfException(wrapper);
				if (s->error != SOAP_OK) {
					ostringstream oss;
					soap_stream_fault(s, oss);
					return oss.str() + " IN " + it->second.getExtensionOrPartName();
				}
			}
		}
		else if (it->second.getContentTypeString().find("application/x-witsml+xml;version=1.4.1.1;type=") == 0)
		{
			string fileStr = package->extractFile(it->second.getExtensionOrPartName().substr(1));
			if (fileStr.empty() == true)
				throw invalid_argument("The EPC document contains the file " + it->second.getExtensionOrPartName().substr(1) + " in its contentType file which cannot be found or cannot be unzipped or is empty.");
			istringstream iss(fileStr);
			s->is = &iss;
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
			
			if (wrapper)
			{
				addGsoapProxyAndDeleteItIfException(wrapper);
				if (s->error != SOAP_OK) {
					ostringstream oss;
					soap_stream_fault(s, oss);
					return oss.str() + " IN " + it->second.getExtensionOrPartName();
				}
			}
		}
	}

	updateAllRelationships();

	return string();
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
	if (it == resqmlAbstractObjectSet.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

witsml1_4_1_1::AbstractObject* EpcDocument::getWitsmlAbstractObjectByUuid(const string & uuid) const
{
	
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.find(uuid);
#else
	std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* >::const_iterator it = witsmlAbstractObjectSet.find(uuid);
#endif
	if (it == witsmlAbstractObjectSet.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

vector<PolylineSetRepresentation*> EpcDocument::getFaultPolylineSetRepSet() const
{
	vector<PolylineSetRepresentation*> result;

	vector<Fault*> faultSet = getFaultSet();
	for (unsigned int featureIndex = 0; featureIndex < faultSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = faultSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
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

	vector<Fracture*> fractureSet = getFractureSet();
	for (unsigned int featureIndex = 0; featureIndex < fractureSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = fractureSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
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
	for (unsigned int featureIndex = 0; featureIndex < frontierSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = frontierSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
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

	vector<Fault*> faultSet = getFaultSet();
	for (unsigned int featureIndex = 0; featureIndex < faultSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = faultSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
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

	vector<Fracture*> fractureSet = getFractureSet();
	for (unsigned int featureIndex = 0; featureIndex < fractureSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = fractureSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
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
	for (unsigned int featureIndex = 0; featureIndex < horizonSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREGrid2dSetRepresentation)
				{
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
	for (unsigned int featureIndex = 0; featureIndex < horizonSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREGrid2dRepresentation)
				{
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
	for (unsigned int featureIndex = 0; featureIndex < horizonSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineRepresentation)
				{
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
	for (unsigned int featureIndex = 0; featureIndex < horizonSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
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

vector<TriangulatedSetRepresentation*> EpcDocument::getHorizonTriangulatedSetRepSet() const
{
	vector<TriangulatedSetRepresentation*> result;

	vector<Horizon*> horizonSet = getHorizonSet();
	for (unsigned int featureIndex = 0; featureIndex < horizonSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORETriangulatedSetRepresentation)
				{
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

	for (unsigned int triRepIndex = 0; triRepIndex < triangulatedSetRepresentationSet.size(); triRepIndex++)
	{
		int soapType = triangulatedSetRepresentationSet[triRepIndex]->getInterpretation()->getGsoapType();
		if (soapType != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREFaultInterpretation && soapType != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREHorizonInterpretation)
		{
			result.push_back(triangulatedSetRepresentationSet[triRepIndex]);
		}
	}

	return result;
}

vector<WellboreTrajectoryRepresentation*> EpcDocument::getWellboreCubicParamLineTrajRepSet() const
{
	vector<WellboreTrajectoryRepresentation*> result;

	for (unsigned int featureIndex = 0; featureIndex < wellboreSet.size(); featureIndex++)
	{
		vector<AbstractFeatureInterpretation*> interpSet = wellboreSet[featureIndex]->getInterpretationSet();
		for (unsigned int interpIndex = 0; interpIndex < interpSet.size(); interpIndex++)
		{
			vector<AbstractRepresentation*> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (unsigned int repIndex = 0; repIndex < repSet.size(); repIndex++)
			{
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREWellboreTrajectoryRepresentation)
				{
					result.push_back(static_cast<WellboreTrajectoryRepresentation*>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<RepresentationSetRepresentation*> EpcDocument::getRepresentationSetRepresentationSet() const
{
	return representationSetRepresentationSet;
}

unsigned int EpcDocument::getRepresentationSetRepresentationCount() const
{
	return representationSetRepresentationSet.size();
}

RepresentationSetRepresentation* EpcDocument::getRepresentationSetRepresentation(const unsigned int & index) const
{
	if (index >= getRepresentationSetRepresentationCount())
		throw range_error("The index of the representation set representaiton is out of range");
	else
		return representationSetRepresentationSet[index];
}

vector<IjkGridParametricRepresentation*> EpcDocument::getIjkGridParametricRepresentationSet() const
{
	vector<AbstractIjkGridRepresentation*> allgrids = getIjkGridRepresentationSet();
	vector<IjkGridParametricRepresentation*> result;
	
	for (unsigned int i = 0; i < allgrids.size(); ++i)
	{
		IjkGridParametricRepresentation* ijkGridParamRep = dynamic_cast<IjkGridParametricRepresentation*>(allgrids[i]);
		if (ijkGridParamRep != nullptr)
			result.push_back(ijkGridParamRep);
	}
	
	return result;
}

vector<IjkGridExplicitRepresentation*> EpcDocument::getIjkGridExplicitRepresentationSet() const
{
	vector<AbstractIjkGridRepresentation*> allgrids = getIjkGridRepresentationSet();
	vector<IjkGridExplicitRepresentation*> result;
	
	for (unsigned int i = 0; i < allgrids.size(); ++i)
	{
		IjkGridExplicitRepresentation* ijkGridParamRep = dynamic_cast<IjkGridExplicitRepresentation*>(allgrids[i]);
		if (ijkGridParamRep != nullptr)
			result.push_back(ijkGridParamRep);
	}
	
	return result;
}

std::vector<PolylineRepresentation*> EpcDocument::getSeismicLinePolylineRepSet() const
{
	vector<PolylineRepresentation*> result;
	vector<PolylineRepresentation*> polylineRepSet = getPolylineRepresentationSet();

	for (unsigned int i = 0; i < polylineRepSet.size(); ++i)
	{
		if (polylineRepSet[i]->isASeismicLine() || polylineRepSet[i]->isAFaciesLine())
			result.push_back(polylineRepSet[i]);
	}

	return result;
}

vector<IjkGridLatticeRepresentation*> EpcDocument::getIjkSeismicCubeGridRepresentationSet() const
{
	vector<AbstractIjkGridRepresentation*> allgrids = getIjkGridRepresentationSet();
	vector<IjkGridLatticeRepresentation*> result;
	
	for (unsigned int i = 0; i < allgrids.size(); ++i)
	{
		IjkGridLatticeRepresentation* ijkGridLatticeRep = dynamic_cast<IjkGridLatticeRepresentation*>(allgrids[i]);
		if (ijkGridLatticeRep != nullptr && (ijkGridLatticeRep->isASeismicCube() || ijkGridLatticeRep->isAFaciesCube()))
			result.push_back(ijkGridLatticeRep);
	}
	
	return result;
}

resqml2_0_1::AbstractHdfProxy* EpcDocument::getHdfProxy(const unsigned int & index) const
{
	if (index >= hdfProxySet.size())
		throw range_error("The index of the requested hdf proxy is out of range");

	return hdfProxySet[index];
}

string EpcDocument::getStorageDirectory() const
{
	size_t slashPos = filePath.find_last_of("/\\");
	if (slashPos != string::npos)
		return filePath.substr(0, slashPos+1);
	else
		return string();
}

string EpcDocument::getName() const
{
	size_t slashPos = filePath.find_last_of("/\\");
	if (slashPos == string::npos)
		return string();

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
		if (it->second->isPartial() == false)
			it->second->importRelationshipSetFromEpc(this);
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
	if (package->getExtendedCoreProperty().find(key) != package->getExtendedCoreProperty().end())
		return (package->getExtendedCoreProperty())[key];
	else
		return string();
}


//************************************
//************ HDF *******************
//************************************

AbstractHdfProxy* EpcDocument::createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath)
{
	AbstractHdfProxy* result = make_hdf_proxy(getGsoapContext(), guid, title, packageDirAbsolutePath, externalFilePath);
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

MdDatum* EpcDocument::createMdDatum(const std::string & guid, const std::string & title,
			class AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3)
{
	MdDatum* result = new MdDatum(getGsoapContext(), guid, title, locCrs, originKind, referenceLocationOrdinal1, referenceLocationOrdinal2, referenceLocationOrdinal3);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}
//************************************
//************ FEATURE ***************
//************************************

BoundaryFeature* EpcDocument::createBoundaryFeature(const std::string & guid, const std::string & title)
{
	BoundaryFeature* result = new BoundaryFeature(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

Horizon* EpcDocument::createHorizon(const std::string & guid, const std::string & title)
{
	Horizon* result = new Horizon(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

TectonicBoundaryFeature* EpcDocument::createTectonicBoundaryFeature(const std::string & guid, const std::string & title)
{
	TectonicBoundaryFeature* result = new TectonicBoundaryFeature(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

Fault* EpcDocument::createFault(const std::string & guid, const std::string & title)
{
	Fault* result = new Fault(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

Fracture* EpcDocument::createFracture(const std::string & guid, const std::string & title)
{
	Fracture* result = new Fracture(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

WellboreFeature* EpcDocument::createWellboreFeature(const std::string & guid, const std::string & title)
{
	WellboreFeature* result = new WellboreFeature(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

SeismicLatticeFeature* EpcDocument::createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount)
{
	SeismicLatticeFeature* result = new SeismicLatticeFeature(getGsoapContext(), guid, title, inlineIncrement, crosslineIncrement, originInline, originCrossline, inlineCount, crosslineCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

SeismicLineFeature* EpcDocument::createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount)
{
	SeismicLineFeature* result = new SeismicLineFeature(getGsoapContext(), guid, title, traceIndexIncrement, firstTraceIndex, traceCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

SeismicLineSetFeature* EpcDocument::createSeismicLineSet(const std::string & guid, const std::string & title)
{
	SeismicLineSetFeature* result = new SeismicLineSetFeature(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

FrontierFeature* EpcDocument::createFrontier(const std::string & guid, const std::string & title)
{
	FrontierFeature* result = new FrontierFeature(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicUnitFeature* EpcDocument::createStratigraphicUnit(const std::string & guid, const std::string & title)
{
	StratigraphicUnitFeature* result = new StratigraphicUnitFeature(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

OrganizationFeature* EpcDocument::createStructuralModel(const std::string & guid, const std::string & title)
{
	OrganizationFeature* result = new OrganizationFeature(getGsoapContext(), guid, title, resqml2__OrganizationKind__structural);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

OrganizationFeature* EpcDocument::createStratigraphicModel(const std::string & guid, const std::string & title)
{
	OrganizationFeature* result = new OrganizationFeature(getGsoapContext(), guid, title, resqml2__OrganizationKind__stratigraphic);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

OrganizationFeature* EpcDocument::createEarthModel(const std::string & guid, const std::string & title)
{
	OrganizationFeature* result = new OrganizationFeature(getGsoapContext(), guid, title, resqml2__OrganizationKind__earth_x0020model);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

FluidBoundaryFeature* EpcDocument::createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact)
{
	FluidBoundaryFeature* result = new FluidBoundaryFeature(getGsoapContext(), guid, title, fluidContact);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

//************************************
//************ INTERPRETATION ********
//************************************

GenericFeatureInterpretation* EpcDocument::createGenericFeatureInterpretation(AbstractFeature * feature, const std::string & guid, const std::string & title)
{
	GenericFeatureInterpretation* result = new GenericFeatureInterpretation(feature, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

BoundaryFeatureInterpretation* EpcDocument::createBoundaryFeatureInterpretation(resqml2_0_1::BoundaryFeature * feature, const std::string & guid, const std::string & title)
{
	BoundaryFeatureInterpretation* result = new BoundaryFeatureInterpretation(feature, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

HorizonInterpretation* EpcDocument::createHorizonInterpretation(Horizon * horizon, const std::string & guid, const std::string & title)
{
	HorizonInterpretation* result = new HorizonInterpretation(horizon, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

FaultInterpretation* EpcDocument::createFaultInterpretation(Fault * fault, const std::string & guid, const std::string & title)
{
	FaultInterpretation* result = new FaultInterpretation(fault, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

WellboreInterpretation* EpcDocument::createWellboreInterpretation(WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled)
{
	WellboreInterpretation* result = new WellboreInterpretation(wellbore, guid, title, isDrilled);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

EarthModelInterpretation* EpcDocument::createEarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	EarthModelInterpretation* result = new EarthModelInterpretation(orgFeat, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StructuralOrganizationInterpretation* EpcDocument::createStructuralOrganizationInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StructuralOrganizationInterpretation* result = new StructuralOrganizationInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__age);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StructuralOrganizationInterpretation* EpcDocument::createStructuralOrganizationInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StructuralOrganizationInterpretation* result = new StructuralOrganizationInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__apparent_x0020depth);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StructuralOrganizationInterpretation* EpcDocument::createStructuralOrganizationInterpretationInMeasuredDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StructuralOrganizationInterpretation* result = new StructuralOrganizationInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__measured_x0020depth);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicColumn* EpcDocument::createStratigraphicColumn(const std::string & guid, const std::string & title)
{
	StratigraphicColumn* result = new StratigraphicColumn(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicUnitInterpretation* EpcDocument::createStratigraphicUnitInterpretation(StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title)
{
	StratigraphicUnitInterpretation* result = new StratigraphicUnitInterpretation(stratiUnitFeature, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicColumnRankInterpretation* EpcDocument::createStratigraphicColumnRankInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank)
{
	StratigraphicColumnRankInterpretation* result = new StratigraphicColumnRankInterpretation(orgFeat, guid, title, rank, resqml2__OrderingCriteria__age);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicColumnRankInterpretation* EpcDocument::createStratigraphicColumnRankInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank)
{
	StratigraphicColumnRankInterpretation* result = new StratigraphicColumnRankInterpretation(orgFeat, guid, title, rank, resqml2__OrderingCriteria__apparent_x0020depth);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicOccurrenceInterpretation* EpcDocument::createStratigraphicOccurrenceInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StratigraphicOccurrenceInterpretation* result = new StratigraphicOccurrenceInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__age);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StratigraphicOccurrenceInterpretation* EpcDocument::createStratigraphicOccurrenceInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	StratigraphicOccurrenceInterpretation* result = new StratigraphicOccurrenceInterpretation(orgFeat, guid, title, resqml2__OrderingCriteria__apparent_x0020depth);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

//************************************
//************ REPRESENTATION ********
//************************************

TriangulatedSetRepresentation* EpcDocument::createTriangulatedSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	TriangulatedSetRepresentation* result = new TriangulatedSetRepresentation(interp, crs, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PolylineSetRepresentation* EpcDocument::createPolylineSetRepresentation(AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PolylineSetRepresentation* result = new PolylineSetRepresentation(crs, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PolylineSetRepresentation* EpcDocument::createPolylineSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PolylineSetRepresentation* result = new PolylineSetRepresentation(interp, crs, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PolylineSetRepresentation* EpcDocument::createPolylineSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind)
{
	PolylineSetRepresentation* result = new PolylineSetRepresentation(interp, crs, guid, title, roleKind);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PointSetRepresentation* EpcDocument::createPointSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PointSetRepresentation* result = new PointSetRepresentation(interp, crs, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PlaneSetRepresentation* EpcDocument::createPlaneSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	PlaneSetRepresentation* result = new PlaneSetRepresentation(interp, crs, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PolylineRepresentation* EpcDocument::createPolylineRepresentation(AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed)
{
	PolylineRepresentation* result = new PolylineRepresentation(crs, guid, title, isClosed);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PolylineRepresentation* EpcDocument::createPolylineRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed)
{
	PolylineRepresentation* result = new PolylineRepresentation(interp, crs, guid, title, isClosed);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PolylineRepresentation* EpcDocument::createPolylineRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind, bool isClosed)
{
	PolylineRepresentation* result = new PolylineRepresentation(interp, crs, guid, title, roleKind, isClosed);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

Grid2dRepresentation* EpcDocument::createGrid2dRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title)
{
	Grid2dRepresentation* result = new Grid2dRepresentation(interp, crs, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

WellboreTrajectoryRepresentation* EpcDocument::createWellboreTrajectoryRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, MdDatum * mdInfo)
{
	WellboreTrajectoryRepresentation* result = new WellboreTrajectoryRepresentation(interp, guid, title, mdInfo);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

WellboreFrameRepresentation* EpcDocument::createWellboreFrameRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	WellboreFrameRepresentation* result = new WellboreFrameRepresentation(interp, guid, title, traj);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

WellboreMarkerFrameRepresentation* EpcDocument::createWellboreMarkerFrameRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	WellboreMarkerFrameRepresentation* result = new WellboreMarkerFrameRepresentation(interp, guid, title, traj);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

BlockedWellboreRepresentation* EpcDocument::createBlockedWellboreRepresentation(WellboreInterpretation* interp,
	const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	BlockedWellboreRepresentation* result = new BlockedWellboreRepresentation(interp, guid, title, traj);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

RepresentationSetRepresentation* EpcDocument::createRepresentationSetRepresentation(
        AbstractOrganizationInterpretation* interp,
        const std::string & guid,
        const std::string & title)
{
	RepresentationSetRepresentation* result = new RepresentationSetRepresentation(interp, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

RepresentationSetRepresentation* EpcDocument::createRepresentationSetRepresentation(
	const std::string & guid,
	const std::string & title)
{
	RepresentationSetRepresentation* result = new RepresentationSetRepresentation(this, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

NonSealedSurfaceFrameworkRepresentation* EpcDocument::createNonSealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp, 
        const std::string & guid,
        const std::string & title,
        const bool & isSealed)
{
	NonSealedSurfaceFrameworkRepresentation* result = new NonSealedSurfaceFrameworkRepresentation(interp, guid, title, isSealed);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

SealedSurfaceFrameworkRepresentation* EpcDocument::createSealedSurfaceFrameworkRepresentation(
        StructuralOrganizationInterpretation* interp,
        const std::string & guid,
        const std::string & title)
{
	SealedSurfaceFrameworkRepresentation* result = new SealedSurfaceFrameworkRepresentation(interp, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

AbstractIjkGridRepresentation* EpcDocument::createPartialIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	AbstractIjkGridRepresentation* result = new AbstractIjkGridRepresentation(dor);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

IjkGridExplicitRepresentation* EpcDocument::createIjkGridExplicitRepresentation(AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridExplicitRepresentation* result = new IjkGridExplicitRepresentation(getGsoapContext(), crs, guid, title, iCount, jCount, kCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

IjkGridExplicitRepresentation* EpcDocument::createIjkGridExplicitRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridExplicitRepresentation* result = new IjkGridExplicitRepresentation(interp, crs, guid, title, iCount, jCount, kCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

IjkGridParametricRepresentation* EpcDocument::createIjkGridParametricRepresentation(AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridParametricRepresentation* result = new IjkGridParametricRepresentation(getGsoapContext(), crs, guid, title, iCount, jCount, kCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

IjkGridParametricRepresentation* EpcDocument::createIjkGridParametricRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridParametricRepresentation* result = new IjkGridParametricRepresentation(interp, crs, guid, title, iCount, jCount, kCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

IjkGridLatticeRepresentation* EpcDocument::createIjkGridLatticeRepresentation(AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridLatticeRepresentation* result = new IjkGridLatticeRepresentation(getGsoapContext(), crs, guid, title, iCount, jCount, kCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

IjkGridLatticeRepresentation* EpcDocument::createIjkGridLatticeRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	IjkGridLatticeRepresentation* result = new IjkGridLatticeRepresentation(interp, crs, guid, title, iCount, jCount, kCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

UnstructuredGridRepresentation* EpcDocument::createPartialUnstructuredGridRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	UnstructuredGridRepresentation* result = new UnstructuredGridRepresentation(dor);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

UnstructuredGridRepresentation* EpcDocument::createUnstructuredGridRepresentation(AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const ULONG64 & cellCount)
{
	UnstructuredGridRepresentation* result = new UnstructuredGridRepresentation(getGsoapContext(), crs, guid, title, cellCount);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::SubRepresentation* EpcDocument::createPartialSubRepresentation(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	SubRepresentation* result = new SubRepresentation(dor);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

SubRepresentation* EpcDocument::createSubRepresentation(const std::string & guid, const std::string & title, AbstractRepresentation * supportingRep)
{
	SubRepresentation* result = new SubRepresentation(guid, title, supportingRep);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

SubRepresentation* EpcDocument::createSubRepresentation(AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, AbstractRepresentation * supportingRep)
{
	SubRepresentation* result = new SubRepresentation(interp, guid, title, supportingRep);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::GridConnectionSetRepresentation* EpcDocument::createGridConnectionSetRepresentation(const std::string & guid, const std::string & title)
{
	GridConnectionSetRepresentation* result = new GridConnectionSetRepresentation(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

GridConnectionSetRepresentation* EpcDocument::createGridConnectionSetRepresentation(AbstractFeatureInterpretation* interp,
        const std::string & guid, const std::string & title)
{
	GridConnectionSetRepresentation* result = new GridConnectionSetRepresentation(interp, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

//************************************
//************* PROPERTIES ***********
//************************************

TimeSeries* EpcDocument::createTimeSeries(const std::string & guid, const std::string & title)
{
	TimeSeries* result = new TimeSeries(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::TimeSeries* EpcDocument::createPartialTimeSeries(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	TimeSeries* result = new TimeSeries(dor);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

StringTableLookup* EpcDocument::createStringTableLookup(const std::string & guid, const std::string & title)
{
	StringTableLookup* result = new StringTableLookup(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PropertyKind* EpcDocument::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	PropertyKind* result = new PropertyKind(getGsoapContext(), guid, title, namingSystem, uom, parentEnergisticsPropertyKind);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

PropertyKind* EpcDocument::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, PropertyKind * parentPropType)
{
	PropertyKind* result = new PropertyKind(getGsoapContext(), guid, title, namingSystem, uom, parentPropType);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

resqml2_0_1::PropertyKind* EpcDocument::createPartialPropertyKind(const std::string & guid, const std::string & title)
{
	eml__DataObjectReference* dor = soap_new_eml__DataObjectReference(s, 1);
	dor->UUID = guid;
	dor->Title = title;
	PropertyKind* result = new PropertyKind(dor);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

CommentProperty* EpcDocument::createCommentProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	CommentProperty* result = new CommentProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

CommentProperty* EpcDocument::createCommentProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, PropertyKind * localPropType)
{
	CommentProperty* result = new CommentProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}
	
ContinuousProperty* EpcDocument::createContinuousProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	ContinuousProperty* result = new ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

ContinuousProperty* EpcDocument::createContinuousProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, PropertyKind * localPropType)
{
	ContinuousProperty* result = new ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, localPropType);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

ContinuousPropertySeries* EpcDocument::createContinuousPropertySeries(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	TimeSeries * ts, const bool & useInterval)
{
	ContinuousPropertySeries* result = new ContinuousPropertySeries(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind, ts, useInterval);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

ContinuousPropertySeries* EpcDocument::createContinuousPropertySeries(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, PropertyKind * localPropType,
	class TimeSeries * ts, const bool & useInterval)
{
	ContinuousPropertySeries* result = new ContinuousPropertySeries(rep, guid, title, dimension, attachmentKind, uom, localPropType, ts, useInterval);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}
	
DiscreteProperty* EpcDocument::createDiscreteProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	DiscreteProperty* result = new DiscreteProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

DiscreteProperty* EpcDocument::createDiscreteProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, PropertyKind * localPropType)
{
	DiscreteProperty* result = new DiscreteProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}
	
DiscretePropertySeries* EpcDocument::createDiscretePropertySeries(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	class TimeSeries * ts, const bool & useInterval)
{
	DiscretePropertySeries* result = new DiscretePropertySeries(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind, ts, useInterval);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

DiscretePropertySeries* EpcDocument::createDiscretePropertySeries(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, PropertyKind * localPropType,
	class TimeSeries * ts, const bool & useInterval)
{
	DiscretePropertySeries* result = new DiscretePropertySeries(rep, guid, title, dimension, attachmentKind, localPropType, ts, useInterval);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

CategoricalProperty* EpcDocument::createCategoricalProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	CategoricalProperty* result = new CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}
	
CategoricalProperty* EpcDocument::createCategoricalProperty(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, PropertyKind * localPropType)
{
	CategoricalProperty* result = new CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, localPropType);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

CategoricalPropertySeries* EpcDocument::createCategoricalPropertySeries(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	class TimeSeries * ts, const bool & useInterval)
{
	CategoricalPropertySeries* result = new CategoricalPropertySeries(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind, ts, useInterval);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

CategoricalPropertySeries* EpcDocument::createCategoricalPropertySeries(AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, PropertyKind * localPropType,
	class TimeSeries * ts, const bool & useInterval)
{
	CategoricalPropertySeries* result = new CategoricalPropertySeries(rep, guid, title, dimension, attachmentKind, strLookup, localPropType, ts, useInterval);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

//************************************
//************* ACTIVITIES ***********
//************************************

ActivityTemplate* EpcDocument::createActivityTemplate(const std::string & guid, const std::string & title)
{
	ActivityTemplate* result = new ActivityTemplate(getGsoapContext(), guid, title);
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}
		
Activity* EpcDocument::createActivity(resqml2::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title)
{
	Activity* result = new Activity(activityTemplate, guid, title);
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
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
	addGsoapProxyAndDeleteItIfException(result);
	return result;
}

void common::EpcDocument::set_hdf_proxy_builder(HdfProxyBuilder builder)
{
  make_hdf_proxy = builder;
}

void common::EpcDocument::set_hdf_proxy_builder(HdfProxyBuilderFromSOAP builder)
{
  make_hdf_proxy_from_soap = builder;
}
