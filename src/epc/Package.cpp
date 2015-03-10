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
#include "Package.h"

#include <iostream> 
#include <fstream>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#else 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#endif

#include "FilePart.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define CORE_PROP_REL_TYPE "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties"
#define EXTENDED_CORE_PROP_REL_TYPE "http://schemas.f2i-consulting.com/package/2014/relationships/extended-core-properties"

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!

Package::Package() : unzipped(NULL)
{
}

Package::Package(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const string & pkgPathName):
	fileCoreProperties(pkgFileCP),fileContentType(pkgFileCT),filePrincipalRelationship(pkgFileRS),allFileParts(pkgFileP),pathName(pkgPathName), unzipped(NULL)
{
}

Package::~Package()
{
	for (PartMap::const_iterator i=allFileParts.begin(); i!=allFileParts.end(); i++)
	{
		delete i->second;
    }
	close();
}

void Package::openForWriting(const std::string & pkgPathName)
{
	pathName.assign(pkgPathName);

	// Clean the potential ending slashes
	while (pathName[pathName.size() - 1] == '/' || pathName[pathName.size() - 1] == '\\')
		pathName = pathName.substr(0, pathName.size()-1);

	ContentType contentTypeRel(true, "application/vnd.openxmlformats-package.relationships+xml", ".rels");
	addContentType(contentTypeRel);

	ContentType contentTypeCoreProp(false, "application/vnd.openxmlformats-package.core-properties+xml", "docProps/core.xml");
	addContentType(contentTypeCoreProp);

	Relationship relToCoreProp("docProps/core.xml", CORE_PROP_REL_TYPE,"CoreProperties");
	addRelationship(relToCoreProp);
}

void Package::openForReading(const std::string & pkgPathName)
{
	pathName.assign(pkgPathName);
	
	unzipped = unzOpen64(pathName.c_str());

	if (unzipped==NULL)
    {
        cerr << "Cannot open " << pathName << endl;
        return;
    }

#ifdef CACHE_FILE_DESCRIPTOR
	// Speedup part lookup, by caching zipped file descriptor using file name

#ifndef UNZ_MAXFILENAMEINZIP
#define UNZ_MAXFILENAMEINZIP (256)
#endif

    char current_filename[UNZ_MAXFILENAMEINZIP+1];
	int err = unzGoToFirstFile2(unzipped, NULL, current_filename, sizeof(current_filename)-1, NULL, 0, NULL, 0);
    while (err == UNZ_OK)
    {
		name2file[current_filename]=*(unz64_s*)unzipped;
        err = unzGoToNextFile2(unzipped, NULL, current_filename, sizeof(current_filename)-1, NULL, 0, NULL, 0);
    }
#endif

	// Package relationships : core properties
	string relFile = extractFile("_rels/.rels", "");
	filePrincipalRelationship.readFromString(relFile);
	vector<Relationship> pckRelset = filePrincipalRelationship.getAllRelationship();
	for (unsigned int i = 0; i < pckRelset.size(); i++)
	{
		if (pckRelset[i].getType().compare(CORE_PROP_REL_TYPE) == 0)
		{
			string corePropFile = extractFile(pckRelset[i].getTarget().c_str(), "");
			fileCoreProperties.readFromString(corePropFile);
		}
	}

	// Package relationships : extended core properties
	string extendedCpRelFilePath = extractFile("docProps/_rels/core.xml.rels", "");
	if (!extendedCpRelFilePath.empty())
	{
		FileRelationship extendedCpRelFile;
		extendedCpRelFile.readFromString(extendedCpRelFilePath);
		vector<Relationship> extendedCpRelSet = extendedCpRelFile.getAllRelationship();
		for (unsigned int i = 0; i < extendedCpRelSet.size(); i++)
		{			
			string extendedCorePropFile = extractFile(extendedCpRelSet[i].getTarget().c_str(), "");
			std::istringstream iss(extendedCorePropFile);

			std::string line;
			while (std::getline(iss, line))
			{
				if (line[0] == '\t') // To find a better condition
				{
					size_t start = line.find("<");
					size_t end = line.find(">");
					if (start != string::npos && end != string::npos)
					{
						size_t end2 = line.find("<", end + 1);
						if (end2 != string::npos)
						{
							extendedCoreProperties[line.substr(start+1, end - start - 1)] = line.substr(end+1, end2 - end - 1);
						}
					}
				}
			}
		}
	}

	// Package content type
	string contentTypeFile = extractFile("[Content_Types].xml", "");
	fileContentType.readFromString(contentTypeFile);
}

void Package::close()
{
	if (unzipped)
	{
		unzClose(unzipped);
		unzipped = NULL;
	}
}

const FileCoreProperties& Package::getFileCoreProperties() const
{
	return fileCoreProperties;
}

const FileContentType& Package::getFileContentType() const
{
	return fileContentType;
}

const FileRelationship& Package::getPrincipalRelationship() const
{
	return filePrincipalRelationship;
}

const Package::PartMap& Package::getAllFilePart() const
{
	return allFileParts;
}

const string& Package::getPathname() const
{
	return pathName;
}

void Package::setFileFileCoreProperties(const FileCoreProperties & pkgFileCP)
{
	fileCoreProperties = pkgFileCP;
}

void Package::addProperty(const CoreProperty::TypeProperty & pkgTypeProperty, const string & pkgPropertyValue)
{
	switch (pkgTypeProperty)
	{
	case CoreProperty::category:
		fileCoreProperties.setCategory(pkgPropertyValue);
		break;
	case CoreProperty::contentStatus:
		fileCoreProperties.setContentStatus(pkgPropertyValue);
		break;
	case CoreProperty::created:
		fileCoreProperties.setCreated(pkgPropertyValue);
		break;
	case CoreProperty::creator:
		fileCoreProperties.setCreator(pkgPropertyValue);
		break;
	case CoreProperty::description:
		fileCoreProperties.setDescription(pkgPropertyValue);
		break;
	case CoreProperty::identifier:
		fileCoreProperties.setIdentifier(pkgPropertyValue);
		break;
	case CoreProperty::keywords:
		fileCoreProperties.addKeywords(pkgPropertyValue);
		break;
	case CoreProperty::language:
		fileCoreProperties.setLanguage(pkgPropertyValue);
		break;
	case CoreProperty::lastModifiedBy:
		fileCoreProperties.setLastModifiedBy(pkgPropertyValue);
		break;
	case CoreProperty::lastPrinted:
		fileCoreProperties.setLastPrinted(pkgPropertyValue);
		break;
	case CoreProperty::modified:
		fileCoreProperties.setModified(pkgPropertyValue);
		break;
	case CoreProperty::revision:
		fileCoreProperties.setRevision(pkgPropertyValue);
		break;
	case CoreProperty::subject:
		fileCoreProperties.setSubject(pkgPropertyValue);
		break;
	case CoreProperty::title:
		fileCoreProperties.setTitle(pkgPropertyValue);
		break;
	case CoreProperty::version:
		fileCoreProperties.setVersion(pkgPropertyValue);
		break;
	}
}

void Package::setFileContentType(const FileContentType & pkgFileCT)
{
	fileContentType = pkgFileCT;
}

void Package::addContentType(const ContentType & contentType)
{
	fileContentType.addContentType(contentType);
};

void Package::setPrincipalRelationship(const FileRelationship & pkgFileRS)
{
	filePrincipalRelationship = pkgFileRS;
}

void Package::addRelationship(const Relationship & relationship)
{
	filePrincipalRelationship.addRelationship(relationship);
}

FilePart* Package::createPart(const std::string & inputContent, const std::string & outputPartPath)
{
	FilePart* fp = new FilePart(inputContent, outputPartPath);
	allFileParts[outputPartPath] = fp;
	return fp;
}

uLong buildTimeInfo(const char *filename, tm_zip *tmzip, uLong *dostime)
{
    int ret = 0;
#ifdef _WIN32
	FILETIME ftUtc;
    FILETIME ftLocal;
    HANDLE hFind;
    WIN32_FIND_DATAA ff32;

    hFind = FindFirstFileA(filename, &ff32);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dostime)+1,((LPWORD)dostime)+0);
        FindClose(hFind);
        ret = 1;
    }
	else
	{
		GetSystemTimeAsFileTime(&ftUtc);
        FileTimeToLocalFileTime(&ftUtc, &ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dostime)+1,((LPWORD)dostime)+0);
        FindClose(hFind);
        ret = 1;
	}
#else
#if defined unix || defined __APPLE__
    struct stat s = {0};
    struct tm* filedate;
    time_t tm_t = time(0);
    filedate = localtime(&tm_t);

    tmzip->tm_sec  = filedate->tm_sec;
    tmzip->tm_min  = filedate->tm_min;
    tmzip->tm_hour = filedate->tm_hour;
    tmzip->tm_mday = filedate->tm_mday;
    tmzip->tm_mon  = filedate->tm_mon ;
    tmzip->tm_year = filedate->tm_year;
#endif
#endif
    return ret;
}

void Package::writeStringIntoNewPart(const std::string &input, zipFile & zf, const std::string & partPath, bool useZip64)
{
	// Initialize the parameters for the creation of a file in the zip archive
	zip_fileinfo zi;
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour = zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;
	char* tmp = new char[partPath.length() + 1];
	strcpy(tmp, partPath.c_str());
	buildTimeInfo(tmp,&zi.tmz_date,&zi.dosDate);
	delete [] tmp;

	// Open the content type part in the zip archive
	int err = zipOpenNewFileInZip64(zf,partPath.c_str(),&zi,
		NULL,0,NULL,0,NULL /* comment*/,
		Z_DEFLATED,						// method
		Z_DEFAULT_COMPRESSION,				// level
		useZip64);								// Zip64
	if (err != ZIP_OK)
		cerr << "error in opening " << partPath << " in zipfile" << endl;

	// Write the content of the content type part
	err = zipWriteInFileInZip (zf,input.c_str(),input.size());
	if (err<0)
	{
		cerr << "error in writing " << partPath << " in the zipfile" << endl;
	}

	// Close the content type part
	err = zipCloseFileInZip(zf);
	if (err!=ZIP_OK)
		cerr << "error in closing " << partPath << " in the zipfile" << endl;
}


void Package::writePackage(bool useZip64) 
{
	// Create a zip archive
	zipFile zf = NULL;
	if (useZip64)
		zf = zipOpen64(pathName.c_str(), 0);
	else
		zf = zipOpen(pathName.c_str(), 0);

	fileCoreProperties.initDefaultCoreProperties();
	writeStringIntoNewPart(fileCoreProperties.toString(), zf, "docProps/core.xml", useZip64);
	if (!extendedCoreProperties.empty())
	{
		// XML def + namespaces def
		ostringstream oss;
		oss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << endl;
		oss << "<extendedCoreProperties xmlns=\"http://schemas.f2i-consulting.com/package/2014/metadata/extended-core-properties\"" << endl;
		oss << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << endl;

		// content
#if defined(_WIN32) || defined(__APPLE__)
		for (std::unordered_map< std::string, std::string >::iterator it = extendedCoreProperties.begin();  it != extendedCoreProperties.end(); ++it)
		{
			oss << "\t<" << it->first << ">" + it->second + "</" + it->first + ">" << endl;
		}
#else
		for (tr1::unordered_map< std::string, std::string >::iterator it = extendedCoreProperties.begin();  it != extendedCoreProperties.end(); ++it)
		{
			oss << "\t<" << it->first << ">" + it->second + "</" + it->first + ">" << endl;
		}
#endif

		// end tag
		oss << "</extendedCoreProperties>" << endl;
		
		writeStringIntoNewPart(oss.str(), zf, "docProps/extendedCore.xml", useZip64);
		
		// Add the content type for extended core properties part
		ContentType contentTypeExtendedCoreProp(false, "application/x-extended-core-properties+xml", "docProps/extendedCore.xml");
		addContentType(contentTypeExtendedCoreProp);
		
		// Relationhsip with the standard core properties part
		Relationship relToExtCoreProp("docProps/extendedCore.xml", EXTENDED_CORE_PROP_REL_TYPE, "ExtendedCoreProperties");
		FileRelationship fileExtCorePropRep(relToExtCoreProp);
		fileExtCorePropRep.setPathName("docProps/_rels/core.xml.rels");
		writeStringIntoNewPart(fileExtCorePropRep.toString(), zf, fileExtCorePropRep.getPathName(), useZip64);
	}

	writeStringIntoNewPart(fileContentType.toString(), zf, "[Content_Types].xml", useZip64);
	
	// write Principal Relationships file.
	if (!filePrincipalRelationship.isEmpty())
		writeStringIntoNewPart(filePrincipalRelationship.toString(), zf, "_rels/.rels", useZip64);
	
	// Write all the parts and their relationships
	for (PartMap::iterator i=allFileParts.begin(); i!=allFileParts.end(); i++){
        FilePart* part = i->second;
		// write Part file.
		writeStringIntoNewPart(part->getContent(), zf, part->getFinalPathName(), useZip64);

		if (!part->getFileRelationship().isEmpty())
		{
			writeStringIntoNewPart(part->getFileRelationship().toString(), zf, part->getFileRelationship().getPathName(), useZip64);
		}
	}

	// Close the zip archive
	int err = zipClose(zf,NULL, useZip64);
	if (err != ZIP_OK)
		cerr << "error in closing " << pathName.substr(0, pathName.size() - 4).c_str() << endl;
}

string do_extract_currentfile(unzFile uf,
    const char* password)
{
    int err=UNZ_OK;
    void* buf;
    uInt size_buf;

    size_buf = WRITEBUFFERSIZE;
    buf = (void*)malloc(size_buf);
    if (buf==NULL)
    {
        printf("Error allocating memory\n");
        return "";
    }

    err = unzOpenCurrentFilePassword(uf,password);
    if (err!=UNZ_OK)
    {
        printf("error %d with zipfile in unzOpenCurrentFilePassword\n",err);
    }

	ostringstream oss;
    do
    {
        err = unzReadCurrentFile(uf,buf,size_buf);
        if (err<0)
        {
            printf("error %d with zipfile in unzReadCurrentFile\n",err);
            break;
        }
		if (err>0)
		{
			oss.write((char*)buf, err);
		}
    }
    while (err>0);

    if (err==UNZ_OK)
    {
        err = unzCloseCurrentFile (uf);
        if (err!=UNZ_OK)
        {
            printf("error %d with zipfile in unzCloseCurrentFile\n",err);
        }
    }
    else
        unzCloseCurrentFile(uf); /* don't lose the error */

    free(buf);
    return oss.str();
}

string Package::extractFile(const string & filename, const string & password)
{
	if (unzipped == NULL)
		return "";

#ifdef CACHE_FILE_DESCRIPTOR
#if defined(_WIN32) || defined(__APPLE__)
	std::unordered_map< std::string, unz64_s >::const_iterator it = name2file.find(filename.c_str());
#else
	std::tr1::unordered_map< std::string, unz64_s >::const_iterator it = name2file.find(filename.c_str());
#endif
	if(it==name2file.end()){
		if (unzLocateFile(unzipped,filename.c_str(),CASESENSITIVITY) != UNZ_OK)
		{
			return "";
		}
		name2file[filename.c_str()]=*(unz64_s*)unzipped;
	}else{
		*(unz64_s*)unzipped = it->second;
	}
#else
	if (unzLocateFile(unzipped,filename.c_str(),CASESENSITIVITY) != UNZ_OK)
    {
        return "";
    }
#endif

	if (!password.empty())
		return do_extract_currentfile(unzipped, password.c_str());
	else
		return do_extract_currentfile(unzipped, NULL);
}

