#pragma once

#include "base/slCBasicString.h"
#include <le/core/slCObject.h>

LE_NAMESPACE_START

class CString : public CObject, public CBasicString
{
	DECLARE_RUNTIME_CLASS(CString);

	public:
		inline CString() {}
		CString(const CDictionary& fromDictionary);
		inline CString(const CBasicString& copy) : CBasicString(copy) {}
		inline CString(const CString& copy) : CBasicString(copy) {}
		inline CString(const Char* cString) : CBasicString(cString) {}
		inline CString(const Char* cString, EStringEncoding encoding) :
			CBasicString(cString, encoding) {}
		inline CString(const WChar* uniString, UInt32 length, EStringEncoding encoding) :
			CBasicString(uniString, length, encoding) {}

		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);
};

LE_NAMESPACE_END
