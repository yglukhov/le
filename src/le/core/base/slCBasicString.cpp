#include <iostream>
#include <cstring>
//#include <stdarg.h>
//#include <stdio.h>

#include "slCBasicString.h"
#include <le/core/debug/slAssert.h>
#include <le/core/config/slCompiler.h>
#include <le/core/slCDictionary.h>

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
#include "vasprintf.cp"
#endif

namespace sokira
{
	namespace le
	{

/*
typedef UInt64 TCharType;

typedef TCharType (*TEncodeFunc)(TCharType);
typedef UInt32 (*TReadBufFunc)(const UInt8 *, UInt32, TCharType&);

static inline UInt32 readASCIIChar(const UInt8 *buffer, UInt32, TCharType& readChar)
{
	readChar = *buffer;
	return 1;
}

typedef std::map<EStringEncoding, std::pair<TEncodeFunc, bool> > SubEncodingInfo;
typedef std::pair<TReadBufFunc, SubEncodingInfo> EncodingInfo;

struct _StringEncoding
{
	std::list<std::pair<EStringEncoding, bool> > acceptedEncodings() const;
};

*/

#if defined(LE_COMPILER_IS_MSVC) && LE_COMPILER_VERSION >= 1400 // MSVS 2005 and higher
#pragma warning (push)
#pragma warning( disable : 4996 )
#endif // MSVS 2005 or higher

static inline void slStrCpy(NChar* dest, const NChar* src)
{
	using namespace std;
	strcpy(dest, src);
}

static inline void slStrCat(NChar* dest, const NChar* src)
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

enum EOwnPolicy
{
	eOwnPolicyCopy = LE_SET_BIT(0),
	eOwnPolicyDealloc = LE_SET_BIT(1),
	eOwnPolicyDeallocWithFree = LE_SET_BIT(2), // If set the dealloc will use free() otherwise delete[]
	eOwnPolicyDefault = eOwnPolicyCopy | eOwnPolicyDealloc,
	eOwnPolicyLiteral = 0
};


struct CBasicString::SStringProxy
{
	inline SStringProxy(const NChar* string, EOwnPolicy ownPolicy = eOwnPolicyDefault, UInt32 length = 0) :
		mOwnPolicy(ownPolicy),
		mRefCount(1),
		mString((ownPolicy & eOwnPolicyCopy)?(new NChar[(length)?(length):(std::strlen(string)) + 1]):(NULL))
	{
		if (mString)
		{
			if (length)
			{
				memcpy(mString, string, length);
				mString[length] = 0;
			}
			else
			{
				slStrCpy(mString, string);
			}
		}
		else
		{
			mString = const_cast<NChar*>(string);
		}
	}

	inline SStringProxy(const NChar* cString1, const NChar* cString2) :
		mOwnPolicy(eOwnPolicyDefault),
		mRefCount(1)
	{
		size_t str1len = (cString1)?(std::strlen(cString1)):(0);
		size_t str2len = (cString1)?(std::strlen(cString2)):(0);

		mString = new NChar[str1len + str2len + 1];

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
				if (mOwnPolicy & eOwnPolicyDeallocWithFree)
				{
					free(mString);
				}
				else
				{
					delete [] mString;
				}
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
	NChar* mString;
};


static inline Bool notEmpty(const NChar* string)
{
	return string && *string;
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

CBasicString::CBasicString(const NChar* cString) :
	mProxy((notEmpty(cString))?(new SStringProxy(cString)):(SStringProxy::emptyStringProxy()->retain()))
{

}

CBasicString::CBasicString(const NChar* cString, EStringEncoding /*encoding*/) :
	mProxy((notEmpty(cString))?(new SStringProxy(cString)):(SStringProxy::emptyStringProxy()->retain()))
{

}

CBasicString::CBasicString(const WChar* /*uniString*/, UInt32 /*length*/, EStringEncoding /*encoding*/) :
	mProxy(new SStringProxy("This string was generated from uniString. Complete the constructor!", eOwnPolicyLiteral))
{
	// TODO: complete
}

CBasicString::CBasicString(const NChar* cString1, const NChar* cString2) :
	mProxy((notEmpty(cString1) || notEmpty(cString2))?(new SStringProxy(cString1, cString2)):(SStringProxy::emptyStringProxy()->retain()))
{

}

CBasicString::CBasicString(SStringProxy* proxy) :
	mProxy(proxy)
{

}

CBasicString CBasicString::__CStringWithLiteral(const NChar* str)
{
	return CBasicString((notEmpty(str))?(new SStringProxy(str, eOwnPolicyLiteral)):(SStringProxy::emptyStringProxy()->retain()));
}

CBasicString CBasicString::__CStringNoCopyDeallocWithFree(const NChar* str)
{
	return CBasicString((notEmpty(str))?(new SStringProxy(str, (EOwnPolicy)(eOwnPolicyDealloc | eOwnPolicyDeallocWithFree))):(SStringProxy::emptyStringProxy()->retain()));
}

CBasicString CBasicString::__CStringNoCopyDeallocWithDelete(const NChar* str)
{
	return CBasicString((notEmpty(str))?(new SStringProxy(str, eOwnPolicyDealloc)):(SStringProxy::emptyStringProxy()->retain()));
}

CBasicString::~CBasicString()
{
	mProxy->release();
}

CBasicString CBasicString::createWithFormat(const NChar *format, ...)
{
	va_list list;
	va_start(list, format);
	CBasicString result = createWithFormat(format, list);
	va_end(list);
	return result;
}

CBasicString CBasicString::createWithFormat(CBasicString format, ...)
{
	va_list list;
	va_start(list, format);
	CBasicString result = createWithFormat(format.cString(), list);
	va_end(list);
	return result;
}

CBasicString CBasicString::createWithFormat(const NChar *format, va_list argList)
{
	char* buffer;
	vasprintf(&buffer, format, argList);
	return CBasicString(new SStringProxy(buffer, (EOwnPolicy)(eOwnPolicyDefault | eOwnPolicyDeallocWithFree)));
}

CBasicString CBasicString::createWithFormat(const CBasicString &format, va_list argList)
{
	return createWithFormat(format.cString(), argList);
}

const CBasicString& CBasicString::operator = (const NChar* cString)
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

SInt32 CBasicString::compare(const NChar* cString) const
{
	return strcmp(mProxy->mString, cString);
}

SInt32 CBasicString::compare(const CBasicString& string) const
{
	return strcmp(mProxy->mString, string.mProxy->mString);
}

Bool CBasicString::operator == (const NChar* cString) const
{
	return !compare(cString);
}

Bool CBasicString::operator == (const CBasicString& string) const
{
	return !compare(string);
}

Bool CBasicString::operator != (const NChar* cString) const
{
	return _LE_BOOL_CAST(compare(cString));
}

Bool CBasicString::operator != (const CBasicString& string) const
{
	return _LE_BOOL_CAST(compare(string));
}


Bool CBasicString::operator < (const NChar* cString) const
{
	return (compare(cString) < 0);
}

Bool CBasicString::operator < (const CBasicString& string) const
{
	return (compare(string) < 0);
}


Bool CBasicString::operator > (const NChar* cString) const
{
	return (compare(cString) > 0);
}

Bool CBasicString::operator > (const CBasicString& string) const
{
	return (compare(string) > 0);
}


Bool CBasicString::operator <= (const NChar* cString) const
{
	return (compare(cString) <= 0);
}

Bool CBasicString::operator <= (const CBasicString& string) const
{
	return (compare(string) <= 0);
}


Bool CBasicString::operator >= (const NChar* cString) const
{
	return (compare(cString) >= 0);
}

Bool CBasicString::operator >= (const CBasicString& string) const
{
	return (compare(string) >= 0);
}


void CBasicString::append(NChar c, EStringEncoding encoding)
{
	char str[] = "x";
	*str = c;
	append(str, encoding);
}

void CBasicString::append(WChar c, EStringEncoding)
{
//	union
//	{
//		WChar c;
//		char s[2];
//	} u;
//	u.c = c;
	// TODO: complete this to correctly handle endians
//	std::cout << (char)c;
	append((char)c);
//#if LE_ENDIANS == LE_ENDIANS_LITTLE
////	std::cout << "CBasicString::append(" << u.s[0] << ")" << std::endl;
//	append(u.s[0]);
//#else
////	std::cout << "CBasicString::append(" << u.s[1] << ")" << std::endl;
//	append(u.s[1]);
//#endif
}

void CBasicString::append(const NChar* cString, EStringEncoding /* encoding*/)
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
void CBasicString::erase(UInt32 fromPos, UInt32 length)
{
	UInt32 len = mProxy->length();
	if (fromPos >= len) return;
	if (length >= len - fromPos || length == 0) length = len - fromPos;
	if (fromPos == 0 && length == len)
	{
		clear();
	}
	else
	{
		NChar* newStr = new NChar[len - length + 1];
		memcpy(newStr, mProxy->mString, fromPos);
		memcpy(newStr + fromPos, mProxy->mString + fromPos + length, len - fromPos - length + 1);
		mProxy->release();
		mProxy = new SStringProxy(newStr, eOwnPolicyDealloc);
	}
}

void CBasicString::trimWhitespace()
{
	NChar* start = mProxy->mString;
	for (; *start && isWhitespace(*start); ++start);
	if (*start)
	{
		NChar* end = start + strlen(start) - 1;
		NChar* endmark = end;
		for (; isWhitespace(*end); --end);
		if (start != mProxy->mString || end != endmark)
		{
			++end;
			NChar* newStr = new NChar[end - start + 1];
			memcpy(newStr, start, end - start);
			*(newStr + (end - start)) = '\0';
			mProxy->release();
			mProxy = new SStringProxy(newStr, eOwnPolicyDealloc);
		}
	}
	else
		clear();
}

UInt32 CBasicString::length() const
{
	return mProxy->length();
}

bool CBasicString::isEmpty() const
{
	return mProxy->isEmpty();
}

SInt32 CBasicString::find(const CBasicString& string) const
{
	char* res = strstr(mProxy->mString, string.mProxy->mString);
	return (res)?(res - mProxy->mString):(-1);
}

SInt32 CBasicString::findLast(const CBasicString& string) const
{
	size_t res = std::string(mProxy->mString).rfind(string.mProxy->mString);
	return (res == std::string::npos)?(-1):((SInt32)res);
}

Bool CBasicString::hasPrefix(const CBasicString& string) const
{
	return !find(string);
}

CBasicString CBasicString::subString(UInt32 from, UInt32 length) const
{
	return CBasicString(new SStringProxy(mProxy->mString + from, eOwnPolicyDefault, length));
}

const NChar* CBasicString::cString(EStringEncoding encoding) const
{
	return mProxy->mString;
}


std::ostream& operator << (std::ostream& stream, const CBasicString& string)
{
	return (stream << (string.cString()));
}

Bool CBasicString::isWhitespace(NChar c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

Bool CBasicString::isWhitespace(WChar c)
{
	return isWhitespace((NChar)c);
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
