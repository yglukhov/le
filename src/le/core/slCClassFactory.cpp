#include <set>
#include <algorithm>

#include "slCClassFactory.h"

namespace sokira
{
	namespace le
	{

typedef std::set<IClassImpl*> CClassSet;
static inline CClassSet& classSet()
{
	static CClassSet theSet;
	return theSet;
}

IClassImpl::IClassImpl(const char* typeName) :
	mName(typeName)
{
	LE_ENTER_LOG_SILENT;
	LE_IF_LOG(log << "Registerinng class \"" << mName << "\"." << std::endl);
	classSet().insert(this);
}

bool CClassFactory::isClassRegistered(const CBasicString& className)
{
	return (_classWithName(className) != NULL);
}

struct SByNameFinder
{
	SByNameFinder(const char* name) :
		mName(name)
	{

	}

	bool operator()(IClassImpl* impl)
	{
		return !strcmp(impl->mName, mName);
	}

	const char* mName;
};

struct SByStdNameFinder
{
	SByStdNameFinder(const char* name) :
		mName(name)
	{

	}

	bool operator()(IClassImpl* impl)
	{
		return !strcmp(impl->stdName(), mName);
	}

	const char* mName;
};


IClassImpl* CClassFactory::_classWithName(const CBasicString& name)
{
	CClassSet::iterator end = classSet().end();
	CClassSet::iterator it = std::find_if(classSet().begin(), end, SByNameFinder(name.cString()));
	if (it != classSet().end())
		return *it;
	return NULL;
}

IClassImpl* CClassFactory::_classWithStdName(const char* name)
{
	CClassSet::iterator end = classSet().end();
	CClassSet::iterator it = std::find_if(classSet().begin(), end, SByStdNameFinder(name));
	if (it != classSet().end())
		return *it;
	return NULL;
}

	} // namespace le
} // namespace sokira
