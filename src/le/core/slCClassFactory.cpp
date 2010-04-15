#include <set>
#include <algorithm>

#include "slCClassFactory.h"

namespace sokira
{
	namespace le
	{

base::IClassImpl::IClassImpl(const char* typeName) :
	mName(typeName)
{
	LE_ENTER_LOG_SILENT;
	LE_IF_LOG(log << "Registering class \"" << mName << "\"." << std::endl);
	CClassFactory::defaultInstance()->registerClass(this);
}

void CClassFactory::registerClass(base::IClassImpl* theClass)
{
	mClassSet.insert(theClass);
}

CClassFactory *CClassFactory::defaultInstance()
{
	static CClassFactory factory;
	return &factory;
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

	bool operator()(base::IClassImpl* impl) const
	{
		return (mName == impl->mName);
	}

	CBasicString mName;
};

base::IClassImpl* CClassFactory::_classWithName(const CBasicString& name)
{
	CClassSet::iterator end = mClassSet.end();
	CClassSet::iterator it = std::find_if(mClassSet.begin(), end, SByNameFinder(name));
	if (it != end)
		return *it;
	return NULL;
}


////////////////////////////////////////////////////////////////////////////////
// Iterators

struct SByParentFinder : public CClassFactory::iterator::IPredicate
{
	SByParentFinder(const std::type_info& stdType) :
		mType(stdType)
	{

	}

	virtual bool operator () (base::IClassImpl* impl) const
	{
		return impl->isChildOfStdClass(mType);
	}

	const std::type_info& mType;
};


CClassFactory::iterator CClassFactory::begin()
{
	return iterator(mClassSet.begin(), mClassSet.begin(), mClassSet.end(), new iterator::IPredicate());
}

CClassFactory::iterator CClassFactory::beginForChildsOf(const CBasicString& name)
{
	return iterator(mClassSet.begin(), mClassSet.begin(), mClassSet.end(), new SByParentFinder(_classWithName(name)->stdType()));
}

CClassFactory::iterator CClassFactory::_beginForChildsOfStd(const std::type_info& type)
{
	return iterator(mClassSet.begin(), mClassSet.begin(), mClassSet.end(), new SByParentFinder(type));
}

CClassFactory::iterator CClassFactory::end()
{
	return iterator(mClassSet.end(), mClassSet.begin(), mClassSet.end(), new iterator::IPredicate());
}

	} // namespace le
} // namespace sokira
