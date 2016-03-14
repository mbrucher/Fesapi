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
#include "resqml2/AbstractObject.h"

#include <stdexcept>
#include <string>
#include <sstream>
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
#include <regex>
#endif

#include "tools/GuidTools.h"

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

using namespace std;
using namespace resqml2;
using namespace gsoap_resqml2_0_1;

/**
* Only for partial transfer
*/
AbstractObject::AbstractObject(common::EpcDocument * epcDoc, gsoap_resqml2_0_1::eml__DataObjectReference* partialObject):
	partialObject(partialObject), gsoapProxy2_0_1(nullptr), epcDocument (nullptr), updateXml(true)
{
}

soap* AbstractObject::getGsoapContext() const
{
	if (getGsoapProxy() == nullptr)
	{
		if (getEpcDocument() == nullptr)
		{
			return nullptr;
		}
		else
		{
			return getEpcDocument()->getGsoapContext();
		}
	}
	else
		return getGsoapProxy()->soap;
}

string AbstractObject::getUuid() const
{
	if (gsoapProxy2_0_1 == nullptr) // partial transfer
		return partialObject->UUID;
	else
		return gsoapProxy2_0_1->uuid;
}

string AbstractObject::getTitle() const
{
	if (gsoapProxy2_0_1 == nullptr) // partial transfer
		return partialObject->Title;
	else
		return gsoapProxy2_0_1->Citation->Title;
}

string AbstractObject::getEditor() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1->Citation->Editor)
		return *gsoapProxy2_0_1->Citation->Editor;
	else
		return "";
}

time_t AbstractObject::getCreation() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy2_0_1->Citation->Creation;
}

string AbstractObject::getOriginator() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy2_0_1->Citation->Originator;
}

string AbstractObject::getDescription() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1->Citation->Description)
		return *gsoapProxy2_0_1->Citation->Description;
	else
		return "";
}

time_t AbstractObject::getLastUpdate() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1->Citation->LastUpdate)
		return *gsoapProxy2_0_1->Citation->LastUpdate;
	else
		return -1;
}

string AbstractObject::getFormat() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return gsoapProxy2_0_1->Citation->Format;
}

string AbstractObject::getDescriptiveKeywords() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1->Citation->DescriptiveKeywords)
		return *gsoapProxy2_0_1->Citation->DescriptiveKeywords;
	else
		return "";
}

void AbstractObject::setUuid(const std::string & uuid)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (uuid.empty() == true)
		gsoapProxy2_0_1->uuid = tools::GuidTools::generateUidAsString();
	else
	{
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
		if (!regex_match(uuid, regex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}")))
			throw invalid_argument("The uuid " + uuid + " does not match the regular expression");
#endif
		gsoapProxy2_0_1->uuid = uuid;
	}
}

void AbstractObject::setTitle(const std::string & title)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (title.empty())
		gsoapProxy2_0_1->Citation->Title = "unknown";
	else
		gsoapProxy2_0_1->Citation->Title = title;
}

void AbstractObject::setEditor(const std::string & editor)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!editor.empty())
	{
		if (gsoapProxy2_0_1->Citation->Editor == nullptr)
			gsoapProxy2_0_1->Citation->Editor = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		gsoapProxy2_0_1->Citation->Editor->assign(editor);
	}
}

void AbstractObject::setCreation(const time_t & creation)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	gsoapProxy2_0_1->Citation->Creation = creation;
}

void AbstractObject::setOriginator(const std::string & originator)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (originator.empty())
		gsoapProxy2_0_1->Citation->Originator = "unknown";
	else
		gsoapProxy2_0_1->Citation->Originator = originator;
}

void AbstractObject::setDescription(const std::string & description)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!description.empty())
	{
		if (gsoapProxy2_0_1->Citation->Description == nullptr)
			gsoapProxy2_0_1->Citation->Description = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		gsoapProxy2_0_1->Citation->Description->assign(description);
	}
}

void AbstractObject::setLastUpdate(const time_t & lastUpdate)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1->Citation->LastUpdate == nullptr)
		gsoapProxy2_0_1->Citation->LastUpdate = (time_t *)soap_malloc(gsoapProxy2_0_1->soap, sizeof(time_t));
	*gsoapProxy2_0_1->Citation->LastUpdate = lastUpdate;
}

void AbstractObject::setFormat(const std::string & format)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (format.empty())
		gsoapProxy2_0_1->Citation->Format = "unknown";
	else
		gsoapProxy2_0_1->Citation->Format = format;
}

void AbstractObject::setDescriptiveKeywords(const std::string & descriptiveKeywords)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!descriptiveKeywords.empty())
	{
		if (gsoapProxy2_0_1->Citation->DescriptiveKeywords == nullptr)
			gsoapProxy2_0_1->Citation->DescriptiveKeywords = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		gsoapProxy2_0_1->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
	}
}

void AbstractObject::initMandatoryMetadata()
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	setUuid("");

	gsoapProxy2_0_1->schemaVersion = getResqmlVersion();

	gsoapProxy2_0_1->Citation = soap_new_eml__Citation(gsoapProxy2_0_1->soap, 1);

	//title
	gsoapProxy2_0_1->Citation->Title = "UNKNOWN TITLE";
	
	// Created time
	time_t now;
	time ( &now );
	gsoapProxy2_0_1->Citation->Creation = now;

	// Creator
#if defined(__gnu_linux__) || defined(__APPLE__)
    register struct passwd *pw;
    register uid_t uid;
                
    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw)
            gsoapProxy2_0_1->Citation->Originator = pw->pw_name;
    else
            gsoapProxy2_0_1->Citation->Originator = "UNKNOWN CREATOR";
#elif defined(_WIN32)
	char acUserName[32];
	DWORD nUserName = sizeof(acUserName);
	GetUserName(acUserName, &nUserName);
    gsoapProxy2_0_1->Citation->Originator = acUserName;
#endif

	//FORMAT
    gsoapProxy2_0_1->Citation->Format = "[F2I-CONSULTING:fesapi]";
}

void AbstractObject::setMetadata(const std::string & guid, const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!guid.empty())
		setUuid(guid);

	if (!title.empty())
		gsoapProxy2_0_1->Citation->Title = title;

	if (!editor.empty())
	{
		if (gsoapProxy2_0_1->Citation->Editor == nullptr)
			gsoapProxy2_0_1->Citation->Editor = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		*(gsoapProxy2_0_1->Citation->Editor) = editor;
	}

	if (creation > 0)
		gsoapProxy2_0_1->Citation->Creation = creation;

	if (!originator.empty())
		gsoapProxy2_0_1->Citation->Originator = originator;

	if (!description.empty())
	{
		if (gsoapProxy2_0_1->Citation->Description == nullptr)
			gsoapProxy2_0_1->Citation->Description = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		*(gsoapProxy2_0_1->Citation->Description) = description;
	}

	if (creation >0)
	{
		if (gsoapProxy2_0_1->Citation->LastUpdate == nullptr)
			gsoapProxy2_0_1->Citation->LastUpdate = (time_t *)soap_malloc(gsoapProxy2_0_1->soap, sizeof(time_t));
		*(gsoapProxy2_0_1->Citation->LastUpdate) = lastUpdate;
	}

	if (!format.empty())
		gsoapProxy2_0_1->Citation->Format = format;

	if (!descriptiveKeywords.empty())
	{
		if (gsoapProxy2_0_1->Citation->DescriptiveKeywords == nullptr)
			gsoapProxy2_0_1->Citation->DescriptiveKeywords = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		*(gsoapProxy2_0_1->Citation->DescriptiveKeywords) = descriptiveKeywords;
	}

}

void AbstractObject::serializeIntoStream(ostream * stream)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!stream)
		throw invalid_argument("The stream where the entity will be stored cannot be null.");

	string xmlTagIncludingNamespace = getXmlNamespace() + ":"+ getXmlTag();

	gsoapProxy2_0_1->soap->os = stream;
	( soap_begin_send(gsoapProxy2_0_1->soap) || soap_send(gsoapProxy2_0_1->soap, gsoapProxy2_0_1->soap->prolog ? gsoapProxy2_0_1->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
		(gsoapProxy2_0_1->soap_serialize(gsoapProxy2_0_1->soap), 0) ||
		gsoapProxy2_0_1->soap_put(gsoapProxy2_0_1->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
		soap_end_send(gsoapProxy2_0_1->soap) );
}

eml__DataObjectReference* AbstractObject::newResqmlReference() const
{
	ostringstream oss;

	eml__DataObjectReference* result = soap_new_eml__DataObjectReference(getGsoapContext(), 1);
	result->UUID = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (gsoapProxy2_0_1 != nullptr) // Not partial transfer
	{
		result->VersionString = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		if (getLastUpdate() != -1)
			oss << getLastUpdate();
		else
			oss << getCreation();
		result->VersionString->assign(oss.str());
	}

	return result;
}

gsoap_resqml2_0_1::resqml2__ContactElementReference* AbstractObject::newResqmlContactElementReference() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	ostringstream oss;

	resqml2__ContactElementReference* result = soap_new_resqml2__ContactElementReference(gsoapProxy2_0_1->soap, 1);
	result->UUID = getUuid();
	result->VersionString = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
	if (getLastUpdate() != -1)
		oss << getLastUpdate();
	else
		oss << getCreation();
	result->VersionString->assign(oss.str());
	result->Title = gsoapProxy2_0_1->Citation->Title;
	result->ContentType = getContentType();

	return result;
}

std::string AbstractObject::getXmlNamespace() const
{
	int soaptype = getGsoapType();
	if (soaptype == SOAP_TYPE_gsoap_resqml2_0_1_eml__obj_USCOREEpcExternalPartReference)
		return "eml";
#ifdef WITH_RESQML2_1
	else if (soaptype == SOAP_TYPE_gsoap_resqml2_1_eml__obj_USCOREEpcExternalPartReference)
		return "eml";
#endif
	else
		return "resqml2";
}

std::string AbstractObject::getResqmlVersion() const
{
	return "2.0";
}

string AbstractObject::getContentType() const
{
	return "application/x-resqml+xml;version=" + getResqmlVersion() + ";type=obj_" + getXmlTag();
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

void AbstractObject::addAlias(const std::string & authority, const std::string & title)
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	eml__ObjectAlias* alias = soap_new_eml__ObjectAlias(gsoapProxy2_0_1->soap, 1);
	alias->authority = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
	alias->authority->assign(authority);
	alias->Identifier = title;
	static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->Aliases.push_back(alias);
}

unsigned int AbstractObject::getAliasCount() const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->Aliases.size();
}

std::string AbstractObject::getAliasAuthorityAtIndex(const unsigned int & index) const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	if ((static_cast<eml__AbstractCitedDataObject*>(gsoapProxy2_0_1)->Aliases)[index]->authority)
		return *((static_cast<eml__AbstractCitedDataObject*>(gsoapProxy2_0_1)->Aliases)[index]->authority);
	else
		return "";
}

std::string AbstractObject::getAliasTitleAtIndex(const unsigned int & index) const
{
	if (gsoapProxy2_0_1 == nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<eml__AbstractCitedDataObject*>(gsoapProxy2_0_1)->Aliases)[index]->Identifier;
}
