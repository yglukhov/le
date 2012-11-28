#include "slCObject.h"
#include <le/core/slCDictionary.h>

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CObject);

CBasicAny CSelectorInvocation::operator()(const std::vector<CBasicReferenceAny>& arguments)
{
	if (mSelector)
	{
		return mSelector->operator()(mObject, arguments);
	}
	return CBasicAny();
}

CString CObject::description() const
{
	CDictionary dict;
	serialize(dict);
	CString result = CString::createWithFormat("%s %p: ", objectClass().name().UTF8String(), (const void*)this);
	result += dict.toString();
	return result;
}

void CObject::serialize(CDictionary& toDictionary) const
{

}

void CObject::deserialize(const CDictionary& fromDictionary)
{

}

Bool CObject::respondsToSelector(const CString& name) const
{
	return objectClass().instanceRespondsToSelector(name);
}

CSelectorInvocation CObject::selector(const CString& name)
{
	ISelector* sel = objectClass().selectorWithName(name);
	if (sel)
	{
		return CSelectorInvocation(this, sel);
	}

	return CSelectorInvocation(NULL, NULL);
}

	} // namespace le
} // namespace sokira
