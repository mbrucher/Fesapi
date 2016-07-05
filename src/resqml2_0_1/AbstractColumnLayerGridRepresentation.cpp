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
#include "resqml2_0_1/AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;
using namespace std;
using namespace epc;

unsigned int AbstractColumnLayerGridRepresentation::getKCellCount() const
{
	return static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk;
}

void AbstractColumnLayerGridRepresentation::setKCellCount(const unsigned int & kCount)
{
	static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
}

void AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp)
{
	// Backward rel
	if (!stratiOrgInterp->isAssociatedToGridRepresentation(this))
	{
		stratiOrgInterp->gridRepresentationSet.push_back(this);
	}

	// XML
	if (updateXml)
	{
		resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		rep->IntervalStratigraphicUnits = soap_new_resqml2__IntervalStratigraphicUnits(rep->soap, 1);
		rep->IntervalStratigraphicUnits->StratigraphicOrganization = stratiOrgInterp->newResqmlReference();

		resqml2__IntegerHdf5Array* xmlDataset = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
		xmlDataset->NullValue = nullValue;
		xmlDataset->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		xmlDataset->Values->HdfProxy = hdfProxy->newResqmlReference();
		xmlDataset->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/IntervalStratigraphicUnits";
		rep->IntervalStratigraphicUnits->UnitIndices = xmlDataset;

		// ************ HDF *************
		hsize_t dim = getKCellCount();
		hdfProxy->writeArrayNd(rep->uuid, "IntervalStratigraphicUnits", H5T_NATIVE_ULLONG, stratiUnitIndices, &dim, 1);
	}
}

std::string AbstractColumnLayerGridRepresentation::getStratigraphicOrganizationInterpretationUuid() const
{
	string result = resqml2::AbstractGridRepresentation::getStratigraphicOrganizationInterpretationUuid();
	if (!result.empty()) {
		return result;
	}

	resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
	if (rep->IntervalStratigraphicUnits == nullptr) {
		return "";
	}

	return rep->IntervalStratigraphicUnits->StratigraphicOrganization->UUID;
}


bool AbstractColumnLayerGridRepresentation::hasIntervalStratigraphicUnitIndices() const
{
	return static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->IntervalStratigraphicUnits != nullptr;
}

ULONG64 AbstractColumnLayerGridRepresentation::getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices)
{
	resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

	if (!hasIntervalStratigraphicUnitIndices())
	{
		throw invalid_argument("This grid has no Interval StratigraphicUnits information");
	}

	if (rep->IntervalStratigraphicUnits->UnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->Values->PathInHdfFile, stratiUnitIndices);
		return static_cast<resqml2__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->NullValue;
	}

	throw logic_error("Not implemented yet.");
}

vector<Relationship> AbstractColumnLayerGridRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractGridRepresentation::getAllEpcRelationships();

	// Strati unit
	if (!hasCellStratigraphicUnitIndices() && hasIntervalStratigraphicUnitIndices())
	{
		AbstractStratigraphicOrganizationInterpretation* stratiOrg = getStratigraphicOrganizationInterpretation();
		Relationship relStrati(stratiOrg->getPartNameInEpcDocument(), "", stratiOrg->getUuid());
		relStrati.setDestinationObjectType();
		result.push_back(relStrati);
	}

	return result;
}

void AbstractColumnLayerGridRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractGridRepresentation::importRelationshipSetFromEpc(epcDoc);

	// Strati org backward relationships
	resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
	if (rep->IntervalStratigraphicUnits != nullptr)
	{
		AbstractObject* stratiOrg = getEpcDocument()->getResqmlAbstractObjectByUuid(rep->IntervalStratigraphicUnits->StratigraphicOrganization->UUID);
		if (dynamic_cast<AbstractStratigraphicOrganizationInterpretation*>(stratiOrg) != nullptr)
		{
			updateXml = false;
			setIntervalAssociationWithStratigraphicOrganizationInterpretation(nullptr, 0, static_cast<AbstractStratigraphicOrganizationInterpretation*>(stratiOrg));
			updateXml = true;
		}
		else
		{
			throw logic_error("The referenced strati organization interpretation does not look to be a strati organization interpretation.");
		}
	}
}
