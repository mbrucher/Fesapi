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
#include "resqml2_0/AbstractValuesProperty.h"

#include <stdexcept>
#include <ostream>
#include <sstream>

#include "resqml2_0/AbstractRepresentation.h"
#include "resqml2_0/PropertyKind.h"
#include "resqml2_0/AbstractLocal3dCrs.h"
#include "resqml2_0/HdfProxy.h"

using namespace gsoap_resqml2_0;
using namespace resqml2_0;
using namespace std;
using namespace epc;

void AbstractValuesProperty::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractProperty::importRelationshipSetFromEpc(epcDoc);

	resqml2__AbstractValuesProperty* prop = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy);

	resqml2__PatchOfValues* firstPatch = prop->PatchOfValues[0];
	int valuesType = firstPatch->Values->soap_type();
	
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__BooleanHdf5Array)
	{
		setHdfProxy(static_cast<HdfProxy*>(epcDoc->getResqmlAbstractObjectByUuid(
			static_cast<resqml2__BooleanHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID)));
	}
	else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		setHdfProxy(static_cast<HdfProxy*>(epcDoc->getResqmlAbstractObjectByUuid(
				static_cast<resqml2__DoubleHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID)));
	}
	else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		setHdfProxy(static_cast<HdfProxy*>(epcDoc->getResqmlAbstractObjectByUuid(
				static_cast<resqml2__IntegerHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID)));
	}
	else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__StringHdf5Array)
	{
		setHdfProxy(static_cast<HdfProxy*>(epcDoc->getResqmlAbstractObjectByUuid(
				static_cast<resqml2__StringHdf5Array*>(firstPatch->Values)->Values->HdfProxy->UUID)));
	}
}

AbstractValuesProperty::hdfDatatypeEnum AbstractValuesProperty::getValuesHdfDatatype() const
{
	if (hdfProxy == NULL)
		return AbstractValuesProperty::UNKNOWN;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__AbstractValuesProperty* prop = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy);

	resqml2__PatchOfValues* firstPatch = prop->PatchOfValues[0];
	int valuesType = firstPatch->Values->soap_type();
	H5::DataType dt = H5::PredType::NATIVE_DOUBLE;
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__BooleanHdf5Array)
	{
		dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
	}
	else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__DoubleHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
	}
	else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__IntegerHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
	}
	else if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__StringHdf5Array)
	{
		dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__StringHdf5Array*>(firstPatch->Values)->Values->PathInHdfFile);
	}
	else
		return AbstractValuesProperty::UNKNOWN;

	if (dt == H5::PredType::NATIVE_DOUBLE)
		return AbstractValuesProperty::DOUBLE;
	else if (dt == H5::PredType::NATIVE_FLOAT)
		return AbstractValuesProperty::FLOAT;
	else if (dt == H5::PredType::NATIVE_LONG)
		return AbstractValuesProperty::LONG;
	else if (dt == H5::PredType::NATIVE_ULONG)
		return AbstractValuesProperty::ULONG;
	else if (dt == H5::PredType::NATIVE_INT)
		return AbstractValuesProperty::INT;
	else if (dt == H5::PredType::NATIVE_UINT)
		return AbstractValuesProperty::UINT;
	else if (dt == H5::PredType::NATIVE_SHORT)
		return AbstractValuesProperty::SHORT;
	else if (dt == H5::PredType::NATIVE_USHORT)
		return AbstractValuesProperty::USHORT;
	else if (dt == H5::PredType::NATIVE_CHAR)
		return AbstractValuesProperty::CHAR;
	else if (dt == H5::PredType::NATIVE_UCHAR)
		return AbstractValuesProperty::UCHAR;

	return AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

long AbstractValuesProperty::getLongValuesOfPatch(const unsigned int & patchIndex, long * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

long AbstractValuesProperty::getNullValueOfPatch(const unsigned int & patchIndex)
{
	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];
	if (patch->Values->soap_type() != SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
		throw invalid_argument("The patch does not contain integer values.");
	else
		return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

unsigned long AbstractValuesProperty::getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

int AbstractValuesProperty::getIntValuesOfPatch(const unsigned int & patchIndex, int * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];
	
	hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

unsigned int AbstractValuesProperty::getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

short AbstractValuesProperty::getShortValuesOfPatch(const unsigned int & patchIndex, short * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

unsigned short AbstractValuesProperty::getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

char AbstractValuesProperty::getCharValuesOfPatch(const unsigned int & patchIndex, char * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

unsigned char AbstractValuesProperty::getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];

	hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile, values);

	return static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->NullValue;
}

unsigned int AbstractValuesProperty::getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];
	std::vector<hsize_t> dims;
	if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		dims = hdfProxy->readArrayDimensions (static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}
	else if(patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		dims = hdfProxy->readArrayDimensions (static_cast<resqml2__DoubleHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}
    else if(patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__StringHdf5Array)
	{
		dims = hdfProxy->readArrayDimensions (static_cast<resqml2__StringHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}

	if (dimIndex < dims.size())
		return dims[dimIndex];
	else
		return 0;
}

unsigned int AbstractValuesProperty::getDimensionsCountOfPatch(const unsigned int & patchIndex)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];
	if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		return hdfProxy->getDimensionCount (static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile); 
	}
	else if(patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		return hdfProxy->getDimensionCount (static_cast<resqml2__DoubleHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}
    else if(patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__StringHdf5Array)
	{
		return hdfProxy->getDimensionCount (static_cast<resqml2__StringHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}
	else
		return 0;
}

unsigned int AbstractValuesProperty::getValuesCountOfPatch (const unsigned int & patchIndex)
{
	if (hdfProxy == NULL)
		throw invalid_argument("The Hdf proxy cannot be NULL.");

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	resqml2__PatchOfValues* patch = static_cast<resqml2__AbstractValuesProperty*>(gsoapProxy)->PatchOfValues[patchIndex];
	if (patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		return hdfProxy->getElementCount (static_cast<resqml2__IntegerHdf5Array*>(patch->Values)->Values->PathInHdfFile); 
	}
	else if(patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		return hdfProxy->getElementCount (static_cast<resqml2__DoubleHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}
    else if(patch->Values->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__StringHdf5Array)
	{
		return hdfProxy->getElementCount (static_cast<resqml2__StringHdf5Array*>(patch->Values)->Values->PathInHdfFile);
	}
	else
		return 0;
}

void AbstractValuesProperty::createLongHdf5Array3dOfValues(
	const unsigned int& valueCountInFastestDim, 
	const unsigned int& valueCountInMiddleDim, 
	const unsigned int& valueCountInSlowestDim, 
	HdfProxy* proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	createLongHdf5ArrayOfValues(valueCountPerDimension, 3, proxy);
}

void AbstractValuesProperty::pushBackLongHdf5SlabArray3dOfValues(
	long* values, 
	const unsigned int& valueCountInFastestDim, 
	const unsigned int& valueCountInMiddleDim, 
	const unsigned int& valueCountInSlowestDim, 
	const unsigned int& offsetInFastestDim, 
	const unsigned int& offsetInMiddleDim, 
	const unsigned int& offsetInSlowestDim,
	HdfProxy * proxy)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = {offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};
	pushBackLongHdf5SlabArrayOfValues(
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3, 
		proxy
	);
}

void AbstractValuesProperty::createLongHdf5ArrayOfValues(
	hsize_t* numValues, 
	const unsigned int& numArrayDimensions, 
	HdfProxy* proxy)
{
	setHdfProxy(proxy);
	gsoap_resqml2_0::_resqml2__CategoricalProperty* prop = static_cast<gsoap_resqml2_0::_resqml2__CategoricalProperty*>(gsoapProxy);

	gsoap_resqml2_0::resqml2__PatchOfValues* patch = gsoap_resqml2_0::soap_new_resqml2__PatchOfValues(gsoapProxy->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	gsoap_resqml2_0::resqml2__IntegerHdf5Array* xmlValues = gsoap_resqml2_0::soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	xmlValues->Values = gsoap_resqml2_0::soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();
	std::ostringstream ossForHdf;
	ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
	xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	patch->Values = xmlValues;

	prop->PatchOfValues.push_back(patch);

	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	hdfProxy->createArrayNd(prop->uuid,
		oss.str(),
		H5::PredType::NATIVE_LONG,
		numValues, numArrayDimensions);
}

void AbstractValuesProperty::pushBackLongHdf5SlabArrayOfValues(
	long* values, hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension, const unsigned int& numArrayDimensions, 
	HdfProxy* proxy)
{
	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy);
	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	hdfProxy->writeArrayNdSlab(prop->uuid,
		oss.str(),
		values,
		numValuesInEachDimension, 
		offsetInEachDimension, 
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOfPatch(
	const unsigned int& patchIndex, 
	long* values, 
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension, 
	const unsigned int& numArrayDimensions)
{
	if (hdfProxy == NULL) {
		return;
	}

	if (!hdfProxy->isOpened()) {
		hdfProxy->openForReading();
	}

	_resqml2__CategoricalProperty* prop = 
		static_cast<_resqml2__CategoricalProperty*>(gsoapProxy);
	resqml2__IntegerHdf5Array* hdfValues = 
		static_cast<resqml2__IntegerHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfLongValues(
		hdfValues->Values->PathInHdfFile, 
		values, 
		numValuesInEachDimension,
		offsetInEachDimension,
		numArrayDimensions);
}

void AbstractValuesProperty::getLongValuesOf3dPatch(
	const unsigned int& patchIndex, 
	long* values, 
	const unsigned int& valueCountInFastestDim, 
	const unsigned int& valueCountInMiddleDim, 
	const unsigned int& valueCountInSlowestDim, 
	const unsigned int& offsetInFastestDim, 
	const unsigned int& offsetInMiddleDim, 
	const unsigned int& offsetInSlowestDim)
{
	hsize_t valueCountPerDimension[3] = 
	{valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	hsize_t offsetPerDimension[3] = 
	{offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim};

	getLongValuesOfPatch(
		patchIndex,
		values, 
		valueCountPerDimension, 
		offsetPerDimension, 
		3
	);
}
