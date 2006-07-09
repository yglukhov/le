#include "slCBasicString.h"
#include <common/debug/slAssert.h>
#include <cstring>

LE_NAMESPACE_START


CBasicString::CBasicString() :
	mString(new Char[1])
{
	*mString = 0;
}

CBasicString::CBasicString(const CBasicString& copy) :
	mString(new Char[copy.length() + 1])
{
	std::strcpy(mString, copy.mString);
}

CBasicString::CBasicString(const Char* cString) :
	mString(new Char[strlen(cString) + 1])
{
	std::strcpy(mString, cString);
}

CBasicString::CBasicString(const Char* cString, EStringEncoding /*encoding*/) :
	mString(new Char[strlen(cString) + 1])
{
	std::strcpy(mString, cString);
}

CBasicString::CBasicString(const WChar* /*uniString*/, UInt32 /*length*/, EStringEncoding /*encoding*/) :
	mString(new Char[100])
{
	// TODO: complete
	std::strcpy(mString, "This string was generated from uniString. Complete the constructor!");
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
	std::strcpy(mString, cString);
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
	strcpy(newString, mString);
	strcat(newString, cString);
	delete [] mString;
	mString = newString;
}

void CBasicString::append(const WChar* /*uniString*/, UInt32 /*length*/,
				EStringEncoding /*encoding*/)
{
	// TODO: complete
	delete [] mString;
	mString = new Char[100];
	strcpy(mString, "This string was generated from uniString. Complete the append method!");
}

void CBasicString::append(const CBasicString& string)
{
	append(string.mString);
}


// Erase characters from string. If toPos is equal to 0, then the
// characters are erased to the end of the string.
void CBasicString::erase(UInt32 /*fromPos*/, UInt32 /*toPos*/)
{
	// TODO: complete
}


UInt32 CBasicString::length() const
{
	return strlen(mString);
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
	return (stream << string.cString());
}

LE_NAMESPACE_END

////////////////////////////////////////////////////////////////////////////////
// CString runtime class implementation
////////////////////////////////////////////////////////////////////////////////
#include <common/types/slCString.h>

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CString);

LE_NAMESPACE_END
