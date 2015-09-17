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
#include "resqml2_0_1/SubRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "resqml2_0_1/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/AbstractLocal3dCrs.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* SubRepresentation::XML_TAG = "SubRepresentation";

void SubRepresentation::init(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
        const string & guid, const string & title,
		AbstractRepresentation * supportingRep)
{
	if (epcDoc == nullptr)
		throw invalid_argument("The EPC document where the subrepresentation will be stored cannot be null.");
	if (crs == nullptr)
		throw invalid_argument("The local CRS of the subrepresentation cannot be null.");
	if (supportingRep == nullptr)
		throw invalid_argument("The supportng representation of the subrepresentation cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCORESubRepresentation(epcDoc->getGsoapContext(), 1);
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);

	initMandatoryMetadata();
    setMetadata(guid, title, "", -1, "", "", -1, "", "");
	
	rep->SupportingRepresentation = supportingRep->newResqmlReference();
	supportingRepresentation = supportingRep;
	supportingRep->addSubRepresentation(this);

	// epc document
	epcDoc->addGsoapProxy(this);

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);
}

SubRepresentation::SubRepresentation(common::EpcDocument* epcDoc, AbstractLocal3dCrs * crs,
        const string & guid, const string & title,
		AbstractRepresentation * supportingRep):
	AbstractRepresentation(nullptr, crs)
{
	init(epcDoc, crs, guid, title, supportingRep);
}

SubRepresentation::SubRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
        const string & guid, const string & title,
		AbstractRepresentation * supportingRep):
	AbstractRepresentation(interp, crs)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the subrepresentation cannot be null.");

	init(interp->getEpcDocument(), crs, guid, title, supportingRep);

	// relationhsips
	setInterpretation(interp);
}

bool SubRepresentation::isElementPairBased(const unsigned int & patchIndex) const
{
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		return rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() == 2;
	}
	else
		throw invalid_argument("The patch does not exist at this index.");
}

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const unsigned int & elementCount, unsigned int * elementIndices, AbstractHdfProxy * proxy)
{
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);

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

void SubRepresentation::pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const unsigned int & elementCount,
			unsigned int * elementIndices0, unsigned int * elementIndices1,
			AbstractHdfProxy * proxy)
{
	pushBackSubRepresentationPatch(elementKind0, elementCount, elementIndices0, proxy);

	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);

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
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);

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
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex)
			return rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->IndexableElement;
		else
			throw invalid_argument("The elementIndices does not exist at this index.");
	}
	else
		throw invalid_argument("The patch does not exist at this index.");
}

ULONG64 SubRepresentation::getElementCountOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		return rep->SubRepresentationPatch[patchIndex]->Count;
	}
	else
		throw invalid_argument("The patch does not exist at this index.");
}

void SubRepresentation::getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, unsigned int * elementIndices) const
{
	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);
	if (rep->SubRepresentationPatch.size() > patchIndex)
	{
		if (rep->SubRepresentationPatch[patchIndex]->ElementIndices.size() > elementIndicesIndex)
		{
			if (rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
				hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(rep->SubRepresentationPatch[patchIndex]->ElementIndices[elementIndicesIndex]->Indices)->Values->PathInHdfFile, elementIndices);
		}
		else
			throw invalid_argument("The elementIndices does not exist at this index.");
	}
	else
		throw invalid_argument("The patch does not exist at this index.");
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

	_resqml2__SubRepresentation* rep = static_cast<_resqml2__SubRepresentation*>(gsoapProxy);

	// Base representation
	if (rep->SupportingRepresentation->UUID.empty() == false)
	{
		supportingRepresentation = static_cast<AbstractRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->SupportingRepresentation->UUID));
		supportingRepresentation->addSubRepresentation(this);
	}
}

ULONG64 SubRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (getElementKindOfPatch(patchIndex, 0) == resqml2__IndexableElements__nodes)
		return getElementCountOfPatch(patchIndex);
	else
		throw logic_error("Not yet implemented.");
}

unsigned int SubRepresentation::getPatchCount() const
{
	return static_cast<_resqml2__SubRepresentation*>(gsoapProxy)->SubRepresentationPatch.size();
}
