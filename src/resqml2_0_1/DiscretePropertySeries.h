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

#include "resqml2_0_1/DiscreteProperty.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT DiscretePropertySeries : public DiscreteProperty
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DiscretePropertySeries(gsoap_resqml2_0_1::eml__DataObjectReference* partialObject) : DiscreteProperty(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param energisticsPropertyKind	The property type of these property values which must be defined in the standard energistics property type dictionary.
		* @param ts							The associated time series.
		* @param useInterval				Indicates wether the property values will be attached to the time index or to the interval between consecutive time index. 
		*/
		DiscretePropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param localPropKind				The property type of these property values which must be defined in the EPC document as a local property kind.
		* @param ts							The associated time series.
		* @param useInterval				Indicates wether the property values will be attached to the time index or to the interval between consecutive time index. 
		*/
		DiscretePropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2::PropertyKind * localPropKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DiscretePropertySeries(gsoap_resqml2_0_1::_resqml2__DiscretePropertySeries* fromGsoap): DiscreteProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~DiscretePropertySeries() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::string getResqmlVersion() const {return "2.0.1";}

	protected:
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);
	};
}
