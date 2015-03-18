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

#include "resqml2_0/AbstractTechnicalFeature.h"

namespace resqml2_0
{
	class DLL_IMPORT_OR_EXPORT SeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param epcDoc					The EPC document which will contain the seismic line.
		* @param guid					The guid to set to this instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param traceIndexIncrement	The trace index increment.
		*								The trace index increment will be the difference in the trace number from abscissa i=0 and abscissa i=1.
		*								The increment can be a positive or negative integer, but not zero.
		* @param firstTraceIndex		The index of the first trace beginning at abscissa i=0.
		* @param traceCount				The count of traces in this seismic line.
		*/
		SeismicLineFeature(common::EpcDocument* epcDoc, const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const int & firstTraceIndex, const unsigned int & traceCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SeismicLineFeature(gsoap_resqml2_0::_resqml2__SeismicLineFeature* fromGsoap): AbstractTechnicalFeature(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		~SeismicLineFeature() {}

		/**
		* Get the trace index increment between two consecutive traces.
		*/
		int getTraceIndexIncrement() const;
		
		/**
		* Get the first trace index.
		*/
		int getFirstTraceIndex() const;
		
		void setSeismicLineSet(class SeismicLineSetFeature * seisLineSet);

		class SeismicLineSetFeature* getSeismicLineSet() {return seismicLineSet;}

		/**
		* Get the total count of traces in this seismic line.
		*/
		unsigned int getTraceCount() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

	private:
		class SeismicLineSetFeature* seismicLineSet;
	};
}