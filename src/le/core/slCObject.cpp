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

Bool CObject::respondsToSelector(const CString& name) const
{
	return objectClass().instanceRespondsToSelector(name);
}

CSelectorInvocation CObject::selector(const CString& name)
{
	std::set<ISelector*> selectors = objectClass().selectors();
	for (std::set<ISelector*>::iterator it = selectors.begin(); it != selectors.end(); ++it)
	{
		if (name == (*it)->name())
		{
			return CSelectorInvocation(this, *it);
		}
	}

	return CSelectorInvocation(NULL, NULL);
}

	} // namespace le
} // namespace sokira
