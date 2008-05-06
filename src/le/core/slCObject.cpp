#include "slCObject.h"
#include <le/core/slCDictionary.h>

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CObject);

CObject::CObject()
{

}

CObject::~CObject()
{

}

CString CObject::description() const
{
	CDictionary dict(LESTR("object"));
	serialize(dict);
	char str[50];
	sprintf(str, "%p", (const void*)this);
	dict.attributeForKey(LESTR("type"), objectClass().name());
	dict.attributeForKey(LESTR("address"), str);
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
