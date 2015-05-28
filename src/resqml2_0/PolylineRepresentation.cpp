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
#include "PolylineRepresentation.h"

#include "AbstractFeatureInterpretation.h"
#include "AbstractLocal3dCrs.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;
using namespace epc;

const char* PolylineRepresentation::XML_TAG = "PolylineRepresentation";

void PolylineRepresentation::init(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREPolylineRepresentation(crs->getGsoapProxy()->soap, 1);
	_resqml2__PolylineRepresentation* polylineRep = static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy);

	polylineRep->IsClosed = isClosed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationships
	if (interp != nullptr)
		setInterpretation(interp);

	localCrs = crs;
	localCrs->addRepresentation(this);

	// epc document
	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

PolylineRepresentation::PolylineRepresentation(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed):
	AbstractRepresentation(nullptr, crs)
{
	init(nullptr, crs, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title, isClosed);
}

PolylineRepresentation::PolylineRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const resqml2__LineRole & roleKind,
			bool isClosed):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title, isClosed);
	static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy->soap, sizeof(resqml2__LineRole));
	(*static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->LineRole) = roleKind;
}

std::string PolylineRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

resqml2__PointGeometry* PolylineRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->NodePatch->Geometry;
	else
		return NULL;
}

unsigned int PolylineRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
	{
		return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->NodePatch->Count;
	}
	else
		return 0;
}

void PolylineRepresentation::setGeometry(double * points, const unsigned int & pointCount, HdfProxy * proxy)
{
	_resqml2__PolylineRepresentation* polylineRep = static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy);
	polylineRep->NodePatch = soap_new_resqml2__NodePatch(gsoapProxy->soap, 1);
	polylineRep->NodePatch->Count = pointCount;
	polylineRep->NodePatch->PatchIndex = 0;

	hsize_t pointCountDims[] = {pointCount};
	polylineRep->NodePatch->Geometry = createPointGeometryPatch(0, points, pointCountDims, 1, proxy);
}

bool PolylineRepresentation::isclosed() const
{
	return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->IsClosed;
}

bool PolylineRepresentation::hasALineRole() const
{
	return static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->LineRole;
}

gsoap_resqml2_0::resqml2__LineRole PolylineRepresentation::getLineRole() const
{
	if (!hasALineRole())
		throw invalid_argument("The polyline doesn't have any role");

	return *(static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->LineRole);
}

vector<Relationship> PolylineRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// Outer rings of
	for(unsigned int i = 0; i < outerRingOfSet.size(); ++i)
	{
		Relationship relOuterRingOf(outerRingOfSet[i]->getPartNameInEpcDocument(), "", outerRingOfSet[i]->getUuid());
		relOuterRingOf.setSourceObjectType();
		result.push_back(relOuterRingOf);
	}

	// Inner rings of
	for(unsigned int i = 0; i < innerRingOfSet.size(); ++i)
	{
		Relationship relInnerRingOf(innerRingOfSet[i]->getPartNameInEpcDocument(), "", innerRingOfSet[i]->getUuid());
		relInnerRingOf.setSourceObjectType();
		result.push_back(relInnerRingOf);
	}

	return result;
}

void PolylineRepresentation::setLineRole(const gsoap_resqml2_0::resqml2__LineRole & lineRole)
{
	if (hasALineRole() == false)
		static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy->soap, sizeof(resqml2__LineRole));

	(*static_cast<_resqml2__PolylineRepresentation*>(gsoapProxy)->LineRole) = lineRole;
}
