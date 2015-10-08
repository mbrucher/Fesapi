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
#include "resqml2_0_1/AbstractGridRepresentation.h"

#include <stdexcept>
#include <limits>

#include "resqml2_0_1/AbstractHdfProxy.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

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
			throw domain_error("The grid Connections Representation associated to the grid cannot be NULL.");
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
			throw domain_error("The child grid cannot be NULL.");
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

void AbstractGridRepresentation::setCellParentWindow(ULONG64 * cellIndices, const ULONG64 & cellIndexCount, AbstractGridRepresentation* parentGrid)
{
	resqml2__AbstractGridRepresentation* rep = static_cast<resqml2__AbstractGridRepresentation*>(gsoapProxy);

	resqml2__CellParentWindow* cpw = soap_new_resqml2__CellParentWindow(rep->soap, 1);
	rep->ParentWindow = cpw;

	cpw->ParentGrid = parentGrid->newResqmlReference();
	if (hdfProxy != nullptr)
	{
		resqml2__IntegerHdf5Array* hdf5CellIndices = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
		cpw->CellIndices = hdf5CellIndices;

		hdf5CellIndices->NullValue = (numeric_limits<ULONG64>::max)();
		hdf5CellIndices->Values = soap_new_eml__Hdf5Dataset(rep->soap, 1);
		hdf5CellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5CellIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/CellParentWindow_CellIndices";
		
		// HDF
		hsize_t numValues = cellIndexCount;
		hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy->uuid, "CellParentWindow_CellIndices", cellIndices, &numValues, 1);
	}
	else
		throw invalid_argument("The HDF proxy is missing.");
	
	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);

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
