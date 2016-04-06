CMAKE_MINIMUM_REQUIRED (VERSION 3.1.0)

PROJECT (Fesapi)

SET (FESAPI_ROOT_DIR ${CMAKE_SOURCE_DIR})
SET (FESAPI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ============================================================================
# user variables
# ============================================================================

# we check if Resqml/Witsml proxies are already provided
FILE (GLOB FESAPI_PROXIES_SOURCES ${FESAPI_ROOT_DIR}/src/proxies/*.cpp)
FILE (GLOB FESAPI_PROXIES_HEADERS ${FESAPI_ROOT_DIR}/src/proxies/*.h)
IF (FESAPI_PROXIES_SOURCES STREQUAL "")
	SET (PROXIES_GENERATION ON)
ELSE (FESAPI_PROXIES_SOURCES STREQUAL "")
	SET (PROXIES_GENERATION OFF)
ENDIF (FESAPI_PROXIES_SOURCES STREQUAL "")

# on Windows checking if the target architecture is 32 bits or 64 bits
IF (WIN32)
	STRING (FIND ${CMAKE_GENERATOR} 64 POS)
	IF (POS EQUAL -1) 
		#SET (ARCHITECTURE "x86" CACHE STRING "Set dependencies to "x64" (resp. "x86") default values")
		SET (ARCHITECTURE "x86")
	ELSE (POS EQUAL -1)
		#SET (ARCHITECTURE "x64" CACHE STRING "Set dependencies to "x64" (resp. "x86") default values")
		SET (ARCHITECTURE "x64")
	ENDIF (POS EQUAL -1) 
ENDIF (WIN32)

GET_FILENAME_COMPONENT (FESAPI_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
SET (BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib")
SET (ENERGISTICS_SCHEMAS_LOCATION  ${FESAPI_PARENT_DIR}/energistics_schemas CACHE PATH "Energistics schemas path")
MARK_AS_ADVANCED (ENERGISTICS_SCHEMAS_LOCATION)
SET (RESQML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/energyml/data/resqmlv2/v2.0.1/xsd_schemas)
SET (WITSML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/WITSML_v1.4.1.1_Data_Schema/witsml_v1.4.1.1_data/xsd_schemas)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET (CMAKE_INSTALL_PREFIX ${FESAPI_BINARY_DIR}/install CACHE PATH "FesapiCpp install prefix" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

IF (UNIX)
	SET (WITH_SZIP ON CACHE BOOL "SZIP support in HDF5")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.6 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.6)
		add_compile_options(-std=c++11)
	endif()
	IF (NOT CMAKE_BUILD_TYPE)
		SET (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel" FORCE)
	ENDIF (NOT CMAKE_BUILD_TYPE)
	add_compile_options(-fPIC)
ENDIF (UNIX)

# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

IF (NOT HDF5_ROOT)
	SET(HDF5_ROOT $ENV{HDF5_ROOT})
ENDIF(NOT HDF5_ROOT)
IF (UNIX)
	FIND_PACKAGE (HDF5 REQUIRED)
	
	IF (NOT ZLIB_ROOT)
		SET(ZLIB_ROOT $ENV{HDF5_ROOT})
	ENDIF(NOT ZLIB_ROOT)
	FIND_PACKAGE (ZLIB REQUIRED)

	IF (WITH_SZIP)
		IF (NOT SZIP_ROOT)
			SET(SZIP_ROOT $ENV{HDF5_ROOT})
		ENDIF(NOT SZIP_ROOT)
		FIND_PACKAGE (SZIP REQUIRED)
	ENDIF (WITH_SZIP)
	
ELSEIF (WIN32)
	SET (WITH_HDF5_SHARED_LIBRARIES ON CACHE BOOL "Use shared or static HDF5 libraries")

	# Need to have set the environment variable HDF5_DIR in windows before!!! This env variable needs to point to the cmake directory of the hdf5 install directory.
	if(${WITH_HDF5_SHARED_LIBRARIES})
		find_package (HDF5 NAMES hdf5 COMPONENTS C shared) 
	else()
		find_package (HDF5 NAMES hdf5 COMPONENTS C static)
	endif()
ENDIF (UNIX)
SET (WITH_RESQML2_1 OFF CACHE BOOL "Support for Resqml 2.1")

FIND_PACKAGE (MiniZip REQUIRED)
MARK_AS_ADVANCED (MINIZIP_INCLUDE_DIR)
MARK_AS_ADVANCED (MINIZIP_LIBRARY)

IF (UNIX)

	IF (PROXIES_GENERATION)
		SET (GSOAP_LOCATION "" CACHE PATH "GSoap sources path")
		FIND_PACKAGE (GSOAP REQUIRED)
	ENDIF (PROXIES_GENERATION)
	
	FIND_PACKAGE (UUID REQUIRED)
	MARK_AS_ADVANCED (UUID_INCLUDE_DIR)
	MARK_AS_ADVANCED (UUID_LIBRARY)
	MARK_AS_ADVANCED (UUID_LIBRARY_DEBUG)
	
ELSEIF (WIN32)

	IF (PROXIES_GENERATION)
		SET (GSOAP_LOCATION ${FESAPI_PARENT_DIR}/dependencies/gsoap-2.8/gsoap CACHE PATH "GSoap path")
		FIND_PACKAGE (GSOAP REQUIRED)
	ENDIF (PROXIES_GENERATION)
	
ENDIF (UNIX)

# ============================================================================
# some useful variables
# ============================================================================

IF (BUILD_SHARED_LIBS)
	SET (LIB_TYPE SHARED)
ELSE (BUILD_SHARED_LIBS)
	SET (LIB_TYPE STATIC)
ENDIF (BUILD_SHARED_LIBS)

# ============================================================================
# compilation options
# ============================================================================

IF (WIN32)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
ENDIF (WIN32)

# ============================================================================
# including subdirectories
# ============================================================================

ADD_SUBDIRECTORY (src)
ADD_SUBDIRECTORY (example)
ADD_SUBDIRECTORY (doc)
