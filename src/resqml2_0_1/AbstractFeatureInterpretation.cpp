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
#include "resqml2_0_1/AbstractFeatureInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractFeature.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/GridConnectionSetRepresentation.h"

using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace std;
using namespace epc;

void AbstractFeatureInterpretation::setInterpretedFeature(AbstractFeature * feature)
{
	if (!feature)
		throw invalid_argument("The interpreted feature cannot be null.");

	// EPC
	interpretedFeature = feature;
	feature->interpretationSet.push_back(this);

	// XMl
	if (updateXml)
	{
		static_cast<resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature = feature->newResqmlReference();
	}
}

void AbstractFeatureInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	resqml2__AbstractFeatureInterpretation* interp = static_cast<resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1);
	interpretedFeature = static_cast<AbstractFeature*>(epcDoc->getResqmlAbstractObjectByUuid(interp->InterpretedFeature->UUID));
	if (interpretedFeature)
	{
		updateXml = false;
		setInterpretedFeature(interpretedFeature);
		updateXml = true;
	}
}

vector<Relationship> AbstractFeatureInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result;

	if (interpretedFeature)
	{
		Relationship rel(interpretedFeature->getPartNameInEpcDocument(), "", interpretedFeature->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	else
		throw domain_error("The feature associated to the interpretation cannot be nullptr.");
	
	for (size_t i = 0; i < representationSet.size(); i++)
	{
		if (representationSet[i] != nullptr)
		{
			Relationship relRep(representationSet[i]->getPartNameInEpcDocument(), "", representationSet[i]->getUuid());
			relRep.setSourceObjectType();
			result.push_back(relRep);
		}
		else
			throw domain_error("The representation associated to the interpretation cannot be nullptr.");
	}

	for (size_t i = 0; i < gridConnectionSetRepresentationSet.size(); i++)
	{
		if (gridConnectionSetRepresentationSet[i] != nullptr)
		{
			Relationship relGsr(gridConnectionSetRepresentationSet[i]->getPartNameInEpcDocument(), "", gridConnectionSetRepresentationSet[i]->getUuid());
			relGsr.setSourceObjectType();
			result.push_back(relGsr);
		}
		else
			throw domain_error("The representation associated to the interpretation cannot be nullptr.");
	}

	for (size_t i = 0; i < isTopFrontierSet.size(); i++)
	{
		Relationship relOrgStack(isTopFrontierSet[i]->getPartNameInEpcDocument(), "", isTopFrontierSet[i]->getUuid());
		relOrgStack.setSourceObjectType();
		result.push_back(relOrgStack);
	}

	for (size_t i = 0; i < isBottomFrontierSet.size(); i++)
	{
		Relationship relOrgStack(isBottomFrontierSet[i]->getPartNameInEpcDocument(), "", isBottomFrontierSet[i]->getUuid());
		relOrgStack.setSourceObjectType();
		result.push_back(relOrgStack);
	}

	for (size_t i = 0; i < isSideFrontierSet.size(); i++)
	{
		Relationship relOrgStack(isSideFrontierSet[i]->getPartNameInEpcDocument(), "", isSideFrontierSet[i]->getUuid());
		relOrgStack.setSourceObjectType();
		result.push_back(relOrgStack);
	}

	return result;
}

std::string AbstractFeatureInterpretation::getInterpretedFeatureUuid() const
{
	return static_cast<resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature->UUID;
}

void AbstractFeatureInterpretation::setDomain(const gsoap_resqml2_0_1::resqml2__Domain & domain)
{
	static_cast<resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = domain;
}

gsoap_resqml2_0_1::resqml2__Domain AbstractFeatureInterpretation::getDomain() const
{
	return static_cast<resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain;
}

AbstractFeature* AbstractFeatureInterpretation::getInterpretedFeature() const
{
	return interpretedFeature;
}

vector<AbstractRepresentation*> AbstractFeatureInterpretation::getRepresentationSet() const
{
	return representationSet;
}

unsigned int AbstractFeatureInterpretation::getRepresentationCount() const
{
	return representationSet.size();
}

AbstractRepresentation*	AbstractFeatureInterpretation::getRepresentation(const unsigned int & index) const
{
	if (representationSet.size() > index)
		return representationSet[index];
	else
		throw range_error("The representaiton index you are requesting is out of range.");
}

vector<GridConnectionSetRepresentation *> AbstractFeatureInterpretation::getGridConnectionSetRepresentationSet()
{
	return gridConnectionSetRepresentationSet;
}

void AbstractFeatureInterpretation::setBottomFrontierOf(StructuralOrganizationInterpretation* structOrg)
{
	isBottomFrontierSet.push_back(structOrg);
}

void AbstractFeatureInterpretation::setTopFrontierOf(StructuralOrganizationInterpretation* structOrg)
{
	isTopFrontierSet.push_back(structOrg);
}

void AbstractFeatureInterpretation::setSideFrontierOf(StructuralOrganizationInterpretation* structOrg)
{
	isSideFrontierSet.push_back(structOrg);
}
