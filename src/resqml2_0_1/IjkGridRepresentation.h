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

#include "resqml2_0_1/AbstractColumnLayerGridRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT IjkGridRepresentation : public AbstractColumnLayerGridRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const;
		gsoap_resqml2_0_1::resqml2__Point3dLatticeArray* getArrayLatticeOfPoints3d() const;

		void init(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

	public:

		IjkGridRepresentation(common::EpcDocument * epcDoc, class AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		IjkGridRepresentation(class AbstractFeatureInterpretation* interp, class AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridRepresentation(gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* fromGsoap): AbstractColumnLayerGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~IjkGridRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Indicates wether the instance has got a parametric geometry or not.
		*/
		bool hasParametricGeometry() const;

		/**
		* Indicates wether the instance corresponds to a seismic cube or not.
		*/
		bool isASeismicCube() const;

		/**
		* Indicates wether the instance corresponds to a facies cube or not.
		*/
		bool isAFaciesCube() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		unsigned int getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

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

		/**
		* Get the I cell count of the grid
		*/
		unsigned int getICount() const;

		/**
		* Set the I cell count of the grid
		*/
		void setICount(const unsigned int & iCount);

		/**
		* Get the J cell count of the grid
		*/
		unsigned int getJCount() const;

		/**
		* Set the J cell count of the grid
		*/
		void setJCount(const unsigned int & jCount);

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		double getXOrigin() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		double getYOrigin() const;

	    /**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		double getZOrigin() const;

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		double getXOriginInGlobalCrs() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		double getYOriginInGlobalCrs() const;

		/**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		double getZOriginInGlobalCrs() const;

		/*****************************************************
		* Notice that, in seismic context, I is the slowest axis, J is the intermediate axis and K is the fastest axis.
		* In reservoir grid, I is the fastest axis, J is the intermediate axis and K is slowest axis.
		* It should be improved in future Resqml versions.
		*****************************************************/

		/**
        * Get the X i offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
        double getXIOffset() const;

        /**
        * Get the Y i offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
        double getYIOffset() const;

		/**
        * Get the Z i offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
        double getZIOffset() const;

		/**
        * Get the X j offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
        double getXJOffset() const;

        /**
        * Get the Y j offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
        double getYJOffset() const;

		/**
        * Get the Z j offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
        double getZJOffset() const;

		/**
        * Get the X k offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
        double getXKOffset() const;

        /**
        * Get the Y k offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
        double getYKOffset() const;

		/**
        * Get the Z k offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
        double getZKOffset() const;

		/**
        * Get the I spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The I spacing otherwise.
        */
		double getISpacing() const;

        /**
        * Get the J spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The J spacing otherwise.
        */
        double getJSpacing() const;

		/**
        * Get the K spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The K spacing otherwise.
        */
        double getKSpacing() const;

		/**
        * Get the label of the first inline.
        */
        int getOriginInline() const;

		/**
        * Get the label of the first crossline.
        */
        int getOriginCrossline() const;

		/**
        * Get the inline I offset value.
        */
        int getInlineIOffset() const;

		/**
        * Get the inline J offset value.
        */
        int getInlineJOffset() const;

		/**
        * Get the inline K offset value.
        */
        int getInlineKOffset() const;

		/**
        * Get the crossline I offset value.
        */
        int getCrosslineIOffset() const;

		/**
        * Get the crossline J offset value.
        */
        int getCrosslineJOffset() const;

		/**
        * Get the crossline K offset value.
        */
        int getCrosslineKOffset() const;

		/**
		* Get the count of cells in the grid
		*/
		unsigned int getCellCount() const {return getICount() * getJCount() * getKCount();}

		/**
		* Get the count of columns in the grid
		*/
		unsigned int getColumnCount() const {return getICount() * getJCount();}

		/**
		* Get the count of pillars in the grid
		*/
		unsigned int getPillarCount() const {return (getICount()+1) * (getJCount()+1);}

		/**
		* Get the max control point coutn on a pillar of the grid.
		* Only relevant in case the IJK grid is a parametric one.
		*/
		unsigned int getControlPointMaxCountPerPillar() const;

		/**
		* Get all the control points of each pillar of the IJK parametric grid.
		* They are ordered first (quickest) by control point max count and then (slowest) by pillar.
		* Only relevant in case the IJK grid is a parametric one.
		*/
		void getControlPoints(double * controlPoints, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		* Check if the IJK grid contains some paraemeters on some control points.
		* It happens when the grid contains at least one non vertical or a non Z linear parametric line.
		*/
		bool hasControlPointParameters() const;

		/**
		* Get all the control point parameters of each pillar of the IJK parametric grid.
		* They are ordered first (quickest) by control point max count and then (slowest) by pillar.
		* Only relevant in case the IJK grid is a parametric one and in case it contains at least one non vertical or non Z linear parametric line.
		*/
		void getControlPointParameters(double * controlPointParameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		* Get the kind of each parametric line representing a pillar :
		*					0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line 
		* Only relevant in case the IJK grid is a parametric one.
		*/
		void getParametricLineKind(short * pillarKind, bool reverseIAxis = false, bool reverseJAxis= false) const;

		/**
		* Get all the parameters of each node of the IJK parametric grid.
		* They are ordered first (quickest) by coordinate line and then (slowest) by K level.
		* Only relevant in case the IJK grid is a parametric one.
		*/
		void getParametersOfNodes(double * parameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		void getCellGeometryIsDefined(bool * cellGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		* Set the geometry of the IJK grid as explicit coordinate line nodes
		*/
		void setGeometryAsCoordinateLineNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * points, class HdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = NULL,
			unsigned int * splitCoordinateLineColumnCumulativeCount = NULL, unsigned int * splitCoordinateLineColumns = NULL);

		/**
		* Set the geometry of the IJK grid as parametric pillar nodes where no pillar is splitted
		* @param lineKind	the kind of each pillar :
		*					0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line 
		*/
		void setGeometryAsParametricNonSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class HdfProxy * proxy,
			unsigned char* cellGeomIsDefined = NULL);

		/**
		* Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is supposed to be splitted
		* @param lineKind	the kind of each pillar :
		*					0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line 
		*/
		void setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class HdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns,
			unsigned char* cellGeomIsDefined = NULL);

		/**
		* Set the geometry of the IJK grid as a regular IJK grid
		*/
		void setGeometryAsCoordinateLineNodes(	const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry,
												const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind,
												const bool & isRightHanded,
												const double & originX, const double & originY, const double & originZ,
												const double & directionIX, const double & directionIY, const double & directionIZ, const double & spacingI,
												const double & directionJX, const double & directionJY, const double & directionJZ, const double & spacingJ,
												const double & directionKX, const double & directionKY, const double & directionKZ, const double & spacingK);

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		void addSeismic3dCoordinatesToPatch(
						const unsigned int patchIndex,
						const double & startInline, const double & incrInline, const unsigned int & countInline,
						const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			            const unsigned int & countSample, AbstractRepresentation * seismicSupport);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		unsigned int getPatchCount() const {return 1;}

		bool isRightHanded() const;

		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;
	};
}
