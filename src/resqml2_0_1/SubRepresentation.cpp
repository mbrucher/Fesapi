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
#include "resqml2_0_1/SubRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

void SubRepresentation::init(
        const string & guid, const string & title,
		AbstractRepresentation * supportingRep)
{
	if (supportingRep == nullptr)
		throw invalid_argument("The supportng representation of the subrepresentation cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCORESubRepresentation(supportingRep->getGsoapContext(), 1);
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "", "");
	
	rep->SupportingRepresentation = supportingRep->newResqmlReference();
	supportingRepresentation = supportingRep;
	supportingRep->addSubRepresentation(this);
}

SubRepresentation::SubRepresentation(
        const string & guid, const string & title,
		AbstractRepresentation * supportingRep):
	AbstractRepresentation(static_cast<AbstractFeatureInterpretation*>(nullptr), nullptr)
{
	init(guid, title, supportingRep);
}

SubRepresentation::SubRepresentation(AbstractFeatureInterpretation* interp,
        const string & guid, const string & title,
		AbstractRepresentation * supportingRep):
	AbstractRepresentation(interp, nullptr)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the subrepresentation cannot be null.");

	init(guid, title, supportingRep);

	// relationhsips
	setInterpretation(interp);
}

_resqml2__SubRepresentation* SubRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial() == true)
		throw logic_error("Partial object");

	return static_cast<_resqml2__SubRepresentation*>(gsoapProxy);
}

bool SubRepresentation::isElementPairBased(const unsigned int & patchIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		return rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() == 2;
	}
	else
		throw range_error("The patch does not exist at this index.");
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & originIndex,
	const unsigned int & elementCountInSlowestDimension,
	const unsigned int & elementCountInMiddleDimension,
	const unsigned int & elementCountInFastestDimension)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml2__SubRepresentationPatch* patch = soap_new_resqml2__SubRepresentationPatch(gsoapProxy->soap, 1);

	// XML
	patch->PatchIndex = rep->SubRepresentationPatch.size();
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCountInSlowestDimension * elementCountInMiddleDimension * elementCountInFastestDimension;
	resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy->soap, 1);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = elementKind;

	resqml2__IntegerLatticeArray * integerArray = soap_new_resqml2__IntegerLatticeArray(gsoapProxy->soap, 1);
	elements->Indices = integerArray;
	integerArray->StartValue = originIndex;

	resqml2__IntegerConstantArray * offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1);
	offset->Count = elementCountInSlowestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1);
	offset->Count = elementCountInMiddleDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);

	offset = soap_new_resqml2__IntegerConstantArray(gsoapProxy->soap, 1);
	offset->Count = elementCountInFastestDimension - 1;
	offset->Value = 1;
	integerArray->Offset.push_back(offset);
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, unsigned int * elementIndices, AbstractHdfProxy * proxy)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	setHdfProxy(proxy);

	resqml2__SubRepresentationPatch* patch = soap_new_resqml2__SubRepresentationPatch(gsoapProxy->soap, 1);

	// XML
	patch->PatchIndex = rep->SubRepresentationPatch.size();
	rep->SubRepresentationPatch.push_back(patch);
	patch->Count = elementCount;
	resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy->soap, 1);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = elementKind;
	
	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices0_patch" << patch->PatchIndex;
	resqml2__IntegerHdf5Array * integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
    eml__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
    resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/" + ossForHdf.str();
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = (std::numeric_limits<unsigned int>::max)();
	elements->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues[] = {elementCount};
	hdfProxy->writeArrayNd(rep->uuid, ossForHdf.str(), H5T_NATIVE_UINT, elementIndices, numValues, 1);
}

void SubRepresentation::pushBackRefToExistingDataset(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, const std::string & dataset,
			const LONG64 & nullValue, AbstractHdfProxy * proxy)
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	
  setHdfProxy(proxy);
  
  resqml2__SubRepresentationPatch* patch = soap_new_resqml2__SubRepresentationPatch(gsoapProxy->soap, 1);

  // XML
  patch->PatchIndex = rep->SubRepresentationPatch.size();
  rep->SubRepresentationPatch.push_back(patch);
  patch->Count = elementCount;
  resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy->soap, 1);
  patch->ElementIndices.push_back(elements);
  elements->IndexableElement = elementKind;

  resqml2__IntegerHdf5Array * integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
  eml__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
  resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
  if (dataset.empty() == true)
  {
    ostringstream ossForHdf;
    ossForHdf << "subrepresentation_elementIndices0_patch" << patch->PatchIndex;
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/" + ossForHdf.str();
  }
  else
  {
    resqmlHDF5dataset->PathInHdfFile = dataset;
  }
  integerArray->Values = resqmlHDF5dataset;
  integerArray->NullValue = nullValue;
  elements->Indices = integerArray;
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			unsigned int * elementIndices0, unsigned int * elementIndices1,
			AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	resqml2__SubRepresentationPatch* patch = rep->SubRepresentationPatch[rep->SubRepresentationPatch.size() - 1];

	// XML
	resqml2__ElementIndices* elements = soap_new_resqml2__ElementIndices(gsoapProxy->soap, 1);
	patch->ElementIndices.push_back(elements);
	elements->IndexableElement = elementKind1;
	
	ostringstream ossForHdf;
	ossForHdf << "subrepresentation_elementIndices1_patch" << patch->PatchIndex;
	resqml2__IntegerHdf5Array * integerArray = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
    eml__Hdf5Dataset * resqmlHDF5dataset = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
    resqmlHDF5dataset->HdfProxy = hdfProxy->newResqmlReference();
    resqmlHDF5dataset->PathInHdfFile = "/RESQML/" + rep->uuid + "/" + ossForHdf.str();
	integerArray->Values = resqmlHDF5dataset;
	integerArray->NullValue = (std::numeric_limits<unsigned int>::max)();
	elements->Indices = integerArray;

	// ************ HDF ************		
	hsize_t numValues[] = {elementCount};
	hdfProxy->writeArrayNd(rep->uuid, ossForHdf.str(), H5T_NATIVE_UINT, elementIndices1, numValues, 1);
}

string SubRepresentation::getHdfProxyUuid() const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (rep->SubRepresentationPatch.size())
	{
		if (rep->SubRepresentationPatch[0]->ElementIndices.size())
		{
			if (rep->SubRepresentationPatch[0]->ElementIndices[0]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
			{
				return static_cast<resqml2__IntegerHdf5Array*>(rep->SubRepresentationPatch[0]->ElementIndices[0]->Indices)->Values->HdfProxy->UUID;
			}
		}
	}

	return "";
}

gsoap_resqml2_0_1::resqml2__IndexableElements SubRepresentation::getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex)
			return rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->IndexableElement;
		else
			throw range_error("The elementIndices does not exist at this index.");
	}
	else
		throw range_error("The patch does not exist at this index.");
}

ULONG64 SubRepresentation::getElementCountOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		return rep->SubRepresentationPatch[patchIndex]->Count;
	}
	else
		throw range_error("The patch does not exist at this index.");
}

bool SubRepresentation::areElementPairwise(const unsigned int & patchIndex) const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch[patchIndex]->ElementIndices.size() > 1;
}

bool SubRepresentation::areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray;
}

LONG64 SubRepresentation::getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false)
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch.size() <= patchIndex)
		throw range_error("The subrepresentation patch index is out of range.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw range_error("The element indices index is out of range.");

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	return lattice->StartValue;
}

unsigned int SubRepresentation::getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false)
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch.size() <= patchIndex)
		throw range_error("The subrepresentation patch index is out of range.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw range_error("The element indices index is out of range.");

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	return lattice->Offset.size();
}

LONG64 SubRepresentation::getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false)
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch.size() <= patchIndex)
		throw range_error("The subrepresentation patch index is out of range.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw range_error("The element indices index is out of range.");

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex)
		throw range_error("The lattice dimension index is out of range.");

	return lattice->Offset[latticeDimensionIndex]->Value;
}

ULONG64 SubRepresentation::getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();

	if (areElementIndicesBasedOnLattice(patchIndex, elementIndicesIndex) == false)
		throw invalid_argument("The element indices are not based on a lattice.");
	if (rep->SubRepresentationPatch.size() <= patchIndex)
		throw range_error("The subrepresentation patch index is out of range.");
	if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() <= elementIndicesIndex)
		throw range_error("The element indices index is out of range.");

	resqml2__IntegerLatticeArray* lattice = static_cast<resqml2__IntegerLatticeArray*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices);
	if (lattice->Offset.size() <= latticeDimensionIndex)
		throw range_error("The lattice dimension index is out of range.");

	return lattice->Offset[latticeDimensionIndex]->Count;
}

void SubRepresentation::getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, unsigned int * elementIndices) const
{
	_resqml2__SubRepresentation* rep = getSpecializedGsoapProxy();
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex)
		{
			if (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
				hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices)->Values->PathInHdfFile, elementIndices);
			else
				throw logic_error("Not yet implemented");
		}
		else
			throw range_error("The elementIndices does not exist at this index.");
	}
	else
		throw range_error("The patch does not exist at this index.");
}

vector<Relationship> SubRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	Relationship rel(supportingRepresentation->getPartNameInEpcDocument(), "", supportingRepresentation->getUuid());
	rel.setDestinationObjectType();
	result.push_back(rel);
    
	return result;
}

void SubRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__SubRepresentation* subRep = getSpecializedGsoapProxy();

	// Supporting representation
	supportingRepresentation = static_cast<AbstractRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(subRep->SupportingRepresentation->UUID));
	if (supportingRepresentation == nullptr) // partial transfer
	{
		getEpcDocument()->addWarning("The referenced grid \"" + subRep->SupportingRepresentation->Title + "\" (" + subRep->SupportingRepresentation->UUID + ") is missing.");
		if (subRep->SupportingRepresentation->ContentType.find("UnstructuredGridRepresentation") != 0)
			supportingRepresentation = epcDoc->createPartialUnstructuredGridRepresentation(subRep->SupportingRepresentation->UUID, subRep->SupportingRepresentation->Title);
		else if (subRep->SupportingRepresentation->ContentType.find("IjkGridRepresentation") != 0)
			supportingRepresentation = epcDoc->createPartialIjkGridRepresentation(subRep->SupportingRepresentation->UUID, subRep->SupportingRepresentation->Title);
	}
	supportingRepresentation->addSubRepresentation(this);
}

ULONG64 SubRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	if (getElementKindOfPatch(patchIndex, 0) == resqml2__IndexableElements__nodes)
		return getElementCountOfPatch(patchIndex);
	else
		throw logic_error("Not yet implemented.");
}

void SubRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	throw logic_error("Not yet implemented.");
}

unsigned int SubRepresentation::getPatchCount() const
{
	return getSpecializedGsoapProxy()->SubRepresentationPatch.size();
}
