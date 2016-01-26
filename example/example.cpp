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
// Acknowledgements: the serializeOrganizations function have been provided by Geosiris (contact: mathieu.poudret@geosiris.com)

//#define OFFICIAL

#ifdef _WIN32
// ************************
// For memory leak
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// ************************
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "proxies/stdsoap2.h"

#include "EpcDocument.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/Fault.h"
#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/PolylineSetRepresentation.h"
#include "resqml2_0_1/PointSetRepresentation.h"
#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/Grid2dSetRepresentation.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/SeismicLineSetFeature.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/MdDatum.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/CategoricalProperty.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/TimeSeries.h"
#include "resqml2_0_1/ContinuousPropertySeries.h"

#include "resqml2_0_1/PropertyKindMapper.h"

#include "resqml2_0_1/Activity.h"
#include "resqml2_0_1/ActivityTemplate.h"

#include "witsml1_4_1_1/Well.h"
#include "witsml1_4_1_1/CoordinateReferenceSystem.h"
#include "witsml1_4_1_1/Trajectory.h"

using namespace std;
using namespace resqml2_0_1;

Horizon* horizon1;
Horizon* horizon2;
Fault* fault1;
HorizonInterpretation* horizon1Interp1;
HorizonInterpretation* horizon2Interp1;
FaultInterpretation* fault1Interp1;
Grid2dRepresentation* h1i1SingleGrid2dRep;
PolylineSetRepresentation* f1i1PolyLineRep;
TriangulatedSetRepresentation* f1i1triRepSinglePatch;
TriangulatedSetRepresentation* f1i1triRep;
TriangulatedSetRepresentation* h1i1triRep;
TriangulatedSetRepresentation* h2i1triRep;
WellboreTrajectoryRepresentation* w1i1TrajRep;
LocalDepth3dCrs* local3dCrs;
LocalTime3dCrs* localTime3dCrs;
WellboreInterpretation* wellbore1Interp1;

witsml1_4_1_1::Wellbore* witsmlWellbore = NULL;

witsml1_4_1_1::CoordinateReferenceSystem* witsmlCrs;

void serializeWells(common::EpcDocument * pck, AbstractHdfProxy* hdfProxy)
{
	witsml1_4_1_1::Trajectory* witsmlTraj = NULL;
	witsml1_4_1_1::Log* witsmlLog = NULL;

	// WELL
	witsml1_4_1_1::Well* witsmlWell = pck->createWell("", "Well1", "00:00");
	witsmlWell->setEastingNorthingLocation(gsoap_witsml1_4_1_1::witsml1__LengthUom__m, 275, 75, witsmlCrs);
	witsmlWell->pushBackDatum("","well1 msl datum", gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum__KB, "EPSG",
		"5100", "Mean Sea Level");
	witsmlWell->pushBackDatum("","well1 datum", gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum__KB, 0,
		gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom__m, 15);

	// WELLBORE
	witsmlWellbore = witsmlWell->createWellbore("", "Wellbore1");

	// TRAJECTORY
	witsmlTraj = witsmlWellbore->createTrajectory("", "Trajectory");
	double mds[4] = {15, 340, 515, 1015};
	double tvds[4] = {0, 325, 500, 1000};
	double incl[4] = {.0, .0, .0, .0};
	double azi[4] = {.0, .0, .0, .0};
	double eastings[4] = {275, 275, 275, 275};
	double northings[4] = {75, 75, 75, 75};
	witsmlTraj->setEastingNorthingTrajectoryStations(4,
		1, gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom__m, mds,
		0, gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom__m, tvds,
		gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom__rad, incl,
		gsoap_witsml1_4_1_1::witsml1__AziRef__grid_x0020north, azi,
		gsoap_witsml1_4_1_1::witsml1__LengthUom__m, eastings, northings,
		witsmlCrs);

	// LOG
	witsmlLog = witsmlWellbore->createLog("", "Log", gsoap_witsml1_4_1_1::witsml1__LogIndexType__measured_x0020depth, "MD");
	vector<string> witsmlLogMds;
	witsmlLogMds.push_back("0,0");
	witsmlLogMds.push_back("250,1");
	witsmlLogMds.push_back("500,2");
	witsmlLogMds.push_back("750,3");
	witsmlLogMds.push_back("1000,4");
	witsmlLog->setValues("", "," , "m", .0, 1000, 250, gsoap_witsml1_4_1_1::witsml1__LogIndexDirection__increasing, "MD,IntervalIdx", "m,Euc", witsmlLogMds);

	////////////////////////
	// RESQML
	////////////////////////

	// Features
	WellboreFeature* wellbore1 = pck->createWellboreFeature("", "Wellbore1");
	if (witsmlWellbore)
		wellbore1->setWitsmlWellbore(witsmlWellbore);

	// Interpretations
	wellbore1Interp1 = pck->createWellboreInterpretation(wellbore1, "", "Wellbore1 Interp1", false);

	// Representation
	MdDatum* mdInfo = pck->createMdDatum("", "md Info", local3dCrs, gsoap_resqml2_0_1::resqml2__MdReference__mean_x0020sea_x0020level, 275, 75, 0);

	//Geometry	
	w1i1TrajRep = pck->createWellboreTrajectoryRepresentation(wellbore1Interp1, "", "Wellbore1 Interp1 TrajRep", mdInfo);
	double controlPoints[12] = {275, 75, 0, 275, 75, 325, 275, 75, 500, 275, 75, 1000};
	double trajectoryTangentVectors[12] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
	double trajectoryMds[4] = {0, 325, 500, 1000};
	w1i1TrajRep->setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, hdfProxy);
	if (witsmlTraj)
		w1i1TrajRep->setWitsmlTrajectory(witsmlTraj);

	// WellboreFeature frame
	WellboreFrameRepresentation* w1i1FrameRep = pck->createWellboreFrameRepresentation(wellbore1Interp1, "", "Wellbore1 Interp1 FrameRep", w1i1TrajRep);
	double logMds[5] = {0, 250, 500, 750, 1000};
	w1i1FrameRep->setMdValues(trajectoryMds, 5, hdfProxy);

	WellboreFrameRepresentation* w1i1RegularFrameRep = pck->createWellboreFrameRepresentation(wellbore1Interp1, "a54b8399-d3ba-4d4b-b215-8d4f8f537e66", "Wellbore1 Interp1 Regular FrameRep", w1i1TrajRep);
	w1i1RegularFrameRep->setMdValues(0, 200, 6);

	PropertyKind * unitNumberPropType = pck->createPropertyKind("", "Unit number", "urn:resqml:geosiris.com:testingAPI", gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__discrete);

	DiscreteProperty* discreteProp = pck->createDiscreteProperty(w1i1FrameRep,"","Wellbore1 Interp1 FrameRep IntervalIndex", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__intervals, unitNumberPropType);
	long unitNumbers[4];
	unitNumbers[0] = 0; 
	unitNumbers[1] = 1; 
	unitNumbers[2] = 2;
	unitNumbers[3] = 3;
	discreteProp->pushBackLongHdf5Array1dOfValues(unitNumbers, 4, hdfProxy, -1);
	if (witsmlLog)
		w1i1FrameRep->setWitsmlLog(witsmlLog);
}

void serializeStratigraphicModel(common::EpcDocument * pck, AbstractHdfProxy* hdfProxy)
{
	witsml1_4_1_1::FormationMarker* witsmlFormationMarker0 = NULL;
	witsml1_4_1_1::FormationMarker* witsmlFormationMarker1 = NULL;

	OrganizationFeature* stratiModelFeature = pck->createStratigraphicModel("", "stratiModel");
	StratigraphicOccurrenceInterpretation* stratiOccurence = pck->createStratigraphicOccurrenceInterpretationInApparentDepth(stratiModelFeature, "", "stratiModel Interp");
	
	// WellboreFeature marker frame
	WellboreMarkerFrameRepresentation* wmf = pck->createWellboreMarkerFrameRepresentation(wellbore1Interp1, "", "Wellbore Marker Frame", w1i1TrajRep);
	double markerMdValues[2] = {350, 550};
	wmf->setMdValues(markerMdValues, 2, hdfProxy);
	WellboreMarker* marker0 = wmf->pushBackNewWellboreMarker("", "", gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__horizon);
	marker0->setBoundaryFeatureInterpretation(horizon1Interp1);
	WellboreMarker* marker1 = wmf->pushBackNewWellboreMarker("", "testing Fault", gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__fault);
	marker1->setBoundaryFeatureInterpretation(fault1Interp1);

	// WITSML MARKER
	witsmlFormationMarker0 = witsmlWellbore->createFormationMarker("", "marker0", 0, gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom__m, 350);
	witsmlFormationMarker1 = witsmlWellbore->createFormationMarker("", "marker1", 0, gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom__m, 550);

	if (witsmlFormationMarker0)
		wmf->setWitsmlFormationMarker(0, witsmlFormationMarker0);
	if (witsmlFormationMarker1)
		wmf->setWitsmlFormationMarker(1, witsmlFormationMarker1);
}

void serializeBoundaries(common::EpcDocument * pck, AbstractHdfProxy* hdfProxy)
{
	// Seismic Lattice
    SeismicLatticeFeature* seismicLattice = pck->createSeismicLattice("", "Seismic lattice", 2, 2, 150, 152, 4, 2);
    GenericFeatureInterpretation* seismicLatticeInterp = pck->createGenericFeatureInterpretation(seismicLattice, "", "Seismic lattice Interp");
    Grid2dRepresentation* seismicLatticeRep = pck->createGrid2dRepresentation(seismicLatticeInterp, local3dCrs, "", "Seismic lattice Rep");
    seismicLatticeRep->setGeometryAsArray2dOfLatticePoints3d(4,2,0,0,0,1,0,0,0,1,0,250,200);
	
    // Seismic Line Set
    SeismicLineSetFeature* seismicLineSet = pck->createSeismicLineSet("", "Seismic line Set");

    // Seismic Line
    SeismicLineFeature* seismicLine = pck->createSeismicLine("", "Seismic line", 1, 0, 5);
    seismicLine->setSeismicLineSet(seismicLineSet);
    GenericFeatureInterpretation* seismicLineInterp = pck->createGenericFeatureInterpretation(seismicLine, "", "Seismic line Interp");
    PolylineRepresentation* seismicLineRep = pck->createPolylineRepresentation(seismicLineInterp, local3dCrs, "", "Seismic line Rep");
    double seismicLinePoints [15] = {0, 100, 0, 150, 110, 0, 300, 120, 0, 450, 130, 0, 600, 140, 0};
    seismicLineRep->setGeometry(seismicLinePoints, 5, hdfProxy);

    // Features
	//BoundaryFeature* bf = pck->createBoundaryFeature("", "testingBoundaryFeature");
    horizon1 = pck->createHorizon("", "Horizon1");
    horizon2 = pck->createHorizon("", "Horizon2");
    fault1 = pck->createFault("", "Fault1");
    fault1->setMetadata("1424bcc2-3d9d-4f30-b1f9-69dcb897e33b", "", "philippe", 148526020, "philippe", "", 148526100, "F2I", "");

    // Interpretations
	//BoundaryFeatureInterpretation* bfi = pck->createBoundaryFeatureInterpretation(bf, "", "testingBoundaryFeatureInterp");
    horizon1Interp1 = pck->createHorizonInterpretation(horizon1, "", "Horizon1 Interp1");
    horizon2Interp1 = pck->createHorizonInterpretation(horizon2, "", "Horizon2 Interp1");
    fault1Interp1 = pck->createFaultInterpretation(fault1, "", "Fault1 Interp1");

    //**************
    // Horizon Representations
    //**************
    PolylineRepresentation* h1i1SinglePolylineRep = pck->createPolylineRepresentation(horizon1Interp1, local3dCrs, "", "Horizon1 Interp1 SinglePolylineRep");
    double h1i1SinglePolylineRepPoints [12] = {0, 100, 300, 150, 110, 300, 450, 130, 350, 600, 140, 350};
    h1i1SinglePolylineRep->setGeometry(h1i1SinglePolylineRepPoints, 4, hdfProxy);
    double seismicLineAbscissa [4] = {0.0, 1.0, 3.0, 4.0};
    //h1i1SinglePolylineRep->pushBackSeismic2dCoordinatesPatch(seismicLineAbscissa, 4, seismicLineRep, hdfProxy);

#if defined(OFFICIAL)
    h1i1SingleGrid2dRep = pck->createGrid2dRepresentation(horizon1Interp1, local3dCrs, "", "Horizon1 Interp1 Grid2dRep");
    double zValues [8] = {300, 300, 350, 350, 300, 300, 350, 350};
    h1i1SingleGrid2dRep->setGeometryAsArray2dOfExplicitZ(zValues, 4, 2, hdfProxy, seismicLatticeRep);
#else
    h1i1SingleGrid2dRep = pck->createGrid2dRepresentation(horizon1Interp1, localTime3dCrs, "", "Horizon1 Interp1 Grid2dRep");
    double zValues [8] = {300, 300, 350, 350, 300, 300, 350, 350};
    h1i1SingleGrid2dRep->setGeometryAsArray2dOfExplicitZ(zValues, 4, 2, hdfProxy, seismicLatticeRep);
#endif

    PointSetRepresentation* h1i1PointSetRep = pck->createPointSetRepresentation(horizon1Interp1, local3dCrs, "", "Horizon1 Interp1 PointSetRep");
    double pointCoords [18] = {10,70,301, 11,21,299, 150,30,301, 400,0,351, 450,75,340, 475,100,350};
    h1i1PointSetRep->pushBackGeometryPatch(6, pointCoords, hdfProxy);

    // Horizon 1 triangulated representation
    h1i1triRep = pck->createTriangulatedSetRepresentation(horizon1Interp1, local3dCrs,
        "",
        "Horizon1 Interp1 TriRep");
    // Patch 0
    double explicitPointsHor1Patch0[15] = {	250, 0, 300, 250, 100, 300, 250, 200, 300, 0,   0, 300, 0,   200, 300};
    unsigned int triangleNodeIndexHorPatch0[9] = {0,1,3, 1,4,3, 1,2,4};
    h1i1triRep->pushBackTrianglePatch(5, explicitPointsHor1Patch0, 3, triangleNodeIndexHorPatch0, hdfProxy);
    // Patch 1
    double explicitPointsHor1Patch1[15] = { 300, 0, 350, 300, 100, 350, 300, 200, 350, 700, 0, 350, 700, 200, 350};
    unsigned int triangleNodeIndexHorPatch1[9] = {5,6,8, 6,9,8, 6,7,9};
    h1i1triRep->pushBackTrianglePatch(5, explicitPointsHor1Patch1, 3, triangleNodeIndexHorPatch1, hdfProxy);

    // Horizon 2 triangulated representation
    h2i1triRep = pck->createTriangulatedSetRepresentation(horizon2Interp1, local3dCrs,
        "",
        "Horizon2 Interp1 TriRep");
    // Patch 0
    double explicitPointsHor2Patch0[30] = {	450, 0, 500, 450, 100, 500, 450, 200, 500, 0,   0, 500, 0,   200, 500};
    h2i1triRep->pushBackTrianglePatch(5, explicitPointsHor2Patch0, 3, triangleNodeIndexHorPatch0, hdfProxy);
    // Patch 1
    double explicitPointsHor2Patch1[30] = {500, 0, 550, 500, 100, 550, 500, 200, 550, 700, 0, 550, 700, 200, 550};
    h2i1triRep->pushBackTrianglePatch(5, explicitPointsHor2Patch1, 3, triangleNodeIndexHorPatch1, hdfProxy);

    //**************
    // Fault Representations
    //**************

    // Single patch triangulated representation
    f1i1triRepSinglePatch = pck->createTriangulatedSetRepresentation(fault1Interp1, local3dCrs,
        "",
        "Fault1 Interp1 TriRep Single Patch");
    //hsize_t dimExplicitPointsFault1 [1] = {6};
    double explicitPointsFault1[54] = {	150, 0, 200, 150, 100, 200, 150, 200, 200,
                                        250, 0, 300, 250, 100, 300, 250, 200, 300,
                                        300, 0, 350, 300, 100, 350, 300, 200, 350,
                                        450, 0, 500, 450, 100, 500, 450, 200, 500,
                                        500, 0, 550, 500, 100, 550 ,500, 200, 550,
                                        600, 0, 650, 600, 100, 650, 600, 200, 650};
    unsigned int triangleNodeIndexFault[60] = {0,4,3, 0,1,4, 1,2,4, 2,5,4,
        3,7,6, 3,4,7, 4,5,7, 5,8,7,
        6,10,9, 6,7,10, 7,8,10, 8,11,10,
        9,13,12, 9,10,13, 10,11,13, 11,14,13,
        12,16,15, 12,13,16, 13,14,16, 14,17,16};
    f1i1triRepSinglePatch->pushBackTrianglePatch(18, explicitPointsFault1, 20, triangleNodeIndexFault, hdfProxy);

    // multi patch triangulated representation
    f1i1triRep = pck->createTriangulatedSetRepresentation(fault1Interp1, local3dCrs,
        "",
        "Fault1 Interp1 TriRep");
    // Patch 0
    double explicitPointsFault1Patch0[18] = {150, 0, 200, 150, 100, 200, 150, 200, 200,
                                             250, 0, 300, 250, 100, 300, 250, 200, 300};
    unsigned int triangleNodeIndexFaultPatch0[12] = {0,4,3, 0,1,4, 1,2,4, 2,5,4};
    f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch0, 4, triangleNodeIndexFaultPatch0, hdfProxy);
    // Patch 1
    double explicitPointsFault1Patch1[18] = {250, 0, 300, 250, 100, 300, 250, 200, 300,
                                             300, 0, 350, 300, 100, 350, 300, 200, 350};
    unsigned int triangleNodeIndexFaultPatch1[12] = {6,10,9, 6,7,10, 7,8,10, 8,11,10};
    f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch1, 4, triangleNodeIndexFaultPatch1, hdfProxy);
    // Patch 2
    double explicitPointsFault1Patch2[18] = {300, 0, 350, 300, 100, 350, 300, 200, 350,
                                             450, 0, 500, 450, 100, 500, 450, 200, 500};
    unsigned int triangleNodeIndexFaultPatch2[12] = {12,16,15, 12,13,16, 13,14,16, 14,17,16};
    f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch2, 4, triangleNodeIndexFaultPatch2, hdfProxy);
    // Patch 3
    double explicitPointsFault1Patch3[18] = {450, 0, 500, 450, 100, 500, 450, 200, 500,
                                             500, 0, 550, 500, 100, 550 ,500, 200, 550};
    unsigned int triangleNodeIndexFaultPatch3[12] = {18,22,21, 18,19,22, 19,20,22, 20,23,22};
    f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch3, 4, triangleNodeIndexFaultPatch3, hdfProxy);
    // Patch 4
    double explicitPointsFault1Patch4[18] = {500, 0, 550, 500, 100, 550 ,500, 200, 550,
                                             600, 0, 650, 600, 100, 650, 600, 200, 650};
    unsigned int triangleNodeIndexFaultPatch4[12] = {24,28,27, 24,25,28, 25,26,28, 26,29,28};
    f1i1triRep->pushBackTrianglePatch(6, explicitPointsFault1Patch4, 4, triangleNodeIndexFaultPatch4, hdfProxy);

    // Fault polyline rep
    f1i1PolyLineRep = pck->createPolylineSetRepresentation(
        fault1Interp1, local3dCrs,
        "",
        "Fault1 Interp1 PolylineRep");
    unsigned int numNodesPerPolylinePerPatch[2] = {3, 2};
    double polylinePoints[15] = {150, 0, 200, 300, 0, 350, 450, 0, 500, 150, 200, 200, 450, 200, 500};
    f1i1PolyLineRep->pushBackGeometryPatch(numNodesPerPolylinePerPatch, polylinePoints, 2, false, hdfProxy);
    double inlines[5] = {0, 1, 2, 3, 4};
    double crosslines[5] = {10, 11, 12, 13, 14};
    //f1i1PolyLineRep->pushBackSeismic3dCoordinatesPatch(inlines, crosslines, 5, seismicLatticeRep, hdfProxy);

#if !defined(OFFICIAL)
    //**************
    // Properties
    //**************
    PropertyKind * propType1 = pck->createPropertyKind("", "propType1", "urn:resqml:f2i.com:testingAPI", gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__continuous);
	ContinuousProperty* contProp1 = pck->createContinuousProperty(h1i1SingleGrid2dRep, "", "Horizon1 Interp1 Grid2dRep Prop1", 2,
        gsoap_resqml2_0_1::resqml2__IndexableElements__nodes, gsoap_resqml2_0_1::resqml2__ResqmlUom__m, propType1);
    double prop1Values[16] = {301,302, 301,302, 351,352, 351,352, 301,302, 301,302, 351,352, 351,352};
    contProp1->pushBackDoubleHdf5Array1dOfValues(prop1Values, 8, hdfProxy);

	PropertyKind * propType2 = pck->createPropertyKind("", "propType2", "urn:resqml:f2i.com:testingAPI", gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, propType1);
	ContinuousProperty* contProp2 = pck->createContinuousProperty(h1i1SingleGrid2dRep, "", "Horizon1 Interp1 Grid2dRep Prop2", 1,
        gsoap_resqml2_0_1::resqml2__IndexableElements__nodes, gsoap_resqml2_0_1::resqml2__ResqmlUom__ft, propType2);
    double prop2Values[8] = {302, 302, 352, 352, 302, 302, 352, 352};
    contProp2->pushBackDoubleHdf5Array1dOfValues(prop2Values, 8, hdfProxy);
#endif
}

void serializeGrid(common::EpcDocument * pck, AbstractHdfProxy* hdfProxy)
{
	OrganizationFeature * earthModel = pck->createEarthModel("", "Grid");
	EarthModelInterpretation * earthModelInterp = pck->createEarthModelInterpretation(earthModel, "", "Grid interp");

	// ONE SUGAR
	IjkGridExplicitRepresentation* singleCellIjkgrid = pck->createIjkGridExplicitRepresentation(local3dCrs, "", "One unfaulted sugar cube", 1, 1, 1);
	double singleCellIjkgridNodes[24] = { 0, 0, 300, 700, 0, 350, 0, 150, 300, 700, 150, 350,
		0, 0, 500, 700, 0, 550, 0, 150, 500, 700, 150, 550 };
	singleCellIjkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, singleCellIjkgridNodes, hdfProxy);

	// TWO SUGARS
	IjkGridExplicitRepresentation* ijkgrid = pck->createIjkGridExplicitRepresentation(local3dCrs, "", "Two faulted sugar cubes", 2, 1, 1);
	double nodes[48] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350,
		0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };
	unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
	unsigned int splitCoordinateLineColumns[2] = { 1, 1 };
	ijkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, nodes, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	//**************
	// Subrepresentations
	//**************
	if (fault1Interp1 != nullptr)
	{
		SubRepresentation * faultSubRep = pck->createSubRepresentation(fault1Interp1, "", "Fault Subrep In Grid", ijkgrid);
		unsigned int faultPillar[2] = { 1, 4 };
		faultSubRep->pushBackSubRepresentationPatch(gsoap_resqml2_0_1::resqml2__IndexableElements__pillars, 2, faultPillar, hdfProxy);
	}

	//**************
	// Grid Connection
	//**************
	if (earthModelInterp != nullptr)
	{
		GridConnectionSetRepresentation * gridConnSet = pck->createGridConnectionSetRepresentation(earthModelInterp, "", "GridConnectionSetRepresentation", ijkgrid);
		ULONG64 cellConn[2] = { 0, 1 };
		gridConnSet->setCellIndexPairs(1, cellConn, 9999, hdfProxy);
		unsigned int localFacePerCellIndexPairs[2] = { 3, 5 };
		gridConnSet->setLocalFacePerCellIndexPairs(1, localFacePerCellIndexPairs, 9999, hdfProxy);
		//unsigned int faultIndices = 0;
		//gridConnSet->setConnectionFaultNames(&faultIndices, 1, 9999, hdfProxy);
	}

	//**************
	// Properties
	//**************
	PropertyKind * propType1 = pck->createPropertyKind("", "cellIndex", "urn:resqml:f2i-consulting.com", gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__discrete);
	DiscreteProperty* discreteProp1 = pck->createDiscreteProperty(ijkgrid, "ee0857fe-23ad-4dd9-8300-21fa2e9fb572", "Two faulted sugar cubes cellIndex", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, propType1);
	long prop1Values[2] = {0,1};
	//discreteProp1->pushBackRefToExistingDataset(hdfProxy, true);
	discreteProp1->pushBackLongHdf5Array3dOfValues(prop1Values, 2, 1, 1, hdfProxy, -1);

	//**************
	// Time Series
	//**************
	TimeSeries * timeSeries = pck->createTimeSeries("", "Testing time series");
	timeSeries->pushBackTimestamp(1378217895);
	timeSeries->pushBackTimestamp(1409753895);
	timeSeries->pushBackTimestamp(1441289895);
	ContinuousProperty* continuousPropTime0 = pck->createContinuousProperty(ijkgrid, "", "Time 0", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlUom__m, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	continuousPropTime0->setTimeIndex(0, timeSeries);
	double valuesTime0[2] = {0,1};
	continuousPropTime0->pushBackDoubleHdf5Array3dOfValues(valuesTime0, 2, 1, 1, hdfProxy);
	ContinuousProperty* continuousPropTime1 = pck->createContinuousProperty(ijkgrid, "", "Time 1", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlUom__m, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	continuousPropTime1->setTimeIndex(1, timeSeries);
	double valuesTime1[2] = {2,3};
	continuousPropTime1->pushBackDoubleHdf5Array3dOfValues(valuesTime1, 2, 1, 1, hdfProxy);
	ContinuousProperty* continuousPropTime2 = pck->createContinuousProperty(ijkgrid, "", "Time 2", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlUom__m, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	continuousPropTime2->setTimeIndex(2, timeSeries);
	double valuesTime2[2] = {3,4};
	continuousPropTime2->pushBackDoubleHdf5Array3dOfValues(valuesTime2, 2, 1, 1, hdfProxy);

	ContinuousPropertySeries* continuousPropertySeries = pck->createContinuousPropertySeries(
		ijkgrid,
		"", "Testing continuous property series",
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length,
		timeSeries);
	double valuesTime[6] = {0,1,2,3,3,4};
	continuousPropertySeries->pushBackDoubleHdf5Array1dOfValues(valuesTime, 6, hdfProxy);

	//**************
	// LGR
	//**************
	
	IjkGridExplicitRepresentation* lgrGrid = pck->createIjkGridExplicitRepresentation(local3dCrs, "", "LGR", 2, 1, 3);
	lgrGrid->setParentWindow(
		0, 2, 1,
		0, 1, 1,
		0, 3, 1,
		ijkgrid);
	
#if !defined(OFFICIAL)
	// Partial transfer
	UnstructuredGridRepresentation* partialGrid = pck->createPartialUnstructuredGridRepresentation("27290b9a-ff46-47b7-befd-cf6b7836045c", "Partial Grid");
	ContinuousProperty* continuousProp1 = pck->createContinuousProperty(partialGrid, "cd627946-0f89-48fa-b99c-bdb35d8ac4aa", "Testing partial property", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlUom__m, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	double continuousProp1Values[6] = {0,1,2,3,4,5};
	continuousProp1->pushBackDoubleHdf5Array1dOfValues(continuousProp1Values, 6, hdfProxy);

	// Tetra grid
	UnstructuredGridRepresentation* tetraGrid = pck->createUnstructuredGridRepresentation(local3dCrs, "", "One tetrahedron grid", 1);
	double tetraGridPoints[12] = {0,0,300, 375,0,300, 0,150,300, 0,0,500};
	unsigned int faceIndicesPerCell[4] = {0,1,2,3};
	unsigned int nodeIndicesPerCell[12] = {0,1,2, 1,2,3, 0,1,3, 0,2,3};
	tetraGrid->setTetrahedraOnlyGeometry(true, tetraGridPoints, 4, 4, hdfProxy, faceIndicesPerCell, nodeIndicesPerCell);
#endif
}

void serializeStructualModel(common::EpcDocument & pck, AbstractHdfProxy* hdfProxy)
{
    // =========================================================================
    // =========================================================================
    // Organization features
    OrganizationFeature * structOrg1 = pck.createStructuralModel("", "StructuralOrg1");
	structOrg1->setOriginator("Geosiris");

    // =========================================================================
    // =========================================================================
    // Organization interpretations
    StructuralOrganizationInterpretation * structuralOrganizationInterpretation = pck.createStructuralOrganizationInterpretationInApparentDepth(structOrg1, "", "StructuralOrg1 Interp1");
	structuralOrganizationInterpretation->setOriginator("Geosiris");
	structuralOrganizationInterpretation->pushBackFaultInterpretation(fault1Interp1);
    structuralOrganizationInterpretation->pushBackHorizonInterpretation(horizon1Interp1, 1);
    structuralOrganizationInterpretation->pushBackHorizonInterpretation(horizon2Interp1, 1);

    // =========================================================================
    // =========================================================================
    // EarthModel
    OrganizationFeature * earthModelOrg = pck.createEarthModel("", "EarthModelOrg");
    earthModelOrg->setOriginator("Geosiris");
	EarthModelInterpretation * earthModel = pck.createEarthModelInterpretation(earthModelOrg,"", "EarthModel");
    earthModel->setOriginator("Geosiris");
    earthModel->setStructuralOrganizationInterpretation(structuralOrganizationInterpretation);

    // =========================================================================
    // =========================================================================
    // Binary contact interpretation

    // Contact 0: fault1Interp1 HANGING_WALL_SIDE SPLITS horizon1Interp1 BOTH_SIDES
    structuralOrganizationInterpretation->pushBackBinaryContact(gsoap_resqml2_0_1::resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary, fault1Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__hanging_x0020wall,
            gsoap_resqml2_0_1::resqml2__ContactVerb__splits,
            horizon1Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__both);

   // Contact 1: fault1Interp1 FOOT_WALL_SIDE SPLITS horizon2Interp1 BOTH_SIDES
   structuralOrganizationInterpretation->pushBackBinaryContact(gsoap_resqml2_0_1::resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary, fault1Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__footwall,
           gsoap_resqml2_0_1::resqml2__ContactVerb__splits,
           horizon1Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__both);

    // Contact 2: fault1Interp1 HANGING_WALL_SIDE SPLITS horizon1Interp1 BOTH_SIDES
    structuralOrganizationInterpretation->pushBackBinaryContact(gsoap_resqml2_0_1::resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary, fault1Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__hanging_x0020wall,
            gsoap_resqml2_0_1::resqml2__ContactVerb__splits,
            horizon2Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__both);

    // Contact 3: fault1Interp1 FOOT_WALL_SIDE SPLITS horizon1Interp1 BOTH_SIDES
    structuralOrganizationInterpretation->pushBackBinaryContact(gsoap_resqml2_0_1::resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary, fault1Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__footwall,
            gsoap_resqml2_0_1::resqml2__ContactVerb__splits,
            horizon2Interp1, gsoap_resqml2_0_1::resqml2__ContactSide__both);

    // =========================================================================
    // =========================================================================
    // SurfaceFramework
//    SurfaceFramework* structuralOrganizationInterpretationSurfaceFramework = pck.createSurfaceFramework(structuralOrganizationInterpretation, "", "StructuralOrg1 Interp1 Interp1 SurfFrmwk", true);
//    structuralOrganizationInterpretationSurfaceFramework->pushBackRepresentation(f1i1triRep);
//    structuralOrganizationInterpretationSurfaceFramework->pushBackRepresentation(h1i1triRep);
//    structuralOrganizationInterpretationSurfaceFramework->pushBackRepresentation(h2i1triRep);

    // Single Patch Fault 1
    SealedSurfaceFrameworkRepresentation* singlePatchFault1SealedSurfaceFramework = pck.createSealedSurfaceFrameworkRepresentation(structuralOrganizationInterpretation, "", "Single Patch Fault1 StructuralOrg1 Interp1 Interp1 SealedSurfFrmwk");
    singlePatchFault1SealedSurfaceFramework->setOriginator("Geosiris");
	f1i1triRepSinglePatch->pushBackIntoRepresentationSet(singlePatchFault1SealedSurfaceFramework);
    h1i1triRep->pushBackIntoRepresentationSet(singlePatchFault1SealedSurfaceFramework);
    h2i1triRep->pushBackIntoRepresentationSet(singlePatchFault1SealedSurfaceFramework);

    // Multipatch Fault 1
    SealedSurfaceFrameworkRepresentation* sealedSurfaceFramework = pck.createSealedSurfaceFrameworkRepresentation(structuralOrganizationInterpretation, "", "StructuralOrg1 Interp1 Interp1 SealedSurfFrmwk");
    sealedSurfaceFramework->setOriginator("Geosiris");
	f1i1triRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);
    h1i1triRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);
    h2i1triRep->pushBackIntoRepresentationSet(sealedSurfaceFramework);

    // =========================================================================
    // =========================================================================
    // Binary contact representations

    // ===================================
    // Single Patch Fault 1 Representation

    // Contact 0
    // nbPatch * nbIdenticalNodes = 9
    int contactIdenticalNodes[9] = {
        0,0,0,
        1,1,1,
        2,2,2
    };
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    singlePatchFault1SealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 0 Patch 0
	int indexSetContact0Patch0[3] = {3, 4, 5};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
                0,
                indexSetContact0Patch0,
                3,
                f1i1triRepSinglePatch, hdfProxy);

    // Contact 0 Patch 1
	int indexSetContact0Patch1[3] = {0, 1, 2};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            0,
            indexSetContact0Patch1,
            3,
            h1i1triRep, hdfProxy);

    // Contact 0 Patch 2
	int indexSetContact0Patch2[3] = {3, 4, 5};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            0,
            indexSetContact0Patch2,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // Contact 1
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    singlePatchFault1SealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 1 Patch 0
	int indexSetContact1Patch0[3] = {6, 7, 8};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            1,
            indexSetContact1Patch0,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // Contact 1 Patch 1
	int indexSetContact1Patch1[3] = {5, 6, 7};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            1,
            indexSetContact1Patch1,
            3,
            h1i1triRep, hdfProxy);

    // Contact 1 Patch 2
	int indexSetContact1Patch2[3] = {6, 7, 8};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            1,
            indexSetContact1Patch2,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // Contact 2
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    singlePatchFault1SealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 2 Patch 0
	int indexSetContact2Patch0[3] = {9, 10, 11};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            2,
            indexSetContact2Patch0,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // Contact 2 Patch 1
	int indexSetContact2Patch1[3] = {0, 1, 2};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            2,
            indexSetContact2Patch1,
            3,
            h2i1triRep, hdfProxy);

    // Contact 2 Patch 2
	int indexSetContact2Patch2[3] = {9, 10, 11};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            2,
            indexSetContact2Patch2,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // Contact 3
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    singlePatchFault1SealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 3 Patch 0
	int indexSetContact3Patch0[3] = {12, 13, 14};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            3,
            indexSetContact3Patch0,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // Contact 3 Patch 1
	int indexSetContact3Patch1[3] = {5, 6, 7};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            3,
            indexSetContact3Patch1,
            3,
            h2i1triRep, hdfProxy);

    // Contact 3 Patch 2
	int indexSetContact3Patch2[3] = {12, 13, 14};
    singlePatchFault1SealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            3,
            indexSetContact3Patch2,
            3,
            f1i1triRepSinglePatch, hdfProxy);

    // ================================
    // Multiatch Fault 1 Representation

    // Contact 0
    // nbPatch * nbIdenticalNodes = 9
//    int contactIdenticalNodes[9] = {
//        0,0,0,
//        1,1,1,
//        2,2,2
//    };
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 0 Patch 0
    //int * indexSetContact0Patch0 = new int[3];
    indexSetContact0Patch0[0] = 3;
    indexSetContact0Patch0[1] = 4;
    indexSetContact0Patch0[2] = 5;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
                0,
                indexSetContact0Patch0,
                3,
                f1i1triRep, hdfProxy);

    // Contact 0 Patch 1
    //int * indexSetContact0Patch1 = new int[3];
    indexSetContact0Patch1[0] = 0;
    indexSetContact0Patch1[1] = 1;
    indexSetContact0Patch1[2] = 2;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            0,
            indexSetContact0Patch1,
            3,
            h1i1triRep, hdfProxy);

    // Contact 0 Patch 2
    //int * indexSetContact0Patch2 = new int[3];
    indexSetContact0Patch2[0] = 6;
    indexSetContact0Patch2[1] = 7;
    indexSetContact0Patch2[2] = 8;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            0,
            indexSetContact0Patch2,
            3,
            f1i1triRep, hdfProxy);

    // Contact 1
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 1 Patch 0
    //int * indexSetContact1Patch0 = new int[3];
    indexSetContact1Patch0[0] = 9;
    indexSetContact1Patch0[1] = 10;
    indexSetContact1Patch0[2] = 11;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            1,
            indexSetContact1Patch0,
            3,
            f1i1triRep, hdfProxy);

    // Contact 1 Patch 1
    //int * indexSetContact1Patch1 = new int[3];
    indexSetContact1Patch1[0] = 5;
    indexSetContact1Patch1[1] = 6;
    indexSetContact1Patch1[2] = 7;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            1,
            indexSetContact1Patch1,
            3,
            h1i1triRep, hdfProxy);

    // Contact 1 Patch 2
    //int * indexSetContact1Patch2 = new int[3];
    indexSetContact1Patch2[0] = 12;
    indexSetContact1Patch2[1] = 13;
    indexSetContact1Patch2[2] = 14;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            1,
            indexSetContact1Patch2,
            3,
            f1i1triRep, hdfProxy);

    // Contact 2
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 2 Patch 0
    //int * indexSetContact2Patch0 = new int[3];
    indexSetContact2Patch0[0] = 15;
    indexSetContact2Patch0[1] = 16;
    indexSetContact2Patch0[2] = 17;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            2,
            indexSetContact2Patch0,
            3,
            f1i1triRep, hdfProxy);

    // Contact 2 Patch 1
    //int * indexSetContact2Patch1 = new int[3];
    indexSetContact2Patch1[0] = 0;
    indexSetContact2Patch1[1] = 1;
    indexSetContact2Patch1[2] = 2;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            2,
            indexSetContact2Patch1,
            3,
            h2i1triRep, hdfProxy);

    // Contact 2 Patch 2
    //int * indexSetContact2Patch2 = new int[3];
    indexSetContact2Patch2[0] = 18;
    indexSetContact2Patch2[1] = 19;
    indexSetContact2Patch2[2] = 20;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            2,
            indexSetContact2Patch2,
            3,
            f1i1triRep, hdfProxy);

    // Contact 3
    //sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml__IdentityKind__COLOCATION, 3, 3, contactIdenticalNodes, hdfProxy);
    sealedSurfaceFramework->pushBackSealedContactRepresentation(gsoap_resqml2_0_1::resqml2__IdentityKind__colocation);

    // Contact 3 Patch 0
    //int * indexSetContact3Patch0 = new int[3];
    indexSetContact3Patch0[0] = 21;
    indexSetContact3Patch0[1] = 22;
    indexSetContact3Patch0[2] = 23;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            3,
            indexSetContact3Patch0,
            3,
            f1i1triRep, hdfProxy);

    // Contact 3 Patch 1
    //int * indexSetContact3Patch1 = new int[3];
    indexSetContact3Patch1[0] = 5;
    indexSetContact3Patch1[1] = 6;
    indexSetContact3Patch1[2] = 7;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            3,
            indexSetContact3Patch1,
            3,
            h2i1triRep, hdfProxy);

    // Contact 3 Patch 2
    //int * indexSetContact3Patch2 = new int[3];
    indexSetContact3Patch2[0] = 24;
    indexSetContact3Patch2[1] = 25;
    indexSetContact3Patch2[2] = 26;
    sealedSurfaceFramework->pushBackContactPatchInSealedContactRepresentation(
            3,
            indexSetContact3Patch2,
            3,
            f1i1triRep, hdfProxy);

    // =========================================================================
    // =========================================================================
    // Contact identities

    // ====================
    // Single Patch Fault 1

    // Contact 0 and 1 was previously colocated
	int contact_0_1_contactRepresentations[2] = {0, 1};
//    int contact_0_1_IdenticalNodes[6] =
//    {
//        0, 0,
//        1, 1,
//        2, 2,
//    };
//    sealedSurfaceFramework->pushBackContactIdentity(
//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
//            2, contact_0_1_contactRepresentations,
//            3, contact_0_1_IdenticalNodes, hdfProxy);
    singlePatchFault1SealedSurfaceFramework->pushBackContactIdentity(
            gsoap_resqml2_0_1::resqml2__IdentityKind__previous_x0020colocation,
            2, contact_0_1_contactRepresentations,
            hdfProxy);

    // Contact 2 and 3 was previously colocated
	int contact_2_3_contactRepresentations[2] = {2, 3};
//    int contact_2_3_IdenticalNodes[6] =
//    {
//        0, 0,
//        1, 1,
//        2, 2,
//    };
//    sealedSurfaceFramework->pushBackContactIdentity(
//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
//            2, contact_2_3_contactRepresentations,
//            3, contact_2_3_IdenticalNodes, hdfProxy);
    singlePatchFault1SealedSurfaceFramework->pushBackContactIdentity(
            gsoap_resqml2_0_1::resqml2__IdentityKind__previous_x0020colocation,
            2, contact_2_3_contactRepresentations,
            hdfProxy);

    // ==================
    // Multipatch Fault 1

    // Contact 0 and 1 was previously colocated
    //int * contact_0_1_contactRepresentations = new int[2];
    //contact_0_1_contactRepresentations[0] = 0;
    //contact_0_1_contactRepresentations[1] = 1;
//    int contact_0_1_IdenticalNodes[6] =
//    {
//        0, 0,
//        1, 1,
//        2, 2,
//    };
//    sealedSurfaceFramework->pushBackContactIdentity(
//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
//            2, contact_0_1_contactRepresentations,
//            3, contact_0_1_IdenticalNodes, hdfProxy);
    sealedSurfaceFramework->pushBackContactIdentity(
            gsoap_resqml2_0_1::resqml2__IdentityKind__previous_x0020colocation,
            2, contact_0_1_contactRepresentations,
            hdfProxy);

    // Contact 2 and 3 was previously colocated
    //int * contact_2_3_contactRepresentations = new int[2];
    //contact_2_3_contactRepresentations[0] = 2;
    //contact_2_3_contactRepresentations[1] = 3;
//    int contact_2_3_IdenticalNodes[6] =
//    {
//        0, 0,
//        1, 1,
//        2, 2,
//    };
//    sealedSurfaceFramework->pushBackContactIdentity(
//            gsoap_resqml2_0_1::resqml__IdentityKind__PREVIOUS_USCORECOLOCATION,
//            2, contact_2_3_contactRepresentations,
//            3, contact_2_3_IdenticalNodes, hdfProxy);
    sealedSurfaceFramework->pushBackContactIdentity(
            gsoap_resqml2_0_1::resqml2__IdentityKind__previous_x0020colocation,
            2, contact_2_3_contactRepresentations,
            hdfProxy);
}

void serializeActivities(common::EpcDocument * epcDoc)
{
	/********************
	* Activity Template
	********************/

	ActivityTemplate* genericCreationActivityTemplate = epcDoc->createActivityTemplate("a41c63bf-78cb-454b-8018-c9df060c5cf3", "GenericCreationActivity");
	genericCreationActivityTemplate->pushBackParameter("CreationInput", true, false, 0, -1);
	genericCreationActivityTemplate->pushBackParameter("CreationOutput", false, true, 1, -1);

	/********************
	* Activities
	********************/
	Activity* pickingActivity = epcDoc->createActivity(genericCreationActivityTemplate, "", "Seismic picking");
	pickingActivity->pushBackParameter("CreationOutput", horizon1);
	pickingActivity->pushBackParameter("CreationOutput", horizon1Interp1);
	pickingActivity->pushBackParameter("CreationOutput", h1i1SingleGrid2dRep);
	pickingActivity->pushBackParameter("CreationOutput", fault1);
	pickingActivity->pushBackParameter("CreationOutput", fault1Interp1);
	pickingActivity->pushBackParameter("CreationOutput", f1i1PolyLineRep);
	
	Activity* h1triangulationActivity = epcDoc->createActivity(genericCreationActivityTemplate, "", "Triangulation");
	h1triangulationActivity->pushBackParameter("CreationInput", h1i1SingleGrid2dRep);
	h1triangulationActivity->pushBackParameter("CreationOutput", h1i1triRep);
	
	Activity* f1TriangulationActivity1 = epcDoc->createActivity(genericCreationActivityTemplate, "", "Triangulation");
	f1TriangulationActivity1->pushBackParameter("CreationInput", f1i1PolyLineRep);
	f1TriangulationActivity1->pushBackParameter("CreationOutput", f1i1triRepSinglePatch);
	
	Activity* f1TriangulationActivity2 = epcDoc->createActivity(genericCreationActivityTemplate, "", "Triangulation");
	f1TriangulationActivity2->pushBackParameter("CreationInput", f1i1PolyLineRep);
	f1TriangulationActivity2->pushBackParameter("CreationOutput", f1i1triRep);

}

void serializePropertyKindMappingFiles(common::EpcDocument * pck)
{

}

void deserializePropertyKindMappingFiles(common::EpcDocument * pck)
{
	PropertyKindMapper* ptMapper = pck->getPropertyKindMapper();

	cout << "Application property kind name for azimuth : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__azimuth, "Petrel") << endl;
	cout << "Application property kind name for azimuth : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__gamma_x0020ray_x0020API_x0020unit, "Petrel") << endl;
	cout << "Application property kind name for azimuth : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__gamma_x0020ray_x0020API_x0020unit, "Sismage") << endl;
	cout << "Application property kind name for dip : " << ptMapper->getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__dip, "myApplication") << endl;

	cout << "Standard property for Petrel \"Dip Azimuth\" : " << ptMapper->getResqmlStandardPropertyKindNameFromApplicationPropertyKindName("Dip Azimuth", "Petrel") << endl;
	cout << "Standard property for Application property Absolute temperature : " << ptMapper->getResqmlStandardPropertyKindNameFromApplicationPropertyKindName("Absolute temperature", "myApplication") << endl;

	cout << "Application property kind for unknown local property type uuid  : " << ptMapper->getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid("unknownUuid", "myApplication") << endl;
	cout << "Application property kind for local property type 959cf4e1-d485-5225-bbdb-f53c16cc0c3c (VShale) : " << ptMapper->getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid("959cf4e1-d485-5225-bbdb-f53c16cc0c3c", "Sismage") << endl;

	ptMapper->addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName("Elevation depth", "Petrel");
}

void deserializeActivity(AbstractObject* resqmlObject)
{
	if (resqmlObject->getActivitySet().size())
		cout << "Activities for object " << resqmlObject->getTitle() << endl;
	for (unsigned int i = 0; i < resqmlObject->getActivitySet().size(); ++i)
	{
		Activity* activity = resqmlObject->getActivitySet()[i];
		cout << "Activity : " << activity->getTitle() << endl;
		cout << "Activity Template : " << activity->getActivityTemplate()->getTitle() << endl;
		for (unsigned int j = 0; j < activity->getActivityTemplate()->getParameterCount(); ++j)
		{
			string paramTitle = activity->getActivityTemplate()->getParameterTitle(j);
			cout << "Parameter : " << paramTitle << endl;
			cout << "Parameter min occurs : " << activity->getActivityTemplate()->getParameterMinOccurences(paramTitle) << endl;
			cout << "Parameter max occurs : " << activity->getActivityTemplate()->getParameterMaxOccurences(paramTitle) << endl;
			cout << "Parameter is input : " << activity->getActivityTemplate()->getParameterIsInput(paramTitle) << endl;
			cout << "Parameter is output : " << activity->getActivityTemplate()->getParameterIsOutput(paramTitle) << endl;
			if (activity->getParameterCount(paramTitle) > 0)
			{
				if (activity->isAFloatingPointQuantityParameter(paramTitle) == true)
				{
					vector<double> vals = activity->getFloatingPointQuantityParameterValue(paramTitle);
					for (unsigned int k = 0; k < vals.size(); ++k)
					{
						cout << "Double value : " << vals[k] << endl;
					}
				}
				else if (activity->isAnIntegerQuantityParameter(paramTitle) == true)
				{
					vector<LONG64> vals = activity->getIntegerQuantityParameterValue(paramTitle);
					for (unsigned int k = 0; k < vals.size(); ++k)
					{
						cout << "Integer value : " << vals[k] << endl;
					}
				}
				else if (activity->isAStringParameter(paramTitle) == true)
				{
					vector<string> vals = activity->getStringParameterValue(paramTitle);
					for (unsigned int k = 0; k < vals.size(); ++k)
					{
						cout << "String value : " << vals[k] << endl;
					}
				}
				else if (activity->isAResqmlObjectParameter(paramTitle) == true)
				{
					vector<AbstractObject*> vals = activity->getResqmlObjectParameterValue(paramTitle);
					for (unsigned int k = 0; k < vals.size(); ++k)
					{
						cout << "Object title : " << vals[k] ->getTitle()<< endl;
					}
				}
				else
				{
					vector<unsigned int> paramIndex = activity->getParameterIndexOfTitle(paramTitle);
					for (unsigned int k = 0; k < paramIndex.size(); ++k)
					{
						if (activity->isAFloatingPointQuantityParameter(paramIndex[k]))
							cout << "Floating Point value : " << activity->getFloatingPointQuantityParameterValue(paramIndex[k]);
						else if (activity->isAnIntegerQuantityParameter(paramIndex[k]))
							cout << "Integer value : " << activity->getIntegerQuantityParameterValue(paramIndex[k]);
						else if (activity->isAStringParameter(paramIndex[k]))
							cout << "String value : " << activity->getStringParameterValue(paramIndex[k]);
						else if (activity->isAResqmlObjectParameter(paramIndex[k]))
							cout << "Object title : " << activity->getResqmlObjectParameterValue(paramIndex[k])->getTitle();
					}
				}
			}
			else
				cout << "No provided parameter in the activity." << endl;
		}
		cout << endl;
	}
}

void serialize(const string & filePath)
{
	common::EpcDocument pck(filePath, true);

	AbstractHdfProxy* hdfProxy = pck.createHdfProxy("", "Hdf Proxy", pck.getStorageDirectory(), pck.getName() + ".h5");
	
	//CRS
	local3dCrs = pck.createLocalDepth3dCrs("", "Default local CRS", .0, .0, .0, .0, gsoap_resqml2_0_1::eml__LengthUom__m, 23031, gsoap_resqml2_0_1::eml__LengthUom__m, "Unknown", false);
	localTime3dCrs = pck.createLocalTime3dCrs("", "Default local time CRS", 1.0, 0.1, 15, .0, gsoap_resqml2_0_1::eml__LengthUom__m, 23031, gsoap_resqml2_0_1::eml__TimeUom__s, gsoap_resqml2_0_1::eml__LengthUom__m, "Unknown", false); // CRS translation is just for testing;
#if !defined(OFFICIAL)
    witsmlCrs = pck.createCoordinateReferenceSystem("","witsmlCrs","EPSG", "5715", "", -1, -1, "");
#endif

	// Comment or uncomment below domains/lines you want wether to test or not
	serializeBoundaries(&pck, hdfProxy);
	serializeStructualModel(pck, hdfProxy);
	serializeGrid(&pck, hdfProxy);
#if !defined(OFFICIAL)
	serializeWells(&pck, hdfProxy);
	serializeStratigraphicModel(&pck, hdfProxy);
	serializeActivities(&pck);
#endif

	// Add an extended core property before to serialize
	pck.setExtendedCoreProperty("F2I-ExtendedCoreProp", "TestingVersion");

	pck.serialize();

	hdfProxy->close();

#if !defined(OFFICIAL)
	serializePropertyKindMappingFiles(&pck);
#endif
}

void showAllMetadata(AbstractResqmlDataObject * obj, const std::string & prefix = "")
{
	std::cout << prefix << "Title is : " << obj->getTitle() << std::endl;
	std::cout << prefix << "Guid is : " << obj->getUuid() << std::endl;
	if (obj->isPartial() == false)
	{
		for (unsigned int i = 0; i < obj->getAliasCount(); ++i)
			std::cout << prefix << "Alias is : " << obj->getAliasAuthorityAtIndex(i) << ":" << obj->getAliasTitleAtIndex(i) << std::endl;
		for (unsigned int i = 0; i < obj->getExtraMetadataCount(); ++i)
			std::cout << prefix << "Extrametadata is : " << obj->getExtraMetadataKeyAtIndex(i) << ":" << obj->getExtraMetadataStringValueAtIndex(i) << std::endl;
	}
	std::cout << prefix << "--------------------------------------------------" << std::endl;
}

void showAllProperties(AbstractRepresentation * rep)
{
	std::vector<AbstractValuesProperty*> propertyValuesSet = rep->getValuesPropertySet();
	if (propertyValuesSet.empty() == false)
		cout << "PROPERTIES" << std::endl;
	std::cout << "\t--------------------------------------------------" << std::endl;
	for (size_t propIndex = 0; propIndex < propertyValuesSet.size(); ++propIndex)
	{
		AbstractValuesProperty* propVal = propertyValuesSet[propIndex];
		showAllMetadata(propVal, "\t");

		std::cout << "\tProperty kind is : " << propVal->getPropertyKindAsString() << std::endl;
		if (propVal->isAssociatedToOneStandardEnergisticsPropertyKind() == true)
		{
			std::cout << "\tProperty kind is an Energistics one" << std::endl;
		}
		else
		{
			std::cout << "\tProperty kind is not an Energistics one" << std::endl;
			if (propVal->getLocalPropertyKind()->isParentAnEnergisticsPropertyKind() == true)
			{
				std::cout << "\t\tProperty kind parent is an Energistics one" << std::endl;
				std::cout << "\t\tProperty kind parent is : " << propVal->getLocalPropertyKind()->getParentAsString() << std::endl;
			}
			else
			{
				std::cout << "\t\tProperty kind parent is not an Energistics one" << std::endl;
				std::cout << "\t\tProperty kind parent is : " << propVal->getLocalPropertyKind()->getParentLocalPropertyKind()->getTitle() << std::endl;
			}
		}
		
		// Dimension
		unsigned int dimCount = propVal->getDimensionsCountOfPatch(0);
		std::cout << "\tDimension count is : " << dimCount << std::endl;
		for (unsigned int dimIndex = 0; dimIndex < dimCount; ++dimIndex)
		{
			std::cout << "\tValues count in dimension " << dimIndex << " is : " << propVal->getValuesCountOfDimensionOfPatch(dimIndex, 0) << std::endl;
		}
		unsigned int valueCount = propVal->getValuesCountOfPatch(0);
		std::cout << "\tValues count in all dimensions is : " << valueCount << std::endl;

		// Datatype
		std::cout << "\tDatatype is : " << propVal->getValuesHdfDatatype() << std::endl;
		bool isFloat = true;
		if (propVal->getValuesHdfDatatype() == 0)
		{
			cerr << "\tERROR !!!!! The hdf datatype is unknown" << endl;
			cout << "\tPress enter to continue..." << endl;
			cin.get();
		}
		else if (propVal->getValuesHdfDatatype() > 2)
		{
			isFloat = false;
			if (dynamic_cast<DiscreteProperty*>(propVal) == nullptr && dynamic_cast<CategoricalProperty*>(propVal) == nullptr)
			{
				cerr << "\tERROR !!!!! The continuous property is linked to an integer HDF5 dataset." << endl;
				cout << "\tTrying to convert.." << endl;
				double* values = new double[valueCount];
				static_cast<ContinuousProperty*>(propVal)->getDoubleValuesOfPatch(0, values);
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
				delete [] values;
				cout << "\tPress enter to continue..." << endl;
				cin.get();
			}
			else
			{
				long* values = new long[valueCount];
				propVal->getLongValuesOfPatch(0, values);
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
				delete [] values;
			}
		}
		else
		{
			if (dynamic_cast<ContinuousProperty*>(propVal) == nullptr)
			{
				cerr << "\tERROR !!!!! The discrete or categorical property is linked to a floating point HDF5 dataset." << endl;
				cout << "\tTrying to convert.." << endl;
				long* values = new long[valueCount];
				propVal->getLongValuesOfPatch(0, values);
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
				delete [] values;
				cout << "\tPress enter to continue..." << endl;
				cin.get();
			}
			else
			{
				double* values = new double[valueCount];
				static_cast<ContinuousProperty*>(propVal)->getDoubleValuesOfPatch(0, values);
				std::cout << "\tFirst value is " << values[0] << endl;
				std::cout << "\tSecond value is " << values[1] << endl;
				delete [] values;
			}
		}
	}
	std::cout << "\t--------------------------------------------------" << std::endl;
}

void deserializeStratiColumn(StratigraphicColumn * stratiColumn)
{
	showAllMetadata(stratiColumn);
	for (size_t i = 0; i < stratiColumn->getStratigraphicColumnRankInterpretationSet().size(); ++i)
	{
		std::cout << "\tCOLUMN RANK INTERP" << std::endl;
		StratigraphicColumnRankInterpretation* stratiColumnRankInterp = stratiColumn->getStratigraphicColumnRankInterpretationSet()[i];
		showAllMetadata(stratiColumnRankInterp);
		if (stratiColumnRankInterp->isAChronoStratiRank() == true)
			cout << "This is a chrono rank!" << endl;
		else
			cout << "This is not a chrono rank!" << endl;
		unsigned int contactCount = stratiColumnRankInterp->getContactCount();
		for (unsigned int contactIndex = 0; contactIndex < contactCount; ++contactIndex)
		{
			cout << "SUBJECT : " << endl;
			showAllMetadata(stratiColumnRankInterp->getSubjectOfContact(contactIndex));
			cout << "DIRECT OBJECT : " << endl;
			showAllMetadata(stratiColumnRankInterp->getDirectObjectOfContact(contactIndex));
		}

		vector<StratigraphicOccurrenceInterpretation*> soiSet = stratiColumnRankInterp->getStratigraphicOccurrenceInterpretationSet();
		for (unsigned int soiIndex = 0; soiIndex < soiSet.size(); ++soiIndex)
		{
			vector<WellboreMarkerFrameRepresentation*> markerFrameSet = soiSet[soiIndex]->getWellboreMarkerFrameRepresentationSet();
			for (unsigned int markerFrameIndex = 0; markerFrameIndex < markerFrameSet.size(); ++markerFrameIndex)
			{
				WellboreMarkerFrameRepresentation* markerFrame = markerFrameSet[markerFrameIndex];
				showAllMetadata(markerFrame);
				vector<WellboreMarker*> markerSet = markerFrame->getWellboreMarkerSet();
				double* doubleMds = new double[markerFrame->getMdValuesCount()];
				markerFrame->getMdAsDoubleValues(doubleMds);
				for (unsigned int mIndex = 0; mIndex < markerSet.size(); ++mIndex)
				{
					if (doubleMds[mIndex] == doubleMds[mIndex])
					{
						cout << doubleMds[mIndex] << endl;
					}
					else
						cout << "NaN" << endl;
				}
			}
		}
	}
}

void deserialize(const string & inputFile)
{
	common::EpcDocument pck(inputFile);
    //common::EpcDocument pck(inputFile, "/home/philippe/dev/fesapi/resources");
	string resqmlResult = pck.deserialize();
	if (!resqmlResult.empty())
	{
		cerr << resqmlResult << endl;
		return;
	}

#if !defined(OFFICIAL)
	//deserializePropertyKindMappingFiles(&pck);
#endif

	cout << "MAPPING ENUM VS STRING" << endl;
	cout << "rock permeability == " << pck.getEnergisticsPropertyKindName(pck.getEnergisticsPropertyKind("rock permeability")) << endl;
	cout << "m (meter) == " << pck.getEnergisticsUnitOfMeasureName(pck.getEnergisticsUnitOfMeasure("m")) << endl;

	cout << "EXTENDED CORE PROPERTIES" << endl;

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
	unordered_map<string, string> & extendedCoreProperty = pck.getExtendedCoreProperty();
	for (unordered_map<string, string>::const_iterator it = extendedCoreProperty.begin(); it != extendedCoreProperty.end(); ++it)
	{
		cout << it->first.c_str() << " " << it->second.c_str() << endl;
	}
#else
	tr1::unordered_map<string, string> & extendedCoreProperty = pck.getExtendedCoreProperty();
	for (tr1::unordered_map<string, string>::const_iterator it = extendedCoreProperty.begin(); it != extendedCoreProperty.end(); ++it)
	{
		cout << it->first.c_str() << " " << it->second.c_str() << endl;
	}
#endif

	cout << "CRS" << endl;
	vector<LocalDepth3dCrs*> depthCrsSet = pck.getLocalDepth3dCrsSet();
	for (size_t i = 0; i < depthCrsSet.size(); ++i)
	{
		cout << "Title is : " << depthCrsSet[i]->getTitle() << endl;
		if (depthCrsSet[i]->isProjectedCrsDefinedWithEpsg())
			cout << "Projected : EPSG one" << endl;
		else if (depthCrsSet[i]->isProjectedCrsUnknown())
			cout << "Projected : Unknown." << "Reason is:" << depthCrsSet[i]->getProjectedCrsUnknownReason() << endl;
	}
	vector<LocalTime3dCrs*> timeCrsSet = pck.getLocalTime3dCrsSet();
	for (size_t i = 0; i < timeCrsSet.size(); ++i)
	{
		cout << "Title is : " << timeCrsSet[i]->getTitle() << endl;
		if (timeCrsSet[i]->isVerticalCrsDefinedWithEpsg())
			cout << "Vertical : EPSG one" << endl;
		else if (timeCrsSet[i]->isVerticalCrsUnknown())
			cout << "Vertical : Unknown." << "Reason is:" << timeCrsSet[i]->getVerticalCrsUnknownReason() << endl;
	}
	cout << endl;

	std::vector<Fault*> faultSet = pck.getFaultSet();
	std::vector<PolylineSetRepresentation*> faultPolyRep = pck.getFaultPolylineSetRepSet();
	std::vector<TriangulatedSetRepresentation*> faultTriRepSet = pck.getFaultTriangulatedSetRepSet();
	std::vector<Horizon*> horizonSet = pck.getHorizonSet();
	std::vector<Grid2dRepresentation*> horizonGrid2dSet = pck.getHorizonGrid2dRepSet();
	std::vector<TriangulatedSetRepresentation*> horizonTriRepSet = pck.getHorizonTriangulatedSetRepSet();
	std::vector<PolylineRepresentation*> horizonSinglePolylineRepSet = pck.getHorizonPolylineRepSet();
	std::vector<WellboreFeature*> wellboreSet = pck.getWellboreSet();
	std::vector<WellboreTrajectoryRepresentation*> wellboreCubicTrajSet = pck.getWellboreCubicParamLineTrajRepSet();
	std::vector<UnstructuredGridRepresentation*> unstructuredGridRepSet = pck.getUnstructuredGridRepresentationSet();
	std::vector<TimeSeries*> timeSeriesSet = pck.getTimeSeriesSet();
	std::vector<StratigraphicColumn*> stratiColumnSet = pck.getStratigraphicColumnSet();

	std::cout << "FAULTS" << endl;
	for (size_t i = 0; i < faultSet.size(); ++i)
	{
		showAllMetadata(faultSet[i]);
	}

	std::cout << faultPolyRep.size() << " FAULT POLYLINE REP" << endl;
	for (size_t i = 0; i < faultPolyRep.size(); ++i)
	{
		showAllMetadata(faultPolyRep[i]);
		ULONG64 nodeCount = faultPolyRep[i]->getXyzPointCountOfAllPatches();
		double* allXyzPoints = new double[nodeCount * 3];
		faultPolyRep[i]->getXyzPointsOfAllPatchesInGlobalCrs(allXyzPoints);
		for (ULONG64 nodeIndex = 0; nodeIndex < nodeCount * 3; nodeIndex += 3)
		{
			std::cout << allXyzPoints[nodeIndex] << " " << allXyzPoints[nodeIndex+1] << " " << allXyzPoints[nodeIndex+2] << endl;
		}
		delete [] allXyzPoints;
		deserializeActivity(faultPolyRep[i]);
/*
		std::cout << "\tSEISMIC INFO" << endl;
		double* inlines = new double[nodeCount];
		faultPolyRep[i]->getInlinesOfPointsOfPatch(0, inlines);
		for (unsigned int index = 0; index < nodeCount; index++)
		{
			std::cout << "\tinline : " << inlines[index] << std::endl;
		}
		delete [] inlines;
		double* crosslines = new double[nodeCount];;
		faultPolyRep[i]->getCrosslinesOfPointsOfPatch(0, crosslines);
		for (unsigned int index = 0; index < nodeCount; index++)
		{
			std::cout << "\tcrossline : " << crosslines[index] << std::endl;
		}
		delete [] crosslines;
		*/

		showAllProperties(faultPolyRep[i]);
	}

	std::cout << "FAULTS TRI REP" << endl;
	for (size_t i = 0; i < faultTriRepSet.size(); i++)
	{
		showAllMetadata(faultTriRepSet[i]);

		ULONG64 pointCount = faultTriRepSet[i]->getXyzPointCountOfAllPatches();
		unsigned int triangleCount = faultTriRepSet[i]->getTriangleCountOfAllPatches();
		cout << "point Count " << pointCount << endl;
		cout << "triangle Count " << triangleCount << endl;

		std::cout << "\tFAULTS TRI REP GEOMETRY" << endl;
		double* xyzPoints = new double [pointCount * 3];
		faultTriRepSet[i]->getXyzPointsOfAllPatchesInGlobalCrs(xyzPoints);
		unsigned int * triangleIndices = new unsigned int [triangleCount * 3];
		faultTriRepSet[i]->getTriangleNodeIndicesOfAllPatches(triangleIndices);
		for (unsigned int j = 0; j < 5; j++)
		{
			std::cout << "\txyzPoints : " << xyzPoints[j] << std::endl;
			std::cout << "\ttriangleIndices : " << triangleIndices[j] << std::endl;
			std::cout << "\t--------------------------------------------------" << std::endl;
		}
		deserializeActivity(faultTriRepSet[i]);

		delete [] xyzPoints;
		delete [] triangleIndices;
		
		showAllProperties(faultTriRepSet[i]);
	}

	std::cout << "HORIZONS" << endl;
	for (size_t i = 0; i < horizonSet.size(); i++)
	{
		showAllMetadata(horizonSet[i]);
		std::cout << std::endl;
	}

	std::cout << "HORIZONS GRID 2D REP" << endl;
	for (size_t i = 0; i < horizonGrid2dSet.size(); i++)
	{
		showAllMetadata(horizonGrid2dSet[i]);

		cout << horizonGrid2dSet[i]->getXOriginInGlobalCrs() << endl;
		cout << horizonGrid2dSet[i]->getYOriginInGlobalCrs() << endl;

		cout << "I Node Count " << horizonGrid2dSet[i]->getNodeCountAlongIAxis() << endl;
		cout << "J Node Count " << horizonGrid2dSet[i]->getNodeCountAlongJAxis() << endl;
		double* zValues = new double [horizonGrid2dSet[i]->getNodeCountAlongIAxis() * horizonGrid2dSet[i]->getNodeCountAlongJAxis()];
		horizonGrid2dSet[i]->getZValuesInGlobalCrs(zValues);
		std::cout << "First zValue is : " << zValues[0] << std::endl;
		delete [] zValues;
		
		deserializeActivity(horizonGrid2dSet[i]);
		showAllProperties(horizonGrid2dSet[i]);
	}

	std::cout << "HORIZONS TRI REP" << endl;
	for (size_t i = 0; i < horizonTriRepSet.size(); i++)
	{
		showAllMetadata(horizonTriRepSet[i]);

		ULONG64 pointCount = horizonTriRepSet[i]->getXyzPointCountOfAllPatches();
		unsigned int triangleCount = horizonTriRepSet[i]->getTriangleCountOfAllPatches();
		cout << "point Count " << pointCount << endl;
		cout << "triangle Count " << triangleCount << endl;

		std::cout << "\tHORIZONS TRI REP GEOMETRY" << endl;
		double* xyzPoints = new double [pointCount * 3];
		horizonTriRepSet[i]->getXyzPointsOfAllPatchesInGlobalCrs(xyzPoints);
		unsigned int * triangleIndices = new unsigned int [triangleCount * 3];
		horizonTriRepSet[i]->getTriangleNodeIndicesOfAllPatches(triangleIndices);
		for (unsigned int j = 0; j < 5; j++)
		{
			std::cout << "\txyzPoints : " << xyzPoints[j] << std::endl;
			std::cout << "\ttriangleIndices : " << triangleIndices[j] << std::endl;
			std::cout << "\t--------------------------------------------------" << std::endl;
		}

		delete [] xyzPoints;
		delete [] triangleIndices;
		deserializeActivity(horizonTriRepSet[i]);
		showAllProperties(horizonTriRepSet[i]);
	}

	std::cout << "HORIZONS SINGLE POLYLINE REP" << endl;
	for (size_t i = 0; i < horizonSinglePolylineRepSet.size(); i++)
	{
		showAllMetadata(horizonSinglePolylineRepSet[i]);
/*
		cout << "Seismic support is : " << horizonSinglePolylineRepSet[i]->getSeismicSupportOfPatch(0)->getTitle() << endl;
		double * lineAbscissa = new double[horizonSinglePolylineRepSet[i]->getSeismicPointCountOfPatch(0)];
		horizonSinglePolylineRepSet[i]->getSeismicLineAbscissaOfPointsOfPatch(0, lineAbscissa);

		for (unsigned int j = 0; j < horizonSinglePolylineRepSet[i]->getSeismicPointCountOfPatch(0); j++)
		{
			std::cout << "line Abscissa : " << lineAbscissa[j] << std::endl;
		}
		delete [] lineAbscissa;
		*/
		showAllProperties(horizonSinglePolylineRepSet[i]);
	}

	std::cout << "STRATI COLUMN" << endl;
	for (size_t i = 0; i < stratiColumnSet.size(); i++)
	{
		deserializeStratiColumn(stratiColumnSet[i]);
	}

	std::cout << "WELLBORES" << endl;
	for (size_t i = 0; i < wellboreSet.size(); i++)
	{
		showAllMetadata(wellboreSet[i]);
		witsml1_4_1_1::Wellbore* witsmlWellbore = wellboreSet[i]->getWitsmlWellbore();
		if (witsmlWellbore != NULL)
		{
			std::cout << "Associated with witsml well bore " << witsmlWellbore->getTitle()
				<< " with GUID " << witsmlWellbore->getUuid() << " and witsml well " << witsmlWellbore->getWell()->getTitle()
				<< " with GUID " << witsmlWellbore->getWell()->getUuid() << std::endl;
			std::cout << "Associated with witsml well bore datum " << witsmlWellbore->getTrajectories()[0]->getMdDatumName();
			std::cout << "Well bore datum elevation uom" << witsmlWellbore->getTrajectories()[0]->getMdDatumElevationUom();
		}
		for (size_t j = 0; j < wellboreSet[i]->getInterpretationSet().size(); j++)
		{
			for (size_t k = 0; k < wellboreSet[i]->getInterpretationSet()[j]->getRepresentationSet().size(); k++)
			{
				if (wellboreSet[i]->getInterpretationSet()[j]->getRepresentationSet()[k]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREWellboreMarkerFrameRepresentation)
				{
					WellboreMarkerFrameRepresentation* wmf = static_cast<WellboreMarkerFrameRepresentation*>(wellboreSet[i]->getInterpretationSet()[j]->getRepresentationSet()[k]);
					vector<WellboreMarker*> marketSet = wmf->getWellboreMarkerSet();
					for (size_t markerIndex = 0; markerIndex < marketSet.size(); ++markerIndex)
					{
						std::cout << "marker : " << marketSet[i]->getTitle() << std::endl;
						std::cout << "marker boundary feature : " << marketSet[i]->getBoundaryFeatureInterpretation()->getTitle() << std::endl;
					}

					for (size_t l = 0; l < wmf->getPropertySet().size(); l++)
					{
						if (wmf->getPropertySet()[l]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalProperty)
						{
							CategoricalProperty* catVal = static_cast<CategoricalProperty*>(wmf->getPropertySet()[l]);
							if (catVal->getValuesHdfDatatype() == AbstractValuesProperty::LONG)
							{
								std::cout << "Hdf datatype is NATIVE LONG" << std::endl;
								long* tmp = new long[wmf->getMdValuesCount()];
								catVal->getLongValuesOfPatch(0, tmp);
								for (unsigned int ind = 0 ; ind < 2; ind++)
									std::cout << "Value " << ind << " : " << tmp[ind] << std::endl;
								delete [] tmp;
							}
							else if (catVal->getValuesHdfDatatype() == AbstractValuesProperty::INT)
							{
								std::cout << "Hdf datatype is NATIVE INT" << std::endl;
							}
						}
					}
				}
			}
		}
	}

	std::cout << endl << "WELLBORES CUBIC TRAJ" << endl;
	for (size_t i = 0; i < wellboreCubicTrajSet.size(); i++)
	{
		showAllMetadata(wellboreCubicTrajSet[i]);
		std::cout << "MD Datum is : " << wellboreCubicTrajSet[i]->getMdDatum()->getTitle() << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
		if (wellboreCubicTrajSet[i]->getXyzPointCountOfAllPatches() == 0)
			break;
		double* mdValues = new double[wellboreCubicTrajSet[i]->getXyzPointCountOfAllPatches()];
		wellboreCubicTrajSet[i]->getMdValues(mdValues);
		double* xyzPt = new double[wellboreCubicTrajSet[i]->getXyzPointCountOfAllPatches() * 3];
		wellboreCubicTrajSet[i]->getXyzPointsOfAllPatchesInGlobalCrs(xyzPt);
		for (ULONG64 j = 0; j < wellboreCubicTrajSet[i]->getXyzPointCountOfAllPatches()*3 && j < 10; j += 3)
		{
			cout << "Trajectory station : MD=" << mdValues[j] << " X=" << xyzPt[j] << " Y=" << xyzPt[j+1] << " Z=" << xyzPt[j+2] << endl;
		}
		delete [] mdValues;
		delete [] xyzPt;
		std::cout << "LOGS" << endl;
		std::cout << "--------------------------------------------------" << std::endl;
		std::vector<WellboreFrameRepresentation*> wellboreFrameSet = wellboreCubicTrajSet[i]->getWellboreFrameRepresentationSet();
		for (size_t j = 0; j < wellboreFrameSet.size(); j++)
		{
			showAllMetadata(wellboreFrameSet[j]);
			std::cout << "Value Count : " << wellboreFrameSet[j]->getMdValuesCount() << endl;
			if (wellboreFrameSet[j]->areMdValuesRegularlySpaced())
			{
				std::cout << "Regularly spaced" << std::endl;
				std::cout << "First Value : " << wellboreFrameSet[j]->getMdFirstValue() << endl;
				std::cout << "Increment : " << wellboreFrameSet[j]->getMdConstantIncrementValue() << endl;
			}
			else
			{
				std::cout << "Iregularly spaced" << std::endl;
			}
			if (wellboreFrameSet[j]->getMdHdfDatatype() == AbstractValuesProperty::DOUBLE)
				std::cout << "Hdf datatype is NATIVE DOUBLE" << std::endl;
			else if (wellboreFrameSet[j]->getMdHdfDatatype() == AbstractValuesProperty::FLOAT)
				std::cout << "Hdf datatype is NATIVE FLOAT" << std::endl;
			else if (wellboreFrameSet[j]->getMdHdfDatatype() == AbstractValuesProperty::UNKNOWN)
				std::cout << "Hdf datatype is UNKNOWN" << std::endl;
		}
	}

	std::cout << endl << "IJK GRID REP" << endl;
	unsigned int ijkGridCount = pck.getIjkGridRepresentationCount();
	for (unsigned int i = 0; i < ijkGridCount; ++i)
	{
		AbstractIjkGridRepresentation* ijkGrid = pck.getIjkGridRepresentation(i);

		showAllMetadata(ijkGrid);
		if (ijkGrid->getGeometryKind() != AbstractIjkGridRepresentation::NO_GEOMETRY)
		{
			std::cout << "Node count is : " << ijkGrid->getXyzPointCountOfPatch(0) << std::endl;
			double * gridPoints = new double[ijkGrid->getXyzPointCountOfPatch(0) * 3];
			ijkGrid->getXyzPointsOfAllPatchesInGlobalCrs(gridPoints);
			std::cout << "--------------------------------------------------" << std::endl;
			delete [] gridPoints;
		}

		if (ijkGrid->getInterpretation())
		{
			std::cout << "Interpretation is : " << ijkGrid->getInterpretation()->getTitle() << std::endl;
			if (ijkGrid->getInterpretation()->getInterpretedFeature())
				std::cout << "Feature is : " << ijkGrid->getInterpretation()->getInterpretedFeature()->getTitle() << std::endl;
			else
				std::cout << " NO Feature" << std::endl;
		}
		else
			std::cout << " NO interpretation" << std::endl;

		for (unsigned int subRepIndex = 0 ; subRepIndex < ijkGrid->getFaultSubRepresentationCount(); ++subRepIndex)
		{
			std::cout << "Fault Subrep is : " << ijkGrid->getFaultSubRepresentation(subRepIndex)->getTitle() << std::endl;
		}

		if (ijkGrid->hasEnabledCellInformation() == true)
		{
			std::cout << "Has enabled/disabled cell information" << std::endl;
			bool * enabledCells = new bool [ijkGrid->getCellCount()];
			ijkGrid->getEnabledCells(enabledCells);
			delete [] enabledCells;
		}

		unsigned int gridConnectionSetCount = ijkGrid->getGridConnectionSetRepresentationCount();
		std::cout << "Grid Connection Count is : " << gridConnectionSetCount << std::endl;
		if (gridConnectionSetCount > 0)
		{
			GridConnectionSetRepresentation* gridConnectionSet = ijkGrid->getGridConnectionSetRepresentation(0);
			unsigned int faultInterpOfGridConnCount = gridConnectionSet->getFaultInterpretationCount();
			std::cout << "Fault interpretation Count of this grid connection set is : " << faultInterpOfGridConnCount << endl;
			if (faultInterpOfGridConnCount > 0)
			{
				FaultInterpretation* faultInterpOfGridConn = gridConnectionSet->getFaultInterpretationFromFaultIndex(0);
				std::cout << "Fault interpretation of this grid connection set is : " << faultInterpOfGridConn->getTitle()  << " With UUID " << faultInterpOfGridConn->getUuid() << endl;
			}
		}

		if (ijkGrid->getParentGrid() != NULL)
		{
			std::cout << "\t PARENT WINDOW" << std::endl;
			if (ijkGrid->getParentGrid()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREIjkGridRepresentation)
			{
				std::cout << "\t Regrid I start at :" << ijkGrid->getRegridStartIndexOnParentGrid('i') << std::endl;
				std::cout << "\t Regrid J start at :" << ijkGrid->getRegridStartIndexOnParentGrid('j') << std::endl;
				std::cout << "\t Regrid K start at :" << ijkGrid->getRegridStartIndexOnParentGrid('k') << std::endl;
				std::cout << "\t I Interval count is :" << ijkGrid->getRegridIntervalCount('i') << std::endl;
				std::cout << "\t J Interval count is :" << ijkGrid->getRegridIntervalCount('j') << std::endl;
				std::cout << "\t K Interval count is :" << ijkGrid->getRegridIntervalCount('k') << std::endl;
			}
			else if (ijkGrid->getParentGrid()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREUnstructuredColumnLayerGridRepresentation)
			{
				std::cout << "\t Refined columns count :" << ijkGrid->getParentColumnIndexCount() << std::endl;
			}
			else if (ijkGrid->getParentGrid()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREUnstructuredGridRepresentation)
			{
				std::cout << "\t Refined cells count :" << ijkGrid->getParentCellIndexCount() << std::endl;
			}
		}
	
		showAllProperties(ijkGrid);
	}

	std::cout << endl << "UNSTRUCTURED GRID REP" << endl;
	for (size_t i = 0; i < unstructuredGridRepSet.size(); ++i)
	{
		showAllMetadata(unstructuredGridRepSet[i]);
		if (!unstructuredGridRepSet[i]->isPartial() && unstructuredGridRepSet[i]->hasGeometry())
		{
			std::cout << "Node count is : " << unstructuredGridRepSet[i]->getXyzPointCountOfPatch(0) << std::endl;
			ULONG64 * faceCountOfCells = new ULONG64 [unstructuredGridRepSet[i]->getCellCount()];
			unstructuredGridRepSet[i]->getCumulativeFaceCountPerCell(faceCountOfCells);
			std::cout << "Face count of cell 0 is : " << faceCountOfCells[0] << std::endl;
			if (unstructuredGridRepSet[i]->getCellCount() > 1)
				std::cout << "Face count of cell 1 is : " << faceCountOfCells[1] - faceCountOfCells[0] << std::endl;
			delete [] faceCountOfCells;
			double * gridPoints = new double[unstructuredGridRepSet[i]->getXyzPointCountOfPatch(0) * 3];
			unstructuredGridRepSet[i]->getXyzPointsOfAllPatchesInGlobalCrs(gridPoints);
			std::cout << "--------------------------------------------------" << std::endl;
			delete [] gridPoints;

			unstructuredGridRepSet[i]->loadGeometry();

			std::cout << "(in memory) Face count of cell 0 is : " << unstructuredGridRepSet[i]->getFaceCountOfCell(0) << std::endl;
			if (unstructuredGridRepSet[i]->getCellCount() > 1)
				std::cout << "(in memory) Face count of cell 1 is : " << unstructuredGridRepSet[i]->getFaceCountOfCell(1) << std::endl;	
			std::cout << "(in memory) Node  count of face 0 of cell 0 is : " << unstructuredGridRepSet[i]->getNodeCountOfFaceOfCell(0, 0) << std::endl;
			std::cout << "(in memory) Node  indice 0 of face 0 of cell 0 is : " << unstructuredGridRepSet[i]->getNodeIndicesOfFaceOfCell(0, 0)[0] << std::endl;
			std::cout << "(in memory) Node  indice 1 of face 0 of cell 0 is : " << unstructuredGridRepSet[i]->getNodeIndicesOfFaceOfCell(0, 0)[1] << std::endl;
			std::cout << "(in memory) Node  indice 2 of face 0 of cell 0 is : " << unstructuredGridRepSet[i]->getNodeIndicesOfFaceOfCell(0, 0)[2] << std::endl;
			std::cout << "(in memory) Node  indice 0 of face 1 of cell 0 is : " << unstructuredGridRepSet[i]->getNodeIndicesOfFaceOfCell(0, 1)[0] << std::endl;

			unstructuredGridRepSet[i]->unloadGeometry();

			showAllProperties(unstructuredGridRepSet[i]);
		}
	}

	std::cout << endl << "TIME SERIES" << endl;
	for (size_t i = 0; i < timeSeriesSet.size(); ++i)
	{
		showAllMetadata(timeSeriesSet[i]);
		for (size_t j = 0; j < timeSeriesSet[i]->getPropertySet().size(); ++j)
		{
			std::cout << endl << "\tPROPERTIES" << endl;
			showAllMetadata(timeSeriesSet[i]->getPropertySet()[j]);
		}
	}

	std::cout << endl << pck.getWarnings().size() << " WARNING(S)" << endl;
	for (size_t i = 0; i < pck.getWarnings().size(); ++i)
		std::cout << i << " - " << pck.getWarnings()[i] << endl;
}

/*
// Performance testing
int main(int argc, char **argv)
{
	string filePath("../../testingPackageCpp.epc");
	common::EpcDocument pck(filePath);

	AbstractHdfProxy* hdfProxy = pck.createHdfProxy("", "Hdf Proxy", pck.getStorageDirectory(), pck.getName() + ".h5");
	hdfProxy->openForWriting();
	
	hsize_t dims[3] = {151, 1, 1};
	float * testingValues = new float[151];
	hdfProxy->writeArrayNdOfFloatValues("testingGroup", "testingDataset", testingValues, dims, 3);

	hsize_t dims2[3] = {152, 1000, 1000};
	float * testingValues2 = new float[152000000];
	hdfProxy->writeArrayNdOfFloatValues("testingGroup", "testingDataset2", testingValues2, dims2, 3);


	pck.serialize();

	hdfProxy->close();

	delete [] testingValues;
}
*/

// filepath is defined in a macro to better check memory leak
#define filePath "../../testingPackageCpp.epc"
//#define filePath "C:/Users/Philippe/data/resqml/resqmlExchangedModel/v2_0/paradigm/unstructured.epc"
int main(int argc, char **argv)
{
	serialize(filePath);
	deserialize(filePath);

	cout << "Press enter to continue..." << endl;
	cin.get();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
