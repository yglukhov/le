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
	SByNameFinder(const CBasicString& name) :
		mName(name)
	{

	}

	bool operator()(IClassImpl* impl) const
	{
		return (mName == impl->mName);
	}

	virtual bool match(IClassImpl* impl) const
	{
		return operator()(impl);
	}

	CBasicString mName;
};

struct SByStdNameFinder
{
	SByStdNameFinder(const char* name) :
		mName(name)
	{

	}

	bool operator()(IClassImpl* impl) const
	{
		return _le_stdNamesEqual(impl->stdName(), mName);
	}

	virtual bool match(IClassImpl* impl) const
	{
		return operator()(impl);
	}

	const char* mName;
};


IClassImpl* CClassFactory::_classWithName(const CBasicString& name)
{
	CClassSet::iterator end = classSet().end();
	CClassSet::iterator it = std::find_if(classSet().begin(), end, SByNameFinder(name));
	if (it != classSet().end())
		return *it;
	return NULL;
}

IClassImpl* _classWithStdName(const char* name)
{
	CClassSet::iterator end = classSet().end();
	CClassSet::iterator it = std::find_if(classSet().begin(), end, SByStdNameFinder(name));
	if (it != end)
		return *it;
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Iterators

struct SByParentFinder : public CClassFactory::iterator::IPredicate
{
	SByParentFinder(const char* stdName) :
		mName(stdName)
	{

	}

	virtual bool match(IClassImpl* impl) const
	{
		return impl->isChildOfStdNamedClass(mName);
	}

	const char* mName;
};


CClassFactory::iterator CClassFactory::begin()
{
	return iterator(classSet().begin(), classSet().begin(), classSet().end(), new iterator::IPredicate());
}

CClassFactory::iterator CClassFactory::beginForChildsOf(const CBasicString& name)
{
	return iterator(classSet().begin(), classSet().begin(), classSet().end(), new SByParentFinder(_classWithName(name)->stdName()));
}

CClassFactory::iterator CClassFactory::_beginForChildsOfStd(const char* name)
{
	return iterator(classSet().begin(), classSet().begin(), classSet().end(), new SByParentFinder(name));
}

CClassFactory::iterator CClassFactory::end()
{
	return iterator(classSet().end(), classSet().begin(), classSet().end(), new iterator::IPredicate());
}

	} // namespace le
} // namespace sokira
