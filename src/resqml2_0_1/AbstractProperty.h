/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2015) 

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

#include "resqml2_0_1/AbstractResqmlDataObject.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractProperty: public AbstractResqmlDataObject
	{
	public:
		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractProperty(): representation(NULL), localPropertyKind(NULL), timeSeries(NULL), local3dCrs(NULL), hdfProxy(NULL) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractProperty(gsoap_resqml2_0_1::resqml2__AbstractProperty* fromGsoap): AbstractResqmlDataObject(fromGsoap), representation(NULL), localPropertyKind(NULL), timeSeries(NULL), local3dCrs(NULL), hdfProxy(NULL) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractProperty() {}

		/**
		 * Get all the relationships of the property in an EPC format/context.
		 */
		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		 * Resolve all relationships in memory based on the XML relationships
		 */
		virtual void importRelationshipSetFromEpc(common::EpcDocument * epcDoc);

		/**
		* Get the unit of measure of the values of this property as a string.
		*/
		std::string getPropertyKindUomAsString() const;

		/**
		 * Get the title of the property kind of this property
		 */
		std::string getPropertyKindDescription() const;

		/**
		 * Get the title of the property kind of this property
		 */
		std::string getPropertyKindAsString() const;

		/**
		 * Get the title of the parent of the property kind.
		 */
		std::string getPropertyKindParentAsString() const;

		/**
		* Indicates if the property type attached to this property is either from the standard catalog of Energistics or from a local property type.
		*/
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;

		/**
		* Getter for the energistics property type which is associated to this intance.
		*/
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind() const;

		std::string getLocalPropertyKindUuid() const;

		/**
		* Getter for the local property type which is associated to this instance.
		* If NULL is returned then it means this instance is associated to an energistics standard property type.
		*/
		class PropertyKind* getLocalPropertyKind() const {return localPropertyKind;}

		/**
		 * Set the representation which is associated to the current property.
		 */
		void setRepresentation(class AbstractRepresentation * rep);

		/**
		* Getter for the representation which supports this instance values.
		*/
		class AbstractRepresentation* getRepresentation() {return representation;}

		/**
		 * Set the representation which is associated to the current property.
		 */
		void setTimeSeries(class TimeSeries * ts);

		/**
		* Getter for the representation which supports this instance values.
		*/
		class TimeSeries* getTimeSeries() {return timeSeries;}

		/**
		* Set the timestamp of this property by means of an index in a time series
		*/
		void setTimeIndex(const unsigned int & timeIndex, class TimeSeries * ts);

		/**
		* Get the timestamp of this property
		* @return maximum value of unsigned int is returned if no timestamp is allowed.
		*/
		time_t getTimestamp() const;

		/**
		* Set the timestep of this property
		*/
		void setTimeStep(const unsigned int & timeStep);

		/*
		 * Getter for the uuid of the representation which is described by this property
		 */
		std::string getRepresentationUuid() const;

		/**
		* Getter for the hdf proxy which stores this instance values.
		*/
		class HdfProxy* getHdfProxy() {return hdfProxy;}

		/*
		 * Getter for the uuid of the hdf proxy which is used for storing the numerical values of this property.
		 * An empty string is returned if no hd fproxy is used for storing the numerical values.
		 */
		std::string getHdfProxyUuid() const;

		/**
		* Getter (in read only mode) of the element count per property value.
		* If the property is a scalar one then it should be one.
		* If it is a vectorial one, the it should be more than one.
		* It is not possible to have some tensor property values (more dimension than a vector).
		*/
		unsigned int getElementCountPerValue() const;

		/**
		* Get the kind of elments the property values are attached to.
		*/
		gsoap_resqml2_0_1::resqml2__IndexableElements getAttachmentKind() const;

		void setHdfProxy(class HdfProxy * proxy);

	protected:

		class AbstractRepresentation *	representation;
		class PropertyKind *			localPropertyKind;
		class TimeSeries *				timeSeries;
		class AbstractLocal3dCrs *				local3dCrs;
		class HdfProxy *				hdfProxy;
	};
}
