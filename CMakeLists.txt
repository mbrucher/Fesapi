CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

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
SET (WITH_PROPERTY_MAPPING ON CACHE BOOL "generates Resqml proxies with property mapping handling" )
SET (BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib")
SET (ENERGISTICS_SCHEMAS_LOCATION  ${FESAPI_PARENT_DIR}/energistics_schemas CACHE PATH "Energistics schemas path")
MARK_AS_ADVANCED (ENERGISTICS_SCHEMAS_LOCATION)
SET (RESQML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/energyml/data/resqmlv2/v2.0/xsd_schemas)
SET (WITSML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/WITSML_v1.4.1.1_Data_Schema/witsml_v1.4.1.1_data/xsd_schemas)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET (CMAKE_INSTALL_PREFIX ${FESAPI_BINARY_DIR}/install CACHE PATH "FesapiCpp install prefix" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

SET (WITH_SZIP ON CACHE BOOL "SZIP support in HDF5")

IF (UNIX)
	IF (NOT CMAKE_BUILD_TYPE)
		SET (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel" FORCE)
	ENDIF (NOT CMAKE_BUILD_TYPE)
ENDIF (UNIX)

# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

IF (UNIX)
	IF (PROXIES_GENERATION)
		SET (GSOAP_LOCATION "" CACHE PATH "GSoap sources path")
		FIND_PACKAGE (GSOAP REQUIRED)
	ENDIF (PROXIES_GENERATION)
	
	FIND_PACKAGE (HDF5 REQUIRED COMPONENTS CXX)
	MARK_AS_ADVANCED (HDF5_DIR)
	
	FIND_PACKAGE (MiniZip REQUIRED)
	MARK_AS_ADVANCED (MINIZIP_INCLUDE_DIR)
	MARK_AS_ADVANCED (MINIZIP_LIBRARY)
	
	FIND_PACKAGE (ZLIB REQUIRED)
	
	IF (WITH_SZIP)
		MESSAGE( STATUS "SZIP_INSTALL:         " $ENV{SZIP_INSTALL} )
		FIND_PACKAGE (SZIP REQUIRED)
	ENDIF (WITH_SZIP)
	
	FIND_PACKAGE (UUID REQUIRED)
	MARK_AS_ADVANCED (UUID_INCLUDE_DIR)
	MARK_AS_ADVANCED (UUID_LIBRARY)
	MARK_AS_ADVANCED (UUID_LIBRARY_DEBUG)
	
ELSEIF (WIN32)
	IF (PROXIES_GENERATION)
		SET (GSOAP_LOCATION ${FESAPI_PARENT_DIR}/dependencies/gsoap-2.8/gsoap CACHE PATH "GSoap path")
		FIND_PACKAGE (GSOAP REQUIRED)
	ENDIF (PROXIES_GENERATION)
	
	IF (ARCHITECTURE MATCHES "x86")
	
		SET (HDF5_INCLUDE_DIRS ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/include CACHE PATH "hdf5 headers path")
		SET (HDF5_LIB ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/lib/hdf5.lib CACHE FILEPATH "hdf5 library")
		SET (HDF5_LIB_CPP ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/lib/hdf5_cpp.lib CACHE FILEPATH "hdf5 c++ library")
		SET (HDF5_LIBS ${HDF5_LIB} ${HDF5_LIB_CPP})
				
		SET (MINIZIP_INCLUDE_DIR ${FESAPI_PARENT_DIR}/dependencies/minizip-win32-vs2012-static/include CACHE PATH "minizip headers path")
		SET (MINIZIP_LIB  ${FESAPI_PARENT_DIR}/dependencies/minizip-win32-vs2012-static/lib/minizip.lib CACHE FILEPATH "minizip library")
		
		SET (ZLIB_INCLUDE_DIRS ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/include CACHE PATH "zlib header path")
		SET (ZLIB_LIB ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/lib/zlib.lib CACHE FILEPATH "zlib library")
		
		IF (WITH_SZIP)
			SET (SZIP_INCLUDE_DIRS ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/include CACHE PATH "szip header path")
			SET (SZIP_LIB ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win32-vs2012-shared/lib/szip.lib CACHE FILEPATH "szip library")
		ENDIF (WITH_SZIP)
	ELSE (ARCHITECTURE MATCHES "x64")
		SET (HDF5_INCLUDE_DIRS ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/include CACHE PATH "hdf5 headers path")
		SET (HDF5_LIB ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/lib/libhdf5.lib CACHE FILEPATH "hdf5 library")
		SET (HDF5_LIB_CPP ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/lib/libhdf5_cpp.lib CACHE FILEPATH "hdf5 c++ library")
		SET (HDF5_LIBS ${HDF5_LIB} ${HDF5_LIB_CPP})
			
		SET (MINIZIP_INCLUDE_DIR ${FESAPI_PARENT_DIR}/dependencies/minizip-win64-vs2012-static/include CACHE PATH "minizip headers path")
		SET (MINIZIP_LIB ${FESAPI_PARENT_DIR}/dependencies/minizip-win64-vs2012-static/lib/minizip.lib CACHE FILEPATH "minizip library")
	
		SET (ZLIB_INCLUDE_DIRS ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/include CACHE PATH "zlib header path")
		SET (ZLIB_LIB ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/lib/libzlib.lib CACHE FILEPATH "zlib library")
	
		IF (WITH_SZIP)
			SET (SZIP_INCLUDE_DIRS ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/include CACHE PATH "szip header path")
			SET (SZIP_LIB ${FESAPI_PARENT_DIR}/dependencies/hdf5-1.8.14-win64-vs2012-static/lib/libszip.lib CACHE FILEPATH "szip library")
		ENDIF (WITH_SZIP)
	ENDIF (ARCHITECTURE MATCHES "x86")
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
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GL /MP")
ENDIF (WIN32)

# ============================================================================
# including subdirectories
# ============================================================================

ADD_SUBDIRECTORY (src)
ADD_SUBDIRECTORY (example)
