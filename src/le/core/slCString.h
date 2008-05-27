#pragma once

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
		inline CString(const NChar* cString, EStringEncoding encoding) :
			CBasicString(cString, encoding) {}
		inline CString(const WChar* uniString, UInt32 length, EStringEncoding encoding) :
			CBasicString(uniString, length, encoding) {}

		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);
};

	} // namespace le
} // namespace sokira
