/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014) 

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
#include "resqml2_0_1/LocalTime3dCrs.h"

#include <stdexcept>

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* LocalTime3dCrs::XML_TAG = "LocalTime3dCrs";

LocalTime3dCrs::LocalTime3dCrs(common::EpcDocument* epcDoc, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const bool & isUpOriented, const unsigned int & verticalEpsgCode)
{
	if (!epcDoc)
		throw invalid_argument("The EPC document where the local CRS will be stored cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCORELocalTime3dCrs(epcDoc->getGsoapContext(), 1);
	_resqml2__LocalTime3dCrs* local3dCrs = static_cast<_resqml2__LocalTime3dCrs*>(gsoapProxy);
	local3dCrs->ArealRotation = soap_new_eml__PlaneAngleMeasure(gsoapProxy->soap, 1);
	local3dCrs->ArealRotation->__item = arealRotation;
	local3dCrs->ArealRotation->uom = eml__PlaneAngleUom__rad;
	local3dCrs->XOffset = originOrdinal1;
	local3dCrs->YOffset = originOrdinal2;
	local3dCrs->ZOffset = originOrdinal3;
	local3dCrs->ZIncreasingDownward = !isUpOriented;
	local3dCrs->ProjectedUom = projectedUom;
	local3dCrs->VerticalUom = verticalUom;
	local3dCrs->TimeUom = timeUom;

	// Projected CRS
	if (projectedEpsgCode != 0)
	{
		eml__ProjectedCrsEpsgCode* projCrs = soap_new_eml__ProjectedCrsEpsgCode(gsoapProxy->soap, 1);
		local3dCrs->ProjectedCrs = projCrs;
		projCrs->EpsgCode = projectedEpsgCode;
	}
	else
	{
		eml__ProjectedUnknownCrs* projCrs = soap_new_eml__ProjectedUnknownCrs(gsoapProxy->soap, 1);
		local3dCrs->ProjectedCrs = projCrs;
		projCrs->Unknown = "Unknown";
	}

	// Vertical CRS
	if (verticalEpsgCode != 0)
	{
		eml__VerticalCrsEpsgCode* vertCrs = soap_new_eml__VerticalCrsEpsgCode(gsoapProxy->soap, 1);
		local3dCrs->VerticalCrs = vertCrs;
		vertCrs->EpsgCode = verticalEpsgCode;
	}
	else
	{
		eml__VerticalUnknownCrs* vertCrs = soap_new_eml__VerticalUnknownCrs(gsoapProxy->soap, 1);
		local3dCrs->VerticalCrs = vertCrs;
		vertCrs->Unknown = "Unknown";
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	epcDoc->addGsoapProxy(this);
}

gsoap_resqml2_0_1::eml__TimeUom LocalTime3dCrs::getUnit() const
{
	return static_cast<_resqml2__LocalTime3dCrs*>(gsoapProxy)->TimeUom;
}

std::string LocalTime3dCrs::getUnitAsString() const
{
	return gsoap_resqml2_0_1::soap_eml__TimeUom2s(gsoapProxy->soap, static_cast<_resqml2__LocalTime3dCrs*>(gsoapProxy)->TimeUom);
}
