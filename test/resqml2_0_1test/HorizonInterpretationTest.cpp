#include "resqml2_0_1test/HorizonInterpretationTest.h"

#include "catch.hpp"
#include "AbstractObjectTest.h"
#include "resqml2_0_1test/HorizonTest.h"

#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/HorizonInterpretation.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* HorizonInterpretationTest::defaultUuid = "4b256b37-4013-47f9-b6c3-4460abc6e421";
const char* HorizonInterpretationTest::defaultTitle = "Horizon Interpretation Test";

HorizonInterpretationTest::HorizonInterpretationTest(const string & epcDocPath)
	: BoundaryFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, HorizonTest::defaultUuid, HorizonTest::defaultTitle)
{
}

HorizonInterpretationTest::HorizonInterpretationTest(EpcDocument * epcDoc, bool init)
	: BoundaryFeatureInterpretationTest(epcDoc, defaultUuid, defaultTitle, HorizonTest::defaultUuid, HorizonTest::defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void HorizonInterpretationTest::initEpcDocHandler()
{
	// creating dependencies
	HorizonTest* horizonTest = new HorizonTest(this->epcDoc, true);

	Horizon* horizon = static_cast<Horizon*>(this->epcDoc->getResqmlAbstractObjectByUuid(HorizonTest::defaultUuid));
	HorizonInterpretation* horizonInterp = this->epcDoc->createHorizonInterpretation(horizon, uuid, title);
	REQUIRE( horizonInterp != nullptr );

	// cleaning
	delete horizonTest;
}

void HorizonInterpretationTest::readEpcDocHandler()
{
	// reading dependencies
	HorizonTest* horizonTest = new HorizonTest(this->epcDoc, false);

	// cleaning
	delete horizonTest;
}