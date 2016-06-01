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
#pragma once

#include "resqml2/AbstractObject.h"

namespace resqml2_0_1 {
	class AbstractRepresentation;
	class AbstractProperty;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT EpcExternalPartReference : public AbstractObject
	{
	public:
		/**
		* @param soapContext				The soap context where the underlying gsoap proxy is going to be created.
		* @param packageDirAbsolutePath		The directory where the EPC document is stored. Must end with a slash or back-slash
		* @param externalFilePath			The relative path regarding packageDirectoryAbsolutePath where the external resource is located
		*/
		EpcExternalPartReference(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EpcExternalPartReference(gsoap_resqml2_0_1::_eml__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath):
			AbstractObject(fromGsoap), packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~EpcExternalPartReference() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since external reference has not forward relationships at all
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		std::vector<resqml2_0_1::AbstractRepresentation*> representationSourceObject;					/// All the representations that use this external reference.
		std::vector<resqml2_0_1::AbstractProperty*> propertySourceObject;								/// All the properties that use this external reference.
		std::string packageDirectoryAbsolutePath;												/// The directory where the EPC document is stored.
		std::string relativeFilePath;															/// Must be relative to the location of the package
	};
}