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
#include "resqml2_0/WellboreMarker.h"

#include <stdexcept>

#include "resqml2_0/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0/HorizonInterpretation.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;
using namespace epc;

const char* WellboreMarker::XML_TAG = "WellboreMarker";

WellboreMarker::WellboreMarker(WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title):
	horizonInterpretation(NULL), wellboreMarkerFrameRepresentation(wellboreMarkerFrame)
{
	gsoapProxy = soap_new_resqml2__WellboreMarker(wellboreMarkerFrame->getGsoapProxy()->soap, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

WellboreMarker::WellboreMarker(WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, const gsoap_resqml2_0::resqml2__GeologicBoundaryKind & geologicBoundaryKind):
	horizonInterpretation(NULL), wellboreMarkerFrameRepresentation(wellboreMarkerFrame)
{
	gsoapProxy = soap_new_resqml2__WellboreMarker(wellboreMarkerFrame->getGsoapProxy()->soap, 1);	
	resqml2__WellboreMarker* marker = static_cast<resqml2__WellboreMarker*>(gsoapProxy);

	marker->GeologicBoundaryKind = (resqml2__GeologicBoundaryKind*)soap_malloc(gsoapProxy->soap, sizeof(resqml2__GeologicBoundaryKind));
	*(marker->GeologicBoundaryKind) = geologicBoundaryKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

bool WellboreMarker::hasAGeologicBoundaryKind()
{
	return static_cast<resqml2__WellboreMarker*>(gsoapProxy)->GeologicBoundaryKind;
}

resqml2__GeologicBoundaryKind WellboreMarker::getGeologicBoundaryKind()
{
	if (!hasAGeologicBoundaryKind())
		throw invalid_argument("The marker has not a Geologic Boundary Kind.");

	return *(static_cast<resqml2__WellboreMarker*>(gsoapProxy)->GeologicBoundaryKind);
}

std::string WellboreMarker::getHorizonInterpretationUuid() const
{
	return static_cast<resqml2__WellboreMarker*>(gsoapProxy)->Interpretation->UUID;
}

void WellboreMarker::setHorizonInterpretation(HorizonInterpretation* interp)
{
	// EPC
	horizonInterpretation = interp;
	interp->wellboreMarkerSet.push_back(this);

    // XML
	if (updateXml)
	{
        resqml2__WellboreMarker* marker = static_cast<resqml2__WellboreMarker*>(gsoapProxy);
		marker->Interpretation = interp->newResqmlReference();
	}
}

void WellboreMarker::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	updateXml = false;

	resqml2__WellboreMarker* marker = static_cast<resqml2__WellboreMarker*>(gsoapProxy);

	if (marker->Interpretation)
	{
		setHorizonInterpretation(static_cast<HorizonInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(marker->Interpretation->UUID)));
	}

	updateXml = true;
}
