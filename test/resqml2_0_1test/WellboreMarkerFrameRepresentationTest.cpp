#include "resqml2_0_1test/WellboreMarkerFrameRepresentationTest.h"

#include "config.h"
#include "resqml2_0_1test/WellboreInterpretationTest.h"
#include "resqml2_0_1test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1;
using namespace resqml2_0_1test;

const char* WellboreMarkerFrameRepresentationTest::defaultUuid = "8f1c7e38-afc7-4cb8-86bb-a116e9135de4";
const char* WellboreMarkerFrameRepresentationTest::defaultTitle = "Wellbore Marker Frame Representation";

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle) {
}

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(EpcDocument * epcDoc)
	: AbstractRepresentationTest(epcDoc, defaultUuid, defaultTitle) {
}

void WellboreMarkerFrameRepresentationTest::initEpcDocHandler() {
	// creating dependencies
	WellboreInterpretationTest * interpTest = new WellboreInterpretationTest(this->epcDoc, true);
	WellboreTrajectoryRepresentationTest * trajTest = new WellboreTrajectoryRepresentationTest(this->epcDoc, true);

	WellboreInterpretation * interp = static_cast<WellboreInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreInterpretationTest::defaultUuid));
	WellboreTrajectoryRepresentation * traj = static_cast<WellboreTrajectoryRepresentation*>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreTrajectoryRepresentationTest::defaultUuid));

	// cleaning
	delete interpTest;
	delete trajTest;

	// WellboreFeature marker frame
	WellboreMarkerFrameRepresentation* wmf = epcDoc->createWellboreMarkerFrameRepresentation(interp, uuid, title, traj);
	double markerMdValues[2] = { 350, 550 };
	wmf->setMdValues(markerMdValues, 2, epcDoc->getHdfProxySet()[0]);
	wmf->pushBackNewWellboreMarker("", "", gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__horizon);
	wmf->pushBackNewWellboreMarker("", "testing Fault", gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__fault);
}

void WellboreMarkerFrameRepresentationTest::readEpcDocHandler() {
	
}
