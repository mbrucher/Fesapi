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

#include "resqml2_0_1/Activity.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT ActivityTemplate : public AbstractResqmlDataObject
	{
	public:

		/**
		* Creates an instance of this class in a gsoap context.
		* @param epcDoc		The Epc document which contains the activity template
		* @param guid		The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		ActivityTemplate(common::EpcDocument* epcDoc, const std::string & guid, const std::string & title);

		ActivityTemplate(gsoap_resqml2_0_1::_resqml2__ActivityTemplate* fromGsoap): AbstractResqmlDataObject(fromGsoap) {}
		virtual ~ActivityTemplate() {}
		
		/**
		* Push back a parameter in the activity template instance.
		* This parameter must not be of a data object kind.
		*/
		void pushBackParameter(const std::string title,
			const gsoap_resqml2_0_1::resqml2__ParameterKind & kind,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const unsigned int & maxOccurs);

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must be of a data object kind.
		*/
		void pushBackDataObjectParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const unsigned int & maxOccurs,
			const std::string & dataObjetContentType);

		const std::string & getParameterTitle(const unsigned int & index) const;
		const std::vector<gsoap_resqml2_0_1::resqml2__ParameterKind> & getParameterAllowedKinds(const unsigned int & index) const;
		const bool & getParameterIsInput(const unsigned int & index) const;
		const bool & getParameterIsOutput(const unsigned int & index) const;
		const unsigned int getParameterMinOccurences(const unsigned int & index) const;
		const unsigned int getParameterMaxOccurences(const unsigned int & index) const;

		const std::vector<Activity*> & getActivitySet() const {return activitySet;}

		//******************************************************************
		//******************** MANDATORY FOR GsoapWrapper ******************
		//******************************************************************
		
		std::string getResqmlVersion() const;

		static const char* XML_TAG;
		std::string getXmlTag() const {return XML_TAG;}

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument * epcDoc) {}

	private:
		
        std::vector<Activity*> activitySet;

		friend void Activity::setActivityTemplate(ActivityTemplate* activityTemplate);
	};
}
