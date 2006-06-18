#include "slCString.h"
#include <common/debug/slAssert.h>
#include <cstring>

LE_NAMESPACE_START

CString::CString() :
	mString(new Char[1])
{
	*mString = 0;
}

CString::CString(const CString& copy) :
	mString(new Char[copy.length() + 1])
{
	std::strcpy(mString, copy.mString);
}

CString::CString(const Char* cString) :
	mString(new Char[strlen(cString) + 1])
{
	std::strcpy(mString, cString);
}

CString::CString(const Char* cString, EStringEncoding /*encoding*/) :
	mString(new Char[strlen(cString) + 1])
{
	std::strcpy(mString, cString);
}

CString::CString(const WChar* /*uniString*/, UInt32 /*length*/, EStringEncoding /*encoding*/) :
	mString(new Char[100])
{
	// TODO: complete
	std::strcpy(mString, "This string was generated from uniString. Complete the constructor!");
	LE_ASSERT(false);
}

CString::~CString()
{
	delete [] mString;
}

const CString& CString::operator = (const Char* cString)
{
	delete [] mString;
	mString = new Char[strlen(cString) + 1];
	std::strcpy(mString, cString);
	return *this;
}

const CString& CString::operator = (const CString& copy)
{
	return operator = (copy.mString);
}


Bool CString::operator == (const Char* cString) const
{
	return !strcmp(mString, cString);
}

Bool CString::operator == (const CString& string) const
{
	return !strcmp(mString, string.mString);
}

Bool CString::operator != (const Char* cString) const
{
	return !(operator==(cString));
}

Bool CString::operator != (const CString& string) const
{
	return !(operator==(string.mString));
}


Bool CString::operator < (const Char* cString) const
{
	return (strcmp(mString, cString) < 0);
}

Bool CString::operator < (const CString& string) const
{
	return (strcmp(mString, string.mString) < 0);
}


Bool CString::operator > (const Char* cString) const
{
	return (strcmp(mString, cString) > 0);
}

Bool CString::operator > (const CString& string) const
{
	return (strcmp(mString, string.mString) > 0);
}


Bool CString::operator <= (const Char* cString) const
{
	return (strcmp(mString, cString) <= 0);
}

Bool CString::operator <= (const CString& string) const
{
	return (strcmp(mString, string.mString) <= 0);
}


Bool CString::operator >= (const Char* cString) const
{
	return (strcmp(mString, cString) >= 0);
}

Bool CString::operator >= (const CString& string) const
{
	return (strcmp(mString, string.mString) >= 0);
}



void CString::append(const Char* cString, EStringEncoding /*encoding*/)
{
	Char* newString = new Char[strlen(mString) + strlen(cString) + 1];
	strcpy(newString, mString);
	strcat(newString, cString);
	delete [] mString;
	mString = newString;
}

void CString::append(const WChar* /*uniString*/, UInt32 /*length*/,
				EStringEncoding /*encoding*/)
{
	// TODO: complete
	delete [] mString;
	mString = new Char[100];
	strcpy(mString, "This string was generated from uniString. Complete the append method!");
}

void CString::append(const CString& string)
{
	append(string.mString);
}


// Erase characters from string. If toPos is equal to 0, then the
// characters are erased to the end of the string.
void CString::erase(UInt32 /*fromPos*/, UInt32 /*toPos*/)
{
	// TODO: complete
}


UInt32 CString::length() const
{
	return strlen(mString);
}

EStringEncoding CString::encoding() const
{
	return eEncodingDefault;
}


const Char* CString::cString(EStringEncoding encoding) const
{
	return mString;
}


std::ostream& operator << (std::ostream& stream, const CString& string)
{
	return (stream << string.cString());
}

LE_NAMESPACE_END
