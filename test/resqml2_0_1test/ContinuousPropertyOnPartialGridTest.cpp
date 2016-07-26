#include "ContinuousPropertyOnPartialGridTest.h"
#include "../config.h"
#include "../catch.hpp"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2/AbstractRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

ContinuousPropertyOnPartialGridTest::ContinuousPropertyOnPartialGridTest(const string & epcDocPath)
	: ContinuousPropertyTest(epcDocPath, uuidContinuousPropertyOnPartialGrid, titleContinuousPropertyOnPartialGrid, uuidPartialUnstructuredGridRepresentation, titlePartialUnstructuredGridRepresentation) {
}

ContinuousPropertyOnPartialGridTest::ContinuousPropertyOnPartialGridTest(common::EpcDocument * epcDoc, bool init)
	: ContinuousPropertyTest(epcDoc, uuidContinuousPropertyOnPartialGrid, titleContinuousPropertyOnPartialGrid, uuidPartialUnstructuredGridRepresentation, titlePartialUnstructuredGridRepresentation) {
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void ContinuousPropertyOnPartialGridTest::initEpcDocHandler() {
	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	resqml2_0_1::UnstructuredGridRepresentation* partialGrid = this->epcDoc->createPartialUnstructuredGridRepresentation(uuidPartialUnstructuredGridRepresentation, titlePartialUnstructuredGridRepresentation);
	REQUIRE( partialGrid != nullptr );
	resqml2_0_1::ContinuousProperty* continuousProperty = this->epcDoc->createContinuousProperty(partialGrid, this->uuid, this->title, 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, 
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m, 
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	double continuousProp1Values[6] = { 0, 1, 2, 3, 4, 5 };
	continuousProperty->pushBackDoubleHdf5Array1dOfValues(continuousProp1Values, 6, hdfProxy);

	resqml2::GridConnectionSetRepresentation* gcs = this->epcDoc->createGridConnectionSetRepresentation("baf32ed5-3265-4552-8530-5580d1a8ddf9", "GCSR");
	gcs->pushBackSupportingGridRepresentation(partialGrid);
	ULONG64 cellConn[2] = {
		1,2
	};
	gcs->setCellIndexPairs(1, cellConn, -1, hdfProxy);
}

void ContinuousPropertyOnPartialGridTest::readEpcDocHandler() {
	// getting the ContinuousProperty
	resqml2_0_1::ContinuousProperty* continuousProperty = static_cast<resqml2_0_1::ContinuousProperty*>(this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid));

	// ************************************
	// reading the ContinuousProperty

	// getElementCountPerValue
	REQUIRE( continuousProperty->getElementCountPerValue() == 1 );

	// getAttachmentKind
	REQUIRE( continuousProperty->getAttachmentKind() == gsoap_resqml2_0_1::resqml2__IndexableElements__cells );

	// getUom
	REQUIRE( continuousProperty->getUom() == gsoap_resqml2_0_1::resqml2__ResqmlUom__m );

	// getEnergisticsPropertyKind
	REQUIRE( continuousProperty->getEnergisticsPropertyKind() == gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length );

	// getValuesCountOfPatch
	REQUIRE( continuousProperty->getValuesCountOfPatch(0) == 6 );

	double* values = new double[6];
	continuousProperty->getDoubleValuesOfPatch(0, values);
	REQUIRE( values[0] == 0 );
	REQUIRE( values[1] == 1 );
	REQUIRE( values[2] == 2 );
	REQUIRE( values[3] == 3 );
	REQUIRE( values[4] == 4 );
	REQUIRE( values[5] == 5 );
	delete [] values;

	// checking that the supporting representation is partial
	REQUIRE( continuousProperty->getRepresentation()->isPartial() );

	resqml2::GridConnectionSetRepresentation* gcs = epcDoc->getResqmlAbstractObjectByUuid<resqml2::GridConnectionSetRepresentation>("baf32ed5-3265-4552-8530-5580d1a8ddf9");
	REQUIRE(gcs->getSupportingGridRepresentationCount() == 1);
	REQUIRE(gcs->getSupportingGridRepresentation(0)->isPartial());
}
