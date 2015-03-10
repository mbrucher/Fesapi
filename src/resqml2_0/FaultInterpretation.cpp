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
#include "resqml2_0/FaultInterpretation.h"

#include <limits>
#include <stdexcept>

#include "resqml2_0/GeneticBoundaryFeature.h"
#include "resqml2_0/Fault.h"
#include "resqml2_0/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;
using namespace epc;

const char* FaultInterpretation::XML_TAG = "FaultInterpretation";

FaultInterpretation::FaultInterpretation(Fault * fault, const string & guid, const string & title)
{
	if (!fault)
		throw invalid_argument("The interpreted fault cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREFaultInterpretation(fault->getGsoapProxy()->soap, 1);
	_resqml2__FaultInterpretation* interp = static_cast<_resqml2__FaultInterpretation*>(gsoapProxy);
	interp->Domain = resqml2__Domain__mixed;
	setInterpretedFeature(fault);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (fault->getEpcDocument())
		fault->getEpcDocument()->addGsoapProxy(this);
}

FaultInterpretation::FaultInterpretation(Fault * fault, const string & guid, const string & title,
										GeneticBoundaryFeature * chronoTop, GeneticBoundaryFeature * chronoBtm)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREFaultInterpretation(fault->getGsoapProxy()->soap, 1);	
	_resqml2__FaultInterpretation* interp = static_cast<_resqml2__FaultInterpretation*>(gsoapProxy);
	interp->Domain = resqml2__Domain__mixed;
	interp->InterpretedFeature = fault->newResqmlReference();

	interp->HasOccuredDuring = soap_new_resqml2__TimeInterval(interp->soap, 1);
	interp->HasOccuredDuring->ChronoBottom = chronoBtm->newResqmlReference();
	interp->HasOccuredDuring->ChronoTop = chronoTop->newResqmlReference();

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	interpretedFeature = fault;
	interpretedFeature->addInterpretation(this);

	epcDocument = fault->getEpcDocument();
	if (epcDocument)
		epcDocument->addGsoapProxy(this);
}

vector<Relationship> FaultInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = BoundaryFeatureInterpretation::getAllEpcRelationships();

	for (unsigned int i = 0; i < structuralOrganizationInterpretationSet.size(); i++)
	{
		if (structuralOrganizationInterpretationSet[i])
		{
			Relationship rel(structuralOrganizationInterpretationSet[i]->getPartNameInEpcDocument(), "", structuralOrganizationInterpretationSet[i]->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
		}
		else
			throw domain_error("The structural Organization Interpretation associated to the fault interpretation cannot be NULL.");
	}

	return result;
}

void FaultInterpretation::pushBackThrowInterpretation(const gsoap_resqml2_0::resqml2__ThrowKind & throwKind)
{
	_resqml2__FaultInterpretation* interp = static_cast<_resqml2__FaultInterpretation*>(gsoapProxy);

	resqml2__FaultThrow * throwInterp = soap_new_resqml2__FaultThrow(gsoapProxy->soap, 1);
	throwInterp->Throw.push_back(throwKind);

	interp->ThrowInterpretation.push_back(throwInterp);
}
