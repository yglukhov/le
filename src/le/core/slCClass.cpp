#include <cstring>
#include "slCClass.h"


namespace sokira
{
	namespace le
	{

// IClassImpl::IClassImpl(const char* typeName); - implemented in slCClassFactory.cpp

static inline IClassImpl* stubClassImpl()
{
	class CStubClassImpl : public IClassImpl
	{
		public:
			CStubClassImpl() : IClassImpl("(null)") {}

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
	};

	static CStubClassImpl stub;
	return &stub;
}


CClass::CClass(IClassImpl* impl) :
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

	} // namespace le
} // namespace sokira
