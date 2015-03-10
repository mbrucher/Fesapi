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
#include "resqml2_0/Grid2dSetRepresentation.h"

#include <algorithm>

#include "resqml2_0/AbstractFeature.h"
#include "resqml2_0/AbstractFeatureInterpretation.h"
#include "resqml2_0/Grid2dRepresentation.h"
#include "resqml2_0/AbstractLocal3dCrs.h"
#include "resqml2_0/HdfProxy.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;
using namespace epc;

const char* Grid2dSetRepresentation::XML_TAG = "Grid2dSetRepresentation";

Grid2dSetRepresentation::Grid2dSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
	const string & guid, const string & title):
	AbstractSurfaceRepresentation(interp, crs)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREGrid2dSetRepresentation(interp->getGsoapProxy()->soap, 1);
	_resqml2__Grid2dSetRepresentation* grid2dSetRep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy);
	
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

unsigned int Grid2dSetRepresentation::getNodeCountAlongIAxis(const unsigned int & patchIndex) const
{
	return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->FastestAxisCount;
}

unsigned int Grid2dSetRepresentation::getNodeCountAlongJAxis(const unsigned int & patchIndex) const
{
	return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->SlowestAxisCount;
}

resqml2__PointGeometry* Grid2dSetRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex < static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch.size())
		return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->Geometry;
	else
		return NULL;
}

string Grid2dSetRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

void Grid2dSetRepresentation::getZValuesOfPatch(const unsigned int & patchIndex, double* values) const
{
	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__Grid2dSetRepresentation* rep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy);
	resqml2__AbstractDoubleArray* zValues = static_cast<resqml2__Point3dZValueArray*>(rep->Grid2dPatch[patchIndex]->Geometry->Points)->ZValues;
	string datasetName = "";
	if (zValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
	{
		datasetName = static_cast<resqml2__DoubleHdf5Array*>(zValues)->Values->PathInHdfFile;
	}
	else
	{
		return;
	}

	hdfProxy->readArrayNdOfDoubleValues(datasetName, values);
}

void Grid2dSetRepresentation::getZValuesOfPatchInGlobalCrs(const unsigned int & patchIndex, double* values) const
{
	getZValuesOfPatch(patchIndex, values);

	if (localCrs->getGsoapProxy()->soap_type() != SOAP_TYPE_gsoap_resqml2_0_resqml2__obj_USCORELocalTime3dCrs)
	{
		_resqml2__Grid2dSetRepresentation* rep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy);
		unsigned int NodeCount = rep->Grid2dPatch[patchIndex]->FastestAxisCount * rep->Grid2dPatch[patchIndex]->SlowestAxisCount;
		double zOffset = localCrs->getOriginDepthOrElevation();
		if (zOffset != .0)
		{
			for (unsigned int index = 0; index < NodeCount; index++)
				values[index] += zOffset;
		}
	}
}

unsigned int Grid2dSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch.size();
}

void Grid2dSetRepresentation::pushBackGeometryPatch(double * zValues,
				const unsigned int & numI, const unsigned int & numJ, HdfProxy * proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI, const unsigned int & startIndexJ,
				const int & indexIncrementI, const int & indexIncrementJ)
{
	resqml2__Grid2dPatch* patch = soap_new_resqml2__Grid2dPatch(gsoapProxy->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch.size();
	static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch.push_back(patch);

	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	supportingRepresentationSet.push_back(supportingGrid2dRepresentation);
	supportingGrid2dRepresentation->supportedRepresentationSet.push_back(this);
	resqml2__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues,
			numI, numJ, proxy,
			supportingGrid2dRepresentation,
			startIndexI + startIndexJ * numI,
			indexIncrementI, indexIncrementJ);
	patch->Geometry = geomPatch;
}

std::string Grid2dSetRepresentation::getSupportingRepresentationUuid(const unsigned int & patchIndex) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->Geometry);
	
	if (geom)
	{
		return geom->SupportingRepresentation->UUID;
	}
	else
	{
		return "";
	}
}

int Grid2dSetRepresentation::getIndexOriginOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const
{
	int result = 0;

	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->Geometry);

	if (geom)
	{
		if (dimension == 0) // J dimension : slowest
			result = geom->NodeIndicesOnSupportingRepresentation->StartValue / getNodeCountAlongIAxis(patchIndex);
		else if (dimension == 1) // I dimension : fastest
			result = geom->NodeIndicesOnSupportingRepresentation->StartValue % getNodeCountAlongIAxis(patchIndex);
	}

	return result;
}

int Grid2dSetRepresentation::getNodeCountOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const
{
	int result = 0;

	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->Geometry);

	if (geom)
		result = geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Count + 1;

	return result;
}

int Grid2dSetRepresentation::getIndexOffsetOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const
{
	int result = 0;

	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy)->Grid2dPatch[patchIndex]->Geometry);

	if (geom)
		result = geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Value;

	return result;
}

vector<Relationship> Grid2dSetRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractSurfaceRepresentation::getAllEpcRelationships();

	// Supporting representations
	for(vector<Grid2dRepresentation*>::const_iterator it = supportingRepresentationSet.begin(); it != supportingRepresentationSet.end(); ++it)
	{
		if (std::find(seismicSupportSet.begin(), seismicSupportSet.end(), *it) == seismicSupportSet.end() &&
			(it == supportingRepresentationSet.begin() || std::find(supportingRepresentationSet.begin(), it, *it) != supportingRepresentationSet.end())) //  No need to add the rel twice
		{
			Relationship relSupportingRepresentation((*it)->getPartNameInEpcDocument(), "", (*it)->getUuid());
			relSupportingRepresentation.setDestinationObjectType();
			result.push_back(relSupportingRepresentation);
		}
	}

	return result;
}

void Grid2dSetRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractSurfaceRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__Grid2dSetRepresentation* grid2dSetRep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy);

	// Supporting representation
	for (unsigned int patchIndex = 0; patchIndex < grid2dSetRep->Grid2dPatch.size(); ++patchIndex)
	{
		string supportingRepUuid = getSupportingRepresentationUuid(patchIndex);
		if (supportingRepUuid.empty() == false)
		{
			Grid2dRepresentation* supportingGrid2dRepresentation = static_cast<Grid2dRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(supportingRepUuid));
			supportingRepresentationSet.push_back(supportingGrid2dRepresentation);
			supportingGrid2dRepresentation->supportedRepresentationSet.push_back(this);
		}
	}
}
