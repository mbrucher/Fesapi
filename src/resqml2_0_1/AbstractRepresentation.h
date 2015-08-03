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

#include "resqml2_0_1/AbstractProperty.h"
#include "H5public.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractRepresentation : public AbstractResqmlDataObject
	{
	protected:

		//AbstractRepresentation(): interpretation(NULL), hdfProxy(NULL), localCrs(NULL) {}

		// Set the domain of the interpretation according to the local CRS
		// Does not set relationship with interp and crs because the gsoap proxy is not allocated yet. This must be done at concrete class level.
		AbstractRepresentation(class AbstractFeatureInterpretation*	interp, class AbstractLocal3dCrs * crs);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractRepresentation(gsoap_resqml2_0_1::resqml2__AbstractRepresentation* fromGsoap): AbstractResqmlDataObject(fromGsoap), interpretation (NULL), hdfProxy(NULL), localCrs(NULL) {}
		
		/**
		* Creates a point geometry patch.
		* @param patchIndex				The index of the patch which will contain this geometry.
		* @param points					All the points to set ordered according the topology of the representation it is based on. It should be 3 * numPoints sized.
		* @param numPoints				The number of points for each dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the points. It must be already opened for writing and won't be closed in this method.
		*/
		gsoap_resqml2_0_1::resqml2__PointGeometry* createPointGeometryPatch(const unsigned int & patchIndex, double * points, hsize_t * numPoints, const unsigned int & numDimensionsInArray, HdfProxy * proxy);
		
		/**
		 * Get the point geometry of a specific patch of the representation.
		 * @return	NULL if there is no point geometry for this particular patch otherwise the found point geometry.
		 */
		virtual gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry(const unsigned int & patchIndex) const = 0;

		std::string getHdfProxyUuidFromPointGeometryPatch(gsoap_resqml2_0_1::resqml2__PointGeometry* patch) const;

		gsoap_resqml2_0_1::resqml2__Seismic2dCoordinates* getSeismic2dCoordinates(const unsigned int & patchIndex) const;

		gsoap_resqml2_0_1::resqml2__Seismic3dCoordinates* getSeismic3dCoordinates(const unsigned int & patchIndex) const;

		/**
		* Push back the seismic support of this representation and sets the opposite relationship
		* i.e. from the base rep to the child rep.
		* Only updates memory, no XML.
		*/
		void pushBackSeismicSupport(AbstractRepresentation * seismicSupport);

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractRepresentation() {}

		/**
		* Getter (read/write access) for the localCrs
		*/
		class AbstractLocal3dCrs * getLocalCrs() const
		{
			return localCrs;
		}
		
		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		virtual std::string getLocalCrsUuid() const;

		/**
		* Getter (read/write access) for the hdf Proxy
		*/
		class HdfProxy * getHdfProxy()
		{
			return hdfProxy;
		}

		/*
		 * Getter for the uuid of the hdf proxy which is used for storing the numerical values of this representation i.e. geometry.
		 * An empty string is returned if no hdf proxy is used for storing the representation/geometry.
		 */
		virtual std::string getHdfProxyUuid() const = 0;

		/**
		* Getter (read only) of all the properties which use this representation as support.
		*/
		const std::vector<class AbstractProperty*> & getPropertySet() const
		{return propertySet;}

		/**
		* Getter of all the properties values which use this representation as support.
		*/
		std::vector<class AbstractValuesProperty*> getValuesPropertySet() const;

		/**
		* Getter of the count of values properties which use this representation as support.
		* Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.
		*/
		unsigned int getValuesPropertyCount() const;

		/**
		* Getter of a particular values property which use this representation as support. It is identified by its index.
		* Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of values property.
		*/
		AbstractValuesProperty* getValuesProperty(const unsigned int & index) const;

		/**
		 * Set the interpretation which is associated to this representation.
		 * And push back this representation as a representation of the interpreation as well.
		 */
		void setInterpretation(class AbstractFeatureInterpretation * interp);

		/**
		* Get the interpretation of this representation
		*/
		class AbstractFeatureInterpretation* getInterpretation() const {return interpretation;}

		/**
		* Add a subrepresentation to this representation
		* Does not add the inverse relationship i.e. from the subrepresentation to this representation.
		*/
		void addSubRepresentation(class SubRepresentation* subRep) {subRepresentationSet.push_back(subRep);}

		/**
		* Get all the subrepresentations of this instance.
		*/
		std::vector<class SubRepresentation*> getSubRepresentationSet() const {return subRepresentationSet;}

		/**
		 * Get the subrepresentation count into this EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		unsigned int getSubRepresentationCount() const {return subRepresentationSet.size();}

		/**
		 * Get a particular subrepresentation according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		class SubRepresentation* getSubRepresentation(const unsigned int & index) const
		{
			if (subRepresentationSet.size() > index) return subRepresentationSet[index]; else return NULL;
		}

		/**
		* Get all the subrepresentations of this instance which represent a fault.
		*/
		std::vector<class SubRepresentation*> getFaultSubRepresentationSet() const;

		/**
		 * Get the subrepresentation count into this EPC document which are representations of a fault.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		unsigned int getFaultSubRepresentationCount() const {return getFaultSubRepresentationSet().size();}

		/**
		 * Get a particular fault subrepresentation according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		class SubRepresentation* getFaultSubRepresentation(const unsigned int & index) const
		{
			std::vector<class SubRepresentation*> tmp = getFaultSubRepresentationSet();
			if (tmp.size() > index) return tmp[index]; else return NULL;
		}

		/**
		* Get the interpretation uuid of this representation
		*/
		std::string getInterpretationUuid() const;
        
		/**
		* Get the xyz point count in a given patch.
		*/
		virtual unsigned int getXyzPointCountOfPatch(const unsigned int & patchIndex) const = 0;

        /**
		* Get the xyz point count of all patches of this representation.
		*/
		unsigned int getXyzPointCountOfAllPatches() const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		virtual void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the global CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension.  It must be pre allocated.
		*/
		void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get all the XYZ points of all patches of this individual representation
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfAllPatches(double * xyzPoints) const;

		/**
		* Get all the XYZ points of all patches of this individual representation
		* XYZ points are given in the global CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension.  It must be pre allocated.
		*/
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;

		/**
		* Get the seismic support representation set of this representation
		*/
		//const std::vector<AbstractRepresentation*> & getSeismicSupportSet() {return seismicSupportSet;}
		
		/**
		* Get the seismic support representation uuid set of this representation.
		* Useful when one of the seismic support representation is not accessible. At least we know its uuid.
		*/
		//std::vector<std::string> getSeismicSupportUuidSet();

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, HdfProxy * proxy);

		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			AbstractRepresentation * seismicSupport);
		
		/**
		* Get all the inlines of the points of a specific patch.
		* @return NULL if seismic info have not been provided.
		*/
		//void getInlinesOfPointsOfPatch(const unsigned int & patchIndex, double* values);

		/**
		* Get all the crosslines of the points of a specific patch.
		* @return NULL if seismic info have not been provided.
		*/
		//void getCrosslinesOfPointsOfPatch(const unsigned int & patchIndex, double* values);

		/**
		* Push back a patch of seismic 2D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		* @param The index of the geometry patch which receives these seismic coordinates
		*/
		void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, HdfProxy * proxy);

		/**
		* Get all the abscissa of the points of a specific patch related to seismic line 2d.
		* @return NULL if seismic info have not been provided.
		*/
		void getSeismicLineAbscissaOfPointsOfPatch(const unsigned int & patchIndex, double* values);

		/**
		* Get the count of seismic points in a particular patch of this representation
		*/
		//unsigned int getSeismicPointCountOfPatch(const unsigned int & patchIndex);

		/**
		* Get the seismic support of a specific patch.
		* @return NULL if seismic info have not been provided.
		*/
		AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex);

		virtual unsigned int getPatchCount() const = 0;

		void pushBackIntoRepresentationSet(class RepresentationSetRepresentation * repSet);

		//******************************************************************
		//******************** MANDATORY FOR GsoapWrapper ******************
		//******************************************************************

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;

		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		void setHdfProxy(class HdfProxy * proxy);

	protected:
		// XML forward relationships
		class AbstractFeatureInterpretation*				interpretation;
		class HdfProxy * 									hdfProxy;
		class AbstractLocal3dCrs *							localCrs;
		std::vector<AbstractRepresentation*> 				seismicSupportSet;

		// XML backward relationships
		std::vector<class SubRepresentation*>				subRepresentationSet;
		std::vector<AbstractProperty*>						propertySet;
		std::vector<AbstractRepresentation*> 				seismicSupportedRepSet;
		std::vector<class RepresentationSetRepresentation*>	representationSetRepresentationSet;

		friend void AbstractProperty::setRepresentation(AbstractRepresentation * rep);
	};
}

