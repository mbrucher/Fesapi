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

#include "resqml2_0_1/AbstractLocal3dCrs.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT LocalDepth3dCrs : public AbstractLocal3dCrs
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap			A gsoap context which will manage the memory and the serialization/deserialization of this instance.
		* @param guid			The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title			A title for the instance to create.
		* @param originOrdinal1	The offset of the global 2d crs on its first axis.
		* @param originOrdinal2	The offset of the global 2d crs on its second axis.
		* @param originOrdinal3	The offset of the global depth.
		* @param arealRotation	The areal rotation in radians regarding the global 2d crs.
		*/
		LocalDepth3dCrs(common::EpcDocument * epcDoc, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const bool & isUpOriented = false, const unsigned int & verticalEpsgCode = 0);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		LocalDepth3dCrs(gsoap_resqml2_0_1::_resqml2__LocalDepth3dCrs* fromGsoap):
			AbstractLocal3dCrs(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		~LocalDepth3dCrs() {}

		//******************************************************************
		//********** INHERITED FROM AbstractObjectWithDcMetadata ***********
		//******************************************************************

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}
