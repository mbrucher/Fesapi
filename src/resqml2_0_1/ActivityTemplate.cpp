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
#include "resqml2_0_1/ActivityTemplate.h"

#include <stdexcept>

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* ActivityTemplate::XML_TAG = "ActivityTemplate";

void ActivityTemplate::pushBackParameter(const std::string title,
			const resqml2__ParameterKind & kind,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const unsigned int & maxOccurs)
{
	// Preconditions
	if (minOccurs > maxOccurs)
		throw invalid_argument("Maximum occurences of a parameter template must be at least equal to the minimum occurences of this same parameter template.");

	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	resqml2__ParameterTemplate* param =soap_new_resqml2__ParameterTemplate(gsoapProxy->soap, 1);
	param->Title = title;
	param->AllowedKind.push_back(kind);
	param->IsInput = isInput;
	param->IsOutput = isOutput;
	if (minOccurs != 1)
	{
		param->MinOccurs = static_cast<LONG64*>(soap_malloc(gsoapProxy->soap, sizeof(LONG64)));
		*(param->MinOccurs) = minOccurs;
	}
	if (maxOccurs != 1)
	{
		param->MaxOccurs = static_cast<LONG64*>(soap_malloc(gsoapProxy->soap, sizeof(LONG64)));
		*(param->MaxOccurs )= maxOccurs;
	}

	activityTemplate->Parameter.push_back(param);
}

void ActivityTemplate::pushBackDataObjectParameter(const std::string title,
	const bool & isInput, const bool isOutput,
	const unsigned int & minOccurs, const unsigned int & maxOccurs,
	const std::string & dataObjetContentType)
{
	pushBackParameter(title, resqml2__ParameterKind__dataObject, isInput, isOutput, minOccurs, maxOccurs);

	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);
	activityTemplate->Parameter[activityTemplate->Parameter.size()-1]->DataObjectContentType = soap_new_std__string(gsoapProxy->soap, 1);
	activityTemplate->Parameter[activityTemplate->Parameter.size()-1]->DataObjectContentType->assign(dataObjetContentType); 
} 

const std::string & ActivityTemplate::getParameterTitle(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->Title;
}

const vector<gsoap_resqml2_0_1::resqml2__ParameterKind> & ActivityTemplate::getParameterAllowedKinds(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->AllowedKind;
}

const bool & ActivityTemplate::getParameterIsInput(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->IsInput;
}

const bool & ActivityTemplate::getParameterIsOutput(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	return activityTemplate->Parameter[index]->IsOutput;
}

const unsigned int ActivityTemplate::getParameterMinOccurences(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	if (activityTemplate->Parameter[index]->MinOccurs == nullptr)
		return 1;
	else
		return *activityTemplate->Parameter[index]->MinOccurs;
}

const unsigned int ActivityTemplate::getParameterMaxOccurences(const unsigned int & index) const
{
	_resqml2__ActivityTemplate* activityTemplate = static_cast<_resqml2__ActivityTemplate*>(gsoapProxy);

	if (activityTemplate->Parameter.size() <= index)
		throw range_error("The parameter template index is not in the parameter range.");

	if (activityTemplate->Parameter[index]->MaxOccurs == nullptr)
		return 1;
	else
		return *activityTemplate->Parameter[index]->MaxOccurs;
}

std::string ActivityTemplate::getResqmlVersion() const
{
	return "2.0.1";
}

ActivityTemplate::ActivityTemplate(common::EpcDocument* epcDoc, const string & guid, const string & title)
{
	if (epcDoc == nullptr)
		throw invalid_argument("The EPC document where the activity template will be stored cannot be null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREActivityTemplate(epcDoc->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	epcDoc->addGsoapProxy(this);
}

vector<Relationship> ActivityTemplate::getAllEpcRelationships() const
{
	vector<Relationship> result;

	for (unsigned int i = 0; i < activitySet.size(); ++i)
	{
		Relationship rel(activitySet[i]->getPartNameInEpcDocument(), "", activitySet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}
