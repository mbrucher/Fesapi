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

#include "resqml2/AbstractRepresentation.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation : public AbstractRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::eml__DataObjectReference* partialObject) :
			AbstractRepresentation(nullptr, partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		*/
		GridConnectionSetRepresentation(class AbstractFeatureInterpretation* interp) : AbstractRepresentation(interp, nullptr) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::_resqml2__GridConnectionSetRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		virtual void pushBackXmlInterpretation(class AbstractFeatureInterpretation* interp) = 0;
		virtual void pushBackXmlSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep) = 0;

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~GridConnectionSetRepresentation() {}
        
		static const char* XML_TAG;
		virtual std::string getXmlTag() const;

		virtual std::string getHdfProxyUuid() const = 0;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		virtual ULONG64 getCellIndexPairCount() const = 0;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		virtual ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const = 0;

		/**
		* Get the cell index pairs count which correspond to a particular interpretation.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		virtual unsigned int getCellIndexPairCountFromInterpretationIndex(const unsigned int & interpretationIndex) const = 0;

		/**
		* Indicates wether the cell connection are associated to interpretation or not.
		*/
		virtual bool isAssociatedToInterpretations() const = 0;

		/**
		* Get the interpretation index cumulative count of this grid connection representation
		* The count of cumulativeCount must be getCellIndexPairCount().
		*/
		virtual void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const = 0;

		/**
		* Get the interpretation indices of this grid connection representation
		* The count of interpretationIndices is the last value of the array returning by getInterpretationIndexCumulativeCount.
		*/
		virtual void getInterpretationIndices(unsigned int * interpretationIndices) const = 0;

		/**
		* Returns the null value for interpretation index.
		*/
		virtual LONG64 getInterpretationIndexNullValue() const = 0;

		/**
		* Get the cell index pairs, the grid index pairs (optional) and the local face pairs (optional) which correspond to a particular  interpretation.
		* @param cellIndexPairs			Mandatory. Must be allocated with getCellIndexPairCountFromIndex first.
		* @param gridIndexPairs			Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromIndex first.
		* @param localFaceIndexPairs	Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromIndex first.
		* @param interpretationIndex	The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		virtual void getGridConnectionSetInformationFromInterpretationIndex(unsigned int * cellIndexPairs, unsigned int * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const = 0;

		/**
		* Get the UUID of a particular interpretation of this grid connection set.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		virtual std::string getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const = 0;

		/**
		* Get a particular interpretation of this grid connection set.
		* @param interpretationIndex The index of the interpretation in the collection of feature interpretation of this grid connection set.
		*/
		class AbstractFeatureInterpretation * getInterpretationFromIndex(const unsigned int & interpretationIndex) const;

		/**
		* Get the count of interpretations in this grid connection set.
		*/
		virtual unsigned int getInterpretationCount() const = 0;

		/**
		* Indicates if the grid connection set representation contains information on the connected faces of the two cells.
		*/
		virtual bool hasLocalFacePerCell() const = 0;

		/**
		* Get the local face cell index pairs of this grid connection representation
		* The count of localFacePerCellIndexPairs must be getCellIndexPairCount()*2.
		*/
		virtual void getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const = 0;

		/**
		* Indicates if the grid connection set representation is based on several grids.
		*/
		virtual bool isBasedOnMultiGrids() const = 0;

		/**
		* Get the grid index pairs of this grid connection representation
		* The count of gridIndexPairs must be getCellIndexPairCount()*2.
		*/
		virtual void getGridIndexPairs(unsigned int * gridIndexPairs) const = 0;

		/**
		* Set the cell index pairs of the grid connections representation
        * @param cellIndexPairCount	The count of cell index pair. It is half of all the stored numerical values.
        * @param cellIndexPair		All the cell index pair in a 1d Array where the cell indices go faster than the pair.
        * @param proxy				The HDF proxy where the numerical values (cell indices) are stored.
		*/
		virtual void setCellIndexPairs(const unsigned int & cellIndexPairCount, ULONG64 * cellIndexPair, const ULONG64 & nullValue, resqml2::AbstractHdfProxy * proxy) = 0;

		/**
		* Optional 2 x #Connections array of local face-per-cell indices for (Cell1,Cell2) for each connection. Local face-per-cell indices are used because global face indices need not have been defined.
		* If no face-per-cell definition occurs as part of the grid representation, e.g., for a block-centered grid, then this array need not appear.
		* Null value = -1 by dcoumentation
		*/
		virtual void setLocalFacePerCellIndexPairs(const unsigned int & cellIndexPairCount, int * localFacePerCellIndexPair, resqml2::AbstractHdfProxy * proxy) = 0;

		/**
		* For each connection in the grid connection set representation, allow to map zero or one feature interpretation. TODO: Resqml allows to map with more than one feature interpretation.
		* @param interpretationIndices		For each connection, the index of the corresponding interpretation in the interpretation set of this grid connection. The count of this array is given by the next parameter.
		* @param interpretationIndiceCount	The count of interpretation indices.
		* @param nullValue					The null value must be used as the corresponding interpretation index for each connection which are not associated to any interpretation.
		* @param proxy						The Hdf proxy where the numerical values will be stored.
		*/
		virtual void setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const ULONG64 & nullValue, resqml2::AbstractHdfProxy * proxy) = 0;

		/**
		* Pushes back an interpretation which can be mapped with some connections.
		* @param interp	The interpration to push back.
		*/
		void pushBackInterpretation(class AbstractFeatureInterpretation* interp);
	
		/**
		 * Pushes back a grid representation which is one of the support of this representation.
		 * And push back this representation as a grid connection information of the grid representation as well.
		 */
		void pushBackSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep);
		
		/**
		* Get the count of the supporting grid representations of this grid connection representation.
		*/
		virtual unsigned int getSupportingGridRepresentationCount() const = 0;

		/**
		* Get the supporting grid representation located at a specific index of this grid connection representation.
		*/
		class AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index) const;
		
		/**
		* Get the first supporting grid representation uuid of this grid connection representation.
		*/
		virtual std::string getSupportingGridRepresentationUuid(unsigned int index) const = 0;

		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Always return one since this representation does not contain patches.
		*/
		unsigned int getPatchCount() const {return 1;}

	private:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);
	};
}
