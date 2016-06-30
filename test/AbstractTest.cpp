#include "AbstractTest.h"
#include "EpcDocument.h"
#include "catch.hpp"
#include "config.h"

using namespace std;
using namespace commontest;
using namespace resqml2_0_1test;

AbstractTest::AbstractTest(const string & epcDocPath) :
	epcDocPath(epcDocPath),
	epcDoc(nullptr) {
}

AbstractTest::AbstractTest(common::EpcDocument* epcDoc) :
	epcDocPath(epcDoc->getStorageDirectory()),
	epcDoc(epcDoc) {
}

void AbstractTest::serialize() {
	this->epcDoc = new common::EpcDocument(this->epcDocPath, common::EpcDocument::OVERWRITE);
	epcDoc->createHdfProxy(uuidHdfProxy, titleHdfProxy, this->epcDoc->getStorageDirectory(), epcDoc->getName() + ".h5");

	this->initEpcDoc();
	
	this->epcDoc->serialize();
	delete this->epcDoc;
}

void AbstractTest::deserialize() {
	this->epcDoc = new common::EpcDocument(this->epcDocPath);

	std::string validationResult = this->epcDoc->deserialize();
	if (validationResult.size() > 0)
		cout << "Validation error: " << validationResult << endl; 
	REQUIRE( validationResult.size() == 0 );
	
	REQUIRE( this->epcDoc->getHdfProxySet().size() == 1 );

	vector<string> warningSet = this->epcDoc->getWarnings();
	if (warningSet.size() > 0) {
		cout << "EPC document " << this->epcDoc->getName() << ".epc deserialized with " << warningSet.size() << " warning(s)" << endl;
		for (size_t i=0; i<warningSet.size(); ++i){
			cout << "Warning " << i+1 << ": " << warningSet[i] << endl;
		}
		cout << endl;
	}

	this->readEpcDoc();

	delete this->epcDoc;
}