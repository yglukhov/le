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
		CString(const WChar* uniString, UInt32 length, EStringEncoding encoding);
		~CString();

		const CString& operator = (const Char* cString);
		const CString& operator = (const CString& copy);

		const CString& operator += (const Char* cString) { append(cString); return *this; }
		const CString& operator += (const CString& string) { append(string); return *this; }

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
		void append(const WChar* uniString, UInt32 length,
						EStringEncoding encoding = eEncodingDefault);
		void append(const CString& string);

		// Erase characters from string. If toPos is equal to 0, then the
		// characters are erased to the end of the string.
		void erase(UInt32 fromPos, UInt32 toPos = 0);

		UInt32 length() const;
		EStringEncoding encoding() const;

		const Char* cString(EStringEncoding encoding = eEncodingDefault) const;


		const CString operator + (const Char* cString) const
		{
			return CString(*this) += cString;
		}

		const CString operator + (const CString& string) const
		{
			return CString(*this) += string;
		}

	private:
		Char* mString;
};

inline const CString operator + (const Char* cString, const CString& string)
{
	return (string + cString);
}

std::ostream& operator << (std::ostream& stream, const CString& string);

LE_NAMESPACE_END
