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
#include "resqml2_0_1/UnstructuredGridRepresentation.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;

const char* UnstructuredGridRepresentation::XML_TAG = "UnstructuredGridRepresentation";


void UnstructuredGridRepresentation::init(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & cellCount)
{
	if (!epcDoc)
		throw invalid_argument("The EPC document where the unstructured grid will be stored cannot be null.");
	if (!crs)
		throw invalid_argument("The local CRS of the unstructured grid cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREUnstructuredGridRepresentation(epcDoc->getGsoapContext(), 1);
	_resqml2__UnstructuredGridRepresentation* unstructuredGrid = getSpecializedGsoapProxy();

	unstructuredGrid->CellCount = cellCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// epc document
	epcDoc->addGsoapProxy(this);

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & cellCount):
	AbstractGridRepresentation(nullptr, crs), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
	cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
	nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr)
{
	init(epcDoc, crs, guid, title, cellCount);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & cellCount):
	AbstractGridRepresentation(interp, crs), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
	cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
	nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the unstructured grid cannot be null.");

	init(interp->getEpcDocument(), crs, guid, title, cellCount);

	// relationhsips
	setInterpretation(interp);
}

_resqml2__UnstructuredGridRepresentation* UnstructuredGridRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial() == true)
		throw logic_error("Partial object");

	return static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy);
}

gsoap_resqml2_0_1::resqml2__PointGeometry* UnstructuredGridRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return getSpecializedGsoapProxy()->Geometry;
	else
		return nullptr;
}

string UnstructuredGridRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

ULONG64 UnstructuredGridRepresentation::getCellCount() const
{
	return getSpecializedGsoapProxy()->CellCount;
}

ULONG64 UnstructuredGridRepresentation::getFaceCount() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry)
		return grid->Geometry->FaceCount;
	else
		return 0;
}

ULONG64 UnstructuredGridRepresentation::getNodeCount() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry)
		return grid->Geometry->NodeCount;
	else
		return 0;
}

ULONG64 UnstructuredGridRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return getNodeCount();
	else
		return 0;
}

void UnstructuredGridRepresentation::getFaceIndicesOfCells(ULONG64 * faceIndices) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->Elements)->Values->PathInHdfFile, faceIndices);	
	}
	else
		throw logic_error("Not yet implemented");
}

void UnstructuredGridRepresentation::getCumulativeFaceCountPerCell(ULONG64 * cumulativeFaceCountPerCell) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == NULL)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->CumulativeLength)->Values->PathInHdfFile, cumulativeFaceCountPerCell);
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		cumulativeFaceCountPerCell[0] = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value;
		const ULONG64 cellCount = getCellCount();
		for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
		{
			cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		cumulativeFaceCountPerCell[0] = static_cast<resqml2__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
}

void UnstructuredGridRepresentation::getFaceCountPerCell(ULONG64 * faceCountPerCell) const
{
	getCumulativeFaceCountPerCell(faceCountPerCell);
	const ULONG64 cellCount = getCellCount();
	for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
	{
		faceCountPerCell[cumulativeFaceCountPerCellIndex] -= faceCountPerCell[cumulativeFaceCountPerCellIndex - 1];
	}
}

bool UnstructuredGridRepresentation::isFaceCountOfCellsConstant() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == NULL)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral || grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		if (static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue == static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value)
			return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantFaceCountOfCells() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (isFaceCountOfCellsConstant() == false)
		throw invalid_argument("The face count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral)
	{
		return 6;
	}
	else if (grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return 4;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		return static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return static_cast<resqml2__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getNodeIndicesOfFaces(ULONG64 * nodeIndices) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == NULL)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->Elements)->Values->PathInHdfFile, nodeIndices);
	}
	else
		throw logic_error("Not yet implemented");
}

void UnstructuredGridRepresentation::getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
		if (grid->Geometry == NULL)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->CumulativeLength)->Values->PathInHdfFile, nodeCountPerFace);
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		nodeCountPerFace[0] = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value;
		const ULONG64 faceCount = getFaceCount();
		for (ULONG64 nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex)
		{
			nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		throw range_error("The *cumulative* length of nodes count per cells cannot be constant.");
	}
}

void UnstructuredGridRepresentation::getNodeCountPerFace(ULONG64 * nodeCountPerFace) const
{
	getCumulativeNodeCountPerFace(nodeCountPerFace);
	const ULONG64 faceCount = getFaceCount();
	for (ULONG64 cumulativeNodeCountPerFaceIndex = 1; cumulativeNodeCountPerFaceIndex < faceCount; ++cumulativeNodeCountPerFaceIndex)
	{
		nodeCountPerFace[cumulativeNodeCountPerFaceIndex] -= nodeCountPerFace[cumulativeNodeCountPerFaceIndex - 1];
	}
}

bool UnstructuredGridRepresentation::isNodeCountOfFacesContant() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == NULL)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral || grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		if (static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue == static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value)
			return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantNodeCountOfFaces() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (isNodeCountOfFacesContant() == false)
		throw invalid_argument("The node count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral)
	{
		return 4;
	}
	else if (grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return 3;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		return static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getCellFaceIsRightHanded(char* cellFaceIsRightHanded) const
{
  _resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
  if (grid->Geometry == NULL)
    throw invalid_argument("There is no geometry in this grid.");
  if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
  {
    hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellFaceIsRightHanded)->Values->PathInHdfFile, cellFaceIsRightHanded);
  }
  else
	  throw logic_error("Not yet implemented.");
}

void UnstructuredGridRepresentation::setGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, AbstractHdfProxy * proxy,
				unsigned int * faceIndicesPerCell, unsigned int * faceIndicesCumulativeCountPerCell, const unsigned int & faceCount,
				unsigned int * nodeIndicesPerFace, unsigned int * nodeIndicesCumulativeCountPerFace, const unsigned int & nodeCount,
				const gsoap_resqml2_0_1::resqml2__CellShape & cellShape)
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
	unsigned long cellCount = getSpecializedGsoapProxy()->CellCount;

	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy->soap, 1);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

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

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, const unsigned int & faceCount, AbstractHdfProxy * proxy,
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
	unsigned long cellCount = getSpecializedGsoapProxy()->CellCount;

	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy->soap, 1);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

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
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "FacesPerCell", H5T_NATIVE_UINT, faceIndicesPerCell, numValues, 2);
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
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "NodesPerFace", H5T_NATIVE_UINT, nodeIndicesPerFace, numValues, 2);
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

void UnstructuredGridRepresentation::loadGeometry()
{
	unloadGeometry();

	if (isNodeCountOfFacesContant() == true)
	{
		constantNodeCountPerFace = getConstantNodeCountOfFaces();
		nodeIndicesOfFaces = new ULONG64[constantNodeCountPerFace * getFaceCount()];
	}
	else
	{
		cumulativeNodeCountPerFace = new ULONG64[getFaceCount()];
		getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace);
		nodeIndicesOfFaces = new ULONG64[cumulativeNodeCountPerFace[getFaceCount() - 1]];
	}

	if (isFaceCountOfCellsConstant() == true)
	{
		constantFaceCountPerCell = getConstantFaceCountOfCells();
		faceIndicesOfCells = new ULONG64[constantFaceCountPerCell * getCellCount()];
	}
	else
	{
		cumulativeFaceCountPerCell = new ULONG64[getCellCount()];
		getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell);
		faceIndicesOfCells = new ULONG64[cumulativeFaceCountPerCell[getCellCount() - 1]];
	}

	getNodeIndicesOfFaces(nodeIndicesOfFaces);

	getFaceIndicesOfCells(faceIndicesOfCells);
}

void UnstructuredGridRepresentation::unloadGeometry()
{
	constantNodeCountPerFace = 0;
	constantFaceCountPerCell = 0;

  delete[] cumulativeNodeCountPerFace;
  cumulativeNodeCountPerFace = nullptr;
  delete[] cumulativeFaceCountPerCell;
  cumulativeFaceCountPerCell = nullptr;
  delete[] nodeIndicesOfFaces;
  nodeIndicesOfFaces = nullptr;
  delete[] faceIndicesOfCells;
  faceIndicesOfCells = nullptr;
}

unsigned int UnstructuredGridRepresentation::getFaceCountOfCell(const ULONG64 & cellIndex) const
{
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");

	if (constantFaceCountPerCell != 0)
		return constantFaceCountPerCell;

	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");

	if (cellIndex == 0)
		return cumulativeFaceCountPerCell[0];
	
	return cumulativeFaceCountPerCell[cellIndex] -  cumulativeFaceCountPerCell[cellIndex-1];
}

unsigned int UnstructuredGridRepresentation::getNodeCountOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const
{
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");
	if (localFaceIndex >= getFaceCountOfCell(cellIndex))
		throw range_error("The face index is out of range.");
	
	if (constantNodeCountPerFace != 0)
		return constantNodeCountPerFace;

	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");

	// Global face index
	ULONG64 globalFaceIndex = 0;
	if (cellIndex == 0)
		globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[0] + localFaceIndex];
	else
		globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[cellIndex-1] + localFaceIndex];
	
	if (globalFaceIndex == 0)
		return cumulativeNodeCountPerFace[0];

	return cumulativeNodeCountPerFace[globalFaceIndex] -  cumulativeNodeCountPerFace[globalFaceIndex-1];
}

ULONG64 * UnstructuredGridRepresentation::getNodeIndicesOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const
{
	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");
	if (localFaceIndex >= getFaceCountOfCell(cellIndex))
		throw range_error("The face index is out of range.");

	// Global face index
	ULONG64 globalFaceIndex = 0;
	if (cellIndex == 0)
		globalFaceIndex = faceIndicesOfCells[localFaceIndex];
	else
	{
		if (constantFaceCountPerCell != 0)
			globalFaceIndex = faceIndicesOfCells[constantFaceCountPerCell * cellIndex + localFaceIndex];
		else
			globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[cellIndex-1] + localFaceIndex];
	}

	if (globalFaceIndex == 0)
		return nodeIndicesOfFaces;

	if (constantNodeCountPerFace != 0)
		return &(nodeIndicesOfFaces[constantNodeCountPerFace * globalFaceIndex]);
	else
		return &(nodeIndicesOfFaces[cumulativeNodeCountPerFace[globalFaceIndex-1]]);
}
