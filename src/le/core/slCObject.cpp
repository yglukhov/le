#include "slCObject.h"
#include <le/core/slCDictionary.h>

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CObject);
//
//CObject::CObject() :
//	mRefCount(1)
//{
//
//}
//
//CObject::~CObject()
//{
//	LE_ASSERT(mRefCount <= 1);
//}

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

//void CObject::retain() const
//{
//	++mRefCount;
//}
//
//void CObject::release() const
//{
//	--mRefCount;
//	if (!mRefCount)
//	{
//		delete this;
//	}
//}

	} // namespace le
} // namespace sokira
