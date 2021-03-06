/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2016) 

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
#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

#include <algorithm>
#include <sstream>

#include "H5public.h"

#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

void AbstractSurfaceRepresentation::setSurfaceRole(const resqml2__SurfaceRole & surfaceRole)
{
	static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->SurfaceRole = surfaceRole;
}

const gsoap_resqml2_0_1::resqml2__SurfaceRole & AbstractSurfaceRepresentation::getSurfaceRole() const
{
	return static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1)->SurfaceRole;
}

resqml2__Point3dFromRepresentationLatticeArray* AbstractSurfaceRepresentation::getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(resqml2__PointGeometry* patch) const
{
	if (patch != nullptr) {
		resqml2__Point3dFromRepresentationLatticeArray* patchOfSupportingRep = nullptr;

		if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray) {
			resqml2__Point3dZValueArray* zValuesPatch = static_cast<resqml2__Point3dZValueArray*>(patch->Points);
			if (zValuesPatch->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dFromRepresentationLatticeArray) {
				patchOfSupportingRep = static_cast<resqml2__Point3dFromRepresentationLatticeArray*>(zValuesPatch->SupportingGeometry);
			}
		}
		else if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dFromRepresentationLatticeArray) {
			patchOfSupportingRep = static_cast<resqml2__Point3dFromRepresentationLatticeArray*>(patch->Points);
		}

		return patchOfSupportingRep;
	}
	
	return nullptr;
}

resqml2__PointGeometry* AbstractSurfaceRepresentation::createArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection)
{
	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dLatticeArray* xmlPoints = soap_new_resqml2__Point3dLatticeArray(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Origin = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Origin->Coordinate1 = xOrigin;
	xmlPoints->Origin->Coordinate2 = yOrigin;
	xmlPoints->Origin->Coordinate3 = zOrigin;

	// first (slowest) dim : fastest is I (or inline), slowest is J (or crossline)
	resqml2__Point3dOffset* latticeDim = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset->Coordinate1 = xOffsetInSlowestDirection;
	latticeDim->Offset->Coordinate2 = yOffsetInSlowestDirection;
	latticeDim->Offset->Coordinate3 = zOffsetInSlowestDirection;
	resqml2__DoubleConstantArray* spacingInfo = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingInfo->Count = numPointsInSlowestDirection-1;
	spacingInfo->Value = spacingInSlowestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Offset.push_back(latticeDim);

	// Second (fastest) dimension :fastest is I (or inline), slowest is J (or crossline)
	latticeDim = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDim->Offset->Coordinate1 = xOffsetInFastestDirection;
	latticeDim->Offset->Coordinate2 = yOffsetInFastestDirection;
	latticeDim->Offset->Coordinate3 = zOffsetInFastestDirection;
	spacingInfo = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingInfo->Count = numPointsInFastestDirection-1;
	spacingInfo->Value = spacingInFastestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Offset.push_back(latticeDim);

	geom->Points = xmlPoints;

	return geom;
}

resqml2__PointGeometry* AbstractSurfaceRepresentation::createArray2dOfExplicitZ(
		const unsigned int & patchIndex,double * zValues,
		const unsigned int & numI, const unsigned int & numJ, resqml2::AbstractHdfProxy * proxy,
		Grid2dRepresentation * supportingRepresentation,
		const unsigned int & startGlobalIndex,
		const int & indexIncrementI, const int & indexIncrementJ)
{
	setHdfProxy(proxy);

	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dZValueArray* xmlPoints = soap_new_resqml2__Point3dZValueArray(gsoapProxy2_0_1->soap, 1);
	resqml2__Point3dFromRepresentationLatticeArray* patchPoints = soap_new_resqml2__Point3dFromRepresentationLatticeArray(gsoapProxy2_0_1->soap, 1);
	patchPoints->SupportingRepresentation = supportingRepresentation->newResqmlReference();
	patchPoints->NodeIndicesOnSupportingRepresentation = soap_new_resqml2__IntegerLatticeArray(gsoapProxy2_0_1->soap, 1);
	patchPoints->NodeIndicesOnSupportingRepresentation->StartValue = startGlobalIndex;
	xmlPoints->SupportingGeometry = patchPoints;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml2__IntegerConstantArray* offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = numJ-1;
	offset->Value = indexIncrementJ;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
	offset->Count = numI-1;
	offset->Value = indexIncrementI;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	// Z Values
	resqml2__DoubleHdf5Array* xmlZValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values->HdfProxy = hdfProxy->newResqmlReference();
	ostringstream oss3;
	oss3 << "points_patch" << patchIndex;
	xmlZValues->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + oss3.str();
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[] = {numJ, numI};
	hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid,
			oss3.str(),
			zValues,
			dim, 2);

	geom->Points = xmlPoints;
	return geom;
}

resqml2__PointGeometry* AbstractSurfaceRepresentation::createArray2dOfExplicitZ(
		const unsigned int & patchIndex, double * zValues,
		const unsigned int & numI, const unsigned int & numJ, resqml2::AbstractHdfProxy * proxy,
		const double & originX, const double & originY, const double & originZ,
		const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
		const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ)
{
	setHdfProxy(proxy);

	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dZValueArray* xmlPoints = soap_new_resqml2__Point3dZValueArray(gsoapProxy2_0_1->soap, 1);
	resqml2__Point3dLatticeArray* latticePoints = soap_new_resqml2__Point3dLatticeArray(gsoapProxy2_0_1->soap, 1);
	latticePoints->Origin = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticePoints->Origin->Coordinate1 = originX;
	latticePoints->Origin->Coordinate2 = originY;
	latticePoints->Origin->Coordinate3 = originZ;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml2__Point3dOffset* latticeDimForJ = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDimForJ->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDimForJ->Offset->Coordinate1 = offsetJX;
	latticeDimForJ->Offset->Coordinate2 = offsetJY;
	latticeDimForJ->Offset->Coordinate3 = offsetJZ;
	resqml2__DoubleConstantArray* spacingForJ = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingForJ->Value = spacingJ;
	spacingForJ->Count = numJ - 1;
	latticeDimForJ->Spacing = spacingForJ;
	latticePoints->Offset.push_back(latticeDimForJ);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml2__Point3dOffset* latticeDimForI = soap_new_resqml2__Point3dOffset(gsoapProxy2_0_1->soap, 1);
	latticeDimForI->Offset = soap_new_resqml2__Point3d(gsoapProxy2_0_1->soap, 1);
	latticeDimForI->Offset->Coordinate1 = offsetIX;
	latticeDimForI->Offset->Coordinate2 = offsetIY;
	latticeDimForI->Offset->Coordinate3 = offsetIZ;
	resqml2__DoubleConstantArray* spacingForI = soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1);
	spacingForI->Value = spacingI;
	spacingForI->Count = numI - 1;
	latticeDimForI->Spacing = spacingForI;
	latticePoints->Offset.push_back(latticeDimForI);
	
	xmlPoints->SupportingGeometry = latticePoints;

	// Z Values
	resqml2__DoubleHdf5Array* xmlZValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlZValues->Values->HdfProxy = hdfProxy->newResqmlReference();
	ostringstream oss3;
	oss3 << "points_patch" << patchIndex;
	xmlZValues->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + oss3.str();
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[] = {numJ, numI};
	hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid,
			oss3.str(),
			zValues,
			dim, 2);

	geom->Points = xmlPoints;
	return geom;
}

vector<Relationship> AbstractSurfaceRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// Outer rings
	for(vector<PolylineRepresentation*>::const_iterator it = outerRingSet.begin(); it != outerRingSet.end(); ++it) {
		if (it == outerRingSet.begin() || std::find(outerRingSet.begin(), it, *it) != outerRingSet.end()) { //  No need to add the rel twice
			Relationship relOuterRing((*it)->getPartNameInEpcDocument(), "", (*it)->getUuid());
			relOuterRing.setDestinationObjectType();
			result.push_back(relOuterRing);
		}
	}

	return result;
}

void AbstractSurfaceRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	resqml2__AbstractSurfaceRepresentation* rep = static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1);

	for (size_t i = 0; i < rep->Boundaries.size(); ++i) {
		if (rep->Boundaries[i]->OuterRing != nullptr) {
			if (rep->Boundaries[i]->OuterRing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPolylineRepresentation) {
				pushBackOuterRing(static_cast<PolylineRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->Boundaries[i]->OuterRing->UUID)));
			}
		}
	}
}

void AbstractSurfaceRepresentation::pushBackOuterRing(PolylineRepresentation * outerRing)
{
	resqml2__AbstractSurfaceRepresentation* rep = static_cast<resqml2__AbstractSurfaceRepresentation*>(gsoapProxy2_0_1);

	resqml2__PatchBoundaries * boundary = soap_new_resqml2__PatchBoundaries(gsoapProxy2_0_1->soap, 1);
	boundary->ReferencedPatch = rep->Boundaries.size();
	boundary->OuterRing = outerRing->newResqmlReference();
	rep->Boundaries.push_back(boundary);

	outerRingSet.push_back(outerRing);
	outerRing->pushBackRepresentationOuterRing(this);
}
