#pragma once

#include <iosfwd>
#include <common/config/slPrefix.h>
#include <common/types/slBasic.h>

LE_NAMESPACE_START


#define LESTR(string) CBasicString::__CStringWithLiteral("" string "")


enum EStringEncoding
{
	eEncodingDefault = 0
};

class CBasicString
{
	public:
		CBasicString();	// Create an empty string.
		CBasicString(const CBasicString& copy);	// Create a copy.
		CBasicString(const Char* cString); // Create a string from C-string with default encoding
		CBasicString(const Char* cString, EStringEncoding encoding); // Create a string from C-string
		CBasicString(const WChar* uniString, UInt32 length, EStringEncoding encoding); // From uni-string
		CBasicString(const Char* cString1, const Char* cString2); // Append 2 cStrings with default encoding.
		~CBasicString();

		const CBasicString& operator = (const Char* cString);
		const CBasicString& operator = (const CBasicString& copy);

		const CBasicString& operator += (const Char* cString) { append(cString); return *this; }
		const CBasicString& operator += (const CBasicString& string) { append(string); return *this; }

		SInt32 compare(const Char* cString) const;
		SInt32 compare(const CBasicString& string) const;

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

		void clear();
		// Erase characters from string. If toPos is equal to 0, then the
		// characters are erased to the end of the string.
		void erase(UInt32 fromPos, UInt32 toPos = 0);

		UInt32 length() const;
		bool isEmpty() const;
		EStringEncoding encoding() const;

		const Char* cString(EStringEncoding encoding = eEncodingDefault) const;

		const CBasicString operator + (const Char* nullTerminatedString) const
		{
			return CBasicString(cString(), nullTerminatedString);
		}

		const CBasicString operator + (const CBasicString& string) const
		{
			return CBasicString(cString(), string.cString());
		}


	// PRIVATE:
		static CBasicString __CStringWithLiteral(const Char*);

	private:
		struct SStringProxy;
		SStringProxy* mProxy;
		inline CBasicString(SStringProxy* mProxy);
};

inline const CBasicString operator + (const Char* cString, const CBasicString& string)
{
	return CBasicString(cString, string.cString());
}

std::ostream& operator << (std::ostream& stream, const CBasicString& string);

LE_NAMESPACE_END
