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

#include "resqml2_0_1/AbstractHdfProxy.h"

#define CUMULATIVE_LENGTH_DS_NAME "cumulativeLength"
#define ELEMENTS_DS_NAME "elements"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT HdfProxy : public AbstractHdfProxy
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @packageDirAbsolutePath	The directory where the EPC document is stored. Must end with a slash or back-slash
		* @relativeFilePath			The relative file path of the associated HDF file. It is relative to the location of the package
		*/
		HdfProxy(common::EpcDocument * epcDoc, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath):
			AbstractHdfProxy(epcDoc, guid, title, packageDirAbsolutePath, externalFilePath), hdfFile(-1), compressionLevel(0) {}

		HdfProxy(gsoap_resqml2_0_1::_eml__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath):
		  AbstractHdfProxy(fromGsoap, packageDirAbsolutePath, externalFilePath), hdfFile(-1), compressionLevel(0) {}

		/**
		* Destructor.
		* Close the hdf file.
		*/
		~HdfProxy() {close();}

		/**
		* Open the file for reading and writing.
		* Does never overwrite an existing file but append to it if it already exists.
		*/
		void open();

		/**
		* Check if the Hdf file is open or not
		*/
		bool isOpened() {return hdfFile != -1;}

		/**
		* Close the file
		*/
		void close();

		/*
		* Get the used (native) datatype in a dataset
		* To compare with H5T_NATIVE_INT, H5T_NATIVE_UINT, H5T_NATIVE_FLOAT, etc...
		*/
		hid_t getHdfDatatypeInDataset(const std::string & groupName);
		
		/**
		* Write an itemized list of list into the HDF file by means of a single group containing 2 datasets.
		* @param groupName				The name of the group where to create the itemized list of list.
		*								This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name					The name of the itemized list of list hdf group.
		* @param cumulativeLength		1d array of positive integers containing for each list the sum of all the previous list lengths including the current one
		* @param cumulativeLengthSize	Size of the cumulativeLength array.
		* @param elements				1d array of elements containing the aggregation of individual list content.
		* @param elementsSize			Size of the elements array.
		*/
		void writeItemizedListOfUnsignedInt(const std::string & groupName,
			const std::string & name,
			unsigned int * cumulativeLength,
			const hsize_t & cumulativeLengthSize,
			unsigned int * elements,
			const hsize_t & elementsSize);

		/**
		* Get the number of dimensions in an HDF dataset of the proxy.
		* @param datasetName	The absolute name of the dataset we want to get the number of dimensions.
		*/
		unsigned int getDimensionCount(const std::string & datasetName);

		/**
		* Get the number of elements in an HDF dataset of the proxy. The number of elements is get from all dimensions.
		* @param datasetName	The absolute name of the dataset we want to get the number of elements.
		*/
		unsigned int getElementCount(const std::string & datasetName);

		/**
		* Set the new compression level which will be used for all data to be written
		* @param compressionLevel				Lower compression levels are faster but result in less compression. Range [0..9] is allowed.
		*/
		void setCompressionLevel(const unsigned int & newCompressionLevel) {if (newCompressionLevel > 9) compressionLevel = 9; else compressionLevel = newCompressionLevel;}

		void writeArrayNdOfFloatValues(const std::string & groupName,
			const std::string & name,
			float * floatValues,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of double values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of double values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of double values hdf dataset. It must not already exist.
		* @param dblValues						1d array of double values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfDoubleValues(const std::string & groupName,
			const std::string & name,
			double * dblValues,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of int values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of int values hdf dataset. It must not already exist.
		* @param intValues						1d array of int values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfIntValues(const std::string & groupName,
			const std::string & name,
			int * intValues,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of gSoap unsigned long 64 values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of gSoap unsigned long 64 values hdf dataset. It must not already exist.
		* @param ulong64Values					1d array of gSoap unsigned long 64 values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfGSoapULong64Values(const std::string & groupName,
			const std::string & name,
			ULONG64 * ulong64Values,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of a specific datatype into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not already exist.
		* @param datatype						The specific datatype of the valeus to write.
		* @param values							1d array of specific datatype ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNd(const std::string & groupName,
			const std::string & name,
			const hid_t & datatype,
			void * values,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions);

		/**
		* Create an array (potentially with multi dimensions) of a specific datatype into the HDF file. Values are not yet written to this array.
		* @param groupName                      The name of the group where to create the array of double values.
		*                                       This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name                           The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not exist.
		* @param datatype                       The specific datatype of the values to write.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to write.
		*/
		void createArrayNd(
			const std::string& groupName,
			const std::string& name,
			const hid_t & datatype,
			hsize_t* numValuesInEachDimension,
			const unsigned int& numDimensions
		);

		/**
		* Find the array associated with @p groupName and @p name and write to it.
		* @param groupName                      The name of the group associated with the array.
		* @param name                           The name of the array (potentially with multi dimensions).
		* @param values                         1d array of specific datatype ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to write.
		*/
		void writeArrayNdSlab(
			const std::string& groupName,
			const std::string& name,
			void* values,
			hsize_t* numValuesInEachDimension,
			hsize_t* offsetValuesInEachDimension,
			const unsigned int& numDimensions
		);

		/**
		* Read an array Nd of double values stored in a specific dataset
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfDoubleValues(const std::string & datasetName, double* values);

		/**
		* Read an array Nd of float values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfFloatValues(const std::string & datasetName, float* values);

		/**
		* Find the array associated with @p datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of float values ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		void readArrayNdOfFloatValues(
			const std::string & datasetName, 
			float* values, 
			hsize_t * numValuesInEachDimension, 
			hsize_t * offsetInEachDimension, 
			const unsigned int & numDimensions
		);

		/**
		* TODO : check all possible size of LONG64 on all different platforms
		*/
		void readArrayNdOfGSoapLong64Values(const std::string & datasetName, LONG64* values);
	
		/**
		* TODO : check all possible size of ULONG64 on all different platforms
		*/
		void readArrayNdOfGSoapULong64Values(const std::string & datasetName, ULONG64* values);

		/**
		* Read an array Nd of long values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfLongValues(const std::string & datasetName, long* values);

		/**
		* Find the array associated with datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of long values ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		void readArrayNdOfLongValues(
			const std::string & datasetName, 
			long* values, 
			hsize_t * numValuesInEachDimension, 
			hsize_t * offsetInEachDimension, 
			const unsigned int & numDimensions
		);

		/**
		* Read an array Nd of unsigned long values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfULongValues(const std::string & datasetName, unsigned long* values);

		/**
		* Read an array Nd of int values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfIntValues(const std::string & datasetName, int* values);

		/**
		* Read an array Nd of unsigned int values stored in a specific dataset
		* Don"t forget to delete the allocated pointer when no more necessary.
		* @param datasetName	The absolute dataset name where to read the values
		*/
		void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values);

		/**
		* Read an array Nd of short values stored in a specific dataset
		* Don"t forget to delete the allocated pointer when no more necessary.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfShortValues(const std::string & datasetName, short* values);

		/**
		* Read an array Nd of unsigned short values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values);

		/**
		* Read an array Nd of char values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfCharValues(const std::string & datasetName, char* values);

		/**
		* Read an array Nd of unsigned char values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		*/
		void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values);

		/**
		* Read the dimensions of an array stored in a specific dataset
		* @param datasetName	The absolute dataset name where to read the array dimensions
		*/
		std::vector<hsize_t> readArrayDimensions(const std::string & datasetName);

	private:
		/**
		* Check if a hdf group named "RESQML" exists as a child of the root of the HDF file.
		* If it exists, it returns the latter. If not, it creates this group and then returns it.
		* Please close the group after having called and used this group.
		*/
		hid_t openOrCreateHdfResqmlGroup();

		/**
		* Check if an hdf group named as groupName exists in the "RESQML" group.
		* If it exists, it returns the latter. If not, it creates this group and then returns it.
		* Please close the group after having called and used this group.
		*/
		hid_t openOrCreateGroupInResqmlGroup(const std::string & groupName);

		hid_t hdfFile;

		unsigned int compressionLevel;
	};
}
