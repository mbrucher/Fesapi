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
#pragma once

#include "gsoap_resqml2_0_1H.h"
#include "EpcDocument.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractObject
	{
	protected:
		
		gsoap_resqml2_0_1::eml__AbstractCitedDataObject* gsoapProxy;
		common::EpcDocument* epcDocument;
		std::vector<class Activity*> activitySet;

		bool updateXml; /// Indicate wether methods update the XML (Gsoap) or only the C++ classes of the API.

		AbstractObject(gsoap_resqml2_0_1::eml__AbstractCitedDataObject* proxy = NULL) : gsoapProxy(proxy), epcDocument (NULL), updateXml(true) {}

		/**
		* Create or set a new GUID for the resqml instance.
		* @param guid				The guid to set to the resqml instance. If empty then a new guid will be generated.
		*/
		void addNewGuid(const std::string & newGuid);

		friend void common::EpcDocument::addGsoapProxy(AbstractObject* proxy);
		friend class Activity; // necessary cause of cyclic include if we try : friend class Activity::pushBackResqmlObjectParameter(const std::string title, AbstractObject* resqmlObject);

		void initMandatoryMetadata();

	public:
		virtual ~AbstractObject() {}

		std::string getUuid() const;
		std::string getTitle() const;
		std::string getEditor() const;
		time_t getCreation() const;
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;

		void setUuid(const std::string & uuid);
		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);

		/**
		* Create a new GUID for the resqml instance.
		* Set a title and other default metadata for the resqml instance.
		* @param guid				The guid to set to the resqml instance. If empty then a new guid will be generated.
		* @apram title				The title to set to the resqml instance
		*/
		void setMetadata(const std::string & guid, const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);

		/**
		* Get the gsoap proxy which is wrapped by this entity
		*/
		gsoap_resqml2_0_1::eml__AbstractCitedDataObject* getGsoapProxy() {return gsoapProxy;}

		/**
		* Serialize the instance into a stream.
		* @param stream	The stream must be opened for writing and won't be closed.
		*/
		void serializeIntoStream(std::ostream * stream);

		/**
		* Get the Gsoap type of the wrapped element
		*/
		int getGsoapType() const {return gsoapProxy->soap_type();}

		gsoap_resqml2_0_1::eml__DataObjectReference* newResqmlReference() const;

		gsoap_resqml2_0_1::resqml2__ContactElementReference* newResqmlContactElementReference() const;

		/**
		 * Return the EPC document which contains this gsoap wrapper.
		 */
		common::EpcDocument* getEpcDocument() const {return epcDocument;}

		/**
		* Resolve all relationships of the object in an epc document
		*/
		virtual void importRelationshipSetFromEpc(common::EpcDocument * epcDoc) = 0;

		/**
		* Get the XML namespace for the tags for the XML serialization of this instance
		*/
		virtual std::string getXmlNamespace() const {return "eml";}

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		virtual std::string getXmlTag() const = 0;

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		virtual std::string getResqmlVersion() const;

		/**
		* Get the content type of the instance according to EPC recommendation
		*/
		std::string getContentType() const;
		
		/**
		* Get part name of this XML top level instance in the EPC document
		*/
		std::string getPartNameInEpcDocument() const;

		/**
		* Return all relationships (backward and forward ones) of the instance using EPC format.
		*/
		virtual std::vector<epc::Relationship> getAllEpcRelationships() const = 0;

		/**
		* Serialize the gsoap proxy into a string
		*/
		std::string serializeIntoString();	

		/**
		* Add or set (if already exists) an alias for this object
		*/
		void addOrSetAlias(const std::string & authority, const std::string & title);

		/**
		* Get an alias according its authority.
		* @return An empty string if the authority does not exist. Or the alias title if it exists
		*/
		std::string getAliasTitle(const std::string & authority);

		/**
		* Get the count of extra metadata in the instance.
		*/
		unsigned int getAliasCount() const;

		/**
		* Get the alias authority at a particular index in the aliases set.
		*/
		std::string getAliasAuthorityAtIndex(const unsigned int & index) const;

		/**
		* Get the alias title at a particular index in the aliases set.
		*/
		std::string getAliasTitleAtIndex(const unsigned int & index) const;

		/**
		* Get all the activities where the instance is involved.
		*/
		const std::vector<class Activity*> & getActivitySet() const {return activitySet;}
	};
}
