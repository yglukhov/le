#pragma once

#include <common/class/slTCClass.h>

LE_NAMESPACE_START

class CDictionary;
class CString;

////////////////////////////////////////////////////////////////////////////////
// CObject
////////////////////////////////////////////////////////////////////////////////
class CObject
{
	DECLARE_RUNTIME_CLASS(CObject);

	public:
		CObject();
		virtual ~CObject();

		CString description() const;
		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);
};

LE_NAMESPACE_END
