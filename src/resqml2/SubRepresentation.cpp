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
#include "resqml2/SubRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

using namespace std;
using namespace epc;
using namespace resqml2;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

vector<Relationship> SubRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	AbstractRepresentation* supportingRep = getSupportingRepresentation();
	if (!supportingRep->isPartial())
	{
		Relationship rel(supportingRep->getPartNameInEpcDocument(), "", supportingRep->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
    
	return result;
}

void SubRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	// Supporting representation
	resqml2::AbstractRepresentation* supportingRepInEpc = getSupportingRepresentation();
	AbstractRepresentation* supportingRep = nullptr;
	if (supportingRepInEpc == nullptr) { // partial transfer
		getEpcDocument()->addWarning("The referenced grid \"" + getSupportingRepresentationTitle() + "\" (" + getSupportingRepresentationUuid() + ") is missing.");
		if (getSupportingRepresentationContentType().find(resqml2_0_1::UnstructuredGridRepresentation::XML_TAG) != 0) {
			supportingRep = epcDoc->createPartialUnstructuredGridRepresentation(getSupportingRepresentationUuid(), getSupportingRepresentationTitle());
		}
		else if (getSupportingRepresentationContentType().find(resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG) != 0) {
			supportingRep = epcDoc->createPartialIjkGridRepresentation(getSupportingRepresentationUuid(), getSupportingRepresentationTitle());
		}
	}
	else if (dynamic_cast<AbstractRepresentation*>(supportingRepInEpc) != nullptr) {
		supportingRep = static_cast<AbstractRepresentation*>(supportingRepInEpc);
	}
	else {
		throw logic_error("The referenced supporting representation does not look to be a representation.");
	}

	supportingRep->addSubRepresentation(this);
}

ULONG64 SubRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	if (getElementKindOfPatch(patchIndex, 0) == NODE)
		return getElementCountOfPatch(patchIndex);
	else
		throw logic_error("Not yet implemented.");
}

void SubRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	throw logic_error("Not implemented yet");
}

resqml2::AbstractRepresentation* SubRepresentation::getSupportingRepresentation() const
{
	return static_cast<resqml2::AbstractRepresentation*>(getEpcDocument()->getResqmlAbstractObjectByUuid(getSupportingRepresentationUuid()));
}
