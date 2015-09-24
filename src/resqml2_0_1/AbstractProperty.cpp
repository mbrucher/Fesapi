/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2015) 

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

#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractHdfProxy.h"
#include "resqml2_0_1/TimeSeries.h"
#include "resqml2_0_1/PropertyKindMapper.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;
using namespace std;
using namespace epc;

vector<Relationship> AbstractProperty::getAllEpcRelationships() const
{
	resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy);

	vector<Relationship> result;

	// XML forward relationship
	if (representation)
	{
		Relationship relRep(representation->getPartNameInEpcDocument(), "", prop->SupportingRepresentation->UUID);
		relRep.setDestinationObjectType();
		result.push_back(relRep);
	}
	else
		throw domain_error("The representation associated to the interpretation cannot be NULL.");

	if (localPropertyKind)
	{
		Relationship relPropType(localPropertyKind->getPartNameInEpcDocument(), "", localPropertyKind->getUuid());
		relPropType.setDestinationObjectType();
		result.push_back(relPropType);
	}

	if (local3dCrs)
	{
		Relationship relCrs(local3dCrs->getPartNameInEpcDocument(), "", local3dCrs->getUuid());
		relCrs.setDestinationObjectType();
		result.push_back(relCrs);
	}

	if (timeSeries)
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
	resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy);

	updateXml = false;
	AbstractRepresentation* rep = static_cast<AbstractRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(prop->SupportingRepresentation->UUID));
	if (rep == nullptr) // partial transfer
	{
		getEpcDocument()->addWarning("The referenced grid \"" + prop->SupportingRepresentation->Title + "\" (" + prop->SupportingRepresentation->UUID + ") is missing.");
		if (prop->SupportingRepresentation->ContentType.find("UnstructuredGridRepresentation") != 0)
			rep = new UnstructuredGridRepresentation(getEpcDocument(), prop->SupportingRepresentation->UUID, prop->SupportingRepresentation->Title);
		else if (prop->SupportingRepresentation->ContentType.find("IjkGridRepresentation") != 0)
			rep = new AbstractIjkGridRepresentation(getEpcDocument(), prop->SupportingRepresentation->UUID, prop->SupportingRepresentation->Title);
	}
	setRepresentation(rep);
	updateXml = true;

	if (prop->TimeIndex)
	{
		updateXml = false;
		setTimeSeries(static_cast<TimeSeries*>(epcDoc->getResqmlAbstractObjectByUuid(prop->TimeIndex->TimeSeries->UUID)));
		updateXml = true;
	}

	if (prop->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__LocalPropertyKind)
	{
		resqml2__LocalPropertyKind* xmlLocalPropertyKind = static_cast<resqml2__LocalPropertyKind*>(prop->PropertyKind);
		localPropertyKind = static_cast<PropertyKind*>(epcDoc->getResqmlAbstractObjectByUuid(xmlLocalPropertyKind->LocalPropertyKind->UUID));
		if( localPropertyKind != nullptr ) // In case of partial transfer, it is possible the local property kind is not in the EPC document.
		{
			localPropertyKind->addProperty(this);
		}
	}
}

std::string AbstractProperty::getPropertyKindUomAsString() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind() == false)
	{
		return getLocalPropertyKind()->getUomAsString();
	}
	else if(epcDocument->getPropertyKindMapper() != NULL)
	{
		return epcDocument->getPropertyKindMapper()->getUomOfResqmlStandardPropertyKindName(getEnergisticsPropertyKind());
	}
	else
		throw std::invalid_argument("You must load the property kind mapping files if you want to get the uom.");
}

gsoap_resqml2_0_1::resqml2__IndexableElements AbstractProperty::getAttachmentKind() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy)->IndexableElement;
}

void AbstractProperty::setRepresentation(AbstractRepresentation * rep)
{
	if (!rep)
		throw invalid_argument("The representation of this property values cannot be null.");

	// EPC
	representation = rep;
	representation->propertySet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<resqml2__AbstractProperty*>(gsoapProxy)->SupportingRepresentation = rep->newResqmlReference();
	}
}

void AbstractProperty::setTimeSeries(TimeSeries * ts)
{
	if (!ts)
		throw invalid_argument("The time series of this property values cannot be null.");

	// EPC
	timeSeries = ts;
	timeSeries->propertySet.push_back(this);

	// XML
	if (updateXml)
	{
		if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalPropertySeries)
		{
			if (static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentPropertySeries)
		{
			if (static_cast<_resqml2__CommentPropertySeries*>(gsoapProxy)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__CommentPropertySeries*>(gsoapProxy)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousPropertySeries)
		{
			if (static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscretePropertySeries)
		{
			if (static_cast<_resqml2__DiscretePropertySeries*>(gsoapProxy)->SeriesTimeIndices != nullptr)
				static_cast<_resqml2__DiscretePropertySeries*>(gsoapProxy)->SeriesTimeIndices->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time indices.");
		}
		else
		{
			if (static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex)
				static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex->TimeSeries = ts->newResqmlReference();
			else
				throw invalid_argument("The time series cannot be set on a property without time index.");
		}
	}
}

void AbstractProperty::setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts)
{
	static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex = soap_new_resqml2__TimeIndex(gsoapProxy->soap, 1);
	static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex->Index = timeIndex;

	setTimeSeries(ts);
}

time_t AbstractProperty::getTimestamp() const
{
	if (timeSeries && static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex)
	{
		return timeSeries->getTimestamp(static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex->Index);
	}
	else
		throw invalid_argument("This property does not have any timestamp.");
}

unsigned int AbstractProperty::getTimeIndex() const
{
	if (timeSeries && static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex)
	{
		return static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeIndex->Index;
	}
	else
		throw invalid_argument("This property does not have any timestamp.");
}

void AbstractProperty::setTimeStep(const unsigned int & timeStep)
{
	if (static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeStep == NULL)
		static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeStep = static_cast<ULONG64*>(soap_malloc(gsoapProxy->soap, sizeof(ULONG64)));
	*(static_cast<resqml2__AbstractProperty*>(gsoapProxy)->TimeStep) = timeStep;
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
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy)->PropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StandardPropertyKind;
}

resqml2__ResqmlPropertyKind AbstractProperty::getEnergisticsPropertyKind() const
{
	if (isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy);
		return static_cast<resqml2__StandardPropertyKind*>(prop->PropertyKind)->Kind;
	}
	else
		throw invalid_argument("The property kind of this property is not an Energistics one.");
}

std::string AbstractProperty::getLocalPropertyKindUuid() const
{
	if (!isAssociatedToOneStandardEnergisticsPropertyKind())
	{
		resqml2__AbstractProperty* prop = static_cast<resqml2__AbstractProperty*>(gsoapProxy);
		return static_cast<resqml2__LocalPropertyKind*>(prop->PropertyKind)->LocalPropertyKind->UUID;
	}
	else
		throw invalid_argument("The property kind of this property is not a local one.");
}

unsigned int AbstractProperty::getElementCountPerValue() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy)->Count;
}

std::string AbstractProperty::getRepresentationUuid() const
{
	return static_cast<resqml2__AbstractProperty*>(gsoapProxy)->SupportingRepresentation->UUID;
}

void AbstractProperty::setHdfProxy(AbstractHdfProxy * proxy)
{
	if (!hdfProxy)
	{
		hdfProxy = proxy;
		proxy->propertySourceObject.push_back(this);
	}
}

std::string AbstractProperty::getHdfProxyUuid() const
{
	if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__AbstractValuesProperty)
	{
		resqml2__AbstractValuesProperty* prop = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy);
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
	else if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPointsProperty)
	{
		_resqml2__PointsProperty* prop = static_cast<_resqml2__PointsProperty*>(gsoapProxy);
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
