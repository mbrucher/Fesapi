/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2015) 

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
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

#include <stdexcept>

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "GuidTools.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"

#include "witsml1_4_1_1/FormationMarker.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* WellboreMarkerFrameRepresentation::XML_TAG = "WellboreMarkerFrameRepresentation";

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj):
	WellboreFrameRepresentation(interp, traj->getLocalCrs())
{
	gsoapProxy = soap_new_resqml2__obj_USCOREWellboreMarkerFrameRepresentation(interp->getEpcDocument()->getGsoapContext(), 1);	
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	trajectory = traj;
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(StratigraphicColumnRankInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj):
	WellboreFrameRepresentation(interp, traj->getLocalCrs())
{
	gsoapProxy = soap_new_resqml2__obj_USCOREWellboreMarkerFrameRepresentation(interp->getEpcDocument()->getGsoapContext(), 1);	
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	trajectory = traj;
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(StratigraphicOccurrenceInterpretation* interp, const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj):
	WellboreFrameRepresentation(interp, traj->getLocalCrs())
{
	gsoapProxy = soap_new_resqml2__obj_USCOREWellboreMarkerFrameRepresentation(interp->getEpcDocument()->getGsoapContext(), 1);	
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	trajectory = traj;
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

WellboreMarkerFrameRepresentation::~WellboreMarkerFrameRepresentation()
{
	for (unsigned int i = 0; i < markerSet.size(); ++i)
		delete markerSet[i];
}

WellboreMarker* WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(const std::string & guid, const std::string & title)
{
	WellboreMarker* marker = new WellboreMarker(this, guid, title);
	markerSet.push_back(marker);

	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);
	frame->WellboreMarker.push_back(static_cast<resqml2__WellboreMarker*>(marker->getGsoapProxy()));	

	return marker;
}

WellboreMarker* WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind)
{
	WellboreMarker* marker = new WellboreMarker(this, guid, title, geologicBoundaryKind);
	markerSet.push_back(marker);

	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);
	frame->WellboreMarker.push_back(static_cast<resqml2__WellboreMarker*>(marker->getGsoapProxy()));	

	return marker;
}

unsigned int WellboreMarkerFrameRepresentation::getWellboreMarkerCount()
{
	return static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy)->WellboreMarker.size();
}

void WellboreMarkerFrameRepresentation::setWitsmlFormationMarker(const unsigned int & resqmlMarkerIndex, witsml1_4_1_1::FormationMarker * witsmlFormationMarker)
{
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);
	if (frame->WellboreMarker.size() <= resqmlMarkerIndex)
		throw out_of_range("The marker index is not valid");

	for (unsigned int i = witsmlFormationMarkerSet.size(); i < resqmlMarkerIndex+1; ++i)
		witsmlFormationMarkerSet.push_back(NULL);

	witsmlFormationMarkerSet[resqmlMarkerIndex] = witsmlFormationMarker;
	witsmlFormationMarker->resqmlWellboreMarkerFrameRepresentation = this;

	if (updateXml)
		frame->WellboreMarker[resqmlMarkerIndex]->WitsmlFormationMarker = witsmlFormationMarker->newResqmlReference();
}

vector<Relationship> WellboreMarkerFrameRepresentation::getAllEpcRelationships() const
{
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);
	
	vector<Relationship> result = WellboreFrameRepresentation::getAllEpcRelationships();

	// XML forward relationship
	for (unsigned int i = 0; i < markerSet.size(); ++i)
	{
		if (markerSet[i]->getBoundaryFeatureInterpretation())
		{
			Relationship relBoundaryFeature(markerSet[i]->getBoundaryFeatureInterpretation()->getPartNameInEpcDocument(), "", markerSet[i]->getBoundaryFeatureInterpretation()->getUuid());
			relBoundaryFeature.setDestinationObjectType();
			result.push_back(relBoundaryFeature);
		}
	}

	int firstNonNullWitsmlMarker = -1;
	for (unsigned int i = 0; i < witsmlFormationMarkerSet.size() && firstNonNullWitsmlMarker < 0; ++i)
	{
		if (witsmlFormationMarkerSet[i])
			firstNonNullWitsmlMarker = i;
	}
	if (firstNonNullWitsmlMarker>=0)
	{
		Relationship relWitsml(witsmlFormationMarkerSet[firstNonNullWitsmlMarker]->getPartNameInEpcDocument(), "", witsmlFormationMarkerSet[firstNonNullWitsmlMarker]->getUuid());
		relWitsml.setDestinationObjectType();
		result.push_back(relWitsml);
	}

	return result;
}

void WellboreMarkerFrameRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	WellboreFrameRepresentation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__WellboreMarkerFrameRepresentation* rep = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy);

	for (unsigned int i = 0; i < rep->WellboreMarker.size(); ++i)
	{
		if (rep->WellboreMarker[i]->WitsmlFormationMarker)
		{
			witsml1_4_1_1::FormationMarker* tmp = static_cast<witsml1_4_1_1::FormationMarker*>(epcDoc->getWitsmlAbstractObjectByUuid(rep->WellboreMarker[i]->WitsmlFormationMarker->UUID));
			if (tmp)
			{
				updateXml = false;
				setWitsmlFormationMarker(i, tmp);
				updateXml = true;
			}
		}

		WellboreMarker* marker = new WellboreMarker(rep->WellboreMarker[i], this);
		if (rep->WellboreMarker[i]->Interpretation)
		{
			marker->setBoundaryFeatureInterpretation(static_cast<BoundaryFeatureInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->WellboreMarker[i]->Interpretation->UUID)));
		}
		markerSet.push_back(marker);
	}

	updateXml = true;
}
