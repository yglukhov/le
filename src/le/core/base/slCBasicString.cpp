#include <iostream>
#include <cstring>
#include <stdarg.h>

#include "slCBasicString.h"
#include <le/core/debug/slAssert.h>
#include <le/core/config/slCompiler.h>
#include <le/core/slCDictionary.h>

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS

#include <windows.h>

static inline int vasprintf(char** buffer, const char* format, va_list args)
{
	int count = _vscprintf(format, args) + 1;
	*buffer = (char*)malloc(count);
	vsprintf(*buffer, format, args);
	return count;
}

#elif LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace sokira
{
	namespace le
	{

#if defined(LE_COMPILER_IS_MSVC) && LE_COMPILER_VERSION >= 1400 // MSVS 2005 and higher
#pragma warning (push)
#pragma warning( disable : 4996 )
#endif // MSVS 2005 or higher

static inline void slStrCpy(NChar* dest, const NChar* src)
{
	using namespace std;
	strcpy(dest, src);
}

static inline void slStrCpy(WChar* dest, const WChar* src)
{
	using namespace std;
	wcscpy(dest, src);
}

static inline void slStrCat(NChar* dest, const NChar* src)
{
	using namespace std;
	strcat(dest, src);
}

static inline size_t slStrLen(const NChar* str)
{
	using namespace std;
	return strlen(str);
}

static inline size_t slStrLen(const WChar* str)
{
	using namespace std;
	return wcslen(str);
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
	eOwnPolicyDeallocWithDelete = LE_SET_BIT(1),
	eOwnPolicyDeallocWithFree = LE_SET_BIT(2),
	eOwnPolicyIsWide = LE_SET_BIT(3),
	eOwnPolicyDefault = eOwnPolicyCopy | eOwnPolicyDeallocWithDelete,
	eOwnPolicyLiteral = 0
};

struct SStringProxy;

template <typename TChar>
static SStringProxy* createProxy(const TChar* string, UInt16 policy = eOwnPolicyDefault, UInt32 length = 0);

struct SStringProxy
{
	~SStringProxy()
	{
		LE_ASSERT(!mEmpty);
		if (mFlags & eOwnPolicyDeallocWithDelete)
		{
			if (isWide())
			{
				delete [] mWString;
			}
			else
			{
				delete [] mNString;
			}
		}
		else if (mFlags & eOwnPolicyDeallocWithFree)
		{
			free(mNString);
		}

		if (mUTF8String != mNString)
		{
			delete [] mUTF8String;
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
			delete this;
		}
	}

	SStringProxy* copy()
	{
		SStringProxy* result;
		if (isWide())
		{
			result = createProxy(mWString);
		}
		else
		{
			result = createProxy(mNString);
		}
		release();
		return result;
	}

	inline UInt32 length() const
	{
		return isWide() ? slStrLen(mWString) : slStrLen(mNString);
	}

	inline Bool isEmpty() const
	{
		return isWide() ? !(*mWString) : !(*mNString);
	}

	inline bool isWide() const
	{
		return !!(mFlags & eOwnPolicyIsWide);
	}

	inline const char* UTF8String() const
	{
		if (!mUTF8String)
		{
			UInt32 wLength = slStrLen(mWString);
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
			// Check our byte order. Assuming we made the string as in your example
			CFStringEncoding encoding = (CFByteOrderLittleEndian == CFByteOrderGetCurrent()) ?
				kCFStringEncodingUTF32LE : kCFStringEncodingUTF32BE;

			CFStringRef string = CFStringCreateWithBytes(kCFAllocatorDefault,
														 (const UInt8 *)mWString,
														 wLength * sizeof(WChar),
														 encoding,
														 false);
			if (string)
			{
				CFIndex length = CFStringGetMaximumSizeForEncoding(wLength, kCFStringEncodingUTF8) + 1;
				mUTF8String = new char[length];
				CFStringGetCString(string, mUTF8String, length, kCFStringEncodingUTF8);
				CFRelease(string);
			}
#elif LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
#if (WINVER >= 0x0600)
			DWORD dwConversionFlags = WC_ERR_INVALID_CHARS;
#else
			DWORD dwConversionFlags = 0;
#endif

			int length = ::WideCharToMultiByte(CP_UTF8, dwConversionFlags, mWString,
					static_cast<int>( wLength + 1 ),   // total source string length, in WCHAR's,
                                        // including end-of-string \0
					NULL,                   // unused - no conversion required in this step
					0,                      // request buffer size
					NULL, NULL);

			LE_ASSERT(length != 0);
			mUTF8String = new char[length];

			::WideCharToMultiByte(CP_UTF8, dwConversionFlags, mWString,
				static_cast<int>( wLength + 1 ),   // total source string length, in WCHAR's,
												// including end-of-string \0
				mUTF8String,                // destination buffer
				length,                 // destination buffer size, in bytes
				NULL, NULL              // unused
				); 
#else
#error Not implemented
#endif
		}
		return mUTF8String;
	}


	template <typename TChar>
	inline TChar*& data();

	union
	{
		char* mString;
		WChar* mWString;
		NChar* mNString;
	};

	mutable char* mUTF8String;

	UInt32 mRefCount;
	UInt16 mFlags;
	bool mEmpty;
};

template <>
NChar*& SStringProxy::data<NChar>()
{
	return mNString;
}

template <>
WChar*& SStringProxy::data<WChar>()
{
	return mWString;
}

template <typename TChar>
static inline Bool notEmpty(const TChar* string)
{
	return string && *string;
}

template <typename TChar>
static inline void setWideFlag(SStringProxy* proxy)
{
	proxy->mUTF8String = proxy->mNString;
}

template <>
inline void setWideFlag<WChar>(SStringProxy* proxy)
{
	proxy->mFlags |= eOwnPolicyIsWide;
	proxy->mUTF8String = NULL;
}


template <typename TChar>
static SStringProxy* createProxy(const TChar* string, UInt16 policy, UInt32 length)
{
	SStringProxy* result = new SStringProxy;
	if (policy & eOwnPolicyCopy)
	{
		UInt32 newLen = length;
		if (!newLen)
		{
			newLen = slStrLen(string);
		}
		result->data<TChar>() = new TChar[newLen + 1];

		if (length)
		{
			memcpy(result->data<TChar>(), string, length * sizeof(TChar));
			result->data<TChar>()[length] = 0;
		}
		else
		{
			slStrCpy(result->data<TChar>(), string);
		}
	}
	else
	{
		result->data<TChar>() = const_cast<TChar*>(string);
	}

	result->mFlags = policy;
	result->mRefCount = 1;
	result->mEmpty = false;
	setWideFlag<TChar>(result);

	return result;
}

static SStringProxy* createEmptyProxy()
{
	static SStringProxy* proxy = createProxy("", eOwnPolicyLiteral);
	proxy->mEmpty = true;
	return proxy->retain();
}

static WChar* widecharWithData(void* data, UInt32 length, EStringEncoding encoding)
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
	CFStringEncoding cfEncoding = kCFStringEncodingInvalidId;
	switch (encoding)
	{
		case eStringEncodingASCII: cfEncoding = kCFStringEncodingASCII; break;
		case eStringEncodingUTF8: cfEncoding = kCFStringEncodingUTF8; break;
		case eStringEncodingUTF16LE: cfEncoding = kCFStringEncodingUTF16LE; break;
		case eStringEncodingUTF16BE: cfEncoding = kCFStringEncodingUTF16BE; break;
		default:
			break;
	}

	if (cfEncoding != kCFStringEncodingInvalidId)
	{
		CFStringRef string = CFStringCreateWithBytesNoCopy(kCFAllocatorDefault,
													 (const UInt8 *)data,
													 length,
													 cfEncoding,
													 false,
														   kCFAllocatorNull);
		if (string)
		{
			// Check our byte order. Assuming we made the string as in your example
			cfEncoding = (CFByteOrderLittleEndian == CFByteOrderGetCurrent()) ?
				kCFStringEncodingUTF32LE : kCFStringEncodingUTF32BE;
			CFIndex cfLen = CFStringGetLength(string);
			CFIndex outputLength = CFStringGetMaximumSizeForEncoding(cfLen + 1, cfEncoding);
			WChar* result = (WChar*) new char[outputLength];
			if (CFStringGetBytes(string, CFRangeMake(0, cfLen), cfEncoding, 0, FALSE, (UInt8*)result, outputLength, NULL) != cfLen)
			{
				delete [] result;
				result = NULL;
			}
			CFRelease(string);
			return result;
		}
	}

	return NULL;
#else
	return NULL;
//#error Not implemented
#endif
}

////////////////////////////////////////////////////////////////////////////////
// CBasicString implementation
////////////////////////////////////////////////////////////////////////////////
CBasicString::CBasicString() :
	mData(createEmptyProxy())
{

}

CBasicString::CBasicString(const CBasicString& copy) :
	mData(((SStringProxy*)copy.mData)->retain())
{

}

CBasicString::CBasicString(const NChar* str) :
	mData(notEmpty(str) ? createProxy(str) : createEmptyProxy())
{

}

CBasicString::CBasicString(const WChar* str) :
	mData(notEmpty(str) ? createProxy(str) : createEmptyProxy())
{

}

CBasicString::CBasicString(void* proxy) :
	mData(proxy)
{

}

CBasicString CBasicString::__CStringWithLiteral(const NChar* str)
{
	return CBasicString(notEmpty(str) ? createProxy(str, eOwnPolicyLiteral) : createEmptyProxy());
}

CBasicString CBasicString::__CStringNoCopyDeallocWithFree(const NChar* str)
{
	return CBasicString(notEmpty(str) ? createProxy(str, eOwnPolicyDeallocWithFree) : createEmptyProxy());
}

CBasicString CBasicString::__CStringNoCopyDeallocWithDelete(const NChar* str)
{
	return CBasicString(notEmpty(str) ? createProxy(str, eOwnPolicyDeallocWithDelete) : createEmptyProxy());
}

CBasicString::~CBasicString()
{
	((SStringProxy*)mData)->release();
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
	CBasicString result = createWithFormat(format.UTF8String(), list);
	va_end(list);
	return result;
}

CBasicString CBasicString::createWithFormat(const NChar *format, va_list argList)
{
	char* buffer;
	vasprintf(&buffer, format, argList);
	return CBasicString(createProxy(buffer, eOwnPolicyDeallocWithFree));
}

CBasicString CBasicString::createWithFormat(const CBasicString &format, va_list argList)
{
	return createWithFormat(format.UTF8String(), argList);
}

CBasicString CBasicString::createWithCharacterRange(NChar startChar, UInt32 rangeLength)
{
	NChar* buffer = new NChar[rangeLength + 1];
	UInt32 i = 0;
	for (; i < rangeLength; ++i)
	{
		buffer[i] = startChar + i;
	}
	buffer[i] = 0;
	return CBasicString(createProxy(buffer, eOwnPolicyDeallocWithDelete));
}

const CBasicString& CBasicString::operator = (NChar character)
{
	((SStringProxy*)mData)->release();
	NChar* str = new NChar[2];
	*str = character;
	str[1] = 0;
	mData = createProxy(str, eOwnPolicyDeallocWithDelete);
	return *this;
}

const CBasicString& CBasicString::operator = (const NChar* cString)
{
	if (((SStringProxy*)mData)->mNString != cString)
	{
		((SStringProxy*)mData)->release();
		mData = notEmpty(cString) ? createProxy(cString) : createEmptyProxy();
	}

	return *this;
}

const CBasicString& CBasicString::operator = (const CBasicString& copy)
{
	if (((SStringProxy*)mData)->mNString != ((SStringProxy*)copy.mData)->mNString)
	{
		((SStringProxy*)mData)->release();
		mData = ((SStringProxy*)copy.mData)->retain();
	}

	return *this;
}

SInt32 CBasicString::compare(const NChar* cString) const
{
	if (((SStringProxy*)mData)->isWide())
	{
		size_t count = mbstowcs(NULL, cString, 0) + 1;
		WChar* buffer = (WChar*)malloc(sizeof(WChar) * count);
		mbstowcs(buffer, cString, count);
		SInt32 result = wcscmp(((SStringProxy*)mData)->mWString, buffer);
		free(buffer);
		return result;
	}

	return strcmp(((SStringProxy*)mData)->mNString, cString);
}

SInt32 CBasicString::compare(const WChar* str) const
{
	if (((SStringProxy*)mData)->isWide())
	{
		return wcscmp(((SStringProxy*)mData)->mWString, str);
	}

	NChar* cString = ((SStringProxy*)mData)->mNString;
	size_t count = mbstowcs(NULL, cString, 0) + 1;
	WChar* buffer = (WChar*)malloc(sizeof(WChar) * count);
	mbstowcs(buffer, cString, count);
	SInt32 result = wcscmp(buffer, str);
	free(buffer);
	return result;
}

SInt32 CBasicString::compare(const CBasicString& string) const
{
	if (((SStringProxy*)string.mData)->isWide())
	{
		return compare(((SStringProxy*)string.mData)->mWString);
	}

	return compare(((SStringProxy*)string.mData)->mNString);
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

WChar CBasicString::characterAtIndex(UInt32 index) const
{
	if (((SStringProxy*)mData)->isWide())
	{
		return ((SStringProxy*)mData)->mWString[index];
	}

	NChar c = ((SStringProxy*)mData)->mNString[index];
	WChar result = 0;
	if (mbtowc(&result, &c, sizeof(c)))
	{
		return result;
	}
	return 0;
}

void CBasicString::append(NChar c)
{
	NChar str[] = {c, 0};
	append(str);
}

void CBasicString::append(WChar c)
{
	WChar str[] = {c, 0};
	append(str);
}

void CBasicString::append(const NChar* cString)
{
	if (!notEmpty(cString))
		return;

	SStringProxy* proxy = (SStringProxy*)mData;
	if (proxy->isWide())
	{
		UInt32 otherLen = mbstowcs(NULL, cString, 0);
		if (otherLen)
		{
			++otherLen;
			UInt32 curLength = slStrLen(proxy->mWString);
			WChar* buffer = new WChar[otherLen + curLength];
			memcpy(buffer, proxy->mWString, curLength * sizeof(WChar));
			mbstowcs(buffer + curLength, cString, otherLen);
			proxy->release();
			mData = createProxy(buffer, eOwnPolicyDeallocWithDelete);
		}
	}
	else
	{
		UInt32 otherLen = slStrLen(cString);
		++otherLen;
		UInt32 curLength = slStrLen(proxy->mNString);
		NChar* buffer = new NChar[otherLen + curLength];
		memcpy(buffer, proxy->mNString, curLength);
		memcpy(buffer + curLength, cString, otherLen);
		proxy->release();
		mData = createProxy(buffer, eOwnPolicyDeallocWithDelete);
	}
}

void CBasicString::append(const WChar* wString)
{
	if (!notEmpty(wString))
		return;

	SStringProxy* proxy = (SStringProxy*)mData;
	if (proxy->isWide())
	{
		UInt32 otherLen = slStrLen(wString) + 1;
		UInt32 curLength = slStrLen(proxy->mWString);
		WChar* buffer = new WChar[otherLen + curLength];
		memcpy(buffer, proxy->mWString, curLength * sizeof(WChar));
		memcpy(buffer + curLength, wString, otherLen * sizeof(WChar));
		proxy->release();
		mData = createProxy(buffer, eOwnPolicyDeallocWithDelete);
	}
	else
	{
		UInt32 curLength = mbstowcs(NULL, proxy->mNString, 0);
		UInt32 otherLen = slStrLen(wString) + 1;
		WChar* buffer = new WChar[otherLen + curLength];
		mbstowcs(buffer, proxy->mNString, curLength);
		memcpy(buffer + curLength, wString, otherLen * sizeof(WChar));
		proxy->release();
		mData = createProxy(buffer, eOwnPolicyDeallocWithDelete);
	}
}

void CBasicString::append(const CBasicString& string)
{
	const SStringProxy* otherProxy = (const SStringProxy*)string.mData;
	if (otherProxy->isWide())
	{
		append(otherProxy->mWString);
	}
	else
	{
		append(otherProxy->mNString);
	}
}

void CBasicString::clear()
{
	((SStringProxy*)mData)->release();
	mData = createEmptyProxy();
}

template <typename TChar>
static inline SStringProxy* createProxyByErasingChars(UInt32 len, UInt32 fromPos, UInt32 length, SStringProxy* proxy)
{
	TChar* newStr = new TChar[len - length + 1];
	memcpy(newStr, proxy->data<TChar>(), fromPos * sizeof(TChar));
	memcpy(newStr + fromPos, proxy->data<TChar>() + fromPos + length, (len - fromPos - length + 1) * sizeof(TChar));
	proxy->release();
	return createProxy(newStr, eOwnPolicyDeallocWithDelete);
}

// Erase characters from string. If toPos is equal to 0, then the
// characters are erased to the end of the string.
void CBasicString::erase(UInt32 fromPos, UInt32 length)
{
	SStringProxy* proxy = ((SStringProxy*)mData);
	UInt32 len = proxy->length();
	if (fromPos >= len) return;
	if (length >= len - fromPos || length == 0) length = len - fromPos;
	if (fromPos == 0 && length == len)
	{
		clear();
	}
	else
	{
		if (proxy->isWide())
		{
			mData = createProxyByErasingChars<WChar>(len, fromPos, length, proxy);
		}
		else
		{
			mData = createProxyByErasingChars<NChar>(len, fromPos, length, proxy);
		}
	}
}

template <typename TChar>
SStringProxy* proxyByTrimmingWhitespace(SStringProxy* proxy)
{
	TChar* start = proxy->data<TChar>();
	for (; *start && CBasicString::isWhitespace(*start); ++start);
	if (*start)
	{
		TChar* end = start + slStrLen(start) - 1;
		TChar* endmark = end;
		for (; CBasicString::isWhitespace(*end); --end);
		if (start != proxy->data<TChar>() || end != endmark)
		{
			++end;
			TChar* newStr = new TChar[end - start + 1];
			memcpy(newStr, start, (end - start) * sizeof(TChar));
			*(newStr + (end - start)) = 0;
			proxy->release();
			return createProxy(newStr, eOwnPolicyDeallocWithDelete);
		}

		return proxy;
	}

	proxy->release();
	return createEmptyProxy();
}

void CBasicString::trimWhitespace()
{
	if (((SStringProxy*)mData)->isWide())
	{
		mData = proxyByTrimmingWhitespace<WChar>((SStringProxy*)mData);
	}
	else
	{
		mData = proxyByTrimmingWhitespace<NChar>((SStringProxy*)mData);
	}
}

UInt32 CBasicString::length() const
{
	return ((SStringProxy*)mData)->length();
}

bool CBasicString::isEmpty() const
{
	return ((SStringProxy*)mData)->isEmpty();
}

template <typename TChar>
static SInt32 _findWithOptions(const TChar* haystack, const TChar* needle, UInt32 fromPos, UInt32 toPos, UInt16 options)
{
	typedef std::basic_string<TChar> StdString;

	size_t haystackLength = slStrLen(haystack);
	if (toPos == 0)
	{
		toPos = haystackLength - 1;
	}

	size_t haystackRange = toPos - fromPos + 1;
	StdString stdHaystack(haystack + fromPos, haystackRange);

	size_t result;

	if (options & CBasicString::eStringOptionsReverse)
	{
		result = stdHaystack.rfind(needle);
	}
	else
	{
		result = stdHaystack.find(needle);
	}

	if (result == std::string::npos)
	{
		return -1;
	}

	return fromPos + result;
}

SInt32 CBasicString::findWithOptions(const NChar* needle, UInt32 fromPos, UInt32 toPos, UInt16 options) const
{
	if (((SStringProxy*)mData)->isWide())
	{
		UInt32 len = mbstowcs(NULL, needle, 0) + 1;
		WChar* buffer = new WChar[len];
		mbstowcs(buffer, needle, len);
		SInt32 result = _findWithOptions(((SStringProxy*)mData)->mWString, buffer, fromPos, toPos, options);
		delete [] buffer;
		return result;
	}
	return _findWithOptions(((SStringProxy*)mData)->mNString, needle, fromPos, toPos, options);
}

SInt32 CBasicString::findWithOptions(const WChar* needle, UInt32 fromPos, UInt32 toPos, UInt16 options) const
{
	if (((SStringProxy*)mData)->isWide())
	{
		return _findWithOptions(((SStringProxy*)mData)->mWString, needle, fromPos, toPos, options);
	}

	UInt32 len = mbstowcs(NULL, ((SStringProxy*)mData)->mNString, 0) + 1;
	WChar* buffer = new WChar[len];
	mbstowcs(buffer, ((SStringProxy*)mData)->mNString, len);
	SInt32 result = _findWithOptions(buffer, needle, fromPos, toPos, options);
	delete [] buffer;
	return result;
}

SInt32 CBasicString::find(const CBasicString& string, UInt32 fromPos) const
{
	if (((SStringProxy*)string.mData)->isWide())
	{
		return findWithOptions(((SStringProxy*)string.mData)->mWString, fromPos, 0, 0);
	}
	return findWithOptions(((SStringProxy*)string.mData)->mNString, fromPos, 0, 0);
}

SInt32 CBasicString::find(WChar c, UInt32 fromPos) const
{
	WChar needle[] = { c, 0 };
	return findWithOptions(needle, fromPos, 0, 0);
}

SInt32 CBasicString::findLast(const CBasicString& string) const
{
	if (((SStringProxy*)string.mData)->isWide())
	{
		return findWithOptions(((SStringProxy*)string.mData)->mWString, 0, 0, eStringOptionsReverse);
	}
	return findWithOptions(((SStringProxy*)string.mData)->mNString, 0, 0, eStringOptionsReverse);
}

SInt32 CBasicString::findLast(WChar c) const
{
	WChar needle[] = { c, 0 };
	return findWithOptions(needle, 0, 0, eStringOptionsReverse);
}

Bool CBasicString::hasPrefix(const CBasicString& string) const
{
	return !find(string);
}

CBasicString CBasicString::subString(UInt32 from, UInt32 length) const
{
	if (((SStringProxy*)mData)->isWide())
	{
		return CBasicString(createProxy(((SStringProxy*)mData)->mWString + from, eOwnPolicyDefault, length));
	}

	return CBasicString(createProxy(((SStringProxy*)mData)->mNString + from, eOwnPolicyDefault, length));
}

const NChar* CBasicString::UTF8String() const
{
	return ((SStringProxy*)mData)->UTF8String();
}

CData CBasicString::dataUsingEncoding(EStringEncoding encoding) const
{
	LE_ASSERT(false);
	return CData();
}

std::ostream& operator << (std::ostream& stream, const CBasicString& string)
{
	return (stream << (string.UTF8String()));
}

static inline void uppercaseChar(NChar& c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = 'A' + (c - 'a');
	}
}

static inline void lowercaseChar(NChar& c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = 'a' + (c - 'A');
	}
}

static inline void uppercaseChar(WChar& c)
{
	if (c >= L'a' && c <= L'z')
	{
		c = L'A' + (c - L'a');
	}
}

static inline void lowercaseChar(WChar& c)
{
	if (c >= L'A' && c <= L'Z')
	{
		c = L'a' + (c - L'A');
	}
}

void CBasicString::uppercase()
{
	mData = ((SStringProxy*)mData)->copy();
	if (((SStringProxy*)mData)->isWide())
	{
		for (WChar* c = ((SStringProxy*)mData)->mWString; *c; ++c) uppercaseChar(*c);
	}
	else
	{
		for (NChar* c = ((SStringProxy*)mData)->mNString; *c; ++c) uppercaseChar(*c);
	}
}

void CBasicString::lowercase()
{
	mData = ((SStringProxy*)mData)->copy();
	if (((SStringProxy*)mData)->isWide())
	{
		for (WChar* c = ((SStringProxy*)mData)->mWString; *c; ++c) lowercaseChar(*c);
	}
	else
	{
		for (NChar* c = ((SStringProxy*)mData)->mNString; *c; ++c) lowercaseChar(*c);
	}
}

void CBasicString::capitalize()
{
	if (length())
	{
		mData = ((SStringProxy*)mData)->copy();
		if (((SStringProxy*)mData)->isWide())
		{
			uppercaseChar(*((SStringProxy*)mData)->mWString);
		}
		else
		{
			uppercaseChar(*((SStringProxy*)mData)->mNString);
		}
	}
}

Bool CBasicString::isWhitespace(NChar c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

Bool CBasicString::isWhitespace(WChar c)
{
	return c == L' ' || c == L'\n' || c == L'\t' || c == L'\r';
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

	} // namespace le
} // namespace sokira
