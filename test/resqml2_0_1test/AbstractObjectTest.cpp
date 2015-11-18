#include "resqml2_0_1test/AbstractObjectTest.h"

#include "catch.hpp"
#include "AbstractTest.h"

#include "EpcDocument.h"
#include "resqml2_0_1/AbstractResqmlDataObject.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace commontest;

AbstractObjectTest::AbstractObjectTest(const string & epcDocPath, const string & uuid, const string & title) :
	AbstractTest(epcDocPath),
	uuid(uuid),
	title(title) {
}

AbstractObjectTest::AbstractObjectTest(common::EpcDocument* epcDoc, const string & uuid, const string & title) :
	AbstractTest(epcDoc),
	uuid(uuid),
	title(title) {
}

void AbstractObjectTest::initEpcDoc()
{
	if (this->epcDoc == nullptr)
		throw std::logic_error("The EPC document is not initialized.");

	if (this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid) != nullptr)
		return;

	this->initEpcDocHandler();
}

void AbstractObjectTest::readEpcDoc() {
	resqml2_0_1::AbstractResqmlDataObject* resqmlObject = static_cast<resqml2_0_1::AbstractResqmlDataObject*>(this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid));
	REQUIRE(resqmlObject != nullptr);
	REQUIRE(resqmlObject->getUuid() == this->uuid);
	REQUIRE( resqmlObject->getTitle() == this->title );

	this->readEpcDocHandler();
}