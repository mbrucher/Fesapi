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
	class DLL_IMPORT_OR_EXPORT MdDatum : public AbstractResqmlDataObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap						A gsoap context which will manage the memory and the serialization/deserialization of this instance.
		* @param guid						The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param locCrs						The local CRS where the ordinal are given
		* @param originKind					Indicates the kind of the MD reference point.
		* @param referenceLocationOrdinal1	The location of the MD reference point on the first axis of the local 3d CRS.
		* @param referenceLocationOrdinal2	The location of the MD reference point on the second axis of the local 3d CRS.
		* @param referenceLocationOrdinal3	The location of the MD reference point on the third axis of the local 3d CRS.
		*/
		MdDatum(common::EpcDocument * epcDoc, const std::string & guid, const std::string & title,
			class AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0::_resqml2__MdDatum* fromGsoap):AbstractResqmlDataObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~MdDatum() {}

		//******************************************************************
		//********** INHERITED FROM AbstractObjectWithDcMetadata ***********
		//******************************************************************

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		/**
		* Add a WellboreFeature trajectory which uses this MD information
		* Does not add the inverse relationship i.e. from the WellboreFeature trajectory to this MD information.
		*/
		void addWellboreTrajectoryRepresentation(class WellboreTrajectoryRepresentation* traj) {wellboreTrajectoryRepresentationSet.push_back(traj);}

		/**
		* Get the Local 3d CRS where the reference point ordinals are given
		*/
		class AbstractLocal3dCrs * getLocalCrs() {return local3dCrs;}

		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		std::string getLocalCrsUuid() const;

		/**
		* Getter (in read-only mode) of the first ordinal of the reference location.
		*/
		const double& getLocationOrdinal1() const;

		/**
		* Getter (in read-only mode) of the second ordinal of the reference location.
		*/
		const double& getLocationOrdinal2() const;

		/**
		* Getter (in read-only mode) of the third ordinal of the reference location.
		*/
		const double& getLocationOrdinal3() const;

		/**
		* Getter (in read-only mode) of the origin kind of the MD.
		*/
		const gsoap_resqml2_0::resqml2__MdReference& getOriginKind() const;

	protected:

		// XML forward relationship
		class AbstractLocal3dCrs * local3dCrs;

		// XML backward relationship
		std::vector<class WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
	};
}
