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

#include "resqml2_0_1/AbstractRepresentation.h"

#include <fstream>
#include <iostream>

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation : public AbstractResqmlDataObject
	{
	protected:
		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractFeatureInterpretation(): interpretedFeature(nullptr) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractFeatureInterpretation(gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation* fromGsoap): AbstractResqmlDataObject(fromGsoap), interpretedFeature(nullptr) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractFeatureInterpretation() {}

		/**
		 * Set the feature which is interpreted by the current instance.
		 */
		void setInterpretedFeature(class AbstractFeature * feature);

		/**
		* Get the feature this instance interprets
		*/
		class AbstractFeature* getInterpretedFeature() const {return interpretedFeature;}

		/**
		* Get the feature uuid this instance interprets
		*/
		std::string getInterpretedFeatureUuid() const;

		/**
		* Get all the representations of this interpretation
		*/
		std::vector<AbstractRepresentation*> getRepresentationSet() const {return representationSet;}

		/**
		 * Get the interpretation count of this feature.
		 */
		unsigned int 						getRepresentationCount() const {return representationSet.size();}

		/**
		 * Get a particular interpretation of this feature according to its position in the interpretation ordering.
		 */
		AbstractRepresentation*				getRepresentation(const unsigned int & index) const {if (representationSet.size() > index) return representationSet[index]; else return nullptr;}

		/**
		* Set the domain of the interpretation
		*/
		void setDomain(const gsoap_resqml2_0_1::resqml2__Domain & domain);

		/**
		* Set the domain of the interpretation
		*/
		gsoap_resqml2_0_1::resqml2__Domain getDomain() const;

		/**
		* Indicates that this interpretation is a frontier of a stack of an organization
		* BE CAREFUL : Does not add back this instance to the organization. It is assumed it is already done.
		*/		
		void setBottomFrontierOf(class StructuralOrganizationInterpretation* structOrg) {isBottomFrontierSet.push_back(structOrg);}
		void setTopFrontierOf(class StructuralOrganizationInterpretation* structOrg) {isTopFrontierSet.push_back(structOrg);}
		void setSideFrontierOf(class StructuralOrganizationInterpretation* structOrg) {isSideFrontierSet.push_back(structOrg);}

	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML Forward relationship
		class AbstractFeature *										interpretedFeature;

		// XML backward relationship
		std::vector<AbstractRepresentation *>						representationSet;
		std::vector<class StructuralOrganizationInterpretation *>	isBottomFrontierSet;
		std::vector<class StructuralOrganizationInterpretation *>	isTopFrontierSet;
		std::vector<class StructuralOrganizationInterpretation *>	isSideFrontierSet;

		friend void AbstractRepresentation::setInterpretation(AbstractFeatureInterpretation * interp);
	};
}
