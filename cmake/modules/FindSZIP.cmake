# - Find SZIP library
# - Derived from the FindZLIB.cmake that is included with cmake
# Find the native SZIP includes and library
# This module defines
#  SZIP_INCLUDE_DIRS, where to find szlib.h, etc.
#  SZIP_LIBRARIES, libraries to link against to use SZIP.
#  SZIP_FOUND, If false, do not try to use SZIP.
#    also defined, but not for general use are
#  SZIP_LIBRARY, where to find the SZIP library.

# message (STATUS "Finding SZIP library and headers..." )

############################################
#
# Check the existence of the libraries.
#
############################################
# This macro was taken directly from the FindZLIB.cmake file that is included
# with the CMake distribution. This is NOT my work. Most of the work was done by the
# original authors of the FindZLIB.cmake file. Only minor modifications were
# made to remove references to make this file applicable to SZIP
#########################################################################

set(_SZIP_SEARCHES)

# Search ZLIB_ROOT first if it is set.
if(SZIP_ROOT)
  set(_SZIP_SEARCH_ROOT PATHS ${SZIP_ROOT} NO_DEFAULT_PATH)
  list(APPEND _SZIP_SEARCHES _SZIP_SEARCH_ROOT)
endif()

# Normal search.
set(_SZIP_SEARCH_NORMAL
  PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\szip;InstallPath]"
        "$ENV{PROGRAMFILES}/szip"
  )
list(APPEND _SZIP_SEARCHES _SZIP_SEARCH_NORMAL)

# Try each search configuration.
foreach(search ${_SZIP_SEARCHES})
  find_path(SZIP_INCLUDE_DIR NAMES szlib.h ${${search}} PATH_SUFFIXES include)
  find_library(SZIP_LIBRARY_SHARED  NAMES szip ${${search}} PATH_SUFFIXES lib)
  find_library(SZIP_LIBRARY_STATIC  NAMES libszip ${${search}} PATH_SUFFIXES lib)
endforeach()

mark_as_advanced(SZIP_LIBRARY_STATIC SZIP_LIBRARY_SHARED SZIP_INCLUDE_DIR)

if(SZIP_INCLUDE_DIR AND EXISTS "${SZIP_INCLUDE_DIR}/szlib.h")
    file(STRINGS "${SZIP_INCLUDE_DIR}/szlib.h" SZIP_H REGEX "^#define SZLIB_VERSION \"[^\"]*\"$")

    string(REGEX REPLACE "^.*SZLIB_VERSION \"([0-9]+).*$" "\\1" SZIP_VERSION_MAJOR "${SZIP_H}")
    string(REGEX REPLACE "^.*SZLIB_VERSION \"[0-9]+\\.([0-9]+).*$" "\\1" SZIP_VERSION_MINOR  "${SZIP_H}")
    set(SZIP_VERSION_STRING "${SZIP_VERSION_MAJOR}.${SZIP_VERSION_MINOR}")
endif()

# handle the QUIETLY and REQUIRED arguments and set SZIP_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
if (SZIP_LIBRARY_SHARED)
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(SZIP REQUIRED_VARS SZIP_LIBRARY_SHARED SZIP_INCLUDE_DIR)
else (SZIP_LIBRARY_SHARED)
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(SZIP REQUIRED_VARS SZIP_LIBRARY_STATIC SZIP_INCLUDE_DIR)
endif()

if(SZIP_FOUND)
    set(SZIP_INCLUDE_DIRS ${SZIP_INCLUDE_DIR})
	
	if (SZIP_LIBRARY_SHARED)
		set(SZIP_LIBRARIES ${SZIP_LIBRARY_SHARED})

		if(NOT TARGET SZIP::SZIP)
		  add_library(SZIP::SZIP UNKNOWN IMPORTED)
		  set_target_properties(SZIP::SZIP PROPERTIES
			IMPORTED_LOCATION "${SZIP_LIBRARY_SHARED}"
			INTERFACE_INCLUDE_DIRECTORIES "${SZIP_INCLUDE_DIRS}")
		endif()
	else (SZIP_LIBRARY_SHARED)
		set(SZIP_LIBRARIES ${SZIP_LIBRARY_STATIC})

		if(NOT TARGET SZIP::SZIP)
		  add_library(SZIP::SZIP UNKNOWN IMPORTED)
		  set_target_properties(SZIP::SZIP PROPERTIES
			IMPORTED_LOCATION "${SZIP_LIBRARY_STATIC}"
			INTERFACE_INCLUDE_DIRECTORIES "${SZIP_INCLUDE_DIRS}")
		endif()
	endif()
endif()
