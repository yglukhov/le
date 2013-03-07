#include <set>
#include <algorithm>

#include "slCClassFactory.h"

namespace sokira
{
	namespace le
	{

base::IClassImpl::IClassImpl(const CBasicString& typeName) :
	mName(typeName)
{
	LE_ENTER_LOG_SILENT;
//	LE_IF_LOG(log << "Registering class \"" << mName << "\"." << std::endl);
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

bool CClassFactory::isClassRegistered(const CBasicString& className) const
{
	return (_classWithName(className) != NULL);
}

CClass CClassFactory::bestSubclassOfClassWithParameters(const CClass& superclass, const CDictionary& parameters) const
{
	CClassSet::iterator end = mClassSet.end();
	
	CClass bestClass = superclass;
	Float32 bestPriority = bestClass.priorityForParameters(parameters);

	for (CClassSet::iterator it = mClassSet.begin(); it != end; ++it)
	{
		CClass curClass(*it);
		if (curClass.isChildOfClass(superclass))
		{
			Float32 priority = curClass.priorityForParameters(parameters);
			if (priority > bestPriority || bestClass == superclass)
			{
				bestPriority = priority;
				bestClass = curClass;
			}
		}
	}

	return bestClass;
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

base::IClassImpl* CClassFactory::_classWithName(const CBasicString& name) const
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
