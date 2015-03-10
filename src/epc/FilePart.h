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
#ifndef EPC_FILEPART
#define EPC_FILEPART

#include "FileRelationship.h"

namespace epc
{

	class FilePart
	{
	private:
		std::string content;				/// The content of the file to write
		std::string finalPathName;			/// The path of the part in the package.
		FileRelationship fileRelationship;	/// The associated rel file to the part

	public:
		/**
		* Constructor
		* @param inputContent		The content which will be included into a part of the package
		* @param outputPartPath		The path of the part within the package.
		*/
		FilePart(const std::string & inputContent, const std::string & outputPartPath);
		~FilePart() {}

		// ACCESSORS
		std::string getContent() const;
		std::string getFinalPathName() const;
		FileRelationship getFileRelationship() const;
		Relationship getIndexRelationship(const int & index) const;

		void setContent(const std::string & inputContent);
		void setFinalPathName(const std::string & finalPath);

		/**
		* Copy an existing relationship into the relationship set of the part.
		*/
		void addRelationship(const Relationship & relationship);

		/**
		* Creates a new relationship into the relationship set of the part according to the supplied parameters
		*/
		void createRelationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, const bool & internalTarget = true);
	};
}

#endif

