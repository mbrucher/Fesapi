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

#include "resqml2_0_1/AbstractRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT GridConnectionSetRepresentation : public AbstractRepresentation
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp	The interpretation the instance represents.
		* @param title A title for the instance to create.
        * @param indexSetPerPatch The indexes of the elements referenced by each patch of the instance.
        * @param numIndexPerPatch The number of referenced element by each patch of the instance.
		*/
		GridConnectionSetRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs, 
                const std::string & guid, const std::string & title,
				class AbstractGridRepresentation * supportingGridRep);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GridConnectionSetRepresentation(gsoap_resqml2_0_1::_resqml2__GridConnectionSetRepresentation* fromGsoap): AbstractRepresentation(fromGsoap), supportingGridRepresentation(NULL) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~GridConnectionSetRepresentation() {}
        
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::string getHdfProxyUuid() const;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		ULONG64 getCellIndexPairCount() const;

		/**
		* Get the cell index pair count of this grid connection representation
		*/
		void getCellIndexPairs(unsigned int * cellIndexPairs) const;

		/**
		* Get the cell index pairs count which correspond to a particular fault interpretation.
		* @param faultIndex The index of the fault in the collection of feature interpretation of this grid connection set.
		*/
		unsigned int getCellIndexPairCountFromFaultIndex(const unsigned int & faultIndex) const;

		/**
		* Indicates wether the cell connection are associated to faults or not.
		*/
		bool isAssociatedToFaults() const;

		/**
		* Get the fault index cumulative count of this grid connection representation
		* The count of localFacePerCellIndexPairs must be getCellIndexPairCount().
		*/
		void getFaultIndexCumulativeCount(unsigned int * cumulativeCount) const;

		/**
		* Get the fault indices of this grid connection representation
		* The count of faultIndices is the last value of the array returning by getFaultIndexCumulativeCount.
		*/
		void getFaultIndices(unsigned int * faultIndices) const;

		/**
		* Returns the null value for fault index.
		*/
		LONG64 getFaultIndexNullValue() const;

		/**
		* Get the cell index pairs, the grid index pairs (optional) and the local face pairs (optional) which correspond to a particular fault interpretation.
		* @param cellIndexPairs			Mandatory. Must be allocated with getCellIndexPairCountFromFaultIndex first.
		* @param gridIndexPairs			Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromFaultIndex first.
		* @param localFaceIndexPairs	Optional (put null if you don't want it). Must be allocated with getCellIndexPairCountFromFaultIndex first.
		* @param faultIndex				The index of the fault in the collection of feature interpretation of this grid connection set.
		*/
		void getGridConnectionSetInformationFromFaultIndex(unsigned int * cellIndexPairs, unsigned int * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & faultIndex) const;

		/**
		* Get the UUID of a particular fault interpretation of this grid connection set.
		* @param faultIndex The index of the fault in the collection of feature interpretation of this grid connection set.
		*/
		std::string getFaultInterpretationUuidFromFaultIndex(const unsigned int & faultIndex) const;

		/**
		* Get a particular fault interpretation of this grid connection set.
		* @param faultIndex The index of the fault in the collection of feature interpretation of this grid connection set.
		*/
		class FaultInterpretation* getFaultInterpretationFromFaultIndex(const unsigned int & faultIndex) const;

		/**
		* Get the count of fault interpretations in this grid connection set.
		*/
		unsigned int getFaultInterpretationCount() const;

		/**
		* Indicates if the grid connection set representation contains information on the connected faces of the two cells.
		*/
		bool hasLocalFacePerCell() const;

		/**
		* Get the local face cell index pairs of this grid connection representation
		* The count of localFacePerCellIndexPairs must be getCellIndexPairCount()*2.
		*/
		void getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;

		/**
		* Indicates if the grid connection set representation is based on several grids.
		*/
		bool isBasedOnMultiGrids() const;

		/**
		* Get the grid index pairs of this grid connection representation
		* The count of gridIndexPairs must be getCellIndexPairCount()*2.
		*/
		void getGridIndexPairs(unsigned int * gridIndexPairs) const;

		/**
		* Set the cell index pairs of the grid connections representation
        * @param cellIndexPairCount	The count of cell index pair. It is half of all the stored numerical values.
        * @param cellIndexPair		All the cell index pair in a 1d Array where the cell indices go faster than the pair.
        * @param proxy				The HDF proxy where the numerical values (cell indices) are stored.
		*/
		void setCellIndexPairs(const unsigned int & cellIndexPairCount, unsigned int * cellIndexPair, const unsigned int & nullValue, AbstractHdfProxy * proxy);

		void setLocalFacePerCellIndexPairs(const unsigned int & cellIndexPairCount, unsigned int * LocalFacePerCellIndexPair, const unsigned int & nullValue, AbstractHdfProxy * proxy);

		void setConnectionFaultNames(unsigned int * faultIndices, const unsigned int & faultIndiceCount, const unsigned int & nullValue, AbstractHdfProxy * proxy);
	
		/**
		 * Set the grid representation which is the support of this representation.
		 * And push back this representation as a grid connetion information of the grid representation as well.
		 */
		void setSupportingGridRepresentation(class AbstractGridRepresentation * supportingGridRep);
		
		/**
		* Get the count of the supporting grid representations of this grid connection representation.
		* TODO: Support more than only one suporting grid representation in this class
		*/
		unsigned int getSupportingGridRepresentationCount() const;

		/**
		* Get the first supporting grid representation of this grid connection representation.
		* TODO: Support more than only one suporting grid representation in this class
		*/
		class AbstractGridRepresentation* getSupportingGridRepresentation() {return supportingGridRepresentation;}
		
		/**
		* Get the first supporting grid representation uuid of this grid connection representation.
		* TODO: Support more than only one suporting grid representation in this class
		*/
		std::string getSupportingGridRepresentationUuid() const;

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const {return NULL;}

		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Always return one since this representation does not contain patches.
		*/
		unsigned int getPatchCount() const {return 1;}

	private:
		class AbstractGridRepresentation* supportingGridRepresentation; // TODO: Support more than only one suporting grid representation in this class
	};
}
