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

#include "resqml2_0/AbstractProperty.h"

namespace resqml2_0
{
	class DLL_IMPORT_OR_EXPORT AbstractValuesProperty : public AbstractProperty
	{
	public:

		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG = 3, ULONG = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};

		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractValuesProperty() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractValuesProperty(gsoap_resqml2_0::resqml2__AbstractValuesProperty* fromGsoap): AbstractProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractValuesProperty() {}

		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		/**
		* Get the values datatype in the HDF dataset
		*/
		AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		long getLongValuesOfPatch(const unsigned int & patchIndex, long * values);

		/**
		* Get the null value of the instance which are supposed to be integer ones.
		* Not for continuous property values.
		* @return the null value
		*/
		long getNullValueOfPatch(const unsigned int & patchIndex);

		/**
		* Get all the values of the instance which are supposed to be unsigned long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned long getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values);

		/**
		* Get all the values of the instance which are supposed to be int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		int getIntValuesOfPatch(const unsigned int & patchIndex, int * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned int getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values);
		
		/**
		* Get all the values of the instance which are supposed to be short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		short getShortValuesOfPatch(const unsigned int & patchIndex, short * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned short getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values);

		/**
		* Get all the values of the instance which are supposed to be char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		char getCharValuesOfPatch(const unsigned int & patchIndex, char * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned char getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values);
	};
}
