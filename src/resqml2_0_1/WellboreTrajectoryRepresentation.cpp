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
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

#include <stdexcept>

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/MdDatum.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

#include "witsml1_4_1_1/Trajectory.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;
using namespace common;

const char* WellboreTrajectoryRepresentation::XML_TAG = "WellboreTrajectoryRepresentation";

WellboreTrajectoryRepresentation::WellboreTrajectoryRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, MdDatum * mdInfo) :
	AbstractRepresentation(interp, mdInfo->getLocalCrs()), mdDatum(mdInfo), parentTraj(nullptr), witsmlTrajectory(nullptr)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREWellboreTrajectoryRepresentation(interp->getEpcDocument()->getGsoapContext(), 1);	
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	
	setInterpretation(interp);

	rep->MdDatum = mdInfo->newResqmlReference();
	mdInfo->addWellboreTrajectoryRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
	
	localCrs = mdInfo->getLocalCrs();
	localCrs->addRepresentation(this);

	rep->MdUom = mdInfo->getLocalCrs()->getVerticalCrsUnit();

	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints, const double & startMd, const double & endMd, const unsigned int & controlPointCount, const int & lineKind, AbstractHdfProxy * proxy)
{
	if (controlPoints == nullptr)
		throw invalid_argument("The control points are missing.");
	if (controlPointCount == 0)
		throw invalid_argument("The control point count cannot be 0.");
	if (proxy == nullptr)
		throw invalid_argument("The HDF proxy is missing.");

	setHdfProxy(proxy);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);

	rep->Geometry = soap_new_resqml2__ParametricLineGeometry(gsoapProxy->soap, 1);
	resqml2__ParametricLineGeometry* paramLine = soap_new_resqml2__ParametricLineGeometry(gsoapProxy->soap, 1);
	paramLine->LocalCrs = localCrs->newResqmlReference();
	rep->StartMd = startMd;
	rep->FinishMd = endMd;
	rep->Geometry = paramLine;

	paramLine->KnotCount = controlPointCount;
	paramLine->LineKindIndex = lineKind;

	// XML control points
	resqml2__Point3dHdf5Array* xmlControlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	xmlControlPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlControlPoints->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
	xmlControlPoints->Coordinates->PathInHdfFile = "/RESQML/" + rep->uuid + "/controlPoints";
	paramLine->ControlPoints = xmlControlPoints;

	// HDF control points
	hsize_t dim[] = { controlPointCount, 3 };
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "controlPoints", controlPoints, dim, 2);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints, double* controlPointParameters, const unsigned int & controlPointCount,
			AbstractHdfProxy * proxy)
{
	if (controlPointParameters == nullptr)
		throw invalid_argument("The control points parameters are missing.");

	setGeometry(controlPoints, controlPointParameters[0], controlPointParameters[controlPointCount - 1], controlPointCount, 2, proxy);
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);

	// XML control point parameters
	resqml2__DoubleHdf5Array* xmlControlPointParameters = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
	xmlControlPointParameters->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlControlPointParameters->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlControlPointParameters->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/controlPointParameters";
	paramLine->ControlPointParameters = xmlControlPointParameters;

	// HDF control point parameters
	hsize_t dimParamDataSet[] = {controlPointCount};
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "controlPointParameters", controlPointParameters, dimParamDataSet, 1);
}

void WellboreTrajectoryRepresentation::setGeometry(double * controlPoints,
			double * tangentVectors, double* controlPointParameters, const unsigned int & controlPointCount,
			AbstractHdfProxy * proxy)
{
	setGeometry(controlPoints, controlPointParameters, controlPointCount, proxy);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
	paramLine->LineKindIndex = 5;

	// XML tangent vectors
	resqml2__Point3dHdf5Array* xmlTangentVectors = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	xmlTangentVectors->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlTangentVectors->Coordinates->HdfProxy = hdfProxy->newResqmlReference();
	xmlTangentVectors->Coordinates->PathInHdfFile = "/RESQML/" + rep->uuid + "/tangentVectors";
	paramLine->TangentVectors = xmlTangentVectors;

	// HDF tangent vectors
	hsize_t dim[] = { controlPointCount, 3 };
	hdfProxy->writeArrayNdOfDoubleValues(rep->uuid, "tangentVectors", tangentVectors, dim, 2);
}

void WellboreTrajectoryRepresentation::setWitsmlTrajectory(witsml1_4_1_1::Trajectory * witsmlTraj)
{
	witsmlTrajectory = witsmlTraj;
	witsmlTraj->resqmlWellboreTrajectoryRepresentation = this;

	if (updateXml)
	{
		resqml2__obj_USCOREWellboreTrajectoryRepresentation* resqmlTraj = static_cast<resqml2__obj_USCOREWellboreTrajectoryRepresentation*>(gsoapProxy);
		resqmlTraj->WitsmlTrajectory = witsmlTraj->newResqmlReference();
	}
}

vector<Relationship> WellboreTrajectoryRepresentation::getAllEpcRelationships() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// XML forward relationship
	if (mdDatum)
	{
		Relationship relMdInfo(mdDatum->getPartNameInEpcDocument(), "", rep->MdDatum->UUID);
		relMdInfo.setDestinationObjectType();
		result.push_back(relMdInfo);
	}
	else
		throw domain_error("The MD information associated to the WellboreFeature trajectory cannot be nullptr.");

	if (parentTraj)
	{
		Relationship relParentTraj(parentTraj->getPartNameInEpcDocument(), "", rep->ParentIntersection->ParentTrajectory->UUID);
		relParentTraj.setDestinationObjectType();
		result.push_back(relParentTraj);
	}

	if (witsmlTrajectory)
	{
		Relationship relWitsmlTraj(witsmlTrajectory->getPartNameInEpcDocument(), "", witsmlTrajectory->getUuid());
		relWitsmlTraj.setDestinationObjectType();
		result.push_back(relWitsmlTraj);
	}

	// XML backward relationship
	for (unsigned int i = 0 ; i < childrenTrajSet.size(); i++)
	{
		Relationship relChildrenTraj(childrenTrajSet[i]->getPartNameInEpcDocument(), "", childrenTrajSet[i]->getUuid());
		relChildrenTraj.setSourceObjectType();
		result.push_back(relChildrenTraj);
	}

	for (unsigned int i = 0 ; i < wellboreFrameRepresentationSet.size(); i++)
	{
		Relationship relFrame(wellboreFrameRepresentationSet[i]->getPartNameInEpcDocument(), "", wellboreFrameRepresentationSet[i]->getUuid());
		relFrame.setSourceObjectType();
		result.push_back(relFrame);
	}

	return result;
}

void WellboreTrajectoryRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);

	mdDatum = static_cast<MdDatum*>(epcDoc->getResqmlAbstractObjectByUuid(rep->MdDatum->UUID));
	if (mdDatum)
		mdDatum->addWellboreTrajectoryRepresentation(this);

	if (rep->ParentIntersection)
	{
		parentTraj = static_cast<WellboreTrajectoryRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->ParentIntersection->ParentTrajectory->UUID));
		parentTraj->addChildrenTrajectory(this);
	}

	if (rep->WitsmlTrajectory)
	{
		witsml1_4_1_1::Trajectory* tmp = static_cast<witsml1_4_1_1::Trajectory*>(epcDoc->getWitsmlAbstractObjectByUuid(rep->WitsmlTrajectory->UUID));
		if (tmp)
		{
			updateXml = false;
			setWitsmlTrajectory(tmp);
			updateXml = true;
		}
	}
}

void WellboreTrajectoryRepresentation::addParentTrajectory(const double & kickoffMd, const double & parentMd, WellboreTrajectoryRepresentation* parentTrajRep)
{
	parentTraj = parentTrajRep;
	parentTrajRep->addChildrenTrajectory(this);

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	rep->ParentIntersection = soap_new_resqml2__WellboreTrajectoryParentIntersection(rep->soap, 1);
	rep->ParentIntersection->KickoffMd = kickoffMd;
	rep->ParentIntersection->ParentMd = parentMd;
	rep->ParentIntersection->ParentTrajectory = parentTrajRep->newResqmlReference();
}

ULONG64 WellboreTrajectoryRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index patch is not in the allowed range of patch.");

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->KnotCount;
}

void WellboreTrajectoryRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index patch is not in the allowed range of patch");

	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	if (rep->Geometry != nullptr)
	{
		resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->PathInHdfFile, xyzPoints);
	}
	else
	{
		throw invalid_argument("The wellbore trajectory has no geometry.");
	}
}

int WellboreTrajectoryRepresentation::getGeometryKind() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	if (rep->Geometry == nullptr)
		return -1;
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineGeometry)
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->LineKindIndex;
}

bool WellboreTrajectoryRepresentation::hasMdValues() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	if (rep->Geometry == nullptr)
		return false;
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineGeometry)
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters != nullptr;
}

void WellboreTrajectoryRepresentation::getMdValues(double * values)
{
	if (hasMdValues() == false)
		throw invalid_argument("This trajectory has not got any md values.");
	if (hdfProxy == nullptr)
		throw invalid_argument("The HDF proxy is missing.");
		
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	resqml2__DoubleHdf5Array* xmlControlPointParameters = static_cast<resqml2__DoubleHdf5Array*>(static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->ControlPointParameters);
	hdfProxy->readArrayNdOfDoubleValues(xmlControlPointParameters->Values->PathInHdfFile, values);
}

double WellboreTrajectoryRepresentation::getStartMd() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy)->StartMd;
}

double WellboreTrajectoryRepresentation::getFinishMd() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy)->FinishMd;
}

bool WellboreTrajectoryRepresentation::hasTangentVectors() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	if (rep->Geometry == nullptr)
		return false;
	if (rep->Geometry->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineGeometry)
		throw logic_error("This kind of parametric line is not yet supported for a wellbore trajectory.");
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->TangentVectors != nullptr;
}

void WellboreTrajectoryRepresentation::getTangentVectors(double* tangentVectors)
{
	if (hdfProxy == nullptr)
		throw invalid_argument("The HDF proxy is missing.");
		
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	resqml2__Point3dHdf5Array* xmlTangentVectors = static_cast<resqml2__Point3dHdf5Array*>(static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->TangentVectors);
	hdfProxy->readArrayNdOfDoubleValues(xmlTangentVectors->Coordinates->PathInHdfFile, tangentVectors);
}

std::string WellboreTrajectoryRepresentation::getMdDatumUuid() const
{
	return static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy)->MdDatum->UUID;
}

std::string WellboreTrajectoryRepresentation::getHdfProxyUuid() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	resqml2__ParametricLineGeometry* paramLine = static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry);
	return static_cast<resqml2__Point3dHdf5Array*>(paramLine->ControlPoints)->Coordinates->HdfProxy->UUID;
}

std::string WellboreTrajectoryRepresentation::getLocalCrsUuid() const
{
	_resqml2__WellboreTrajectoryRepresentation* rep = static_cast<_resqml2__WellboreTrajectoryRepresentation*>(gsoapProxy);
	return static_cast<resqml2__ParametricLineGeometry*>(rep->Geometry)->LocalCrs->UUID;
}
