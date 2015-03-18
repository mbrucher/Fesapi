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
#include "resqml2_0/WellboreFrameRepresentation.h"

#include <stdexcept>

#include "resqml2_0/WellboreInterpretation.h"
#include "resqml2_0/WellboreTrajectoryRepresentation.h"
#include "resqml2_0/AbstractLocal3dCrs.h"
#include "resqml2_0/HdfProxy.h"

#include "witsml1_4_1_1/Log.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;
using namespace epc;

const char* WellboreFrameRepresentation::XML_TAG = "WellboreFrameRepresentation";

WellboreFrameRepresentation::WellboreFrameRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj) :
	AbstractRepresentation(interp, traj->getLocalCrs()), trajectory(traj), witsmlLog(NULL)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREWellboreFrameRepresentation(interp->getGsoapProxy()->soap, 1);	
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

vector<Relationship> WellboreFrameRepresentation::getAllEpcRelationships() const
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);
	
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// XML forward relationship
	if (trajectory)
	{
		Relationship relTraj(trajectory->getPartNameInEpcDocument(), "", frame->Trajectory->UUID);
		relTraj.setDestinationObjectType();
		result.push_back(relTraj);
	}
	else
		throw domain_error("The trajectory associated to the WellboreFeature frame cannot be NULL.");

	if (witsmlLog)
	{
		Relationship relWitsmlLog(witsmlLog->getPartNameInEpcDocument(), "", witsmlLog->getUuid());
		relWitsmlLog.setDestinationObjectType();
		result.push_back(relWitsmlLog);
	}

	return result;
}

void WellboreFrameRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	_resqml2__WellboreFrameRepresentation* rep = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);

	// need to do that before AbstractRepresentation::importRelationshipSetFromEpc because the trajectory is used for finding the local crs relationship.
	trajectory = static_cast<WellboreTrajectoryRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->Trajectory->UUID));
	if (trajectory)
		trajectory->addWellboreFrameRepresentation(this);

	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	int valuesType = rep->NodeMd->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		setHdfProxy(static_cast<HdfProxy*>(epcDoc->getResqmlAbstractObjectByUuid(static_cast<resqml2__DoubleHdf5Array*>(rep->NodeMd)->Values->HdfProxy->UUID)));
	}

	if (rep->WitsmlLogReference)
	{
		witsml1_4_1_1::Log* tmp = static_cast<witsml1_4_1_1::Log*>(epcDoc->getWitsmlAbstractObjectByUuid(rep->WitsmlLogReference->UUID));
		if (tmp)
		{
			updateXml = false;
			setWitsmlLog(tmp);
			updateXml = true;
		}
	}
}

void WellboreFrameRepresentation::setMdValuesAsArray1dOfExplicitValues(double * mdValues, const unsigned int & numMdValues, HdfProxy * proxy)
{
	setHdfProxy(proxy);

	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);

	// XML
	resqml2__DoubleHdf5Array* xmlMdValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
	xmlMdValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlMdValues->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlMdValues->Values->PathInHdfFile = "/RESQML/" + frame->uuid + "/mdValues";

	frame->NodeMd = xmlMdValues;

	frame->NodeCount = numMdValues;

	// HDF
	hsize_t dim[] = {numMdValues};
	hdfProxy->writeArrayNd(frame->uuid,
			"mdValues",
			H5::PredType::NATIVE_DOUBLE,
			mdValues,
			dim, 1);
}

unsigned int WellboreFrameRepresentation::getMdValuesCount() const
{
	if (hdfProxy == NULL)
		return 0;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		return hdfProxy->getElementCount(static_cast<resqml2__DoubleHdf5Array*>(
			frame->NodeMd)->Values->PathInHdfFile);
	}

	return 0;
}

AbstractValuesProperty::hdfDatatypeEnum WellboreFrameRepresentation::getMdHdfDatatype() const
{
	if (hdfProxy == NULL)
		return AbstractValuesProperty::UNKNOWN;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		H5::DataType dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->PathInHdfFile);
		if (dt == H5::PredType::NATIVE_DOUBLE)
			return AbstractValuesProperty::DOUBLE;
		else if (dt == H5::PredType::NATIVE_FLOAT)
			return AbstractValuesProperty::FLOAT;
		else if (dt == H5::PredType::NATIVE_LONG)
			return AbstractValuesProperty::LONG;
		else if (dt == H5::PredType::NATIVE_ULONG)
			return AbstractValuesProperty::ULONG;
		else if (dt == H5::PredType::NATIVE_INT)
			return AbstractValuesProperty::INT;
		else if (dt == H5::PredType::NATIVE_UINT)
			return AbstractValuesProperty::UINT;
		else if (dt == H5::PredType::NATIVE_SHORT)
			return AbstractValuesProperty::SHORT;
		else if (dt == H5::PredType::NATIVE_USHORT)
			return AbstractValuesProperty::USHORT;
		else if (dt == H5::PredType::NATIVE_CHAR)
			return AbstractValuesProperty::CHAR;
		else if (dt == H5::PredType::NATIVE_UCHAR)
			return AbstractValuesProperty::UCHAR;
	}

	return AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

void WellboreFrameRepresentation::getMdAsDoubleValues(double * values)
{
	if (hdfProxy == NULL)
		return;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(
			frame->NodeMd)->Values->PathInHdfFile, values);
	}
}

void WellboreFrameRepresentation::getMdAsFloatValues(float *  values)
{
	if (hdfProxy == NULL)
		return;

	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		hdfProxy->readArrayNdOfFloatValues(static_cast<resqml2__DoubleHdf5Array*>(
			frame->NodeMd)->Values->PathInHdfFile, values);
	}
}

std::string WellboreFrameRepresentation::getWellboreTrajectoryUuid() const
{
	return static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy)->Trajectory->UUID;
}

std::string WellboreFrameRepresentation::getLocalCrsUuid() const
{
	return trajectory->getLocalCrsUuid();
}

std::string WellboreFrameRepresentation::getHdfProxyUuid() const
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		return static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->HdfProxy->UUID;
	}
	else
		return "";
}

void WellboreFrameRepresentation::setWitsmlLog(witsml1_4_1_1::Log * witsmlLogToSet)
{
	witsmlLog = witsmlLogToSet;
	witsmlLog->resqmlWellboreFrameRepresentation = this;

	if (updateXml)
	{
		resqml2__obj_USCOREWellboreFrameRepresentation* resqmlLog = static_cast<resqml2__obj_USCOREWellboreFrameRepresentation*>(gsoapProxy);
		resqmlLog->WitsmlLogReference = witsmlLog->newResqmlReference();
	}
}