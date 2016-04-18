%{
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping

#include "resqml2/ActivityTemplate.h"

%}
typedef long long					LONG64;

#ifdef SWIGJAVA
typedef long long					ULONG64; // We don't want o use BigInteger in java.
#else
typedef unsigned long long	ULONG64;
#endif

typedef long long 				time_t;


//************************
// STD::VECTOR DEFINITIONS
//************************

namespace resqml2 {
	class Activity;
}

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
%include "std_vector.i"
namespace std {
   %template(ActivityVector) vector<resqml2::Activity*>;
}

#ifdef SWIGPYTHON
namespace resqml2
{
	%typemap(out) AbstractObject* {
		// Check potential downcasting
		swig_type_info * const outtype = SWIG_TypeQuery(("resqml2::" + result->getXmlTag() + " *").c_str());
		resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), outtype, 0);
	}
}
#endif
#ifdef SWIGJAVA
	%include "swigResqml2JavaInclude.i"
#endif
#ifdef SWIGCSHARP
	%include "swigResqml2CsInclude.i"
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace resqml2::AbstractObject;
	%nspace resqml2::AbstractFeature;
	%nspace resqml2::Activity;
	%nspace resqml2::ActivityTemplate;
#endif

namespace resqml2_0_1
{
	class AbstractFeatureInterpretation;
}

namespace resqml2
{
	%nodefaultctor; // Disable creation of default constructors
		
	class Activity;
#ifdef SWIGPYTHON
	%rename(Resqml2AbstractObject) AbstractObject;
#endif
	class AbstractObject
	{
	public:
		common::EpcDocument* getEpcDocument() const;
	
		bool isPartial() const;
	
		std::string getUuid() const;
		std::string getTitle() const;
		std::string getEditor() const;
		time_t getCreation() const;
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;
		
		void setMetadata(const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);
		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);
				
		std::string getXmlTag() const;
		
		void addAlias(const std::string & authority, const std::string & title);
		unsigned int getAliasCount() const;
		std::string getAliasAuthorityAtIndex(const unsigned int & index) const;
		std::string getAliasTitleAtIndex(const unsigned int & index) const;
		
		void addOrSetExtraMetadata(const std::string & key, const std::string & value);
		std::string getExtraMetadata(const std::string & key);
		
		unsigned int getExtraMetadataCount() const;
		std::string getExtraMetadataKeyAtIndex(const unsigned int & index) const;
		std::string getExtraMetadataStringValueAtIndex(const unsigned int & index) const;
		
		const std::vector<resqml2::Activity*> & getActivitySet() const;
	};
	
	//************************************
	//************ Activity **************
	//************************************

	class ActivityTemplate : public AbstractObject
	{
	public:
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType);
		bool isAnExistingParameter(const std::string & paramTitle) const;
		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(const unsigned int & index) const;
		const bool & getParameterIsInput(const unsigned int & index) const;
		const bool & getParameterIsInput(const std::string & paramTitle) const;
		const bool & getParameterIsOutput(const unsigned int & index) const;
		const bool & getParameterIsOutput(const std::string & paramTitle) const;
		const LONG64 getParameterMinOccurences(const unsigned int & index) const;
		const LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		const LONG64 getParameterMaxOccurences(const unsigned int & index) const;
		const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;
	};

	class Activity : public AbstractObject
	{
	public:
		void pushBackParameter(const std::string title,
			const std::string & value);
		void pushBackParameter(const std::string title,
			const LONG64 & value);
		void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(const unsigned int & index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(const unsigned int & index) const;
		double getFloatingPointQuantityParameterValue(const unsigned int & index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(const unsigned int & index) const;
		LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(const unsigned int & index) const;
		const std::string & getStringParameterValue(const unsigned int & index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		bool isAResqmlObjectParameter(const unsigned int & index) const;
		AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const;

		void setActivityTemplate(ActivityTemplate* activityTemplate);
		ActivityTemplate* getActivityTemplate() const;
	};
	
	//************************************
	//************ FEATURE ***************
	//************************************

	class AbstractFeature : public AbstractObject
	{
	public:
		unsigned int getInterpretationCount() const;
		resqml2_0_1::AbstractFeatureInterpretation* getInterpretation(const unsigned int & index) const;
	};
}
