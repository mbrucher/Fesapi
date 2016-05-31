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
#include "resqml2_0_1/CategoricalProperty.h"

#include <stdexcept>
#include <sstream>

#include "hdf5.h"

#include "resqml2_0_1/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* CategoricalProperty::XML_TAG = "CategoricalProperty";

CategoricalProperty::CategoricalProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
		: stringLookup(strLookup)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECategoricalProperty(rep->getGsoapContext(), 1);	
	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

CategoricalProperty::CategoricalProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			StringTableLookup* strLookup, PropertyKind * localPropKind)
	:stringLookup(strLookup)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECategoricalProperty(rep->getGsoapContext(), 1);	
	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> CategoricalProperty::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractValuesProperty::getAllEpcRelationships();

	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);

	if (stringLookup)
	{
		Relationship rel(stringLookup->getPartNameInEpcDocument(), "", prop->Lookup->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	else
		throw domain_error("The string lookup associated to the categorical property values cannot be nullptr.");

	return result;
}

void CategoricalProperty::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractValuesProperty:: importRelationshipSetFromEpc(epcDoc);

	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);
	stringLookup = static_cast<StringTableLookup*>(epcDoc->getResqmlAbstractObjectByUuid(prop->Lookup->UUID));
	if (stringLookup)
		stringLookup->addCategoricalPropertyValues(this);
}

void CategoricalProperty::pushBackLongHdf5Array1dOfValues(long * values, const unsigned int & valueCount, resqml2::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5Array2dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5Array3dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5ArrayOfValues(long * values, hsize_t * numValues, const unsigned int & numDimensionsInArray, resqml2::AbstractHdfProxy * proxy, const long & nullValue)
{
	setHdfProxy(proxy);
	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);

	resqml2__PatchOfValues* patch = soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	ostringstream oss;
	resqml2__IntegerHdf5Array* xmlValues = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlValues->NullValue = nullValue;
	xmlValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();;
	ostringstream ossForHdf;
	ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
	xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	patch->Values = xmlValues;

	// HDF
	hdfProxy->writeArrayNd(prop->uuid,
			ossForHdf.str(),
			H5T_NATIVE_LONG,
			values,
			numValues, numDimensionsInArray);

	prop->PatchOfValues.push_back(patch);
}

std::string CategoricalProperty::getStringLookupUuid() const
{
	return static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup->UUID;
}

