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
#include "resqml2_0_1/EarthModelInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* EarthModelInterpretation::XML_TAG = "EarthModelInterpretation";

EarthModelInterpretation::EarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const string & title):
	structuralOrganization(nullptr), stratigraphicColumn(nullptr)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREEarthModelInterpretation(orgFeat->getGsoapContext(), 1);
	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	interp->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(orgFeat);
}

void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization)
{
    // epc
    this->structuralOrganization = structOrganization;
	structuralOrganization->earthModelSet.push_back(this);
        
    // XML
	if (updateXml)
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = structOrganization->newResqmlReference();
}

void EarthModelInterpretation::setStratiColumn(StratigraphicColumn * stratiColumn)
{
    // epc
    this->stratigraphicColumn = stratiColumn;
    stratiColumn->earthModel = this;
        
    // XML
	if (updateXml)
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn = stratiColumn->newResqmlReference();
}

void EarthModelInterpretation::pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence)
{
    // epc
	this->stratigraphicOccurenceSet.push_back(stratiOccurence);
    stratiOccurence->earthModelSet.push_back(this);
        
    // XML
	if (updateXml)
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.push_back(stratiOccurence->newResqmlReference());
}

vector<Relationship> EarthModelInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();
        
    if (structuralOrganization)
    {
        Relationship rel(structuralOrganization->getPartNameInEpcDocument(), "", structuralOrganization->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

    if (stratigraphicColumn)
    {
        Relationship rel(stratigraphicColumn->getPartNameInEpcDocument(), "", stratigraphicColumn->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

	for (unsigned int i = 0; i< stratigraphicOccurenceSet.size();i++)
    {
		if (stratigraphicOccurenceSet[i])
		{
			Relationship rel(stratigraphicOccurenceSet[i]->getPartNameInEpcDocument(), "", stratigraphicOccurenceSet[i]->getUuid());
			rel.setDestinationObjectType();
			result.push_back(rel);
		}
		else
			throw domain_error("The stratigraphic occurence associated to the earth model cannot be nullptr.");
    }
        
    return result;
}
		
void EarthModelInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractFeatureInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	if (interp->Structure)
	{
		StructuralOrganizationInterpretation* structuralOrganizationInterp = static_cast<StructuralOrganizationInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->Structure->UUID));
		if (structuralOrganizationInterp)
			setStructuralOrganizationInterpretation(structuralOrganizationInterp);
	}

	if (interp->StratigraphicColumn)
	{
		StratigraphicColumn* stratCol = static_cast<StratigraphicColumn*>(epcDoc->getResqmlAbstractObjectByUuid(interp->StratigraphicColumn->UUID));
		if (stratCol)
			setStratiColumn(stratCol);
	}

	for (unsigned int i = 0; i < interp->StratigraphicOccurrences.size(); i++)
	{
		pushBackStratiOccurence(static_cast<StratigraphicOccurrenceInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->StratigraphicOccurrences[i]->UUID)));
	}

	updateXml = true;
}
