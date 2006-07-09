#pragma once

#include <iosfwd>
#include <common/config/slPrefix.h>
#include <common/types/slBasic.h>
//#include <common/slCObject.h>

LE_NAMESPACE_START


#define LESTR(string) "" string ""


enum EStringEncoding
{
	eEncodingDefault = 0
};

class CBasicString
{
	public:
		CBasicString();
		CBasicString(const CBasicString& copy);
		CBasicString(const Char* cString);
		CBasicString(const Char* cString, EStringEncoding encoding);
		CBasicString(const WChar* uniString, UInt32 length, EStringEncoding encoding);
		~CBasicString();

		const CBasicString& operator = (const Char* cString);
		const CBasicString& operator = (const CBasicString& copy);

		const CBasicString& operator += (const Char* cString) { append(cString); return *this; }
		const CBasicString& operator += (const CBasicString& string) { append(string); return *this; }

		Bool operator == (const Char* cString) const;
		Bool operator == (const CBasicString& string) const;

		Bool operator != (const Char* cString) const;
		Bool operator != (const CBasicString& string) const;

		Bool operator < (const Char* cString) const;
		Bool operator < (const CBasicString& string) const;

		Bool operator > (const Char* cString) const;
		Bool operator > (const CBasicString& string) const;

		Bool operator <= (const Char* cString) const;
		Bool operator <= (const CBasicString& string) const;

		Bool operator >= (const Char* cString) const;
		Bool operator >= (const CBasicString& string) const;

		void append(const Char* cString, EStringEncoding encoding = eEncodingDefault);
		void append(const WChar* uniString, UInt32 length,
						EStringEncoding encoding = eEncodingDefault);
		void append(const CBasicString& string);

		// Erase characters from string. If toPos is equal to 0, then the
		// characters are erased to the end of the string.
		void erase(UInt32 fromPos, UInt32 toPos = 0);

		UInt32 length() const;
		EStringEncoding encoding() const;

		const Char* cString(EStringEncoding encoding = eEncodingDefault) const;

		const CBasicString operator + (const Char* cString) const
		{
			return CBasicString(*this) += cString;
		}

		const CBasicString operator + (const CBasicString& string) const
		{
			return CBasicString(*this) += string;
		}

	private:
		Char* mString;
};

inline const CBasicString operator + (const Char* cString, const CBasicString& string)
{
	return (string + cString);
}

std::ostream& operator << (std::ostream& stream, const CBasicString& string);


LE_NAMESPACE_END
