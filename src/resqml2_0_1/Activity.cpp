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
