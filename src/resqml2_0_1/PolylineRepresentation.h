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

#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT PolylineRepresentation : public AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const;

		/**
		 * Push back a representation for which the current instance is it outer ring.
		 * Does not add the inverse relationship i.e. from the representaiton to this outer ring.
		 */
		void pushBackRepresentationOuterRing(AbstractSurfaceRepresentation* rep) {outerRingOfSet.push_back(rep);}
		friend void AbstractSurfaceRepresentation::pushBackOuterRing(PolylineRepresentation * outerRing);

		/**
		 * Push back a representation for which the current instance is it inner ring.
		 * Does not add the inverse relationship i.e. from the representaiton to this inner ring.
		 */
		void pushBackRepresentationInnerRing(AbstractSurfaceRepresentation* rep) {innerRingOfSet.push_back(rep);}

		// Backward relationships
		std::vector<AbstractSurfaceRepresentation*> outerRingOfSet;
		std::vector<AbstractSurfaceRepresentation*> innerRingOfSet;

		void init(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The interpretation which this representation represents.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param roleKind				Indicates the role of this representation.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind,
			bool isClosed = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The interpretation which this representation represents.
		* @param crs					The local 3d crs where this representation is given.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isClosed				Indicates wether this line representaiton is closed or not.
		*/
		PolylineRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PolylineRepresentation(gsoap_resqml2_0_1::_resqml2__PolylineRepresentation* fromGsoap): AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PolylineRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * @param points		The points which constitute the polyline. Ordered by XYZ and then points.
		 * @param pointCount	The count of points in the polyline. Must be three times the count of the array of doubles "points".
		 * @param proxy			The HDf proxy defining the HDF file where the double array will be stored.
		 */
		void setGeometry(double * points, const unsigned int & pointCount, resqml2::AbstractHdfProxy* proxy);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Indicates if the representaiton is a closed polyline or a non closed polyline.
		*/
		bool isClosed() const;

		/**
		* Indicates if the polyline is associated to a particular LineRole.
		*/
		bool hasALineRole() const;
		
		/**
		* Indicates wether the instance corresponds to a seismic 2D line or not.
		*/
		bool isASeismicLine() const;

		/**
		* Indicates wether the instance corresponds to a facies 2d line or not.
		*/
		bool isAFaciesLine() const;

		/**
		* Get the role of this polyline.
		* Throw an exception if the polyline has no role (see method hasALineRole).
		*/
        gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;

		/**
		* Set the line role of this instance
		*/
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);

		unsigned int getPatchCount() const {return 1;}

	protected:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
	};
}
