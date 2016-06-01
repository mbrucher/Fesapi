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
#include "resqml2_0_1/AbstractProperty.h"

#include <stdexcept>

#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2_0_1/TimeSeries.h"
#include "resqml2_0_1/PropertyKindMapper.h"

using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;
using namespace std;
using namespace epc;

vector<Relationship> AbstractProperty::getAllEpcRelationships() const
{
	resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1);

	vector<Relationship> result;

	// XML forward relationship
	if (representation)
	{
		Relationship relRep(representation->getPartNameInEpcDocument(), "", prop->SupportingRepresentation->UUID);
		relRep.setDestinationObjectType();
		result.push_back(relRep);
	}
	else
		throw domain_error("The representation associated to the interpretation cannot be nullptr.");

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

	if (local3dCrs)
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

	if (hdfProxy != nullptr)
	{
		Relationship relHdf(hdfProxy->getPartNameInEpcDocument(), "", hdfProxy->getUuid());
		relHdf.setMlToExternalPartProxyType();
		result.push_back(relHdf);
	}

	return result;
}

void AbstractProperty::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1);

	updateXml = false;
	AbstractRepresentation* rep = static_cast<AbstractRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(prop->SupportingRepresentation->UUID));
	if (rep == nullptr) // partial transfer
	{
		epcDoc->addWarning("The referenced grid \"" + prop->SupportingRepresentation->Title + "\" (" + prop->SupportingRepresentation->UUID + ") is missing.");
		if (prop->SupportingRepresentation->ContentType.find(UnstructuredGridRepresentation::XML_TAG) != string::npos) {
			rep = epcDoc->createPartialUnstructuredGridRepresentation(prop->SupportingRepresentation->UUID, prop->SupportingRepresentation->Title);
		}
		else if (prop->SupportingRepresentation->ContentType.find(AbstractIjkGridRepresentation::XML_TAG) != string::npos) {
			rep = epcDoc->createPartialIjkGridRepresentation(prop->SupportingRepresentation->UUID, prop->SupportingRepresentation->Title);
		}
		else if (prop->SupportingRepresentation->ContentType.find(SubRepresentation::XML_TAG) != string::npos) {
			rep = epcDoc->createPartialSubRepresentation(prop->SupportingRepresentation->UUID, prop->SupportingRepresentation->Title);
		}
		else {
			throw logic_error("The partial supporting representation of property " + getTitle() + " is not supported yet.");
		}
	}
	setRepresentation(rep);
	updateXml = true;

	if (prop->TimeIndex != nullptr)
	{
		updateXml = false;
		TimeSeries* ts = static_cast<TimeSeries*>(epcDoc->getResqmlAbstractObjectByUuid(prop->TimeIndex->TimeSeries->UUID));
		if (ts == nullptr)
		{
			epcDoc->addWarning("The referenced time series \"" + prop->TimeIndex->TimeSeries->Title + "\" (" + prop->TimeIndex->TimeSeries->UUID + ") is missing.");
			ts = epcDoc->createPartialTimeSeries(prop->TimeIndex->TimeSeries->UUID, prop->SupportingRepresentation->Title);
		}
		setTimeSeries(ts);
		updateXml = true;
	}

	if (prop->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__LocalPropertyKind)
	{
		updateXml = false;
		resqml2__LocalPropertyKind* xmlLocalPropertyKind = static_cast<resqml2__LocalPropertyKind*>(prop->PropertyKind);
		PropertyKind* pk = static_cast<PropertyKind*>(epcDoc->getResqmlAbstractObjectByUuid(xmlLocalPropertyKind->LocalPropertyKind->UUID));
		if (pk == nullptr)
		{
			epcDoc->addWarning("The referenced local property kind \"" + xmlLocalPropertyKind->LocalPropertyKind->Title + "\" (" + xmlLocalPropertyKind->LocalPropertyKind->UUID + ") is missing.");
			pk = epcDoc->createPartialPropertyKind(xmlLocalPropertyKind->LocalPropertyKind->UUID, prop->SupportingRepresentation->Title);
		}
		setLocalPropertyKind(pk);
		updateXml = true;
	}
}

gsoap_resqml2_0_1::resqml2__IndexableElements AbstractProperty::getAttachmentKind() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->IndexableElement;
}

void AbstractProperty::setRepresentation(AbstractRepresentation * rep)
{
	if (rep == nullptr)
		throw invalid_argument("The representation of this property values cannot be null.");

	// EPC
	representation = rep;
	representation->propertySet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation = rep->newResqmlReference();
	}
}

TimeSeries* AbstractProperty::getTimeSeries() const
{
	if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries)
	{
		if (static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
			return static_cast<TimeSeries*>(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID));
		else
			return nullptr;
	}
	else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries)
	{
		if (static_cast<_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
			return static_cast<TimeSeries*>(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID));
		else
			return nullptr;
	}
	else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries)
	{
		if (static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
			return static_cast<TimeSeries*>(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID));
		else
			return nullptr;
	}
	else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries)
	{
		if (static_cast<_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
			return static_cast<TimeSeries*>(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries->UUID));
		else
			return nullptr;
	}
	else
	{
		if (static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
			return static_cast<TimeSeries*>(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries->UUID));
		else
			return nullptr;
	}
}

void AbstractProperty::setTimeSeries(TimeSeries * ts)
{
	if (ts == nullptr)
		throw invalid_argument("The time series of this property values cannot be null.");

	// EPC
	ts->propertySet.push_back(this);

	// XML
	if (updateXml)
	{
		if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries)
		{
			if (static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries)
		{
			if (static_cast<_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__CommentPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries)
		{
			if (static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries)
		{
			if (static_cast<_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__DiscretePropertySeries*>(gsoapProxy2_0_1)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else
		{
			if (static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
				static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time index.");
		}
	}
}

void AbstractProperty::setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts)
{
	static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex = soap_new_resqml2__TimeIndex(gsoapProxy2_0_1->soap, 1);
	static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index = timeIndex;

	setTimeSeries(ts);
}

time_t AbstractProperty::getTimestamp() const
{
	TimeSeries* timeSeries = getTimeSeries();
	if (timeSeries && static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
	{
		return timeSeries->getTimestamp(static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index);
	}
	else
		throw invalid_argument("This property does not have any timestamp.");
}

unsigned int AbstractProperty::getTimeIndex() const
{
	TimeSeries* timeSeries = getTimeSeries();
	if (timeSeries && static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex)
	{
		return static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeIndex->Index;
	}
	else
		throw invalid_argument("This property does not have any timestamp.");
}

void AbstractProperty::setTimeStep(const unsigned int & timeStep)
{
	if (static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep == nullptr)
		static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->TimeStep) = timeStep;
}

std::string AbstractProperty::getPropertyKindDescription() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind()) {
		if(epcDocument->getPropertyKindMapper())
			return epcDocument->getPropertyKindMapper()->getPropertyKindParentOfResqmlStandardPropertyKindNameAsString(getEnergisticsPropertyKind());
		else
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
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
		if(epcDocument->getPropertyKindMapper())
			return epcDocument->getPropertyKindMapper()->getPropertyKindParentOfResqmlStandardPropertyKindNameAsString(getEnergisticsPropertyKind());
		else
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the parent property kind.");
	}
	else {
		return getLocalPropertyKind()->getParentAsString();
	}
}

bool AbstractProperty::isAssociatedToOneStandardEnergisticsPropertyKind() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StandardPropertyKind;
}

resqml2__ResqmlPropertyKind AbstractProperty::getEnergisticsPropertyKind() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1);
		return static_cast<resqml2__StandardPropertyKind*>(prop->PropertyKind)->Kind;
	}
	else
		throw invalid_argument("The property kind of this property is not an Energistics one.");
}

void AbstractProperty::setLocalPropertyKind(PropertyKind* propKind)
{
	if (propKind == nullptr)
		throw invalid_argument("The local property kind of this property cannot be null.");

	// EPC
	propKind->propertySet.push_back(this);

	// XML
	if (updateXml)
	{
		resqml2__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml2__LocalPropertyKind(gsoapProxy2_0_1->soap, 1);
		xmlLocalPropKind->LocalPropertyKind = propKind->newResqmlReference();
		static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlLocalPropKind;
	}
}

std::string AbstractProperty::getLocalPropertyKindUuid() const
{
	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1);
		return static_cast<resqml2__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind->UUID;
	}
	else
		throw invalid_argument("The property kind of this property is not a local one.");
}

PropertyKind* AbstractProperty::getLocalPropertyKind() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind() == false)
	{
		resqml2__LocalPropertyKind* xmlLocalPropertyKind = static_cast<resqml2__LocalPropertyKind*>(static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->PropertyKind);
		return static_cast<PropertyKind*>(getEpcDocument()->getResqmlAbstractObjectByUuid(xmlLocalPropertyKind->LocalPropertyKind->UUID));
	}
	else
		throw invalid_argument("The property kind of this property is not a local one.");
}

unsigned int AbstractProperty::getElementCountPerValue() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->Count;
}

std::string AbstractProperty::getRepresentationUuid() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy2_0_1)->SupportingRepresentation->UUID;
}

void AbstractProperty::setHdfProxy(resqml2::AbstractHdfProxy * proxy)
{
	if (!hdfProxy)
	{
		hdfProxy = proxy;
		proxy->propertySourceObject.push_back(this);
	}
}

std::string AbstractProperty::getHdfProxyUuid() const
{
	if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__AbstractValuesProperty)
	{
		resqml2__AbstractValuesProperty* prop = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy2_0_1);
		resqml2__PatchOfValues* firstPatch = prop->PatchOfValues[0];

		int valuesType = firstPatch->Values->soap_type();
		/*if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
		{
			return static_cast<resqml2__BooleanHdf5Array*>(prop->Values)->Values->HdfProxy->uuid;
		}
		else */if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
		{
			return static_cast<resqml2__DoubleHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
		}
		else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			return static_cast<resqml2__IntegerHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID;
		}
		else
			return "";
	}
	else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPointsProperty)
	{
		_resqml2__PointsProperty* prop = static_cast<_resqml2__PointsProperty*>(gsoapProxy2_0_1);
		resqml2__PatchOfPoints* firstPatch = prop->PatchOfPoints[0];
		
		int valuesType = firstPatch->Points->soap_type();
		if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
		{
			return static_cast<resqml2__Point3dHdf5Array*>(firstPatch->Points)->Coordinates->HdfProxy->UUID;
		}
		else
			return "";
	}
	else
		return "";
}
