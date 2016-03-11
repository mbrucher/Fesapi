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
#include "resqml2_0_1/BlockedWellboreRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/AbstractGridRepresentation.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* BlockedWellboreRepresentation::XML_TAG = "BlockedWellboreRepresentation";

void BlockedWellboreRepresentation::init(soap* soapContext,
	const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREBlockedWellboreRepresentation(soapContext, 1);
	_resqml2__BlockedWellboreRepresentation* frame = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	frame->Trajectory = traj->newResqmlReference();
	trajectory = traj;
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> BlockedWellboreRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = WellboreFrameRepresentation::getAllEpcRelationships();

	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < rep->Grid.size(); ++i)
	{
		Relationship relSupportingGrid(misc::getPartNameFromReference(rep->Grid[i]), "", rep->Grid[i]->UUID);
		relSupportingGrid.setDestinationObjectType();
		result.push_back(relSupportingGrid);
	}

	return result;
}

void BlockedWellboreRepresentation::setIntevalGridCells(unsigned int * gridIndices, unsigned int gridIndicesNullValue, unsigned int cellCount, ULONG64* cellIndices, unsigned char* localFacePairPerCellIndices, unsigned char localFacePairPerCellIndicesNullValue, AbstractHdfProxy * hdfProxy)
{
	// Preconditions
	if (getXyzPointCountOfAllPatches() == 0)
	{
		throw logic_error("You must first provide MD values of the frame before to use this method");
	}
	if (gridIndices == nullptr)
	{
		throw invalid_argument("The grid indices cannot be null.");
	}
	if (cellCount == 0)
	{
		throw invalid_argument("The intersected cell count must not be zero.");
	}
	if (cellIndices == nullptr)
	{
		throw invalid_argument("The cell indices cannot be null.");
	}
	if (localFacePairPerCellIndices == nullptr)
	{
		throw invalid_argument("The local Face Per Cell Indices cannot be null.");
	}

	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);
	rep->CellCount = cellCount;

	setHdfProxy(hdfProxy);

	// gridIndices
	// XML
	resqml2__IntegerHdf5Array* xmlGridIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlGridIndices->NullValue = gridIndicesNullValue;
	xmlGridIndices->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlGridIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlGridIndices->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/GridIndices";
	rep->GridIndices = xmlGridIndices;
	// HDF
	hsize_t dimGridIndices[] = { rep->NodeCount };
	hdfProxy->writeArrayNd(rep->uuid,
		"GridIndices",
		H5T_NATIVE_UINT,
		gridIndices,
		dimGridIndices, 1);

	// cellIndices
	// XML
	resqml2__IntegerHdf5Array* xmlCellIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlCellIndices->NullValue = -1;
	xmlCellIndices->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlCellIndices->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/CellIndices";
	rep->CellIndices = xmlCellIndices;
	// HDF
	hsize_t dimCellIndices[] = { cellCount };
	hdfProxy->writeArrayNd(rep->uuid,
		"CellIndices",
		H5T_NATIVE_ULLONG,
		cellIndices,
		dimCellIndices, 1);

	// localFacePairPerCellIndices
	// XML
	resqml2__IntegerHdf5Array* xmlLocalFacePairPerCellIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlLocalFacePairPerCellIndices->NullValue = localFacePairPerCellIndicesNullValue;
	xmlLocalFacePairPerCellIndices->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlLocalFacePairPerCellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlLocalFacePairPerCellIndices->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/LocalFacePairPerCellIndices";
	rep->LocalFacePairPerCellIndices = xmlLocalFacePairPerCellIndices;
	// HDF
	hsize_t dimLocalFacePerCellIndicesNullValue[] = { cellCount*2 };
	hdfProxy->writeArrayNd(rep->uuid,
		"LocalFacePairPerCellIndices",
		H5T_NATIVE_UCHAR,
		localFacePairPerCellIndices,
		dimLocalFacePerCellIndicesNullValue, 1);

}

void BlockedWellboreRepresentation::pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep)
{
	if (!supportingGridRep)
	{
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	supportingGridRep->blockedWellboreRepresentationSet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.push_back(supportingGridRep->newResqmlReference());
	}
}

std::string BlockedWellboreRepresentation::getSupportingGridRepresentationUuid(unsigned int index) const
{
	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	if (index >= rep->Grid.size())
	{
		throw range_error("The requested index is out of range of the available supporting grid representations.");
	}
	return rep->Grid[index]->UUID;
}

void BlockedWellboreRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__BlockedWellboreRepresentation* rep = static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1);

	// Supporting grid representation
	updateXml = false;
	for (size_t i = 0; i < rep->Grid.size(); ++i)
	{
		resqml2::AbstractObject* supportingGridRep = epcDocument->getResqmlAbstractObjectByUuid(rep->Grid[i]->UUID);
		if (dynamic_cast<AbstractGridRepresentation*>(supportingGridRep) == nullptr)
		{
			throw logic_error("The referenced supporting grid rep does not look to be a grid rep.");
		}

		pushBackSupportingGridRepresentation(static_cast<AbstractGridRepresentation*>(supportingGridRep));
	}
	updateXml = true;

}

unsigned int BlockedWellboreRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml2__BlockedWellboreRepresentation*>(gsoapProxy2_0_1)->Grid.size();
}

AbstractGridRepresentation* BlockedWellboreRepresentation::getSupportingGridRepresentation(unsigned int index) const
{
	return static_cast<AbstractGridRepresentation*>(epcDocument->getResqmlAbstractObjectByUuid(getSupportingGridRepresentationUuid(index)));
}
