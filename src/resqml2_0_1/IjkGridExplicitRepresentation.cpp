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
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/AbstractValuesProperty.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;

IjkGridExplicitRepresentation::IjkGridExplicitRepresentation(soap* soapContext, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
			AbstractIjkGridRepresentation(soapContext, crs, guid, title, iCount, jCount, kCount)
{
}

IjkGridExplicitRepresentation::IjkGridExplicitRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(interp, crs, guid, title, iCount, jCount, kCount)
{
}

string IjkGridExplicitRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 IjkGridExplicitRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(patchIndex));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	const unsigned int kNodeCount = getKCellCount() + 1;
	ULONG64 result = (getICellCount() + 1) * (getJCellCount() + 1) * kNodeCount;

	if (geom->SplitCoordinateLines != nullptr) {
		result += geom->SplitCoordinateLines->Count * kNodeCount;
	}
	if (geom->SplitNodes != nullptr) {
		result += geom->SplitNodes->Count;
	}

	return result;
}

void IjkGridExplicitRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	resqml2__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the grid either does not exist or it is not an explicit one.");
}

void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodes(
	const resqml2__PillarShape & mostComplexPillarGeometry,
	const resqml2__KDirection & kDirectionKind,
	const bool & isRightHanded,
	double * points, resqml2::AbstractHdfProxy * proxy,
	const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns)
{
	if (proxy == nullptr) {
		throw invalid_argument("The hdf proxy cannot be null.");
	}
	if (points == nullptr) {
		throw invalid_argument("The points of the ijk grid cannot be null.");
	}
	if (splitCoordinateLineCount != 0 && (pillarOfCoordinateLine == nullptr || splitCoordinateLineColumnCumulativeCount == nullptr || splitCoordinateLineColumns == nullptr)) {
		throw invalid_argument("The definition of the split coordinate lines is incomplete.");
	}

	setHdfProxy(proxy);

	resqml2__IjkGridGeometry* geom = soap_new_resqml2__IjkGridGeometry(gsoapProxy2_0_1->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = mostComplexPillarGeometry;
	geom->KDirection = kDirectionKind;

	// Pillar defined
	resqml2__BooleanConstantArray* definedPillars = soap_new_resqml2__BooleanConstantArray(gsoapProxy2_0_1->soap, 1);
	geom->PillarGeometryIsDefined = definedPillars;
	definedPillars->Count = (getICellCount() + 1) * (getJCellCount() + 1);
	definedPillars->Value = true;

	// XML coordinate lines
	resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/Points";

	if (splitCoordinateLineCount == 0)
	{
		// HDF
		hsize_t * numValues = new hsize_t[4];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = getJCellCount() + 1;
		numValues[2] = getICellCount() + 1;
		numValues[3] = 3; // 3 for X, Y and Z
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 4);
		delete [] numValues;
	}
	else
	{
		// HDF
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;
		numValues[2] = 3; // 3 for X, Y and Z
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 3);
		delete [] numValues;
		
		// XML split coordinate lines
		geom->SplitCoordinateLines = soap_new_resqml2__ColumnLayerSplitCoordinateLines(gsoapProxy2_0_1->soap, 1);;
		geom->SplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		resqml2__IntegerHdf5Array* pillarIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		geom->SplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		pillarIndices->Values->HdfProxy = proxy->newResqmlReference();
		pillarIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/PillarIndices";
		// HDF
		numValues = new hsize_t[1];
		numValues[0] = splitCoordinateLineCount;
		hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
		delete [] numValues;

		//XML
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
		// Cumulative
		resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1] + 1;
		cumulativeLength->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
		cumulativeLength->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME;
		// Elements
		resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		elements->Values->HdfProxy = proxy->newResqmlReference();
		elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME;

		// HDF
		hdfProxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "ColumnsPerSplitCoordinateLine", H5T_NATIVE_UINT, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, H5T_NATIVE_UINT, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}
}

AbstractIjkGridRepresentation::geometryKind IjkGridExplicitRepresentation::getGeometryKind() const
{
	return EXPLICIT;
}
