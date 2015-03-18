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
#include "resqml2_0/UnstructuredGridRepresentation.h"

#include <stdexcept>

#include "resqml2_0/AbstractLocal3dCrs.h"
#include "resqml2_0/HdfProxy.h"
//#include "Vector3d.h"

using namespace std;
using namespace gsoap_resqml2_0;
using namespace resqml2_0;

const char* UnstructuredGridRepresentation::XML_TAG = "UnstructuredGridRepresentation";

UnstructuredGridRepresentation::UnstructuredGridRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & cellCount):
	AbstractGridRepresentation(NULL, crs)
{
	if (!epcDoc)
		throw invalid_argument("The EPC document where the unstructured grid will be stored cannot be null.");
	if (!crs)
		throw invalid_argument("The local CRS of the unstructured grid cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREUnstructuredGridRepresentation(epcDoc->getGsoapContext(), 1);
	_resqml2__UnstructuredGridRepresentation* unstructuredGrid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);

	unstructuredGrid->CellCount = cellCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// epc document
	epcDoc->addGsoapProxy(this);

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);
}

gsoap_resqml2_0::resqml2__PointGeometry* UnstructuredGridRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->Geometry;
	else
		return NULL;
}

string UnstructuredGridRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

unsigned long UnstructuredGridRepresentation::getCellCount() const
{
	return static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->CellCount;
}

unsigned long UnstructuredGridRepresentation::getFaceCount() const
{
	_resqml2__UnstructuredGridRepresentation* grid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
	if (grid->Geometry)
		return grid->Geometry->FaceCount;
	else
		return 0;
}

unsigned long UnstructuredGridRepresentation::getNodeCount() const
{
	_resqml2__UnstructuredGridRepresentation* grid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
	if (grid->Geometry)
		return grid->Geometry->NodeCount;
	else
		return 0;
}

unsigned int UnstructuredGridRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return getNodeCount();
	else
		return 0;
}

void UnstructuredGridRepresentation::getFacesOfCells(unsigned int * faceIndices) const
{
	_resqml2__UnstructuredGridRepresentation* grid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
	if (grid->Geometry == NULL)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->Elements)->Values->PathInHdfFile, faceIndices);
	}
}

void UnstructuredGridRepresentation::getFaceCountOfCells(unsigned int * faceCountPerCell) const
{
	_resqml2__UnstructuredGridRepresentation* grid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
		if (grid->Geometry == NULL)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->CumulativeLength)->Values->PathInHdfFile, faceCountPerCell);
	}
}

void UnstructuredGridRepresentation::getNodesOfFaces(unsigned int * nodeIndices) const
{
	_resqml2__UnstructuredGridRepresentation* grid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
	if (grid->Geometry == NULL)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->Elements)->Values->PathInHdfFile, nodeIndices);
	}
}

void UnstructuredGridRepresentation::getNodeCountOfFaces(unsigned int * NodeCountPerFace) const
{
	_resqml2__UnstructuredGridRepresentation* grid = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
		if (grid->Geometry == NULL)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->CumulativeLength)->Values->PathInHdfFile, NodeCountPerFace);
	}
}

void UnstructuredGridRepresentation::setGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, HdfProxy * proxy,
				unsigned int * faceIndicesPerCell, unsigned int * faceIndicesCumulativeCountPerCell, const unsigned int & faceCount,
				unsigned int * nodeIndicesPerFace, unsigned int * nodeIndicesCumulativeCountPerFace, const unsigned int & nodeCount,
				const gsoap_resqml2_0::resqml2__CellShape & cellShape)
{
	if (!proxy)
		throw invalid_argument("The hdf proxy cannot be null.");
	if (!points)
		throw invalid_argument("The points of the ijk grid cannot be null.");
	if (!faceIndicesPerCell)
		throw invalid_argument("The definition of the face indices per cell is incomplete.");
	if (!faceIndicesCumulativeCountPerCell)
		throw invalid_argument("The definition of the face indices count per cell is incomplete.");
	if (!nodeIndicesPerFace)
		throw invalid_argument("The definition of the node indices per face is incomplete.");
	if (!nodeIndicesCumulativeCountPerFace)
		throw invalid_argument("The definition of the node indices count per face is incomplete.");

	setHdfProxy(proxy);
	unsigned long cellCount = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->CellCount;

	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy->soap, 1);
	static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->Geometry = geom;
	static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->Geometry->LocalCrs = localCrs->newResqmlReference();

	// Right handed
	resqml2__BooleanConstantArray* constantBoolArray = soap_new_resqml2__BooleanConstantArray(gsoapProxy->soap, 1);
	constantBoolArray->Count = faceIndicesCumulativeCountPerCell[faceCount-1];
	constantBoolArray->Value = isRightHanded;
	geom->CellFaceIsRightHanded = constantBoolArray;

	geom->FaceCount = faceCount;
	geom->NodeCount = nodeCount;
	geom->CellShape = cellShape;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	// Cumulative
	resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->FacesPerCell->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = faceIndicesCumulativeCountPerCell[cellCount - 1] + 1;
	cumulativeLength->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/FacesPerCell/" + CUMULATIVE_LENGTH_DS_NAME;
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/FacesPerCell/" + ELEMENTS_DS_NAME;
	// HDF
	hdfProxy->writeItemizedListOfUnsignedInt(gsoapProxy->uuid, "FacesPerCell", faceIndicesCumulativeCountPerCell, cellCount, faceIndicesPerCell, faceIndicesCumulativeCountPerCell[cellCount - 1]);

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	// Cumulative
	cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = nodeIndicesCumulativeCountPerFace[faceCount - 1] + 1;
	cumulativeLength->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/NodesPerFace/" + CUMULATIVE_LENGTH_DS_NAME;
	// Elements
	elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = nodeCount;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/NodesPerFace/" + ELEMENTS_DS_NAME;
	// HDF
	hdfProxy->writeItemizedListOfUnsignedInt(gsoapProxy->uuid, "NodesPerFace", nodeIndicesCumulativeCountPerFace, faceCount, nodeIndicesPerFace, nodeIndicesCumulativeCountPerFace[faceCount - 1]);

	// XML points
	resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/Points";
	// HDF
	hsize_t * numValues = new hsize_t[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "Points", points, numValues, 2);
	delete [] numValues;
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, const unsigned int & faceCount, HdfProxy * proxy,
						unsigned int * faceIndicesPerCell, unsigned int * nodeIndicesPerFace)
{
	if (!proxy)
		throw invalid_argument("The hdf proxy cannot be null.");
	if (!points)
		throw invalid_argument("The points of the ijk grid cannot be null.");
	if (!faceIndicesPerCell)
		throw invalid_argument("The definition of the face indices per cell is incomplete.");
	if (!nodeIndicesPerFace)
		throw invalid_argument("The definition of the node indices per face is incomplete.");

	setHdfProxy(proxy);
	unsigned long cellCount = static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->CellCount;

	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy->soap, 1);
	static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->Geometry = geom;
	static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy)->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	geom->CellShape = resqml2__CellShape__tetrahedral;

	// Right handed
	resqml2__BooleanConstantArray* constantBoolArray = soap_new_resqml2__BooleanConstantArray(gsoapProxy->soap, 1);
	constantBoolArray->Count = geom->FaceCount;
	constantBoolArray->Value = isRightHanded;
	geom->CellFaceIsRightHanded = constantBoolArray;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	// Cumulative
	if (cellCount == 1)
	{
		resqml2__IntegerConstantArray* cumulativeLength = soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->Count = cellCount;
		cumulativeLength->Value = 4;
	}
	else
	{
		resqml2__IntegerLatticeArray* cumulativeLength = soap_new_resqml2__IntegerLatticeArray(gsoapProxy->soap, 1);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->StartValue = 4;
		cumulativeLength->Offset.push_back(soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1));
		cumulativeLength->Offset[0]->Count = cellCount - 1;
		cumulativeLength->Offset[0]->Value = 4;
	}
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/FacesPerCell";
	// HDF
	hsize_t * numValues = new hsize_t[2];
	numValues[0] = cellCount;
	numValues[1] = 4;
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "FacesPerCell", H5::PredType::NATIVE_UINT, faceIndicesPerCell, numValues, 2);
	delete [] numValues;

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	// Cumulative
	resqml2__IntegerLatticeArray* cumulativeLength = soap_new_resqml2__IntegerLatticeArray(gsoapProxy->soap, 1);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->StartValue = 3;
	cumulativeLength->Offset.push_back(soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1));
	cumulativeLength->Offset[0]->Count = geom->FaceCount - 1;
	cumulativeLength->Offset[0]->Value = 3;
	// Elements
	elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/NodesPerFace";
	// HDF
	numValues = new hsize_t[2];
	numValues[0] = faceCount;
	numValues[1] = 3;
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "NodesPerFace", H5::PredType::NATIVE_UINT, nodeIndicesPerFace, numValues, 2);
	delete [] numValues;

	// XML points
	resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/Points";
	// HDF
	numValues = new hsize_t[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "Points", points, numValues, 2);
	delete [] numValues;
}