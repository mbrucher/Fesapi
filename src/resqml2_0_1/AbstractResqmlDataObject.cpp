#include "resqml2_0_1/AbstractResqmlDataObject.h"

#include <stdexcept>

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

void AbstractResqmlDataObject::addOrSetExtraMetadata(const std::string & key, const std::string & value)
{
	for (unsigned int i = 0; i < static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata.size(); i++)
	{
		if (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata[i]->Name.compare(key) == 0)
		{
			static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata[i]->Value = value;
			return;
		}
	}

	resqml2__NameValuePair* stringPair = soap_new_resqml2__NameValuePair(gsoapProxy->soap, 1);
	stringPair->Name = key;
	stringPair->Value = value;
	static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata.push_back(stringPair);
}

#if defined(_WIN32) || defined(__APPLE__)
std::unordered_map< std::string, std::string > AbstractResqmlDataObject::getExtraMetadataSet() const
{
	std::unordered_map< std::string, std::string > result;
#else
std::tr1::unordered_map< std::string, std::string > AbstractResqmlDataObject::getExtraMetadataSet() const
{
	std::tr1::unordered_map< std::string, std::string > result;
#endif
	for (unsigned int i = 0; i < static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata.size(); i++)
	{
		result[static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata[i]->Name] = static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata[i]->Value;
	}

	return result;
}

string AbstractResqmlDataObject::getExtraMetadata(const std::string & key)
{
	string result = "";

	for (unsigned int i = 0; i < static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata.size(); i++)
	{
		if (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata[i]->Name.compare(key) == 0)
		{
			return static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata[i]->Value;
		}
	}

	return result;
}

unsigned int AbstractResqmlDataObject::getExtraMetadataCount() const
{
	return static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata.size();
}

std::string AbstractResqmlDataObject::getExtraMetadataKeyAtIndex(const unsigned int & index) const
{
	if (getExtraMetadataCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata)[index]->Name;
}

std::string AbstractResqmlDataObject::getExtraMetadataStringValueAtIndex(const unsigned int & index) const
{
	if (getExtraMetadataCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy)->ExtraMetadata)[index]->Value;
}
