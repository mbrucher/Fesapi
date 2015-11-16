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
#include "resqml2_0_1/IjkGridNoGeometryRepresentation.h"

#include <stdexcept>

#include "resqml2_0_1/AbstractFeatureInterpretation.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "nullptr_emulation.h"
#endif

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace resqml2_0_1;

IjkGridNoGeometryRepresentation::IjkGridNoGeometryRepresentation(common::EpcDocument* epcDoc,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(epcDoc, nullptr, guid, title, iCount, jCount, kCount)
{
}

IjkGridNoGeometryRepresentation::IjkGridNoGeometryRepresentation(AbstractFeatureInterpretation* interp,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(interp, nullptr, guid, title, iCount, jCount, kCount)
{
}

string IjkGridNoGeometryRepresentation::getHdfProxyUuid() const
{
	return "";
}

ULONG64 IjkGridNoGeometryRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	if (getParentGrid() != nullptr && getParentGrid()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREIjkGridRepresentation)
	{
		ULONG64 kIntervalCount =  getRegridIntervalCount('k');
		ULONG64* kChildCellCountPerInterval = new ULONG64[kIntervalCount];
		getRegridChildCellCountPerInterval('k', kChildCellCountPerInterval);
		ULONG64 jIntervalCount =  getRegridIntervalCount('j');
		ULONG64* jChildCellCountPerInterval = new ULONG64[jIntervalCount];
		getRegridChildCellCountPerInterval('j', jChildCellCountPerInterval);
		ULONG64 iIntervalCount =  getRegridIntervalCount('i');
		ULONG64* iChildCellCountPerInterval = new ULONG64[iIntervalCount];
		getRegridChildCellCountPerInterval('i', iChildCellCountPerInterval);
		
		ULONG64 kCount = 1;
		ULONG64 jCount = 1;
		ULONG64 iCount = 1;
		for (unsigned int kInterval = 0; kInterval < kIntervalCount; ++kInterval)
			kCount += kChildCellCountPerInterval[kInterval];
		for (unsigned int jInterval = 0; jInterval < jIntervalCount; ++jInterval)
			jCount += jChildCellCountPerInterval[jInterval];
		for (unsigned int iInterval = 0; iInterval < iIntervalCount; ++iInterval)
			iCount += iChildCellCountPerInterval[iInterval];

		delete [] kChildCellCountPerInterval;
		delete [] jChildCellCountPerInterval;
		delete [] iChildCellCountPerInterval;

		return iCount * jCount * kCount;
	}
	else if (getParentGrid() == nullptr)
	{
		return getCellCount(); // There should be only one XYZ (center) per cell
	}
	else
		throw logic_error("Not yet implemented. Please use parent window information or geometrical property information.");
}

void IjkGridNoGeometryRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	throw logic_error("Not yet implemented. Please use parent window information or geometrical property information.");
}

AbstractIjkGridRepresentation::geometryKind IjkGridNoGeometryRepresentation::getGeometryKind() const
{
	return NO_GEOMETRY;
}