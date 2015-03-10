/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014) 

philippe.verney@f2i-consulting.com

Ce logiciel est un programme informatique servant à accéder aux données formatées à l'aide des standards Energistics. 

Ce logiciel est régi par la licence CeCILL-B soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffusée par le CEA, le CNRS et l'INRIA 
sur le site http://www.cecill.info.

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant 
donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 

Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
termes.
-----------------------------------------------------------------------*/
#include "FileRelationship.h"

#include <sstream>

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!

FileRelationship::FileRelationship()
{
}

FileRelationship::FileRelationship(const Relationship & frRelationship)
{
	pathName = "_rels\\.rels";
	relationship.push_back(frRelationship);
}

FileRelationship::FileRelationship(const vector<Relationship> & frRelationship):
	relationship(frRelationship)
{
	pathName = "_rels\\.rels";
}

bool FileRelationship::isEmpty() const
{
	return relationship.empty();
}

string FileRelationship::getPathName() const
{
	return pathName;
}

vector<Relationship> FileRelationship::getAllRelationship() const
{
	return relationship;
}

Relationship FileRelationship::getIndexRelationship(const int & index) const
{
	return relationship[index];
}

string FileRelationship::toString() const
{
	ostringstream oss;
	if (!isEmpty())
	{
		// XML def + namespaces def
		oss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << endl << "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">" << endl;

		// parcourir le vector...
		int numRelationship = relationship.size();
		for (int i = 0; i < numRelationship; i++)
		{
			oss << "\t" << relationship[i].toString() << endl;
		}

		// end tag
		oss << "</Relationships>" << endl;
	}
	return oss.str();
}

void FileRelationship::setPathName(const std::string & frPathName)
{
	pathName = frPathName;
}

void FileRelationship::addRelationship(const Relationship & frRelationship)
{
	relationship.push_back(frRelationship);
}

void FileRelationship::readFromString(const string & textInput)
{
	relationship.clear();

	size_t pos = textInput.find("<Relationship ");
	while (pos != string::npos)
	{
		size_t end = textInput.find("/>", pos);
		if (end == string::npos)
			end = textInput.find("</Relationship>", pos);
		
		//ID
		string id = "";
		size_t attStart = textInput.find("Id=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 4;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				id = textInput.substr(attStart, attEnd - attStart);
		}

		//type
		string type = "";
		attStart = textInput.find("Type=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 6;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				type = textInput.substr(attStart, attEnd - attStart);
		}

		//Target
		string target = "";
		attStart = textInput.find("Target=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 8;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				target = textInput.substr(attStart, attEnd - attStart);
		}

		//TargetMode
		bool internalTarget = true;
		attStart = textInput.find("TargetMode=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 12;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
			{
				string readString = textInput.substr(attStart, attEnd - attStart);
				if (readString.compare("External") == 0)
					internalTarget = false;
			}
		}

		Relationship rel(target, type, id, internalTarget);
		addRelationship(rel);

		pos = textInput.find("<Relationship ", pos + 14);
	}
}

