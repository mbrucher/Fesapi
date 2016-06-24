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

namespace resqml2
{
	class WellboreTrajectoryRepresentation;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT MdDatum : public AbstractObject
	{
	protected :

		/**
		* Default constructor does nothing
		*/
		MdDatum() :AbstractObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0_1::_resqml2__MdDatum* fromGsoap) :AbstractObject(fromGsoap) {}

	public:
		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~MdDatum() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add a WellboreFeature trajectory which uses this MD information
		* Does not add the inverse relationship i.e. from the WellboreFeature trajectory to this MD information.
		*/
		void addWellboreTrajectoryRepresentation(resqml2_0_1::WellboreTrajectoryRepresentation* traj) { wellboreTrajectoryRepresentationSet.push_back(traj); }

		/**
		* Set the local CR Swhere the reference point ordinals are given
		*/
		void setLocalCrs(class AbstractLocal3dCrs * localCrs);

		/**
		* Get the Local 3d CRS where the reference point ordinals are given
		*/
		class AbstractLocal3dCrs * getLocalCrs() const;

		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		virtual std::string getLocalCrsUuid() const = 0;

		/**
		* Getter of the first ordinal of the reference location.
		*/
		virtual double getX() const = 0;
		virtual double getXInGlobalCrs() const = 0;

		/**
		* Getter of the second ordinal of the reference location.
		*/
		virtual double getY() const = 0;
		virtual double getYInGlobalCrs() const = 0;

		/**
		* Getter of the third ordinal of the reference location.
		*/
		virtual double getZ() const = 0;
		virtual double getZInGlobalCrs() const = 0;

	protected:

		virtual void setXmlLocalCrs(resqml2::AbstractLocal3dCrs * localCrs) = 0;

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML backward relationship
		std::vector<resqml2_0_1::WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
	};
}
