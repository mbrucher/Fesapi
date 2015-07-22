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

#include "resqml2_0_1/AbstractGridRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const;

	public:

		UnstructuredGridRepresentation(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & cellCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		UnstructuredGridRepresentation(gsoap_resqml2_0_1::_resqml2__UnstructuredGridRepresentation* fromGsoap): AbstractGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~UnstructuredGridRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		unsigned int getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get all the faces of all the cells.
		 * @param faces 			It must be pre allocated.
		 */
		void getFacesOfCells(unsigned int * faceIndices) const;
		void getFaceCountOfCells(unsigned int * faceCountPerCell) const;

		/**
		 * Get all the nodes of all the cells.
		 * @param nodes 			It must be pre allocated.
		 */
		void getNodesOfFaces(unsigned int * nodeIndices) const;
		void getNodeCountOfFaces(unsigned int * NodeCountPerFace) const;

		/**
		 * Get the cell count
		 */
		unsigned long getCellCount() const;

		/**
		 * Get the face count
		 */
		unsigned long getFaceCount() const;

		/**
		 * Get the node count
		 */
		unsigned long getNodeCount() const;

		/**
		 * Set the geometry
		 */
		void setGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, class HdfProxy * proxy,
				unsigned int * faceIndicesPerCell, unsigned int * faceIndicesCumulativeCountPerCell, const unsigned int & faceCount,
				unsigned int * nodeIndicesPerFace, unsigned int * nodeIndicesCumulativeCountPerFace, const unsigned int & nodeCount,
				const gsoap_resqml2_0_1::resqml2__CellShape & cellShape);

		/**
		 * Set a geometry which is only defined using tetrahedra.
		 */
		void setTetrahedraOnlyGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, const unsigned int & faceCount, class HdfProxy * proxy,
						unsigned int * faceIndicesPerCell, unsigned int * nodeIndicesPerFace);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		unsigned int getPatchCount() const {return 1;}
	};
}
