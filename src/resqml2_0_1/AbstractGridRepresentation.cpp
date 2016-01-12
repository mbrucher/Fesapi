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
#include "resqml2_0_1/AbstractGridRepresentation.h"

#include <stdexcept>
#include <limits>

#include "hdf5.h"

#include "resqml2_0_1/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace std;
using namespace epc;

vector<Relationship> AbstractGridRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();
	
	for (unsigned int i = 0; i < gridConnectionSetRepresentationSet.size(); ++i)
	{
		if (gridConnectionSetRepresentationSet[i] != nullptr)
		{
			Relationship relRep(gridConnectionSetRepresentationSet[i]->getPartNameInEpcDocument(), "", gridConnectionSetRepresentationSet[i]->getUuid());
			relRep.setSourceObjectType();
			result.push_back(relRep);
		}
		else
			throw domain_error("The grid Connections Representation associated to the grid cannot be nullptr.");
	}

	if (getParentGrid() != nullptr)
	{
		Relationship relParent(getParentGrid()->getPartNameInEpcDocument(), "", getParentGrid()->getUuid());
		relParent.setDestinationObjectType();
		result.push_back(relParent);
	}

	unsigned int cildGridCount = getChildGridCount();
	for (unsigned int i = 0; i < cildGridCount; ++i)
	{
		AbstractGridRepresentation* childGrid = getChildGrid(i);
		if (childGrid != nullptr)
		{
			Relationship relChild(childGrid->getPartNameInEpcDocument(), "", childGrid->getUuid());
			relChild.setSourceObjectType();
			result.push_back(relChild);
		}
		else
			throw domain_error("The child grid cannot be nullptr.");
	}

	return result;
}

GridConnectionSetRepresentation* AbstractGridRepresentation::getGridConnectionSetRepresentation(const unsigned int & index) const
{
	if (gridConnectionSetRepresentationSet.size() > index)
		return gridConnectionSetRepresentationSet[index];
	else
		throw std::out_of_range("No GridConnectionSetRepresentation at this index.");
}

AbstractGridRepresentation* AbstractGridRepresentation::getParentGrid() const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			resqml2__IjkParentWindow* pw = static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow);
			return static_cast<AbstractGridRepresentation*>(getEpcDocument()->getResqmlAbstractObjectByUuid(pw->ParentGrid->UUID));
		}
		else if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			resqml2__ColumnLayerParentWindow* pw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
			return static_cast<AbstractGridRepresentation*>(getEpcDocument()->getResqmlAbstractObjectByUuid(pw->ParentGrid->UUID));
		}
		else if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__CellParentWindow)
		{
			resqml2__CellParentWindow* pw = static_cast<resqml2__CellParentWindow*>(rep->ParentWindow);
			return static_cast<AbstractGridRepresentation*>(getEpcDocument()->getResqmlAbstractObjectByUuid(pw->ParentGrid->UUID));
		}
		else
			throw logic_error("Unexpected parent window type.");
	}
	else
		return nullptr;
}

resqml2__Regrid* AbstractGridRepresentation::createRegrid(const unsigned int & indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount, double * childCellWeights,
														  const std::string & dimension)
{
	resqml2__Regrid* regrid  = soap_new_resqml2__Regrid(gsoapProxy->soap, 1);
	regrid->InitialIndexOnParentGrid = indexRegridStart;
	regrid->Intervals = soap_new_resqml2__Intervals(gsoapProxy->soap, 1);
	regrid->Intervals->IntervalCount = intervalCount;

	if (intervalCount > 1 && hdfProxy != nullptr)
	{
		resqml2__IntegerHdf5Array* hdf5ChildCountPerInterval = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
		regrid->Intervals->ChildCountPerInterval = hdf5ChildCountPerInterval;
		hdf5ChildCountPerInterval->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ChildCountPerInterval->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		hdf5ChildCountPerInterval->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ChildCountPerInterval->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_" + dimension + "Regrid_ChildCountPerInterval";

		resqml2__IntegerHdf5Array* hdf5ParentCountPerInterval = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
		regrid->Intervals->ParentCountPerInterval = hdf5ParentCountPerInterval;
		hdf5ParentCountPerInterval->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ParentCountPerInterval->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		hdf5ParentCountPerInterval->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ParentCountPerInterval->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_" + dimension + "Regrid_ParentCountPerInterval";
		
		// HDF
		hsize_t numValues = intervalCount;
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "ParentWindow_" + dimension + "Regrid_ChildCountPerInterval", H5T_NATIVE_UINT, childCellCountPerInterval, &numValues, 1);
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "ParentWindow_" + dimension + "Regrid_ParentCountPerInterval", H5T_NATIVE_UINT, parentCellCountPerInterval, &numValues, 1);
	}
	else if (intervalCount == 1)
	{
		resqml2__IntegerConstantArray* xmlChildCountPerInterval = soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1);
		xmlChildCountPerInterval->Value = *childCellCountPerInterval;
		xmlChildCountPerInterval->Count = 1;
		regrid->Intervals->ChildCountPerInterval = xmlChildCountPerInterval;

		resqml2__IntegerConstantArray* xmlParentCountPerInterval = soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1);
		xmlParentCountPerInterval->Value = *parentCellCountPerInterval;
		xmlParentCountPerInterval->Count = 1;
		regrid->Intervals->ParentCountPerInterval = xmlParentCountPerInterval;
	}
	else if (intervalCount == 0)
		throw invalid_argument("Cannot regrid an empty list of intervals.");
	else
		throw invalid_argument("The HDF proxy is missing.");
	
	if (childCellWeights != nullptr)
	{
		resqml2__DoubleHdf5Array* hdf5ChildCellWeights = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
		regrid->Intervals->ChildCellWeights = hdf5ChildCellWeights;
		hdf5ChildCellWeights->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		hdf5ChildCellWeights->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ChildCellWeights->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_" + dimension + "Regrid_ChildCellWeights";
		
		// HDF
		hsize_t numValues = 0;
		for (unsigned int i = 0; i < intervalCount; ++i)
			numValues += childCellCountPerInterval[i];
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "ParentWindow_" + dimension + "Regrid_ChildCellWeights", childCellWeights, &numValues, 1);
	}

	return regrid;
}

void AbstractGridRepresentation::setParentWindow(ULONG64 * cellIndices, const ULONG64 & cellIndexCount, UnstructuredGridRepresentation* parentGrid)
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	resqml2__CellParentWindow* cpw = soap_new_resqml2__CellParentWindow(rep->soap, 1);
	rep->ParentWindow = cpw;

	cpw->ParentGrid = parentGrid->newResqmlReference();
	if (cellIndexCount > 1 && hdfProxy != nullptr)
	{
		resqml2__IntegerHdf5Array* hdf5CellIndices = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
		cpw->CellIndices = hdf5CellIndices;

		hdf5CellIndices->NullValue = (numeric_limits<ULONG64>::max)();
		hdf5CellIndices->Values = soap_new_eml__Hdf5Dataset(rep->soap, 1);
		hdf5CellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5CellIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_CellIndices";
		
		// HDF
		hsize_t numValues = cellIndexCount;
		hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy->uuid, "ParentWindow_CellIndices", cellIndices, &numValues, 1);
	}
	else if (cellIndexCount == 1)
	{
		resqml2__IntegerConstantArray* xmlCellIndices = soap_new_resqml2__IntegerConstantArray(rep->soap, 1);
		xmlCellIndices->Value = *cellIndices;
		xmlCellIndices->Count = 1;
		cpw->CellIndices = xmlCellIndices;
	}
	else if (cellIndexCount == 0)
		throw invalid_argument("Cannot regrid an empty list of cells.");
	else
		throw invalid_argument("The HDF proxy is missing.");
	
	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(unsigned int * columnIndices, const unsigned int & columnIndexCount,
			const unsigned int & kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount,
			AbstractColumnLayerGridRepresentation* parentGrid, double * childCellWeights)
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	resqml2__ColumnLayerParentWindow* clpw = soap_new_resqml2__ColumnLayerParentWindow(rep->soap, 1);
	rep->ParentWindow = clpw;

	clpw->ParentGrid = parentGrid->newResqmlReference();

	// COLUMN INDICES
	if (columnIndexCount > 1 && hdfProxy != nullptr)
	{
		resqml2__IntegerHdf5Array* hdf5ColumnIndices = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
		clpw->ColumnIndices = hdf5ColumnIndices;

		hdf5ColumnIndices->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ColumnIndices->Values = soap_new_eml__Hdf5Dataset(rep->soap, 1);
		hdf5ColumnIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ColumnIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_ColumnIndices";
		
		// HDF
		hsize_t numValues = columnIndexCount;
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "ParentWindow_ColumnIndices", H5T_NATIVE_UINT, columnIndices, &numValues, 1);
	}
	else if (columnIndexCount == 1)
	{
		resqml2__IntegerConstantArray* xmlColumnIndices = soap_new_resqml2__IntegerConstantArray(rep->soap, 1);
		xmlColumnIndices->Value = *columnIndices;
		xmlColumnIndices->Count = 1;
		clpw->ColumnIndices = xmlColumnIndices;
	}
	else if (columnIndexCount == 0)
		throw invalid_argument("Cannot regrid an empty list of columns.");
	else
		throw invalid_argument("The HDF proxy is missing.");

	// K Regrid
	clpw->KRegrid = createRegrid(kLayerIndexRegridStart, childCellCountPerInterval, parentCellCountPerInterval, intervalCount, childCellWeights, "K");

	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(
	const unsigned int & iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  const unsigned int & iIntervalCount,
	const unsigned int & jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  const unsigned int & jIntervalCount,
	const unsigned int & kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  const unsigned int & kIntervalCount,
	AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	resqml2__IjkParentWindow* ijkpw = soap_new_resqml2__IjkParentWindow(rep->soap, 1);
	rep->ParentWindow = ijkpw;

	ijkpw->ParentGrid = parentGrid->newResqmlReference();
	
	// Regrids
	ijkpw->IRegrid = createRegrid(iCellIndexRegridStart, childCellCountPerIInterval, parentCellCountPerIInterval, iIntervalCount, iChildCellWeights, "I");
	ijkpw->JRegrid = createRegrid(jCellIndexRegridStart, childCellCountPerJInterval, parentCellCountPerJInterval, jIntervalCount, jChildCellWeights, "J");
	ijkpw->KRegrid = createRegrid(kCellIndexRegridStart, childCellCountPerKInterval, parentCellCountPerKInterval, kIntervalCount, kChildCellWeights, "K");

	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(
	const unsigned int & iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
	const unsigned int & jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
	const unsigned int & kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
	AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	setParentWindow(
		iCellIndexRegridStart, &iChildCellCount, &iParentCellCount, 1,
		jCellIndexRegridStart, &jChildCellCount, &jParentCellCount, 1,
		kCellIndexRegridStart, &kChildCellCount, &kParentCellCount, 1,
		parentGrid, iChildCellWeights, jChildCellWeights, kChildCellWeights);
}

void AbstractGridRepresentation::setForcedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount)
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	if (rep->ParentWindow != nullptr)
	{
		resqml2__AbstractIntegerArray* xmlCellIndices = nullptr;
		if (cellIndexCount > 1 && hdfProxy != nullptr)
		{
			xmlCellIndices = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
			static_cast<resqml2__IntegerHdf5Array*>(xmlCellIndices)->NullValue = (numeric_limits<ULONG64>::max)();
			static_cast<resqml2__IntegerHdf5Array*>(xmlCellIndices)->Values = soap_new_eml__Hdf5Dataset(rep->soap, 1);
			static_cast<resqml2__IntegerHdf5Array*>(xmlCellIndices)->Values->HdfProxy = hdfProxy->newResqmlReference();
			static_cast<resqml2__IntegerHdf5Array*>(xmlCellIndices)->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_CellIndices";
			
			// HDF
			hsize_t numValues = cellIndexCount;
			hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy->uuid, "ParentWindow_CellIndices", cellIndices, &numValues, 1);
		}
		else if (cellIndexCount == 1)
		{
			xmlCellIndices = soap_new_resqml2__IntegerConstantArray(rep->soap, 1);
			static_cast<resqml2__IntegerConstantArray*>(xmlCellIndices)->Value = *cellIndices;
			static_cast<resqml2__IntegerConstantArray*>(xmlCellIndices)->Count = 1;
		}
		else if (cellIndexCount == 0)
			throw invalid_argument("Cannot force an empty list of cells.");
		else
			throw invalid_argument("The HDF proxy is missing.");

		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->OmitParentCells = xmlCellIndices;
		}
		else if  (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow)->OmitParentCells = xmlCellIndices;
		}
		else
			throw invalid_argument("You can only force parent cell on a ijk or column layer parent window.");
	}
	else
		throw invalid_argument("You cannot force parent cell without a parent window. Set the parent window first please.");
}

void AbstractGridRepresentation::setCellOverlap(const ULONG64 & parentChildCellPairCount, ULONG64 * parentChildCellPair,
			const gsoap_resqml2_0_1::eml__VolumeUom & volumeUom, double * overlapVolumes)
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	if (rep->ParentWindow != nullptr)
	{
		if (parentChildCellPairCount > 0 && hdfProxy != nullptr)
		{
			rep->ParentWindow->CellOverlap = soap_new_resqml2__CellOverlap(gsoapProxy->soap, 1);

			resqml2__IntegerHdf5Array* hdf5CellPairs = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence = soap_new___resqml2__CellOverlap_sequence(rep->soap, 1);
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence->Count = parentChildCellPairCount;
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence->ParentChildCellPairs = hdf5CellPairs;
			hdf5CellPairs->NullValue = (numeric_limits<ULONG64>::max)();
			hdf5CellPairs->Values = soap_new_eml__Hdf5Dataset(rep->soap, 1);
			hdf5CellPairs->Values->HdfProxy = hdfProxy->newResqmlReference();
			hdf5CellPairs->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_CellOverlap";
		
			// HDF
			hsize_t numValues[] = {parentChildCellPairCount, 2};
			hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy->uuid, "ParentWindow_CellOverlap", parentChildCellPair, numValues, 2);
		}
		else if (parentChildCellPairCount == 0)
			throw invalid_argument("Cannot give cell overlap information with an empty list of cell pairs.");
		else
			throw invalid_argument("The HDF proxy is missing.");

		if (overlapVolumes != nullptr)
		{
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume = soap_new_resqml2__OverlapVolume(rep->soap, 1);
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence = soap_new___resqml2__OverlapVolume_sequence(rep->soap, 1);
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence->VolumeUom = volumeUom;

			resqml2__DoubleHdf5Array* hdf5OverlapVolume = soap_new_resqml2__DoubleHdf5Array(rep->soap, 1);
			rep->ParentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence->OverlapVolumes = hdf5OverlapVolume;
			hdf5OverlapVolume->Values = soap_new_eml__Hdf5Dataset(rep->soap, 1);
			hdf5OverlapVolume->Values->HdfProxy = hdfProxy->newResqmlReference();
			hdf5OverlapVolume->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ParentWindow_OverlapVolume";
		
			// HDF
			hsize_t numValues = parentChildCellPairCount;
			hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "ParentWindow_OverlapVolume", overlapVolumes, &numValues, 1);
		}
	}
	else
		throw invalid_argument("You cannot give cell overlap information without a parent window. Set the parent window first please.");
}

LONG64 AbstractGridRepresentation::getParentCellIndexCount() const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__CellParentWindow)
		{
			resqml2__CellParentWindow* cpw = static_cast<resqml2__CellParentWindow*>(rep->ParentWindow);
			if (cpw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
			{
				return hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(cpw->CellIndices)->Values->PathInHdfFile);
			}
			else
				throw invalid_argument("This list of cells can only be stored in HDF5 file.");
		}
		else
			throw invalid_argument("This information is only avaialble for cell parent window.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

void AbstractGridRepresentation::getParentCellIndices(ULONG64 * parentCellIndices) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__CellParentWindow)
		{
			resqml2__CellParentWindow* cpw = static_cast<resqml2__CellParentWindow*>(rep->ParentWindow);
			if (cpw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
			{
				hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(cpw->CellIndices)->Values->PathInHdfFile, parentCellIndices);
			}
			else
				throw invalid_argument("This list of cells can only be stored in HDF5 file.");
		}
		else
			throw invalid_argument("This information is only avaialble for cell parent window.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

LONG64 AbstractGridRepresentation::getParentColumnIndexCount() const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			resqml2__ColumnLayerParentWindow* clpw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
			if (clpw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
			{
				return hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(clpw->ColumnIndices)->Values->PathInHdfFile);
			}
			else
				throw invalid_argument("This list of columns can only be stored in HDF5 file.");
		}
		else
			throw invalid_argument("This information is only avaialble for column layer parent window.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

void AbstractGridRepresentation::getParentColumnIndices(ULONG64 * parentColumnIndices) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			resqml2__ColumnLayerParentWindow* clpw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
			if (clpw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
			{
				return hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(clpw->ColumnIndices)->Values->PathInHdfFile, parentColumnIndices);
			}
			else
				throw invalid_argument("This list of columns can only be stored in HDF5 file.");
		}
		else
			throw invalid_argument("This information is only avaialble for column layer parent window.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

ULONG64 AbstractGridRepresentation::getRegridStartIndexOnParentGrid(const char & dimension) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			if (dimension == 'i' || dimension == 'I')
			{
				return static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->IRegrid->InitialIndexOnParentGrid;
			}
			else if (dimension == 'j' || dimension == 'J')
			{
				return static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->JRegrid->InitialIndexOnParentGrid;
			}
			else if (dimension == 'k' || dimension == 'K')
			{
				return static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->KRegrid->InitialIndexOnParentGrid;
			}
			else
				throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
		}
		else if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			if (dimension == 'k' || dimension == 'K')
			{
				return static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow)->KRegrid->InitialIndexOnParentGrid;
			}
			else
				throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
		}
		else
			throw invalid_argument("Regrid information is only avaialble for ijk or column layer parent window.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

ULONG64 AbstractGridRepresentation::getRegridIntervalCount(const char & dimension) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			if (dimension == 'i' || dimension == 'I')
			{
				if (static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->IRegrid->Intervals != nullptr)
					return static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->IRegrid->Intervals->IntervalCount;
				else
					return 0;
			}
			else if (dimension == 'j' || dimension == 'J')
			{
				if (static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->JRegrid->Intervals != nullptr)
					return static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->JRegrid->Intervals->IntervalCount;
				else
					return 0;
			}
			else if (dimension == 'k' || dimension == 'K')
			{
				if (static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->KRegrid->Intervals != nullptr)
					return static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow)->KRegrid->Intervals->IntervalCount;
				else
					return 0;
			}
			else
				throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
		}
		else if  (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			if (dimension == 'k' || dimension == 'K')
			{
				if (static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow)->KRegrid->Intervals != nullptr )
					return static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow)->KRegrid->Intervals->IntervalCount;
				else
					return 0;
			}
			else
				throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
		}
		else
			throw invalid_argument("The parent window has not got any regrid information.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

void AbstractGridRepresentation::getRegridChildCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			resqml2__IjkParentWindow* ijkpw = static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow);
			if (dimension == 'i' || dimension == 'I')
			{
				if (ijkpw->IRegrid->Intervals != nullptr)
				{
					if (ijkpw->IRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(ijkpw->IRegrid->Intervals->ChildCountPerInterval)->Values->PathInHdfFile, childCellCountPerInterval);
					else if (ijkpw->IRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(ijkpw->IRegrid->Intervals->ChildCountPerInterval)->Count; ++i)
							childCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(ijkpw->IRegrid->Intervals->ChildCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for I regrid.");
			}
			else if (dimension == 'j' || dimension == 'J')
			{
				if (ijkpw->JRegrid->Intervals != nullptr)
				{
					if (ijkpw->JRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(ijkpw->JRegrid->Intervals->ChildCountPerInterval)->Values->PathInHdfFile, childCellCountPerInterval);
					else if (ijkpw->JRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(ijkpw->JRegrid->Intervals->ChildCountPerInterval)->Count; ++i)
							childCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(ijkpw->JRegrid->Intervals->ChildCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for J regrid.");
			}
			else if (dimension == 'k' || dimension == 'K')
			{
				if (ijkpw->KRegrid->Intervals != nullptr)
				{
					if (ijkpw->KRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(ijkpw->KRegrid->Intervals->ChildCountPerInterval)->Values->PathInHdfFile, childCellCountPerInterval);
					else if (ijkpw->KRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(ijkpw->KRegrid->Intervals->ChildCountPerInterval)->Count; ++i)
							childCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(ijkpw->KRegrid->Intervals->ChildCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
		}
		else if  (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			if (dimension == 'k' || dimension == 'K')
			{
				resqml2__ColumnLayerParentWindow* clpw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
				if (clpw->KRegrid->Intervals != nullptr )
				{
					if (clpw->KRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(clpw->KRegrid->Intervals->ChildCountPerInterval)->Values->PathInHdfFile, childCellCountPerInterval);
					else if (clpw->KRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(clpw->KRegrid->Intervals->ChildCountPerInterval)->Count; ++i)
							childCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(clpw->KRegrid->Intervals->ChildCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
		}
		else
			throw invalid_argument("The parent window has not got any regrid information.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

void AbstractGridRepresentation::getRegridParentCellCountPerInterval(const char & dimension, ULONG64 * parentCellCountPerInterval) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			resqml2__IjkParentWindow* ijkpw = static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow);
			if (dimension == 'i' || dimension == 'I')
			{
				if (ijkpw->IRegrid->Intervals != nullptr)
				{
					if (ijkpw->IRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(ijkpw->IRegrid->Intervals->ParentCountPerInterval)->Values->PathInHdfFile, parentCellCountPerInterval);
					else if (ijkpw->IRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(ijkpw->IRegrid->Intervals->ParentCountPerInterval)->Count; ++i)
							parentCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(ijkpw->IRegrid->Intervals->ParentCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for I regrid.");
			}
			else if (dimension == 'j' || dimension == 'J')
			{
				if (ijkpw->JRegrid->Intervals != nullptr)
				{
					if (ijkpw->JRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(ijkpw->JRegrid->Intervals->ParentCountPerInterval)->Values->PathInHdfFile, parentCellCountPerInterval);
					else if (ijkpw->JRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(ijkpw->JRegrid->Intervals->ParentCountPerInterval)->Count; ++i)
							parentCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(ijkpw->JRegrid->Intervals->ParentCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for J regrid.");
			}
			else if (dimension == 'k' || dimension == 'K')
			{
				if (ijkpw->KRegrid->Intervals != nullptr)
				{
					if (ijkpw->KRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(ijkpw->KRegrid->Intervals->ParentCountPerInterval)->Values->PathInHdfFile, parentCellCountPerInterval);
					else if (ijkpw->KRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(ijkpw->KRegrid->Intervals->ParentCountPerInterval)->Count; ++i)
							parentCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(ijkpw->KRegrid->Intervals->ParentCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
		}
		else if  (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			if (dimension == 'k' || dimension == 'K')
			{
				resqml2__ColumnLayerParentWindow* clpw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
				if (clpw->KRegrid->Intervals != nullptr )
				{
					if (clpw->KRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(clpw->KRegrid->Intervals->ParentCountPerInterval)->Values->PathInHdfFile, parentCellCountPerInterval);
					else if (clpw->KRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
					{
						for (unsigned int i = 0; i < static_cast<resqml2__IntegerConstantArray*>(clpw->KRegrid->Intervals->ParentCountPerInterval)->Count; ++i)
							parentCellCountPerInterval[i] = static_cast<resqml2__IntegerConstantArray*>(clpw->KRegrid->Intervals->ParentCountPerInterval)->Value;
					}
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
		}
		else
			throw invalid_argument("The parent window has not got any regrid information.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

bool AbstractGridRepresentation::hasRegridChildCellWeights(const char & dimension) const
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			resqml2__IjkParentWindow* ijkpw = static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow);
			if (dimension == 'i' || dimension == 'I')
			{
				if (ijkpw->IRegrid->Intervals != nullptr)
				{
					return ijkpw->IRegrid->Intervals->ChildCellWeights != nullptr;
				}
				else
					throw invalid_argument("No interval for I regrid.");
			}
			else if (dimension == 'j' || dimension == 'J')
			{
				if (ijkpw->JRegrid->Intervals != nullptr)
				{
					return ijkpw->JRegrid->Intervals->ChildCellWeights != nullptr;
				}
				else
					throw invalid_argument("No interval for J regrid.");
			}
			else if (dimension == 'k' || dimension == 'K')
			{
				if (ijkpw->KRegrid->Intervals != nullptr)
				{
					return ijkpw->KRegrid->Intervals->ChildCellWeights != nullptr;
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
		}
		else if  (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			if (dimension == 'k' || dimension == 'K')
			{
				resqml2__ColumnLayerParentWindow* clpw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
				if (clpw->KRegrid->Intervals != nullptr )
				{
					return clpw->KRegrid->Intervals->ChildCellWeights != nullptr;
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
		}
		else
			throw invalid_argument("The parent window has not got any regrid information.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

void AbstractGridRepresentation::getRegridChildCellWeights(const char & dimension, ULONG64 * childCellWeights) const
{
	
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);
	if (rep->ParentWindow != nullptr)
	{
		if (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
		{
			resqml2__IjkParentWindow* ijkpw = static_cast<resqml2__IjkParentWindow*>(rep->ParentWindow);
			if (dimension == 'i' || dimension == 'I')
			{
				if (ijkpw->IRegrid->Intervals != nullptr && ijkpw->IRegrid->Intervals->ChildCellWeights != nullptr)
				{
					if (ijkpw->IRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__DoubleHdf5Array*>(ijkpw->IRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
					else
						throw invalid_argument("ChildCellWeights should be in HDF5 file.");
				}
				else
					throw invalid_argument("No interval for I regrid.");
			}
			else if (dimension == 'j' || dimension == 'J')
			{
				if (ijkpw->JRegrid->Intervals != nullptr && ijkpw->JRegrid->Intervals->ChildCellWeights != nullptr)
				{
					if (ijkpw->JRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__DoubleHdf5Array*>(ijkpw->JRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
					else
						throw invalid_argument("ChildCellWeights should be in HDF5 file.");
				}
				else
					throw invalid_argument("No interval for J regrid.");
			}
			else if (dimension == 'k' || dimension == 'K')
			{
				if (ijkpw->KRegrid->Intervals != nullptr && ijkpw->KRegrid->Intervals->ChildCellWeights != nullptr)
				{
					if (ijkpw->KRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__DoubleHdf5Array*>(ijkpw->KRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
					else
						throw invalid_argument("ChildCellWeights should be in HDF5 file.");
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
		}
		else if  (rep->ParentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
		{
			if (dimension == 'k' || dimension == 'K')
			{
				resqml2__ColumnLayerParentWindow* clpw = static_cast<resqml2__ColumnLayerParentWindow*>(rep->ParentWindow);
				if (clpw->KRegrid->Intervals != nullptr  && clpw->KRegrid->Intervals->ChildCellWeights != nullptr)
				{
					if (clpw->KRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
						hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__DoubleHdf5Array*>(clpw->KRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
					else
						throw invalid_argument("ChildCellWeights should be in HDF5 file.");
				}
				else
					throw invalid_argument("No interval for K regrid.");
			}
			else
				throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
		}
		else
			throw invalid_argument("The parent window has not got any regrid information.");
	}
	else
		throw invalid_argument("There is no parent window on this grid.");
}

void AbstractGridRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	// LGR backward relationships
	AbstractGridRepresentation* parentGrid = getParentGrid();
	if (parentGrid != nullptr)
	{
		parentGrid->childGridSet.push_back(this);
	}
}
