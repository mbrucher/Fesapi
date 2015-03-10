// unitTest.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "EpcDocument.h"
#include "resqml2_0/LocalDepth3dCrs.h"
#include "resqml2_0/LocalTime3dCrs.h"
#include "resqml2_0/HdfProxy.h"
#include "resqml2_0/WellboreTrajectoryRepresentation.h"
#include "resqml2_0/MdDatum.h"
#include "resqml2_0/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0/StratigraphicColumn.h"
#include "resqml2_0/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0/StratigraphicUnitFeature.h"
#include "resqml2_0/StratigraphicUnitInterpretation.h"

using namespace std;
using namespace resqml2_0;

static const char* uuidWellbore = "0c970a12-7950-4c20-8c2d-05111b509635";
static const char* uuidWellboreInterp = "0878cefc-8019-435c-a399-5e8a23180dc1";
static const char* uuidMdDatum = "a9096300-bc89-4dcd-8ebd-fe70a53fe891";
static const char* uuidWellTrajectory = "06fc15a5-e95a-4217-a6d2-cfe5c4cbbf07";

void initEpcDocument(common::EpcDocument * epcDoc)
{
	HdfProxy* hdfProxy = epcDoc->createHdfProxy("", "Hdf Proxy", epcDoc->getStorageDirectory(), epcDoc->getName() + ".h5");
	hdfProxy->openForWriting();

	//CRS
	LocalDepth3dCrs* local3dCrs = epcDoc->createLocalDepth3dCrs("", "Default local CRS", .0, .0, .0, .0, gsoap_resqml2_0::eml__LengthUom__m, 23031, gsoap_resqml2_0::eml__LengthUom__m);
	LocalTime3dCrs* localTime3dCrs = epcDoc->createLocalTime3dCrs("", "Default local time CRS", 1.0, 0.1, .2, .0, gsoap_resqml2_0::eml__LengthUom__m, 23031, gsoap_resqml2_0::eml__TimeUom__s, gsoap_resqml2_0::eml__LengthUom__m); // CRS translation is just for testing;
}

WellboreTrajectoryRepresentation* addWellTrajectory(common::EpcDocument * epcDoc)
{
	// Features
	WellboreFeature* wellbore1 = epcDoc->createWellboreFeature(uuidWellbore, "Wellbore1");

	// Interpretations
	WellboreInterpretation* wellbore1Interp1 = epcDoc->createWellboreInterpretation(wellbore1, uuidWellboreInterp, "Wellbore1 Interp1", false);

	// Representation
	MdDatum* mdInfo = epcDoc->createMdDatum(uuidMdDatum, "md Info", epcDoc->getLocalDepth3dCrsSet()[0], gsoap_resqml2_0::resqml2__MdReference__mean_x0020sea_x0020level, 275, 75, 0);

	//Geometry	
	WellboreTrajectoryRepresentation* w1i1TrajRep = epcDoc->createWellboreTrajectoryRepresentation(wellbore1Interp1, uuidWellTrajectory, "Wellbore1 Interp1 TrajRep", mdInfo);
	double controlPoints[12] = {275, 75, 0, 275, 75, 325, 275, 75, 500, 275, 75, 1000};
	double trajectoryTangentVectors[12] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
	double trajectoryMds[4] = {0, 325, 500, 1000};
	w1i1TrajRep->setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, epcDoc->getHdfProxySet()[0]);

	return w1i1TrajRep;
}

WellboreMarkerFrameRepresentation* addWellboreMarkerFrameToStrtiOrganization(common::EpcDocument * epcDoc)
{
	WellboreTrajectoryRepresentation* w1i1TrajRep = addWellTrajectory(epcDoc);

	StratigraphicColumn* sc = epcDoc->createStratigraphicColumn("", "Stratigrahic column");
	OrganizationFeature* stratiModelFeature = epcDoc->createStratigraphicModel("", "Stratigraphic model");
	StratigraphicColumnRankInterpretation* scRank = epcDoc->createStratigraphicColumnRankInterpretationInApparentDepth(stratiModelFeature, "", "Stratigraphic rank interp", 0);
	sc->pushBackStratiColumnRank(scRank);
	StratigraphicUnitFeature* overburdenFeature = epcDoc->createStratigraphicUnit("", "Overburden");
	StratigraphicUnitFeature* stratiLayerFeature = epcDoc->createStratigraphicUnit("", "stratiLayer");
	StratigraphicUnitFeature* underburdenFeature = epcDoc->createStratigraphicUnit("", "Underburden");
	StratigraphicUnitInterpretation* overburdenInterp = epcDoc->createStratigraphicUnitInterpretation(overburdenFeature, "", "stratiLayer");
	StratigraphicUnitInterpretation* stratiLayerInterp = epcDoc->createStratigraphicUnitInterpretation(stratiLayerFeature, "", "stratiLayer");
	StratigraphicUnitInterpretation* underburdenInterp = epcDoc->createStratigraphicUnitInterpretation(underburdenFeature, "", "stratiLayer");
	scRank->pushBackStratiUnitInterpretation(overburdenInterp);
	scRank->pushBackStratiUnitInterpretation(stratiLayerInterp);
	scRank->pushBackStratiUnitInterpretation(underburdenInterp);
	StratigraphicOccurrenceInterpretation* stratiOccurence = epcDoc->createStratigraphicOccurrenceInterpretationInApparentDepth(stratiModelFeature, "", "Strati along well Interp");
	stratiOccurence->setStratigraphicColumnRankInterpretation(scRank);
	
	// WellboreFeature marker frame
	WellboreMarkerFrameRepresentation* wmf = epcDoc->createWellboreMarkerFrameRepresentation(stratiOccurence, "", "Wellbore Marker Frame", w1i1TrajRep);
	double markerMdValues[2] = {350, 550};
	wmf->setMdValuesAsArray1dOfExplicitValues(markerMdValues, 2, epcDoc->getHdfProxySet()[0]);
	wmf->pushBackNewWellboreMarker("", "", gsoap_resqml2_0::resqml2__GeologicBoundaryKind__horizon);
	wmf->pushBackNewWellboreMarker("", "testing Fault", gsoap_resqml2_0::resqml2__GeologicBoundaryKind__fault);

	return wmf;
}

TEST_CASE( "Export and import a well trajectory", "[well]" )
{
	//Export
	common::EpcDocument* epcDoc = new common::EpcDocument("../../testingWell.epc");
	initEpcDocument(epcDoc);
	
	addWellTrajectory(epcDoc);

	epcDoc->serialize();
	delete epcDoc;

	// Import
	epcDoc = new common::EpcDocument("../../testingWell.epc");
	string validationResult = epcDoc->deserialize();
	REQUIRE( validationResult.size() == 0 );
	REQUIRE( epcDoc->getLocalDepth3dCrsSet().size() == 1 );
	REQUIRE( epcDoc->getLocalTime3dCrsSet().size() == 1 );
	REQUIRE( epcDoc->getHdfProxySet().size() == 1 );

	REQUIRE( epcDoc->getWellboreCubicParamLineTrajRepSet().size() == 1);
	WellboreTrajectoryRepresentation* w1i1TrajRep = epcDoc->getWellboreCubicParamLineTrajRepSet()[0];
	REQUIRE( w1i1TrajRep->getUuid() == uuidWellTrajectory);
	REQUIRE( w1i1TrajRep->getLocalCrs() == epcDoc->getLocalDepth3dCrsSet()[0]);
	REQUIRE( w1i1TrajRep->getMdDatum()->getUuid() == uuidMdDatum);
	REQUIRE( w1i1TrajRep->getXyzPointCountOfAllPatches() == 4);
	double trajectoryMds[4];
	w1i1TrajRep->getMdValues(trajectoryMds);
	REQUIRE( trajectoryMds[0] == 0);
	REQUIRE( trajectoryMds[1] == 325);
	REQUIRE( trajectoryMds[2] == 500);
	REQUIRE( trajectoryMds[3] == 1000);
	double controlPoints[12];
	w1i1TrajRep->getXyzPointsOfAllPatchesInGlobalCrs(controlPoints);
	REQUIRE( controlPoints[0] == 275);
	REQUIRE( controlPoints[1] == 75);
	REQUIRE( controlPoints[2] == 0);
	REQUIRE( controlPoints[3] == 275);

	delete epcDoc;
}

TEST_CASE( "Export and import a wellbore marker frame", "[well][stratigraphy]" )
{
	//Export
	common::EpcDocument* epcDoc = new common::EpcDocument("../../testingStratiMarker.epc");
	initEpcDocument(epcDoc);
	
	addWellboreMarkerFrameToStrtiOrganization(epcDoc);

	epcDoc->serialize();
	delete epcDoc;

	// Import
	epcDoc = new common::EpcDocument("../../testingStratiMarker.epc");
	string validationResult = epcDoc->deserialize();
	REQUIRE( validationResult.size() == 0 );
	REQUIRE( epcDoc->getLocalDepth3dCrsSet().size() == 1 );
	REQUIRE( epcDoc->getLocalTime3dCrsSet().size() == 1 );
	REQUIRE( epcDoc->getHdfProxySet().size() == 1 );

	REQUIRE( epcDoc->getStratigraphicColumnSet().size() == 1);
	StratigraphicColumn* sc = epcDoc->getStratigraphicColumnSet()[0];
	REQUIRE( sc->getStratigraphicColumnRankInterpretationSet().size() == 1);
	StratigraphicColumnRankInterpretation* scRank = sc->getStratigraphicColumnRankInterpretationSet()[0];
	REQUIRE( scRank->getStratigraphicOccurrenceInterpretationSet().size() == 1);
	StratigraphicOccurrenceInterpretation* stratiOccurence = scRank->getStratigraphicOccurrenceInterpretationSet()[0];
	REQUIRE( stratiOccurence->getWellboreMarkerFrameRepresentationSet().size() == 1);
	WellboreMarkerFrameRepresentation* wmf = stratiOccurence->getWellboreMarkerFrameRepresentationSet()[0];
	REQUIRE( wmf->getMdValuesCount() == 2);
	double markerMdValues[2];
	wmf->getMdAsDoubleValues(markerMdValues);
	REQUIRE( markerMdValues[0] == 350);
	REQUIRE( markerMdValues[1] == 550);

	delete epcDoc;
}