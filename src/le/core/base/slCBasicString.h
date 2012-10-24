#if !defined H_slCBasicString_included
#define H_slCBasicString_included

#include <iosfwd>
#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

#define LESTR(string) ::sokira::le::CBasicString::__CStringWithLiteral("" string "")

class CData;

enum EStringEncoding
{
	eStringEncodingASCII = 0,
	eStringEncodingUTF8,
	eStringEncodingUTF8NoBOM,
	eStringEncodingUTF16BE,
	eStringEncodingUTF16BENoBOM,
	eStringEncodingUTF16LE,
	eStringEncodingUTF16LENoBOM,
#if (LE_ENDIAN == LE_ENDIAN_LITTLE)
	eStringEncodingUTF16 = eStringEncodingUTF16LE,
	eStringEncodingUTF16NoBOM = eStringEncodingUTF16LENoBOM
#else
	eStringEncodingUTF16 = eStringEncodingUTF16BE,
	eStringEncodingUTF16NoBOM = eStringEncodingUTF16BENoBOM
#endif
};

class CBasicString
{
	public:
		CBasicString();	// Create an empty string.
		CBasicString(const CBasicString& copy);	// Create a copy.
		CBasicString(const NChar* cString); // Create a string from C-string with ASCII encoding
		CBasicString(const WChar* wString); // Create a string from wide string
		CBasicString(const void* data, UInt32 length, EStringEncoding encoding); // From data
		~CBasicString();

		static CBasicString createWithFormat(const NChar *format, ...);
		static CBasicString createWithFormat(CBasicString format, ...);

		static CBasicString createWithFormat(const NChar *format, va_list argList);
		static CBasicString createWithFormat(const CBasicString &format, va_list argList);

		static CBasicString createWithCharacterRange(NChar startChar, UInt32 rangeLength);

		const CBasicString& operator = (NChar character);
		const CBasicString& operator = (const NChar* cString);
		const CBasicString& operator = (const CBasicString& copy);

		const CBasicString& operator += (const NChar* cString) { append(cString); return *this; }
		const CBasicString& operator += (const CBasicString& string) { append(string); return *this; }

		SInt32 compare(const NChar* cString) const;
		SInt32 compare(const WChar* cString) const;
		SInt32 compare(const CBasicString& string) const;

		Bool operator == (const NChar* cString) const;
		Bool operator == (const CBasicString& string) const;

		Bool operator != (const NChar* cString) const;
		Bool operator != (const CBasicString& string) const;

		Bool operator < (const NChar* cString) const;
		Bool operator < (const CBasicString& string) const;

		Bool operator > (const NChar* cString) const;
		Bool operator > (const CBasicString& string) const;

		Bool operator <= (const NChar* cString) const;
		Bool operator <= (const CBasicString& string) const;

		Bool operator >= (const NChar* cString) const;
		Bool operator >= (const CBasicString& string) const;

		void append(NChar c);
		void append(WChar c);
		void append(const NChar* cString);
		void append(const WChar* wString);
		void append(const CBasicString& string);

		WChar characterAtIndex(UInt32 index) const;

		void clear();
		// Erase characters from string. If toPos is equal to 0, then the
		// characters are erased to the end of the string.
		void erase(UInt32 fromPos, UInt32 length = 0);

		void trimWhitespace();

		UInt32 length() const;
		bool isEmpty() const;

		enum EFindOptions
		{
			eStringOptionsCaseInsensitive = LE_SET_BIT(0),
			eStringOptionsReverse = LE_SET_BIT(1)
		};

		SInt32 findWithOptions(const NChar* needle, UInt32 fromPos, UInt32 toPos, UInt16 options) const;
		SInt32 findWithOptions(const WChar* needle, UInt32 fromPos, UInt32 toPos, UInt16 options) const;

		SInt32 find(const CBasicString& string, UInt32 fromPos = 0) const;
		SInt32 find(WChar c, UInt32 fromPos = 0) const;
		SInt32 findLast(const CBasicString& string) const;
		SInt32 findLast(WChar c) const;
		Bool hasPrefix(const CBasicString& prefix) const;

		CBasicString subString(UInt32 from, UInt32 length) const;

		const NChar* UTF8String() const;

		CData dataUsingEncoding(EStringEncoding encoding) const;

		const CBasicString operator + (const NChar* nullTerminatedString) const
		{
			CBasicString result(*this);
			result.append(nullTerminatedString);
			return result;
		}

		const CBasicString operator + (const CBasicString& string) const
		{
			CBasicString result(*this);
			result.append(string);
			return result;
		}

		void uppercase();
		void lowercase();

		void capitalize();

		static Bool isWhitespace(NChar c);
		static Bool isWhitespace(WChar c);
	// PRIVATE:
		static CBasicString __CStringWithLiteral(const NChar*);
		static CBasicString __CStringNoCopyDeallocWithFree(const NChar*);
		static CBasicString __CStringNoCopyDeallocWithDelete(const NChar*);

	private:
		void* mData;
		inline CBasicString(void*);
};

inline const CBasicString operator + (const NChar* cString, const CBasicString& string)
{
	return CBasicString::__CStringWithLiteral(cString) + string;
}

std::ostream& operator << (std::ostream& stream, const CBasicString& string);

	} // namespace le
} // namespace sokira

#endif // not defined H_slCBasicString_included
