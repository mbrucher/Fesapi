#include "resqml2_0_1test/RightHanded4x3x2ExplicitIjkGrid.h"

#include "catch.hpp"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

const char* RightHanded4x3x2ExplicitIjkGrid::defaultUuid = "f274d3d8-80ff-4860-90fb-609716303887";
const char* RightHanded4x3x2ExplicitIjkGrid::defaultTitle = "Right Handed 4x3x2 Explicit Ijk Grid";
const ULONG64 RightHanded4x3x2ExplicitIjkGrid::nodesCountIjkGridRepresentation = 72;
double RightHanded4x3x2ExplicitIjkGrid::nodesIjkGridRepresentation[] = {
	0, 150, 300, 150, 150, 300, 375, 150, 300, 550, 150, 350, 700, 150, 350, //IJ0K0
	0, 100, 300, 150, 100, 300, 375, 100, 300, 550, 100, 350, 700, 100, 350, //IJ1K0
	0, 50, 300, 150, 50, 300, 375, 50, 300, 550, 50, 350, 700, 50, 350, //IJ2K0
	0, 0, 300, 150, 0, 300, 375, 0, 300, 550, 0, 350, 700, 0, 350, //IJ3K0
	375, 0, 350, 375, 50, 350, 375, 100, 350, 375, 150, 350, // SPLIT K0
	0, 150, 400, 150, 150, 400, 375, 150, 400, 550, 150, 450, 700, 150, 450, //IJ0K1
	0, 100, 400, 150, 100, 400, 375, 100, 400, 550, 100, 450, 700, 100, 450, //IJ1K1
	0, 50, 400, 150, 50, 400, 375, 50, 400, 550, 50, 450, 700, 50, 450, //IJ2K1
	0, 0, 400, 150, 0, 400, 375, 0, 400, 550, 0, 450, 700, 0, 450, //IJ3K1
	375, 0, 450, 375, 50, 450, 375, 100, 450, 375, 150, 450, // SPLIT K1
	0, 150, 500, 150, 150, 500, 375, 150, 500, 550, 150, 550, 700, 150, 550, //IJ0K2
	0, 100, 500, 150, 100, 500, 375, 100, 500, 550, 100, 550, 700, 100, 550, //IJ1K2
	0, 50, 500, 150, 50, 500, 375, 50, 500, 550, 50, 550, 700, 50, 550, //IJ2K2
	0, 0, 500, 150, 0, 500, 375, 0, 500, 550, 0, 550, 700, 0, 550, //IJ3K2
	375, 0, 550, 375, 50, 550, 375, 100, 550, 375, 150, 550 // SPLIT K2
};

RightHanded4x3x2ExplicitIjkGrid::RightHanded4x3x2ExplicitIjkGrid(const string & epcDocPath)
	: AbstractIjkGridRepresentationTest(epcDocPath, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
}

RightHanded4x3x2ExplicitIjkGrid::RightHanded4x3x2ExplicitIjkGrid(EpcDocument * epcDoc, bool init)
	: AbstractIjkGridRepresentationTest(epcDoc, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void RightHanded4x3x2ExplicitIjkGrid::initEpcDocHandler() {
	// getting the local depth 3d crs
	LocalDepth3dCrsTest* crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
	resqml2_0_1::LocalDepth3dCrs* crs = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ijk grid
	resqml2_0_1::IjkGridExplicitRepresentation* ijkGrid = this->epcDoc->createIjkGridExplicitRepresentation(crs, uuid, title, 4, 3, 2);
	REQUIRE(ijkGrid != nullptr);
	unsigned int pillarOfCoordinateLine[4] = { 2, 7, 12, 17 };
	unsigned int splitCoordinateLineColumnCumulativeCount[4] = { 1, 3, 5, 6 };
	unsigned int splitCoordinateLineColumns[6] = { 2, 2, 6, 6, 10, 10 };
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, this->xyzPointsOfAllPatchesInGlobalCrs, hdfProxy,
		4, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// cleaning
	delete crsTest;
}

void RightHanded4x3x2ExplicitIjkGrid::readEpcDocHandler() {
}