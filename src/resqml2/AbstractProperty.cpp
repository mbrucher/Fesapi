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
#include "resqml2/AbstractProperty.h"

#include <stdexcept>

#include "resqml2/SubRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2/PropertyKind.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2/TimeSeries.h"
#include "resqml2_0_1/PropertyKindMapper.h"

using namespace resqml2;
using namespace std;
using namespace epc;


void AbstractProperty::setXmlRepresentation(resqml2::AbstractRepresentation * rep)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation = rep->newResqmlReference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setXmlTimeSeries(TimeSeries * ts)
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr) {
				static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			}
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries)
		{
			if (static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
		else
		{
			if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
				static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries = ts->newResqmlReference();
			}
			else {
				throw invalid_argument("The time series cannot be set on a property without time indices.");
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setXmlLocalPropertyKind(class PropertyKind* propKind)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__LocalPropertyKind* xmlLocalPropKind = gsoap_resqml2_0_1::soap_new_resqml2__LocalPropertyKind(gsoapProxy2_0_1->soap, 1);
		xmlLocalPropKind->LocalPropertyKind = propKind->newResqmlReference();
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlLocalPropKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

vector<Relationship> AbstractProperty::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	AbstractRepresentation* representation = getRepresentation();
	Relationship relRep(representation->getPartNameInEpcDocument(), "", representation->getUuid());
	relRep.setDestinationObjectType();
	result.push_back(relRep);

	if (local3dCrs != nullptr)
	{
		Relationship relCrs(local3dCrs->getPartNameInEpcDocument(), "", local3dCrs->getUuid());
		relCrs.setDestinationObjectType();
		result.push_back(relCrs);
	}

	TimeSeries* timeSeries = getTimeSeries();
	if (timeSeries != nullptr)
	{
		Relationship relTs(timeSeries->getPartNameInEpcDocument(), "", timeSeries->getUuid());
		relTs.setDestinationObjectType();
		result.push_back(relTs);
	}

	AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy != nullptr)
	{
		Relationship relHdf(hdfProxy->getPartNameInEpcDocument(), "", hdfProxy->getUuid());
		relHdf.setMlToExternalPartProxyType();
		result.push_back(relHdf);
	}

	if (isAssociatedToOneStandardEnergisticsPropertyKind() == false)
	{
		PropertyKind* pk = getLocalPropertyKind();
		if (pk != nullptr)
		{
			Relationship relPropType(pk->getPartNameInEpcDocument(), "", pk->getUuid());
			relPropType.setDestinationObjectType();
			result.push_back(relPropType);
		}
	}

	return result;
}

void AbstractProperty::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	string uuidRep = getRepresentationUuid();
	string titleRep = getRepresentationTitle();
	string ctRep = getRepresentationContentType();
	resqml2::AbstractRepresentation* rep = epcDoc->getResqmlAbstractObjectByUuid<AbstractRepresentation>(uuidRep);
	if (rep == nullptr) // partial transfer
	{
		epcDoc->addWarning("The referenced grid \"" + titleRep + "\" (" + uuidRep + ") is missing.");
		if (ctRep.find(resqml2_0_1::UnstructuredGridRepresentation::XML_TAG) != string::npos) {
			rep = epcDoc->createPartialUnstructuredGridRepresentation(uuidRep, titleRep);
		}
		else if (ctRep.find(resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG) != string::npos) {
			rep = epcDoc->createPartialIjkGridRepresentation(uuidRep, titleRep);
		}
		else if (ctRep.find(resqml2::SubRepresentation::XML_TAG) != string::npos) {
			rep = epcDoc->createPartialSubRepresentation(uuidRep, titleRep);
		}
		else {
			throw logic_error("The partial supporting representation of property " + getTitle() + " is not supported yet.");
		}
	}
	updateXml = false;
	setRepresentation(static_cast<resqml2::AbstractRepresentation*>(rep));
	updateXml = true;

	string uuidTimeSeries = getTimeSeriesUuid();
	string titleTimeSeries = getTimeSeriesTitle();
	if (!uuidTimeSeries.empty())
	{
		resqml2::TimeSeries* ts = epcDoc->getResqmlAbstractObjectByUuid<TimeSeries>(uuidTimeSeries);
		if (ts == nullptr) {
			epcDoc->addWarning("The referenced time series \"" + titleTimeSeries + "\" (" + uuidTimeSeries + ") is missing.");
			ts = epcDoc->createPartialTimeSeries(uuidTimeSeries, titleTimeSeries);
		}
		updateXml = false;
		setTimeSeries(static_cast<resqml2::TimeSeries*>(ts));
		updateXml = true;
	}

	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		string uuidLocalPropertyKind = getLocalPropertyKindUuid();
		string titleLocalPropertyKind = getLocalPropertyKindTitle();
		resqml2::PropertyKind* pk = epcDoc->getResqmlAbstractObjectByUuid<PropertyKind>(uuidLocalPropertyKind);
		if (pk == nullptr) {
			epcDoc->addWarning("The referenced local property kind \"" + titleLocalPropertyKind + "\" (" + uuidLocalPropertyKind + ") is missing.");
			pk = epcDoc->createPartialPropertyKind(uuidLocalPropertyKind, titleLocalPropertyKind);
		}
		else {
			if (pk->isAbstract()) {
				throw invalid_argument("A property cannot be associated to a local property kind which is abstract.");
			}
			if (epcDocument->getPropertyKindMapper() != nullptr) {
				if (!pk->isChildOf(getFirstAllowedPropertyKindParent())) {
					throw invalid_argument("A property cannot be associated to a local property kind which does not derive from the main kind (i.e discret, categorical or continuous) of the property.");
				}
			}
			else {
				epcDoc->addWarning("Cannot verify if the parent property kind of the property is right because no property kind mapping files have been loaded.");
			}
		}
		updateXml = false;
		setLocalPropertyKind(static_cast<resqml2::PropertyKind*>(pk));
		updateXml = true;
	}
	else {
		if (epcDocument->getPropertyKindMapper() != nullptr) {
			if (epcDocument->getPropertyKindMapper()->isAbstract(getEnergisticsPropertyKind())) {
				throw invalid_argument("A property cannot be associated to a resqml property kind which is abstract.");
			}
			if (!epcDocument->getPropertyKindMapper()->isChildOf(getEnergisticsPropertyKind(), getFirstAllowedPropertyKindParent())) {
				throw invalid_argument("A property cannot be associated to a resqml property kind which does not derive from the main kind (i.e discret, categorical or continuous) of the property.");
			}
		}
		else {
			epcDoc->addWarning("Cannot verify if the resqml property kind is abstract or not because no property kind mapping files have been loaded.");
		}
	}

	string uuidHdfProxy = getHdfProxyUuid();
	if (!uuidHdfProxy.empty()) {
		resqml2::AbstractHdfProxy* hdfProxy = epcDoc->getResqmlAbstractObjectByUuid<AbstractHdfProxy>(uuidHdfProxy);
		if (hdfProxy == nullptr) {
			epcDoc->addWarning("The referenced hdf proxy (" + uuidHdfProxy + ") is missing.");
		}
		updateXml = false;
		setHdfProxy(static_cast<resqml2::AbstractHdfProxy*>(hdfProxy));
		updateXml = true;
	}
}

void AbstractProperty::setRepresentation(AbstractRepresentation * rep)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	// EPC
	rep->propertySet.push_back(this);

	// XML
	if (updateXml) {
		setXmlRepresentation(rep);
	}
}

AbstractRepresentation* AbstractProperty::getRepresentation() const
{
	return static_cast<AbstractRepresentation*>(epcDocument->getResqmlAbstractObjectByUuid(getRepresentationUuid()));
}

std::string AbstractProperty::getRepresentationUuid() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation->UUID;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractProperty::getRepresentationTitle() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation->Title;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractProperty::getRepresentationContentType() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation->ContentType;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

TimeSeries* AbstractProperty::getTimeSeries() const
{
	return static_cast<TimeSeries*>(epcDocument->getResqmlAbstractObjectByUuid(getTimeSeriesUuid()));
}

void AbstractProperty::setTimeSeries(TimeSeries * ts)
{
	if (ts == nullptr) {
		throw invalid_argument("The time series of this property values cannot be null.");
	}

	// EPC
	ts->propertySet.push_back(this);

	// XML
	if (updateXml) {
		setXmlTimeSeries(ts);
	}
}

std::string AbstractProperty::getTimeSeriesUuid() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID;
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries) {
			if (static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				return static_cast<gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID;
		}
		else {
			if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
				return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries->UUID;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return "";
}


std::string AbstractProperty::getTimeSeriesTitle() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
			return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries->Title;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return "";
}

void AbstractProperty::setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex = gsoap_resqml2_0_1::soap_new_resqml2__TimeIndex(gsoapProxy2_0_1->soap, 1);
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index = timeIndex;
	}
	else {
		throw logic_error("Not implemented yet");
	}

	setTimeSeries(ts);
}

void AbstractProperty::setTimeStep(const unsigned int & timeStep)
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep == nullptr) {
			static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		}
		*(static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep) = timeStep;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

time_t AbstractProperty::getTimestamp() const
{
	TimeSeries* timeSeries = getTimeSeries();

	if (gsoapProxy2_0_1 != nullptr) {
		if (timeSeries && static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
			return timeSeries->getTimestamp(static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index);
		}
		else {
			throw invalid_argument("This property does not have any timestamp.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int AbstractProperty::getTimeIndex() const
{
	TimeSeries* timeSeries = getTimeSeries();

	if (gsoapProxy2_0_1 != nullptr) {
		if (timeSeries && static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex) {
			return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index;
		}
		else {
			throw invalid_argument("This property does not have any timestamp.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractProperty::setHdfProxy(resqml2::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		throw invalid_argument("The hdf proxy cannot be null");
	}

	proxy->propertySourceObject.push_back(this);
}

AbstractHdfProxy* AbstractProperty::getHdfProxy() const
{
	return static_cast<AbstractHdfProxy*>(epcDocument->getResqmlAbstractObjectByUuid(getHdfProxyUuid()));
}

std::string AbstractProperty::getHdfProxyUuid() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPointsProperty)
		{
			gsoap_resqml2_0_1::_resqml2__PointsProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml2__PointsProperty*>(gsoapProxy2_0_1);
			gsoap_resqml2_0_1::resqml2__PatchOfPoints* firstPatch = prop->PatchOfPoints[0];

			int valuesType = firstPatch->Points->soap_type();
			if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__Point3dHdf5Array*>(firstPatch->Points)->Coordinates->HdfProxy->UUID;
			}
			else {
				return "";
			}
		}
		else {
			gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);
			gsoap_resqml2_0_1::resqml2__PatchOfValues* firstPatch = prop->PatchOfValues[0];

			int valuesType = firstPatch->Values->soap_type();
			if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__BooleanHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringHdf5Array) {
				return static_cast<gsoap_resqml2_0_1::resqml2__StringHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
			}
			else {
				return "";
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return "";
}

unsigned int AbstractProperty::getElementCountPerValue() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->Count;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml2__IndexableElements AbstractProperty::getAttachmentKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->IndexableElement;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractProperty::isAssociatedToOneStandardEnergisticsPropertyKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StandardPropertyKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractProperty::getPropertyKindDescription() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (epcDocument->getPropertyKindMapper() != nullptr) {
			return epcDocument->getPropertyKindMapper()->getDescriptionOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
		}
		else {
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
		}
	}
	else {
		return getLocalPropertyKind()->getDescription();
	}
}

std::string AbstractProperty::getPropertyKindAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		return epcDocument->getEnergisticsPropertyKindName(getEnergisticsPropertyKind());
	}
	else {
		return getLocalPropertyKind()->getTitle();
	}
}

std::string AbstractProperty::getPropertyKindParentAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if (epcDocument->getPropertyKindMapper() != nullptr) {
			gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind propKindEnum = epcDocument->getPropertyKindMapper()->getPropertyKindParentOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
			return epcDocument->getEnergisticsPropertyKindName(propKindEnum);
		}
		else {
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
		}
	}
	else {
		return getLocalPropertyKind()->getParentAsString();
	}
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind AbstractProperty::getEnergisticsPropertyKind() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml2__StandardPropertyKind*>(prop->PropertyKind)->Kind;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
	
	throw invalid_argument("The property kind of this property is not an Energistics one.");
}

void AbstractProperty::setLocalPropertyKind(PropertyKind* propKind)
{
	if (propKind == nullptr) {
		throw invalid_argument("The local property kind of this property cannot be null.");
	}

	// EPC
	propKind->propertySet.push_back(this);

	// XML
	if (updateXml)
	{
		setXmlLocalPropertyKind(propKind);
	}
}

std::string AbstractProperty::getLocalPropertyKindUuid() const
{
	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml2__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind->UUID;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
	
	throw invalid_argument("The property kind of this property is not a local one.");
}

std::string AbstractProperty::getLocalPropertyKindTitle() const
{
	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__AbstractProperty* prop = static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml2__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind->Title;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
	
	throw invalid_argument("The property kind of this property is not a local one.");
}

PropertyKind* AbstractProperty::getLocalPropertyKind() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind() == false)
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__LocalPropertyKind* xmlLocalPropertyKind = static_cast<gsoap_resqml2_0_1::resqml2__LocalPropertyKind*>(static_cast<gsoap_resqml2_0_1::resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind);
			return static_cast<PropertyKind*>(getEpcDocument()->getResqmlAbstractObjectByUuid(xmlLocalPropertyKind->LocalPropertyKind->UUID));
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
	
	throw invalid_argument("The property kind of this property is not a local one.");
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind AbstractProperty::getFirstAllowedPropertyKindParent() const
{
	return gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__RESQML_x0020root_x0020property;
}
