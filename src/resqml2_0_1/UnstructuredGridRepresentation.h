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

#include "resqml2_0_1/AbstractGridRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	private :
		void init(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & cellCount);

		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		UnstructuredGridRepresentation(common::EpcDocument * epcDoc, const std::string & guid, const std::string & title):AbstractGridRepresentation(epcDoc, guid, title) {}

		UnstructuredGridRepresentation(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & cellCount);

		UnstructuredGridRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs,
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
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get all the face indices of all the cells.
		 * @param faceIndices 			It must be pre allocated with the last value returned by getCumulativeFaceCountOfCells()
		 */
		void getFaceIndicesOfCells(ULONG64 * faceIndices) const;

		/**
		* Get the cumulative face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the first and in the second cell. Third value is the count of faces in the first and in the second and in the third cell. Etc...
		* Count of this array is equal to getCellCount()
		* A single face count should be at least 4.
		* @param cumulativeFaceCountPerCellIndex	It must be pre allocated with getCellCount()
		*/
		void getCumulativeFaceCountOfCells(ULONG64 * cumulativeFaceCountPerCell) const;

		/**
		* Less efficient than getCumulativeFaceCountOfCells.
		* Get the face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the second cell. etc...
		* @param faceCountPerCell	It must be pre allocated with getCellCount()
		*/
		void getFaceCountOfCells(ULONG64 * faceCountPerCell) const;

		/**
		* Detect if the face count per cell is constant in the grid.
		*/
		bool isFaceCountOfCellsConstant() const;

		/*
		* Get the constant face count per cell in the grid.
		*/
		unsigned int getConstantFaceCountOfCells() const;

		/**
		 * Get all the nodes of all the cells.
		 * @param nodes 			It must be pre allocated.
		 */
		void getNodesOfFaces(unsigned int * nodeIndices) const;

		/**
		* Get the cumulative node count per face. First value is the count of nodes in the first face.
		* Second value is the count of nodes in the first and in the second face. Third value is the count of nodes in the first and in the second and in the third face. Etc...
		* Count of this array is equal to getFaceCount()
		* A single node count should be at least 3.
		*/
		void getCumulativeNodeCountOfFaces(unsigned int * nodeCountPerFace) const;

		/**
		* Detect if the node count per face is constant in the grid.
		*/
		bool isNodeCountOfFacesContant() const;

		/*
		* Get the constant node count per face in the grid.
		*/
		unsigned int getConstantNodeCountOfFaces() const;

		/**
		 * Get the cell count
		 */
		ULONG64 getCellCount() const;

		/**
		 * Get the face count
		 */
		ULONG64 getFaceCount() const;

		/**
		 * Get the node count
		 */
		ULONG64 getNodeCount() const;

		/**
		 * Set the geometry
		 */
		void setGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, class AbstractHdfProxy * proxy,
				unsigned int * faceIndicesPerCell, unsigned int * faceIndicesCumulativeCountPerCell, const unsigned int & faceCount,
				unsigned int * nodeIndicesPerFace, unsigned int * nodeIndicesCumulativeCountPerFace, const unsigned int & nodeCount,
				const gsoap_resqml2_0_1::resqml2__CellShape & cellShape);

		/**
		 * Set a geometry which is only defined using tetrahedra.
		 */
		void setTetrahedraOnlyGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, const unsigned int & faceCount, class AbstractHdfProxy * proxy,
						unsigned int * faceIndicesPerCell, unsigned int * nodeIndicesPerFace);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		unsigned int getPatchCount() const {return 1;}
	};
}
