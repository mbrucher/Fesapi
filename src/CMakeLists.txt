CMAKE_MINIMUM_REQUIRED (VERSION 3.1.0)


PROJECT (Fesapi_SRC)
set (Fesapi_SRC_VERSION_MAJOR 0)
set (Fesapi_SRC_VERSION_MINOR 10)
set (Fesapi_SRC_VERSION_PATCH 0)
set (Fesapi_SRC_VERSION_TWEAK 0)
set (Fesapi_SRC_VERSION ${Fesapi_SRC_VERSION_MAJOR}.${Fesapi_SRC_VERSION_MINOR}.${Fesapi_SRC_VERSION_PATCH}.${Fesapi_SRC_VERSION_TWEAK})

# ============================================================================
# Resqml/Witsqml proxies generation
# ============================================================================

SET (RESQML_PREFIX_2 "resqml2")
SET (RESQML_PREFIX_2_0_1 "resqml2_0_1")
SET (RESQML_PREFIX_2_1 "resqml2_1")
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
		OUTPUT ${RESQML_PREFIX_2_0_1}ForGsoap.h
		COMMAND ${GSOAP_WSDL2H} -W -gjk -q gsoap_${RESQML_PREFIX_2_0_1} -o ${RESQML_PREFIX_2_0_1}ForGsoap.h ${RESQML_XSD_FILES} ${CMAKE_CURRENT_BINARY_DIR}/PropertyTypeMapping.xsd
		DEPENDS typemap.dat PropertyTypeMapping.xsd
	)

	ADD_CUSTOM_COMMAND (
		OUTPUT 
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}C.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}H.h
			${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}Stub.h
		COMMAND ${GSOAP_SOAPCPP2} -jCLbst -I${GSOAP_LOCATION}/import -p${RESQML_PREFIX_2_0_1} -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESQML_PREFIX_2_0_1}ForGsoap.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${RESQML_PREFIX_2_0_1}C.cpp ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}C.cpp
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${RESQML_PREFIX_2_0_1}H.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}H.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gsoap_${RESQML_PREFIX_2_0_1}Stub.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}Stub.h
		DEPENDS ${RESQML_PREFIX_2_0_1}ForGsoap.h
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
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_0_1}C.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${WITSML_PREFIX}C.cpp
	)
	SET (FESAPI_PROXIES_HEADERS
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/envH.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/envStub.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_resqml2_0_1H.h
		${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_resqml2_0_1Stub.h
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

FILE (GLOB FESAPI_TOOLS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.cpp)
FILE (GLOB FESAPI_TOOLS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.h)

FILE (GLOB FESAPI_EPC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.cpp)
FILE (GLOB FESAPI_EPC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.h)

FILE (GLOB FESAPI_RESQML_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.cpp)
FILE (GLOB FESAPI_RESQML_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.h)

FILE (GLOB FESAPI_RESQML_2_0_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.cpp)
FILE (GLOB FESAPI_RESQML_2_0_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.h)

if (${WITH_RESQML2_1})
	FILE (GLOB FESAPI_RESQML_2_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_1}/*.cpp)
	FILE (GLOB FESAPI_RESQML_2_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_1}/*.h)
else (${WITH_RESQML2_1})
	list(REMOVE_ITEM FESAPI_PROXIES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_1}C.cpp)
	list(REMOVE_ITEM FESAPI_PROXIES_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_1}H.h ${CMAKE_CURRENT_SOURCE_DIR}/proxies/gsoap_${RESQML_PREFIX_2_1}Stub.h)
endif (${WITH_RESQML2_1})
	
FILE (GLOB FESAPI_WITSML_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX}/*.cpp)
FILE (GLOB FESAPI_WITSML_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX}/*.h)

SET (ALL_SOURCES_AND_HEADERS
	${FESAPI_SOURCES}
	${FESAPI_HEADERS}
	${FESAPI_TOOLS_SOURCES}
	${FESAPI_TOOLS_HEADERS}
	${FESAPI_EPC_SOURCES}
	${FESAPI_EPC_HEADERS}
	${FESAPI_RESQML_2_SOURCES}
	${FESAPI_RESQML_2_HEADERS}
	${FESAPI_RESQML_2_0_1_SOURCES}
	${FESAPI_RESQML_2_0_1_HEADERS}
	${FESAPI_WITSML_SOURCES}
	${FESAPI_WITSML_HEADERS}
	${FESAPI_PROXIES_SOURCES}
	${FESAPI_PROXIES_HEADERS}
)

if (${WITH_RESQML2_1})
	SET (ALL_SOURCES_AND_HEADERS
		${ALL_SOURCES_AND_HEADERS}
		${FESAPI_RESQML_2_1_SOURCES}
		${FESAPI_RESQML_2_1_HEADERS}
	)
endif (${WITH_RESQML2_1})

IF (WITH_JAVA_WRAPPING)
	FIND_PACKAGE(JNI REQUIRED)
	FIND_PACKAGE(SWIG REQUIRED)
	FIND_PACKAGE(Java REQUIRED)
	INCLUDE(UseJava)

	message("Generating SWIG files")
	#Cleaning
	FILE (GLOB TO_DELETE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/*.java)
	if (TO_DELETE)
		FILE (REMOVE ${TO_DELETE})
	endif (TO_DELETE)
	FILE (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/common)
	FILE (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2)
	FILE (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2_0_1)
	FILE (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/witsml1_4_1_1)

	# Filling
	IF (WIN32)
		set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i")
		execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
	ELSEIF (UNIX)
		set ( EXECUTE_COMMAND ${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i)
		execute_process(COMMAND ${EXECUTE_COMMAND})
	ENDIF (WIN32)
	message("SWIG files have been generated")
	
	# Building the jar
	FILE (GLOB_RECURSE SWIG_JAVA_FILES ${FESAPI_ROOT_DIR}/java/src/*.java)
	add_jar(fesapiJava ${SWIG_JAVA_FILES})
	install_jar(fesapiJava ${CMAKE_INSTALL_PREFIX}/lib)
	
	SET (ALL_SOURCES_AND_HEADERS
		${ALL_SOURCES_AND_HEADERS}
		${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp
	)
	INCLUDE_DIRECTORIES (${JAVA_INCLUDE_PATH}
		${JAVA_INCLUDE_PATH2}
	)

ENDIF (WITH_JAVA_WRAPPING)

IF (WITH_DOTNET_WRAPPING)
	FIND_PACKAGE(SWIG REQUIRED)
	
	message("Generating SWIG files")
	#Cleaning
	execute_process(COMMAND powershell "Remove-Item ${FESAPI_ROOT_DIR}/cs/src/* -recurse")
	
	# Filling
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -csharp -dllimport ${FESAPI_LIBRARY_NAME}.${Fesapi_SRC_VERSION}.dll -namespace f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/cs/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
	message("SWIG files have been generated")

	#Add the swig cpp file to the FesapiCpp
	SET (ALL_SOURCES_AND_HEADERS
		${ALL_SOURCES_AND_HEADERS}
		${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp
	)
	 
	# Copy the UTF8Marshaller csharp class to the cshapr src directory
	CONFIGURE_FILE(${FESAPI_ROOT_DIR}/cmake/UTF8Marshaler.cs ${FESAPI_ROOT_DIR}/cs/src/UTF8Marshaler.cs) # Overwrite if different
	
	# Create the Visual Studio project from a template file
	FILE(TO_NATIVE_PATH "${FESAPI_ROOT_DIR}/cs/src" DOS_STYLE_SOURCE_DIR)
	CONFIGURE_FILE(${FESAPI_ROOT_DIR}/cmake/fesapiCs.csproj.template ${FESAPI_ROOT_DIR}/cs/fesapiCs.csproj) # Overwrite if different
ENDIF (WITH_DOTNET_WRAPPING)

# organizing sources and headers in the Visual Studio Project
IF (WIN32)
	SOURCE_GROUP ("" FILES ${FESAPI_SOURCES} ${FESAPI_HEADERS})
	SOURCE_GROUP ("tools" FILES ${FESAPI_TOOLS_SOURCES} ${FESAPI_TOOLS_HEADERS})
	SOURCE_GROUP ("epc" FILES ${FESAPI_EPC_SOURCES} ${FESAPI_EPC_HEADERS})
	
	SOURCE_GROUP ("${RESQML_PREFIX_2}" FILES ${FESAPI_RESQML_2_SOURCES} ${FESAPI_RESQML_2_HEADERS})
	
	SOURCE_GROUP ("${RESQML_PREFIX_2_0_1}" FILES ${FESAPI_RESQML_2_0_1_SOURCES} ${FESAPI_RESQML_2_0_1_HEADERS})
	
if (${WITH_RESQML2_1})
	SOURCE_GROUP ("${RESQML_PREFIX_2_1}" FILES ${FESAPI_RESQML_2_1_SOURCES} ${FESAPI_RESQML_2_1_HEADERS})
endif (${WITH_RESQML2_1})
	
	SOURCE_GROUP ("${WITSML_PREFIX}" FILES ${FESAPI_WITSML_SOURCES} ${FESAPI_WITSML_HEADERS})
	SOURCE_GROUP ("proxies" FILES ${FESAPI_PROXIES_SOURCES} ${FESAPI_PROXIES_HEADERS})
ENDIF (WIN32)

# ============================================================================
# Setting include directories
# ============================================================================

INCLUDE_DIRECTORIES (
	${CMAKE_CURRENT_SOURCE_DIR}
	${HDF5_INCLUDE_DIR}
	${HDF5_INCLUDE_DIRS}
	${MINIZIP_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIR}
)


IF (UNIX)
	IF (WITH_SZIP)
		INCLUDE_DIRECTORIES (${SZIP_INCLUDE_DIRS})
	ENDIF (WITH_SZIP)

	INCLUDE_DIRECTORIES (${UUID_INCLUDE_DIRS})
ENDIF (UNIX)

# ============================================================================
# Add FesapiCpp library to build
# ============================================================================

IF (WIN32)
	ADD_DEFINITIONS (/bigobj)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS (-DFESAPI_DLL)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (WIN32)

if (${WITH_RESQML2_1})
	ADD_DEFINITIONS (/DWITH_RESQML2_1)
endif (${WITH_RESQML2_1})

ADD_LIBRARY (${FESAPI_LIBRARY_NAME} ${LIB_TYPE} ${ALL_SOURCES_AND_HEADERS})
SET_TARGET_PROPERTIES(${FESAPI_LIBRARY_NAME} PROPERTIES DEBUG_POSTFIX "d")

IF (WIN32)
	if(${WITH_HDF5_SHARED_LIBRARIES})
		TARGET_LINK_LIBRARIES (${FESAPI_LIBRARY_NAME} ${MINIZIP_LIBRARY} ${ZLIB_LIBRARIES} ${HDF5_C_SHARED_LIBRARY})
	else ()
		TARGET_LINK_LIBRARIES (${FESAPI_LIBRARY_NAME} ${MINIZIP_LIBRARY} ${ZLIB_LIBRARIES} ${HDF5_C_STATIC_LIBRARY})
	endif ()
	SET_TARGET_PROPERTIES(FesapiCpp PROPERTIES
									LINK_FLAGS "/INCREMENTAL:NO /OPT:REF"
									RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}
									SUFFIX ".${Fesapi_SRC_VERSION}.dll"
									IMPORT_SUFFIX ".${Fesapi_SRC_VERSION}.lib"
									VERSION ${Fesapi_SRC_VERSION_MAJOR}.${Fesapi_SRC_VERSION_MINOR})
ELSEIF (UNIX)
	IF (WITH_SZIP)
		TARGET_LINK_LIBRARIES (${FESAPI_LIBRARY_NAME} ${UUID_LIBRARIES} ${SZIP_LIBRARIES} ${ZLIB_LIBRARIES} ${GSOAP_LIBRARIES} ${MINIZIP_LIBRARY} ${HDF5_hdf5_LIBRARY_RELEASE})
	ELSE (WITH_SZIP)
		TARGET_LINK_LIBRARIES (${FESAPI_LIBRARY_NAME} ${UUID_LIBRARIES} ${ZLIB_LIBRARIES} ${GSOAP_LIBRARIES} ${MINIZIP_LIBRARY} ${HDF5_hdf5_LIBRARY_RELEASE})
	ENDIF (WITH_SZIP)
	SET_TARGET_PROPERTIES(FesapiCpp PROPERTIES
									COMPILE_FLAGS "-fPIC"
									VERSION ${Fesapi_SRC_VERSION}
									SOVERSION ${Fesapi_SRC_VERSION_MAJOR}.${Fesapi_SRC_VERSION_MINOR})
ENDIF (WIN32)

# ============================================================================
# Install FesapiCpp library
# ============================================================================

INSTALL (
	TARGETS ${FESAPI_LIBRARY_NAME}
	DESTINATION lib
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

# tools headers
INSTALL (
	FILES ${FESAPI_TOOLS_HEADERS}
	DESTINATION include/tools/
)

# epc headers
INSTALL (
	FILES ${FESAPI_EPC_HEADERS}
	DESTINATION include/epc/
)

# resqml headers
INSTALL (
	FILES ${FESAPI_RESQML_2_HEADERS}
	DESTINATION include/${RESQML_PREFIX_2}/
)

INSTALL (
	FILES ${FESAPI_RESQML_2_0_1_HEADERS}
	DESTINATION include/${RESQML_PREFIX_2_0_1}/
)

if (${WITH_RESQML2_1})
	INSTALL (
		FILES ${FESAPI_RESQML_2_1_HEADERS}
		DESTINATION include/${RESQML_PREFIX_2_1}/
	)
endif (${WITH_RESQML2_1})

# witsml headers
INSTALL (
	FILES ${FESAPI_WITSML_HEADERS}
	DESTINATION include/${WITSML_PREFIX}/
)

# PropertyTypeMapping.xml
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/resources/PropertyKindMapping.xml
	DESTINATION resources/
)
