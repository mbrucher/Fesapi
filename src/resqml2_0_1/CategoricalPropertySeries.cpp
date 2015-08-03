/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2015) 

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
#include "resqml2_0_1/CategoricalPropertySeries.h"

#include "resqml2_0_1/TimeSeries.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "resqml2_0_1/HdfProxy.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* CategoricalPropertySeries::XML_TAG = "CategoricalPropertySeries";

CategoricalPropertySeries::CategoricalPropertySeries(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			const unsigned int & timeIndexCount, class TimeSeries * ts, const bool & useInterval)
		: CategoricalProperty(strLookup)
{
	gsoapProxy = soap_new_resqml2__obj_USCORECategoricalPropertySeries(rep->getGsoapProxy()->soap, 1);	
	_resqml2__CategoricalPropertySeries* prop = static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (rep->getEpcDocument())
		rep->getEpcDocument()->addGsoapProxy(this);
}

CategoricalPropertySeries::CategoricalPropertySeries(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			StringTableLookup* strLookup, PropertyKind * localPropType,
			const unsigned int & timeIndexCount, class TimeSeries * ts, const bool & useInterval)
	:CategoricalProperty(strLookup)
{
	gsoapProxy = soap_new_resqml2__obj_USCORECategoricalPropertySeries(rep->getGsoapProxy()->soap, 1);	
	_resqml2__CategoricalPropertySeries* prop = static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml2__LocalPropertyKind(gsoapProxy->soap, 1);
	xmlLocalPropKind->LocalPropertyKind = localPropType->newResqmlReference();
	prop->PropertyKind = xmlLocalPropKind;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	localPropertyKind = localPropType;
	localPropType->addProperty(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (rep->getEpcDocument())
		rep->getEpcDocument()->addGsoapProxy(this);
}

void CategoricalPropertySeries::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	CategoricalProperty:: importRelationshipSetFromEpc(epcDoc);

	_resqml2__CategoricalPropertySeries* prop = static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy);
	if (prop->SeriesTimeIndices != nullptr)
	{
		updateXml = false;
		setTimeSeries(static_cast<TimeSeries*>(epcDoc->getResqmlAbstractObjectByUuid(prop->SeriesTimeIndices->TimeSeries->UUID)));
		updateXml = true;
	}
}

std::string CategoricalPropertySeries::getResqmlVersion() const
{
	return "2.0.1";
}
