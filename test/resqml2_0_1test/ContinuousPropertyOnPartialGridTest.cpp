#include "ContinuousPropertyOnPartialGridTest.h"
#include "../config.h"
#include "../catch.hpp"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2/GridConnectionSetRepresentation.h"

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

	// Unstructured grid
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

	// IJK grid
	resqml2_0_1::AbstractIjkGridRepresentation* partialIjkGrid = epcDoc->createPartialIjkGridRepresentation("b0ec8bf4-9b93-428b-a814-87c38887f6d0", "PartialIjk Grid");
	REQUIRE(partialIjkGrid != nullptr);
	resqml2_0_1::ContinuousProperty* continuousPropertyOnIjk = epcDoc->createContinuousProperty(partialIjkGrid, "b20299b9-6881-4b91-ae2f-a87213437dce", "Continuous prop on partial ijk grid", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	double continuousPropOnIjkValues[6] = { 0, 1, 2, 3, 4, 5 };
	continuousPropertyOnIjk->pushBackDoubleHdf5Array1dOfValues(continuousPropOnIjkValues, 6, hdfProxy);

	// Truncated IJK grid
	resqml2_0_1::AbstractIjkGridRepresentation* partialTruncIjkGrid = epcDoc->createPartialTruncatedIjkGridRepresentation("def167fb-89b2-45bc-92ff-01d228142350", "PartialIjk Grid");
	REQUIRE(partialIjkGrid != nullptr);
	resqml2_0_1::ContinuousProperty* continuousPropertyOnTruncIjk = epcDoc->createContinuousProperty(partialTruncIjkGrid, "4caa8e9a-00b3-40c2-9460-72cb8790393a", "Continuous prop on partial truncated ijk grid", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	double continuousPropOnTruncIjkValues[6] = { 0, 1, 2, 3, 4, 5 };
	continuousPropertyOnTruncIjk->pushBackDoubleHdf5Array1dOfValues(continuousPropOnTruncIjkValues, 6, hdfProxy);

}

void ContinuousPropertyOnPartialGridTest::readEpcDocHandler() {
	// getting the ContinuousProperty
	resqml2_0_1::ContinuousProperty* continuousProperty = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::ContinuousProperty>(uuid);
	resqml2_0_1::ContinuousProperty* continuousPropertyOnIjk = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::ContinuousProperty>("b20299b9-6881-4b91-ae2f-a87213437dce");
	resqml2_0_1::ContinuousProperty* continuousPropertyOnTruncIjk = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::ContinuousProperty>("4caa8e9a-00b3-40c2-9460-72cb8790393a");

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
	REQUIRE(continuousProperty->getRepresentation()->isPartial());
	REQUIRE(continuousPropertyOnIjk->getRepresentation()->isPartial());
	REQUIRE(continuousPropertyOnIjk->getRepresentation()->getXmlTag().compare(resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG) == 0);
	REQUIRE(continuousPropertyOnTruncIjk->getRepresentation()->isPartial());
	REQUIRE(continuousPropertyOnTruncIjk->getRepresentation()->getXmlTag().compare(resqml2_0_1::AbstractIjkGridRepresentation::XML_TAG_TRUNCATED) == 0);

	resqml2::GridConnectionSetRepresentation* gcs = epcDoc->getResqmlAbstractObjectByUuid<resqml2::GridConnectionSetRepresentation>("baf32ed5-3265-4552-8530-5580d1a8ddf9");
	REQUIRE(gcs->getSupportingGridRepresentationCount() == 1);
	REQUIRE(gcs->getSupportingGridRepresentation(0)->isPartial());
}
