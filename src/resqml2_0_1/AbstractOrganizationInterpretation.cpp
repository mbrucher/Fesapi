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
#include "resqml2_0_1/AbstractOrganizationInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/EarthModelInterpretation.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

void AbstractOrganizationInterpretation::pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, AbstractFeatureInterpretation* directObject)
{
	if (!subject)
		throw invalid_argument("The subject of the binary contact cannot be null.");
	if (!directObject)
		throw invalid_argument("The direct object of the binary contact cannot be null.");

	resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy);

	resqml2__BinaryContactInterpretationPart* contact = soap_new_resqml2__BinaryContactInterpretationPart(org->soap, 1);
	contact->Index = org->ContactInterpretation.size();
	org->ContactInterpretation.push_back(contact);

	contact->ContactRelationship = kind;
	contact->Subject = subject->newResqmlContactElementReference(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
	contact->Verb = verb;
	contact->DirectObject = directObject->newResqmlContactElementReference(); // Not to add for EPC relationships since by business rule it must be present in the object listing/stack of the organization
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, AbstractFeatureInterpretation* directObject,
		const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier)
{
	resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy);

	pushBackBinaryContact(kind, subject, verb, directObject);
	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->DirectObject->Qualifier = static_cast<resqml2__ContactSide*>(soap_malloc(gsoapProxy->soap, sizeof(resqml2__ContactSide)));
	*(contact->DirectObject->Qualifier) = directObjectQualifier;
}

void AbstractOrganizationInterpretation::pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactSide & subjectQualifier,
        const gsoap_resqml2_0_1::resqml2__ContactVerb & verb,
        AbstractFeatureInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier)
{
    resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy);

    pushBackBinaryContact(kind, subject, verb, directObject);
    resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->Qualifier = static_cast<resqml2__ContactSide*>(soap_malloc(gsoapProxy->soap, sizeof(resqml2__ContactSide)));
    *(contact->DirectObject->Qualifier) = directObjectQualifier;
    contact->Subject->Qualifier = static_cast<resqml2__ContactSide*>(soap_malloc(gsoapProxy->soap, sizeof(resqml2__ContactSide)));
    *(contact->Subject->Qualifier) = subjectQualifier;
}
