// unitTest.cpp : définit le point d'entrée pour l'application console.
//

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#endif

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "EpcDocumentTest.h"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"
#include "resqml2_0_1test/HorizonTest.h"
#include "resqml2_0_1test/HorizonInterpretationTest.h"
#include "resqml2_0_1test/FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "resqml2_0_1test/FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "resqml2_0_1test/FaultSingleAndMultiPatchTriangulatedSetRepresentationTest.h"
#include "resqml2_0_1test/ActivityTemplateGenericCreationTest.h"
#include "resqml2_0_1test/ActivityCreationTest.h"
#include "resqml2_0_1test/OneTetrahedronUnstructuredGridRepresentationTest.h"
#include "resqml2_0_1test/UnstructuredFromIjkGridRepresentationTest.h"
#include "resqml2_0_1test/TimeSeriesTest.h"
#include "resqml2_0_1test/ContinuousPropertySeriesTest.h"
#include "resqml2_0_1test/ContinuousPropertyOnPartialGridTest.h"
#include "resqml2_0_1test/WellboreMarkerFrameRepresentationTest.h"

#include "EpcDocument.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/MdDatum.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/WellboreInterpretation.h"

using namespace commontest;
using namespace resqml2_0_1test;

TEST_CASE( "Deserialize an EPC document", "[epc]")
{
	EpcDocumentTest* epcDocumentTest = new EpcDocumentTest("../../testingPackageCpp.epc");
	epcDocumentTest->deserialize();
}

TEST_CASE( "Export and import a local depth 3d crs", "[crs]" )
{
	LocalDepth3dCrsTest* localDepth3dCrsTest = new LocalDepth3dCrsTest("../../localDepth3dCrsTest.epc");

	localDepth3dCrsTest->serialize();
	localDepth3dCrsTest->deserialize();
}

TEST_CASE( "Export and import an horizon", "[feature]" )
{
	HorizonTest* horizonTest = new HorizonTest("../../testHorizon.epc");
	
	horizonTest->serialize();
	horizonTest->deserialize();
}

TEST_CASE( "Export and import an horizon interpretation", "[interpretation]" )
{
	HorizonInterpretationTest* horizonInterpretationTest = new HorizonInterpretationTest("../../testHorizonInterpretation.epc");

	horizonInterpretationTest->serialize();
	horizonInterpretationTest->deserialize();
}

TEST_CASE( "Export and import a single patch triangulated set fault representation", "[representation]" )
{
	FaultSinglePatchTriangulatedSetRepresentationTest* faultSinglePatchTriangulatedSetRepresentation = new FaultSinglePatchTriangulatedSetRepresentationTest("../../faultSinglePatchTriangulatedSetRepresentation.epc");
	
	faultSinglePatchTriangulatedSetRepresentation->serialize();
	faultSinglePatchTriangulatedSetRepresentation->deserialize();
}

TEST_CASE( "Export and import a multi patch triangulated set fault representation", "[representation]" )
{
	FaultMultiPatchTriangulatedSetRepresentationTest* faultMultiPatchTriangulatedSetRepresentation = new FaultMultiPatchTriangulatedSetRepresentationTest("../../faultMultiPatchTriangulatedSetRepresentation.epc");
	
	faultMultiPatchTriangulatedSetRepresentation->serialize();
	faultMultiPatchTriangulatedSetRepresentation->deserialize();
}

TEST_CASE( "Export and import a single and multi patch triangulated set fault representation", "[representation]" )
{
	FaultSingleAndMultiPatchTriangulatedSetRepresentationTest* faultSingleAndMultiPatchTriangulatedSetRepresentationTest = new FaultSingleAndMultiPatchTriangulatedSetRepresentationTest("../../faultSingleAndMultiPatchTriangulatedSetRepresentation.epc");
	
	faultSingleAndMultiPatchTriangulatedSetRepresentationTest->serialize();
	faultSingleAndMultiPatchTriangulatedSetRepresentationTest->deserialize();
}

TEST_CASE( "Export and import a generic creation activity template", "[activity]" )
{
	ActivityTemplateGenericCreationTest* activityTemplate = new ActivityTemplateGenericCreationTest("../../activityTemplateGenericCreationTest.epc");

	activityTemplate->serialize();
	activityTemplate->deserialize();
}

TEST_CASE( "Export and import an activity", "[activity]" )
{
	ActivityCreationTest* activity = new ActivityCreationTest("../../activityCreationTest.epc");

	activity->serialize();
	activity->deserialize();
}

TEST_CASE( "Export and import an unstructured grid", "[grid]" )
{
	OneTetrahedronUnstructuredGridRepresentationTest* gridTest = new OneTetrahedronUnstructuredGridRepresentationTest("../../oneTetrahedronUnstructuredGridRepresentationTest.epc");

	gridTest->serialize();
	gridTest->deserialize();
}

TEST_CASE( "Ijk to unstructured grid", "[grid]" )
{
	UnstructuredFromIjkGridRepresentationTest* gridTest = new UnstructuredFromIjkGridRepresentationTest("../../unstructuredFromIjkGridRepresentationTest.epc");

	gridTest->serialize();
	gridTest->deserialize();
}

TEST_CASE( "Export and import a time series", "[property]" )
{
	TimeSeriesTest* timeSeriesTest = new TimeSeriesTest("../../timeSeriesTest.epc");

	timeSeriesTest->serialize();
	timeSeriesTest->deserialize();
}

TEST_CASE( "Export and import continuous property series", "[property]" )
{
	ContinuousPropertySeriesTest* continuousPropertySeriesTest = new ContinuousPropertySeriesTest("../../continuousPropertySeriesTest.epc");

	continuousPropertySeriesTest->serialize();
	continuousPropertySeriesTest->deserialize();
}

TEST_CASE( "Export and import continuous property on partial grid", "[property]" )
{
	ContinuousPropertyOnPartialGridTest* continuousPropertyOnPartialGridTest = new ContinuousPropertyOnPartialGridTest("../../continuousPropertyOnPartialGridTest.epc");

	continuousPropertyOnPartialGridTest->serialize();
	continuousPropertyOnPartialGridTest->deserialize();
}

TEST_CASE("Export and import a wellbore marker frame", "[well][stratigraphy]")
{
	WellboreMarkerFrameRepresentationTest* wellboreMarkerFrameRepresentationTest = new WellboreMarkerFrameRepresentationTest("../../wellboreMarkerFrameRepresentationTest.epc");

	wellboreMarkerFrameRepresentationTest->serialize();
	wellboreMarkerFrameRepresentationTest->deserialize();
}