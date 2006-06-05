#pragma once

#include <common/types/slBasic.h>
#include <iostream>

LE_NAMESPACE_START


#define LESTR(string) "" string ""


enum EStringEncoding
{
	eEncodingDefault = 0
};

class CString
{
	public:
		CString();
		CString(const CString& copy);
		CString(const Char* cString);
		CString(const Char* cString, EStringEncoding encoding);
		CString(const WChar* uniString, UInt4 length, EStringEncoding encoding);
		~CString();

		const CString& operator = (const Char* cString);
		const CString& operator = (const CString& copy);

		Bool operator == (const Char* cString) const;
		Bool operator == (const CString& string) const;

		Bool operator != (const Char* cString) const;
		Bool operator != (const CString& string) const;

		Bool operator < (const Char* cString) const;
		Bool operator < (const CString& string) const;

		Bool operator > (const Char* cString) const;
		Bool operator > (const CString& string) const;

		Bool operator <= (const Char* cString) const;
		Bool operator <= (const CString& string) const;

		Bool operator >= (const Char* cString) const;
		Bool operator >= (const CString& string) const;

		void append(const Char* cString, EStringEncoding encoding = eEncodingDefault);
		void append(const WChar* uniString, UInt4 length,
						EStringEncoding encoding = eEncodingDefault);
		void append(const CString& string);

		// Erase characters from string. If toPos is equal to 0, then the
		// characters are erased to the end of the string.
		void erase(UInt4 fromPos, UInt4 toPos = 0);

		UInt4 length() const;
		EStringEncoding encoding() const;

		const Char* cString(EStringEncoding encoding = eEncodingDefault) const;

	private:
		Char* mString;
};


std::ostream& operator << (std::ostream& stream, const CString& string);

LE_NAMESPACE_END
