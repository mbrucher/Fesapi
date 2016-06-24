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
#include "resqml2/GridConnectionSetRepresentation.h"

#include <algorithm>
#if defined(__gnu_linux__) || defined(__APPLE__) 
#include <stdexcept>
#endif 

#include "hdf5.h"

#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/AbstractGridRepresentation.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace epc;
using namespace resqml2;
using namespace gsoap_resqml2_0_1;

const char* GridConnectionSetRepresentation::XML_TAG = "GridConnectionSetRepresentation";

vector<Relationship> GridConnectionSetRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	const unsigned int supportingGridCount = getSupportingGridRepresentationCount();
	for (unsigned int i = 0; i < supportingGridCount; ++i)
	{
		resqml2_0_1::AbstractGridRepresentation* grid = getSupportingGridRepresentation(i);
		Relationship relSupportingGrid(grid->getPartNameInEpcDocument(), "", grid->getUuid());
		relSupportingGrid.setDestinationObjectType();
		result.push_back(relSupportingGrid);
	}
    
	const unsigned int interpCount = getInterpretationCount();
	for (unsigned int i = 0; i < interpCount; ++i)
	{
		AbstractFeatureInterpretation* interp = getInterpretationFromIndex(i);
		Relationship relInterp(interp->getPartNameInEpcDocument(), "", interp->getUuid());
		relInterp.setDestinationObjectType();
		result.push_back(relInterp);
	}

	return result;
}

void GridConnectionSetRepresentation::pushBackSupportingGridRepresentation(resqml2_0_1::AbstractGridRepresentation * supportingGridRep)
{
	if (supportingGridRep == nullptr) {
		throw invalid_argument("The supporting Grid Representation cannot be null.");
	}

	// EPC
	supportingGridRep->gridConnectionSetRepresentationSet.push_back(this);

	// XML
	if (updateXml) {
		pushBackXmlSupportingGridRepresentation(supportingGridRep);
	}
}

void GridConnectionSetRepresentation::pushBackInterpretation(AbstractFeatureInterpretation* interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation to push back cannot be null.");
	}

	if (std::find(interp->gridConnectionSetRepresentationSet.begin(), interp->gridConnectionSetRepresentationSet.end(), this) == interp->gridConnectionSetRepresentationSet.end()) {
		interp->gridConnectionSetRepresentationSet.push_back(this);
	}

	if (updateXml) {
		pushBackXmlInterpretation(interp);
	}
}

void GridConnectionSetRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	// Supporting grid representation
	updateXml = false;
	unsigned int supportingGridCount = getSupportingGridRepresentationCount();
	for (unsigned int i = 0; i < supportingGridCount; ++i) {
		resqml2_0_1::AbstractGridRepresentation* supportingGridRep = epcDocument->getResqmlAbstractObjectByUuid<resqml2_0_1::AbstractGridRepresentation>(getSupportingGridRepresentationUuid(i));
		if (supportingGridRep == nullptr) {
			throw logic_error("Partial transfer not implemented yet for GridConnectionSetRepresentation");
		}
		else {
			pushBackSupportingGridRepresentation(static_cast<resqml2_0_1::AbstractGridRepresentation*>(supportingGridRep));
		}
	}
	updateXml = true;

	if (isAssociatedToInterpretations()) {
		updateXml = false;
		unsigned int interpCount = getInterpretationCount();
		for (unsigned int i = 0; i < interpCount; ++i) {
			resqml2::AbstractFeatureInterpretation* interp = epcDocument->getResqmlAbstractObjectByUuid<AbstractFeatureInterpretation>(getInterpretationUuidFromIndex(i));
			if (interp == nullptr) {
				throw logic_error("Partial transfer not implemented yet for GridConnectionSetRepresentation");
			}
			else {
				pushBackInterpretation(static_cast<AbstractFeatureInterpretation*>(interp));
			}
		}
		updateXml = true;
	}
}

ULONG64 GridConnectionSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	throw logic_error("Not implemented yet");
}

void GridConnectionSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	throw logic_error("Not implemented yet");
}

AbstractFeatureInterpretation * GridConnectionSetRepresentation::getInterpretationFromIndex(const unsigned int & interpretationIndex) const
{
	return static_cast<AbstractFeatureInterpretation*>(epcDocument->getResqmlAbstractObjectByUuid(getInterpretationUuidFromIndex(interpretationIndex)));
}

resqml2_0_1::AbstractGridRepresentation* GridConnectionSetRepresentation::getSupportingGridRepresentation(unsigned int index) const 
{
	return static_cast<resqml2_0_1::AbstractGridRepresentation*>(epcDocument->getResqmlAbstractObjectByUuid(getSupportingGridRepresentationUuid(index)));
}
