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
#include "resqml2_0/ContinuousProperty.h"

#include <sstream>

#include "resqml2_0/AbstractRepresentation.h"
#include "resqml2_0/PropertyKind.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;

const char* ContinuousProperty::XML_TAG = "ContinuousProperty";

ContinuousProperty::ContinuousProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREContinuousProperty(rep->getGsoapProxy()->soap, 1);	
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;
	prop->UOM = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (rep->getEpcDocument())
		rep->getEpcDocument()->addGsoapProxy(this);
}

ContinuousProperty::ContinuousProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0::resqml2__ResqmlUom & uom, PropertyKind * localPropType)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREContinuousProperty(rep->getGsoapProxy()->soap, 1);	
	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;
	prop->UOM = uom;

	resqml2__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml2__LocalPropertyKind(gsoapProxy->soap, 1);
	xmlLocalPropKind->LocalPropertyKind = localPropType->newResqmlReference();
	prop->PropertyKind = xmlLocalPropKind;

	setRepresentation(rep);

	localPropertyKind = localPropType;
	localPropType->addProperty(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (rep->getEpcDocument())
		rep->getEpcDocument()->addGsoapProxy(this);
}

const gsoap_resqml2_0::resqml2__ResqmlUom & ContinuousProperty::getUom() const
{
	return static_cast<_resqml2__ContinuousProperty*>(gsoapProxy)->UOM;
}

std::string ContinuousProperty::getUomAsString() const
{
	return gsoap_resqml2_0::soap_resqml2__ResqmlUom2s(gsoapProxy->soap, getUom());
}

void ContinuousProperty::pushBackDoubleHdf5Array1dOfValues(double * values, const unsigned int & valueCount, HdfProxy * proxy,
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

void ContinuousProperty::pushBackDoubleHdf5Array2dOfValues(double * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, HdfProxy * proxy,
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

void ContinuousProperty::pushBackDoubleHdf5Array3dOfValues(double * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, HdfProxy * proxy,
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

void ContinuousProperty::pushBackDoubleHdf5ArrayOfValues(double * values, hsize_t * numValues, const unsigned int & numArrayDimensions, HdfProxy * proxy,
	double * minimumValue, double * maximumValue)
{
	pushBackXmlPartOfArrayNdOfExplicitValues(values, numValues, numArrayDimensions, proxy, minimumValue, maximumValue);

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy);
	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	hdfProxy->writeArrayNd(prop->uuid,
			oss.str(),
			H5::PredType::NATIVE_DOUBLE,
			values,
			numValues, numArrayDimensions);
}



void ContinuousProperty::pushBackFloatHdf5Array1dOfValues(float * values, const unsigned int & valueCount, HdfProxy * proxy,
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

void ContinuousProperty::pushBackFloatHdf5Array2dOfValues(float * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, HdfProxy * proxy,
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

void ContinuousProperty::pushBackFloatHdf5Array3dOfValues(float * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, HdfProxy * proxy,
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

void ContinuousProperty::pushBackFloatHdf5ArrayOfValues(float * values, hsize_t * numValues, const unsigned int & numArrayDimensions, HdfProxy * proxy,
	double * minimumValue, double * maximumValue)
{
	pushBackXmlPartOfArrayNdOfExplicitValues(values, numValues, numArrayDimensions, proxy, minimumValue, maximumValue);

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy);
	ostringstream oss;
	oss << "values_patch" << prop->PatchOfValues.size() - 1;

	// HDF
	hdfProxy->writeArrayNd(prop->uuid,
			oss.str(),
			H5::PredType::NATIVE_FLOAT,
			values,
			numValues, numArrayDimensions);
}

void ContinuousProperty::getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values)
{
	if (hdfProxy == NULL)
		return;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfDoubleValues(hdfValues->Values->PathInHdfFile, values);
}

void ContinuousProperty::getFloatValuesOfPatch(const unsigned int & patchIndex, float * values)
{
	if (hdfProxy == NULL)
		return;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__ContinuousProperty* prop = static_cast<_resqml2__ContinuousProperty*>(gsoapProxy);
	resqml2__DoubleHdf5Array* hdfValues = static_cast<resqml2__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);

	hdfProxy->readArrayNdOfFloatValues(hdfValues->Values->PathInHdfFile, values);
}

