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
#include "resqml2_0_1/Activity.h"

#include "resqml2_0_1/ActivityTemplate.h"

#include <algorithm>
#include <stdexcept>

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* Activity::XML_TAG = "Activity";

Activity::Activity(ActivityTemplate* activityTemplate, const string & guid, const string & title)
{
	if (activityTemplate == nullptr)
		throw invalid_argument("The activity template of an activity must be not null.");

	gsoapProxy = soap_new_resqml2__obj_USCOREActivity(activityTemplate->getGsoapProxy()->soap, 1);

	setActivityTemplate(activityTemplate);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	if (activityTemplate->getEpcDocument() != nullptr)
		activityTemplate->getEpcDocument()->addGsoapProxy(this);
}

void Activity::pushBackParameter(const std::string title,
			const double & value, const resqml2__ResqmlUom & uom)
{
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	long long maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	vector<resqml2__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
	if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__double_) == allowedKinds.end())
		throw invalid_argument("The parameter template " + title + " does not allow a double datatype.");

	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	resqml2__DoubleQuantityParameter* dqp = soap_new_resqml2__DoubleQuantityParameter(activity->soap, 1);
	dqp->Title = title;
	dqp->Value = value;
	dqp->Uom = uom;
	activity->Parameter.push_back(dqp);
}

void Activity::pushBackParameter(const std::string title, const std::string & value)
{
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	long long maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	vector<resqml2__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
	if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__string) == allowedKinds.end())
		throw invalid_argument("The parameter template " + title + " does not allow a string datatype.");

	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	resqml2__StringParameter* sp = soap_new_resqml2__StringParameter(activity->soap, 1);
	sp->Title = title;
	sp->Value = value;
	activity->Parameter.push_back(sp);
}

void Activity::pushBackParameter(const std::string title, const long long & value)
{
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	long long maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	vector<resqml2__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
	if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__integer) == allowedKinds.end())
		throw invalid_argument("The parameter template " + title + " does not allow an integer datatype.");

	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	resqml2__IntegerQuantityParameter* iqp = soap_new_resqml2__IntegerQuantityParameter(activity->soap, 1);
	iqp->Title = title;
	iqp->Value = value;
	activity->Parameter.push_back(iqp);
}

void Activity::pushBackResqmlObjectParameter(const std::string title,
			AbstractObject* resqmlObject)
{
	if (resqmlObject == nullptr)
		throw invalid_argument("The resqml object must be non null.");
	if (activityTemplate->isAnExistingParameter(title) == false)
		throw invalid_argument("The parameter " + title + " does not exist in the associated activity template.");
	long long maxOccurs = activityTemplate->getParameterMaxOccurences(title);
	if (maxOccurs > -1 && maxOccurs <= getParameterCount(title))
		throw invalid_argument("The max number of occurences has already been reached for parameter " + title);
	vector<resqml2__ParameterKind> allowedKinds = activityTemplate->getParameterAllowedKinds(title);
	if (allowedKinds.size() > 0 && find(allowedKinds.begin(), allowedKinds.end(), resqml2__ParameterKind__dataObject) == allowedKinds.end())
		throw invalid_argument("The parameter template " + title + " does not allow a data object datatype.");

	//EPC
	bool alreadyInserted = (std::find(resqmlObjectSet.begin(), resqmlObjectSet.end(), resqmlObject) != resqmlObjectSet.end()); // In case the resqml object is both input and output of the activity
	if (!alreadyInserted)
	{		
		resqmlObjectSet.push_back(resqmlObject);
	}
	alreadyInserted = (std::find(resqmlObject->activitySet.begin(), resqmlObject->activitySet.end(), this) != resqmlObject->activitySet.end()); // In case the resqml object is both input and output of the activity
	if (!alreadyInserted)
	{
		resqmlObject->activitySet.push_back(this);
	}

	// XML
	if (updateXml)
	{
		_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

		resqml2__DataObjectParameter* dop = soap_new_resqml2__DataObjectParameter(activity->soap, 1);
		dop->Title = title;
		dop->DataObject = resqmlObject->newResqmlReference();
		activity->Parameter.push_back(dop);
	}
}

unsigned int Activity::getParameterCount() const
{
	return static_cast<_resqml2__Activity*>(gsoapProxy)->Parameter.size();
}

unsigned int Activity::getParameterCount(const std::string & paramTitle) const
{
	return getParameterFromTitle(paramTitle).size();
}

const std::string & Activity::getParameterTitle(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->Title;
}

std::vector<unsigned int> Activity::getParameterIndexOfTitle(const std::string & paramTitle) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	vector<unsigned int> paramIndex;
	for (unsigned int i = 0; i < activity->Parameter.size(); ++i)
	{
		if (activity->Parameter[i]->Title == paramTitle)
		{
			paramIndex.push_back(i);
		}
	}

	return paramIndex;
}

std::vector<resqml2__AbstractActivityParameter*> Activity::getParameterFromTitle(const std::string & paramTitle) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	std::vector<resqml2__AbstractActivityParameter*> params;
	for (unsigned int i = 0; i < activity->Parameter.size(); ++i)
	{
		if (activity->Parameter[i]->Title == paramTitle)
		{
			params.push_back(activity->Parameter[i]);
		}
	}

	return params;
}

/*****************************
********** DOUBLE ************
*****************************/
bool Activity::isADoubleQuantityParameter(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isADoubleQuantityParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleQuantityParameter;
}

vector<double> Activity::getDoubleQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<double> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__DoubleQuantityParameter*>(param[i])->Value);
	}

	return result;
}

double Activity::getDoubleQuantityParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__DoubleQuantityParameter*>(activity->Parameter[index])->Value;
}

vector<resqml2__ResqmlUom> Activity::getDoubleQuantityParameterUom(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<resqml2__ResqmlUom> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__DoubleQuantityParameter*>(param[i])->Uom);
	}

	return result;
}

gsoap_resqml2_0_1::resqml2__ResqmlUom Activity::getDoubleQuantityParameterUom(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__DoubleQuantityParameter*>(activity->Parameter[index])->Uom;
}

/*****************************
********** INTEGER ***********
*****************************/
bool Activity::isAnIntegerQuantityParameter(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter)
			return false;
	}

	return true;
}

bool Activity::isAnIntegerQuantityParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter;
}

vector<long long> Activity::getIntegerQuantityParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<long long> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__IntegerQuantityParameter*>(param[i])->Value);
	}

	return result;
}

long long Activity::getIntegerQuantityParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerQuantityParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__IntegerQuantityParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** STRING ************
*****************************/
bool Activity::isAStringParameter(const std::string & paramTitle) const
{	
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter)
			return false;
	}

	return true;
}

bool Activity::isAStringParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter;
}

vector<string> Activity::getStringParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<string> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(static_cast<resqml2__StringParameter*>(param[i])->Value);
	}

	return result;
}

const std::string & Activity::getStringParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__StringParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return static_cast<resqml2__StringParameter*>(activity->Parameter[index])->Value;
}

/*****************************
********** OBJECT ************
*****************************/
bool Activity::isAResqmlObjectParameter(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
			return false;
	}

	return true;
}

bool Activity::isAResqmlObjectParameter(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	return activity->Parameter[index]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter;
}

vector<AbstractObject*> Activity::getResqmlObjectParameterValue(const std::string & paramTitle) const
{
	vector<resqml2__AbstractActivityParameter*> param = getParameterFromTitle(paramTitle);

	if (param.size() < 1)
		throw range_error("The parameter " + paramTitle + " is not in the parameter range.");

	vector<AbstractObject*> result;
	for (unsigned int i = 0; i < param.size(); ++i)
	{
		if (param[i]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
			throw invalid_argument("The parameter " + paramTitle + " contains some non double values.");
		else
			result.push_back(getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<resqml2__DataObjectParameter*>(param[i])->DataObject->UUID));
	}

	return result;
}

AbstractObject* Activity::getResqmlObjectParameterValue(const unsigned int & index) const
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->Parameter.size() <= index)
		throw range_error("The parameter index is not in the parameter range.");

	if (activity->Parameter[index]->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
		throw invalid_argument("The parameter index is not in the parameter range.");

	return getEpcDocument()->getResqmlAbstractObjectByUuid(static_cast<resqml2__DataObjectParameter*>(activity->Parameter[index])->DataObject->UUID);
}

void Activity::setActivityTemplate(ActivityTemplate * activityTemplate)
{
	if (activityTemplate == nullptr)
	{
		return;
	}

	// EPC
	this->activityTemplate = activityTemplate;
	activityTemplate->activitySet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<_resqml2__Activity*>(gsoapProxy)->ActivityDescriptor = activityTemplate->newResqmlReference();
	}
}

std::string Activity::getResqmlVersion() const
{
	return "2.0.1";
}

vector<Relationship> Activity::getAllEpcRelationships() const
{
	vector<Relationship> result;

	if (activityTemplate)
	{
		Relationship rel(activityTemplate->getPartNameInEpcDocument(), "", activityTemplate->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	else
		throw domain_error("The activity template associated to the activity cannot be NULL.");

	for (unsigned int i = 0; i < resqmlObjectSet.size(); ++i)
	{
		if (resqmlObjectSet[i])
		{
			Relationship relResqmlObject(resqmlObjectSet[i]->getPartNameInEpcDocument(), "", resqmlObjectSet[i]->getUuid());
			relResqmlObject.setDestinationObjectType();
			result.push_back(relResqmlObject);
		}
		else
			throw domain_error("The resqml Object associated to the activity cannot be NULL.");
	}

	return result;
}

void Activity::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	_resqml2__Activity* activity = static_cast<_resqml2__Activity*>(gsoapProxy);

	if (activity->ActivityDescriptor)
	{
		updateXml = false;
		setActivityTemplate(static_cast<ActivityTemplate*>(epcDoc->getResqmlAbstractObjectByUuid(activity->ActivityDescriptor->UUID)));
		updateXml = true;
	}
	else
		throw domain_error("The activity template associated to the activity cannot be NULL.");

	for (unsigned int i = 0; i < activity->Parameter.size(); ++i)
	{
		if (activity->Parameter[i]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DataObjectParameter)
		{
			resqml2__DataObjectParameter* dop = static_cast<resqml2__DataObjectParameter*>(activity->Parameter[i]);
			if (dop->DataObject == NULL)
				throw domain_error("The resqml object of a data object parameter cannot be null.");

			updateXml = false;
			pushBackResqmlObjectParameter(dop->Title, epcDoc->getResqmlAbstractObjectByUuid(dop->DataObject->UUID));
			updateXml = true;
		}
	}
}
