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

#include <string>
#include <vector>
#include <limits>

#include "stdsoap2.h"
#include "gsoap_resqml2_0_1H.h"
#include "gsoap_witsml1_4_1_1H.h"

#include "Package.h"

#if defined(_WIN32) && defined(DLL)
	#ifdef DLL_EXPORTS
		#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
	#else
		#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
	#endif
#else
	#define DLL_IMPORT_OR_EXPORT
#endif

namespace resqml2_0_1
{
	class Activity;
	class ActivityTemplate;
	class PropertyKindMapper;
	class LocalDepth3dCrs;
	class LocalTime3dCrs;
	class MdDatum;
	class AbstractObject;
	class Fault;
	class Fracture;
	class Horizon;
	class WellboreFeature;
	class SeismicLineFeature;
	class StratigraphicUnitFeature;
	class PolylineSetRepresentation;
	class PolylineRepresentation;
	class TriangulatedSetRepresentation;
	class Grid2dSetRepresentation;
	class Grid2dRepresentation;
	class WellboreTrajectoryRepresentation;
	class IjkGridRepresentation;
	class UnstructuredGridRepresentation;
	class HdfProxy;
	class BoundaryFeature;
	class BoundaryFeatureInterpretation;
	class TectonicBoundaryFeature;
	class AbstractLocal3dCrs;
	class SeismicLatticeFeature;
	class SeismicLineSetFeature;
	class OrganizationFeature;
	class GenericFeatureInterpretation;
	class HorizonInterpretation;
	class FaultInterpretation;
	class WellboreInterpretation;
	class EarthModelInterpretation;
	class StructuralOrganizationInterpretation;
	class StratigraphicUnitInterpretation;
	class StratigraphicColumn;
	class StratigraphicColumnRankInterpretation;
	class PointSetRepresentation;
	class WellboreFrameRepresentation;
	class WellboreMarkerFrameRepresentation;
	class RepresentationSetRepresentation;
	class NonSealedSurfaceFrameworkRepresentation;
	class SealedSurfaceFrameworkRepresentation;
	class SubRepresentation;
	class GridConnectionSetRepresentation;
	class TimeSeries;
	class StringTableLookup;
	class PropertyKind;
	class CommentProperty;
	class ContinuousProperty;
	class ContinuousPropertySeries;
	class DiscreteProperty;
	class DiscretePropertySeries;
	class CategoricalProperty;
	class CategoricalPropertySeries;
	class AbstractRepresentation;
	class AbstractFeatureInterpretation;
	class AbstractFeature;
	class AbstractOrganizationInterpretation;
	class AbstractGridRepresentation;
	class OrganizationFeature;
	class StratigraphicOccurrenceInterpretation;
	class FrontierFeature;
	class PlaneSetRepresentation;
	class FluidBoundaryFeature;
}

namespace witsml1_4_1_1
{
	class AbstractObject;
	class Well;
	class CoordinateReferenceSystem;
	class Trajectory;
}

namespace common
{
	/**
	* This class allows an access to a memory package representing an EPC document.
	*/
	class DLL_IMPORT_OR_EXPORT EpcDocument
	{
	public:
		EpcDocument(const std::string & fileName);
		EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory);

		~EpcDocument();

		/**
		 * Open an epc document
		 * @return	false if the epc document cannot be opened for example if it is already opened.
		 */
		bool open(const std::string & fileName);
	
		/**
		 * Free all ressources contained in this package.
		 */
		void close();

		/**
		* Serialize the package by serializing all the gsoap wrappers and by zipping the package.
		*/
		void serialize(bool useZip64 = false);

		/**
		* Unzip the package and get all contained elements with their relationships
		* @return			An empty string if everything's ok otherwise the error string.
		*/
		std::string deserialize();

		/**
		* Get the soap context of the epc document.
		*/
		soap* getGsoapContext() {return s;}

		/**
		* Add a gsoap proxy to serialize with the package
		*/
		void addGsoapProxy(resqml2_0_1::AbstractObject* proxy);

		/**
		* Add a gsoap proxy to serialize with the package
		*/
		void addGsoapProxy(witsml1_4_1_1::AbstractObject* proxy);

		/**
		 * Get the property kind mapper of this epc document if given at EPC document construction time.
		 * Else return NULL.
		 */
		resqml2_0_1::PropertyKindMapper* getPropertyKindMapper() const {return propertyKindMapper;}

		/**
		* Get the name of the resqml standard property type as a string based on the enumerated property type.
		* @return The empty string if no correspondence is found
		*/
		std::string getResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlLengthUom(const gsoap_witsml1_4_1_1::witsml1__LengthUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlWellVerticalCoordinateUom(const gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlMeasuredDepthUom(const gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlPlaneAngleUom(const gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom & witsmlUom) const;

		/**
		* Get the Energistics unit of measure enumerated value from the name (string) of the uom.
		* @return The Euclidian (no uom) energistics uom if no correspondance is found with the uom string/name.
		*/
		gsoap_resqml2_0_1::resqml2__ResqmlUom getResqmlUnitOfMeasure(const std::string & uomName) const;

		/**
		* Add a resqml2 object in the package which is described as an xml string.
		*/
		resqml2_0_1::AbstractObject* addResqmlObject(const std::string & xml);

		/**
		* Get all the resqml gsoap wrappers from the epc document
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		const std::unordered_map< std::string, resqml2_0_1::AbstractObject* > & getResqmlAbstractObjectSet() const {return resqmlAbstractObjectSet;}
#else
		const std::tr1::unordered_map< std::string, resqml2_0_1::AbstractObject* > & getResqmlAbstractObjectSet() const {return resqmlAbstractObjectSet;}
#endif

		/**
		* Get a gsoap wrapper from the epc document by means of its uuid
		*/
		resqml2_0_1::AbstractObject* getResqmlAbstractObjectByUuid(const std::string & uuid) const;

		witsml1_4_1_1::AbstractObject* getWitsmlAbstractObjectByUuid(const std::string & uuid) const;

		/**
		* Get all the local 3d depth crs contained into the EPC document
		*/
		const std::vector<resqml2_0_1::LocalDepth3dCrs*> & getLocalDepth3dCrsSet() const {return localDepth3dCrsSet;}

		/**
		* Get all the local 3d time crs contained into the EPC document
		*/
		const std::vector<resqml2_0_1::LocalTime3dCrs*> & getLocalTime3dCrsSet() const {return localTime3dCrsSet;}

		/**
		* Get all the stratigraphic columns contained into the EPC document
		*/
		const std::vector<resqml2_0_1::StratigraphicColumn*> & getStratigraphicColumnSet() const {return stratigraphicColumnSet;}

		/**
		* Get all the faults contained into the EPC document
		*/
		const std::vector<resqml2_0_1::Fault*> & getFaultSet() const {return faultSet;}

		/**
		* Get all the fractures contained into the EPC document
		*/
		const std::vector<resqml2_0_1::Fracture*> & getFractureSet() const {return fractureSet;}

		/**
		* Get all the individual representations of faults which are associated to a polyline topology
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFaultPolylineSetRepSet() const;

		/**
		* Get all the individual representations of fractures which are associated to a polyline topology
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFracturePolylineSetRepSet() const;

		/**
		* Get all the individual representations of frontiers which are associated to a polyline set topology
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFrontierPolylineSetRepSet() const;

		/**
		* Get all the individual representations of faults which are associated to a triangulation set topology
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFaultTriangulatedSetRepSet() const;

        /**
		* Get all the individual representations of fractures which are associated to a triangulation set topology
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFractureTriangulatedSetRepSet() const;

		/**
		* Get all the horizons contained into the EPC document
		*/
		const std::vector<resqml2_0_1::Horizon*> & getHorizonSet() const {return horizonSet;}

		/**
		* Get all the individual representations of horizons which are associated to grid 2d set topology
		*/
		std::vector<resqml2_0_1::Grid2dSetRepresentation*> getHorizonGrid2dSetRepSet() const;
        
		/**
		* Get all the individual representations of horizons which are associated to grid 2d set topology
		*/
		std::vector<resqml2_0_1::Grid2dRepresentation*> getHorizonGrid2dRepSet() const;
        
		/**
		* Get all the single polyline representations of all the horizons
		*/
		std::vector<resqml2_0_1::PolylineRepresentation*> getHorizonPolylineRepSet() const;
        
		/**
		* Get all the single polyline representations of all the horizons
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getHorizonPolylineSetRepSet() const;
        
        /**
		* Get all the triangulated set representations of all the horizons
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getHorizonTriangulatedSetRepSet() const;

		/**
		* Get all the triangulated set representations of the EPC document
		*/
		const std::vector<resqml2_0_1::TriangulatedSetRepresentation*> & getAllTriangulatedSetRepSet() const {return triangulatedSetRepresentationSet;}

		/**
		* Get all the triangulated set representations of the EPC document which are not horizon and fault neither.
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;

		/**
		* Get all the seismic line contained into the EPC document
		*/
		std::vector<resqml2_0_1::SeismicLineFeature*> getSeismicLineSet() const {return seismicLineSet;}

		/**
		* Get all the wellbores contained into the EPC document
		*/
		std::vector<resqml2_0_1::WellboreFeature*> getWellboreSet() const {return wellboreSet;}

		/**
		* Get all the individual representations of wellbores which uses a cubic parametric line geometry.
		*/
		std::vector<resqml2_0_1::WellboreTrajectoryRepresentation*> getWellboreCubicParamLineTrajRepSet() const;

		/**
		* Get all the polyline representation contained into the EPC document.
		*/
		std::vector<resqml2_0_1::PolylineRepresentation*> getPolylineRepresentationSet() const {return polylineRepresentationSet;}

		/**
		* Get all the single polyline representations contained into the EPC document which correspond to a seismic line.
		*/
		std::vector<resqml2_0_1::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;

		/**
		* Get all the ijk grid contained into the EPC document.
		*/
		std::vector<resqml2_0_1::IjkGridRepresentation*> getIjkGridRepresentationSet() const {return ijkGridRepresentationSet;}

		/**
		* Get all the ijk grid contained into the EPC document which have a parametric geometry.
		*/
		std::vector<resqml2_0_1::IjkGridRepresentation*> getIjkParametricGridRepresentationSet() const;

		/**
		* Get all the ijk grid contained into the EPC document which correspond to a seismic cube.
		*/
		std::vector<resqml2_0_1::IjkGridRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;

		/**
		* Get all the unstructured grid contained into the EPC document
		*/
		std::vector<resqml2_0_1::UnstructuredGridRepresentation*> getUnstructuredGridRepresentationSet() const {return unstructuredGridRepresentationSet;}

		/**
		* Get all the frontier features contained into the EPC document
		*/
		const std::vector<resqml2_0_1::FrontierFeature*> & getFrontierSet() const {return frontierSet;}

		/**
		* Get all the Hdf proxies used with this EPC document
		*/
		std::vector<resqml2_0_1::HdfProxy*> getHdfProxySet() const {return hdfProxySet;}

		/**
		* Get the absolute path of the directory where the epc document is stored.
		*/
		std::string getStorageDirectory() const;

		/**
		* Get the name of the epc document.
		*/
		std::string getName() const;

		/**
		* Try to resolve in memory all the relationshsips which are serialized into Resqml objects of the EPC document
		*/
		void updateAllRelationships();

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > & getExtendedCoreProperty() {return package->getExtendedCoreProperty();}
#else
		std::tr1::unordered_map< std::string, std::string > & getExtendedCoreProperty() {return package->getExtendedCoreProperty();}
#endif

		void setExtendedCoreProperty(const std::string & key, const std::string & value);

		/**
		* Get an extended core property value according its key.
		* @return An empty string if the extended core property does not exist. Or the extended core property value if it exists
		*/
		std::string getExtendedCoreProperty(const std::string & key);

		/**
		 * ALLOWS CREATION FROM THE EPC DOCUMENT
		 * MAINLY USED IN JAVA AND .NET SWIG WRAPPERS CONTEXT
		 */

		//************************************
		//************ HDF *******************
		//************************************

		resqml2_0_1::HdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		//************************************
		//************ CRS *******************
		//************************************

		/**
		* Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		* @param guid				The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param originOrdinal1		The offset of the global 2d crs on its first axis.
		* @param originOrdinal2		The offset of the global 2d crs on its second axis.
		* @param originOrdinal3		The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation		The areal rotation in radians regarding the projected crs.
		* @param projectedUom		The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode	The epsg code of the associated projected CRS.
		* @param verticalUom		The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode	The epsg code of the associated vertical CRS.
		* @param isUpOriented		If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
		
		/**
		* Creates a local depth 3d CRS which is fully unknown.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is identified by an EPSG code for its projected part and which is unkown for its vertial part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode		The epsg code of the associated projected CRS.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which unkown for its projected part and which is identified by an EPSG code for its vertical part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode		The epsg code of the associated vertical CRS.
		* @param isUpOriented			If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
	
		/**
		* Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		* @param guid				The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param originOrdinal1		The offset of the global 2d crs on its first axis.
		* @param originOrdinal2		The offset of the global 2d crs on its second axis.
		* @param originOrdinal3		The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation		The areal rotation in radians regarding the projected crs.
		* @param projectedUom		The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode	The epsg code of the associated projected CRS.
		* @param timeUom			The unit of measure of the Z offset of this instance.
		* @param verticalUom		The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode	The epsg code of the associated vertical CRS.
		* @param isUpOriented		If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is fully unknown.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is identified by an EPSG code for its projected part and which is unkown for its vertial part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param projectedEpsgCode		The epsg code of the associated projected CRS.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which unkown for its projected part and which is identified by an EPSG code for its vertical part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode		The epsg code of the associated vertical CRS.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		resqml2_0_1::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			resqml2_0_1::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************************************
		//************ FEATURE ***************
		//************************************

		resqml2_0_1::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::Horizon* createHorizon(const std::string & guid, const std::string & title);

		resqml2_0_1::TectonicBoundaryFeature* createTectonicBoundaryFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::Fault* createFault(const std::string & guid, const std::string & title);

		resqml2_0_1::Fracture* createFracture(const std::string & guid, const std::string & title);

		resqml2_0_1::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount);

		resqml2_0_1::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount);

		resqml2_0_1::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		resqml2_0_1::FrontierFeature* createFrontier(const std::string & guid, const std::string & title);

		resqml2_0_1::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);

		resqml2_0_1::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);

		resqml2_0_1::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

        resqml2_0_1::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);
		
		resqml2_0_1::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact);

		//************************************
		//************ INTERPRETATION ********
		//************************************

		resqml2_0_1::GenericFeatureInterpretation* createGenericFeatureInterpretation(resqml2_0_1::AbstractFeature * feature, const std::string & guid, const std::string & title);
		
		resqml2_0_1::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(resqml2_0_1::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		resqml2_0_1::HorizonInterpretation* createHorizonInterpretation(resqml2_0_1::Horizon * horizon, const std::string & guid, const std::string & title);

		resqml2_0_1::FaultInterpretation* createFaultInterpretation(resqml2_0_1::Fault * fault, const std::string & guid, const std::string & title);

		resqml2_0_1::WellboreInterpretation* createWellboreInterpretation(resqml2_0_1::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);
                
		resqml2_0_1::EarthModelInterpretation* createEarthModelInterpretation(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		
		resqml2_0_1::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(resqml2_0_1::StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		resqml2_0_1::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		resqml2_0_1::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		//************************************
		//************ REPRESENTATION ********
		//************************************

		resqml2_0_1::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);

		resqml2_0_1::PointSetRepresentation* createPointSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PlaneSetRepresentation* createPlaneSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind, bool isClosed = false);

		resqml2_0_1::Grid2dRepresentation* createGrid2dRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::MdDatum * mdInfo);

		resqml2_0_1::WellboreFrameRepresentation* createWellboreFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

		resqml2_0_1::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj); // deprecated
		resqml2_0_1::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(resqml2_0_1::StratigraphicColumnRankInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj); // deprecated
		resqml2_0_1::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(resqml2_0_1::StratigraphicOccurrenceInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

		resqml2_0_1::RepresentationSetRepresentation* createRepresentationSetRepresentation(
                resqml2_0_1::AbstractOrganizationInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
                const std::string & guid,
                const std::string & title);
                
        resqml2_0_1::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
                resqml2_0_1::StructuralOrganizationInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, 
                const std::string & guid, 
                const std::string & title,
                const bool & isSealed);

        resqml2_0_1::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
                resqml2_0_1::StructuralOrganizationInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
                const std::string & guid,
                const std::string & title);

		resqml2_0_1::IjkGridRepresentation* createIjkGridRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridRepresentation* createIjkGridRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & cellCount);

		resqml2_0_1::SubRepresentation* createSubRepresentation(resqml2_0_1::AbstractLocal3dCrs * crs, 
                const std::string & guid, const std::string & title,
				resqml2_0_1::AbstractRepresentation * supportingRep);

		resqml2_0_1::SubRepresentation* createSubRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, 
                const std::string & guid, const std::string & title,
				resqml2_0_1::AbstractRepresentation * supportingRep);

		resqml2_0_1::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(resqml2_0_1::AbstractFeatureInterpretation* interp, resqml2_0_1::AbstractLocal3dCrs * crs, 
                const std::string & guid, const std::string & title,
				resqml2_0_1::AbstractGridRepresentation * supportingGridRep);

		//************************************
		//************* PROPERTIES ***********
		//************************************

		resqml2_0_1::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		resqml2_0_1::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);

		resqml2_0_1::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		resqml2_0_1::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2_0_1::PropertyKind * parentPropType);

		resqml2_0_1::CommentProperty* createCommentProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::CommentProperty* createCommentProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2_0_1::PropertyKind * localPropType);
	
		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2_0_1::PropertyKind * localPropType);

		resqml2_0_1::ContinuousPropertySeries* createContinuousPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			const unsigned int & timeIndexCount, resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::ContinuousPropertySeries* createContinuousPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2_0_1::PropertyKind * localPropType,
			const unsigned int & timeIndexCount, resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);
	
		resqml2_0_1::DiscreteProperty* createDiscreteProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::DiscreteProperty* createDiscreteProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2_0_1::PropertyKind * localPropType);
	
		resqml2_0_1::DiscretePropertySeries* createDiscretePropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			const unsigned int & timeIndexCount, resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::DiscretePropertySeries* createDiscretePropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2_0_1::PropertyKind * localPropType,
			const unsigned int & timeIndexCount, resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::CategoricalProperty* createCategoricalProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);
	
		resqml2_0_1::CategoricalProperty* createCategoricalProperty(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, resqml2_0_1::PropertyKind * localPropType);

		resqml2_0_1::CategoricalPropertySeries* createCategoricalPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			const unsigned int & timeIndexCount, resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::CategoricalPropertySeries* createCategoricalPropertySeries(resqml2_0_1::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, resqml2_0_1::PropertyKind * localPropType,
			const unsigned int & timeIndexCount, resqml2_0_1::TimeSeries * ts, const bool & useInterval = false);

		//************************************
		//************* ACTIVITIES ***********
		//************************************

		resqml2_0_1::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);
		
		resqml2_0_1::Activity* createActivity(resqml2_0_1::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);
		
		//************************************
		//*************** WITSML *************
		//************************************
		
		/**
		* Get all the witsml trajectories contained into the EPC document
		*/
		std::vector<witsml1_4_1_1::Trajectory*> getWitsmlTrajectorySet() const {return witsmlTrajectorySet;}

		witsml1_4_1_1::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone);

		witsml1_4_1_1::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone,
			const std::string & operator_,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWell,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWell,
			gsoap_witsml1_4_1_1::witsml1__WellFluid fluidWell,
			gsoap_witsml1_4_1_1::witsml1__WellDirection directionWell,
			const time_t & dTimSpud,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		witsml1_4_1_1::CoordinateReferenceSystem* createCoordinateReferenceSystem(
			const std::string & guid,
			const std::string & title,
			const std::string & namingSystem,
			const std::string & code,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

	private :
		static const char * DOCUMENT_EXTENSION;

		epc::Package* package;
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, resqml2_0_1::AbstractObject* > resqmlAbstractObjectSet;
#else
		std::tr1::unordered_map< std::string, resqml2_0_1::AbstractObject* > resqmlAbstractObjectSet;
#endif
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* > witsmlAbstractObjectSet;
#else
		std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* > witsmlAbstractObjectSet;
#endif
		soap* s;
		std::string filePath;

		// Better for performance reason to have set of important objects instead of having a global vector of GsoapWrapper
		// Even if redundant with resqmlAbstractObjectSet
		std::vector<resqml2_0_1::LocalDepth3dCrs*>				localDepth3dCrsSet;
		std::vector<resqml2_0_1::LocalTime3dCrs*>					localTime3dCrsSet;
		std::vector<resqml2_0_1::Fault*>							faultSet;
		std::vector<resqml2_0_1::Fracture*>						fractureSet;
		std::vector<resqml2_0_1::Horizon*>						horizonSet;
		std::vector<resqml2_0_1::SeismicLineFeature*>				seismicLineSet;
		std::vector<resqml2_0_1::HdfProxy*>						hdfProxySet;
		std::vector<resqml2_0_1::WellboreFeature*>				wellboreSet;
		std::vector<witsml1_4_1_1::Trajectory*>					witsmlTrajectorySet;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*>	triangulatedSetRepresentationSet;
		std::vector<resqml2_0_1::PolylineRepresentation*>			polylineRepresentationSet;
		std::vector<resqml2_0_1::IjkGridRepresentation*>			ijkGridRepresentationSet;
		std::vector<resqml2_0_1::UnstructuredGridRepresentation*>	unstructuredGridRepresentationSet;
		std::vector<resqml2_0_1::StratigraphicColumn*>			stratigraphicColumnSet;
		std::vector<resqml2_0_1::FrontierFeature*>				frontierSet;

		resqml2_0_1::PropertyKindMapper* propertyKindMapper;
	};
}


