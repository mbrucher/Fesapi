/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014) 

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
