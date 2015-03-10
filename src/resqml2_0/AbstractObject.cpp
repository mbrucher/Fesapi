/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014) 

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
#include "resqml2_0/AbstractObject.h"

#include <stdexcept>
#include <string>
#include <sstream>

#include "GuidTools.h"

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;


string AbstractObject::getUuid() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy->uuid;
}

string AbstractObject::getTitle() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy->Citation->Title;
}

string AbstractObject::getEditor() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->Editor)
		return *gsoapProxy->Citation->Editor;
	else
		return "";
}

time_t AbstractObject::getCreation() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy->Citation->Creation;
}

string AbstractObject::getOriginator() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy->Citation->Originator;
}

string AbstractObject::getDescription() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->Description)
		return *gsoapProxy->Citation->Description;
	else
		return "";
}

time_t AbstractObject::getLastUpdate() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->LastUpdate)
		return *gsoapProxy->Citation->LastUpdate;
	else
		return -1;
}

string AbstractObject::getFormat() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy->Citation->Format;
}

string AbstractObject::getDescriptiveKeywords() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->DescriptiveKeywords)
		return *gsoapProxy->Citation->DescriptiveKeywords;
	else
		return "";
}

void AbstractObject::setUuid(const std::string & uuid)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	gsoapProxy->uuid = uuid;
}

void AbstractObject::setTitle(const std::string & title)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	gsoapProxy->Citation->Title = title;
}

void AbstractObject::setEditor(const std::string & editor)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->Editor == NULL)
		gsoapProxy->Citation->Editor = soap_new_std__string(gsoapProxy->soap, 1);
	gsoapProxy->Citation->Editor->assign(editor);
}

void AbstractObject::setCreation(const time_t & creation)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	gsoapProxy->Citation->Creation = creation;
}

void AbstractObject::setOriginator(const std::string & originator)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	gsoapProxy->Citation->Originator = originator;
}

void AbstractObject::setDescription(const std::string & description)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->Description == NULL)
		gsoapProxy->Citation->Description = soap_new_std__string(gsoapProxy->soap, 1);
	gsoapProxy->Citation->Description->assign(description);
}

void AbstractObject::setLastUpdate(const time_t & lastUpdate)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->LastUpdate == NULL)
		gsoapProxy->Citation->LastUpdate = (time_t *)soap_malloc(gsoapProxy->soap, sizeof(time_t));
	*gsoapProxy->Citation->LastUpdate = lastUpdate;
}

void AbstractObject::setFormat(const std::string & format)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	gsoapProxy->Citation->Format = format;
}

void AbstractObject::setDescriptiveKeywords(const std::string & descriptiveKeywords)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy->Citation->DescriptiveKeywords == NULL)
		gsoapProxy->Citation->DescriptiveKeywords = soap_new_std__string(gsoapProxy->soap, 1);
	gsoapProxy->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
}

void AbstractObject::addNewGuid(const string & newGuid)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (newGuid.empty())
		gsoapProxy->uuid = tools::GuidTools::generateUidAsString();
	else
		gsoapProxy->uuid = newGuid;
}

void AbstractObject::initMandatoryMetadata()
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	addNewGuid("");

	gsoapProxy->schemaVersion = "2.0";

	gsoapProxy->Citation = soap_new_eml__Citation(gsoapProxy->soap, 1);

	//title
	gsoapProxy->Citation->Title = "UNKNOWN TITLE";
	
	// Created time
	time_t now;
	time ( &now );
	gsoapProxy->Citation->Creation = now;

	// Creator
#if defined(__gnu_linux__) || defined(__APPLE__)
    register struct passwd *pw;
    register uid_t uid;
                
    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw)
            gsoapProxy->Citation->Originator = pw->pw_name;
    else
            gsoapProxy->Citation->Originator = "UNKNOWN CREATOR";
#elif defined(_WIN32)
	char acUserName[32];
	DWORD nUserName = sizeof(acUserName);
	GetUserName(acUserName, &nUserName);
    gsoapProxy->Citation->Originator = acUserName;
#endif

	//FORMAT
    gsoapProxy->Citation->Format = "[F2I-CONSULTING:resqml2CppApi]";
}

void AbstractObject::setMetadata(const std::string & guid, const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!guid.empty())
		addNewGuid(guid);

	if (!title.empty())
		gsoapProxy->Citation->Title = title;

	if (!editor.empty())
	{
		if (gsoapProxy->Citation->Editor == NULL)
			gsoapProxy->Citation->Editor = soap_new_std__string(gsoapProxy->soap, 1);
		*(gsoapProxy->Citation->Editor) = editor;
	}

	if (creation > 0)
		gsoapProxy->Citation->Creation = creation;

	if (!originator.empty())
		gsoapProxy->Citation->Originator = originator;

	if (!description.empty())
	{
		if (gsoapProxy->Citation->Description == NULL)
			gsoapProxy->Citation->Description = soap_new_std__string(gsoapProxy->soap, 1);
		*(gsoapProxy->Citation->Description) = description;
	}

	if (creation >0)
	{
		if (gsoapProxy->Citation->LastUpdate == NULL)
			gsoapProxy->Citation->LastUpdate = (time_t *)soap_malloc(gsoapProxy->soap, sizeof(time_t));
		*(gsoapProxy->Citation->LastUpdate) = lastUpdate;
	}

	if (!format.empty())
		gsoapProxy->Citation->Format = format;

	if (!descriptiveKeywords.empty())
	{
		if (gsoapProxy->Citation->DescriptiveKeywords == NULL)
			gsoapProxy->Citation->DescriptiveKeywords = soap_new_std__string(gsoapProxy->soap, 1);
		*(gsoapProxy->Citation->DescriptiveKeywords) = descriptiveKeywords;
	}

}

void AbstractObject::serializeIntoStream(ostream * stream)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!stream)
		throw invalid_argument("The stream where the entity will be stored cannot be null.");

	string xmlTagIncludingNamespace = getXmlNamespace() + ":"+ getXmlTag();

	gsoapProxy->soap->os = stream;
	( soap_begin_send(gsoapProxy->soap) || soap_send(gsoapProxy->soap, gsoapProxy->soap->prolog ? gsoapProxy->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
		(gsoapProxy->soap_serialize(gsoapProxy->soap), 0) ||
		gsoapProxy->soap_put(gsoapProxy->soap, xmlTagIncludingNamespace.c_str(), NULL) ||
		soap_end_send(gsoapProxy->soap) );
}

eml__DataObjectReference* AbstractObject::newResqmlReference() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	ostringstream oss;

	eml__DataObjectReference* result = soap_new_eml__DataObjectReference(gsoapProxy->soap, 1);
	result->UUID = getUuid();
	result->VersionString = soap_new_std__string(gsoapProxy->soap, 1);
	if (getLastUpdate() != -1)
		oss << getLastUpdate();
	else
		oss << getCreation();
	result->VersionString->assign(oss.str());
	result->Title = gsoapProxy->Citation->Title;
	result->ContentType = getContentType();

	return result;
}

gsoap_resqml2_0::resqml2__ContactElementReference* AbstractObject::newResqmlContactElementReference() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	ostringstream oss;

	resqml2__ContactElementReference* result = soap_new_resqml2__ContactElementReference(gsoapProxy->soap, 1);
	result->UUID = getUuid();
	result->VersionString = soap_new_std__string(gsoapProxy->soap, 1);
	if (getLastUpdate() != -1)
		oss << getLastUpdate();
	else
		oss << getCreation();
	result->VersionString->assign(oss.str());
	result->Title = gsoapProxy->Citation->Title;
	result->ContentType = getContentType();

	return result;
}

string AbstractObject::getContentType() const
{
	return "application/x-resqml+xml;version=2.0;type=obj_" + getXmlTag();
}

std::string AbstractObject::getPartNameInEpcDocument() const
{
	return "obj_" + getXmlTag() + "_" + getUuid() + ".xml";
}

string AbstractObject::serializeIntoString()
{
	ostringstream oss;

	serializeIntoStream(&oss);

	return oss.str();
}

void AbstractObject::addOrSetAlias(const std::string & authority, const std::string & title)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	for (unsigned int i = 0; i < static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases.size(); i++)
	{
		if (static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases[i]->authority &&
			static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases[i]->authority->compare(authority) == 0)
		{
			static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases[i]->Identifier = title;
			return;
		}
	}

	eml__ObjectAlias* alias = soap_new_eml__ObjectAlias(gsoapProxy->soap, 1);
	alias->authority = soap_new_std__string(gsoapProxy->soap, 1);
	alias->authority->assign(authority);
	alias->Identifier = title;
	static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->Aliases.push_back(alias);
}

string AbstractObject::getAliasTitle(const std::string & authority)
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	string result = "";

	for (unsigned int i = 0; i < static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases.size(); i++)
	{
		if (static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases[i]->authority &&
			static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases[i]->authority->compare(authority) == 0)
		{
			return static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases[i]->Identifier;
		}
	}

	return result;
}

unsigned int AbstractObject::getAliasCount() const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata.size();
}

std::string AbstractObject::getAliasAuthorityAtIndex(const unsigned int & index) const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	if ((static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases)[index]->authority)
		return *((static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases)[index]->authority);
	else
		return "";
}

std::string AbstractObject::getAliasTitleAtIndex(const unsigned int & index) const
{
	if (!gsoapProxy)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<eml__AbstractCitedDataObject*>(gsoapProxy)->Aliases)[index]->Identifier;
}
