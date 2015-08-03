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
#include "PolylineSetRepresentation.h"

#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "AbstractFeatureInterpretation.h"
#include "AbstractLocal3dCrs.h"
#include "HdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* PolylineSetRepresentation::XML_TAG = "PolylineSetRepresentation";

void PolylineSetRepresentation::init(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
									 const std::string & guid, const std::string & title)
{
	gsoapProxy = soap_new_resqml2__obj_USCOREPolylineSetRepresentation(crs->getGsoapProxy()->soap, 1);
	_resqml2__PolylineSetRepresentation* polylineSetRep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationships
	if (interp != nullptr)
		setInterpretation(interp);

	localCrs = crs;
	localCrs->addRepresentation(this);

	// epc document
	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

PolylineSetRepresentation::PolylineSetRepresentation(common::EpcDocument * epcDoc, AbstractLocal3dCrs * crs, const string & guid, const string & title):
	AbstractRepresentation(nullptr, crs)
{
	init(nullptr, crs, guid, title);
}

PolylineSetRepresentation::PolylineSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
													 const std::string & guid, const std::string & title):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title);
}

PolylineSetRepresentation::PolylineSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
													 const std::string & guid, const std::string & title,
													 const resqml2__LineRole & roleKind):
	AbstractRepresentation(interp, crs)
{
	init(interp, crs, guid, title);
	static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy->soap, sizeof(resqml2__LineRole));
	(*static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LineRole) = roleKind;
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, const bool & allPolylinesClosedFlag,
				HdfProxy * proxy)
{
	resqml2__PolylineSetPatch* patch = soap_new_resqml2__PolylineSetPatch(gsoapProxy->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.size();

	// node count
	resqml2__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlNodeCountPerPolyline->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << patch->PatchIndex;
	xmlNodeCountPerPolyline->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/" + ossForHdf.str();
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim[1] = {polylineCount};
	proxy->writeArrayNd(gsoapProxy->uuid,
		ossForHdf.str(), H5::PredType::NATIVE_UINT,
		NodeCountPerPolyline,
		dim, 1);

	// closed polylines
	resqml2__BooleanConstantArray* xmlClosedPolylines = soap_new_resqml2__BooleanConstantArray(gsoapProxy->soap, 1);
	xmlClosedPolylines->Count = polylineCount;
	xmlClosedPolylines->Value = allPolylinesClosedFlag;
	patch->ClosedPolylines = xmlClosedPolylines;

	// XYZ points
	unsigned int NodeCount = 0;
	for (unsigned int i = 0; i < polylineCount; ++i)
		NodeCount += NodeCountPerPolyline[i];
	hsize_t pointCountDims[] = {NodeCount};
	patch->Geometry = createPointGeometryPatch(patch->PatchIndex, nodes, pointCountDims, 1, proxy);

	static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.push_back(patch);
}

void PolylineSetRepresentation::pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, bool * polylineClosedFlags,
				HdfProxy * proxy)
{
	resqml2__PolylineSetPatch* patch = soap_new_resqml2__PolylineSetPatch(gsoapProxy->soap, 1);
	patch->PatchIndex = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.size();

	// node count
	resqml2__IntegerHdf5Array* xmlNodeCountPerPolyline = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	xmlNodeCountPerPolyline->NullValue = (std::numeric_limits<int>::max)();
	xmlNodeCountPerPolyline->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlNodeCountPerPolyline->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "NodeCountPerPolyline_patch" << patch->PatchIndex;
	xmlNodeCountPerPolyline->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/" + ossForHdf.str();
	patch->NodeCountPerPolyline = xmlNodeCountPerPolyline;
	// ************ HDF *************
	hsize_t dim[1] = {polylineCount};
	proxy->writeArrayNd(gsoapProxy->uuid,
		ossForHdf.str(), H5::PredType::NATIVE_UINT,
		NodeCountPerPolyline,
		dim, 1);

	// closed polylines
	resqml2__BooleanHdf5Array* xmlClosedPolylines = soap_new_resqml2__BooleanHdf5Array(gsoapProxy->soap, 1);
	xmlClosedPolylines->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	xmlClosedPolylines->Values->HdfProxy = proxy->newResqmlReference();
	ossForHdf.str("");
	ossForHdf.clear();
	ossForHdf << "ClosedPolylines_patch" << patch->PatchIndex;
	xmlClosedPolylines->Values->PathInHdfFile = "/RESQML/" + gsoapProxy->uuid + "/" + ossForHdf.str();
	patch->ClosedPolylines = xmlClosedPolylines;
	// ************ HDF *************
	proxy->writeArrayNd(gsoapProxy->uuid,
		ossForHdf.str(), H5::PredType::NATIVE_UCHAR,
		polylineClosedFlags,
		dim, 1);

	// XYZ points
	unsigned int NodeCount = 0;
	for (unsigned int i = 0; i < polylineCount; ++i)
		NodeCount += NodeCountPerPolyline[i];
	hsize_t pointCountDims[] = {NodeCount};
	patch->Geometry = createPointGeometryPatch(patch->PatchIndex, nodes, pointCountDims, 1, proxy);

	static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.push_back(patch);
}

string PolylineSetRepresentation::getHdfProxyUuid() const
{
	string result = "";

	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[0];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			return static_cast<resqml2__IntegerHdf5Array*>(patch->NodeCountPerPolyline)->Values->HdfProxy->UUID;
		}
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		return static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->HdfProxy->UUID;
	}

	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

resqml2__PointGeometry* PolylineSetRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	if (patchIndex < static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.size() &&
		static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex]->Geometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__PointGeometry)
			return static_cast<resqml2__PointGeometry*>(static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex]->Geometry);
	else
		return NULL;
}

unsigned int PolylineSetRepresentation::getPolylineCountOfPatch(const unsigned int & patchIndex) const
{
	unsigned int result = 0;

	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		return static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Count;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		return hdfProxy->getElementCount(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);
	}

	return result;
}

unsigned int PolylineSetRepresentation::getPolylineCountOfAllPatches() const
{
	unsigned int result = 0;

	for (unsigned int i = 0; i < static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.size(); i++)
	{
		result += getPolylineCountOfPatch(i);
	}

	return result;
}

void PolylineSetRepresentation::getNodeCountPerPolylineInPatch(const unsigned int & patchIndex, unsigned int * NodeCountPerPolyline) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex];
	if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		resqml2__IntegerConstantArray* xmlNodeCountPerPolyline = static_cast<resqml2__IntegerConstantArray*>(patch->NodeCountPerPolyline);
		for (unsigned int i = 0; i < xmlNodeCountPerPolyline->Count; i++)
			NodeCountPerPolyline[i] = xmlNodeCountPerPolyline->Value;
	}
	else if (patch->NodeCountPerPolyline->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(patch->NodeCountPerPolyline)->Values->PathInHdfFile, NodeCountPerPolyline);
	}
}

void PolylineSetRepresentation::getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy);
	for (unsigned int i = 0; i < rep->LinePatch.size(); i++)
	{
		getNodeCountPerPolylineInPatch(i, NodeCountPerPolyline);
		NodeCountPerPolyline += getPolylineCountOfPatch(i);
	}
}

unsigned int PolylineSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	unsigned int NodeCount = 0;

	unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
	unsigned int* NodeCountPerPolyline = new unsigned int[polylineCount];

	getNodeCountPerPolylineInPatch(patchIndex, NodeCountPerPolyline);
	for (unsigned int NodeCountPerPolylineIndex = 0; NodeCountPerPolylineIndex < polylineCount; NodeCountPerPolylineIndex++)
	{
		NodeCount += NodeCountPerPolyline[NodeCountPerPolylineIndex];
	}

	delete [] NodeCountPerPolyline;
	return NodeCount;
}

unsigned int PolylineSetRepresentation::getPatchCount() const
{
    return static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch.size();
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfPatch(const unsigned int & patchIndex) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		return static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Value;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
		H5::DataType datatype = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);

		bool result = true;
		if (datatype == H5::PredType::NATIVE_CHAR)
		{
			char* tmp = new char[polylineCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_UCHAR)
		{
			unsigned char* tmp = new unsigned char[polylineCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_SHORT)
		{
			short* tmp = new short[polylineCount];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_USHORT)
		{
			unsigned short* tmp = new unsigned short[polylineCount];
			hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_INT)
		{
			int* tmp = new int[polylineCount];
			hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_UINT)
		{
			unsigned int* tmp = new unsigned int[polylineCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_LONG)
		{
			long* tmp = new long[polylineCount];
			hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_ULONG)
		{
			unsigned long* tmp = new unsigned long[polylineCount];
			hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			if (find(tmp, tmp + polylineCount, 0) != tmp + polylineCount)
				result = false;
			delete [] tmp;
		}
		else
			throw logic_error("Not yet implemented.");

		return result;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesClosedOfAllPatches() const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy);
	for (unsigned int patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++)
	{
		if (areAllPolylinesClosedOfPatch(patchIndex) == false)
			return false;
	}

	return true;
}

bool isNotZero(const long & i)
{
	return i != 0;
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfPatch(const unsigned int & patchIndex) const
{
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		return static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Value == false;
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
		H5::DataType datatype = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);

		bool result = true;
		if (datatype == H5::PredType::NATIVE_CHAR)
		{
			char* tmp = new char[polylineCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](char i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_UCHAR)
		{
			unsigned char* tmp = new unsigned char[polylineCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned char i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_SHORT)
		{
			short* tmp = new short[polylineCount];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](short i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_USHORT)
		{
			unsigned short* tmp = new unsigned short[polylineCount];
			hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned short i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_INT)
		{
			int* tmp = new int[polylineCount];
			hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](int i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_UINT)
		{
			unsigned int* tmp = new unsigned int[polylineCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned int i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_LONG)
		{
			long* tmp = new long[polylineCount];
			hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](long i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_ULONG)
		{
			unsigned long* tmp = new unsigned long[polylineCount];
			hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
#if (defined(_WIN32) && _MSC_VER >= 1600) || (__GNUC__ > 4 && __GNUC_MINOR__ > 4)
			if (find_if(tmp, tmp + polylineCount, [](unsigned long i){return i != 0;}) != tmp + polylineCount)
				result = false;
#else
			if (find_if(tmp, tmp + polylineCount, isNotZero) != tmp + polylineCount)
				result = false;
#endif
			delete [] tmp;
		}
		else
			throw logic_error("Not yet implemented.");

		return result;
	}
	else
		throw logic_error("Not yet implemented.");
}

bool PolylineSetRepresentation::areAllPolylinesNonClosedOfAllPatches() const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy);
	for (unsigned int patchIndex = 0; patchIndex < rep->LinePatch.size(); patchIndex++)
	{
		if (areAllPolylinesNonClosedOfPatch(patchIndex) == false)
			return false;
	}

	return true;
}
		
void PolylineSetRepresentation::getClosedFlagPerPolylineOfPatch(const unsigned int & patchIndex, bool * closedFlagPerPolyline) const
{
	unsigned int polylineCount = getPolylineCountOfPatch(patchIndex);
	resqml2__PolylineSetPatch* patch = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LinePatch[patchIndex];
	if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
	{
		fill(closedFlagPerPolyline, closedFlagPerPolyline + polylineCount, static_cast<resqml2__BooleanConstantArray*>(patch->ClosedPolylines)->Value);
	}
	else if (patch->ClosedPolylines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
	{
		H5::DataType datatype = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile);

		bool result = true;
		if (datatype == H5::PredType::NATIVE_CHAR)
		{
			char* tmp = new char[polylineCount];
			hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_UCHAR)
		{
			unsigned char* tmp = new unsigned char[polylineCount];
			hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_SHORT)
		{
			short* tmp = new short[polylineCount];
			hdfProxy->readArrayNdOfShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_USHORT)
		{
			unsigned short* tmp = new unsigned short[polylineCount];
			hdfProxy->readArrayNdOfUShortValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_INT)
		{
			int* tmp = new int[polylineCount];
			hdfProxy->readArrayNdOfIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_UINT)
		{
			unsigned int* tmp = new unsigned int[polylineCount];
			hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_LONG)
		{
			long* tmp = new long[polylineCount];
			hdfProxy->readArrayNdOfLongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else if (datatype == H5::PredType::NATIVE_ULONG)
		{
			unsigned long* tmp = new unsigned long[polylineCount];
			hdfProxy->readArrayNdOfULongValues(static_cast<resqml2__BooleanHdf5Array*>(patch->ClosedPolylines)->Values->PathInHdfFile, tmp);
			for (unsigned int i = 0; i < polylineCount; ++i)
				closedFlagPerPolyline[i] = tmp[i];
			delete [] tmp;
		}
		else
			throw logic_error("Not yet implemented.");
	}
	else
		throw logic_error("Not yet implemented.");
}

void PolylineSetRepresentation::getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const
{
	_resqml2__PolylineSetRepresentation* rep = static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy);
	for (unsigned int i = 0; i < rep->LinePatch.size(); i++)
	{
		getClosedFlagPerPolylineOfPatch(i, closedFlagPerPolyline);
		closedFlagPerPolyline += getPolylineCountOfPatch(i);
	}
}

bool PolylineSetRepresentation::hasALineRole() const
{
	return static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LineRole;
}

gsoap_resqml2_0_1::resqml2__LineRole PolylineSetRepresentation::getLineRole() const
{
	if (!hasALineRole())
		throw invalid_argument("The polylineSet doesn't have any role");

	return *(static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LineRole);
}

void PolylineSetRepresentation::setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole)
{
	if (hasALineRole() == false)
		static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LineRole = (resqml2__LineRole*)soap_malloc(gsoapProxy->soap, sizeof(resqml2__LineRole));

	(*static_cast<_resqml2__PolylineSetRepresentation*>(gsoapProxy)->LineRole) = lineRole;
}
