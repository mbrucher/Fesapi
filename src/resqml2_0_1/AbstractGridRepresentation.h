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

#include "resqml2_0_1/GridConnectionSetRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractGridRepresentation : public AbstractRepresentation
	{
	private:
		gsoap_resqml2_0_1::resqml2__Regrid* createRegrid(const unsigned int & indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount, double * childCellWeights,
														  const std::string & dimension);

	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractGridRepresentation(common::EpcDocument * epcDoc, gsoap_resqml2_0_1::eml__DataObjectReference* partialObject):AbstractRepresentation(epcDoc, partialObject)  {}

		AbstractGridRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs): AbstractRepresentation(interp, crs) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractGridRepresentation(gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* fromGsoap): AbstractRepresentation(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractGridRepresentation() {}

		std::vector<GridConnectionSetRepresentation*> getGridConnectionSetRepresentationSet() const {return gridConnectionSetRepresentationSet;}

		/**
		 * Get the GridConnectionSetRepresentation count into this EPC document which are associated to this grid.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		unsigned int getGridConnectionSetRepresentationCount() const {return gridConnectionSetRepresentationSet.size();}

		/**
		 * Get a particular ijk parametric grid according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		class GridConnectionSetRepresentation* getGridConnectionSetRepresentation(const unsigned int & index) const;

		/**
		* Get the count of (volumic) cells in the grid.
		*/
		virtual ULONG64 getCellCount() const = 0;

		/**
		* Get the parent grid of this grid.
		* @return	nullptr if the grid is not a child grid (not a LGR)
		*/
		AbstractGridRepresentation* getParentGrid() const;

		/**
		* Return the count of child grid in this grid.
		*/
		unsigned int getChildGridCount() const {return childGridSet.size();}

		/**
		* Return the count of child grid in this grid.
		*/
		AbstractGridRepresentation* getChildGrid(const unsigned int & index) const {return childGridSet[index];}

		/**
		* Indicates that this grid takes place into another unstructured parent grid.
		*/
		void setParentWindow(ULONG64 * cellIndices, const ULONG64 & cellIndexCount, class UnstructuredGridRepresentation* parentGrid);

		/**
		* Indicates that this grid takes place into another Column Layer parent grid.
		* @param	columnIndices				Identifies the columns (of the parent grid) which are regrided.
		* @param	columnIndexCount			Identifies the coutn of columns (of the parent grid) which are regrided.
		* @param	kLayerIndexRegridStart		Identifies the first kLayer of all above columns (of the parent grid) which is regrided.
		* @param	childCellCountPerInterval	The count of cells per interval in this (child) grid.
		* @param	parentCellCountPerInterval	The count of cells per interval in the parent grid.
		* @param	intervalCount				The count of intervals. An interval is a portion of cells to regrid which is independant to other portion of cell. Intervals are the same for all the columns.
		* @param	parentGrid					The parent grid which is regridded.
		* @param	childCellWeights			The weights that are proportional to the relative sizes of child cells within each interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells per column (sum of child cells per interval).
		*/
		void setParentWindow(unsigned int * columnIndices, const unsigned int & columnIndexCount,
			const unsigned int & kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount,
			class AbstractColumnLayerGridRepresentation* parentGrid, double * childCellWeights = NULL);

		/**
		* Indicates that this grid takes place into another IJK parent grid.
		* @param	iCellIndexRegridStart		Identifies the first Cell by its i dimension of the regrid window.
		* @param	childCellCountPerIInterval	The count of cells per i interval in this (child) grid.
		* @param	parentCellCountPerIInterval	The count of cells per i interval in the parent grid.
		* @param	iIntervalCount				The count of intervals on i dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	jCellIndexRegridStart		Identifies the first Cell by its j dimension of the regrid window.
		* @param	childCellCountPerJInterval	The count of cells per j interval in this (child) grid.
		* @param	parentCellCountPerJInterval	The count of cells per j interval in the parent grid.
		* @param	jIntervalCount				The count of intervals on j dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	kCellIndexRegridStart		Identifies the first Cell by its k dimension of the regrid window.
		* @param	childCellCountPerKInterval	The count of cells per k interval in this (child) grid.
		* @param	parentCellCountPerKInterval	The count of cells per k interval in the parent grid.
		* @param	kIntervalCount				The count of intervals on k dimension. An interval is a portion of cells to regrid which is independant to other portion of cell.
		* @param	parentGrid					The parent grid which is regridded.
		* @param	iChildCellWeights			The weights that are proportional to the relative i sizes of child cells within each i interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on i dimension (sum of child cells per interval).
		* @param	jChildCellWeights			The weights that are proportional to the relative j sizes of child cells within each j interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on j dimension (sum of child cells per interval).
		* @param	kChildCellWeights			The weights that are proportional to the relative k sizes of child cells within each k interval. The weights need not to be normalized. The count of double values must be equal to the count of all child cells on k dimension (sum of child cells per interval).
		*/
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  const unsigned int & iIntervalCount,
			const unsigned int & jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  const unsigned int & jIntervalCount,
			const unsigned int & kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  const unsigned int & kIntervalCount,
			class AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = NULL, double * jChildCellWeights = NULL, double * kChildCellWeights = NULL);

		/**
		* Indicates that this grid takes place into another IJK parent grid.
		* this method assume there is only one regrid interval per dimension.
		* @param	iCellIndexRegridStart		Identifies the first Cell by its i dimension of the regrid window.
		* @param	iChildCellCount				The count of cells per i interval in this (child) grid.
		* @param	iParentCellCount			The count of cells per i interval in the parent grid.
		* @param	jCellIndexRegridStart		Identifies the first Cell by its j dimension of the regrid window.
		* @param	jChildCellCount				The count of cells per j interval in this (child) grid.
		* @param	jParentCellCount			The count of cells per j interval in the parent grid.
		* @param	kCellIndexRegridStart		Identifies the first Cell by its k dimension of the regrid window.
		* @param	kChildCellCount				The count of cells per k interval in this (child) grid.
		* @param	kParentCellCount			The count of cells per k interval in the parent grid.
		* @param	parentGrid					The parent grid which is regridded.
		* @param	iChildCellWeights			The weights that are proportional to the relative i sizes of child cells. The weights need not to be normalized. The count of double values must be equal to iChildCellCount.
		* @param	jChildCellWeights			The weights that are proportional to the relative j sizes of child cells. The weights need not to be normalized. The count of double values must be equal to jChildCellCount.
		* @param	kChildCellWeights			The weights that are proportional to the relative k sizes of child cells. The weights need not to be normalized. The count of double values must be equal to kChildCellCount.
		*/
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			const unsigned int & jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			const unsigned int & kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			class AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = NULL, double * jChildCellWeights = NULL, double * kChildCellWeights = NULL);

		/**
		* When a parent windows has been defined, this method allows to force some parent cells to be noted as non regridded.
		* It mainly allows non-rectangular local grids to be specified.
		*/
		void setForcedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount);

		/**
		* Optional cell volume overlap information between the current grid (the child) and the parent grid. Use this data-object when the child grid has an explicitly defined geometry, and these relationships cannot be inferred from the regrid descriptions.
		*/
		void setCellOverlap(const ULONG64 & parentChildCellPairCount, ULONG64 * parentChildCellPair,
			const gsoap_resqml2_0_1::eml__VolumeUom & volumeUom = gsoap_resqml2_0_1::eml__VolumeUom__m3, double * overlapVolumes = NULL);

		/**
		* Only run this method for an unstructured parent grid.
		* Use regrid information for ijk parent grid or (regrid and columIndexCount) for strict column layer parent grid.
		*/
		LONG64 getParentCellIndexCount() const;

		/**
		* Only run this method for an unstructured parent grid.
		* @param parentCellIndices	This array must have been preallocated with a size of getParentCellIndexCount().
		*/
		void getParentCellIndices(ULONG64 * parentCellIndices) const;

		/**
		* Only run this method for a strict column layer parent grid.
		*/
		LONG64 getParentColumnIndexCount() const;

		/**
		* Only run this method for an unstructured parent grid.
		* @param parentCellIndices	This array must have been preallocated with a size of getParentCellIndexCount().
		*/
		void getParentColumnIndices(ULONG64 * parentColumnIndices) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* Get the first cell index of the regrid on a particular dimension.
		* @param	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		*/
		ULONG64 getRegridStartIndexOnParentGrid(const char & dimension) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* Get the count of intervals which are regridded on a particular dimension
		* @param	dimension	It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		*/
		ULONG64 getRegridIntervalCount(const char & dimension) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childCellCountPerInterval	This array must have been preallocated with a size of getRegridIntervalCount().
		*/
		void getRegridChildCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	parentCellCountPerInterval	This array must have been preallocated with a size of getRegridIntervalCount().
		*/
		void getRegridParentCellCountPerInterval(const char & dimension, ULONG64 * parentCellCountPerInterval) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension					It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		*/
		bool hasRegridChildCellWeights(const char & dimension) const;

		/**
		* Only run this method for an ijk parent grid or a strict column layer parent grid.
		* @param	dimension			It must be either 'i', 'j' ou 'k' (upper or lower case) for an ijk parent grid. 'k' for a strict column layer parent grid.
		* @param	childCellWeights	This array must have been preallocated with a size equal to the sum of ChildCellCountPerInterval.
		*/
		void getRegridChildCellWeights(const char & dimension, ULONG64 * childCellWeights) const;


	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		std::vector<AbstractGridRepresentation*> childGridSet;

		std::vector<GridConnectionSetRepresentation*> gridConnectionSetRepresentationSet;

		friend void GridConnectionSetRepresentation::setSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);

	};
}
