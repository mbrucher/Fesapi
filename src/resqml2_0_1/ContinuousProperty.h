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
#pragma once

#include "resqml2/AbstractValuesProperty.h"
#include "resqml2/AbstractHdfProxy.h"

#include <stdexcept>
#include <sstream>      // std::ostringstream

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT ContinuousProperty : public resqml2::AbstractValuesProperty
	{
	public:

		ContinuousProperty() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @apram uom						The uom of the values
		* @param energisticsPropertyKind	The property kind of these property values which must be defined in the standard energistics property type dictionary.
		*/
		ContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @apram uom						The uom of the values
		* @param localPropType				The property kind of these property values which must be defined in the EPC document as a local property kind.
		*/
		ContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousProperty(gsoap_resqml2_0_1::_resqml2__ContinuousProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~ContinuousProperty() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Get the unit of measure of the values of this property.
		*/
		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;

		/**
		* Get the unit of measure of the values of this property as a string.
		*/
		std::string getUomAsString() const;

		/**
		* Add a 1d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5Array1dOfValues(double * values, const ULONG64 & valueCount, resqml2::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 2d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5Array2dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 3d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5Array3dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add an array (potentially multi dimensions) of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5ArrayOfValues(double * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, resqml2::AbstractHdfProxy* proxy,
			double * minimumValue = nullptr, double * maximumValue = nullptr);

		/**
		* Add a 1d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5Array1dOfValues(float * values, const ULONG64 & valueCount, resqml2::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 2d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the slowest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5Array2dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 3d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the slowest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the slowest dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5Array3dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, resqml2::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add an array (potentially multi dimensions) of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5ArrayOfValues(float * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, resqml2::AbstractHdfProxy* proxy,
			double * minimumValue = nullptr, double * maximumValue = nullptr);

		/**
		* Create an array (potentially multi dimensions) of explicit float values to the property values. No values are written to this array yet.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void createFloatHdf5ArrayOfValues(
				unsigned long long* numValues,
			const unsigned int& numArrayDimensions, 
			resqml2::AbstractHdfProxy* proxy
		);

		/**
		* Create a 3d array of explicit float values to the property values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void createFloatHdf5Array3dOfValues(
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			resqml2::AbstractHdfProxy* proxy
		);

		/**
		* Add a 3d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackFloatHdf5SlabArray3dOfValues(
			float* values, 
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			const ULONG64& offsetInFastestDim,
			const ULONG64& offsetInMiddleDim,
			const ULONG64& offsetInSlowestDim,
			resqml2::AbstractHdfProxy* proxy
		);

		/**
		* Add an array (potentially multi dimensions) of explicit float values to the property values.
		* This method is to be used along with createFloatHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackFloatHdf5SlabArrayOfValues(
			float * values, 
			unsigned long long * numValues,
			unsigned long long * offsetValues,
			const unsigned int & numArrayDimensions, 
			resqml2::AbstractHdfProxy* proxy
		);

		/**
		* Get all the values of the instance which are supposed to be double ones.
		* @param values	The array (pointer) of values must be preallocated.
		*/
		void getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values);

		/**
		* Get all the values of the instance which are supposed to be float ones.
		* @param values	The array (pointer) of values must be preallocated.
		*/
		void getFloatValuesOfPatch(const unsigned int & patchIndex, float * values);

		/**
		* Get all the values of the instance which are supposed to be float ones.
		* @param patchIndex					Patch index.
		* @param values						The array (pointer) of values. It must be preallocated.
		* @param numValuesInEachDimension	The number of property values ordered by dimension of the array to write.
		* @param offsetInEachDimension		The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions			The number of dimensions of the HDF5 array to read.
		*/
		void getFloatValuesOfPatch(
			const unsigned int& patchIndex, 
			float* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);

		/**
		* Get all the values of the instance which are supposed to be float ones.
		* @param patchIndex				Patch index.
		* @param values					The array (pointer) of values. It must be preallocated.
		* @param valueCountInFastestDim	The number of values to read in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to read in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to read in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset value to read in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to read in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to read in the slowest dimension (mainly K dimension).
		*/
		void getFloatValuesOf3dPatch(
			const unsigned int& patchIndex, 
			float* values, 
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			const ULONG64& offsetInFastestDim,
			const ULONG64& offsetInMiddleDim,
			const ULONG64& offsetInSlowestDim
		);

		double getMinimumValue();
		double getMaximumValue();

		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getFirstAllowedPropertyKindParent() const;

	private:

		/**
		* Compute and set the minimum and maximum value in \p values. 
		* @param values				The array of values.
		* @param numValues			The number of property values in each dimension.
		* @param numArrayDimensions	The number of dimensions of the array.
		*/
		template <class T>
		void setPropertyMinMax(
			T* values, 
			unsigned long long* numValuesInEachDimension,
			const unsigned int& numArrayDimensions
		) {
			gsoap_resqml2_0_1::_resqml2__ContinuousProperty* prop = 
				static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
			if (prop->Count == 1) {

				ULONG64 nValues = numValuesInEachDimension[0];

				for (unsigned int dim = 1; dim < numArrayDimensions; dim++) {
					nValues *= numValuesInEachDimension[dim];
				}

				T computedMin = prop->MinimumValue[0];
				T computedMax = prop->MaximumValue[0];

				for (ULONG64 i = 0; i < nValues; ++i) {
					if( values[i] < computedMin ) {
						computedMin = values[i];
					} else if( values[i] > computedMax ) {
						computedMax = values[i];
					}
				}
				prop->MinimumValue[0] = computedMin;
				prop->MaximumValue[0] = computedMax;
			} else if (prop->Count > 1) {
				//In this case, the last (fastest) dimension 
				//has the number of elements in the representation.
				ULONG64 nValues = numValuesInEachDimension[0];

				for (unsigned int dim = 1; dim < numArrayDimensions-1; dim++) {
					nValues *= numValuesInEachDimension[dim];
				}

				const int nProperties = prop->Count;

				for(int propIndex = 0; propIndex < nProperties; ++propIndex) {
					T computedMin = prop->MinimumValue[propIndex];
					T computedMax = prop->MaximumValue[propIndex];

					for (ULONG64 valIndex = 0; valIndex < nValues; ++valIndex) {
						T propVal = values[propIndex+(nProperties*valIndex)];
						if( propVal < computedMin ) {
							computedMin = values[valIndex];
						} else if( propVal > computedMax ) {
							computedMax = values[valIndex];
						}
					}
					prop->MinimumValue.push_back(computedMin);
					prop->MaximumValue.push_back(computedMax);
				}
			}
		}

		template <class valueType>
		void pushBackXmlPartOfArrayNdOfExplicitValues(valueType * values, unsigned long long * numValues, const unsigned int & numValueDimensions, resqml2::AbstractHdfProxy * proxy,
			double * minimumValue = nullptr, double * maximumValue = nullptr)
		{
			setHdfProxy(proxy);
			gsoap_resqml2_0_1::_resqml2__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);

			if (prop->Count == 1)
			{
				double computedMinimumValue;
				double computedMaximumValue;
				if (minimumValue == nullptr || maximumValue == nullptr)
				{
					ULONG64 numTotalValues = numValues[0];
					for (unsigned int dim = 1; dim < numValueDimensions; dim++)
						numTotalValues *= numValues[dim];

					unsigned int i = 0;
					computedMinimumValue = std::numeric_limits<double>::quiet_NaN();
					computedMaximumValue = std::numeric_limits<double>::quiet_NaN();
					while (values[i] != values[i]) ++i;
					if (i < numTotalValues)
					{
						computedMinimumValue = values[i];
						computedMaximumValue = values[i];
					}
					for (; i < numTotalValues; ++i)
					{
						if (values[i] == values[i])
						{
							if (values[i] > computedMaximumValue)
								computedMaximumValue = values[i];
							else if (values[i] < computedMinimumValue)
								computedMinimumValue = values[i];
						}
					}
				}
				else
				{
					computedMinimumValue = minimumValue[0];
					computedMaximumValue = maximumValue[0];
				}

				prop->MinimumValue.push_back(computedMinimumValue);
				prop->MaximumValue.push_back(computedMaximumValue);
			}
			else if (minimumValue || maximumValue)
			{
				if (minimumValue)
				{
					prop->MinimumValue.clear();
					for (unsigned int i = 0; i < prop->Count; i++)
					{
						prop->MinimumValue.push_back(minimumValue[i]);
					}
				}
				if (maximumValue)
				{
					prop->MaximumValue.clear();
					for (unsigned int i = 0; i < prop->Count; i++)
					{
						prop->MaximumValue.push_back(maximumValue[i]);
					}
				}
			}

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
		}
	};
}
