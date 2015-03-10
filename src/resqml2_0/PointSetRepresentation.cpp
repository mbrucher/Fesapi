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
#include "resqml2_0/PointSetRepresentation.h"

#include "resqml2_0/AbstractFeatureInterpretation.h"
#include "resqml2_0/AbstractLocal3dCrs.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;

const char* PointSetRepresentation::XML_TAG = "PointSetRepresentation";

PointSetRepresentation::PointSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREPointSetRepresentation(interp->getGsoapProxy()->soap, 1);
	_resqml2__PointSetRepresentation* rep = static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	setInterpretation(interp);

	localCrs = crs;
	localCrs->addRepresentation(this);

	// epc document
	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

void PointSetRepresentation::pushBackGeometryPatch(
				const unsigned int & xyzPointCount, double * xyzPoints,
				HdfProxy * proxy)
{
	resqml2__NodePatch* patch = soap_new_resqml2__NodePatch(gsoapProxy->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch.size();
	patch->Count = xyzPointCount;

	// XYZ points
	hsize_t pointCountDims[] = {xyzPointCount};
	patch->Geometry = createPointGeometryPatch(patch->PatchIndex, xyzPoints, pointCountDims, 1, proxy);

	static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch.push_back(patch);
}

string PointSetRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

resqml2__PointGeometry* PointSetRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex < static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch.size())
			return static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch[patchIndex]->Geometry;
	else
		return NULL;
}

unsigned int PointSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex < static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch.size())
		return static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch[patchIndex]->Count;
	else
		return 0;
}

unsigned int PointSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml2__PointSetRepresentation*>(gsoapProxy)->NodePatch.size();
}

