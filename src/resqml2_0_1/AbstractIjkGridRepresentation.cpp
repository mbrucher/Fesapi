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
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/CategoricalProperty.h"
#include "resqml2_0_1/CommentProperty.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/DiscretePropertySeries.h"
#include "resqml2_0_1/StringTableLookup.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;

const char* AbstractIjkGridRepresentation::XML_TAG = "IjkGridRepresentation";

void AbstractIjkGridRepresentation::init(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	if (epcDoc == nullptr)
		throw invalid_argument("The EPC document where the ijk grid will be stored cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREIjkGridRepresentation(epcDoc->getGsoapContext(), 1);
	_resqml2__IjkGridRepresentation* ijkGrid = getSpecializedGsoapProxy();

	ijkGrid->Ni = iCount;
	ijkGrid->Nj = jCount;
	ijkGrid->Nk = kCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// epc document
	epcDoc->addGsoapProxy(this);

	// relationhsips
	if (crs != nullptr)
	{
		localCrs = crs;
		localCrs->addRepresentation(this);
	}
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(nullptr, crs), splitInformation(nullptr)
{
	init(epcDoc, crs, guid, title, iCount, jCount, kCount);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(interp, crs), splitInformation(nullptr)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the IJK grid cannot be null.");

	init(interp->getEpcDocument(), crs, guid, title, iCount, jCount, kCount);

	// relationhsips
	setInterpretation(interp);
}

_resqml2__IjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial() == true)
		throw logic_error("Partial object");

	return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
}

gsoap_resqml2_0_1::resqml2__PointGeometry* AbstractIjkGridRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return getSpecializedGsoapProxy()->Geometry;
	else
		throw range_error("There cannot be more than one patch is an ijk grid representation.");
}

unsigned int AbstractIjkGridRepresentation::getICellCount() const
{
	return getSpecializedGsoapProxy()->Ni;
}

void AbstractIjkGridRepresentation::setICellCount(const unsigned int & iCount)
{
	getSpecializedGsoapProxy()->Ni = iCount;
}

unsigned int AbstractIjkGridRepresentation::getJCellCount() const
{
	return (int)getSpecializedGsoapProxy()->Nj;
}

void AbstractIjkGridRepresentation::setJCellCount(const unsigned int & jCount)
{
	getSpecializedGsoapProxy()->Nj = jCount;
}

bool AbstractIjkGridRepresentation::isRightHanded() const
{
	if (getSpecializedGsoapProxy()->Geometry)
		return getSpecializedGsoapProxy()->Geometry->GridIsRighthanded;
	else
		throw invalid_argument("The grid has no geometry.");
}

void AbstractIjkGridRepresentation::getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry->SplitCoordinateLines == nullptr)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->PillarIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->PillarIndices)->Values->PathInHdfFile, pillarIndices);
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		if (reverseIAxis)
		{
			for (unsigned int index = 0; index < getSplitCoordinateLineCount(); ++index)
			{
				unsigned int iPillar = pillarIndices[index] % iPillarCount;
				unsigned int jPillar = pillarIndices[index] / iPillarCount;
				pillarIndices[index] = (getICellCount() - iPillar) + jPillar*iPillarCount;
			}
		}
		if (reverseJAxis)
		{
			for (unsigned int index = 0; index < getSplitCoordinateLineCount(); ++index)
			{
				unsigned int iPillar = pillarIndices[index] % iPillarCount;
				unsigned int jPillar = pillarIndices[index] / iPillarCount;
				pillarIndices[index] = iPillar + (getJCellCount()-jPillar)*iPillarCount;
			}
		}
	}
}

void AbstractIjkGridRepresentation::getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry->SplitCoordinateLines == nullptr)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile, columnIndices);
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		hssize_t datasetValueCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile);
		if (reverseIAxis)
		{
			for (unsigned int index = 0; index < datasetValueCount; ++index)
			{
				unsigned int iColumn = columnIndices[index] % getICellCount();
				unsigned int jColumn = columnIndices[index] / getICellCount();
				columnIndices[index] = (getICellCount() - 1 - iColumn) + jColumn*getICellCount();
			}
		}
		if (reverseJAxis)
		{
			for (unsigned int index = 0; index < datasetValueCount; ++index)
			{
				unsigned int iColumn = columnIndices[index] % getICellCount();
				unsigned int jColumn = columnIndices[index] / getICellCount();
				columnIndices[index] = iColumn + (getJCellCount() - 1 - jColumn)*getICellCount();
			}
		}
	}
}

void AbstractIjkGridRepresentation::getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry->SplitCoordinateLines == nullptr)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength)->Values->PathInHdfFile, columnIndexCountPerSplitCoordinateLine);
	}
	else
		throw std::logic_error("Not yet implemented");
}

unsigned long AbstractIjkGridRepresentation::getSplitCoordinateLineCount() const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry->SplitCoordinateLines)
	{
		return grid->Geometry->SplitCoordinateLines->Count;
	}
	else
		return 0;
}

void AbstractIjkGridRepresentation::getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry)
	{
		unsigned int pillarCount = (getJCellCount() + 1) * (getICellCount() + 1);
		if (grid->Geometry->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
		{
			if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile) == H5T_NATIVE_CHAR)
			{
				char* tmp = new char[pillarCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; i++)
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile) == H5T_NATIVE_UCHAR)
			{
				unsigned char* tmp = new unsigned char[pillarCount];
				hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; i++)
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else if (grid->Geometry->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
		{
			if (static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->PillarGeometryIsDefined)->Value == true)
				for (unsigned int i = 0; i < pillarCount; i++)
					pillarGeometryIsDefined[i] = true;
			else
				for (unsigned int i = 0; i < pillarCount; i++)
					pillarGeometryIsDefined[i] = false;
		}
		else
			throw std::logic_error("Not yet implemented");
		}
	else
		throw invalid_argument("The grid has no geometry.");

	

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		bool * initialPillarGeometryIsDefined = new bool [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialPillarGeometryIsDefined[index] = pillarGeometryIsDefined[index];
		}

		if (reverseIAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[getICellCount() - i + j*iPillarCount];
					++pillarIndex;
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[i + (getJCellCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}

		delete [] initialPillarGeometryIsDefined;
	}
}

bool AbstractIjkGridRepresentation::hasEnabledCellInformation() const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	return grid->Geometry != nullptr && grid->Geometry->CellGeometryIsDefined != nullptr;
}

void AbstractIjkGridRepresentation::getEnabledCells(bool * enabledCells, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	if (hasEnabledCellInformation() == false)
		throw invalid_argument("The grid has no geometry or no information about enabled cells.");

	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	ULONG64 cellCount = getCellCount();
	if (grid->Geometry->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		hid_t dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile);
		if (H5Tequal(dt, H5T_NATIVE_CHAR) > 0)
		{
			char* tmp = new char[cellCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
			for (ULONG64 i = 0; i < cellCount; i++)
				if (tmp[i] == 0) enabledCells[i] = false; else enabledCells[i] = true;
			delete [] tmp;
		}
		else if (H5Tequal(dt, H5T_NATIVE_UCHAR) > 0)
		{
			unsigned char* tmp = new unsigned char[cellCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
			for (ULONG64 i = 0; i < cellCount; i++)
				if (tmp[i] == 0) enabledCells[i] = false; else enabledCells[i] = true;
			delete [] tmp;
		}
		else
			throw std::logic_error("Only CHAR and UCHAR are supported for now for storing cellGeometryIsDefined information.");
	}
	else if (grid->Geometry->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		if (static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->CellGeometryIsDefined)->Value == true)
			for (unsigned int i = 0; i < cellCount; i++)
				enabledCells[i] = true;
		else
			for (unsigned int i = 0; i < cellCount; i++)
				enabledCells[i] = false;
	}
	else
		throw std::logic_error("Not yet implemented");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		ULONG64 arrayCount = getCellCount();
		bool * initialCellGeometryIsDefined = new bool [arrayCount];
		for (ULONG64 index = 0; index < arrayCount; ++index)
		{
			initialCellGeometryIsDefined[index] = enabledCells[index];
		}

		if (reverseIAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCellCount(); ++j)
				{
					for (unsigned int i = 0; i < getICellCount(); ++i)
					{
						enabledCells[cellIndex] = initialCellGeometryIsDefined[getICellCount() - 1 - i + j*getICellCount() + k*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCellCount(); ++j)
				{
					for (unsigned int i = 0; i < getICellCount(); ++i)
					{
						enabledCells[cellIndex] = initialCellGeometryIsDefined[i + (getJCellCount() - 1 -j)*getICellCount() + k*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseKAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCellCount(); ++j)
				{
					for (unsigned int i = 0; i < getICellCount(); ++i)
					{
						enabledCells[cellIndex] = initialCellGeometryIsDefined[i + j*getICellCount() + (getKCellCount() - 1 -k)*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		delete [] initialCellGeometryIsDefined;
	}
}

unsigned int AbstractIjkGridRepresentation::getIPillarFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getPillarCount())
		throw invalid_argument("The pillar index is out of range.");

	return globalIndex % (getICellCount() + 1);
}

unsigned int AbstractIjkGridRepresentation::getJPillarFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getPillarCount())
		throw invalid_argument("The pillar index is out of range.");

	return globalIndex / (getICellCount() + 1);
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexPillarFromIjIndex(const unsigned int & iPillar, const unsigned int & jPillar) const
{
	if (iPillar > getICellCount())
		throw invalid_argument("The pillar I index is out of range.");
	if (jPillar > getJCellCount())
		throw invalid_argument("The pillar J index is out of range.");

	return iPillar + (getICellCount() + 1) * jPillar;
}

unsigned int AbstractIjkGridRepresentation::getIColumnFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getColumnCount())
		throw invalid_argument("The column index is out of range.");

	return globalIndex % getICellCount();
}

unsigned int AbstractIjkGridRepresentation::getJColumnFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getColumnCount())
		throw invalid_argument("The column index is out of range.");

	return globalIndex / getICellCount();
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexColumnFromIjIndex(const unsigned int & iColumn, const unsigned int & jColumn) const
{
	if (iColumn >= getICellCount())
		throw invalid_argument("The column I index is out of range.");
	if (jColumn >= getJCellCount())
		throw invalid_argument("The column J index is out of range.");

	return iColumn + getICellCount() * jColumn;
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexCellFromIjkIndex(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell) const
{
	if (iCell >= getICellCount())
		throw invalid_argument("The cell I index is out of range.");
	if (jCell >= getJCellCount())
		throw invalid_argument("The cell J index is out of range.");
	if (kCell >= getKCellCount())
		throw invalid_argument("The cell K index is out of range.");

	return iCell + getICellCount() * jCell + getColumnCount() * kCell;
}

void AbstractIjkGridRepresentation::loadSplitInformation()
{
	unloadSplitInformation();
	splitInformation = new std::vector< std::pair< unsigned int, std::vector<unsigned int> > >[(getICellCount()+1) * (getJCellCount()+1)];

	_resqml2__IjkGridRepresentation* ijkGrid = getSpecializedGsoapProxy();
	if (ijkGrid->Geometry && ijkGrid->Geometry->SplitCoordinateLines != nullptr)
	{
		// Read the split information
		unsigned int* splitPillars = new unsigned int [getSplitCoordinateLineCount()];
		getPillarsOfSplitCoordinateLines(splitPillars);
		unsigned int* columnIndexCumulativeCountPerSplitCoordinateLine = new unsigned int[getSplitCoordinateLineCount()];
		getColumnCountOfSplitCoordinateLines(columnIndexCumulativeCountPerSplitCoordinateLine);
		unsigned int* splitColumnIndices = new unsigned int [columnIndexCumulativeCountPerSplitCoordinateLine[getSplitCoordinateLineCount() - 1]];
		getColumnsOfSplitCoordinateLines(splitColumnIndices);

		// Rearrange the split information
		std::pair< unsigned int, std::vector<unsigned int> > splittedColumns;
		splittedColumns.first = 0;
		for (unsigned int splitColumnIndex = 0;
			splitColumnIndex < columnIndexCumulativeCountPerSplitCoordinateLine[0];
			++splitColumnIndex)
		{
			splittedColumns.second.push_back(splitColumnIndices[splitColumnIndex]);
		}
		splitInformation[splitPillars[0]].push_back(splittedColumns);
		for (unsigned int splitPillarIndex = 1; splitPillarIndex < getSplitCoordinateLineCount(); ++splitPillarIndex)
		{
			splittedColumns.first = splitPillarIndex;
			splittedColumns.second.clear();
			for (unsigned int splitColumnIndex = columnIndexCumulativeCountPerSplitCoordinateLine[splitPillarIndex-1];
				splitColumnIndex < columnIndexCumulativeCountPerSplitCoordinateLine[splitPillarIndex];
				++splitColumnIndex)
			{
				splittedColumns.second.push_back(splitColumnIndices[splitColumnIndex]);
			}
			splitInformation[splitPillars[splitPillarIndex]].push_back(splittedColumns);
		}
		
		delete [] splitPillars;
		delete [] columnIndexCumulativeCountPerSplitCoordinateLine;
		delete [] splitColumnIndices;
	}
}

void AbstractIjkGridRepresentation::unloadSplitInformation()
{
	if (splitInformation != nullptr)
	{
		delete [] splitInformation;
		splitInformation = nullptr;
	}
}

unsigned int AbstractIjkGridRepresentation::getFaceCount() const
{
	unsigned int faceCount = getICellCount() * getJCellCount() * (getKCellCount() + 1); // K faces which are assumed to be not splitted
	faceCount += getICellCount() * (getJCellCount() + 1) * getKCellCount(); // non splitted J faces
	faceCount += (getICellCount() + 1) * getJCellCount() * getKCellCount(); // non splitted I faces

	_resqml2__IjkGridRepresentation* ijkGrid = getSpecializedGsoapProxy();
	if (ijkGrid->Geometry->SplitCoordinateLines != nullptr)
	{
		// i split
		for (unsigned int j = 0; j < getJCellCount(); ++j)
			for (unsigned int i = 0; i < getICellCount() - 1; ++i)
			{
				if (isColumnEdgeSplitted(i, j, 1) == true)
					faceCount += getKCellCount();
			}

		// j split
		for (unsigned int j = 0; j < getJCellCount()-1; ++j)
			for (unsigned int i = 0; i < getICellCount(); ++i)
			{
				if (isColumnEdgeSplitted(i, j, 2) == true)
					faceCount += getKCellCount();
			}
	}

	return faceCount;
}

bool AbstractIjkGridRepresentation::isColumnEdgeSplitted(const unsigned int & iColumn, const unsigned int & jColumn, const unsigned int & edge) const
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
	if (iColumn > getICellCount())
		throw range_error("I column is out of range.");
	if (jColumn > getJCellCount())
		throw range_error("J column is out of range.");
	if (edge > 7)
		throw range_error("Edge is out of range.");

	// Pillar
	unsigned int iPillarIndex = iColumn;
	if (edge == 1 || edge == 2)
		++iPillarIndex;
	unsigned int jPillarIndex = jColumn;
	if (edge == 2 || edge == 3)
		++jPillarIndex;

	// Other column identification
	int iOtherColum = iColumn;
	int jOtherColum = jColumn;
					
	if (edge == 0) --jOtherColum;
	else if (edge == 1) ++iOtherColum;
	else if (edge == 2) ++jOtherColum;
	else if (edge == 3) --iOtherColum;

	if (iOtherColum < 0 || jOtherColum < 0 || iOtherColum >= getICellCount() || jOtherColum >= getJCellCount())
		return false;
	unsigned int otherColumnIndex = getGlobalIndexColumnFromIjIndex(iOtherColum, jOtherColum);

	// Check split on first pillar of the column edge
	bool result = false;
	unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iColumn, jColumn);
		for (unsigned int columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (unsigned int column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					result = true;
					for (unsigned int otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == otherColumnIndex)
							result = false;
					}
					if (result == true)
						return true;
					else
					{
						columnSet = splitInformation[pillarIndex].size();
						break;
					}
				}
				else if  (splitInformation[pillarIndex][columnSet].second[column] == otherColumnIndex)
				{
					result = true;
					for (unsigned int otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == columnIndex)
							result = false;
					}
					if (result == true)
						return true;
					else
					{
						columnSet = splitInformation[pillarIndex].size();
						break;
					}
				}
			}
	}

	// Check split on second pillar of the column edge
	iPillarIndex = iColumn;
	if (edge == 0 || edge == 1)
		++iPillarIndex;
	jPillarIndex = jColumn;
	if (edge == 1 || edge == 2)
		++jPillarIndex;

	pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iColumn, jColumn);
		for (unsigned int columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (unsigned int column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					for (unsigned int otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == otherColumnIndex)
							return false;
					}
					return true;
				}
				else if (splitInformation[pillarIndex][columnSet].second[column] == otherColumnIndex)
				{
					for (unsigned int otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == columnIndex)
							return false;
					}
					return true;
				}
			}
	}

	return result;
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointIndexFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner) const
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
	if (iCell > getICellCount())
		throw range_error("I Cell is out of range.");
	if (jCell > getJCellCount())
		throw range_error("J Cell is out of range.");
	if (kCell > getKCellCount())
		throw range_error("K Cell is out of range.");
	if (corner > 7)
		throw range_error("Corner is out of range.");

	unsigned int iPillarIndex = iCell;
	if (corner == 1 || corner == 2 || corner == 5 || corner == 6)
		++iPillarIndex;
	unsigned int jPillarIndex = jCell;
	if (corner == 2 || corner == 3 || corner == 6 || corner == 7)
		++jPillarIndex;
	unsigned int kPointIndex = kCell;
	if (corner > 3)
		++kPointIndex;

	unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iCell, jCell);
		for (unsigned int columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (unsigned int column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					return (getICellCount()+1) * (getJCellCount()+1) + splitInformation[pillarIndex][columnSet].first + kPointIndex * ((getICellCount()+1) * (getJCellCount()+1) + getSplitCoordinateLineCount()); // splitted point
				}
			}
	}

	return iPillarIndex + jPillarIndex * (getICellCount()+1) + kPointIndex * ((getICellCount()+1) * (getJCellCount()+1) + getSplitCoordinateLineCount()); // non splitted point
}

UnstructuredGridRepresentation* AbstractIjkGridRepresentation::cloneToUnstructuredGridRepresentation(const std::string & guid, const std::string & title)
{
	if (epcDocument->getResqmlAbstractObjectByUuid(guid) != nullptr)
		throw invalid_argument("Cannot create the unstructured grid because it already exists a resqml object with the same uuid in the EPC document.");

	_resqml2__IjkGridRepresentation* ijkGrid = getSpecializedGsoapProxy();

	UnstructuredGridRepresentation* result = nullptr;
	if (interpretation != nullptr) result = new UnstructuredGridRepresentation(interpretation, localCrs, guid, title, getCellCount());
	else result = new UnstructuredGridRepresentation(getEpcDocument(), localCrs, guid, title, getCellCount());
	result->addAlias("EpcDocument", ijkGrid->uuid);
	
	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy->soap, 1);
	static_cast<_resqml2__UnstructuredGridRepresentation*>(result->getGsoapProxy())->Geometry = geom;
	static_cast<_resqml2__UnstructuredGridRepresentation*>(result->getGsoapProxy())->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->NodeCount = getXyzPointCountOfPatch(0);
	geom->CellShape = resqml2__CellShape__hexahedral;

	
	vector<ULONG64> cellIndexPair;
	vector<unsigned int> localFacePerCellIndexPair;
	vector<long> connectionOrientationPropValues;
	GridConnectionSetRepresentation* gcsr = nullptr;
	if (gridConnectionSetRepresentationSet.size() > 1)
	{
		throw new invalid_argument("Cannot clone IJK grid which has got more than one GridConnectionSetRepresentationSet.");
	}
	else if (gridConnectionSetRepresentationSet.size() == 1)
	{
		gcsr = gridConnectionSetRepresentationSet[0];
		cellIndexPair.resize(gcsr->getCellIndexPairCount() * 2);
		localFacePerCellIndexPair.resize(gcsr->getCellIndexPairCount() * 2, (numeric_limits<int>::max)());
		gcsr->getCellIndexPairs(&cellIndexPair[0]);
		if (gcsr->hasLocalFacePerCell())
			gcsr->getLocalFacePerCellIndexPairs(&localFacePerCellIndexPair[0]);

		connectionOrientationPropValues.resize(gcsr->getCellIndexPairCount(), (numeric_limits<long>::max)());
		for (size_t i = 0; i < connectionOrientationPropValues.size(); i++)
		{
			/*
			if ((localFacePerCellIndexPair[2*i] == 3 && localFacePerCellIndexPair[2*i + 1] == 5) ||
				(localFacePerCellIndexPair[2*i] == 5 && localFacePerCellIndexPair[2*i + 1] == 3))
				connectionOrientationPropValues[i] = 0;
			else if ((localFacePerCellIndexPair[2*i] == 2 && localFacePerCellIndexPair[2*i + 1] == 4) ||
				(localFacePerCellIndexPair[2*i] == 4 && localFacePerCellIndexPair[2*i + 1] == 2))
				connectionOrientationPropValues[i] = 1;
			else if ((localFacePerCellIndexPair[2*i] == 0 && localFacePerCellIndexPair[2*i + 1] == 1) ||
				(localFacePerCellIndexPair[2*i] == 1 && localFacePerCellIndexPair[2*i + 1] == 0))
				connectionOrientationPropValues[i] = 2;
			*/
			connectionOrientationPropValues[i] = 4;
		}
	}

	loadSplitInformation();
	geom->FaceCount = getFaceCount();
	ULONG64* faceIndicesPerCell = new ULONG64[getCellCount() * 6];
	char* cellFaceIsRightHanded = new char[getCellCount() * 6];
	ULONG64* nodeIndicesPerFace = new ULONG64[geom->FaceCount * 4];
	unsigned int nodeIndicesPerFaceIndex = 0;
	ULONG64 cellIndex = 0;
	unsigned int columnIndex = 0;
	
	pair<unsigned int, unsigned int> previousIFace;
	unsigned int* previousJFaces = new unsigned int[getICellCount()];
	unsigned int* previousKFaces = new unsigned int[getICellCount() * getJCellCount()];
	for (unsigned int kCell = 0; kCell < getKCellCount(); ++kCell)
	{
		columnIndex = 0;
		for (unsigned int jCell = 0; jCell < getJCellCount(); ++jCell)
		{
			for (unsigned int iCell = 0; iCell < getICellCount(); ++iCell)
			{
				//****************************
				//****** Nodes and faces *****
				//****************************

				// 0 Upper K face  : Cannot be splitted by hypothesis. Split nodes are not supported yet
				faceIndicesPerCell[cellIndex*6] = nodeIndicesPerFaceIndex/4;
				cellFaceIsRightHanded[cellIndex*6] = 0;
				unsigned int previousKFace = previousKFaces[columnIndex];
				previousKFaces[columnIndex] = nodeIndicesPerFaceIndex/4;

				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 4);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 5);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 6);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 7);
				++nodeIndicesPerFaceIndex;

				// 1 Lower K Face : Cannot be splitted by hypothesis. Split nodes are not supported yet
				cellFaceIsRightHanded[cellIndex*6 + 1] = 1;
				if (kCell == 0)
				{
					faceIndicesPerCell[cellIndex*6 + 1] = nodeIndicesPerFaceIndex/4;

					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 0);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 1);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 2);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 3);
					++nodeIndicesPerFaceIndex;
				}
				else // The face has already been created as the bottom of the previous loop.
				{
					faceIndicesPerCell[cellIndex*6 + 1] = previousKFace;
				}

				// 2 Lower J face
				cellFaceIsRightHanded[cellIndex*6 + 2] = 1;
				if (jCell == 0 || isColumnEdgeSplitted(iCell, jCell, 0) == true)
				{
					faceIndicesPerCell[cellIndex*6 + 2] = nodeIndicesPerFaceIndex/4;

					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 0);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 4);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 5);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 1);
					++nodeIndicesPerFaceIndex;
				}
				else // The face has already been created
				{
					faceIndicesPerCell[cellIndex*6 + 2] = previousJFaces[iCell];
				}
				
				// 3 Upper I Face
				faceIndicesPerCell[cellIndex*6 + 3] = nodeIndicesPerFaceIndex/4;
				cellFaceIsRightHanded[cellIndex*6 + 3] = 0;
				previousIFace.first = previousIFace.second;
				previousIFace.second = nodeIndicesPerFaceIndex/4;

				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 1);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 2);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 6);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 5);
				++nodeIndicesPerFaceIndex;

				// 4 Upper J Face
				faceIndicesPerCell[cellIndex*6 + 4] = nodeIndicesPerFaceIndex/4;
				cellFaceIsRightHanded[cellIndex*6 + 4] = 0;
				previousJFaces[iCell] = nodeIndicesPerFaceIndex/4;

				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 3);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 7);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 6);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 2);
				++nodeIndicesPerFaceIndex;

				// 5 Lower I face
				cellFaceIsRightHanded[cellIndex*6 + 5] = 1;
				if (iCell == 0 || isColumnEdgeSplitted(iCell, jCell, 3) == true)
				{
					faceIndicesPerCell[cellIndex*6 + 5] = nodeIndicesPerFaceIndex/4;

					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 0);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 3);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 7);
					++nodeIndicesPerFaceIndex;
					nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 4);
					++nodeIndicesPerFaceIndex;
				}
				else // The face has already been created
				{
					faceIndicesPerCell[cellIndex*6 + 5] = previousIFace.first;
				}

				//****************************
				//****** Grid Connection *****
				//****************************

				// I connection
				if (iCell < getICellCount()-1 &&
					isColumnEdgeSplitted(iCell, jCell, 1) == false)
				{
					cellIndexPair.push_back(cellIndex);
					cellIndexPair.push_back(cellIndex+1);
					localFacePerCellIndexPair.push_back(3);
					localFacePerCellIndexPair.push_back(5);
					connectionOrientationPropValues.push_back(0);
				}

				// J connection
				if (jCell < getJCellCount()-1 &&
					isColumnEdgeSplitted(iCell, jCell, 2) == false)
				{
					cellIndexPair.push_back(cellIndex);
					cellIndexPair.push_back(cellIndex+getICellCount());
					localFacePerCellIndexPair.push_back(4);
					localFacePerCellIndexPair.push_back(2);
					connectionOrientationPropValues.push_back(1);
				}

				// K connection : Cannot be splitted by hypothesis.
				if (kCell < getKCellCount()-1)
				{
					cellIndexPair.push_back(cellIndex);
					cellIndexPair.push_back(cellIndex+getColumnCount());
					localFacePerCellIndexPair.push_back(0);
					localFacePerCellIndexPair.push_back(1);
					connectionOrientationPropValues.push_back(2);
				}

				++columnIndex;
				++cellIndex;
			}
		}
	}
	delete [] previousJFaces;
	delete [] previousKFaces;
	unloadSplitInformation();
	
	// Right handed
	resqml2__BooleanHdf5Array* hdfBoolArray = soap_new_resqml2__BooleanHdf5Array(gsoapProxy->soap, 1);
	hdfBoolArray->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	hdfBoolArray->Values->HdfProxy = hdfProxy->newResqmlReference();
	hdfBoolArray->Values->PathInHdfFile = "/RESQML/" + result->getUuid() + "/CellFaceIsRightHanded";
	geom->CellFaceIsRightHanded = hdfBoolArray;
	// HDF
	hsize_t * dim = new hsize_t[4];
	dim[0] = getKCellCount();
	dim[1] = getJCellCount();
	dim[2] = getICellCount();
	dim[3] = 6; // 6 faces per cell
	hdfProxy->writeArrayNd(result->getUuid(),
		"CellFaceIsRightHanded", H5T_NATIVE_CHAR,
		cellFaceIsRightHanded,
		dim, 4);
	delete [] cellFaceIsRightHanded;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	// Cumulative
	resqml2__IntegerLatticeArray* cumulativeLength = soap_new_resqml2__IntegerLatticeArray(gsoapProxy->soap, 1);
	geom->FacesPerCell->CumulativeLength = cumulativeLength;
	cumulativeLength->StartValue = 6;
	cumulativeLength->Offset.push_back(soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1));
	cumulativeLength->Offset[0]->Count = getCellCount()-1;
	cumulativeLength->Offset[0]->Value = 6;
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = geom->FaceCount;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = hdfProxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + result->getUuid() + "/FacesPerCell";
	// HDF
	hdfProxy->writeArrayNd(result->getUuid(),
		"FacesPerCell", H5T_NATIVE_ULLONG,
		faceIndicesPerCell,
		dim, 4);
	delete [] dim;
	delete [] faceIndicesPerCell;

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	// Cumulative
	cumulativeLength = soap_new_resqml2__IntegerLatticeArray(gsoapProxy->soap, 1);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->StartValue = 4;
	cumulativeLength->Offset.push_back(soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1));
	cumulativeLength->Offset[0]->Count = geom->FaceCount-1;
	cumulativeLength->Offset[0]->Value = 4;
	// Elements
	elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = geom->FaceCount * 4;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = hdfProxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + result->getUuid() + "/NodesPerFace";
	// HDF
	dim = new hsize_t[2];
	dim[0] = geom->FaceCount;
	dim[1] = 4; // 4 nodes par face
	hdfProxy->writeArrayNd(result->getUuid(),
		"NodesPerFace", H5T_NATIVE_ULLONG,
		nodeIndicesPerFace,
		dim, 2);
	delete [] dim;
	delete [] nodeIndicesPerFace;

	/**********************************
	*********** POINTS ****************
	**********************************/

	// XYZ points are referenced in case of explicit geometry. They are transformed (and then copied) in case of parametric geometry.
	if (ijkGrid->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
	{
		geom->Points = ijkGrid->Geometry->Points;
	}
	else if (ijkGrid->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray)
	{
		double* points = new double[getXyzPointCountOfPatch(0) * 3];
		getXyzPointsOfPatch(0, points);

		// XML coordinate lines
		resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
		geom->Points = xmlPoints;
		xmlPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		xmlPoints->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
		xmlPoints->Coordinates->PathInHdfFile = "/RESQML/" + result->getUuid() + "/Points";

		unsigned int splitCoordinateLineCount = getSplitCoordinateLineCount();
		if (splitCoordinateLineCount == 0)
		{
			// HDF
			hsize_t * numValues = new hsize_t[4];
			numValues[0] = getKCellCount() + 1;
			numValues[1] = getJCellCount() + 1;
			numValues[2] = getICellCount() + 1;
			numValues[3] = 3; // 3 for X, Y and Z

			hdfProxy->writeArrayNdOfDoubleValues(result->getUuid(), "Points", points, numValues, 4);
			delete [] numValues;
		}
		else
		{
			// HDF
			hsize_t * numValues = new hsize_t[3];
			numValues[0] = getKCellCount() + 1;
			numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;
			numValues[2] = 3; // 3 for X, Y and Z

			hdfProxy->writeArrayNdOfDoubleValues(result->getUuid(), "Points", points, numValues, 3);
			delete [] numValues;
		}

		delete [] points;
	}

	/**********************************
	********** ACTNUM *****************
	**********************************/

	if (ijkGrid->Geometry->CellGeometryIsDefined != nullptr)
	{
		// Property kind
		AbstractObject* actnumUuidObj = epcDocument->getResqmlAbstractObjectByUuid("556b918e-fb78-43b9-b224-7d3ae7488f47");
		PropertyKind* kind = nullptr;
		if (actnumUuidObj != nullptr && actnumUuidObj->getXmlTag() == PropertyKind::XML_TAG)
			kind = static_cast<PropertyKind*>(actnumUuidObj);
		else if (actnumUuidObj == nullptr)
			kind = new PropertyKind(getEpcDocument(), "556b918e-fb78-43b9-b224-7d3ae7488f47", "ACTNUM", "F2I", resqml2__ResqmlUom__Euc, resqml2__ResqmlPropertyKind__discrete);
		else
			throw invalid_argument("Cannot create the actnum property kind because it already exists a resqml object with the same uuid in the EPC document.");

		// Property
		DiscreteProperty* actnum = new DiscreteProperty(result, "", "ACTNUM", 1, resqml2__IndexableElements__cells, kind);

		// Values
		resqml2__PatchOfValues* patch = soap_new_resqml2__PatchOfValues(gsoapProxy->soap, 1);
		patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy->soap, sizeof(ULONG64)));
		*(patch->RepresentationPatchIndex) = 0;
		patch->Values = ijkGrid->Geometry->CellGeometryIsDefined;
		static_cast<_resqml2__DiscreteProperty*>(actnum->getGsoapProxy())->PatchOfValues.push_back(patch);

		actnum->setHdfProxy(hdfProxy);
	}

	/**********************************
	******** CELL CONNECTIONS *********
	**********************************/
	
	if (gcsr != nullptr && static_cast<_resqml2__GridConnectionSetRepresentation*>(gcsr->getGsoapProxy())->GridIndexPairs != nullptr)
	{
		throw new invalid_argument("Cannot clone IJK grid which has got a GridConnectionSetRepresentationSet dependent on several grids.");
	}
	GridConnectionSetRepresentation* gcsrCopy = new GridConnectionSetRepresentation(interpretation, "", "Grid Connection Set", result);
	gcsrCopy->setCellIndexPairs(cellIndexPair.size()/2, &cellIndexPair[0], (numeric_limits<ULONG64>::max)(), hdfProxy);
	gcsrCopy->setLocalFacePerCellIndexPairs(cellIndexPair.size()/2, &localFacePerCellIndexPair[0], (numeric_limits<unsigned int>::max)(), hdfProxy);

	// Property kind
	AbstractObject* connectionOrientationPropKindUuidObj = epcDocument->getResqmlAbstractObjectByUuid("238fa7fe-1178-406d-bc0e-3bf212476012");
	PropertyKind* kind = nullptr;
	if (connectionOrientationPropKindUuidObj != nullptr && connectionOrientationPropKindUuidObj->getXmlTag() == PropertyKind::XML_TAG)
		kind = static_cast<PropertyKind*>(connectionOrientationPropKindUuidObj);
	else if (connectionOrientationPropKindUuidObj == nullptr)
		kind = new PropertyKind(getEpcDocument(), "238fa7fe-1178-406d-bc0e-3bf212476012", "CONNECTION_ORIENTATION", "F2I", resqml2__ResqmlUom__Euc, resqml2__ResqmlPropertyKind__categorical);
	else
		throw invalid_argument("Cannot create the conneciton orientation property kind because it already exists a resqml object with the same uuid in the EPC document.");

	// Property
	StringTableLookup* stl = new StringTableLookup(getEpcDocument(), "a8b9a605-7836-4dac-9e17-756c0c22e980", "Connection Orientation string table lookup");
	stl->addValue("I", 0);
	stl->addValue("J", 1);
	stl->addValue("K", 2);
	stl->addValue("MF", 3);
	stl->addValue("FAULT", 4);
	CategoricalProperty* connectionOrientationProp = new CategoricalProperty(result, "", "CONNECTION_ORIENTATION", 1, resqml2__IndexableElements__edges, stl, kind);

	// Values
	connectionOrientationProp->pushBackLongHdf5Array1dOfValues(&connectionOrientationPropValues[0], connectionOrientationPropValues.size(), hdfProxy, (numeric_limits<long>::max)());

	//**********************************
	//*********** PROPERTIES ***********
	//**********************************

	for (unsigned int i = 0; i < propertySet.size(); ++i)
	{
		AbstractProperty* prop = propertySet[i];

		AbstractValuesProperty* propCopy = nullptr;
		if (prop->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalProperty)
		{
			if (prop->isAssociatedToOneStandardEnergisticsPropertyKind() == true)
			{
				propCopy = new CategoricalProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), static_cast<CategoricalProperty*>(prop)->getStringLookup(), prop->getEnergisticsPropertyKind());
			}
			else
			{
				propCopy = new CategoricalProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), static_cast<CategoricalProperty*>(prop)->getStringLookup(), prop->getLocalPropertyKind());
			}
		}
		else if (prop->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentProperty)
		{
			if (prop->isAssociatedToOneStandardEnergisticsPropertyKind() == true)
			{
				propCopy = new CommentProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), prop->getEnergisticsPropertyKind());
			}
			else
			{
				propCopy = new CommentProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), prop->getLocalPropertyKind());
			}
			static_cast<_resqml2__CommentProperty*>(propCopy->getGsoapProxy())->Language = static_cast<_resqml2__CommentProperty*>(prop->getGsoapProxy())->Language;
		}
		else if (prop->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousProperty)
		{
			if (prop->isAssociatedToOneStandardEnergisticsPropertyKind() == true)
			{
				propCopy = new ContinuousProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), static_cast<ContinuousProperty*>(prop)->getUom(), prop->getEnergisticsPropertyKind());
			}
			else
			{
				propCopy = new ContinuousProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), static_cast<ContinuousProperty*>(prop)->getUom(), prop->getLocalPropertyKind());
			}
			static_cast<_resqml2__ContinuousProperty*>(propCopy->getGsoapProxy())->MinimumValue = static_cast<_resqml2__ContinuousProperty*>(prop->getGsoapProxy())->MinimumValue;
			static_cast<_resqml2__ContinuousProperty*>(propCopy->getGsoapProxy())->MaximumValue = static_cast<_resqml2__ContinuousProperty*>(prop->getGsoapProxy())->MaximumValue;
		}
		else if (prop->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscreteProperty)
		{
			if (prop->isAssociatedToOneStandardEnergisticsPropertyKind() == true)
			{
				propCopy = new DiscreteProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), prop->getEnergisticsPropertyKind());
			}
			else
			{
				propCopy = new DiscreteProperty(result, "", prop->getTitle(), prop->getElementCountPerValue(),
						prop->getAttachmentKind(), prop->getLocalPropertyKind());
			}
			static_cast<_resqml2__DiscreteProperty*>(propCopy->getGsoapProxy())->MinimumValue = static_cast<_resqml2__DiscreteProperty*>(prop->getGsoapProxy())->MinimumValue;
			static_cast<_resqml2__DiscreteProperty*>(propCopy->getGsoapProxy())->MaximumValue = static_cast<_resqml2__DiscreteProperty*>(prop->getGsoapProxy())->MaximumValue;
		}

		if (propCopy != nullptr)
		{
			propCopy->setHdfProxy(hdfProxy);
			if (prop->getTimeSeries() != nullptr)
			{
				propCopy->setTimeIndex(prop->getTimeIndex(), prop->getTimeSeries());
			}
			resqml2__AbstractValuesProperty* propProxy= static_cast<resqml2__AbstractValuesProperty*>(prop->getGsoapProxy());
			resqml2__AbstractValuesProperty* propCopyProxy= static_cast<resqml2__AbstractValuesProperty*>(propCopy->getGsoapProxy());
			propCopyProxy->PatchOfValues = propProxy->PatchOfValues;
			propCopyProxy->Facet = propProxy->Facet;
		}
	}

	return result;
}

void AbstractIjkGridRepresentation::setEnabledCells(unsigned char* enabledCells)
{
	resqml2__IjkGridGeometry* geom = getSpecializedGsoapProxy()->Geometry;
	if (geom == nullptr)
	{
		throw invalid_argument("The geometry of the ijk grid has not been defined yet.");
	}

	resqml2__BooleanHdf5Array* boolArray = soap_new_resqml2__BooleanHdf5Array(gsoapProxy->soap, 1);
	geom->CellGeometryIsDefined = boolArray;

	boolArray->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	boolArray->Values->HdfProxy = hdfProxy->newResqmlReference();
	boolArray->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/CellGeometryIsDefined";

	// HDF
	hsize_t * cellGeometryIsDefinedCount = new hsize_t[3];
	cellGeometryIsDefinedCount[0] = getKCellCount();
	cellGeometryIsDefinedCount[1] = getJCellCount();
	cellGeometryIsDefinedCount[2] = getICellCount();
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "CellGeometryIsDefined", H5T_NATIVE_UCHAR, enabledCells, cellGeometryIsDefinedCount, 3);
	delete [] cellGeometryIsDefinedCount;
}
