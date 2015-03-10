CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (Fesapi_SRC)

# ============================================================================
# Resqml/Witsqml proxies generation
# ============================================================================

SET (RESQML_PREFIX "resqml2_0")
SET (WITSML_PREFIX "witsml1_4_1_1")

IF (PROXIES_GENERATION)
	# setting RESQML_XSD_FILES 
	SET (RESQML_XSD_FILES ${RESQML_SCHEMA_LOCATION}/ResqmlAllObjects.xsd)

	# copying namespace.cpp to proxies output directory
	ADD_CUSTOM_COMMAND (
			OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/proxies/namespace.cpp
			COMMAND ${CMAKE_COMMAND} -E copy ${FESAPI_ROOT_DIR}/gsoap/namespace.cpp ${CMAKE_CURRENT_SOURCE_DIR}/proxies/namespace.cpp
	)

	# copying stdsoap2.cpp(.h) to proxies output directory
	ADD_CUSTOM_COMMAND (
			OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/proxies/stdsoap2.cpp
			OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/proxies/stdsoap2.h
			COMMAND ${CMAKE_COMMAND} -E copy ${GSOAP_STDSOAP2_H} ${CMAKE_CURRENT_SOURCE_DIR}/proxies/stdsoap2.h
			COMMAND ${CMAKE_COMMAND} -E copy ${GSOAP_STDSOAP2_CPP} ${CMAKE_CURRENT_SOURCE_DIR}/proxies/stdsoap2.cpp
	)
		
	ADD_CUSTOM_COMMAND (
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/proxies/envC.cpp ${CMAKE_CURRENT_SOURCE_DIR}/proxies/envH.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/envStub.h
		COMMAND ${GSOAP_SOAPCPP2} -penv -d${CMAKE_CURRENT_BINARY_DIR} ${FESAPI_ROOT_DIR}/gsoap/env.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/envC.cpp ${CMAKE_CURRENT_SOURCE_DIR}/proxies/envC.cpp
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/envH.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/envH.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/envStub.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/envStub.h
	)

	if(WITH_PROPERTY_MAPPING)
		IF (UNIX) 
			ADD_CUSTOM_COMMAND (
				OUTPUT typemap.dat PropertyTypeMapping.xsd
				COMMAND ${CMAKE_COMMAND} -E copy ${FESAPI_ROOT_DIR}/gsoap/typemap.dat ${CMAKE_CURRENT_BINARY_DIR}/typemap.dat
				COMMAND ${CMAKE_COMMAND} -E copy ${FESAPI_ROOT_DIR}/gsoap/PropertyTypeMapping.xsd ${CMAKE_CURRENT_BINARY_DIR}/PropertyTypeMapping.xsd
				# next command aims at inserting the Resqml schema location into PropertyTypeMapping.xsd
				COMMAND sed -i -e 's|RESQML_SCHEMA_LOCATION|${RESQML_SCHEMA_LOCATION}|g' ${CMAKE_CURRENT_BINARY_DIR}/PropertyTypeMapping.xsd 
			)
		ELSEIF (WIN32)
			ADD_CUSTOM_COMMAND (
				OUTPUT typemap.dat PropertyTypeMapping.xsd
				COMMAND ${CMAKE_COMMAND} -E copy ${FESAPI_ROOT_DIR}/gsoap/typemap.dat ${CMAKE_CURRENT_BINARY_DIR}/typemap.dat
				# next command aims at inserting the Resqml schema location into PropertyTypeMapping.xsd
				COMMAND cscript ${FESAPI_ROOT_DIR}/gsoap/sed.vbs "s*RESQML_SCHEMA_LOCATION*${RESQML_SCHEMA_LOCATION}*g" < ${FESAPI_ROOT_DIR}/gsoap/PropertyTypeMapping.xsd > ${CMAKE_CURRENT_BINARY_DIR}/PropertyTypeMapping.xsd
			)
		ENDIF (UNIX)
	
		add_custom_command(
			OUTPUT ${RESQML_PREFIX}ForGsoap.h
			COMMAND ${GSOAP_WSDL2H} -W -gjk -q gsoap_${RESQML_PREFIX} -o ${RESQML_PREFIX}ForGsoap.h ${RESQML_XSD_FILES} ${CMAKE_CURRENT_BINARY_DIR}/PropertyTypeMapping.xsd
			DEPENDS typemap.dat PropertyTypeMapping.xsd
		)
	else(WITH_PROPERTY_MAPPING)
		ADD_CUSTOM_COMMAND(
			OUTPUT typemap.dat
			COMMAND ${CMAKE_COMMAND} -E copy ${FESAPI_ROOT_DIR}/gsoap/typemap.dat ${CMAKE_CURRENT_BINARY_DIR}/typemap.dat
		)
		
		ADD_CUSTOM_COMMAND(
			OUTPUT ${RESQML_PREFIX}ForGsoap.h
			COMMAND ${GSOAP_WSDL2H} -W -gjk -q gsoap_${RESQML_PREFIX} -o ${RESQML_PREFIX}ForGsoap.h ${RESQML_XSD_FILES}
			DEPENDS typemap.dat
		)
	endif(WITH_PROPERTY_MAPPING)

	ADD_CUSTOM_COMMAND (
		OUTPUT 
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}C.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}H.h
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}Stub.h
		COMMAND ${GSOAP_SOAPCPP2} -jCLbst -I${GSOAP_LOCATION}/import -p${RESQML_PREFIX} -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESQML_PREFIX}ForGsoap.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${RESQML_PREFIX}C.cpp ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}C.cpp
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${RESQML_PREFIX}H.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}H.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${RESQML_PREFIX}Stub.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}Stub.h
		DEPENDS ${RESQML_PREFIX}ForGsoap.h
	)

	# setting WITSML_XSD_FILES
	SET(WITSML_XSD_FILES
		${WITSML_SCHEMA_LOCATION}/obj_well.xsd
		${WITSML_SCHEMA_LOCATION}/obj_wellbore.xsd
		${WITSML_SCHEMA_LOCATION}/obj_trajectory.xsd
		${WITSML_SCHEMA_LOCATION}/obj_log.xsd 
		${WITSML_SCHEMA_LOCATION}/obj_formationMarker.xsd
		${WITSML_SCHEMA_LOCATION}/obj_coordinateReferenceSystem.xsd
	)

	ADD_CUSTOM_COMMAND (
		OUTPUT ${WITSML_PREFIX}ForGsoap.h
		COMMAND ${GSOAP_WSDL2H} -W -gjk -q gsoap_${WITSML_PREFIX} -o ${WITSML_PREFIX}ForGsoap.h ${WITSML_XSD_FILES}
		DEPENDS typemap.dat
	)
	ADD_CUSTOM_COMMAND (
		OUTPUT 
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}C.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}H.h
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}Stub.h
		COMMAND ${GSOAP_SOAPCPP2} -jCLbst -I${GSOAP_LOCATION}/import -p${WITSML_PREFIX} -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${WITSML_PREFIX}ForGsoap.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${WITSML_PREFIX}C.cpp ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}C.cpp
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${WITSML_PREFIX}H.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}H.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${WITSML_PREFIX}Stub.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}Stub.h
		DEPENDS ${WITSML_PREFIX}ForGsoap.h
	)

	SET (FESAPI_PROXIES_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/envC.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/stdsoap2.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/namespace.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX}C.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}C.cpp
	)
	SET (FESAPI_PROXIES_HEADERS
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/envH.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/envStub.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_resqml2_0H.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_resqml2_0Stub.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_witsml1_4_1_1H.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_witsml1_4_1_1Stub.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/stdsoap2.h
	)
ENDIF (PROXIES_GENERATION)

# ============================================================================
# Getting source files
# ============================================================================

SET (WITH_JAVA_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for Java wrappers.")
SET (WITH_DOTNET_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for .NET wrappers.")

FILE (GLOB FESAPI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE (GLOB FESAPI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

FILE (GLOB FESAPI_EPC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.cpp)
FILE (GLOB FESAPI_EPC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.h)

FILE (GLOB FESAPI_RESQML_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX}/*.cpp)
FILE (GLOB FESAPI_RESQML_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX}/*.h)
# removing some sources/headers if property mapping is not handled
IF (NOT WITH_PROPERTY_MAPPING)
	LIST (REMOVE_ITEM FESAPI_RESQML_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX}/PropertyKindMapper.cpp)
	LIST (REMOVE_ITEM FESAPI_RESQML_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX}/PropertyKindMapper.h)
ENDIF (NOT WITH_PROPERTY_MAPPING)
	
FILE (GLOB FESAPI_WITSML_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX}/*.cpp)
FILE (GLOB FESAPI_WITSML_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX}/*.h)

SET (ALL_SOURCES_AND_HEADERS
	${FESAPI_SOURCES}
	${FESAPI_HEADERS}
	${FESAPI_EPC_SOURCES}
	${FESAPI_EPC_HEADERS}
	${FESAPI_RESQML_SOURCES}
	${FESAPI_RESQML_HEADERS}
	${FESAPI_WITSML_SOURCES}
	${FESAPI_WITSML_HEADERS}
	${FESAPI_PROXIES_SOURCES}
	${FESAPI_PROXIES_HEADERS}
)

IF (WITH_JAVA_WRAPPING)
	find_package(JNI)

	if (JNI_FOUND)
	    	SET (ALL_SOURCES_AND_HEADERS
			${ALL_SOURCES_AND_HEADERS}
			${CMAKE_CURRENT_SOURCE_DIR}/../swig/swigGeneratedJavaWrapper.cpp
		)
		INCLUDE_DIRECTORIES (${JAVA_INCLUDE_PATH}
			${JAVA_INCLUDE_PATH2}
		)
	endif(JNI_FOUND)

ENDIF (WITH_JAVA_WRAPPING)

IF (WITH_DOTNET_WRAPPING)
	SET (ALL_SOURCES_AND_HEADERS
		${ALL_SOURCES_AND_HEADERS}
		${CMAKE_CURRENT_SOURCE_DIR}/../swig/swigGeneratedCsWrapper.cpp
	)
ENDIF (WITH_DOTNET_WRAPPING)

# organizing sources and headers in the Visual Studio Project
IF (WIN32)
	SOURCE_GROUP ("" FILES ${FESAPI_SOURCES} ${FESAPI_HEADERS})
	SOURCE_GROUP ("epc" FILES ${FESAPI_EPC_SOURCES} ${FESAPI_EPC_HEADERS})
	SOURCE_GROUP ("${RESQML_PREFIX}" FILES ${FESAPI_RESQML_SOURCES} ${FESAPI_RESQML_HEADERS})
	SOURCE_GROUP ("${WITSML_PREFIX}" FILES ${FESAPI_WITSML_SOURCES} ${FESAPI_WITSML_HEADERS})
	SOURCE_GROUP ("proxies" FILES ${FESAPI_PROXIES_SOURCES} ${FESAPI_PROXIES_HEADERS})
ENDIF (WIN32)

# ============================================================================
# Setting include directories
# ============================================================================

INCLUDE_DIRECTORIES (
	${CMAKE_CURRENT_SOURCE_DIR}/proxies/
	${CMAKE_CURRENT_SOURCE_DIR}/epc/
	${CMAKE_CURRENT_SOURCE_DIR}
	${HDF5_INCLUDE_DIRS}
	${MINIZIP_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIRS}
)

IF (WITH_SZIP)
	INCLUDE_DIRECTORIES (${SZIP_INCLUDE_DIRS})
ENDIF (WITH_SZIP)

IF (UNIX)
	INCLUDE_DIRECTORIES (${UUID_INCLUDE_DIRS})
ENDIF (UNIX)

# ============================================================================
# Add FesapiCpp library to build
# ============================================================================

IF (WIN32)
	ADD_DEFINITIONS (/bigobj)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS (-DDLL -DDLL_EXPORTS)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (WIN32)

ADD_LIBRARY (FesapiCpp ${LIB_TYPE} ${ALL_SOURCES_AND_HEADERS})

IF (WIN32)
	
	IF (WITH_SZIP)
		TARGET_LINK_LIBRARIES (FesapiCpp ${MINIZIP_LIB} ${HDF5_LIBS} ${ZLIB_LIB} ${SZIP_LIB})
	ELSE (WITH_SZIP)
		TARGET_LINK_LIBRARIES (FesapiCpp ${MINIZIP_LIB} ${HDF5_LIBS} ${ZLIB_LIB})
	ENDIF (WITH_SZIP)
	SET_TARGET_PROPERTIES (FesapiCpp PROPERTIES LINK_FLAGS "/LTCG /INCREMENTAL:NO /OPT:REF")
	SET_TARGET_PROPERTIES (FesapiCpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
ELSEIF (UNIX)
	IF (WITH_SZIP)
		TARGET_LINK_LIBRARIES (FesapiCpp ${GSOAP_LIBRARIES} ${MINIZIP_LIBRARY} ${HDF5_CXX_LIBRARIES} ${ZLIB_LIBRARIES} ${UUID_LIBRARIES})
	ELSE (WITH_SZIP)
		TARGET_LINK_LIBRARIES (FesapiCpp ${GSOAP_LIBRARIES} ${MINIZIP_LIBRARY} ${HDF5_CXX_LIBRARIES} ${ZLIB_LIBRARIES} ${UUID_LIBRARIES})
	ENDIF (WITH_SZIP)
ENDIF (WIN32)

# ============================================================================
# Install FesapiCpp library
# ============================================================================

SET (LIB_PATH lib)
#IF (WIN32)
#	SET (LIB_PATH lib/\${CMAKE_INSTALL_CONFIG_NAME})
#ELSEIF (UNIX)
#	SET (LIB_PATH lib/${CMAKE_BUILD_TYPE})
#ENDIF (WIN32)

INSTALL (
	TARGETS FesapiCpp
	DESTINATION ${LIB_PATH}
)

# proxies headers
INSTALL (
	FILES ${FESAPI_PROXIES_HEADERS}
	DESTINATION include/proxies/
)	

# main headers
INSTALL (
	FILES ${FESAPI_HEADERS}
	DESTINATION include/
)

# epc headers
INSTALL (
	FILES ${FESAPI_EPC_HEADERS}
	DESTINATION include/epc/
)

# resqml headers
INSTALL (
	FILES ${FESAPI_RESQML_HEADERS}
	DESTINATION include/${RESQML_PREFIX}/
)

# witsml headers
INSTALL (
	FILES ${FESAPI_WITSML_HEADERS}
	DESTINATION include/${WITSML_PREFIX}/
)

IF (WITH_PROPERTY_MAPPING)
	# PropertyTypeMapping.xml
	INSTALL (
		FILES ${FESAPI_ROOT_DIR}/resources/PropertyTypeMapping.xml
		DESTINATION resources/
	)
ENDIF (WITH_PROPERTY_MAPPING)
