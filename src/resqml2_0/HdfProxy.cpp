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
#include "resqml2_0/HdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0;
using namespace resqml2_0;
#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

HdfProxy::HdfProxy(common::EpcDocument* epcDoc, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath):
	EpcExternalPartReference(epcDoc, guid, title, packageDirAbsolutePath, externalFilePath), hdfFile(NULL), compressionLevel(0)
{
	static_cast<_eml__EpcExternalPartReference*>(gsoapProxy)->MimeType = "application/x-hdf5";
}

void HdfProxy::openForWriting()
{
	if (hdfFile)
	{
		close();
	}
	hdfFile = new H5File( (packageDirectoryAbsolutePath+relativeFilePath).c_str(), H5F_ACC_TRUNC ); // Issues when using H5std_string with prebuilt HDF5 binaries in debug mode 32 bits (HDF 1.8.12).

	// Add the uuid of the HDF proxy as an attribute of the hdfFile
#if H5_VERSION_GE(1,8,12)
	hsize_t attributeDims[] = {getUuid().size() + 1};
	DataSpace attributeDataSpace( 1, attributeDims );

	Attribute attribute = hdfFile->createAttribute("uuid", PredType::C_S1, attributeDataSpace);
	attribute.write( PredType::C_S1, getUuid().c_str() );

	attribute.close();
	attributeDataSpace.close();
#else
	hid_t aid  = H5Screate(H5S_SCALAR);
	hid_t atype = H5Tcopy(H5T_C_S1);
	H5Tset_size(atype, getUuid().size() + 1);
	H5Tset_strpad(atype,H5T_STR_NULLTERM);
	hid_t attribute_id = H5Acreate2(hdfFile->getId(), "uuid", atype, aid, H5P_DEFAULT, H5P_DEFAULT);

	/* Write the attribute data. */
	int status = H5Awrite(attribute_id, atype, getUuid().c_str());
	/* Close the attribute. */
	status = H5Sclose(aid);
	status = H5Tclose(atype);
	status = H5Aclose(attribute_id);
#endif
}

void HdfProxy::openForReading()
{
	if (hdfFile)
	{
		close();
	}

	hdfFile = new H5File( (packageDirectoryAbsolutePath+relativeFilePath).c_str(), H5F_ACC_RDONLY);
}

void HdfProxy::close()
{
	if (hdfFile)
	{
		hdfFile->close();
		delete hdfFile;
		hdfFile = NULL;
	}
}

H5::DataType HdfProxy::getHdfDatatypeInDataset(const std::string & datasetName)
{
	if (!isOpened())
		openForReading();

	return hdfFile->openDataSet(datasetName.c_str()).getDataType();
}

void HdfProxy::writeItemizedListOfUnsignedInt(const string & groupName,
			const string & name,
			unsigned int * cumulativeLength,
			const hsize_t & cumulativeLengthSize,
			unsigned int * elements,
			const hsize_t & elementsSize)
{
	if (!isOpened())
		openForWriting();

	Group parentGrp = getOrCreateGroupInResqmlGroup(groupName.c_str());
	Group grp = parentGrp.createGroup(name.c_str());
	parentGrp.close();

	// ************* CUMULATIVE LENGTH *************
	// Create dataspace for the dataset in the file.
	hsize_t fdimCL[] = {cumulativeLengthSize};
	DataSpace fspaceCL( 1, fdimCL );

	if (compressionLevel)
	{
		// Create dataset and write it into the file.
		DSetCreatPropList ds_creatplistCL;  // create dataset creation prop list
		ds_creatplistCL.setChunk( 1, fdimCL );  // then modify it for compression
		ds_creatplistCL.setDeflate( compressionLevel );
		DataSet datasetCL = grp.createDataSet(CUMULATIVE_LENGTH_DS_NAME, PredType::NATIVE_UINT, fspaceCL, ds_creatplistCL);

		// Write data to the dataset;
		datasetCL.write(cumulativeLength, PredType::NATIVE_UINT);

		fspaceCL.close();
		ds_creatplistCL.close();
		datasetCL.close();
	}
	else
	{
		DataSet datasetCL = grp.createDataSet(CUMULATIVE_LENGTH_DS_NAME, PredType::NATIVE_UINT, fspaceCL);
		datasetCL.write(cumulativeLength, PredType::NATIVE_UINT);

		fspaceCL.close();
		datasetCL.close();
	}

	

	// ************* ELEMENTS *************
	// Create dataspace for the dataset in the file.
	hsize_t fdimE[] = {elementsSize};
	DataSpace fspaceE( 1, fdimE );

	if (compressionLevel)
	{
		// Create dataset and write it into the file.
		DSetCreatPropList ds_creatplistE;  // create dataset creation prop list
		ds_creatplistE.setChunk( 1, fdimE );  // then modify it for compression
		ds_creatplistE.setDeflate( compressionLevel );
		DataSet datasetE = grp.createDataSet(ELEMENTS_DS_NAME, PredType::NATIVE_UINT, fspaceE, ds_creatplistE);

		// Write data to the dataset;
		datasetE.write(elements, PredType::NATIVE_UINT);

		fspaceE.close();
		ds_creatplistE.close();
		datasetE.close();
	}
	else
	{
		DataSet datasetE = grp.createDataSet(ELEMENTS_DS_NAME, PredType::NATIVE_UINT, fspaceE);
		datasetE.write(elements, PredType::NATIVE_UINT);

		fspaceE.close();
		datasetE.close();
	}

	grp.close();
}

unsigned int HdfProxy::getDimensionCount(const std::string & datasetName)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());

	DataSpace dataspace = dataset.getSpace();
	unsigned int result = dataspace.getSimpleExtentNdims();

	dataspace.close();
	dataset.close();

	return result;
}

unsigned int HdfProxy::getElementCount(const std::string & datasetName)
{
	if (!isOpened())
		openForReading();

    DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	DataSpace dataspace = dataset.getSpace();

	unsigned int result = dataspace.getSimpleExtentNpoints();

	dataspace.close();
	dataset.close();

	return result;
}

void HdfProxy::writeArrayNdOfFloatValues(const string & groupName,
			const string & name,
			float * floatValues,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, PredType::NATIVE_FLOAT, floatValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfDoubleValues(const string & groupName,
			const string & name,
			double * dblValues,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, PredType::NATIVE_DOUBLE, dblValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfIntValues(const string & groupName,
        const string & name,
        int * intValues,
        hsize_t * numValuesInEachDimension,
        const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, PredType::NATIVE_INT, intValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNd(const string & groupName,
			const string & name,
			const H5::DataType & datatype,
			void * values,
			hsize_t * numValuesInEachDimension,
			const unsigned int & numDimensions)
{
	if (!isOpened())
		openForWriting();

	Group grp = getOrCreateGroupInResqmlGroup(groupName.c_str());

	// Create the data space
    DataSpace space(numDimensions, numValuesInEachDimension);

    // Create the dataset.
	if (compressionLevel)
	{
		DSetCreatPropList ds_creatplist;  // create dataset creation prop list
		ds_creatplist.setChunk( numDimensions, numValuesInEachDimension );  // then modify it for compression
		ds_creatplist.setDeflate( compressionLevel );
		DataSet dataset = grp.createDataSet(name.c_str(), datatype, space, ds_creatplist);

		dataset.write(values, datatype);

		space.close();
		ds_creatplist.close();
		dataset.close();
	}
	else
	{
		DataSet dataset = grp.createDataSet(name.c_str(), datatype, space);

		dataset.write(values, datatype);

		space.close();
		dataset.close();
	}

	grp.close();
}

void HdfProxy::createArrayNd(
	const string& groupName,
	const string& datasetName,
	const H5::DataType& datatype,
	hsize_t* numValuesInEachDimension,
	const unsigned int& numDimensions
) {
	if (!isOpened()) {
		openForWriting();
	}

	Group grp = getOrCreateGroupInResqmlGroup(groupName.c_str());

	// Create the data space
	DataSpace space(numDimensions, numValuesInEachDimension);

	// Create the dataset.
	if (compressionLevel) {
		// create dataset creation prop list
		DSetCreatPropList ds_creatplist;

		// then modify it for compression
		ds_creatplist.setChunk( numDimensions, numValuesInEachDimension );
		ds_creatplist.setDeflate( compressionLevel );
		DataSet dataset = grp.createDataSet(
			datasetName.c_str(), datatype, space, ds_creatplist
		);

		dataset.close();
		ds_creatplist.close();
	} else {
		DataSet dataset = grp.createDataSet(datasetName.c_str(), datatype, space);
		dataset.close();
	}

	space.close();
	grp.close();
}


void HdfProxy::writeArrayNdSlab(
	const string& groupName,
	const string& datasetName,
	void* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions
) {
	if (!isOpened()) {
		openForWriting();
	}

	Group grp = getOrCreateGroupInResqmlGroup(groupName.c_str());
	DataSet dataset = grp.openDataSet(datasetName.c_str());

	DataSpace filespace = dataset.getSpace();
	filespace.selectHyperslab(
		H5S_SELECT_SET, numValuesInEachDimension, offsetInEachDimension);

	hsize_t slab_size = 1;
	for(int h = 0; h < numDimensions; h++){
		slab_size *= numValuesInEachDimension[h];
	}

	DataSpace memspace;
	memspace.setExtentSimple(1, &slab_size, &slab_size);
	dataset.write(values, dataset.getDataType(), memspace, filespace);

	memspace.close();
	filespace.close();
	dataset.close();
	grp.close();
}

void HdfProxy::readArrayNdOfDoubleValues(const std::string & datasetName, double* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_DOUBLE);
	dataset.close();
}

void HdfProxy::readArrayNdOfFloatValues(const std::string & datasetName, float* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_FLOAT);
	dataset.close();
}

void HdfProxy::readArrayNdOfFloatValues(
	const std::string& datasetName, float* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	if (!isOpened()) {
		openForReading();
	}

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());

	DataSpace filespace = dataset.getSpace();
	filespace.selectHyperslab(
		H5S_SELECT_SET, numValuesInEachDimension, offsetInEachDimension);

	hsize_t slab_size =1;
	for(int h=0; h<numDimensions; h++){
		slab_size *= numValuesInEachDimension[h];
	}

	H5::DataSpace memspace;
	memspace.setExtentSimple(1, &slab_size, &slab_size);

	dataset.read(values, PredType::NATIVE_FLOAT, memspace, filespace);

	memspace.close();
	filespace.close();
	dataset.close();
}

void HdfProxy::readArrayNdOfLongValues(const std::string & datasetName, long* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_LONG);
	dataset.close();
}

void HdfProxy::readArrayNdOfLongValues(
	const std::string& datasetName, long* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	if (!isOpened()) {
		openForReading();
	}

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());

	DataSpace filespace = dataset.getSpace();
	filespace.selectHyperslab(
		H5S_SELECT_SET, numValuesInEachDimension, offsetInEachDimension);

	hsize_t slab_size =1;
	for(int h=0; h<numDimensions; h++){
		slab_size *= numValuesInEachDimension[h];
	}

	DataSpace memspace;
	memspace.setExtentSimple(1, &slab_size, &slab_size);

	dataset.read(values, PredType::NATIVE_LONG, memspace, filespace);

	memspace.close();
	filespace.close();
	dataset.close();
}

void HdfProxy::readArrayNdOfULongValues(const std::string & datasetName, unsigned long* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_ULONG);
	dataset.close();
}

void HdfProxy::readArrayNdOfIntValues(const std::string & datasetName, int* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_INT);
	dataset.close();
}

void HdfProxy::readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_UINT);
	dataset.close();
}

 void HdfProxy::readArrayNdOfShortValues(const std::string & datasetName, short* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_SHORT);
	dataset.close();
}

void HdfProxy::readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_USHORT);
	dataset.close();
}

void HdfProxy::readArrayNdOfCharValues(const std::string & datasetName, char* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_CHAR);
	dataset.close();
}

void HdfProxy::readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());
	dataset.read(values, PredType::NATIVE_UCHAR);
	dataset.close();
}

Group HdfProxy::getOrCreateHdfResqmlGroup()
{
	if (!isOpened())
		openForWriting();

	for (hsize_t i=0; i < hdfFile->getNumObjs(); i++)
	{
		if (hdfFile->getObjTypeByIdx(i) == H5G_GROUP)
		{
			char objName[1024]; // Issues when using H5std_string with prebuilt HDF5 binaries in debug mode 32 bits (HDF 1.8.12).
			hdfFile->getObjnameByIdx(i, objName, 1024);
			if (strcmp(objName, "RESQML") == 0)
			{
				return hdfFile->openGroup("/RESQML");
			}
		}
	}
	return hdfFile->createGroup("/RESQML", 6);
}

Group HdfProxy::getOrCreateGroupInResqmlGroup(const string & groupName)
{
	Group resqmlGrp = getOrCreateHdfResqmlGroup();
	for (hsize_t i=0; i < resqmlGrp.getNumObjs(); i++)
	{
		if (resqmlGrp.getObjTypeByIdx(i) == H5G_GROUP)
		{
			char objName[1024]; // Issues when using H5std_string with prebuilt HDF5 binaries in debug mode 32 bits (HDF 1.8.12).
			resqmlGrp.getObjnameByIdx(i, objName, 1024);
			if (strcmp(objName, groupName.c_str()) == 0)
			{
				Group result = resqmlGrp.openGroup(objName);
				resqmlGrp.close();
				return result;
			}
		}
	}
	Group result = resqmlGrp.createGroup(groupName.c_str()); // Issues when using H5std_string with prebuilt HDF5 binaries in debug mode 32 bits (HDF 1.8.12).
	resqmlGrp.close();
	return result;
}

std::vector<hsize_t> HdfProxy::readArrayDimensions(const std::string & datasetName)
{
	if (!isOpened())
		openForReading();

	DataSet dataset = hdfFile->openDataSet(datasetName.c_str());

	DataSpace dataspace = dataset.getSpace();
	int nDim = dataspace.getSimpleExtentNdims();
	std::vector<hsize_t> dims(nDim, 0);
	dataspace.getSimpleExtentDims(&dims[0]);

	dataspace.close();
	dataset.close();

	return dims;
}
