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

#include "resqml2_0_1/AbstractColumnLayerGridRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractIjkGridRepresentation : public AbstractColumnLayerGridRepresentation
	{
	private :
		void init(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

	protected :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const;

	public:

		enum geometryKind { EXPLICIT = 0, PARAMETRIC = 1, LATTICE = 2 };

		AbstractIjkGridRepresentation(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		AbstractIjkGridRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractIjkGridRepresentation(gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* fromGsoap): AbstractColumnLayerGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractIjkGridRepresentation() {}

		/**
		* Get the I cell count of the grid
		*/
		unsigned int getICellCount() const;

		/**
		* Set the I cell count of the grid
		*/
		void setICellCount(const unsigned int & iCount);

		/**
		* Get the J cell count of the grid
		*/
		unsigned int getJCellCount() const;

		/**
		* Set the J cell count of the grid
		*/
		void setJCellCount(const unsigned int & jCount);

		/**
		* Get the count of cells in the grid
		*/
		unsigned int getCellCount() const {return getICellCount() * getJCellCount() * getKCellCount();}

		/**
		* Get the count of columns in the grid
		*/
		unsigned int getColumnCount() const {return getICellCount() * getJCellCount();}

		/**
		* Get the count of pillars in the grid
		*/
		unsigned int getPillarCount() const {return (getICellCount()+1) * (getJCellCount()+1);}

		bool isRightHanded() const;

		/**
		 * Get all the pillars which correspond to all split coordinate lines.
		 * Order of the pillar correspond to order of the split coordinate lines.
		 * @param pillarIndices It must be pre allocated.
		 */
		void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Get all the columns impacted by all the split coordinate lines.
		 * @param columnIndices 			It must be pre allocated.
		 */
		void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;

		/**
		 * Get the split coordinate line count
		 */
		unsigned long getSplitCoordinateLineCount() const;
		
		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;

		void getCellGeometryIsDefined(bool * cellGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		virtual geometryKind getGeometryKind() const = 0;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		unsigned int getPatchCount() const {return 1;}
	};
}
