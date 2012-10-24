#include <cstring>
#include "slCClass.h"


namespace sokira
{
	namespace le
	{

// IClassImpl::IClassImpl(const char* typeName); - implemented in slCClassFactory.cpp

static inline base::IClassImpl* stubClassImpl()
{
	class CStubClassImpl : public base::IClassImpl
	{
		public:
			CStubClassImpl() : base::IClassImpl("(null)") {}

			virtual void* create(const std::type_info&) const
			{
				return NULL;
			}

			virtual const std::type_info& stdType() const
			{
				return typeid(NULL);
			}

			virtual bool isChildOfStdClass(const std::type_info&) const
			{
				return false;
			}

			virtual std::vector<CClass> parents() const
			{
				return std::vector<CClass>();
			}

			virtual Float32 priorityForParameters(const CDictionary& params) const
			{
				return 0;
			}
	};

	static CStubClassImpl stub;
	return &stub;
}


CClass::CClass(base::IClassImpl* impl) :
	mImpl((impl)?(impl):(stubClassImpl()))
{

}

CBasicString CClass::name() const
{
	return CBasicString::__CStringWithLiteral(mImpl->mName);
}

bool CClass::operator == (const CClass rhs)
{
	return !std::strcmp(mImpl->mName, rhs.mImpl->mName);
}

std::vector<CClass> CClass::parents() const
{
	return mImpl->parents();
}

std::set<ISelector*> CClass::selectors() const
{
	std::set<ISelector*> result = mImpl->mSelectors;
	std::vector<CClass> theParents = parents();
	for (std::vector<CClass>::iterator it = theParents.begin(); it != theParents.end(); ++it)
	{
		std::set<ISelector*> tmp = it->selectors();
		result.insert(tmp.begin(), tmp.end());
	}
	return result;
}

std::set<ISelector*> CClass::ownSelectors() const
{
	return mImpl->mSelectors;
}

Bool CClass::instanceRespondsToSelector(const CBasicString& name) const
{
	return !!selectorWithName(name);
}

ISelector* CClass::selectorWithName(const CBasicString& name) const
{
	std::set<ISelector*> allSelectors = selectors();

	for (std::set<ISelector*>::iterator it = allSelectors.begin(); it != allSelectors.end(); ++it)
	{
		if (name == (*it)->name())
		{
			return *it;
		}
	}

	return NULL;
}


	} // namespace le
} // namespace sokira
