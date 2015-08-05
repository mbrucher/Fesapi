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

/**
* \file Package.cpp
* \class epc::Package
* \author Philippe Verney
*
*	EPC Package class
*	Copyright (c) 2014 F2I-CONSULTING. All rights reserved.
*/

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include "FileCoreProperties.h"
#include "FileContentType.h"
#include "FileRelationship.h"

#include "zip.h"
#include "unzip.h"

namespace epc
{

#define CACHE_FILE_DESCRIPTOR //When defined all file descriptors are cached to speedup file lookup

#ifdef CACHE_FILE_DESCRIPTOR
	/* unz_file_info_interntal contain internal info about a file in zipfile*/
	typedef struct unz_file_info64_internal_s
	{
		ZPOS64_T offset_curfile;            /* relative offset of local header 8 bytes */
		ZPOS64_T byte_before_the_zipfile;   /* byte before the zipfile, (>0 for sfx) */
	#ifdef HAVE_AES
		uLong aes_encryption_mode;
		uLong aes_compression_method;
	#endif
	} unz_file_info64_internal;

	/* file_in_zip_read_info_s contain internal information about a file in zipfile */
	typedef struct
	{
		Bytef *read_buffer;                 /* internal buffer for compressed data */
		z_stream stream;                    /* zLib stream structure for inflate */

	#ifdef HAVE_BZIP2
		bz_stream bstream;                  /* bzLib stream structure for bziped */
	#endif
	#ifdef HAVE_AES
		fcrypt_ctx aes_ctx;
	#endif

		ZPOS64_T pos_in_zipfile;            /* position in byte on the zipfile, for fseek */
		uLong stream_initialised;           /* flag set if stream structure is initialised */

		ZPOS64_T offset_local_extrafield;   /* offset of the local extra field */
		uInt size_local_extrafield;         /* size of the local extra field */
		ZPOS64_T pos_local_extrafield;      /* position in the local extra field in read */
		ZPOS64_T total_out_64;

		uLong crc32;                        /* crc32 of all data uncompressed */
		uLong crc32_wait;                   /* crc32 we must obtain after decompress all */
		ZPOS64_T rest_read_compressed;      /* number of byte to be decompressed */
		ZPOS64_T rest_read_uncompressed;    /* number of byte to be obtained after decomp */

		zlib_filefunc64_32_def z_filefunc;

		voidpf filestream;                  /* io structore of the zipfile */
		uLong compression_method;           /* compression method (0==store) */
		ZPOS64_T byte_before_the_zipfile;   /* byte before the zipfile, (>0 for sfx) */
		int raw;
	} file_in_zip64_read_info_s;

	/* unz64_s contain internal information about the zipfile */
	typedef struct
	{
		zlib_filefunc64_32_def z_filefunc;
		voidpf filestream;                  /* io structure of the current zipfile */
		voidpf filestream_with_CD;          /* io structure of the disk with the central directory */
		unz_global_info64 gi;               /* public global information */
		ZPOS64_T byte_before_the_zipfile;   /* byte before the zipfile, (>0 for sfx)*/
		ZPOS64_T num_file;                  /* number of the current file in the zipfile*/
		ZPOS64_T pos_in_central_dir;        /* pos of the current file in the central dir*/
		ZPOS64_T current_file_ok;           /* flag about the usability of the current file*/
		ZPOS64_T central_pos;               /* position of the beginning of the central dir*/
		uLong number_disk;                  /* number of the current disk, used for spanning ZIP*/
		ZPOS64_T size_central_dir;          /* size of the central directory  */
		ZPOS64_T offset_central_dir;        /* offset of start of central directory with
											   respect to the starting disk number */

		unz_file_info64 cur_file_info;      /* public info about the current file in zip*/
		unz_file_info64_internal cur_file_info_internal;
											/* private info about it*/
		file_in_zip64_read_info_s* pfile_in_zip_read;
											/* structure about the current file if we are decompressing it */
		int encrypted;                      /* is the current file encrypted */
		int isZip64;                        /* is the current file zip64 */
	#ifndef NOUNCRYPT
		unsigned long keys[3];              /* keys defining the pseudo-random sequence */
		const unsigned long* pcrc_32_tab;
	#endif
	} unz64_s;
#endif

	class Package
	{
    public:

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		typedef std::unordered_map<std::string, class FilePart*> PartMap;
#else
		typedef std::tr1::unordered_map<std::string, class FilePart*> PartMap;
#endif

	private :
		FileCoreProperties	fileCoreProperties;											/// Core Properties file
		FileContentType		fileContentType;											/// ContentTypes file
		FileRelationship	filePrincipalRelationship;									/// Relationships file
		PartMap				allFileParts;												/// Set of parts file
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string >		extendedCoreProperties;		/// Set of non standard (extended) core properties
#else
		std::tr1::unordered_map< std::string, std::string >	extendedCoreProperties;		/// Set of non standard (extended) core properties
#endif
		std::string			pathName;													/// Pathname of package
		unzFile				unzipped;
        zipFile             zf;
        bool                isZip64;
#ifdef CACHE_FILE_DESCRIPTOR
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, unz64_s > name2file;
#else
		std::tr1::unordered_map< std::string, unz64_s > name2file;
#endif
#endif

		/**
		* This method allows to write a string content to a non existing part of the package.
		* This method does not create any new FilePart in 'allFileParts' class member.
		*/
		void writeStringIntoNewPart(const std::string &input, const std::string & partPath);
		
		static const char* CORE_PROP_REL_TYPE;
		static const char* EXTENDED_CORE_PROP_REL_TYPE;

	public:
		/** 
		* Create a Package with pathname.
		*/
		Package();

		/**
		* Create a Package with CoreProperties file, ContentType file, Relationship file, vector of Part file and pathname.
		*/
		Package(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const std::string & pkgPathName);

		/**
		* Destructor : free memory allocated for the parts
		*/
		~Package();

		/**
		* Open the package for writing purpose
		*/
		void openForWriting(const std::string & pkgPathName, bool useZip64 = false);

		/**
		* Open the package for reading purpose
		*/
		void openForReading(const std::string & pkgPathName);

		/**
		* Close the package
		*/
		void close();

		/** 
		* @return CoreProperties file.
		*/
		const FileCoreProperties& getFileCoreProperties() const;

		/** 
		* @return ContentType file.
		*/
		const FileContentType& getFileContentType() const;

		/** 
		* @return Relationship file.
		*/
		const FileRelationship& getPrincipalRelationship() const;

		/** 
		* vector of part file.
		*/
		const PartMap & getAllFilePart() const;

		/**
		* Get a const string reference on the name of the package.
		*/
		const std::string & getPathname() const;

		/**
		* @brief set the CoreProperties file.
		* @param pkgFileCP CoreProperties file.
		*/
		void setFileFileCoreProperties(const FileCoreProperties & pkgFileCP);

		/**
		* Get in read/write access all the non standard core properties of this package
		* All added non standard core properties will be stored in a single part which will be linked to the standard core properties part.
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > & getExtendedCoreProperty() {return extendedCoreProperties;}
#else
		std::tr1::unordered_map< std::string, std::string > & getExtendedCoreProperty() {return extendedCoreProperties;}
#endif

		/**
		* @brief add a Property in the CoreProperties file of package.
		* @param pkgTypeProperty	The type of the property to add.
		* @param pkgPropertyValue	The value of the property to add.
		*/
		void addProperty(const CoreProperty::TypeProperty & pkgTypeProperty, const std::string & pkgPropertyValue);

		/**
		* @brief set the ContentTypes file.
		* @param pkgFileCT	The ContentType file.
		*/
		void setFileContentType(const FileContentType & pkgFileCT);

		/**
		* @brief add a ContentType in the ContentTypes file of package.
		* @param contentType The ContentType to add.
		*/
		void addContentType(const ContentType & contentType);

		/**
		* @brief set the Relationships file.
		* @param pkgFileRS Relationship file.
		*/
		void setPrincipalRelationship(const FileRelationship & pkgFileRS);

		/**
		* @brief add a Relationship in the Relationships file of package.
		* @param relationship Relationship file.
		*/
		void addRelationship(const Relationship & relationship);

		/**
		* @brief set all Parts file.
		* @param pkgFilePart	a vector of Part file.
		*/
		void setAllFilePart(const std::vector<class FilePart*> & pkgFilePart);

		/**
		* @brief Creates a part in the package and returns it. This part will be automatically destroy with the package.
		* @return a new part.
		*/
		class FilePart* createPart(const std::string & inputContent, const std::string & outputPartPath);

        /**
         * @brief Find a part corresponding to the given path
         */
        class FilePart* findPart(const std::string & outputPartPath) const;
		
        /**
         * Check that a given file exists in the zip file
         */
        bool fileExists(const std::string & filename) const;

        /**
         * Extract the content of a given file from the zip file
         */
		std::string extractFile(const std::string & filename, const std::string & password = "");

		void writePackage();
	};
}
