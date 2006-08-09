#include <iostream>
#include <cstring>
#include "slCBasicString.h"
#include <common/debug/slAssert.h>
#include <common/config/slCompiler.h>
#include <common/types/slCDictionary.h>

LE_NAMESPACE_START

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


CBasicString::CBasicString() :
	mString(new Char[1])
{
	*mString = 0;
}

CBasicString::CBasicString(const CBasicString& copy) :
	mString(new Char[copy.length() + 1])
{
	slStrCpy(mString, copy.mString);
}

CBasicString::CBasicString(const Char* cString) :
	mString(new Char[strlen(cString) + 1])
{
	slStrCpy(mString, cString);
}

CBasicString::CBasicString(const Char* cString, EStringEncoding /*encoding*/) :
	mString(new Char[strlen(cString) + 1])
{
	slStrCpy(mString, cString);
}

CBasicString::CBasicString(const WChar* /*uniString*/, UInt32 /*length*/, EStringEncoding /*encoding*/) :
	mString(new Char[100])
{
	// TODO: complete
	slStrCpy(mString, "This string was generated from uniString. Complete the constructor!");
	LE_ASSERT(false);
}

CBasicString::~CBasicString()
{
	delete [] mString;
}

const CBasicString& CBasicString::operator = (const Char* cString)
{
	delete [] mString;
	mString = new Char[strlen(cString) + 1];
	slStrCpy(mString, cString);
	return *this;
}

const CBasicString& CBasicString::operator = (const CBasicString& copy)
{
	return operator = (copy.mString);
}


Bool CBasicString::operator == (const Char* cString) const
{
	return !strcmp(mString, cString);
}

Bool CBasicString::operator == (const CBasicString& string) const
{
	return !strcmp(mString, string.mString);
}

Bool CBasicString::operator != (const Char* cString) const
{
	return !(operator==(cString));
}

Bool CBasicString::operator != (const CBasicString& string) const
{
	return !(operator==(string.mString));
}


Bool CBasicString::operator < (const Char* cString) const
{
	return (strcmp(mString, cString) < 0);
}

Bool CBasicString::operator < (const CBasicString& string) const
{
	return (strcmp(mString, string.mString) < 0);
}


Bool CBasicString::operator > (const Char* cString) const
{
	return (strcmp(mString, cString) > 0);
}

Bool CBasicString::operator > (const CBasicString& string) const
{
	return (strcmp(mString, string.mString) > 0);
}


Bool CBasicString::operator <= (const Char* cString) const
{
	return (strcmp(mString, cString) <= 0);
}

Bool CBasicString::operator <= (const CBasicString& string) const
{
	return (strcmp(mString, string.mString) <= 0);
}


Bool CBasicString::operator >= (const Char* cString) const
{
	return (strcmp(mString, cString) >= 0);
}

Bool CBasicString::operator >= (const CBasicString& string) const
{
	return (strcmp(mString, string.mString) >= 0);
}



void CBasicString::append(const Char* cString, EStringEncoding /*encoding*/)
{
	Char* newString = new Char[strlen(mString) + strlen(cString) + 1];
	slStrCpy(newString, mString);
	slStrCat(newString, cString);
	delete [] mString;
	mString = newString;
}

void CBasicString::append(const WChar* /*uniString*/, UInt32 /*length*/,
				EStringEncoding /*encoding*/)
{
	// TODO: complete
	delete [] mString;
	mString = new Char[100];
	slStrCpy(mString, "This string was generated from uniString. Complete the append method!");
}

void CBasicString::append(const CBasicString& string)
{
	append(string.mString);
}

void CBasicString::clear()
{
	mString[0] = 0;
}

// Erase characters from string. If toPos is equal to 0, then the
// characters are erased to the end of the string.
void CBasicString::erase(UInt32 /*fromPos*/, UInt32 /*toPos*/)
{
	// TODO: complete
}


UInt32 CBasicString::length() const
{
	return static_cast<UInt32>(std::strlen(mString));
}

bool CBasicString::isEmpty() const
{
	return (length() == 0);
}

EStringEncoding CBasicString::encoding() const
{
	return eEncodingDefault;
}


const Char* CBasicString::cString(EStringEncoding encoding) const
{
	return mString;
}


std::ostream& operator << (std::ostream& stream, const CBasicString& string)
{
	return (stream << (string.cString()));
}

LE_NAMESPACE_END

////////////////////////////////////////////////////////////////////////////////
// CString runtime class implementation
////////////////////////////////////////////////////////////////////////////////
#include <common/types/slCString.h>

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CString);

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

LE_NAMESPACE_END
