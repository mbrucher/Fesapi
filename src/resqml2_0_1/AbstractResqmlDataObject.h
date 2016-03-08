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

#if defined(_WIN32) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractResqmlDataObject : public resqml2::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractResqmlDataObject(common::EpcDocument * epcDoc, gsoap_resqml2_0_1::eml__DataObjectReference* partialObject) : resqml2::AbstractObject(epcDoc, partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractResqmlDataObject(): AbstractObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractResqmlDataObject(gsoap_resqml2_0_1::resqml2__AbstractResqmlDataObject* fromGsoap): AbstractObject(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractResqmlDataObject() {}

		/**
		* Add or set (if already exists) an extra metadata (not a standard one)
		*/
		void addOrSetExtraMetadata(const std::string & key, const std::string & value);

		/**
		* Getter (in read only mode) of all the extra metadata
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > getExtraMetadataSet() const;
#else
		std::tr1::unordered_map< std::string, std::string > getExtraMetadataSet() const;
#endif

		/**
		* Get an extra metadata according its key.
		* @return An empty string if the extra metadata does not exist. Or the extra metadata value if it exists
		*/
		std::string getExtraMetadata(const std::string & key);

		/**
		* Get the count of extra metadata in the instance.
		*/
		unsigned int getExtraMetadataCount() const;

		/**
		* Get the key of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataKeyAtIndex(const unsigned int & index) const;

		/**
		* Get the string value of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataStringValueAtIndex(const unsigned int & index) const;
	};
}
