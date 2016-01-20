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

#include "resqml2_0_1/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* CommentProperty::XML_TAG = "CommentProperty";

CommentProperty::CommentProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy = soap_new_resqml2__obj_USCORECommentProperty(rep->getEpcDocument()->getGsoapContext(), 1);	
	_resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (rep->getEpcDocument())
		rep->getEpcDocument()->addGsoapProxy(this);
}

CommentProperty::CommentProperty(AbstractRepresentation * rep, const string & guid, const string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, PropertyKind * localPropKind)
{
	gsoapProxy = soap_new_resqml2__obj_USCORECommentProperty(rep->getEpcDocument()->getGsoapContext(), 1);	
	_resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (rep->getEpcDocument())
		rep->getEpcDocument()->addGsoapProxy(this);
}

void CommentProperty::pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values,
													   AbstractHdfProxy * proxy)
{
	setHdfProxy(proxy);
    _resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy);

	resqml2__PatchOfValues* patch = soap_new_resqml2__PatchOfValues(gsoapProxy->soap, 1);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	ostringstream oss;
    resqml2__StringHdf5Array* xmlValues = soap_new_resqml2__StringHdf5Array(gsoapProxy->soap, 1);
	xmlValues->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();;
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
    hdfProxy->writeArrayNd(prop->uuid,
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
	std::list<std::string> shpLabels; // use list because of the push_front method (performance reason)
	std::vector<std::string> result;

	if (hdfProxy == nullptr)
		return result;

	_resqml2__CommentProperty* prop = static_cast<_resqml2__CommentProperty*>(gsoapProxy);
	resqml2__StringHdf5Array* hdfValues = static_cast<resqml2__StringHdf5Array*>(prop->PatchOfValues[patchIndex]->Values);
	std::string datasetName = hdfValues->Values->PathInHdfFile;

	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions (datasetName);
	if (dims.size() != 2)
		return result;

	int nbStrings = (int)dims [0];
	int stringLen = (int)dims [1];

	unsigned int totNbChar = nbStrings*stringLen;
	unsigned char* values = new unsigned char[totNbChar];
	hdfProxy->readArrayNdOfUCharValues (datasetName, values);

	int indStr = nbStrings;
	int currBeg = (indStr-1)*stringLen;
	for (int charind = totNbChar-1 ; charind >= 0 ; charind--)
	{
		if (charind >= currBeg && charind <= currBeg + (stringLen-1) && values[charind] != '\0')
		{
			// The label is found
			std::string aLabel = (char*)&values[currBeg];
			aLabel.resize(stringLen);
			shpLabels.push_front (aLabel);
			indStr--;
			currBeg -= stringLen;
		}
		if (charind == currBeg)
		{
			// No label found for this index
			shpLabels.push_front ("NaN");
			indStr--;
			currBeg -= stringLen;
		}
	}

	delete [] values;
	
	result.insert(result.end(), shpLabels.begin(), shpLabels.end());
	return result;
}
