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
#include "resqml2_0_1/GridConnectionSetRepresentation.h"

#if defined(__gnu_linux__) || defined(__APPLE__) 
#include <stdexcept>
#endif 

#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/AbstractGridRepresentation.h"
#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* GridConnectionSetRepresentation::XML_TAG = "GridConnectionSetRepresentation";

GridConnectionSetRepresentation::GridConnectionSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
        const string & guid, const string & title,
		AbstractGridRepresentation * supportingGridRep):
	AbstractRepresentation(interp, crs)
{
    gsoapProxy = soap_new_resqml2__obj_USCOREGridConnectionSetRepresentation(interp->getGsoapProxy()->soap, 1);
    _resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);
    
    initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "", "");
    
	// relationshsips
	setInterpretation(interp);
	setSupportingGridRepresentation(supportingGridRep);
	
	// epc document
	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

void GridConnectionSetRepresentation::setCellIndexPairs(const unsigned int & cellIndexPairCount, unsigned int * cellIndexPair, const unsigned int & nullValue, HdfProxy * proxy)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);
	rep->Count = cellIndexPairCount;

	setHdfProxy(proxy);

	// XML
	resqml2__IntegerHdf5Array* integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
    eml__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
    resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/CellIndexPairs";
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	rep->CellIndexPairs = integerArray;

	// ************ HDF ************		
	hsize_t numValues[] = {cellIndexPairCount,2};
	hdfProxy->writeArrayNd(rep->uuid, "CellIndexPairs", H5::PredType::NATIVE_UINT, cellIndexPair, numValues, 2);
}

void GridConnectionSetRepresentation::setLocalFacePerCellIndexPairs(const unsigned int & cellIndexPairCount, unsigned int * LocalFacePerCellIndexPair, const unsigned int & nullValue, HdfProxy * proxy)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	setHdfProxy(proxy);

	// XML
	resqml2__IntegerHdf5Array* integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
    eml__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
    resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/LocalFacePerCellIndexPairs";
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = nullValue;
	rep->LocalFacePerCellIndexPairs = integerArray;

	// ************ HDF ************		
	hsize_t numValues[] = {cellIndexPairCount,2};
	hdfProxy->writeArrayNd(rep->uuid, "LocalFacePerCellIndexPairs", H5::PredType::NATIVE_UINT, LocalFacePerCellIndexPair, numValues, 2);
}

string GridConnectionSetRepresentation::getHdfProxyUuid() const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		return static_cast<resqml2__IntegerHdf5Array*>(rep->CellIndexPairs)->Values->HdfProxy->UUID;
	}
	else
		throw std::logic_error("Not yet implemented");

	return "";
}

unsigned int GridConnectionSetRepresentation::getCellIndexPairCount() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy)->Count;
}

unsigned int GridConnectionSetRepresentation::getCellIndexPairCountFromFaultIndex(const unsigned int & faultIndex) const
{
	unsigned int result = 0;
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->ConnectionInterpretations)
	{
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			unsigned int faultIndexCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile);
			unsigned int * faultIndices = new unsigned int[faultIndexCount];

			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile, faultIndices);
			for (unsigned int i = 0; i < faultIndexCount; ++i)
				if (faultIndices[i] == faultIndex) result++;

			delete [] faultIndices;
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
	{
		throw invalid_argument("The grid connection does not contain any fault association."); 
	}

	return result;
}

void GridConnectionSetRepresentation::getCellIndexPairFromFaultIndex(unsigned int * cellIndexPair, const unsigned int & faultIndex) const
{
	unsigned int result = 0;

	unsigned int * totalCellIndexPair = new unsigned int[getCellIndexPairCount()];
	getCellIndexPair(totalCellIndexPair);

	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->ConnectionInterpretations)
	{
		unsigned int * faultIndices = NULL;
		if (rep->ConnectionInterpretations->InterpretationIndices->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			unsigned int faultIndexCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile);
			faultIndices = new unsigned int[faultIndexCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->Elements)->Values->PathInHdfFile, faultIndices);
		}
		else
		{
			delete [] totalCellIndexPair;
			throw std::logic_error("Not yet implemented");
		}

		unsigned int * cumulativeCount = NULL;
		if (rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			cumulativeCount = new unsigned int[getCellIndexPairCount()];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength)->Values->PathInHdfFile, cumulativeCount);
		}
		else
		{
			delete [] totalCellIndexPair;
			delete [] faultIndices;
			throw std::logic_error("Not yet implemented");
		}

		unsigned int cellIndexPairIndex = 0;
		unsigned int j = 0;
		for (unsigned int i = 0; i < getCellIndexPairCount(); ++i)
		{
			for (; j < cumulativeCount[i]; ++j)
			{
				if (faultIndices[j] == faultIndex)
				{
					cellIndexPair[cellIndexPairIndex*2] = totalCellIndexPair[i*2];
					cellIndexPair[cellIndexPairIndex*2+1] = totalCellIndexPair[i*2+1];
					++cellIndexPairIndex;
					break;
				}
			}
		}

		delete [] faultIndices;
		delete [] cumulativeCount;
	}
	else
	{
		delete [] totalCellIndexPair;
		throw invalid_argument("The grid connection does not contain any fault association."); 
	}
	
	delete [] totalCellIndexPair;
}

std::string GridConnectionSetRepresentation::getFaultInterpretationUuidFromFaultIndex(const unsigned int & faultIndex) const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->ConnectionInterpretations)
	{
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > faultIndex)
		{
			if (rep->ConnectionInterpretations->FeatureInterpretation[faultIndex]->ContentType.find("FaultInterpretation") != string::npos)
			{
				return rep->ConnectionInterpretations->FeatureInterpretation[faultIndex]->UUID;
			}
			else
			{
				throw invalid_argument("The associated feature interpretation is not a fault one. Legal but not yet implemented.");
			}
		}
		else
		{
			throw range_error("The fault index is out of range in this grid connection context.");
		}
	}
	else
	{
		throw invalid_argument("The grid connection does not contain any fault association.");
	}
}

FaultInterpretation* GridConnectionSetRepresentation::getFaultInterpretationFromFaultIndex(const unsigned int & faultIndex) const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->ConnectionInterpretations)
	{
		if (rep->ConnectionInterpretations->FeatureInterpretation.size() > faultIndex)
		{
			AbstractObject* result = epcDocument->getResqmlAbstractObjectByUuid(rep->ConnectionInterpretations->FeatureInterpretation[faultIndex]->UUID);
			if (result->getGsoapProxy()->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREFaultInterpretation)
			{
				return static_cast<FaultInterpretation*>(result);
			}
			else
			{
				throw invalid_argument("The associated feature interpretation is not a fault one. Legal but not yet implemented.");
			}
		}
		else
		{
			throw range_error("The fault index is out of range in this grid connection context.");
		}
	}
	else
	{
		throw invalid_argument("The grid connection does not contain any fault association.");
	}
}

unsigned int GridConnectionSetRepresentation::getFaultInterpretationCount() const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->ConnectionInterpretations)
	{
		return rep->ConnectionInterpretations->FeatureInterpretation.size();
	}
	else
	{
		return 0;
	}
}

void GridConnectionSetRepresentation::getCellIndexPair(unsigned int * cellIndexPair) const
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	if (rep->CellIndexPairs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->CellIndexPairs)->Values->PathInHdfFile, cellIndexPair);
	}
	else
		throw std::logic_error("Not yet implemented");
}

vector<Relationship> GridConnectionSetRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	Relationship rel(supportingGridRepresentation->getPartNameInEpcDocument(), "", supportingGridRepresentation->getUuid());
	rel.setDestinationObjectType();
	result.push_back(rel);
    
	return result;
}

void GridConnectionSetRepresentation::setSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep)
{
	if (!supportingGridRep)
		throw invalid_argument("The supporting Grid Representation cannot be null.");

	// EPC
	supportingGridRepresentation = supportingGridRep;
	supportingGridRepresentation->gridConnectionSetRepresentationSet.push_back(this);

	// XMl
	if (updateXml)
	{
		static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy)->Grid.push_back(supportingGridRep->newResqmlReference());
	}
}

std::string GridConnectionSetRepresentation::getSupportingGridRepresentationUuid() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy)->Grid[0]->UUID;
}

void GridConnectionSetRepresentation::setConnectionFaultNames(unsigned int * faultIndices, const unsigned int & faultIndiceCount, const unsigned int & nullValue, HdfProxy * proxy)
{
	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);
	rep->ConnectionInterpretations = soap_new_resqml2__ConnectionInterpretations(gsoapProxy->soap, 1);
	rep->ConnectionInterpretations->InterpretationIndices = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy->soap, 1);
	
	// Cumulative
	resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	rep->ConnectionInterpretations->InterpretationIndices->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = nullValue;
	cumulativeLength->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/InterpretationIndices/" + CUMULATIVE_LENGTH_DS_NAME;
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	rep->ConnectionInterpretations->InterpretationIndices->Elements = elements;
	elements->NullValue = nullValue;
	elements->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/InterpretationIndices/" + ELEMENTS_DS_NAME;

	// HDF
	unsigned int * cumulative = new unsigned int[faultIndiceCount];
	for (unsigned int i = 0; i < faultIndiceCount; ++i)
		cumulative[i] = i+1;
	hdfProxy->writeItemizedListOfUnsignedInt(gsoapProxy->uuid, "InterpretationIndices", cumulative, faultIndiceCount, faultIndices, faultIndiceCount);
	delete [] cumulative;
}

void GridConnectionSetRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__GridConnectionSetRepresentation* rep = static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy);

	// Supporting grid representation
	//for (unsigned int i = 0; i < rep->Grid.size(); ++i)
	if (rep->Grid.size() > 0)
	{
		updateXml = false;
		setSupportingGridRepresentation(static_cast<AbstractGridRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->Grid[0]->UUID)));
		updateXml = true;
	}
}

unsigned int GridConnectionSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	throw logic_error("Not yet implemented.");
}

unsigned int GridConnectionSetRepresentation::getSupportingGridRepresentationCount() const
{
	return static_cast<_resqml2__GridConnectionSetRepresentation*>(gsoapProxy)->Grid.size(); 
}
