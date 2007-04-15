#include <iostream>
#include <cstring>
#include "slCBasicString.h"
#include <le/core/debug/slAssert.h>
#include <le/core/config/slCompiler.h>
#include <le/core/slCDictionary.h>

namespace sokira
{
	namespace le
	{

#if defined(LE_COMPILER_IS_MSVC) && LE_COMPILER_VERSION >= 1400 // MSVS 2005 and higher
#pragma warning (push)
#pragma warning( disable : 4996 )
#endif // MSVS 2005 or higher

static inline void slStrCpy(Char* dest, const Char* src)
{
	using namespace std;
	strcpy(dest, src);
}

static inline void slStrCat(Char* dest, const Char* src)
{
	using namespace std;
	strcat(dest, src);
}

#if defined(LE_COMPILER_IS_MSVC) && LE_COMPILER_VERSION >= 1400 // MSVS 2005 and higher
#pragma warning (pop)
#endif // MSVS 2005 or higher

////////////////////////////////////////////////////////////////////////////////
// String proxy implementation
////////////////////////////////////////////////////////////////////////////////
#define LE_SET_BIT(x) (1 << (x))

enum EOwnPolicy
{
	eOwnPolicyCopy = LE_SET_BIT(0),
	eOwnPolicyDealloc = LE_SET_BIT(1),
	eOwnPolicyDefault = eOwnPolicyCopy | eOwnPolicyDealloc,
	eOwnPolicyLiteral = 0
};


struct CBasicString::SStringProxy
{
	inline SStringProxy(const Char* string, EOwnPolicy ownPolicy = eOwnPolicyDefault) :
		mOwnPolicy(ownPolicy),
		mRefCount(1),
		mString((ownPolicy & eOwnPolicyCopy)?(new Char[std::strlen(string) + 1]):(NULL))
	{
		if (mString)
		{
			slStrCpy(mString, string);
		}
		else
		{
			mString = const_cast<Char*>(string);
		}
	}

	inline SStringProxy(const Char* cString1, const Char* cString2) :
		mOwnPolicy(eOwnPolicyDefault),
		mRefCount(1)
	{
		size_t str1len = (cString1)?(std::strlen(cString1)):(0);
		size_t str2len = (cString1)?(std::strlen(cString2)):(0);

		mString = new Char[str1len + str2len + 1];

		if (str1len)
		{
			slStrCpy(mString, cString1);
			if (str2len)
			{
				slStrCat(mString, cString2);
			}
		}
		else
		{
			slStrCpy(mString, cString2);
		}
	}


	inline SStringProxy* retain()
	{
		++mRefCount;
		return this;
	}

	void release()
	{
		--mRefCount;
		if (!mRefCount)
		{
			if (mOwnPolicy & eOwnPolicyDealloc)
			{
				delete [] mString;
			}
			delete this;
		}
	}

	inline UInt32 length() const
	{
		return static_cast<UInt32>(std::strlen(mString));
	}

	inline Bool isEmpty() const
	{
		return !(*mString);
	}

	static inline SStringProxy* emptyStringProxy()
	{
		static SStringProxy proxy("", eOwnPolicyLiteral);
		return &proxy;
	}

	EOwnPolicy mOwnPolicy;
	UInt32 mRefCount;
	Char* mString;
};


static inline Bool notEmpty(const Char* string)
{
	return (string)?(*string):(false);
}

////////////////////////////////////////////////////////////////////////////////
// CBasicString implementation
////////////////////////////////////////////////////////////////////////////////
CBasicString::CBasicString() :
	mProxy(SStringProxy::emptyStringProxy()->retain())
{

}

CBasicString::CBasicString(const CBasicString& copy) :
	mProxy(copy.mProxy->retain())
{

}

CBasicString::CBasicString(const Char* cString) :
	mProxy((notEmpty(cString))?(new SStringProxy(cString)):(SStringProxy::emptyStringProxy()->retain()))
{

}

CBasicString::CBasicString(const Char* cString, EStringEncoding /*encoding*/) :
	mProxy((notEmpty(cString))?(new SStringProxy(cString)):(SStringProxy::emptyStringProxy()->retain()))
{

}

CBasicString::CBasicString(const WChar* /*uniString*/, UInt32 /*length*/, EStringEncoding /*encoding*/) :
	mProxy(new SStringProxy("This string was generated from uniString. Complete the constructor!", eOwnPolicyLiteral))
{
	// TODO: complete
}

CBasicString::CBasicString(const Char* cString1, const Char* cString2) :
	mProxy((notEmpty(cString1) || notEmpty(cString2))?(new SStringProxy(cString1, cString2)):(SStringProxy::emptyStringProxy()->retain()))
{

}

CBasicString::CBasicString(SStringProxy* proxy) :
	mProxy(proxy)
{

}

CBasicString CBasicString::__CStringWithLiteral(const Char* str)
{
	return CBasicString((notEmpty(str))?(new SStringProxy(str, eOwnPolicyLiteral)):(SStringProxy::emptyStringProxy()->retain()));
}

CBasicString::~CBasicString()
{
	mProxy->release();
}

const CBasicString& CBasicString::operator = (const Char* cString)
{
	if (mProxy->mString != cString)
	{
		mProxy->release();
		mProxy = (notEmpty(cString))?(new SStringProxy(cString)):(SStringProxy::emptyStringProxy()->retain());
	}

	return *this;
}

const CBasicString& CBasicString::operator = (const CBasicString& copy)
{
	if (mProxy->mString != copy.mProxy->mString)
	{
		mProxy->release();
		mProxy = copy.mProxy->retain();
	}

	return *this;
}

SInt32 CBasicString::compare(const Char* cString) const
{
	return strcmp(mProxy->mString, cString);
}

SInt32 CBasicString::compare(const CBasicString& string) const
{
	return strcmp(mProxy->mString, string.mProxy->mString);
}

Bool CBasicString::operator == (const Char* cString) const
{
	return !compare(cString);
}

Bool CBasicString::operator == (const CBasicString& string) const
{
	return !compare(string);
}

Bool CBasicString::operator != (const Char* cString) const
{
	return compare(cString);
}

Bool CBasicString::operator != (const CBasicString& string) const
{
	return compare(string);
}


Bool CBasicString::operator < (const Char* cString) const
{
	return (compare(cString) < 0);
}

Bool CBasicString::operator < (const CBasicString& string) const
{
	return (compare(string) < 0);
}


Bool CBasicString::operator > (const Char* cString) const
{
	return (compare(cString) > 0);
}

Bool CBasicString::operator > (const CBasicString& string) const
{
	return (compare(string) > 0);
}


Bool CBasicString::operator <= (const Char* cString) const
{
	return (compare(cString) <= 0);
}

Bool CBasicString::operator <= (const CBasicString& string) const
{
	return (compare(string) <= 0);
}


Bool CBasicString::operator >= (const Char* cString) const
{
	return (compare(cString) >= 0);
}

Bool CBasicString::operator >= (const CBasicString& string) const
{
	return (compare(string) >= 0);
}



void CBasicString::append(const Char* cString, EStringEncoding /* encoding*/)
{
	if (!notEmpty(cString))
		return;

	SStringProxy* newProxy = new SStringProxy(mProxy->mString, cString);
	mProxy->release();
	mProxy = newProxy;
}

void CBasicString::append(const WChar* /*uniString*/, UInt32 /*length*/,
				EStringEncoding /*encoding*/)
{
	// TODO: complete
	mProxy->release();
	mProxy = new SStringProxy("This string was generated from uniString. Complete the append() method!", eOwnPolicyLiteral);
}

void CBasicString::append(const CBasicString& string)
{
	append(string.cString());
}

void CBasicString::clear()
{
	mProxy->release();
	mProxy = SStringProxy::emptyStringProxy()->retain();
}

// Erase characters from string. If toPos is equal to 0, then the
// characters are erased to the end of the string.
void CBasicString::erase(UInt32 /*fromPos*/, UInt32 /*toPos*/)
{
	// TODO: complete
}


UInt32 CBasicString::length() const
{
	return mProxy->length();
}

bool CBasicString::isEmpty() const
{
	return mProxy->isEmpty();
}

EStringEncoding CBasicString::encoding() const
{
	return eEncodingDefault;
}


const Char* CBasicString::cString(EStringEncoding encoding) const
{
	return mProxy->mString;
}


std::ostream& operator << (std::ostream& stream, const CBasicString& string)
{
	return (stream << (string.cString()));
}

	} // namespace le
} // namespace sokira

////////////////////////////////////////////////////////////////////////////////
// CString runtime class implementation
////////////////////////////////////////////////////////////////////////////////
#include <le/core/slCString.h>

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CString);

CString::CString(const CDictionary& fromDictionary) :
	CBasicString(fromDictionary.rootValue())
{

}

void CString::serialize(CDictionary& toDictionary) const
{
	toDictionary.rootValue(*this);
}

void CString::deserialize(const CDictionary& fromDictionary)
{
	CString::operator=(fromDictionary.rootValue());
}

	} // namespace le
} // namespace sokira
