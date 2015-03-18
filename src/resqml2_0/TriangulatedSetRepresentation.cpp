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
#include "resqml2_0/TriangulatedSetRepresentation.h"

#include <sstream>
#include <stdexcept>

#include "resqml2_0/AbstractFeatureInterpretation.h"
#include "resqml2_0/AbstractLocal3dCrs.h"
#include "resqml2_0/HdfProxy.h"

using namespace std;
using namespace resqml2_0;
using namespace gsoap_resqml2_0;
using namespace epc;

const char* TriangulatedSetRepresentation::XML_TAG = "TriangulatedSetRepresentation";

TriangulatedSetRepresentation::TriangulatedSetRepresentation(AbstractFeatureInterpretation* interp, AbstractLocal3dCrs * crs,
		const std::string & guid, const std::string & title):
	AbstractSurfaceRepresentation(interp, crs)
{
	gsoapProxy = soap_new_resqml2__obj_USCORETriangulatedSetRepresentation(interp->getGsoapProxy()->soap, 1);
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	setInterpretation(interp);

	localCrs = crs;
	localCrs->addRepresentation(this);

	// epc document
	if (interp->getEpcDocument())
		interp->getEpcDocument()->addGsoapProxy(this);
}

string TriangulatedSetRepresentation::getHdfProxyUuid() const
{
	string result = "";

	resqml2__TrianglePatch* patch = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy)->TrianglePatch[0];
	if (patch->Triangles->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		return static_cast<resqml2__IntegerHdf5Array*>(patch->Triangles)->Values->HdfProxy->UUID;
	}

	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry(0));
}

resqml2__PointGeometry* TriangulatedSetRepresentation::getPointGeometry(const unsigned int & patchIndex) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Geometry;
	else
		throw out_of_range("The patchIndex is out of range");
}

void TriangulatedSetRepresentation::pushBackTrianglePatch(
	const unsigned int & nodeCount, double * nodes,
	const unsigned int & triangleCount, unsigned int * triangleNodeIndices,
	HdfProxy * proxy)
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);

	resqml2__TrianglePatch* patch = soap_new_resqml2__TrianglePatch(gsoapProxy->soap, 1);
	patch->PatchIndex = triRep->TrianglePatch.size();
	triRep->TrianglePatch.push_back(patch);

	hsize_t pointCountDims[] = {nodeCount};
	patch->NodeCount = nodeCount;
	patch->Geometry = createPointGeometryPatch(patch->PatchIndex, nodes, pointCountDims, 1, proxy);
	patch->Geometry->LocalCrs = localCrs->newResqmlReference();

	patch->Count = triangleCount;
	resqml2__IntegerHdf5Array* hdfTriangles = soap_new_resqml2__IntegerHdf5Array(gsoapProxy->soap, 1);
	patch->Triangles = hdfTriangles;
	hdfTriangles->NullValue = (std::numeric_limits<int>::max)();
	hdfTriangles->Values = soap_new_eml__Hdf5Dataset(gsoapProxy->soap, 1);
	hdfTriangles->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdf;
	ossForHdf << "triangles_patch" << patch->PatchIndex;
	hdfTriangles->Values->PathInHdfFile = "/RESQML/" + triRep->uuid + "/" + ossForHdf.str();
	// ************ HDF *************
	hsize_t dim[2] = {triangleCount, 3};
	proxy->writeArrayNd(triRep->uuid,
		ossForHdf.str(), H5::PredType::NATIVE_UINT,
		triangleNodeIndices,
		dim, 2);
}

unsigned int TriangulatedSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->NodeCount;
	else
		throw out_of_range("The patchIndex is out of range");
}

unsigned int TriangulatedSetRepresentation::getTriangleCountOfPatch(const unsigned int & patchIndex) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);
	
	if (triRep->TrianglePatch.size() > patchIndex)
		return triRep->TrianglePatch[patchIndex]->Count;
	else
		throw out_of_range("The patchIndex is out of range");
}

unsigned int TriangulatedSetRepresentation::getTriangleCountOfAllPatches() const
{
	unsigned int result = 0;

	std::vector<resqml2__TrianglePatch * > patches = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy)->TrianglePatch;
	for (unsigned int i = 0; i < patches.size(); ++i)
		result += patches[i]->Count;

	return result;
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfPatch(const unsigned int & patchIndex, unsigned int * triangleNodeIndices) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);
	if (triRep->TrianglePatch[patchIndex]->Triangles->soap_type() == SOAP_TYPE_gsoap_resqml2_0_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(triRep->TrianglePatch[patchIndex]->Triangles)->Values->PathInHdfFile, triangleNodeIndices);
	}
}

void TriangulatedSetRepresentation::getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const
{
	_resqml2__TriangulatedSetRepresentation* triRep = static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy);
	unsigned int patchCount = triRep->TrianglePatch.size();
	for (unsigned int patchIndex = 0; patchIndex < patchCount; patchIndex++)
	{
		getTriangleNodeIndicesOfPatch(patchIndex, triangleNodeIndices);
		triangleNodeIndices += getTriangleCountOfPatch(patchIndex) * 3;
	}
}

unsigned int TriangulatedSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml2__TriangulatedSetRepresentation*>(gsoapProxy)->TrianglePatch.size();
}