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
#include "resqml2_0_1/DiscreteProperty.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "tools/Statistics.h"
#include "resqml2_0_1/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* DiscreteProperty::XML_TAG = "DiscreteProperty";

DiscreteProperty::DiscreteProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREDiscreteProperty(rep->getGsoapContext(), 1);	
	_resqml2__DiscreteProperty* prop = static_cast<_resqml2__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

DiscreteProperty::DiscreteProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREDiscreteProperty(rep->getGsoapContext(), 1);	
	_resqml2__DiscreteProperty* prop = static_cast<_resqml2__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(long * values, const unsigned int & valueCount, resqml2::AbstractHdfProxy * proxy,
		const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array1dOfValues(long * values, const unsigned int & valueCount, resqml2::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(int * values, const unsigned int & valueCount, resqml2::AbstractHdfProxy * proxy,
	const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array1dOfValues(int * values, const unsigned int & valueCount, resqml2::AbstractHdfProxy * proxy,
	const int & nullValue)
{
	hsize_t valueCountPerDimension[1] = { valueCount };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
			const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array2dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(int * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
	const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array2dOfValues(int * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
	const int & nullValue)
{
	hsize_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
			const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackLongHdf5Array3dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(int * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
	const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue, minimumValue, maximumValue);
}

void DiscreteProperty::pushBackIntHdf5Array3dOfValues(int * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
	const int & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackIntHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

string DiscreteProperty::pushBackOnlyXmlPartOfArrayOfValues(resqml2::AbstractHdfProxy* proxy, const long & nullValue, const long &  minimumValue, const long &  maximumValue)
{
	setHdfProxy(proxy);
	_resqml2__DiscreteProperty* prop = static_cast<_resqml2__DiscreteProperty*>(gsoapProxy2_0_1);

	if (prop->Count == 1)
	{
		if (prop->MinimumValue.size() == 0)
			prop->MinimumValue.push_back(minimumValue);
		else
			prop->MinimumValue[0] = minimumValue;

		if (prop->MaximumValue.size() == 0)
			prop->MaximumValue.push_back(maximumValue);
		else
			prop->MaximumValue[0] = maximumValue;
	}

	resqml2__PatchOfValues* patch = soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	resqml2__IntegerHdf5Array* xmlValues = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlValues->NullValue = nullValue;
	xmlValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
	xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	patch->Values = xmlValues;

	prop->PatchOfValues.push_back(patch);

	return ossForHdf.str();
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(long * values, hsize_t * numValues, const unsigned int & numDimensionsInArray, resqml2::AbstractHdfProxy * proxy,
	const long & nullValue, const long & minimumValue, const long & maximumValue)
{
	string datasetName = pushBackOnlyXmlPartOfArrayOfValues(proxy, nullValue, minimumValue, maximumValue);

	// HDF
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_LONG,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackLongHdf5ArrayOfValues(long * values, hsize_t * numValues, const unsigned int & numDimensionsInArray, resqml2::AbstractHdfProxy * proxy,
	const long & nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; dim++)
		numTotalValues *= numValues[dim];

	pair<long, long> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackLongHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(int * values, hsize_t * numValues, const unsigned int & numDimensionsInArray, resqml2::AbstractHdfProxy* proxy, const int & nullValue, const int &  minimumValue, const int &  maximumValue)
{
	string datasetName = pushBackOnlyXmlPartOfArrayOfValues(proxy, nullValue, minimumValue, maximumValue);

	// HDF
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_LONG,
		values,
		numValues, numDimensionsInArray);
}

void DiscreteProperty::pushBackIntHdf5ArrayOfValues(int * values, hsize_t * numValues, const unsigned int & numDimensionsInArray, resqml2::AbstractHdfProxy* proxy, const int & nullValue)
{
	hsize_t numTotalValues = numValues[0];
	for (unsigned int dim = 1; dim < numDimensionsInArray; dim++)
		numTotalValues *= numValues[dim];

	pair<int, int> minMax = statistics::getMinMax(values, nullValue, numTotalValues);
	pushBackIntHdf5ArrayOfValues(values, numValues, numDimensionsInArray, proxy, nullValue, minMax.first, minMax.second);

}
