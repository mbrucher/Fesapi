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
#include "resqml2_0_1/HdfProxy.h"

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
	AbstractColumnLayerGridRepresentation(nullptr, crs)
{
	init(epcDoc, crs, guid, title, iCount, jCount, kCount);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(interp, crs)
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
			if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_CHAR)
			{
				char* tmp = new char[pillarCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; i++)
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_UCHAR)
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
			if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_CHAR)
			{
				char* tmp = new char[cellCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < cellCount; i++)
					if (tmp[i] == 0) cellGeometryIsDefined[i] = false; else cellGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_UCHAR)
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
