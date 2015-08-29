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

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

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
	if (crs == nullptr)
		throw invalid_argument("The local CRS of the IJK Grid cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREIjkGridRepresentation(epcDoc->getGsoapContext(), 1);
	_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);

	ijkGrid->Ni = iCount;
	ijkGrid->Nj = jCount;
	ijkGrid->Nk = kCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// epc document
	epcDoc->addGsoapProxy(this);

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);
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

gsoap_resqml2_0_1::resqml2__PointGeometry* AbstractIjkGridRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry;
	else
		return NULL;
}

unsigned int AbstractIjkGridRepresentation::getICellCount() const
{
	return (int)static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Ni;
}

void AbstractIjkGridRepresentation::setICellCount(const unsigned int & iCount)
{
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Ni = iCount;
}

unsigned int AbstractIjkGridRepresentation::getJCellCount() const
{
	return (int)static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Nj;
}

void AbstractIjkGridRepresentation::setJCellCount(const unsigned int & jCount)
{
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Nj = jCount;
}

bool AbstractIjkGridRepresentation::isRightHanded() const
{
	if (static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry)
		return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry->GridIsRighthanded;
	else
		throw invalid_argument("The grid has no geometry.");
}

void AbstractIjkGridRepresentation::getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines == NULL)
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
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines == NULL)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile, columnIndices);
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int datasetValueCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile);
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
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines == NULL)
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
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines)
	{
		return grid->Geometry->SplitCoordinateLines->Count;
	}
	else
		return 0;
}

void AbstractIjkGridRepresentation::getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
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


void AbstractIjkGridRepresentation::getCellGeometryIsDefined(bool * cellGeometryIsDefined, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry)
	{
		unsigned int cellCount = getCellCount();
		if (grid->Geometry->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
		{
			if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile) == H5T_NATIVE_CHAR)
			{
				char* tmp = new char[cellCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < cellCount; i++)
					if (tmp[i] == 0) cellGeometryIsDefined[i] = false; else cellGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile) == H5T_NATIVE_UCHAR)
			{
				unsigned char* tmp = new unsigned char[cellCount];
				hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < cellCount; i++)
					if (tmp[i] == 0) cellGeometryIsDefined[i] = false; else cellGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else if (grid->Geometry->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
		{
			if (static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->CellGeometryIsDefined)->Value == true)
				for (unsigned int i = 0; i < cellCount; i++)
					cellGeometryIsDefined[i] = true;
			else
				for (unsigned int i = 0; i < cellCount; i++)
					cellGeometryIsDefined[i] = false;
		}
		else
			throw std::logic_error("Not yet implemented");
		}
	else
		throw invalid_argument("The grid has no geometry.");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int arrayCount = getCellCount();
		bool * initialCellGeometryIsDefined = new bool [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialCellGeometryIsDefined[index] = cellGeometryIsDefined[index];
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
						cellGeometryIsDefined[cellIndex] = initialCellGeometryIsDefined[getICellCount() - 1 - i + j*getICellCount() + k*getICellCount()*getJCellCount()];
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
						cellGeometryIsDefined[cellIndex] = initialCellGeometryIsDefined[i + (getJCellCount() - 1 -j)*getICellCount() + k*getICellCount()*getJCellCount()];
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
						cellGeometryIsDefined[cellIndex] = initialCellGeometryIsDefined[i + j*getICellCount() + (getKCellCount() - 1 -k)*getICellCount()*getJCellCount()];
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

void AbstractIjkGridRepresentation::loadSplitInformation()
{
	unloadSplitInformation();
	splitInformation = new std::vector< std::pair< unsigned int, std::vector<unsigned int> > >[(getICellCount()+1) * (getJCellCount()+1)];

	_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (ijkGrid->Geometry->SplitCoordinateLines != nullptr)
	{
		// Read the split information
		unsigned int* splitPillars = new unsigned int [getSplitCoordinateLineCount()];
		getPillarsOfSplitCoordinateLines(splitPillars);
		unsigned int* columnIndexCumulativeCountPerSplitCoordinateLine = new unsigned int[getSplitCoordinateLineCount()];
		getColumnCountOfSplitCoordinateLines(columnIndexCumulativeCountPerSplitCoordinateLine);
		unsigned int* splitColumnIndices = new unsigned int [columnIndexCumulativeCountPerSplitCoordinateLine[getSplitCoordinateLineCount() - 1]];
		getColumnsOfSplitCoordinateLines(splitColumnIndices);

		// Compute the split faces
		std::pair< unsigned int, std::vector<unsigned int>> splittedColumns;
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

	_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
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

unsigned int AbstractIjkGridRepresentation::getXyzPointIndexFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner) const
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
	_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);

	UnstructuredGridRepresentation* result = nullptr;
	if (interpretation != nullptr) result = new UnstructuredGridRepresentation(interpretation, localCrs, guid, title, getCellCount());
	else result = new UnstructuredGridRepresentation(getEpcDocument(), localCrs, guid, title, getCellCount());
	
	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy->soap, 1);
	static_cast<_resqml2__UnstructuredGridRepresentation*>(result->getGsoapProxy())->Geometry = geom;
	static_cast<_resqml2__UnstructuredGridRepresentation*>(result->getGsoapProxy())->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->NodeCount = getXyzPointCountOfPatch(0);
	geom->CellShape = gsoap_resqml2_0_1::resqml2__CellShape::resqml2__CellShape__hexahedral;

	loadSplitInformation();
	geom->FaceCount = getFaceCount();
	unsigned int* faceIndicesPerCell = new unsigned int[getCellCount() * 6];
	char* cellFaceIsRightHanded = new char[getCellCount() * 6];
	unsigned int* nodeIndicesPerFace = new unsigned int[geom->FaceCount * 4];
	unsigned int nodeIndicesPerFaceIndex = 0;
	unsigned int cellIndex = 0;
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
				// 0 Top face : Cannot be splitted by hypothesis. Split nodes are not supported yet
				cellFaceIsRightHanded[cellIndex*6] = 1;
				if (kCell == 0)
				{
					faceIndicesPerCell[cellIndex*6] = nodeIndicesPerFaceIndex/4;

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
					faceIndicesPerCell[cellIndex*6] = previousKFaces[columnIndex];
				}

				// 1 Bottom face  : Cannot be splitted by hypothesis. Split nodes are not supported yet
				faceIndicesPerCell[cellIndex*6 + 1] = nodeIndicesPerFaceIndex/4;
				cellFaceIsRightHanded[cellIndex*6 + 1] = 0;
				previousKFaces[columnIndex] = nodeIndicesPerFaceIndex/4;

				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 4);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 5);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 6);
				++nodeIndicesPerFaceIndex;
				nodeIndicesPerFace[nodeIndicesPerFaceIndex] = getXyzPointIndexFromCellCorner(iCell, jCell, kCell, 7);
				++nodeIndicesPerFaceIndex;

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
		"FacesPerCell", H5T_NATIVE_UINT,
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
		"NodesPerFace", H5T_NATIVE_UINT,
		nodeIndicesPerFace,
		dim, 2);
	delete [] dim;
	delete [] nodeIndicesPerFace;

	// XML points
	geom->Points = ijkGrid->Geometry->Points;

	return result;
}
