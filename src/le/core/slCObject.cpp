#include "slCObject.h"
#include <le/core/slCDictionary.h>

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CObject);

CString CObject::description() const
{
	CDictionary dict(LESTR("object"));
	serialize(dict);
	CString addressStr = CString::createWithFormat("%p", (const void*)this);
	dict.setAttributeForKey(LESTR("type"), objectClass().name());
	dict.setAttributeForKey(LESTR("address"), addressStr);
	return dict.toString();
}

void CObject::serialize(CDictionary& toDictionary) const
{

}

void CObject::deserialize(const CDictionary& fromDictionary)
{

}

	} // namespace le
} // namespace sokira
