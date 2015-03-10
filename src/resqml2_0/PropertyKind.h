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

#include "resqml2_0/AbstractResqmlDataObject.h"

namespace resqml2_0
{
	class DLL_IMPORT_OR_EXPORT PropertyKind : public AbstractResqmlDataObject
	{
	public:
		/**
		* Creates a local property type which derives from a standard Energistics property type.
		* @param epcDoc							the epc document where this intance will be stored.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param namingSystem					The name of the dictionary within which the property is unique.
		* @param uom							The unit of measure of the property type.
		* @param parentEnergisticsPropertyKind	The name of the parent property type in the Energistics property dictionary.
		*/
		PropertyKind(common::EpcDocument * epcDoc, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0::resqml2__ResqmlUom & uom, const gsoap_resqml2_0::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		/**
		* Creates a local property type which derives from another local property type.
		* @param epcDoc							the epc document where this intance will be stored.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param namingSystem					The name of the dictionary within which the property is unique.
		* @param uom							The unit of measure of the property type.
		* @param parentPropType					The local parent property type in the EPC document.
		*/
		PropertyKind(common::EpcDocument * epcDoc, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0::resqml2__ResqmlUom & uom, PropertyKind * parentPropType);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertyKind(gsoap_resqml2_0::_resqml2__PropertyKind* fromGsoap):AbstractResqmlDataObject(fromGsoap), parentPropertyKind(NULL) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PropertyKind() {}

		/**
		* Getter (in read only mode) of the naming system of this property type
		*/
		const std::string & getNamingSystem() const;

		/**
		* Get the unit of measure of the values of this property kind.
		*/
		const gsoap_resqml2_0::resqml2__ResqmlUom & getUom() const;

		/**
		* Get the unit of measure of the values of this property kind as a string.
		*/
		std::string getUomAsString() const;

		/**
		 * Get the title of the parent of this property kind.
		 */
		std::string getParentAsString() const;

		//******************************************************************
		//********** INHERITED FROM AbstractObjectWithDcMetadata ***********
		//******************************************************************

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Instantiate the link with the parent local property type.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		/**
		* Add a representation values object which uses this property type.
		* Does not add the inverse relationship i.e. from the representation values object to this property type.
		*/
		void addProperty(class AbstractProperty* repVal) {propertySet.push_back(repVal);}

	protected:

		// XML forward relationship
		PropertyKind* parentPropertyKind;

		// XML backward relationship
		std::vector<class AbstractProperty*> propertySet;
		std::vector<PropertyKind*> childPropertyKind;
	};
}

