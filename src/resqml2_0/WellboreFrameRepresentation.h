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

#include "resqml2_0/AbstractRepresentation.h"
#include "resqml2_0/AbstractValuesProperty.h"

namespace witsml1_4_1_1
{
	class Log;
}

namespace resqml2_0
{
	class DLL_IMPORT_OR_EXPORT WellboreFrameRepresentation : public AbstractRepresentation
	{
	protected:
		gsoap_resqml2_0::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const {return NULL;}

		WellboreFrameRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs): AbstractRepresentation(interp, crs), trajectory(NULL), witsmlLog(NULL) {}

	public:

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp		The WellboreFeature interpretation the instance represents.
		* @param guid		The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param traj		The trajectory this WellboreFeature frame is based on.
		*/
		WellboreFrameRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0::_resqml2__WellboreFrameRepresentation* fromGsoap): AbstractRepresentation(fromGsoap), trajectory(NULL), witsmlLog(NULL)  {}

		~WellboreFrameRepresentation() {}

		/**
		* Set the MD values of this WellboreFeature frame to an array 1d of explicit values.
		* @param mdValues		All the MD values to set from top of the well trajectory to bottom.
		* @param numMdValues	The MD values count.
		* @param proxy			The HDF proxy where to write the MD values. It must be already opened for writing and won't be closed in this method.
		*/
		void setMdValuesAsArray1dOfExplicitValues(double * mdValues, const unsigned int & numMdValues, class HdfProxy * proxy);

		/**
		* Get the number of Md values in this WellboreFeature frame.
		*/
		unsigned int getMdValuesCount() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		unsigned int getXyzPointCountOfPatch(const unsigned int & patchIndex) const {return getMdValuesCount();}

		/**
		* Get the Measured Depth datatype in the HDF dataset
		*/
		AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;

		/**
		* Get all the md values of the instance which are supposed to be double ones.
		*/
		void getMdAsDoubleValues(double * values);

		/**
		* Get all the md values of the instance which are supposed to be float ones.
		*/
		void getMdAsFloatValues(float * values);

		/**
		* Get the associated resqml wellbore trajectory uuid
		*/
		std::string getWellboreTrajectoryUuid() const;

		/**
		* Get the associated resqml wellbore trajector
		*/
		class WellboreTrajectoryRepresentation* getWellboreTrajectory() {return trajectory;}

		std::string getLocalCrsUuid() const;

		std::string getHdfProxyUuid() const;

		unsigned int getPatchCount() const {return 1;}

		void setWitsmlLog(witsml1_4_1_1::Log * witsmlLogToSet);
		witsml1_4_1_1::Log* getWitsmlLog() {return witsmlLog;}

		//******************************************************************
		//******************** MANDATORY FOR GsoapWrapper ******************
		//******************************************************************

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;

		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

	protected:
		class WellboreTrajectoryRepresentation * trajectory;
		witsml1_4_1_1::Log * witsmlLog;
	};
}
