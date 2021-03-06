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
#include "resqml2_0_1/SeismicLatticeFeature.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* SeismicLatticeFeature::XML_TAG = "SeismicLatticeFeature";

SeismicLatticeFeature::SeismicLatticeFeature(soap* soapContext, const string & guid, const string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESeismicLatticeFeature(soapContext, 1);
	_resqml2__SeismicLatticeFeature* seismicLattice = static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1);

	seismicLattice->InlineIndexIncrement = inlineIncrement;
	seismicLattice->CrosslineIndexIncrement = crosslineIncrement;
	seismicLattice->FirstInlineIndex = originInline;
	seismicLattice->FirstCrosslineIndex = originCrossline;
	seismicLattice->InlineCount = inlineCount;
	seismicLattice->CrosslineCount = crosslineCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

int SeismicLatticeFeature::getCrosslineIncrement() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->CrosslineIndexIncrement;
}
		
int SeismicLatticeFeature::getInlineIncrement() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->InlineIndexIncrement;
}
		
int SeismicLatticeFeature::getOriginCrossline() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->FirstCrosslineIndex;
}
		
int SeismicLatticeFeature::getOriginInline() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->FirstInlineIndex;
}

