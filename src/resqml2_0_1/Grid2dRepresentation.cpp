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
#include "resqml2_0_1/Grid2dRepresentation.h"

#include <algorithm>
#include <stdexcept>

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* Grid2dRepresentation::XML_TAG = "Grid2dRepresentation";

Grid2dRepresentation::Grid2dRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
	const string & guid, const std::string & title):
	AbstractSurfaceRepresentation(interp, crs), supportingRepresentation(NULL)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREGrid2dRepresentation(interp->getGsoapProxy()->soap, 1);
	_resqml2__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// Surface role
	if (interp->getInterpretedFeature()->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORESeismicLatticeFeature)
		singleGrid2dRep->SurfaceRole = resqml2__SurfaceRole__pick;

	// relationhsips
	setInterpretation(interp);

	localCrs = crs;
	localCrs->addRepresentation(this);

	// epc document
	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

resqml2__PointGeometry* Grid2dRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->Geometry;
	else
		return NULL;
}

string Grid2dRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

unsigned int Grid2dRepresentation::getNodeCountAlongIAxis() const
{
	return static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->FastestAxisCount;
}

unsigned int Grid2dRepresentation::getNodeCountAlongJAxis() const
{
	return static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->SlowestAxisCount;
}

unsigned int Grid2dRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
	{
		return getNodeCountAlongIAxis() * getNodeCountAlongJAxis();
	}
	else
		return 0;
}

void Grid2dRepresentation::getZValues(double* values) const
{
	if (!hdfProxy->isOpened())
		hdfProxy->openForReading();

	_resqml2__Grid2dRepresentation* rep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy);
	resqml2__AbstractDoubleArray* zValues = static_cast<resqml2__Point3dZValueArray*>(rep->Grid2dPatch->Geometry->Points)->ZValues;
	string datasetName = "";
	if (zValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		datasetName = static_cast<resqml2__DoubleHdf5Array*>(zValues)->Values->PathInHdfFile;
	}
	else
	{
		return;
	}

	hdfProxy->readArrayNdOfDoubleValues(datasetName, values);
}

void Grid2dRepresentation::getZValuesInGlobalCrs(double * values) const
{
	getZValues(values);

	if (localCrs->getGsoapProxy()->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
	{
		_resqml2__Grid2dRepresentation* rep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy);
		unsigned int NodeCount = rep->Grid2dPatch->FastestAxisCount * rep->Grid2dPatch->SlowestAxisCount;
		double zOffset = localCrs->getOriginDepthOrElevation();
		if (zOffset != .0)
		{
			for (unsigned int index = 0; index < NodeCount; index++)
				values[index] += zOffset;
		}
	}
}

resqml2__Point3dLatticeArray* Grid2dRepresentation::getArrayLatticeOfPoints3d() const
{
	resqml2__Point3dLatticeArray* result = NULL;

	resqml2__Grid2dPatch* patch = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch;
	if (patch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray)
	{
		result = static_cast<resqml2__Point3dLatticeArray*>(patch->Geometry->Points);
	}
	else if (patch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray)
	{
		resqml2__Point3dZValueArray* arrayOfZValuePoints3d = static_cast<resqml2__Point3dZValueArray*>(patch->Geometry->Points);
		if (arrayOfZValuePoints3d->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray)
		{
			result = static_cast<resqml2__Point3dLatticeArray*>(arrayOfZValuePoints3d->SupportingGeometry);
		}
	}

	return result;
}

double Grid2dRepresentation::getXOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d)
		return arrayLatticeOfPoints3d->Origin->Coordinate1;
	else if (getSupportingRepresentationUuid().size())
	{
		int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		double xOrigin = supportingRepresentation->getXOrigin();

		if (iOrigin != 0 || jOrigin != 0)
		{
			double xIOffset = supportingRepresentation->getXIOffset();
			double xJOffset = supportingRepresentation->getXJOffset();

			return xOrigin + iOrigin*xIOffset + jOrigin*xJOffset;
		}
		else
		{
			return xOrigin;
		}
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getYOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d)
		return arrayLatticeOfPoints3d->Origin->Coordinate2;
	else if (getSupportingRepresentationUuid().size())
	{
		int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		double yOrigin = supportingRepresentation->getYOrigin();

		if (iOrigin != 0 || jOrigin != 0)
		{
			double yIOffset = supportingRepresentation->getYIOffset();
			double yJOffset = supportingRepresentation->getYJOffset();

			return yOrigin + iOrigin*yIOffset + jOrigin*yJOffset;
		}
		else
		{
			return yOrigin;
		}
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getXOriginInGlobalCrs() const
{
	double result = getXOrigin();
	if (result != result)
		return result;

	return result + localCrs->getOriginOrdinal1(); // TODO rotation
}

double Grid2dRepresentation::getYOriginInGlobalCrs() const
{
	double result = getYOrigin();
	if (result != result)
		return result;

	return result + localCrs->getOriginOrdinal2(); // TODO rotation
}

double Grid2dRepresentation::getXJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d)
		return arrayLatticeOfPoints3d->Offset[0]->Offset->Coordinate1;
	else if (getSupportingRepresentationUuid().size())
	{
		return supportingRepresentation->getXJOffset();
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getYJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d)
		return arrayLatticeOfPoints3d->Offset[0]->Offset->Coordinate2;
	else if (getSupportingRepresentationUuid().size())
	{
		return supportingRepresentation->getYJOffset();
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

// TODO rotation
double Grid2dRepresentation::getXJOffsetInGlobalCrs() const
{
	double result = getXJOffset();

	return result;
}

// TODO rotation
double Grid2dRepresentation::getYJOffsetInGlobalCrs() const
{
	double result = getYJOffset();

	return result;
}

double Grid2dRepresentation::getXIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d)
		return arrayLatticeOfPoints3d->Offset[1]->Offset->Coordinate1;
	else if (getSupportingRepresentationUuid().size())
	{
		return supportingRepresentation->getXIOffset();
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getYIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d)
		return arrayLatticeOfPoints3d->Offset[1]->Offset->Coordinate2;
	else if (getSupportingRepresentationUuid().size())
	{
		return supportingRepresentation->getYIOffset();
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

// TODO rotation
double Grid2dRepresentation::getXIOffsetInGlobalCrs() const
{
	double result = getXIOffset();

	return result;
}

// TODO rotation
double Grid2dRepresentation::getYIOffsetInGlobalCrs() const
{
	double result = getYIOffset();

	return result;
}


double Grid2dRepresentation::getJSpacing() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleConstantArray)
		return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
	else if (getSupportingRepresentationUuid().size())
	{
		int jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
		double jSpacingOnSupportingRep = supportingRepresentation->getJSpacing();

		return jIndexOffset * jSpacingOnSupportingRep;
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getISpacing() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleConstantArray)
		return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
	else if (getSupportingRepresentationUuid().size())
	{
		int iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
		double iSpacingOnSupportingRep = supportingRepresentation->getISpacing();

		return iIndexOffset * iIndexOffset;
	}
	else
		return std::numeric_limits<double>::signaling_NaN();
}

void Grid2dRepresentation::setGeometryAsArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection)
{
	resqml2__PointGeometry* geomPatch = createArray2dOfLatticePoints3d(numPointsInFastestDirection, numPointsInSlowestDirection,
			xOrigin, yOrigin, zOrigin,
			xOffsetInFastestDirection, yOffsetInFastestDirection, zOffsetInFastestDirection,
			xOffsetInSlowestDirection, yOffsetInSlowestDirection, zOffsetInSlowestDirection,
			spacingInFastestDirection, spacingInSlowestDirection);

	resqml2__Grid2dPatch* patch = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch;
	patch = soap_new_resqml2__Grid2dPatch(gsoapProxy->soap, 1);
	patch->PatchIndex = 0;
	patch->Geometry = geomPatch;
	patch->SlowestAxisCount = numPointsInSlowestDirection;
	patch->FastestAxisCount = numPointsInFastestDirection;

	static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch = patch;
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
		double * zValues,
		const unsigned int & numI, const unsigned int & numJ, HdfProxy * proxy,
		Grid2dRepresentation * supportingGrid2dRepresentation,
		const unsigned int & startIndexI, const unsigned int & startIndexJ,
		const int & indexIncrementI, const int & indexIncrementJ)
{
	resqml2__Grid2dPatch* patch = soap_new_resqml2__Grid2dPatch(gsoapProxy->soap, 1);
	static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch = patch;

	patch->PatchIndex = 0;
	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	setSupportingRepresentation(supportingGrid2dRepresentation);
	resqml2__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues,
			numI, numJ, proxy,
			supportingGrid2dRepresentation,
			startIndexI + startIndexJ * getNodeCountAlongIAxis(),
			indexIncrementI, indexIncrementJ);
	patch->Geometry = geomPatch;
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, HdfProxy * proxy,
				const double & originX, const double & originY, const double & originZ,
				const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
				const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ)
{
	resqml2__Grid2dPatch* patch = soap_new_resqml2__Grid2dPatch(gsoapProxy->soap, 1);
	static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch = patch;

	patch->PatchIndex = 0;
	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	resqml2__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues,
			numI, numJ, proxy,
			originX, originY, originZ,
			offsetIX, offsetIY, offsetIZ, spacingI,
			offsetJX, offsetJY, offsetJZ, spacingJ);
	patch->Geometry = geomPatch;
}

std::string Grid2dRepresentation::getSupportingRepresentationUuid() const
{
	_resqml2__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy);
	if (singleGrid2dRep && singleGrid2dRep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray)
	{
		resqml2__Point3dZValueArray* tmp = static_cast<resqml2__Point3dZValueArray*>(singleGrid2dRep->Grid2dPatch->Geometry->Points);
		if (tmp->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dFromRepresentationLatticeArray)
		{
			return static_cast<resqml2__Point3dFromRepresentationLatticeArray*>(tmp->SupportingGeometry)->SupportingRepresentation->UUID;
		}
	}

	return "";
}

void Grid2dRepresentation::setSupportingRepresentation(Grid2dRepresentation * supportingRep)
{
	supportingRepresentation = supportingRep;
	supportingRepresentation->supportedRepresentationSet.push_back(this);
}

int Grid2dRepresentation::getIndexOriginOnSupportingRepresentation() const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->Geometry);

	if (geom)
		return geom->NodeIndicesOnSupportingRepresentation->StartValue;
	else
		throw invalid_argument("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getIndexOriginOnSupportingRepresentation(const unsigned int & dimension) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->Geometry);

	if (geom)
	{
		if (dimension == 0) // J dimension : slowest
			return geom->NodeIndicesOnSupportingRepresentation->StartValue / supportingRepresentation->getNodeCountAlongIAxis();
		else if (dimension == 1) // I dimension : fastest
			return geom->NodeIndicesOnSupportingRepresentation->StartValue % supportingRepresentation->getNodeCountAlongIAxis();
		throw invalid_argument("There cannot be more than 2 dimensions for a grid 2d representation.");
	}
	else
		throw invalid_argument("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getNodeCountOnSupportingRepresentation(const unsigned int & dimension) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->Geometry);

	if (geom)
		return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Count + 1;
	else
		throw invalid_argument("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getIndexOffsetOnSupportingRepresentation(const unsigned int & dimension) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy)->Grid2dPatch->Geometry);

	if (geom)
		return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Value;
	else
		throw invalid_argument("It does not exist supporting representation for this representation.");
}

vector<Relationship> Grid2dRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractSurfaceRepresentation::getAllEpcRelationships();

	// Supporting representation
	if (supportingRepresentation && std::find(seismicSupportSet.begin(), seismicSupportSet.end(), supportingRepresentation) == seismicSupportSet.end())
	{
		Relationship relSupportingRepresentation(supportingRepresentation->getPartNameInEpcDocument(), "", supportingRepresentation->getUuid());
		relSupportingRepresentation.setDestinationObjectType();
		result.push_back(relSupportingRepresentation);
	}

	// Supported representations
	for(vector<AbstractRepresentation*>::const_iterator it = supportedRepresentationSet.begin(); it != supportedRepresentationSet.end(); ++it)
	{
		if (it == supportedRepresentationSet.begin() || std::find(supportedRepresentationSet.begin(), it, *it) != supportedRepresentationSet.end()) //  No need to add the rel twice
		{
			Relationship relChildRepresentation((*it)->getPartNameInEpcDocument(), "", (*it)->getUuid());
			relChildRepresentation.setSourceObjectType();
			result.push_back(relChildRepresentation);
		}
	}

	return result;
}

void Grid2dRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractSurfaceRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy);

	// Base representation
	string supportingRepUuid = getSupportingRepresentationUuid();
	if (supportingRepUuid.empty() == false)
		setSupportingRepresentation(static_cast<Grid2dRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(supportingRepUuid)));
}
