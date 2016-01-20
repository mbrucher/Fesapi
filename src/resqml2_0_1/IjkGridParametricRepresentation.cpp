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
#include "resqml2_0_1/IjkGridParametricRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractFeature.h"
#include "resqml2_0_1/AbstractValuesProperty.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;

IjkGridParametricRepresentation::IjkGridParametricRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(epcDoc, crs, guid, title, iCount, jCount, kCount)
{
}

IjkGridParametricRepresentation::IjkGridParametricRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(interp, crs, guid, title, iCount, jCount, kCount)
{
}

unsigned int IjkGridParametricRepresentation::getControlPointMaxCountPerPillar() const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		return static_cast<resqml2__ParametricLineArray*>(points->ParametricLines)->KnotCount;
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getControlPoints(double * controlPoints, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPoints->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(paramLineArray->ControlPoints)->Coordinates->PathInHdfFile, controlPoints);
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * getControlPointMaxCountPerPillar() * 3;

		// Copy in order not to modify the controlPoints pointer
		double * reversedControlPoints = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			reversedControlPoints[index] = controlPoints[index];
		}

		if (reverseIAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = getICellCount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
						controlPoints[controlPointIndex*3] = reversedControlPoints[reversedControlPointIndex*3];
						controlPoints[controlPointIndex*3 + 1] = reversedControlPoints[reversedControlPointIndex*3 + 1];
						controlPoints[controlPointIndex*3 + 2] = reversedControlPoints[reversedControlPointIndex*3 + 2];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = i + (getJCellCount() - j)*iPillarCount + k*iPillarCount*jPillarCount;
						controlPoints[controlPointIndex*3] = reversedControlPoints[reversedControlPointIndex*3];
						controlPoints[controlPointIndex*3 + 1] = reversedControlPoints[reversedControlPointIndex*3 + 1];
						controlPoints[controlPointIndex*3 + 2] = reversedControlPoints[reversedControlPointIndex*3 + 2];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseKAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = i + j*iPillarCount + (getControlPointMaxCountPerPillar()-1-k)*iPillarCount*jPillarCount;
						controlPoints[controlPointIndex*3] = reversedControlPoints[reversedControlPointIndex*3];
						controlPoints[controlPointIndex*3 + 1] = reversedControlPoints[reversedControlPointIndex*3 + 1];
						controlPoints[controlPointIndex*3 + 2] = reversedControlPoints[reversedControlPointIndex*3 + 2];
						++controlPointIndex;
					}
				}
			}
		}

		delete [] reversedControlPoints;
	}
}

bool IjkGridParametricRepresentation::hasControlPointParameters() const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		return paramLineArray->ControlPointParameters != nullptr;
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getControlPointParameters(double * controlPointParameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPointParameters == nullptr)
			throw invalid_argument("The grid does not contain any control point parameters.");
		if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(paramLineArray->ControlPointParameters)->Values->PathInHdfFile, controlPointParameters);
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");
	
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * getControlPointMaxCountPerPillar();

		// Copy in order not to modify the controlPoints pointer
		double * reversedControlPointParameters = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			reversedControlPointParameters[index] = controlPointParameters[index];
		}

		if (reverseIAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = getICellCount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = i + (getJCellCount() - j)*iPillarCount + k*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		if (reverseKAxis)
		{
			unsigned int controlPointIndex = 0;
			for (unsigned int k = 0; k < getControlPointMaxCountPerPillar(); ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						unsigned int reversedControlPointIndex = i + j*iPillarCount + (getControlPointMaxCountPerPillar()-1-k)*iPillarCount*jPillarCount;
						controlPointParameters[controlPointIndex] = reversedControlPointParameters[reversedControlPointIndex];
						++controlPointIndex;
					}
				}
			}
		}

		delete [] reversedControlPointParameters;
	}
}

void IjkGridParametricRepresentation::getParametricLineKind(short * pillarKind, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values->PathInHdfFile, pillarKind);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			const LONG64 value =
				static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			const ULONG64 lineKindCount =
				static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
			if( lineKindCount != getPillarCount() )
			{
				throw invalid_argument("The parametric line kind count is inconsistent with the pillar count.");
			}
			for (unsigned int i = 0; i < lineKindCount; ++i)
			{
				pillarKind[i] = (short)value;
			}
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		double * initialPillarKind = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialPillarKind[index] = pillarKind[index];
		}

		if (reverseIAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarKind[pillarIndex] = initialPillarKind[getICellCount() - i + j*iPillarCount];
					++pillarIndex;
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarKind[pillarIndex] = initialPillarKind[i + (getJCellCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}

		delete [] initialPillarKind;
	}
}

void IjkGridParametricRepresentation::getParametersOfNodes(double * parameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(points->Parameters)->Values->PathInHdfFile, parameters);
	}
	else
		throw std::logic_error("Not yet implemented");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int kNodeCount = getKCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount * kNodeCount + getSplitCoordinateLineCount()*kNodeCount;
		double * initialParameters = new double [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialParameters[index] = parameters[index];
		}

		if (reverseIAxis)
		{
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						parameters[nodeIndex] = initialParameters[getICellCount() - i + j*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		if (reverseJAxis)
		{
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						parameters[nodeIndex] = initialParameters[i + (getJCellCount() -j)*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		if (reverseKAxis)
		{
			unsigned int nodeIndex = 0;
			for (unsigned int k = 0; k < kNodeCount; ++k)
			{
				for (unsigned int j = 0; j < jPillarCount; ++j)
				{
					for (unsigned int i = 0; i < iPillarCount; ++i)
					{
						parameters[nodeIndex] = initialParameters[i + j*iPillarCount + (getKCellCount() - k)*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		delete [] initialParameters;
	}
}

string IjkGridParametricRepresentation::getHdfProxyUuid() const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		return static_cast<resqml2__DoubleHdf5Array*>(points->Parameters)->Values->HdfProxy->UUID;
	}
	else
		throw std::logic_error("Not yet implemented");
}

ULONG64 IjkGridParametricRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
	{
		_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		ULONG64 result = (ijkGrid->Ni+1) * (ijkGrid->Nj+1) * (ijkGrid->Nk+1);

		if (ijkGrid->Geometry->SplitCoordinateLines != nullptr)
		{
			result += ijkGrid->Geometry->SplitCoordinateLines->Count * (ijkGrid->Nk+1);
		}

		return result;
	}
	else
		return 0;
}

void IjkGridParametricRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	resqml2__PointGeometry* pointGeom = getPointGeometry(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dParametricArray)
	{
		getXyzPointsOfPatchFromParametricPoints(static_cast<resqml2__Point3dParametricArray*>(pointGeom->Points), xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the grid either does not exist or it is not a parametric one.");
}

void IjkGridParametricRepresentation::setGeometryAsParametricNonSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class AbstractHdfProxy * proxy)
{
	setGeometryAsParametricSplittedPillarNodes(mostComplexPillarGeometry, kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, proxy,
		0, nullptr, nullptr, nullptr);
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class AbstractHdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns)
{
	if (!proxy)
		throw invalid_argument("The hdf proxy cannot be null.");
	if (!parameters)
		throw invalid_argument("The parameters of the nodes of the ijk grid cannot be null.");
	if (!controlPoints)
		throw invalid_argument("The control points of the coordinate lines of the ijk grid cannot be null.");
	if (controlPointMaxCountPerPillar<1)
		throw invalid_argument("The max count of control points per coordinate line of the ijk grid cannot be less than one.");
	if (!pillarKind)
		throw invalid_argument("the kind of the coordinate lines cannot be null.");
	if (splitCoordinateLineCount != 0 && (!pillarOfCoordinateLine || !splitCoordinateLineColumnCumulativeCount || !splitCoordinateLineColumns))
		throw invalid_argument("The definition of the split coordinate lines is incomplete.");

	setHdfProxy(proxy);

	resqml2__IjkGridGeometry* geom = soap_new_resqml2__IjkGridGeometry(gsoapProxy->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry = geom;
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = mostComplexPillarGeometry;
	geom->KDirection = kDirectionKind;

	// XML Pillar defined
	resqml2__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml2__BooleanHdf5Array(gsoapProxy->soap, 1);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/PillarGeometryIsDefined";

	// HDF Pillar defined
	unsigned char * definedPillars = new unsigned char[(getJCellCount() + 1) * (getICellCount() + 1)];
	for (unsigned int i = 0; i < (getJCellCount() + 1) * (getICellCount() + 1); ++i)
		if (pillarKind[i] == -1) definedPillars[i] = 0; else definedPillars[i] = 1;
	hsize_t * pillarGeometryIsDefinedCount = new hsize_t[2];
	pillarGeometryIsDefinedCount[0] = getJCellCount() + 1;
	pillarGeometryIsDefinedCount[1] = getICellCount() + 1;
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "PillarGeometryIsDefined", H5T_NATIVE_UCHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
	delete [] pillarGeometryIsDefinedCount;
	delete [] definedPillars;

	// XML parametric nodes
	resqml2__Point3dParametricArray* xmlPoints = soap_new_resqml2__Point3dParametricArray(gsoapProxy->soap, 1);
	geom->Points = xmlPoints;
	resqml2__DoubleHdf5Array* xmlParameters = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
	xmlPoints->Parameters = xmlParameters;
	xmlParameters->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlParameters->Values->HdfProxy = proxy->newResqmlReference();
	xmlParameters->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/PointParameters";

	if (splitCoordinateLineCount == 0)
	{
		// HDF
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = getJCellCount() + 1;
		numValues[2] = getICellCount() + 1;
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "PointParameters", parameters, numValues, 3);
		delete [] numValues;
	}
	else
	{
		// HDF
		hsize_t * numValues = new hsize_t[2];
		numValues[0] = getKCellCount() + 1;
		numValues[1] = (getJCellCount() + 1) * (getICellCount() + 1) + splitCoordinateLineCount;
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "PointParameters", parameters, numValues, 2);
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

	// *********************************
	// Parametric coordinate lines
	// *********************************
	resqml2__ParametricLineArray* paramLines = soap_new_resqml2__ParametricLineArray(gsoapProxy->soap, 1);
	xmlPoints->ParametricLines = paramLines;
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml2__IntegerHdf5Array* xmlLineKinds = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/LineKindIndices";

	// HDF Line kinds
	hsize_t * lineKindCount = new hsize_t[2];
	lineKindCount[0] = getJCellCount() + 1;
	lineKindCount[1] = getICellCount() + 1;
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "LineKindIndices", H5T_NATIVE_SHORT, pillarKind, lineKindCount, 2);
	delete [] lineKindCount;

	// XML control points
	resqml2__Point3dHdf5Array* xmlcontrolPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy->soap, 1);
	paramLines->ControlPoints = xmlcontrolPoints;
	xmlcontrolPoints->Coordinates = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlcontrolPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlcontrolPoints->Coordinates->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/ControlPoints";

	// HDF control points
	hsize_t * controlPointCount = new hsize_t[4];
	controlPointCount[0] = controlPointMaxCountPerPillar;
	controlPointCount[1] = getJCellCount() + 1;
	controlPointCount[2] = getICellCount() + 1;
	controlPointCount[3] = 3; // 3 for X, Y and Z
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "ControlPoints", H5T_NATIVE_DOUBLE, controlPoints, controlPointCount, 4);
	delete [] controlPointCount;

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (controlPointParameters)
	{
		// XML control point parameters
		resqml2__DoubleHdf5Array* xmlcontrolPointParams = soap_new_resqml2__DoubleHdf5Array(gsoapProxy->soap, 1);
		paramLines->ControlPointParameters = xmlcontrolPointParams;
		xmlcontrolPointParams->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		xmlcontrolPointParams->Values->HdfProxy = proxy->newResqmlReference();
		xmlcontrolPointParams->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/controlPointParameters";

		// HDF control points parameters
		hsize_t * controlPointParamCount = new hsize_t[3];
		controlPointParamCount[0] = controlPointMaxCountPerPillar;
		controlPointParamCount[1] = getJCellCount() + 1;
		controlPointParamCount[2] = getICellCount() + 1;
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "controlPointParameters", H5T_NATIVE_DOUBLE, controlPointParameters, controlPointParamCount, 3);
		delete [] controlPointParamCount;
	}
}

void IjkGridParametricRepresentation::getXyzPointsOfPatchFromParametricPoints(gsoap_resqml2_0_1::resqml2__Point3dParametricArray* parametricPoint3d, double * xyzPoints) const
{
	ULONG64 xyzPointCount = getXyzPointCountOfPatch(0);

	// parameters : ordered
	double * parameters = new double[xyzPointCount];
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values->PathInHdfFile, parameters);
	}
	else
		throw logic_error("Not yet implemented");

	if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ParametricLineArray)
	{
		resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(parametricPoint3d->ParametricLines);
		unsigned int maxControlPointCount = getControlPointMaxCountPerPillar();
		unsigned int parametricLineCount = getPillarCount();
		unsigned int splitLineCount = getSplitCoordinateLineCount();

		// Control points
		double * controlPoints = new double[parametricLineCount*maxControlPointCount*3];
		getControlPoints(controlPoints);

		// Control points parameters
		double * controlPointParameters = nullptr;
		if (paramLineArray->ControlPointParameters != nullptr)
		{
			controlPointParameters = new double[parametricLineCount*maxControlPointCount];
			getControlPointParameters(controlPointParameters);
		}

		// Line kind indices
		short * pillarKind = new short[parametricLineCount];
		getParametricLineKind(pillarKind);

		// Pillars of split line
		unsigned int* pillarOfSplitCoordLines = nullptr;
		if (splitLineCount > 0)
		{
			pillarOfSplitCoordLines = new unsigned int [splitLineCount];
			getPillarsOfSplitCoordinateLines(pillarOfSplitCoordLines);
		}

		//Mapping
		unsigned int paramIndex = 0;
		for (unsigned int kInterface = 0; kInterface < getKCellCount() + 1; ++kInterface)
		{
			for (unsigned int coordLineIndex = 0; coordLineIndex < parametricLineCount; ++coordLineIndex)
			{
				if (pillarKind[coordLineIndex] == -1) // not defined line
				{
					xyzPoints[paramIndex*3] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[paramIndex*3+1] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[paramIndex*3+2] = std::numeric_limits<double>::quiet_NaN();
				}
				else if (pillarKind[coordLineIndex] == 0) // vertical (parameter must be the Z value)
				{
					xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3];
					xyzPoints[paramIndex*3+1] = controlPoints[coordLineIndex*3+1];
					xyzPoints[paramIndex*3+2] = parameters[paramIndex];
				}
				else if (pillarKind[coordLineIndex] == 1) // linear interpolation
				{
					unsigned int controlPointCount = 0;
					while (controlPointCount < maxControlPointCount &&
						controlPoints[(coordLineIndex + controlPointCount*parametricLineCount)*3] == controlPoints[(coordLineIndex + controlPointCount*parametricLineCount)*3])
					{
						controlPointCount++;
					}

					// Control point count on this line
					if (controlPointCount == 2) // straight
					{
						double ratioFromFirstControlPoint = .0;
						double parameterDistance = .0;
						if (controlPointParameters != nullptr)
						{
							parameterDistance = controlPointParameters[coordLineIndex + parametricLineCount] - controlPointParameters[coordLineIndex]; // Parameter distance from top to bottom.
							if (parameterDistance != .0)
								ratioFromFirstControlPoint = (parameters[paramIndex] - controlPointParameters[coordLineIndex]) / parameterDistance;
						}
						else // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						{
							parameterDistance = controlPoints[(coordLineIndex + parametricLineCount)*3+2] - controlPoints[coordLineIndex*3+2]; // Parameter distance from top to bottom.
							if (parameterDistance != .0)
								ratioFromFirstControlPoint = (parameters[paramIndex] - controlPoints[coordLineIndex*3+2]) / parameterDistance;
						}
						xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount)*3] - controlPoints[coordLineIndex*3]);
						xyzPoints[paramIndex*3 + 1] = controlPoints[coordLineIndex*3 + 1] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount)*3 + 1] - controlPoints[coordLineIndex*3 + 1]);
						xyzPoints[paramIndex*3 + 2] = controlPoints[coordLineIndex*3 + 2] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount)*3 + 2] - controlPoints[coordLineIndex*3 + 2]);
					}
					else // piecewise linear
					{
						throw logic_error("Piecewise linear pillars are not yet implemented");
					}
				}
				else
					throw logic_error("Not yet implemented");
				++paramIndex;
			}
			for (unsigned int splitLineIndex = 0; splitLineIndex < splitLineCount; ++splitLineIndex)
			{
				unsigned int coordLineIndex = pillarOfSplitCoordLines[splitLineIndex];
				if (pillarKind[coordLineIndex] == -1) // not defined line
				{
					xyzPoints[paramIndex*3] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[paramIndex*3+1] = std::numeric_limits<double>::quiet_NaN();
					xyzPoints[paramIndex*3+2] = std::numeric_limits<double>::quiet_NaN();
				}
				else if (pillarKind[coordLineIndex] == 0) // vertical (parameter must be the Z value)
				{
					xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3];
					xyzPoints[paramIndex*3+1] = controlPoints[coordLineIndex*3+1];
					xyzPoints[paramIndex*3+2] = parameters[paramIndex];
				}
				else if (pillarKind[coordLineIndex] == 1) // Linear interpolation
				{
					unsigned int controlPointCount = 0;
					while (controlPointCount < maxControlPointCount &&
						controlPoints[(coordLineIndex + controlPointCount*parametricLineCount)*3] == controlPoints[(coordLineIndex + controlPointCount*parametricLineCount)*3])
					{
						controlPointCount++;
					}

					// Control point count on this line
					if (controlPointCount == 2) // straight
					{
						double ratioFromFirstControlPoint = .0;
						double parameterDistance = .0;
						if (controlPointParameters != nullptr)
						{
							parameterDistance = controlPointParameters[coordLineIndex + parametricLineCount] - controlPointParameters[coordLineIndex]; // Parameter distance from top to bottom.
							if (parameterDistance != .0)
								ratioFromFirstControlPoint = (parameters[paramIndex] - controlPointParameters[coordLineIndex]) / parameterDistance;
						}
						else // Should never occur by business rule. Assume the parameters are Z values for now (workaround for some softwares)....
						{
							parameterDistance = controlPoints[(coordLineIndex + parametricLineCount)*3+2] - controlPoints[coordLineIndex*3+2]; // Parameter distance from top to bottom.
							if (parameterDistance != .0)
								ratioFromFirstControlPoint = (parameters[paramIndex] - controlPoints[coordLineIndex*3+2]) / parameterDistance;
						}

						xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount)*3] - controlPoints[coordLineIndex*3]);
						xyzPoints[paramIndex*3 + 1] = controlPoints[coordLineIndex*3 + 1] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount)*3 + 1] - controlPoints[coordLineIndex*3 + 1]);
						xyzPoints[paramIndex*3 + 2] = controlPoints[coordLineIndex*3 + 2] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount)*3 + 2] - controlPoints[coordLineIndex*3 + 2]);
					}
					else // piecewise linear
					{
						// Cleaning
						delete [] controlPoints;
						delete [] pillarKind;
						if (pillarOfSplitCoordLines != nullptr)
							delete [] pillarOfSplitCoordLines;
						if (controlPointParameters != nullptr)
							delete [] controlPointParameters;
						delete [] parameters;
						throw logic_error("Piecewise linear pillars are not yet implemented");
					}
				}
				else
				{
					// Cleaning
					delete [] controlPoints;
					delete [] pillarKind;
					if (pillarOfSplitCoordLines != nullptr)
						delete [] pillarOfSplitCoordLines;
					if (controlPointParameters != nullptr)
						delete [] controlPointParameters;
					delete [] parameters;
					throw logic_error("Not yet implemented");
				}
				++paramIndex;
			}
		}

		// Cleaning
		delete [] controlPoints;
		delete [] pillarKind;
		if (pillarOfSplitCoordLines != nullptr)
			delete [] pillarOfSplitCoordLines;
		if (controlPointParameters != nullptr)
			delete [] controlPointParameters;
	}
	else
	{
		delete [] parameters;
		throw logic_error("Not yet implemented");
	}

	delete [] parameters;
}

AbstractIjkGridRepresentation::geometryKind IjkGridParametricRepresentation::getGeometryKind() const
{
	return PARAMETRIC;
}
