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
#include "resqml2_0/IjkGridRepresentation.h"

#include <stdexcept>

#include "resqml2_0/AbstractFeatureInterpretation.h"
#include "resqml2_0/AbstractLocal3dCrs.h"
#include "resqml2_0/AbstractFeature.h"
#include "resqml2_0/AbstractValuesProperty.h"
#include "resqml2_0/HdfProxy.h"
//#include "Vector3d.h"

using namespace std;
using namespace gsoap_resqml2_0;
using namespace resqml2_0;

const char* IjkGridRepresentation::XML_TAG = "IjkGridRepresentation";

void IjkGridRepresentation::init(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount)
{
	if (epcDoc == nullptr)
		throw invalid_argument("The EPC document where the ijk grid will be stored cannot be null.");
	if (crs == nullptr)
		throw invalid_argument("The local CRS of the IJK Grid cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREIjkGridRepresentation(epcDoc->getGsoapContext(), 1);
	_resqml2__IjkGridRepresentation* ijkGrid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);

	ijkGrid->Ni = iCount;
	ijkGrid->Nj = jCount;
	ijkGrid->Nk = kCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// epc document
	epcDoc->addGsoapProxy(this);

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);
}

IjkGridRepresentation::IjkGridRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(nullptr, crs)
{
	init(epcDoc, crs, guid, title, iCount, jCount, kCount);
}

IjkGridRepresentation::IjkGridRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractColumnLayerGridRepresentation(interp, crs)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the IJK grid cannot be null.");

	init(interp->getEpcDocument(), crs, guid, title, iCount, jCount, kCount);

	// relationhsips
	setInterpretation(interp);
}

bool IjkGridRepresentation::hasParametricGeometry() const
{
	return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__Point3dParametricArray;
}

bool IjkGridRepresentation::isASeismicCube() const
{
	// A Seismic cube is defined by an IjkGridRepresentation that has a feature of type SeismicLatticeFeature and that
	// has at least one continuous property (amplitude).
	bool atLeastOneContProp = false;
    vector<AbstractValuesProperty*> allValuesProperty = getValuesPropertySet();
    for (unsigned int propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__obj_USCOREContinuousProperty)
        {
            atLeastOneContProp = true;
            break;
        }
    }
    if (!atLeastOneContProp)
        return false;

	return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__obj_USCORESeismicLatticeFeature;
}

bool IjkGridRepresentation::isAFaciesCube() const
{
	// A Facies cube is defined by an IjkGridRepresentation that has a feature of type SeismicLatticeFeature and that
	// has at least one categorical property (facies).
	bool atLeastOneCateProp = false;
    vector<AbstractValuesProperty*> allValuesProperty = getValuesPropertySet();
    for (unsigned int propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__obj_USCORECategoricalProperty)
        {
            atLeastOneCateProp = true;
            break;
        }
    }
    if (!atLeastOneCateProp)
        return false;

	return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__obj_USCORESeismicLatticeFeature;
}

gsoap_resqml2_0::resqml2__PointGeometry* IjkGridRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry;
	else
		return NULL;
}

void IjkGridRepresentation::getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines == NULL)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->PillarIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->PillarIndices)->Values->PathInHdfFile, pillarIndices);
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICount()+1;
		unsigned int jPillarCount = getJCount()+1;
		if (reverseIAxis)
		{
			for (unsigned int index = 0; index < getSplitCoordinateLineCount(); ++index)
			{
				unsigned int iPillar = pillarIndices[index] % iPillarCount;
				unsigned int jPillar = pillarIndices[index] / iPillarCount;
				pillarIndices[index] = (getICount() - iPillar) + jPillar*iPillarCount;
			}
		}
		if (reverseJAxis)
		{
			for (unsigned int index = 0; index < getSplitCoordinateLineCount(); ++index)
			{
				unsigned int iPillar = pillarIndices[index] % iPillarCount;
				unsigned int jPillar = pillarIndices[index] / iPillarCount;
				pillarIndices[index] = iPillar + (getJCount()-jPillar)*iPillarCount;
			}
		}
	}
}

void IjkGridRepresentation::getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines == NULL)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile, columnIndices);
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int datasetValueCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile);
		if (reverseIAxis)
		{
			for (unsigned int index = 0; index < datasetValueCount; ++index)
			{
				unsigned int iColumn = columnIndices[index] % getICount();
				unsigned int jColumn = columnIndices[index] / getICount();
				columnIndices[index] = (getICount() - 1 - iColumn) + jColumn*getICount();
			}
		}
		if (reverseJAxis)
		{
			for (unsigned int index = 0; index < datasetValueCount; ++index)
			{
				unsigned int iColumn = columnIndices[index] % getICount();
				unsigned int jColumn = columnIndices[index] / getICount();
				columnIndices[index] = iColumn + (getJCount() - 1 - jColumn)*getICount();
			}
		}
	}
}

void IjkGridRepresentation::getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines == NULL)
		throw invalid_argument("There is no split coordinate line in this grid.");
	if (grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength)->Values->PathInHdfFile, columnIndexCountPerSplitCoordinateLine);
	}
	else
		throw std::logic_error("Not yet implemented");
}

unsigned int IjkGridRepresentation::getControlPointMaxCountPerPillar() const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__ParametricLineArray)
		{
			return static_cast<resqml2__ParametricLineArray*>(points->ParametricLines)->KnotCount;
		}
		else
			throw std::logic_error("Not yet implemented");
	}

	return 0;
}

void IjkGridRepresentation::getControlPoints(double * controlPoints, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__ParametricLineArray)
		{
			resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
			if (paramLineArray->ControlPoints->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__Point3dHdf5Array)
			{
				hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(paramLineArray->ControlPoints)->Coordinates->PathInHdfFile, controlPoints);
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw invalid_argument("The grid is not a parametric one.");

	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICount()+1;
		unsigned int jPillarCount = getJCount()+1;
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
						unsigned int reversedControlPointIndex = getICount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
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
						unsigned int reversedControlPointIndex = i + (getJCount() - j)*iPillarCount + k*iPillarCount*jPillarCount;
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

bool IjkGridRepresentation::isRightHanded() const
{
	if (static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry)
		return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry->GridIsRighthanded;
	else
		throw invalid_argument("The grid has no geometry.");
}

bool IjkGridRepresentation::hasControlPointParameters() const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__ParametricLineArray)
		{
			resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
			return paramLineArray->ControlPointParameters != NULL;
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw invalid_argument("The grid is not a parametric one.");
}

void IjkGridRepresentation::getControlPointParameters(double * controlPointParameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__ParametricLineArray)
		{
			resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
			if (paramLineArray->ControlPointParameters == NULL)
				throw invalid_argument("The grid does not contain any control point parameters.");
			if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
			{
				hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(paramLineArray->ControlPointParameters)->Values->PathInHdfFile, controlPointParameters);
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw invalid_argument("The grid is not a parametric one.");

	
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICount()+1;
		unsigned int jPillarCount = getJCount()+1;
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
						unsigned int reversedControlPointIndex = getICount() - i + j*iPillarCount + k*iPillarCount*jPillarCount;
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
						unsigned int reversedControlPointIndex = i + (getJCount() - j)*iPillarCount + k*iPillarCount*jPillarCount;
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

void IjkGridRepresentation::getParametricLineKind(short * pillarKind, bool reverseIAxis, bool reverseJAxis) const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__ParametricLineArray)
		{
			resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(points->ParametricLines);
			if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
			{
				hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values->PathInHdfFile, pillarKind);
			} else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerConstantArray)
			{
				const unsigned int value = 
					static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
				const unsigned int lineKindCount = 
					static_cast<resqml2__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
				if( lineKindCount != ((getICount() + 1) * (getJCount() + 1)) ) {
					throw invalid_argument("3D Grid not initialized properly.");
				}
				std::fill(pillarKind, pillarKind+lineKindCount, value);
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw invalid_argument("The grid is not a parametric one.");

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICount()+1;
		unsigned int jPillarCount = getJCount()+1;
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
					pillarKind[pillarIndex] = initialPillarKind[getICount() - i + j*iPillarCount];
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
					pillarKind[pillarIndex] = initialPillarKind[i + (getJCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}

		delete [] initialPillarKind;
	}
}

void IjkGridRepresentation::getParametersOfNodes(double * parameters, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(points->Parameters)->Values->PathInHdfFile, parameters);
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw invalid_argument("The grid is not a parametric one.");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int iPillarCount = getICount()+1;
		unsigned int jPillarCount = getJCount()+1;
		unsigned int kNodeCount = getKCount()+1;
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
						parameters[nodeIndex] = initialParameters[getICount() - i + j*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
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
						parameters[nodeIndex] = initialParameters[i + (getJCount() -j)*iPillarCount + k*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
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
						parameters[nodeIndex] = initialParameters[i + j*iPillarCount + (getKCount() - k)*(jPillarCount*iPillarCount+getSplitCoordinateLineCount())];
						++nodeIndex;
					}
				}
				nodeIndex += getSplitCoordinateLineCount();
			}
		}

		delete [] initialParameters;
	}
}

void IjkGridRepresentation::getCellGeometryIsDefined(bool * cellGeometryIsDefined, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry)
	{
		unsigned int cellCount = getKCount() * getJCount() * getICount();
		if (grid->Geometry->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__BooleanHdf5Array)
		{
			if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_CHAR)
			{
				char* tmp = new char[cellCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < cellCount; i++)
					if (tmp[i] == 0) cellGeometryIsDefined[i] = false; else cellGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_UCHAR)
			{
				unsigned char* tmp = new unsigned char[cellCount];
				hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < cellCount; i++)
					if (tmp[i] == 0) cellGeometryIsDefined[i] = false; else cellGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else if (grid->Geometry->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__BooleanConstantArray)
		{
			if (static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->CellGeometryIsDefined)->Value == true)
				for (unsigned int i = 0; i < cellCount; i++)
					cellGeometryIsDefined[i] = true;
			else
				for (unsigned int i = 0; i < cellCount; i++)
					cellGeometryIsDefined[i] = false;
		}
		else
			throw std::logic_error("Not yet implemented");
		}
	else
		throw invalid_argument("The grid has no geometry.");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis)
	{
		unsigned int arrayCount = getICount() * getJCount() * getKCount();
		bool * initialCellGeometryIsDefined = new bool [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialCellGeometryIsDefined[index] = cellGeometryIsDefined[index];
		}

		if (reverseIAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCount(); ++j)
				{
					for (unsigned int i = 0; i < getICount(); ++i)
					{
						cellGeometryIsDefined[cellIndex] = initialCellGeometryIsDefined[getICount() - 1 - i + j*getICount() + k*getICount()*getJCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCount(); ++j)
				{
					for (unsigned int i = 0; i < getICount(); ++i)
					{
						cellGeometryIsDefined[cellIndex] = initialCellGeometryIsDefined[i + (getJCount() - 1 -j)*getICount() + k*getICount()*getJCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseKAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCount(); ++j)
				{
					for (unsigned int i = 0; i < getICount(); ++i)
					{
						cellGeometryIsDefined[cellIndex] = initialCellGeometryIsDefined[i + j*getICount() + (getKCount() - 1 -k)*getICount()*getJCount()];
						++cellIndex;
					}
				}
			}
		}

		delete [] initialCellGeometryIsDefined;
	}
}

void IjkGridRepresentation::getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry)
	{
		unsigned int pillarCount = (getJCount() + 1) * (getICount() + 1);
		if (grid->Geometry->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__BooleanHdf5Array)
		{
			if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_CHAR)
			{
				char* tmp = new char[pillarCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; i++)
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else if (hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile) == H5::PredType::NATIVE_UCHAR)
			{
				unsigned char* tmp = new unsigned char[pillarCount];
				hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; i++)
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				delete [] tmp;
			}
			else
				throw std::logic_error("Not yet implemented");
		}
		else if (grid->Geometry->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__BooleanConstantArray)
		{
			if (static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->PillarGeometryIsDefined)->Value == true)
				for (unsigned int i = 0; i < pillarCount; i++)
					pillarGeometryIsDefined[i] = true;
			else
				for (unsigned int i = 0; i < pillarCount; i++)
					pillarGeometryIsDefined[i] = false;
		}
		else
			throw std::logic_error("Not yet implemented");
		}
	else
		throw invalid_argument("The grid has no geometry.");

	

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICount()+1;
		unsigned int jPillarCount = getJCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		bool * initialPillarGeometryIsDefined = new bool [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialPillarGeometryIsDefined[index] = pillarGeometryIsDefined[index];
		}

		if (reverseIAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[getICount() - i + j*iPillarCount];
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
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[i + (getJCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}

		delete [] initialPillarGeometryIsDefined;
	}
}

string IjkGridRepresentation::getHdfProxyUuid() const
{
	if (hasParametricGeometry())
	{
		_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
		resqml2__Point3dParametricArray* points = static_cast<resqml2__Point3dParametricArray*>(grid->Geometry->Points);
		if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
		{
			return static_cast<resqml2__DoubleHdf5Array*>(points->Parameters)->Values->HdfProxy->UUID;
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

unsigned int IjkGridRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
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

unsigned long IjkGridRepresentation::getSplitCoordinateLineCount() const
{
	_resqml2__IjkGridRepresentation* grid = static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy);
	if (grid->Geometry->SplitCoordinateLines)
	{
		return grid->Geometry->SplitCoordinateLines->Count;
	}
	else
		return 0;
}

unsigned int IjkGridRepresentation::getICount() const
{
	return (int)static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Ni;
}

void IjkGridRepresentation::setICount(const unsigned int & iCount)
{
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Ni = iCount;
}

unsigned int IjkGridRepresentation::getJCount() const
{
	return (int)static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Nj;
}

void IjkGridRepresentation::setJCount(const unsigned int & jCount)
{
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Nj = jCount;
}

resqml2__Point3dLatticeArray* IjkGridRepresentation::getArrayLatticeOfPoints3d() const
{
    resqml2__Point3dLatticeArray* result = NULL;

    resqml2__PointGeometry* ptGeom = getPointGeometry(0);
    if (ptGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__Point3dLatticeArray)
    {
        result = static_cast<resqml2__Point3dLatticeArray*>(ptGeom->Points);
    }

    return result;
}

double IjkGridRepresentation::getXOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getXOriginInGlobalCrs() const
{
	double result = getXOrigin();
	if (result != result)
		return result;

	return result + localCrs->getOriginOrdinal1(); // TODO rotation
}

double IjkGridRepresentation::getYOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getYOriginInGlobalCrs() const
{
	double result = getYOrigin();
	if (result != result)
		return result;

	return result + localCrs->getOriginOrdinal2(); // TODO rotation
}

double IjkGridRepresentation::getZOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getZOriginInGlobalCrs() const
{
	double result = getZOrigin();
	if (result != result || localCrs->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__obj_USCORELocalTime3dCrs)
		return result;

	return result + localCrs->getOriginDepthOrElevation();
}

double IjkGridRepresentation::getXIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[0]->Offset->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getYIOffset() const
{
    resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[0]->Offset->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getZIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[0]->Offset->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getXJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[1]->Offset->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getYJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[1]->Offset->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getZJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[1]->Offset->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getXKOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[2]->Offset->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getYKOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[2]->Offset->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getZKOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[2]->Offset->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getISpacing() const
{
    resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
        return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getJSpacing() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
        return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridRepresentation::getKSpacing() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[2]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
        return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[2]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

int IjkGridRepresentation::getOriginInline() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
		return (int)static_cast<resqml2__DoubleLatticeArray*>(s3c->InlineCoordinates)->StartValue;
	else
		return 0;
}

int IjkGridRepresentation::getOriginCrossline() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
		return (int)static_cast<resqml2__DoubleLatticeArray*>(s3c->CrosslineCoordinates)->StartValue;
	else
		return 0;
}

int IjkGridRepresentation::getInlineIOffset() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
	{
		resqml2__DoubleLatticeArray* dla = static_cast<resqml2__DoubleLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[0]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
		{
			return (int)static_cast<resqml2__DoubleConstantArray*>(dla->Offset[0])->Value;
		}
	}

	return 0;
}

int IjkGridRepresentation::getInlineJOffset() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
	{
		resqml2__DoubleLatticeArray* dla = static_cast<resqml2__DoubleLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[1]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
		{
			return (int)static_cast<resqml2__DoubleConstantArray*>(dla->Offset[1])->Value;
		}
	}

	return 0;
}

int IjkGridRepresentation::getInlineKOffset() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
	{
		resqml2__DoubleLatticeArray* dla = static_cast<resqml2__DoubleLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[2]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
		{
			return (int)static_cast<resqml2__DoubleConstantArray*>(dla->Offset[2])->Value;
		}
	}

	return 0;
}

int IjkGridRepresentation::getCrosslineIOffset() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
	{
		resqml2__DoubleLatticeArray* dla = static_cast<resqml2__DoubleLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[0]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
		{
			return (int)static_cast<resqml2__DoubleConstantArray*>(dla->Offset[0])->Value;
		}
	}

	return 0;
}

int IjkGridRepresentation::getCrosslineJOffset() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
	{
		resqml2__DoubleLatticeArray* dla = static_cast<resqml2__DoubleLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[1]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
		{
			return (int)static_cast<resqml2__DoubleConstantArray*>(dla->Offset[1])->Value;
		}
	}

	return 0;
}

int IjkGridRepresentation::getCrosslineKOffset() const
{
	resqml2__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleLatticeArray)
	{
		resqml2__DoubleLatticeArray* dla = static_cast<resqml2__DoubleLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[2]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleConstantArray)
		{
			return (int)static_cast<resqml2__DoubleConstantArray*>(dla->Offset[2])->Value;
		}
	}

	return 0;
}

void IjkGridRepresentation::setGeometryAsCoordinateLineNodes(
	const resqml2__PillarShape & mostComplexPillarGeometry,
	const resqml2__KDirection & kDirectionKind,
	const bool & isRightHanded,
	double * points, HdfProxy * proxy,
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
	definedPillars->Count = (getICount() + 1) * (getJCount() + 1);
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
		numValues[0] = getKCount() + 1;
		numValues[1] = getJCount() + 1;
		numValues[2] = getICount() + 1;
		numValues[3] = 3; // 3 for X, Y and Z
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "Points", points, numValues, 4);
		delete [] numValues;
	}
	else
	{
		// HDF
		hsize_t * numValues = new hsize_t[3];
		numValues[0] = getKCount() + 1;
		numValues[1] = (getJCount() + 1) * (getICount() + 1) + splitCoordinateLineCount;
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
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "PillarIndices", H5::PredType::NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
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

void IjkGridRepresentation::setGeometryAsParametricNonSplittedPillarNodes(
			const gsoap_resqml2_0::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class HdfProxy * proxy,
			unsigned char* cellGeomIsDefined)
{
	setGeometryAsParametricSplittedPillarNodes(mostComplexPillarGeometry, kDirectionKind, isRightHanded, parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, pillarKind, proxy,
		0, NULL, NULL, NULL, cellGeomIsDefined);
}

void IjkGridRepresentation::setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class HdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns,
			unsigned char* cellGeomIsDefined)
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
	unsigned char * definedPillars = new unsigned char[(getJCount() + 1) * (getICount() + 1)];
	for (unsigned int i = 0; i < (getJCount() + 1) * (getICount() + 1); ++i)
		if (pillarKind[i] == -1) definedPillars[i] = 0; else definedPillars[i] = 1;
	hsize_t * pillarGeometryIsDefinedCount = new hsize_t[2];
	pillarGeometryIsDefinedCount[0] = getJCount() + 1;
	pillarGeometryIsDefinedCount[1] = getICount() + 1;
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "PillarGeometryIsDefined", H5::PredType::NATIVE_UCHAR, definedPillars, pillarGeometryIsDefinedCount, 2);
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
		numValues[0] = getKCount() + 1;
		numValues[1] = getJCount() + 1;
		numValues[2] = getICount() + 1;
	
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy->uuid, "PointParameters", parameters, numValues, 3);
		delete [] numValues;
	}
	else
	{
		// HDF
		hsize_t * numValues = new hsize_t[2];
		numValues[0] = getKCount() + 1;
		numValues[1] = (getJCount() + 1) * (getICount() + 1) + splitCoordinateLineCount;
	
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
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "PillarIndices", H5::PredType::NATIVE_UINT, pillarOfCoordinateLine, numValues, 1);
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
	lineKindCount[0] = getJCount() + 1;
	lineKindCount[1] = getICount() + 1;
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "LineKindIndices", H5::PredType::NATIVE_SHORT, pillarKind, lineKindCount, 2);
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
	controlPointCount[1] = getJCount() + 1;
	controlPointCount[2] = getICount() + 1;
	controlPointCount[3] = 3; // 3 for X, Y and Z
	hdfProxy->writeArrayNd(gsoapProxy->uuid, "ControlPoints", H5::PredType::NATIVE_DOUBLE, controlPoints, controlPointCount, 4);
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
		controlPointParamCount[1] = getJCount() + 1;
		controlPointParamCount[2] = getICount() + 1;
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "controlPointParameters", H5::PredType::NATIVE_DOUBLE, controlPointParameters, controlPointParamCount, 3);
		delete [] controlPointParamCount;
	}

	// *********************************
	// Cell geometry is defined
	// *********************************
	if (cellGeomIsDefined)
	{
		resqml2__BooleanHdf5Array* boolArray = soap_new_resqml2__BooleanHdf5Array(gsoapProxy->soap, 1);
		geom->CellGeometryIsDefined = boolArray;
		
		boolArray->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
		boolArray->Values->HdfProxy = proxy->newResqmlReference();
		boolArray->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/CellGeometryIsDefined";

		// HDF
		hsize_t * cellGeometryIsDefinedCount = new hsize_t[3];
		cellGeometryIsDefinedCount[0] = getKCount();
		cellGeometryIsDefinedCount[1] = getJCount();
		cellGeometryIsDefinedCount[2] = getICount();
		hdfProxy->writeArrayNd(gsoapProxy->uuid, "CellGeometryIsDefined", H5::PredType::NATIVE_UCHAR, cellGeomIsDefined, cellGeometryIsDefinedCount, 3);
		delete [] cellGeometryIsDefinedCount;
	}
}

void IjkGridRepresentation::setGeometryAsCoordinateLineNodes(
	const resqml2__PillarShape & mostComplexPillarGeometry,
	const resqml2__KDirection & kDirectionKind,
	const bool & isRightHanded,
	const double & originX, const double & originY, const double & originZ,
	const double & directionIX, const double & directionIY, const double & directionIZ, const double & spacingI,
	const double & directionJX, const double & directionJY, const double & directionJZ, const double & spacingJ,
	const double & directionKX, const double & directionKY, const double & directionKZ, const double & spacingK)
{
	resqml2__IjkGridGeometry* geom = soap_new_resqml2__IjkGridGeometry(gsoapProxy->soap, 1);
	geom->LocalCrs = localCrs->newResqmlReference();
	static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy)->Geometry = geom;
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = mostComplexPillarGeometry;
	geom->KDirection = kDirectionKind;

	// Pillar defined
	resqml2__BooleanConstantArray* definedPillars = soap_new_resqml2__BooleanConstantArray(gsoapProxy->soap, 1);
	geom->PillarGeometryIsDefined = definedPillars;
	definedPillars->Count = (getICount() + 1) * (getJCount() + 1);
	definedPillars->Value = true;

	// XML coordinate lines
	resqml2__Point3dLatticeArray* xmlPoints = soap_new_resqml2__Point3dLatticeArray(gsoapProxy->soap, 1);
	geom->Points = xmlPoints;

	xmlPoints->AllDimensionsAreOrthogonal = (bool*)soap_malloc(gsoapProxy->soap, sizeof(bool));
	*xmlPoints->AllDimensionsAreOrthogonal = true;
	xmlPoints->Origin = soap_new_resqml2__Point3d(gsoapProxy->soap, 1);
	xmlPoints->Origin->Coordinate1 = originX;
	xmlPoints->Origin->Coordinate2 = originY;
	xmlPoints->Origin->Coordinate3 = originZ;

	// slowest axis to fastest axis so k,j,i 
	resqml2__Point3dOffset * dimK = soap_new_resqml2__Point3dOffset (gsoapProxy->soap, 1);
	xmlPoints->Offset.push_back(dimK);
	// the dimension is the index of the axis in the collection. here we start from 0 and goes up by 1
	dimK->Offset = soap_new_resqml2__Point3d(gsoapProxy->soap, 1);
	dimK->Offset->Coordinate1 = directionKX;
	dimK->Offset->Coordinate2 = directionKY;
	dimK->Offset->Coordinate3 = directionKZ;
	resqml2__DoubleConstantArray * xmlSpacingK = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	dimK->Spacing = xmlSpacingK;
	xmlSpacingK->Count = getKCount(); // number of cells on K axis
	xmlSpacingK->Value = spacingK;
	
	resqml2__Point3dOffset * dimJ = soap_new_resqml2__Point3dOffset (gsoapProxy->soap, 1);
	xmlPoints->Offset.push_back(dimJ);
	// the dimension is the index of the axis in the collection
	dimJ->Offset = soap_new_resqml2__Point3d(gsoapProxy->soap, 1);
	dimJ->Offset->Coordinate1 = directionJX;
	dimJ->Offset->Coordinate2 = directionJY;
	dimJ->Offset->Coordinate3 = directionJZ;
	resqml2__DoubleConstantArray * xmlSpacingJ = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	dimJ->Spacing = xmlSpacingJ;
	xmlSpacingJ->Count = getJCount(); // number of cells on J axis
	xmlSpacingJ->Value = spacingJ;

	resqml2__Point3dOffset * dimI = soap_new_resqml2__Point3dOffset (gsoapProxy->soap, 1);
	xmlPoints->Offset.push_back(dimI);
	// the dimension is the index of the axis in the collection
	dimI->Offset = soap_new_resqml2__Point3d(gsoapProxy->soap, 1);
	dimI->Offset->Coordinate1 = directionIX;
	dimI->Offset->Coordinate2 = directionIY;
	dimI->Offset->Coordinate3 = directionIZ;
	resqml2__DoubleConstantArray * xmlSpacingI = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	dimI->Spacing = xmlSpacingI;
	xmlSpacingI->Count = getICount(); // number of cells on I axis
	xmlSpacingI->Value = spacingI;

	return;
}

void IjkGridRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	resqml2__PointGeometry* pointGeom = getPointGeometry(patchIndex);
	if (pointGeom)
	{
		if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__Point3dHdf5Array)
		{
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
		}
		else if (pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__Point3dParametricArray)
		{
			resqml2__Point3dParametricArray* parametricPoint3d = static_cast<resqml2__Point3dParametricArray*>(pointGeom->Points);
			unsigned int xyzPointCount = getXyzPointCountOfPatch(patchIndex);

			// parameters : ordered
			double * parameters = new double[xyzPointCount];
			if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__DoubleHdf5Array)
			{
				hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values->PathInHdfFile, parameters);
			}
			else
				throw logic_error("Not yet implemented");

			if (parametricPoint3d->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__ParametricLineArray)
			{
				resqml2__ParametricLineArray* paramLineArray = static_cast<resqml2__ParametricLineArray*>(parametricPoint3d->ParametricLines);
				unsigned int maxControlPointCount = getControlPointMaxCountPerPillar();
				unsigned int parametricLineCount = (getICount() + 1) * (getJCount() + 1);
				unsigned int splitLineCount = getSplitCoordinateLineCount();
				
				// Control points
				double * controlPoints = new double[parametricLineCount*maxControlPointCount*3];
				getControlPoints(controlPoints);

				// Control points parameters
				double * controlPointParameters = NULL;
				if (paramLineArray->ControlPointParameters)
				{
					controlPointParameters = new double[parametricLineCount*maxControlPointCount];
					getControlPointParameters(controlPointParameters);
				}

				// Line kind indices
				short * pillarKind = new short[parametricLineCount];
				getParametricLineKind(pillarKind);

				// Pillars of split line
				unsigned int* pillarOfSplitCoordLines = new unsigned int [splitLineCount];
				getPillarsOfSplitCoordinateLines(pillarOfSplitCoordLines);

				//Mapping
				unsigned int paramIndex = 0;
				for (unsigned int kInterface = 0; kInterface < getKCount() + 1; ++kInterface)
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
								controlPoints[coordLineIndex*3 + controlPointCount*(parametricLineCount+splitLineCount)*3] == controlPoints[coordLineIndex*3 + controlPointCount*(parametricLineCount+splitLineCount)*3])
							{
								controlPointCount++;
							}

							// Control point count on this line
							if (controlPointCount == 2) // straight
							{
								double ratioFromFirstControlPoint = (parameters[paramIndex] - controlPointParameters[coordLineIndex*3]) / (controlPointParameters[coordLineIndex + (parametricLineCount+splitLineCount)] - controlPointParameters[coordLineIndex]);
								xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3] + ratioFromFirstControlPoint * (controlPoints[coordLineIndex + parametricLineCount+splitLineCount] - controlPoints[coordLineIndex]);
								xyzPoints[paramIndex*3 + 1] = controlPoints[coordLineIndex*3 + 1] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount+splitLineCount)*3 + 1] - controlPoints[coordLineIndex*3 + 1]);
								xyzPoints[paramIndex*3 + 2] = controlPoints[coordLineIndex*3 + 2] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount+splitLineCount)*3 + 2] - controlPoints[coordLineIndex*3 + 2]);
							}
							else // piecewise linear
							{
								throw logic_error("Not yet implemented");
							}
						}
						else
							throw logic_error("Not yet implemented");
						paramIndex++;
					}
					for (unsigned int splitLineIndex = 0; splitLineIndex < splitLineCount; ++splitLineIndex)
					{
						unsigned int coordLineIndex = pillarOfSplitCoordLines[splitLineIndex];
						if (pillarKind[pillarOfSplitCoordLines[coordLineIndex]] == -1) // not defined line
						{
							xyzPoints[paramIndex*3] = std::numeric_limits<double>::quiet_NaN();
							xyzPoints[paramIndex*3+1] = std::numeric_limits<double>::quiet_NaN();
							xyzPoints[paramIndex*3+2] = std::numeric_limits<double>::quiet_NaN();
						}
						else if (pillarKind[pillarOfSplitCoordLines[coordLineIndex]] == 0) // vertical (parameter must be the Z value)
						{
							xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3];
							xyzPoints[paramIndex*3+1] = controlPoints[coordLineIndex*3+1];
							xyzPoints[paramIndex*3+2] = parameters[paramIndex];
						}
						else if (pillarKind[coordLineIndex] == 1) // piecewiselinear
						{
							unsigned int controlPointCount = 0;
							while (controlPointCount < maxControlPointCount &&
								controlPoints[coordLineIndex*3 + controlPointCount*(parametricLineCount+splitLineCount)*3] == controlPoints[coordLineIndex*3 + controlPointCount*(parametricLineCount+splitLineCount)*3])
							{
								controlPointCount++;
							}

							// Control point count on this line
							if (controlPointCount == 2) // straight
							{
								double ratioFromFirstControlPoint = (parameters[paramIndex] - controlPointParameters[coordLineIndex*3]) / (controlPointParameters[coordLineIndex + (parametricLineCount+splitLineCount)] - controlPointParameters[coordLineIndex]);
								xyzPoints[paramIndex*3] = controlPoints[coordLineIndex*3] + ratioFromFirstControlPoint * (controlPoints[coordLineIndex + parametricLineCount+splitLineCount] - controlPoints[coordLineIndex]);
								xyzPoints[paramIndex*3 + 1] = controlPoints[coordLineIndex*3 + 1] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount+splitLineCount)*3 + 1] - controlPoints[coordLineIndex*3 + 1]);
								xyzPoints[paramIndex*3 + 2] = controlPoints[coordLineIndex*3 + 2] + ratioFromFirstControlPoint * (controlPoints[(coordLineIndex + parametricLineCount+splitLineCount)*3 + 2] - controlPoints[coordLineIndex*3 + 2]);
							}
							else // piecewise linear
							{
								throw logic_error("Not yet implemented");
							}
						}
						else
							throw logic_error("Not yet implemented");
						paramIndex++;
					}
				}

				// Cleaning
				delete [] controlPoints;
				delete [] pillarKind;
				if (controlPointParameters)
					delete [] controlPointParameters;
			}
			else
				throw logic_error("Not yet implemented");

			delete [] parameters;
		}
	}
}

void IjkGridRepresentation::addSeismic3dCoordinatesToPatch(
								const unsigned int patchIndex,
								const double & startInline, const double & incrInline, const unsigned int & countInline,
								const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
								const unsigned int & countSample, AbstractRepresentation * seismicSupport)
{
	resqml2__PointGeometry* geom = getPointGeometry(patchIndex);
	if (!geom)
		throw invalid_argument("The patchIndex does not identify a point geometry.");

	if (geom->SeismicCoordinates == NULL)
		geom->SeismicCoordinates = soap_new_resqml2__Seismic3dCoordinates(gsoapProxy->soap, 1);
	else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__Seismic2dCoordinates)
		throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
	resqml2__Seismic3dCoordinates* patch = static_cast<resqml2__Seismic3dCoordinates*>(geom->SeismicCoordinates);

	patch->SeismicSupport = seismicSupport->newResqmlReference();
	pushBackSeismicSupport(seismicSupport);

	// inlines XML
	resqml2__DoubleLatticeArray* inlineValues = soap_new_resqml2__DoubleLatticeArray(gsoapProxy->soap, 1);
	inlineValues->StartValue = startInline;

	resqml2__DoubleConstantArray * IoffsetInline = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	IoffsetInline->Count = countInline - 1;
	IoffsetInline->Value = incrInline;
	inlineValues->Offset.push_back(IoffsetInline);

	resqml2__DoubleConstantArray * IoffsetCrossline = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	IoffsetCrossline->Count = countCrossline -1;
	IoffsetCrossline->Value = 0;
	inlineValues->Offset.push_back(IoffsetCrossline);

	resqml2__DoubleConstantArray * IoffsetSample = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	IoffsetSample->Count = countSample -1;
	IoffsetSample->Value = 0;
	inlineValues->Offset.push_back(IoffsetSample);

	patch->InlineCoordinates = inlineValues;

	// crosslines XML
	resqml2__DoubleLatticeArray* crosslineValues = soap_new_resqml2__DoubleLatticeArray(gsoapProxy->soap, 1);
	crosslineValues->StartValue = startCrossline;

	resqml2__DoubleConstantArray * CoffsetInline = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	CoffsetInline->Count = countInline - 1;
	CoffsetInline->Value = 0;
	crosslineValues->Offset.push_back(CoffsetInline);
	resqml2__DoubleConstantArray * CoffsetCrossline = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	CoffsetCrossline->Count = countCrossline - 1;
	CoffsetCrossline->Value = incrCrossline;
	crosslineValues->Offset.push_back(CoffsetCrossline);
	resqml2__DoubleConstantArray * CoffsetSample = soap_new_resqml2__DoubleConstantArray(gsoapProxy->soap, 1);
	CoffsetSample->Count = countSample - 1;
	CoffsetSample->Value = 0;
	crosslineValues->Offset.push_back(CoffsetSample);

	patch->CrosslineCoordinates = crosslineValues;
}
