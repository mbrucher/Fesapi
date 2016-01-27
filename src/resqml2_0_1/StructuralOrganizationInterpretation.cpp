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
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/EarthModelInterpretation.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* StructuralOrganizationInterpretation::XML_TAG = "StructuralOrganizationInterpretation";

StructuralOrganizationInterpretation::StructuralOrganizationInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title,
		const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREStructuralOrganizationInterpretation(orgFeat->getGsoapContext(), 1);
	
	static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy)->OrderingCriteria = orderingCriteria;
	static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy)->Domain = resqml2__Domain__mixed;

    initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(orgFeat);
}

void StructuralOrganizationInterpretation::pushBackFaultInterpretation(FaultInterpretation * faultInterpretation)
{
    // EPC
	faultInterpretationSet.push_back(faultInterpretation);
	faultInterpretation->structuralOrganizationInterpretationSet.push_back(this);

    // XML
	if (updateXml)
	{
        eml__DataObjectReference* faultInterpRef = faultInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy);
		structuralOrganization->Faults.push_back(faultInterpRef);
	}
}

FaultInterpretation* StructuralOrganizationInterpretation::getFaultInterpretation(const unsigned int & index)
{
	if (index < faultInterpretationSet.size())
		return faultInterpretationSet[index];
	else
		throw std::out_of_range("The fault index is out of range.");
}

void StructuralOrganizationInterpretation::pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank)
{
    // EPC
    horizonInterpretationSet.push_back(horizonInterpretation);
	horizonInterpretation->structuralOrganizationInterpretationSet.push_back(this);

    // XML
	if (updateXml)
	{
		_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy);

		resqml2__HorizonInterpretationIndex* horizonInterpListElement = soap_new_resqml2__HorizonInterpretationIndex(gsoapProxy->soap, 1);
		horizonInterpListElement->StratigraphicRank = static_cast<ULONG64*>(soap_malloc(gsoapProxy->soap, sizeof(ULONG64)));
		*(horizonInterpListElement->StratigraphicRank) = stratigraphicRank;
		horizonInterpListElement->Index = structuralOrganization->Horizons.size();
        eml__DataObjectReference* horizonInterpRef = horizonInterpretation->newResqmlReference();
        horizonInterpListElement->Horizon = horizonInterpRef;
		structuralOrganization->Horizons.push_back(horizonInterpListElement);
	}
}

void StructuralOrganizationInterpretation::pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation)
{
    // EPC
	topFrontierInterpretationSet.push_back(topFrontierInterpretation);
	topFrontierInterpretation->setTopFrontierOf(this);

    // XML
	if (updateXml)
	{
        eml__DataObjectReference* interpRef = topFrontierInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy);
		structuralOrganization->TopFrontier.push_back(interpRef);
	}
}

void StructuralOrganizationInterpretation::pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation)
{
    // EPC
	bottomFrontierInterpretationSet.push_back(bottomFrontierInterpretation);
	bottomFrontierInterpretation->setBottomFrontierOf(this);

    // XML
	if (updateXml)
	{
        eml__DataObjectReference* interpRef = bottomFrontierInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy);
		structuralOrganization->BottomFrontier.push_back(interpRef);
	}
}

void StructuralOrganizationInterpretation::pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation)
{
    // EPC
	sideFrontierInterpretationSet.push_back(sideFrontierInterpretation);
	sideFrontierInterpretation->setSideFrontierOf(this);

    // XML
	if (updateXml)
	{
        eml__DataObjectReference* interpRef = sideFrontierInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy);
		structuralOrganization->Sides.push_back(interpRef);
	}
}

vector<Relationship> StructuralOrganizationInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractOrganizationInterpretation::getAllEpcRelationships();

	for (unsigned int i = 0; i < faultInterpretationSet.size(); i++)
	{
		Relationship rel(faultInterpretationSet[i]->getPartNameInEpcDocument(), "", faultInterpretationSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    for (unsigned int i = 0; i < horizonInterpretationSet.size(); i++)
	{
		Relationship rel(horizonInterpretationSet[i]->getPartNameInEpcDocument(), "", horizonInterpretationSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    for (unsigned int i = 0; i < bottomFrontierInterpretationSet.size(); i++)
	{
		Relationship rel(bottomFrontierInterpretationSet[i]->getPartNameInEpcDocument(), "", bottomFrontierInterpretationSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    for (unsigned int i = 0; i < topFrontierInterpretationSet.size(); i++)
	{
		Relationship rel(topFrontierInterpretationSet[i]->getPartNameInEpcDocument(), "", topFrontierInterpretationSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    for (unsigned int i = 0; i < sideFrontierInterpretationSet.size(); i++)
	{
		Relationship rel(sideFrontierInterpretationSet[i]->getPartNameInEpcDocument(), "", sideFrontierInterpretationSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    for (unsigned int i = 0; i < earthModelSet.size(); i++)
    {
        Relationship rel(earthModelSet[i]->getPartNameInEpcDocument(), "", earthModelSet[i]->getUuid());
		rel.setSourceObjectType();
        result.push_back(rel);
    }
    
	return result;
}
		
void StructuralOrganizationInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractOrganizationInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__StructuralOrganizationInterpretation* interp = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy);

	for (unsigned int i = 0; i < interp->Faults.size(); i++)
	{
		pushBackFaultInterpretation(static_cast<FaultInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->Faults[i]->UUID)));
	}
	for (unsigned int i = 0; i < interp->Horizons.size(); i++)
	{
		if (interp->Horizons[i]->StratigraphicRank)
			pushBackHorizonInterpretation(static_cast<HorizonInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->Horizons[i]->Horizon->UUID)), *(interp->Horizons[i]->StratigraphicRank));
		else
			throw logic_error("Not yet implemented");
	}

	for (unsigned int i = 0; i < interp->TopFrontier.size(); i++)
	{
		pushBackTopFrontierInterpretation(static_cast<FaultInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->TopFrontier[i]->UUID)));
	}
	for (unsigned int i = 0; i < interp->BottomFrontier.size(); i++)
	{
		pushBackBottomFrontierInterpretation(static_cast<FaultInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->BottomFrontier[i]->UUID)));
	}
	for (unsigned int i = 0; i < interp->Sides.size(); i++)
	{
		pushBackSideFrontierInterpretation(static_cast<FaultInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->Sides[i]->UUID)));
	}

	updateXml = true;
}
