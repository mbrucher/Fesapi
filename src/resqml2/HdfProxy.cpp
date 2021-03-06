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
#include "resqml2/HdfProxy.h"

#include <stdexcept>

#include "hdf5.h"

using namespace std;
using namespace resqml2;


HdfProxy::HdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
	AbstractHdfProxy(packageDirAbsolutePath, externalFilePath), hdfFile(-1), compressionLevel(0) {}

void HdfProxy::open()
{
	herr_t hdf5Err = H5Eset_auto(H5E_DEFAULT, nullptr, nullptr);
	if (hdf5Err < 0) {
		throw invalid_argument("The HDF5 error handling could not have been disabled.");
	}

	if (hdfFile != -1) {
		close();
	}

	switch (getEpcDocument()->getHdf5PermissionAccess())
	{
	case common::EpcDocument::READ_ONLY:
		if (H5Fis_hdf5((packageDirectoryAbsolutePath + relativeFilePath).c_str()) > 0) {
			hdfFile = H5Fopen((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
		}
		else {
			throw invalid_argument("The HDF5 file " + packageDirectoryAbsolutePath + relativeFilePath + " does not exist or is not a valid HDF5 file.");
		}
		break;
	case common::EpcDocument::READ_WRITE:
		hdfFile = H5Fcreate((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT);

		if (hdfFile < 0) {
			if (H5Fis_hdf5((packageDirectoryAbsolutePath + relativeFilePath).c_str()) > 0) {
				hdfFile = H5Fopen((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
			}
			else {
				throw invalid_argument("The HDF5 file " + packageDirectoryAbsolutePath + relativeFilePath + " is not a valid HDF5 file.");
			}
		}
		break;
	case common::EpcDocument::OVERWRITE:
	{
		hdfFile = H5Fcreate((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

		// create an attribute at the file level to store the uuid of the corresponding resqml hdf proxy.
		hid_t aid = H5Screate(H5S_SCALAR);
		hid_t atype = H5Tcopy(H5T_C_S1);
		H5Tset_size(atype, getUuid().size());
		hid_t attribute_id = H5Acreate2(hdfFile, "uuid", atype, aid, H5P_DEFAULT, H5P_DEFAULT);
		int status = H5Awrite(attribute_id, atype, getUuid().c_str());

		// Close the attribute.
		status = H5Sclose(aid);
		status = H5Tclose(atype);
		status = H5Aclose(attribute_id);

		break;
	}
	default:
		throw invalid_argument("The HDF5 permission access is unknown.");
	}

	if (hdfFile < 0) {
		throw invalid_argument("The HDF5 file " + packageDirectoryAbsolutePath + relativeFilePath + " could not have been created or opened.");
	}
}

void HdfProxy::close()
{
	if (hdfFile != -1) {
		H5Fclose(hdfFile);
		hdfFile = -1;
	}
}

void HdfProxy::readArrayNdOfValues(const std::string & datasetName, void* values, const hid_t & datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
	}
	hid_t readingError = H5Dread (dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, values);

	H5Dclose(dataset);
	if (readingError < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be read.");
	}
}

void HdfProxy::readArrayNdOfValues(
	  const std::string & datasetName,
	  void* values,
	  unsigned long long * numValuesInEachDimension,
	  unsigned long long * offsetInEachDimension,
	  const unsigned int & numDimensions, const hid_t & datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
	}

	hid_t filespace = H5Dget_space(dataset);
	if (filespace < 1) {
		H5Dclose(dataset);
		throw invalid_argument("The filespace of resqml dataset " + datasetName + " could not be opened.");
	}
	herr_t result = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offsetInEachDimension, nullptr, numValuesInEachDimension, nullptr);
	if (result < 1){
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The hyperslabbing of resqml dataset " + datasetName + " could not be selected.");
	}

	hsize_t slab_size =1;
	for (unsigned int h = 0; h < numDimensions; ++h) {
		slab_size *= numValuesInEachDimension[h];
	}
	hid_t memspace = H5Screate_simple(1, &slab_size, nullptr);
	if (memspace < 1){
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The memory space for the slabbing of resqml dataset " + datasetName + " could not be created.");
	}

	hid_t readingError = H5Dread(dataset, datatype, memspace, filespace, H5P_DEFAULT, values);

	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);

	if (readingError < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be read.");
	}
}

int HdfProxy::getHdfDatatypeInDataset(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT); 
	hid_t datatype = H5Dget_type(dataset); 
	hid_t native_datatype =  H5Tget_native_type(datatype, H5T_DIR_ASCEND); 

	H5Dclose(dataset);
	H5Tclose(datatype);

	return native_datatype;
}

void HdfProxy::writeItemizedListOfList(const string & groupName,
			const string & name,
			const int & cumulativeLengthDatatype,
			void * cumulativeLength,
			const unsigned long long & cumulativeLengthSize,
			const int & elementsDatatype,
			void * elements,
			const unsigned long long & elementsSize)
{
	if (!isOpened()) {
		open();
	}

	hid_t parentGrp = openOrCreateGroupInResqmlGroup(groupName);
	hid_t grp = H5Gcreate(parentGrp, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	H5Gclose(parentGrp);

	// ************* CUMULATIVE LENGTH *************
	// Create dataspace for the dataset in the file.
	hid_t fspaceCL = H5Screate_simple(1, &cumulativeLengthSize, nullptr);

	hid_t datasetCL;
	if (compressionLevel) {
		// Create dataset and write it into the file.
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, 1, &cumulativeLengthSize);

		datasetCL = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, cumulativeLengthDatatype, fspaceCL, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		datasetCL = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, cumulativeLengthDatatype, fspaceCL, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Dwrite(datasetCL, cumulativeLengthDatatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, cumulativeLength);
	H5Sclose(fspaceCL);
	H5Dclose(datasetCL);

	// ************* ELEMENTS *************
	// Create dataspace for the dataset in the file.
	hid_t fspaceE = H5Screate_simple(1, &elementsSize, nullptr);

	hid_t datasetE;
	if (compressionLevel) {
		// Create dataset and write it into the file.
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, 1, &elementsSize);

		datasetE = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, elementsDatatype, fspaceE, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		datasetE = H5Dcreate(grp, ELEMENTS_DS_NAME, elementsDatatype, fspaceE, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Dwrite(datasetE, elementsDatatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, elements);
	H5Sclose(fspaceE);
	H5Dclose(datasetE);

	H5Gclose(grp);
}

unsigned int HdfProxy::getDimensionCount(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t dataspace = H5Dget_space(dataset);
	int result = H5Sget_simple_extent_ndims(dataspace);

	H5Sclose(dataspace);
	H5Dclose(dataset);

	return result;
}

hssize_t HdfProxy::getElementCount(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

    hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	
	hid_t dataspace = H5Dget_space(dataset);
	hssize_t result = H5Sget_simple_extent_npoints(dataspace);

	H5Sclose(dataspace);
	H5Dclose(dataset);

	return result;
}

void HdfProxy::writeArrayNdOfFloatValues(const string & groupName,
		const string & name,
		float * floatValues,
		hsize_t * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_FLOAT, floatValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfDoubleValues(const string & groupName,
		const string & name,
		double * dblValues,
		hsize_t * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_DOUBLE, dblValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfCharValues(const std::string & groupName,
		const std::string & name,
		char * intValues,
		unsigned long long * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_CHAR, intValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfIntValues(const string & groupName,
        const string & name,
        int * intValues,
        hsize_t * numValuesInEachDimension,
        const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_INT, intValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfGSoapULong64Values(const std::string & groupName,
		const std::string & name,
		ULONG64 * ulong64Values,
		hsize_t * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_ULLONG, ulong64Values, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNd(const std::string & groupName,
			const std::string & name,
			const int & datatype,
			void * values,
			unsigned long long * numValuesInEachDimension,
			const unsigned int & numDimensions)
{
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroupInResqmlGroup(groupName);
	if (grp < 0) {
		throw invalid_argument("The group " + groupName + " could not be created.");
	}

	// Create the data space
	hid_t space = H5Screate_simple(numDimensions, numValuesInEachDimension, nullptr);
	if (space < 0) {
		H5Gclose(grp);
		throw invalid_argument("The dataspace for the dataset " + name + " could not be created.");
	}

    // Create the dataset.
	herr_t error;
	hid_t dataset;
	if (compressionLevel) {
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, numDimensions, numValuesInEachDimension);

		dataset = H5Dcreate(grp, name.c_str(), datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
		if (dataset < 0) {
			H5Pclose(dcpl);
			H5Sclose(space);
			H5Gclose(grp);
			throw invalid_argument("The dataset " + name + " could not be created.");
		}

		H5Pclose(dcpl);
	}
	else {
		dataset = H5Dcreate (grp, name.c_str(), datatype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		if (dataset < 0) {
			H5Sclose(space);
			H5Gclose(grp);
			throw invalid_argument("The dataset " + name + " could not be created.");
		}
	}

	error = H5Dwrite(dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, values);
	if (error < 0) {
		H5Sclose(space);
		H5Dclose(dataset);
		H5Gclose(grp);
		throw invalid_argument("The data could not be written in dataset " + name);
	}

	H5Sclose(space);
	H5Dclose(dataset);
	H5Gclose(grp);
}

void HdfProxy::createArrayNd(
	const std::string& groupName,
	const std::string& datasetName,
	const int & datatype,
	unsigned long long* numValuesInEachDimension,
	const unsigned int& numDimensions
) {
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroupInResqmlGroup(groupName);

	// Create the data space
	hid_t space = H5Screate_simple(numDimensions, numValuesInEachDimension, nullptr);

	// Create the dataset.
	hid_t dataset;
	if (compressionLevel) {
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, numDimensions, numValuesInEachDimension);

		dataset = H5Dcreate (grp, datasetName.c_str(), datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		dataset = H5Dcreate (grp, datasetName.c_str(), datatype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Sclose(space);
	H5Dclose(dataset);
	H5Gclose(grp);

}


void HdfProxy::writeArrayNdSlab(
	const string& groupName,
	const string& datasetName,
	const int & datatype,
	void* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroupInResqmlGroup(groupName);
	hid_t dataset = H5Dopen(grp, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
	}
	
	hid_t filespace = H5Dget_space(dataset);
	if (filespace < 0) {
		throw invalid_argument("The resqml dataspace of " + datasetName + " could not be opened.");
	}
	herr_t errorCode = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offsetInEachDimension, nullptr, numValuesInEachDimension, nullptr);
	if (errorCode < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		H5Gclose(grp);
		throw invalid_argument("The slab of dataset " + datasetName + " could not have been selected");
	}

	hsize_t slab_size = 1;
	for(unsigned int h = 0; h < numDimensions; ++h){
		slab_size *= numValuesInEachDimension[h];
	}
	hid_t memspace = H5Screate_simple(1, &slab_size, nullptr);
	if (memspace < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		H5Gclose(grp);
		throw invalid_argument("The dataspace for the slab of the dataset " + datasetName + " could not be created.");
	}

	hid_t datatypeOfDataset = H5Dget_type(dataset);
	if (datatypeOfDataset < 0) {
		throw invalid_argument("The datatype of the dataset " + datasetName + " could not be retrieved.");
	}
	if (H5Tequal(datatype, datatypeOfDataset) <= 0) {
		throw invalid_argument("The given datatype for the slab is not compatible with the datatype of the dataset.");
	}
	errorCode = H5Dwrite(dataset, datatype, memspace, filespace, H5P_DEFAULT, values);

	H5Tclose(datatype);
	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);
	H5Gclose(grp);

	if (errorCode < 0) {
		throw invalid_argument("The data could not be written in dataset slab " + datasetName);
	}
}

void HdfProxy::readArrayNdOfDoubleValues(const std::string & datasetName, double* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfDoubleValues(
	  const std::string & datasetName, double* values,
	  hsize_t * numValuesInEachDimension,
	  hsize_t * offsetInEachDimension,
	  const unsigned int & numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfFloatValues(const std::string & datasetName, float* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_FLOAT);
}

void HdfProxy::readArrayNdOfFloatValues(
	const std::string& datasetName, float* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_FLOAT);
}

void HdfProxy::readArrayNdOfGSoapLong64Values(const std::string & datasetName, LONG64* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_LLONG);
}

void HdfProxy::readArrayNdOfGSoapULong64Values(const std::string & datasetName, ULONG64* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_ULLONG);
}

void HdfProxy::readArrayNdOfLongValues(const std::string & datasetName, long* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_LONG);
}

void HdfProxy::readArrayNdOfLongValues(
	const std::string& datasetName, long* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_LONG);
}

void HdfProxy::readArrayNdOfULongValues(const std::string & datasetName, unsigned long* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_ULONG);
}

void HdfProxy::readArrayNdOfIntValues(const std::string & datasetName, int* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_INT);
}

void HdfProxy::readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_UINT);
}

 void HdfProxy::readArrayNdOfShortValues(const std::string & datasetName, short* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_SHORT);
}

void HdfProxy::readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_USHORT);
}

void HdfProxy::readArrayNdOfCharValues(const std::string & datasetName, char* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_CHAR);
}

void HdfProxy::readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_UCHAR);
}

int HdfProxy::openOrCreateHdfResqmlGroup()
{
	if (!isOpened()) {
		open();
	}

	H5O_info_t info;
	herr_t status = H5Oget_info_by_name(hdfFile, "/RESQML", &info, H5P_DEFAULT);

	return status >= 0 ? H5Gopen(hdfFile, "/RESQML", H5P_DEFAULT) : H5Gcreate(hdfFile, "/RESQML", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
}

int HdfProxy::openOrCreateGroupInResqmlGroup(const string & groupName)
{
	hid_t resqmlGroup = openOrCreateHdfResqmlGroup();
	if (resqmlGroup < 0) {
		throw invalid_argument("The resqml group could not be opended or created in the hdf file.");
	}

	H5O_info_t info;
	herr_t status = H5Oget_info_by_name(resqmlGroup, groupName.c_str(), &info, H5P_DEFAULT);

	hid_t result = -1;
	if (status >= 0) {
		result = H5Gopen(resqmlGroup, groupName.c_str(), H5P_DEFAULT);
	}
	else {
		result = H5Gcreate(resqmlGroup, groupName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}
	
	H5Gclose(resqmlGroup);
	return result;
}

std::vector<hsize_t> HdfProxy::readArrayDimensions(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t dataspace = H5Dget_space(dataset);
	int nDim = H5Sget_simple_extent_ndims(dataspace);
	std::vector<hsize_t> dims(nDim, 0);
	H5Sget_simple_extent_dims(dataspace, &dims[0], nullptr);

	H5Sclose(dataspace);
	H5Dclose(dataset);

	return dims;
}
