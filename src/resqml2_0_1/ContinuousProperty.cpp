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
#include "resqml2_0_1/ContinuousProperty.h"

#include <sstream>

#include "hdf5.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* ContinuousProperty::XML_TAG = "ContinuousProperty";

ContinuousProperty::ContinuousProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREContinuousProperty(rep->getGsoapContext(), 1);	
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;
	prop->UOM = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

ContinuousProperty::ContinuousProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREContinuousProperty(rep->getGsoapContext(), 1);	
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;
	prop->UOM = uom;

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

const gsoap_resqml2_0_1::resqml2__ResqmlUom & ContinuousProperty::getUom() const
{
	return static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1)->UOM;
}

std::string ContinuousProperty::getUomAsString() const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlUom2s(gsoapProxy2_0_1->soap, getUom());
}

void ContinuousProperty::pushBackDoubleHdf5Array1dOfValues(double * values, const ULONG64 & valueCount, resqml2::AbstractHdfProxy * proxy,
		const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array2dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
			const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5Array3dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
			const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackDoubleHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
	}
}

void ContinuousProperty::pushBackDoubleHdf5ArrayOfValues(double * values, hsize_t * numValues, const unsigned int & numArrayDimensions, resqml2::AbstractHdfProxy * proxy,
	double * minimumValue, double * maximumValue)
{
	pushBackXmlPartOfArrayNdOfExplicitValues(values, numValues, numArrayDimensions, proxy, minimumValue, maximumValue);

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	proxy->writeArrayNd(prop->uuid,
			oss.str(),
			H5T_NATIVE_DOUBLE,
			values,
			numValues, numArrayDimensions);
}

void ContinuousProperty::pushBackFloatHdf5Array1dOfValues(float * values, const ULONG64 & valueCount, resqml2::AbstractHdfProxy * proxy,
		const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array2dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
			const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy);
	}
}

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy * proxy,
			const double & minimumValue, const double & maximumValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	if (minimumValue == minimumValue && maximumValue == maximumValue)
	{
		double minimumValuePerDimension[1] = {minimumValue};
		double maximumValuePerDimension[1] = {maximumValue};
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, minimumValuePerDimension, maximumValuePerDimension);
	}
	else
	{
		pushBackFloatHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy);
	}
}

void ContinuousProperty::createFloatHdf5Array3dOfValues(
	const ULONG64& valueCountInFastestDim,
	const ULONG64& valueCountInMiddleDim,
	const ULONG64& valueCountInSlowestDim,
	resqml2::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	createFloatHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
}

void ContinuousProperty::pushBackFloatHdf5SlabArray3dOfValues(
	float* values, 
	const ULONG64& valueCountInFastestDim,
	const ULONG64& valueCountInMiddleDim,
	const ULONG64& valueCountInSlowestDim,
	const ULONG64& offsetInFastestDim,
	const ULONG64& offsetInMiddleDim,
	const ULONG64& offsetInSlowestDim,
	resqml2::AbstractHdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
	pushBackFloatHdf5SlabArrayOfValues(
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3, 
		proxy
	);
}

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(float * values, ULONG64 * numValues, const unsigned int & numArrayDimensions, resqml2::AbstractHdfProxy * proxy,
	double * minimumValue, double * maximumValue)
{
	pushBackXmlPartOfArrayNdOfExplicitValues(values, numValues, numArrayDimensions, proxy, minimumValue, maximumValue);

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	proxy->writeArrayNd(prop->uuid,
			oss.str(),
			H5T_NATIVE_FLOAT,
			values,
			numValues, numArrayDimensions);
}

void ContinuousProperty::createFloatHdf5ArrayOfValues(
	ULONG64* numValues,
	const unsigned int& numArrayDimensions, 
	resqml2::AbstractHdfProxy* proxy)
{
	setHdfProxy(proxy);
	gsoap_resqml2_0_1::_resqml2__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::resqml2__PatchOfValues* patch = gsoap_resqml2_0_1::soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	gsoap_resqml2_0_1::resqml2__DoubleHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values = gsoap_resqml2_0_1::soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values->HdfProxy = proxy->newResqmlReference();
	std::ostringstream ossForHdf;
	ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
	xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	patch->Values = xmlValues;

	prop->PatchOfValues.push_back(patch);

	for (ULONG64 i = 0; i < prop->Count; ++i) {
		prop->MinimumValue.push_back(FLT_MAX);
		prop->MaximumValue.push_back(FLT_MIN);
	}

	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	proxy->createArrayNd(prop->uuid,
		oss.str(),
		H5T_NATIVE_FLOAT,
		numValues, numArrayDimensions);
}


void ContinuousProperty::pushBackFloatHdf5SlabArrayOfValues(
	float* values, ULONG64* numValuesInEachDimension,
	ULONG64* offsetInEachDimension, const unsigned int& numArrayDimensions,
	resqml2::AbstractHdfProxy* proxy)
{
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	setPropertyMinMax(
		values,
		numValuesInEachDimension, 
		numArrayDimensions
	);

	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	proxy->writeArrayNdSlab(
		prop->uuid,
		oss.str(),
		H5T_NATIVE_FLOAT,
		values,
		numValuesInEachDimension, 
		offsetInEachDimension, 
		numArrayDimensions);
}

void ContinuousProperty::getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values)
{
	resqml2::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfDoubleValues(hdfValues->Values->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(const unsigned int & patchIndex, float * values)
{
	resqml2::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfFloatValues(hdfValues->Values->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(
	const unsigned int& patchIndex, 
	float* values, 
	ULONG64* numValuesInEachDimension,
	ULONG64* offsetInEachDimension,
	const unsigned int& numArrayDimensions)
{
	resqml2::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfFloatValues(
        hdfValues->Values->PathInHdfFile, 
		values, 
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void ContinuousProperty::getFloatValuesOf3dPatch(
	const unsigned int& patchIndex, 
	float* values, 
	const ULONG64& valueCountInFastestDim,
	const ULONG64& valueCountInMiddleDim,
	const ULONG64& valueCountInSlowestDim,
	const ULONG64& offsetInFastestDim,
	const ULONG64& offsetInMiddleDim,
	const ULONG64& offsetInSlowestDim)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};

	getFloatValuesOfPatch(
		patchIndex,
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3
	);
}

double ContinuousProperty::getMinimumValue()
{
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MinimumValue[0];
}

double ContinuousProperty::getMaximumValue()
{
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MaximumValue[0];
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind ContinuousProperty::getFirstAllowedPropertyKindParent() const
{
	return gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__continuous;
}
