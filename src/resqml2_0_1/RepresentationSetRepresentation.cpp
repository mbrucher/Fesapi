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
#include "resqml2_0_1/RepresentationSetRepresentation.h"

#include "resqml2/AbstractFeatureInterpretation.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

RepresentationSetRepresentation::RepresentationSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, const std::string & guid, const string & title) :
	resqml2::RepresentationSetRepresentation(interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The linked interpretation cannot be null. Please use another constructor.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERepresentationSetRepresentation(interp->getGsoapContext(), 1);
	static_cast<_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
	
	// XML relationships
	setInterpretation(interp);
}

RepresentationSetRepresentation::RepresentationSetRepresentation(common::EpcDocument* epcDoc, const std::string & guid, const std::string & title)
{
	if (epcDoc == nullptr) {
		throw invalid_argument("The epc document cannot be NULL.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERepresentationSetRepresentation(epcDoc->getGsoapContext(), 1);
	static_cast<_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->IsHomogeneous = true;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}
