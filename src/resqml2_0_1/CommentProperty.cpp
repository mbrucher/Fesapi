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
#include "resqml2_0_1/CommentProperty.h"

#include <sstream>
#include <list>

#include "hdf5.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* CommentProperty::XML_TAG = "CommentProperty";

CommentProperty::CommentProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECommentProperty(rep->getGsoapContext(), 1);	
	_resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

CommentProperty::CommentProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECommentProperty(rep->getGsoapContext(), 1);	
	_resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void CommentProperty::pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values,
	resqml2::AbstractHdfProxy * proxy)
{
	setHdfProxy(proxy);
    _resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy2_0_1);

	resqml2__PatchOfValues* patch = soap_new_resqml2__PatchOfValues(gsoapProxy2_0_1->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	ostringstream oss;
    resqml2__StringHdf5Array* xmlValues = soap_new_resqml2__StringHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlValues->Values->HdfProxy = proxy->newResqmlReference();;
	ostringstream ossForHdf;
	ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
	xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	patch->Values = xmlValues;

	// Build the CHAR array
	hsize_t dimTwo = 0;
	for (std::vector<std::string>::const_iterator it = values.begin() ; it!= values.end() ; it++){
		if ((*it).length() > dimTwo)
			dimTwo = (*it).length();
	}

	hsize_t strNb = values.size();
	unsigned char* cTab;
	cTab = new unsigned char[strNb*dimTwo];

	int indStr = 0;
	for (std::vector<std::string>::const_iterator it = values.begin() ; it!= values.end() ; it++){
		for (unsigned int indCha = 0 ; indCha < dimTwo ; indCha++) {
			if (indCha < (*it).length())
				cTab[(indStr*dimTwo)+indCha] = (*it)[indCha];
			else
				cTab[(indStr*dimTwo)+indCha] = '\0';
		}
		indStr++;
	}

	hsize_t nbValPerDim[] = {strNb, dimTwo};
	const unsigned int nbDimensions = 2;

    // HDF
	proxy->writeArrayNd(prop->uuid,
                    ossForHdf.str(),
                    H5T_NATIVE_UCHAR,
                    cTab,
                    nbValPerDim,   // 0 = number of strings, 1 = length of the longest string 
					nbDimensions); // 2

    delete [] cTab;

	prop->PatchOfValues.push_back(patch);
}

std::vector<std::string> CommentProperty::getStringValuesOfPatch(const unsigned int & patchIndex)
{
	// Check that the hdf proxy has been resolved.
	resqml2::AbstractHdfProxy* hdfProxy = getHdfProxy();
	if (hdfProxy == nullptr) {
		throw invalid_argument("The hdf proxy does not exist");
	}

	std::vector<std::string> result;

	// Look for the hdf dataset name where the comments are stored.
	_resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy2_0_1);
	resqml2__StringHdf5Array* hdfValues = static_cast<resqml2__StringHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);
	const std::string datasetName = hdfValues->Values->PathInHdfFile;

	// Check if the hdf dataset really contains constant length string.
	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions (datasetName);
	if (dims.size() != 2) {
		return result;
	}
	// Check if the hdf dataset really contains unsigned char values.
	if (getValuesHdfDatatype() != AbstractValuesProperty::UCHAR) {
		return result;
	}

	const unsigned int nbStrings = (unsigned int)dims[0]; // The count of strings in the HDF dataset.
	const unsigned int stringLength = (unsigned int)dims[1]; // The constant string length in the hdf dataset.

	// Read all char/strings from the hdf dataset
	unsigned char* values = new unsigned char[nbStrings * stringLength];
	hdfProxy->readArrayNdOfUCharValues (datasetName, values);

	for (unsigned int stringIndex = 0; stringIndex < nbStrings; ++stringIndex) {
		std::string comment = string();
		bool terminatingChar = false;
		for (unsigned int localCharIndex = 0; localCharIndex < stringLength; ++localCharIndex) {
			if (values[localCharIndex + stringIndex*stringLength] == '\0') {
				terminatingChar = true;
				comment.assign((char*)&values[stringIndex*stringLength]);
				break;
			}
		}

		if (!terminatingChar) {
			comment.assign((char*)&values[stringIndex*stringLength], stringLength);
		}

		result.push_back(comment);
	}

	delete [] values;

	return result;
}
