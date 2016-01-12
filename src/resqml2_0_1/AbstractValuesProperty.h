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
#pragma once

#include "resqml2_0_1/AbstractProperty.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractValuesProperty : public AbstractProperty
	{
	public:

		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG = 3, ULONG = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};

		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractValuesProperty() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractValuesProperty(gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* fromGsoap): AbstractProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractValuesProperty() {}

		/**
		* Get the values datatype in the HDF dataset
		*/
		AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;

		/**
		* Push back a new patch of values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	isAnIntegerDataset	If false, indicates that this dataset contains some floating point values. If true, this dataset contains some integer values.
		* @param	dataset				If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		*/
		void pushBackRefToExistingDataset(class AbstractHdfProxy * hdfProxy, const bool & isAnIntegerDataset, const std::string & dataset = "");

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		long getLongValuesOfPatch(const unsigned int & patchIndex, long * values);

		/**
		* Get the null value of the instance which are supposed to be integer ones.
		* Not for continuous property values.
		* @return the null value
		*/
		long getNullValueOfPatch(const unsigned int & patchIndex);

		/**
		* Get all the values of the instance which are supposed to be unsigned long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned long getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values);

		/**
		* Get all the values of the instance which are supposed to be int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		int getIntValuesOfPatch(const unsigned int & patchIndex, int * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned int getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values);
		
		/**
		* Get all the values of the instance which are supposed to be short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		short getShortValuesOfPatch(const unsigned int & patchIndex, short * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned short getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values);

		/**
		* Get all the values of the instance which are supposed to be char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		char getCharValuesOfPatch(const unsigned int & patchIndex, char * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned char getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values);

		/**
		* Get the count of all values contained into the underlying HDF5 dataset of this property for a particular patch.
		*/
		unsigned int getValuesCountOfPatch (const unsigned int & patchIndex);

		/**
		* Get the count of values on a specific dimension of the underlying HDF5 dataset of this property.
		* @param dimIndex	The index of the dimension we want to know the values count in this property.
		* @param patchIndex	The index of the patch we want to know the values count in this property.
		* @return			The number of values, 0 otherwise.
		*/
		unsigned int getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex);

		/**
		* Get the count of dimension of the underlying HDF5 dataset of this property.
		* @param patchIndex	The index of the patch we want to know the dimensions in this property.
		* @return			The number of values, 0 otherwise.
		*/
		unsigned int getDimensionsCountOfPatch(const unsigned int & patchIndex);

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		* Create an array (potentially multi dimensions) of explicit long values to the property values. No values are written to this array yet.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			const unsigned int& numArrayDimensions, 
			class AbstractHdfProxy* proxy
		);

		/**
		* Create a 3d array of explicit Long values to the property values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void createLongHdf5Array3dOfValues(
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			class AbstractHdfProxy * proxy
		);

		/**
		* Add a 3d array of explicit Long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackLongHdf5SlabArray3dOfValues(
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim, 
			class AbstractHdfProxy* proxy
		);

		/**
		* Add an array (potentially multi dimensions) of explicit long values to the property values.
		* This method is to be used along with createLongHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackLongHdf5SlabArrayOfValues(
			long * values, 
			unsigned long long * numValues,
			unsigned long long * offsetValues,
			const unsigned int & numArrayDimensions, 
			class AbstractHdfProxy * proxy
		);

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* @param patchIndex	Patch index.
		* @param values					The array (pointer) of values which must be preallocated.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		*/
		void getLongValuesOfPatch(
			const unsigned int& patchIndex, 
			long* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* @param patchIndex				Patch index.
		* @param values					The array (pointer) of values must be preallocated.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		*/
		void getLongValuesOf3dPatch(
			const unsigned int& patchIndex, 
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim
		);

	protected:	
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

	};
}
