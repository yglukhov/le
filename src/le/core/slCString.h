#if !defined SL_LE_core_slCString_h
#define SL_LE_core_slCString_h

#include "base/slCBasicString.h"
#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{

class CString : public CObject, public CBasicString
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CString)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		inline CString() {}
		CString(const CDictionary& fromDictionary);
		inline CString(const CBasicString& copy) : CBasicString(copy) {}
		inline CString(const CString& copy) : CBasicString(copy) {}
		inline CString(const NChar* cString) : CBasicString(cString) {}
		inline CString(const WChar* wString) : CBasicString(wString) {}
		inline CString(const void* data, UInt32 length, EStringEncoding encoding) :
			CBasicString(data, length, encoding) {}

		const CString& operator = (NChar character) { CBasicString::operator = (character); return *this; }
		const CString& operator = (WChar character) { CBasicString::operator = (character); return *this; }
		const CString& operator = (const NChar* string) { CBasicString::operator = (string); return *this; }
		const CString& operator = (const WChar* string) { CBasicString::operator = (string); return *this; }
		const CString& operator = (const CBasicString& string) { CBasicString::operator = (string); return *this; }

		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);
		virtual CString description() const { return *this; }
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCString_h
