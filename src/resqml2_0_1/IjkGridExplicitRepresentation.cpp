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
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractFeature.h"
#include "resqml2_0_1/AbstractValuesProperty.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;

IjkGridExplicitRepresentation::IjkGridExplicitRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(epcDoc, crs, guid, title, iCount, jCount, kCount)
{
}

IjkGridExplicitRepresentation::IjkGridExplicitRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(interp, crs, guid, title, iCount, jCount, kCount)
{
}

string IjkGridExplicitRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

unsigned int IjkGridExplicitRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
	{
		_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		unsigned int result = (ijkGrid->Ni+1) * (ijkGrid->Nj+1) * (ijkGrid->Nk+1);

		if (ijkGrid->Geometry->SplitCoordinateLines != NULL)
		{
			result += ijkGrid->Geometry->SplitCoordinateLines->Count * (ijkGrid->Nk+1);
		}

		return result;
	}
	else
		return 0;
}

void IjkGridExplicitRepresentation::setGeometryAsCoordinateLineNodes(
	const resqml2__PillarShape & mostComplexPillarGeometry,
	const resqml2__KDirection & kDirectionKind,
	const bool & isRightHanded,
	double * points, AbstractHdfProxy * proxy,
	const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns)
{
	if (!proxy)
		throw invalid_argument("The hdf proxy cannot be null.");
	if (!points)
		throw invalid_argument("The points of the ijk grid cannot be null.");
	if (splitCoordinateLineCount != 0 && (!pillarOfCoordinateLine || !splitCoordinateLineColumnCumulativeCount || !splitCoordinateLineColumns))
		throw invalid_argument("The definition of the split coordinate lines is incomplete.");

	setHdfProxy(proxy);

	resqml2__IjkGridGeometry* geom = soap_new_resqml2__IjkGridGeometry(gsoapProxy->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry = geom;
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = mostComplexPillarGeometry;
	geom->KDirection = kDirectionKind;

	// Pillar defined
	resqml2__BooleanConstantArray* definedPillars = soap_new_resqml2__BooleanConstantArray(gsoapProxy->soap, 1);
	geom->PillarGeometryIsDefined = definedPillars;
	definedPillars->Count = (getICellCount() + 1) * (getJCellCount() + 1);
	definedPillars->Value = true;

	// XML coordinate lines
	resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/Points";

	if (splitCoordinateLineCount == 0)
	{
		// HDF
		hsize_t * numValues = new hsize_t[4];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = getJCellCount() + 1;
		numValues[2] = getICellCount() + 1;
		numValues[3] = 3; // 3 for X, Y and Z
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "Points", points, numValues, 4);
		delete [] numValues;
	}
	else
	{
		// HDF
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;
		numValues[2] = 3; // 3 for X, Y and Z
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "Points", points, numValues, 3);
		delete [] numValues;
		
		// XML split coordinate lines
		geom->SplitCoordinateLines = soap_new_resqml2__ColumnLayerSplitCoordinateLines(gsoapProxy->soap, 1);;
		geom->SplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		resqml2__IntegerHdf5Array* pillarIndices = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
		geom->SplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		pillarIndices->Values->HdfProxy = proxy->newResqmlReference();
		pillarIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/PillarIndices";
		// HDF
		numValues = new hsize_t[1];
		numValues[0] = splitCoordinateLineCount;
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "PillarIndices", H5T_NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
		delete [] numValues;

		//XML
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
		// Cumulative
		resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1] + 1;
		cumulativeLength->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
		cumulativeLength->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME;
		// Elements
		resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		elements->Values->HdfProxy = proxy->newResqmlReference();
		elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME;

		// HDF
		hdfProxy->writeItemizedListOfUnsignedInt(gsoapProxy->uuid, "ColumnsPerSplitCoordinateLine", splitCoordinateLineColumnCumulativeCount, splitCoordinateLineCount, splitCoordinateLineColumns, splitCoordinateLineColumnCumulativeCount[splitCoordinateLineCount - 1]);
	}
}

void IjkGridExplicitRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	resqml2__PointGeometry* pointGeom = getPointGeometry(patchIndex);
	if (pointGeom)
	{
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
		}
	}
}

AbstractIjkGridRepresentation::geometryKind IjkGridExplicitRepresentation::getGeometryKind() const
{
	return AbstractIjkGridRepresentation::geometryKind::EXPLICIT;
}
