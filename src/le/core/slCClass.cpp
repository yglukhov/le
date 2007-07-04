#include <cstring>
#include "slCClass.h"


namespace sokira
{
	namespace le
	{

// IClassImpl::IClassImpl(const char* typeName); - implemented in slCClassFactory.cpp

static inline IClassImpl* stubClassImpl()
{
	struct CStubClassImpl : public IClassImpl
	{
		CStubClassImpl() : IClassImpl("(null)") {}

		virtual void* create(const char* typeName) const
		{
			return NULL;
		}

		virtual const char* stdName() const
		{
			return "(null)";
		}
		
		virtual bool isChildOfStdNamedClass(const char*)
		{
			return false;
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

	} // namespace le
} // namespace sokira
