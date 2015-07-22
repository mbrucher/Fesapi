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
#include "resqml2_0_1/AbstractRepresentation.h"

#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "resqml2_0_1/AbstractTechnicalFeature.h"
#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/RepresentationSetRepresentation.h"
#include "resqml2_0_1/AbstractValuesProperty.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"

using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;
using namespace std;
using namespace epc;

AbstractRepresentation::AbstractRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs): interpretation(NULL), hdfProxy(NULL), localCrs(NULL)
{
	if (interp)
	{
		if (interp->getRepresentationCount() == 0)
		{
			if (crs->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
				static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain = resqml2__Domain__time;
			else
				static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain = resqml2__Domain__depth;
		}
		else if (static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain != resqml2__Domain__mixed)
		{
			AbstractLocal3dCrs* local3dCrs = NULL;
			unsigned int repIndex = 0;
			local3dCrs = interp->getRepresentation(repIndex)->getLocalCrs();
			while (local3dCrs == NULL && repIndex < interp->getRepresentationCount()-1)
			{
				++repIndex;
				local3dCrs = interp->getRepresentation(repIndex)->getLocalCrs();
			}
			if (local3dCrs)
			{
				if (interp->getRepresentation(repIndex)->getLocalCrs()->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs &&
					crs->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalDepth3dCrs)
					static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain = resqml2__Domain__mixed;
				else if (interp->getRepresentation(repIndex)->getLocalCrs()->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalDepth3dCrs &&
					crs->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
					static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain = resqml2__Domain__mixed;
			}
			else
			{
				if (crs->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
					static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain = resqml2__Domain__time;
				else
					static_cast<resqml2__AbstractFeatureInterpretation*>(interp->getGsoapProxy())->Domain = resqml2__Domain__depth;
			}
		}
	}
}


std::string AbstractRepresentation::getLocalCrsUuid() const
{
	resqml2__PointGeometry* pointGeom = getPointGeometry(0);
	if (pointGeom)
	{
		return pointGeom->LocalCrs->UUID;
	}
	else
		throw invalid_argument("No CRS is attached to this representation meaning that this representation has no geometry by itself.");
}

std::vector<SubRepresentation*> AbstractRepresentation::getFaultSubRepresentationSet() const
{
	std::vector<SubRepresentation*> result;

	for (unsigned int i = 0; i <subRepresentationSet.size(); ++i)
	{
		if (subRepresentationSet[i]->getInterpretation() && subRepresentationSet[i]->getInterpretation()->getXmlTag() == "FaultInterpretation")
			result.push_back(subRepresentationSet[i]);
	}

	return result;
}

void AbstractRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	resqml2__AbstractRepresentation* rep = static_cast<resqml2__AbstractRepresentation*>(gsoapProxy);

	if (rep->RepresentedInterpretation)
	{
		updateXml = false;
		setInterpretation(static_cast<AbstractFeatureInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->RepresentedInterpretation->UUID)));
		updateXml = true;
	}

	// Local CRS
	try
	{
		localCrs = static_cast<AbstractLocal3dCrs*>(epcDoc->getResqmlAbstractObjectByUuid(getLocalCrsUuid()));
		if (localCrs)
			localCrs->addRepresentation(this);
	}
	catch (const invalid_argument &) // No attached CRS
	{
		localCrs = NULL;
	}


	if (getHdfProxyUuid().empty() == false)
	{
		setHdfProxy(static_cast<HdfProxy*>(epcDoc->getResqmlAbstractObjectByUuid(getHdfProxyUuid())));
	}

	// Seismic support
	for (unsigned int patchIndex = 0; patchIndex < getPatchCount(); ++patchIndex)
	{
		resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
		if (geom && geom->SeismicCoordinates)
		{
			if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic3dCoordinates)
			{
				resqml2__Seismic3dCoordinates* seis3dInfo = static_cast<resqml2__Seismic3dCoordinates*>(geom->SeismicCoordinates);
				pushBackSeismicSupport(static_cast<AbstractRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(seis3dInfo->SeismicSupport->UUID)));
			}
			else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic2dCoordinates)
			{
				resqml2__Seismic2dCoordinates* seis2dInfo = static_cast<resqml2__Seismic2dCoordinates*>(geom->SeismicCoordinates);
				pushBackSeismicSupport(static_cast<AbstractRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(seis2dInfo->SeismicSupport->UUID)));
			}
		}
	}
}

void AbstractRepresentation::setInterpretation(AbstractFeatureInterpretation * interp)
{
	if (interp == nullptr)
	{
		return;
	}

	// EPC
	interpretation = interp;
	interpretation->representationSet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<resqml2__AbstractRepresentation*>(gsoapProxy)->RepresentedInterpretation = interp->newResqmlReference();
	}
}

vector<Relationship> AbstractRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result;

	if (interpretation)
	{
		Relationship relInterp(interpretation->getPartNameInEpcDocument(), "", interpretation->getUuid());
		relInterp.setDestinationObjectType();
		result.push_back(relInterp);
	}

	if (localCrs)
	{
		Relationship relCrs(localCrs->getPartNameInEpcDocument(), "", localCrs->getUuid());
		relCrs.setDestinationObjectType();
		result.push_back(relCrs);
	}

	if (hdfProxy)
	{
		Relationship relHdf(hdfProxy->getPartNameInEpcDocument(), "", hdfProxy->getUuid());
		relHdf.setMlToExternalPartProxyType();
		result.push_back(relHdf);
	}

	for (unsigned int i = 0; i < subRepresentationSet.size(); i++)
	{
		Relationship relSubRep(subRepresentationSet[i]->getPartNameInEpcDocument(), "", subRepresentationSet[i]->getUuid());
		relSubRep.setSourceObjectType();
		result.push_back(relSubRep);
	}

	for (unsigned int i = 0; i < propertySet.size(); i++)
	{
		Relationship relValues(propertySet[i]->getPartNameInEpcDocument(), "", propertySet[i]->getUuid());
		relValues.setSourceObjectType();
		result.push_back(relValues);
	}

	// Seismic support
	for(vector<AbstractRepresentation*>::const_iterator it = seismicSupportSet.begin(); it != seismicSupportSet.end(); ++it)
	{
		if (it == seismicSupportSet.begin() || std::find(seismicSupportSet.begin(), it, *it) != seismicSupportSet.end()) //  No need to add the rel twice
		{
			Relationship relSeisSupport((*it)->getPartNameInEpcDocument(), "", (*it)->getUuid());
			relSeisSupport.setDestinationObjectType();
			result.push_back(relSeisSupport);
		}
	}

	for (unsigned int i=0; i < seismicSupportedRepSet.size(); i++)
    {
        Relationship relSeisSupportedRep(seismicSupportedRepSet[i]->getPartNameInEpcDocument(), "", seismicSupportedRepSet[i]->getUuid());
        relSeisSupportedRep.setSourceObjectType();
        result.push_back(relSeisSupportedRep);
    }

	for (unsigned int i = 0; i < representationSetRepresentationSet.size(); i++)
	{
		Relationship relOrg(representationSetRepresentationSet[i]->getPartNameInEpcDocument(), "", representationSetRepresentationSet[i]->getUuid());
		relOrg.setSourceObjectType();
		result.push_back(relOrg);
	}

	return result;
}

std::string AbstractRepresentation::getInterpretationUuid() const
{
	if (static_cast<resqml2__AbstractRepresentation*>(gsoapProxy)->RepresentedInterpretation)
		return static_cast<resqml2__AbstractRepresentation*>(gsoapProxy)->RepresentedInterpretation->UUID;
	else
		return "";
}

void AbstractRepresentation::setHdfProxy(HdfProxy * proxy)
{
	if (!hdfProxy)
	{
		hdfProxy = proxy;
		proxy->representationSourceObject.push_back(this);
	}
}

std::vector<AbstractValuesProperty*> AbstractRepresentation::getValuesPropertySet() const
{
	std::vector<AbstractValuesProperty*> result;

	for (unsigned int i = 0; i < propertySet.size();i ++)
	{
		if (propertySet[i]->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREContinuousProperty ||
			propertySet[i]->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECategoricalProperty ||
			propertySet[i]->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREDiscreteProperty ||
			propertySet[i]->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORECommentProperty)
		{
			result.push_back(static_cast<AbstractValuesProperty*>(propertySet[i]));
		}
	}

	return result;
}

unsigned int AbstractRepresentation::getValuesPropertyCount() const
{
	return getValuesPropertySet().size();
}

AbstractValuesProperty* AbstractRepresentation::getValuesProperty(const unsigned int & index) const
{
	std::vector<AbstractValuesProperty*> set = getValuesPropertySet();

	if (set.size() > index)
		return getValuesPropertySet()[index];
	else
		throw out_of_range("The index of the property to get is out of range of the array of properties for this representation.");
}

std::string AbstractRepresentation::getHdfProxyUuidFromPointGeometryPatch(gsoap_resqml2_0_1::resqml2__PointGeometry* patch) const
{
	string result = "";
	if (patch)
	{
		if (patch->Points->soap_type() ==  SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray)
		{
			resqml2__Point3dZValueArray* tmp = static_cast<resqml2__Point3dZValueArray*>(patch->Points);
			if (tmp->ZValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
			{
				return static_cast<resqml2__DoubleHdf5Array*>(tmp->ZValues)->Values->HdfProxy->UUID;
			}
		}
		else if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
		{
			return static_cast<resqml2__Point3dHdf5Array*>(patch->Points)->Coordinates->HdfProxy->UUID;
		}
	}

	return result;
}

unsigned int AbstractRepresentation::getXyzPointCountOfAllPatches() const
{
	unsigned int result = 0;

	unsigned int patchCount = getPatchCount();
	for (unsigned int patchIndex = 0; patchIndex < patchCount; patchIndex++)
	{
		result += getXyzPointCountOfPatch(patchIndex);
	}

	return result;
}

gsoap_resqml2_0_1::resqml2__Seismic2dCoordinates* AbstractRepresentation::getSeismic2dCoordinates(const unsigned int & patchIndex) const
{
	resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
	if (!geom)
		return NULL;

	if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic2dCoordinates)
		return static_cast<resqml2__Seismic2dCoordinates*>(geom->SeismicCoordinates);
	else
		return NULL;
}

gsoap_resqml2_0_1::resqml2__Seismic3dCoordinates* AbstractRepresentation::getSeismic3dCoordinates(const unsigned int & patchIndex) const
{
	resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
	if (!geom)
		return NULL;

	if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic3dCoordinates)
		return static_cast<resqml2__Seismic3dCoordinates*>(geom->SeismicCoordinates);
	else
		return NULL;
}

void AbstractRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	resqml2__PointGeometry* pointGeom = getPointGeometry(patchIndex);
	if (pointGeom)
	{
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
		}
		else if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray)
		{
			throw logic_error("Reading parametric points should be implemented in specialized classes");
		}
	}
	else if (patchIndex == 0)
	{
		if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREWellboreTrajectoryRepresentation)
		{
			_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
			resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->PathInHdfFile, xyzPoints);
		}
	}
	else
	{
		if (gsoapProxy->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREPlaneSetRepresentation)
		{
			_resqml2__PlaneSetRepresentation* rep = static_cast<_resqml2__PlaneSetRepresentation*>(gsoapProxy);
			if (rep->Planes[patchIndex]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__HorizontalPlaneGeometry)
			{
				xyzPoints[0] = numeric_limits<double>::quiet_NaN();
				xyzPoints[1] = numeric_limits<double>::quiet_NaN();
				xyzPoints[2] = static_cast<resqml2__HorizontalPlaneGeometry*>(rep->Planes[patchIndex])->Coordinate;
			}
			else
			{
				resqml2__TiltedPlaneGeometry* tiltedPlane = static_cast<resqml2__TiltedPlaneGeometry*>(rep->Planes[patchIndex]); // TODO : allow more than one plane in one tilted plane
				xyzPoints[0] = tiltedPlane->Plane[0]->Point3d[0]->Coordinate1;
				xyzPoints[1] = tiltedPlane->Plane[0]->Point3d[0]->Coordinate2;
				xyzPoints[2] = tiltedPlane->Plane[0]->Point3d[0]->Coordinate3;
				xyzPoints[3] = tiltedPlane->Plane[1]->Point3d[1]->Coordinate1;
				xyzPoints[4] = tiltedPlane->Plane[1]->Point3d[1]->Coordinate2;
				xyzPoints[5] = tiltedPlane->Plane[1]->Point3d[1]->Coordinate3;
				xyzPoints[6] = tiltedPlane->Plane[2]->Point3d[2]->Coordinate1;
				xyzPoints[7] = tiltedPlane->Plane[2]->Point3d[2]->Coordinate2;
				xyzPoints[8] = tiltedPlane->Plane[2]->Point3d[2]->Coordinate3;
			}
		}
	}
}

void AbstractRepresentation::getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const
{
	getXyzPointsOfPatch(patchIndex, xyzPoints);

	double originOrdinal1 = localCrs->getOriginOrdinal1();
	double originOrdinal2 = localCrs->getOriginOrdinal2();
	double originOrdinal3 = .0;
	if (localCrs->getGsoapProxy()->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
		originOrdinal3 = localCrs->getOriginDepthOrElevation();
	double arealRotation = -localCrs->getArealRotation();

	if (originOrdinal1 == .0 && originOrdinal2 == .0 && originOrdinal3 == .0 && arealRotation == .0)
		return;

	unsigned int coordinatePointCount = getXyzPointCountOfPatch(patchIndex) * 3;
	for (unsigned int i = 0; i < coordinatePointCount; i+=3 )
	{
		xyzPoints[i] += originOrdinal1;
		xyzPoints[i+1] += originOrdinal2;
		xyzPoints[i+2] += originOrdinal3;
	}
}

void AbstractRepresentation::getXyzPointsOfAllPatches(double * xyzPoints) const
{
	unsigned int patchCount = getPatchCount();
	getXyzPointsOfPatch(0, xyzPoints);
	for (unsigned int patchIndex = 1; patchIndex < patchCount; patchIndex++)
	{
		xyzPoints += getXyzPointCountOfPatch(patchIndex-1) * 3;
		getXyzPointsOfPatch(patchIndex, xyzPoints);
	}
}

void AbstractRepresentation::getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const
{
	getXyzPointsOfAllPatches(xyzPoints);

	double originOrdinal1 = localCrs->getOriginOrdinal1();
	double originOrdinal2 = localCrs->getOriginOrdinal2();
	double originOrdinal3 = .0;
	if (localCrs->getGsoapProxy()->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
		originOrdinal3 = localCrs->getOriginDepthOrElevation();
	double arealRotation = -localCrs->getArealRotation();

	if (originOrdinal1 == .0 && originOrdinal2 == .0 && originOrdinal3 == .0 && arealRotation == .0)
		return;

	unsigned int coordinatePointCount = getXyzPointCountOfAllPatches() * 3;
	for (unsigned int i = 0; i < coordinatePointCount; i+=3 )
	{
		xyzPoints[i] += originOrdinal1;
		xyzPoints[i+1] += originOrdinal2;
		xyzPoints[i+2] += originOrdinal3;
	}
}

resqml2__PointGeometry* AbstractRepresentation::createPointGeometryPatch(const unsigned int & patchIndex,
	double * points, hsize_t * numPoints, const unsigned int & numDimensionsInArray, HdfProxy * proxy)
{
	setHdfProxy(proxy);

	resqml2__PointGeometry* geom = soap_new_resqml2__PointGeometry(gsoapProxy->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	resqml2__Point3dHdf5Array* xmlPts = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	xmlPts->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlPts->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
	ostringstream oss;
	oss << "points_patch" << patchIndex;
	xmlPts->Coordinates->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
	geom->Points = xmlPts;

	// HDF
	hsize_t * numValues = new hsize_t[numDimensionsInArray + 1];
	for (unsigned int i = 0; i < numDimensionsInArray; i++)
	{
		numValues[i] = numPoints[i];
	}
	numValues[numDimensionsInArray] = 3; // 3 for X, Y and Z

	hdfProxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), points, numValues, numDimensionsInArray + 1);

	delete [] numValues;

	return geom;
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
	AbstractRepresentation * seismicSupport, HdfProxy * proxy)
{
	setHdfProxy(proxy);

	resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
	if (!geom)
		throw invalid_argument("The patchIndex does not identify a point geometry.");

	if (geom->SeismicCoordinates == NULL)
		geom->SeismicCoordinates = soap_new_resqml2__Seismic3dCoordinates(gsoapProxy->soap, 1);
	else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic2dCoordinates)
		throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
	resqml2__Seismic3dCoordinates* patch = static_cast<resqml2__Seismic3dCoordinates*>(geom->SeismicCoordinates);

	patch->SeismicSupport = seismicSupport->newResqmlReference();
	pushBackSeismicSupport(seismicSupport);

	// inlines XML
	resqml2__DoubleHdf5Array* inlineValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
	inlineValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	inlineValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss;
	oss << "inlineCoordinates_patch" << patchIndex;
	inlineValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
	patch->InlineCoordinates = inlineValues;

	// inlines HDF
	hsize_t dim[] = {pointCount};
	hdfProxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), inlines, dim, 1);

	// crosslines XML
	resqml2__DoubleHdf5Array* crosslineValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
	crosslineValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	crosslineValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss2;
	oss2 << "crosslineCoordinates_patch" << patchIndex;
	crosslineValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss2.str();
	patch->CrosslineCoordinates = crosslineValues;

	// crosslines HDF
	hdfProxy->writeArrayNdOfDoubleValues(getUuid(), oss2.str(), crosslines, dim, 1);
}

void AbstractRepresentation::addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			AbstractRepresentation * seismicSupport)
{
	resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
	if (!geom)
		throw invalid_argument("The patchIndex does not identify a point geometry.");

	if (geom->SeismicCoordinates == NULL)
		geom->SeismicCoordinates = soap_new_resqml2__Seismic3dCoordinates(gsoapProxy->soap, 1);
	else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic2dCoordinates)
		throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
	resqml2__Seismic3dCoordinates* patch = static_cast<resqml2__Seismic3dCoordinates*>(geom->SeismicCoordinates);

	patch->SeismicSupport = seismicSupport->newResqmlReference();
	pushBackSeismicSupport(seismicSupport);

	// inlines XML
	resqml2__DoubleLatticeArray* inlineValues = soap_new_resqml2__DoubleLatticeArray(gsoapProxy->soap, 1);
	patch->InlineCoordinates = inlineValues;
	inlineValues->StartValue = startInline;
	resqml2__DoubleConstantArray * spacInline = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	spacInline->Count = countInline - 1;
	spacInline->Value = incrInline;
	inlineValues->Offset.push_back(spacInline);

	// crosslines XML
	resqml2__DoubleLatticeArray* crosslineValues = soap_new_resqml2__DoubleLatticeArray(gsoapProxy->soap, 1);
	patch->CrosslineCoordinates = crosslineValues;
	crosslineValues->StartValue = startCrossline;
	resqml2__DoubleConstantArray * spacCrossline = soap_new_resqml2__DoubleConstantArray (gsoapProxy->soap, 1);
	spacCrossline->Count = countCrossline - 1;
	spacCrossline->Value = incrCrossline;
	crosslineValues->Offset.push_back(spacCrossline);
}

void AbstractRepresentation::addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, HdfProxy * proxy)
{
	setHdfProxy(proxy);

	resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
	if (!geom)
		throw invalid_argument("The patchIndex does not identify a point geometry.");

	if (geom->SeismicCoordinates == NULL)
		geom->SeismicCoordinates = soap_new_resqml2__Seismic2dCoordinates(gsoapProxy->soap, 1);
	else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Seismic3dCoordinates)
		throw invalid_argument("It already exists some seismic 3d coordinates for this patch.");
	resqml2__Seismic2dCoordinates* patch = static_cast<resqml2__Seismic2dCoordinates*>(geom->SeismicCoordinates);

	patch->SeismicSupport = seismicSupport->newResqmlReference();
	pushBackSeismicSupport(seismicSupport);

	// abscissa XML
	resqml2__DoubleHdf5Array* abscissaValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
	abscissaValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	abscissaValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss;
	oss << "lineAbscissa_patch" << patchIndex;
	abscissaValues->Values->PathInHdfFile = "/RESQML/" + getUuid() + "/" + oss.str();
	patch->LineAbscissa = abscissaValues;

	// inlines HDF
	hsize_t dim[] = {pointCount};
	hdfProxy->writeArrayNdOfDoubleValues(getUuid(), oss.str(), lineAbscissa, dim, 1);
}

void AbstractRepresentation::pushBackSeismicSupport(AbstractRepresentation * seismicSupport)
{
	seismicSupportSet.push_back(seismicSupport);
	if (std::find(seismicSupportedRepSet.begin(), seismicSupportedRepSet.end(), this) == seismicSupportedRepSet.end())
		seismicSupport->seismicSupportedRepSet.push_back(this);
}
/*
void AbstractRepresentation::getInlinesOfPointsOfPatch(const unsigned int & patchIndex, double * values)
{
	gsoap_resqml2_0_1::resqml2__cs_USCOREseismic3dCoordinatesInfo* seisInfo = getSeismic3dCoordinatesInfo();
	if (!seisInfo)
		return;

	if (seisInfo->patch[patchIndex]->inlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		resqml2__DoubleHdf5Array* dblValues = static_cast<resqml2__DoubleHdf5Array*>(seisInfo->patch[patchIndex]->inlineCoordinates);
		hdfProxy->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
	}
}

void AbstractRepresentation::getCrosslinesOfPointsOfPatch(const unsigned int & patchIndex, double * values)
{
	gsoap_resqml2_0_1::resqml2__cs_USCOREseismic3dCoordinatesInfo* seisInfo = getSeismic3dCoordinatesInfo();
	if (!seisInfo)
		return;

	if (seisInfo->patch[patchIndex]->crosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		resqml2__DoubleHdf5Array* dblValues = static_cast<resqml2__DoubleHdf5Array*>(seisInfo->patch[patchIndex]->crosslineCoordinates);
		hdfProxy->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
	}
}
*/
void AbstractRepresentation::getSeismicLineAbscissaOfPointsOfPatch(const unsigned int & patchIndex, double * values)
{
	gsoap_resqml2_0_1::resqml2__Seismic2dCoordinates* seisInfo = getSeismic2dCoordinates(patchIndex);
	if (!seisInfo)
		return;

	if (seisInfo->LineAbscissa->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		resqml2__DoubleHdf5Array* dblValues = static_cast<resqml2__DoubleHdf5Array*>(seisInfo->LineAbscissa);
		hdfProxy->readArrayNdOfDoubleValues(dblValues->Values->PathInHdfFile, values);
	}
}

AbstractRepresentation* AbstractRepresentation::getSeismicSupportOfPatch(const unsigned int & patchIndex)
{
	if (seismicSupportSet.size() > patchIndex)
		return seismicSupportSet[patchIndex];
	else
		return NULL;
}

void AbstractRepresentation::pushBackIntoRepresentationSet(class RepresentationSetRepresentation * repSet)
{
	// XML
	static_cast<_resqml2__RepresentationSetRepresentation*>(repSet->getGsoapProxy())->Representation.push_back(newResqmlReference());

	// EPC
	repSet->representationSet.push_back(this);

	// Add the relationship
	representationSetRepresentationSet.push_back(repSet);
}
