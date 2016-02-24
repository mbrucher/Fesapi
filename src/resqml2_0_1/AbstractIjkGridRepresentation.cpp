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
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

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

void AbstractIjkGridRepresentation::init(soap* soapContext, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREIjkGridRepresentation(soapContext, 1);
	_resqml2__IjkGridRepresentation* ijkGrid = getSpecializedGsoapProxy();

	ijkGrid->Ni = iCount;
	ijkGrid->Nj = jCount;
	ijkGrid->Nk = kCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	if (crs != nullptr)
	{
		localCrs = crs;
		localCrs->addRepresentation(this);
	}
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(soap* soapContext, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(nullptr, crs), splitInformation(nullptr)
{
	init(soapContext, crs, guid, title, iCount, jCount, kCount);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(interp, crs), splitInformation(nullptr)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the IJK grid cannot be null.");

	init(interp->getGsoapContext(), crs, guid, title, iCount, jCount, kCount);

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

ULONG64 AbstractIjkGridRepresentation::getSplitNodeCount() const
{
	_resqml2__IjkGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry->SplitNodes)
	{
		return grid->Geometry->SplitNodes->Count;
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

gsoap_resqml2_0_1::resqml2__KDirection AbstractIjkGridRepresentation::getKDirection() const
{
	resqml2__IjkGridGeometry* geom = getSpecializedGsoapProxy()->Geometry;
	if (geom == nullptr)
	{
		throw invalid_argument("The geometry of the ijk grid has not been defined yet.");
	}

	return geom->KDirection;
}
