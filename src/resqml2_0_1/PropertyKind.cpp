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
#include "resqml2_0_1/PropertyKind.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractValuesProperty.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* PropertyKind::XML_TAG = "PropertyKind";

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
			const string & namingSystem, const resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind):
	parentPropertyKind(nullptr)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPropertyKind(soapContext, 1);
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();
	
	propType->NamingSystem = namingSystem;
	propType->RepresentativeUom = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	propType->ParentPropertyKind = xmlStandardPropKind;
	
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
			const string & namingSystem, const resqml2__ResqmlUom & uom, PropertyKind * parentPropType):
	parentPropertyKind(parentPropType)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPropertyKind(soapContext, 1);
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();
	
	propType->NamingSystem = namingSystem;
	propType->RepresentativeUom = uom;

	resqml2__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml2__LocalPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlLocalPropKind->LocalPropertyKind = parentPropType->newResqmlReference();
	propType->ParentPropertyKind = xmlLocalPropKind;
	
	parentPropType->childPropertyKind.push_back(this);
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

_resqml2__PropertyKind* PropertyKind::getSpecializedGsoapProxy() const
{
	if (isPartial() == true)
		throw logic_error("Partial object");

	return static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1);
}

const std::string & PropertyKind::getNamingSystem() const
{
	return getSpecializedGsoapProxy()->NamingSystem;
}

const resqml2__ResqmlUom & PropertyKind::getUom() const
{
	return getSpecializedGsoapProxy()->RepresentativeUom;
}

std::string PropertyKind::getUomAsString() const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlUom2s(gsoapProxy2_0_1->soap, getUom());
}

vector<Relationship> PropertyKind::getAllEpcRelationships() const
{
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();

	vector<Relationship> result;

	// forward relationships
	if (parentPropertyKind)
	{
		Relationship rel(parentPropertyKind->getPartNameInEpcDocument(), "", static_cast<resqml2__LocalPropertyKind*>(propType->ParentPropertyKind)->LocalPropertyKind->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	// backwards relationships
	for (unsigned int i = 0; i < propertySet.size(); i++)
	{
		Relationship rel(propertySet[i]->getPartNameInEpcDocument(), "", propertySet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (unsigned int i = 0; i < childPropertyKind.size(); i++)
	{
		Relationship rel(childPropertyKind[i]->getPartNameInEpcDocument(), "", childPropertyKind[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

std::string PropertyKind::getParentAsString() const
{
	if (parentPropertyKind)
		return parentPropertyKind->getTitle();
	else
	{
		_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();
		return epcDocument->getEnergisticsPropertyKindName(static_cast<resqml2__StandardPropertyKind*>(propType->ParentPropertyKind)->Kind);
	}
}

bool PropertyKind::isParentAnEnergisticsPropertyKind() const
{
	return getSpecializedGsoapProxy()->ParentPropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StandardPropertyKind;
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind PropertyKind::getParentEnergisticsPropertyKind() const
{
	if (isParentAnEnergisticsPropertyKind())
	{
		_resqml2__PropertyKind* propKind = getSpecializedGsoapProxy();
		return static_cast<resqml2__StandardPropertyKind*>(propKind->ParentPropertyKind)->Kind;
	}
	else
		throw invalid_argument("The property kind parent of this property kind is not an Energistics one.");
}

std::string PropertyKind::getParentLocalPropertyKindUuid() const
{
	if (isParentAnEnergisticsPropertyKind() == false)
	{
		_resqml2__PropertyKind* propKind = getSpecializedGsoapProxy();
		return static_cast<resqml2__LocalPropertyKind*>(propKind->ParentPropertyKind)->LocalPropertyKind->UUID;
	}
	else
		throw invalid_argument("The property kind parent of this property kind is not a local one.");
}

void PropertyKind::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();

	if (propType->ParentPropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__LocalPropertyKind)
	{
		parentPropertyKind = static_cast<PropertyKind*>(epcDoc->getResqmlAbstractObjectByUuid(static_cast<resqml2__LocalPropertyKind*>(propType->ParentPropertyKind)->LocalPropertyKind->UUID));
		if (parentPropertyKind)
			parentPropertyKind->childPropertyKind.push_back(this);
	}
}

