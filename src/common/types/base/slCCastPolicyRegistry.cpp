#include "slCCastPolicyRegistry.h"

LE_NAMESPACE_START

CCastPolicyRegistry* CCastPolicyRegistry::instance()
{
	static CCastPolicyRegistry* registry = new CCastPolicyRegistry();
	return registry;
}

bool CCastPolicyRegistry::castAvailable(const NChar* from, const NChar* to)
{
	return static_cast<bool>(findCaster(from, to));
}

ICastPolicy* CCastPolicyRegistry::findCaster(const NChar* from, const NChar* to)
{
	CPolicyMap::iterator foundFrom = mPolicyMap.find(CString(from));
	if (foundFrom != mPolicyMap.end())
	{
		std::map<CString, ICastPolicy*>::iterator foundTo = foundFrom->second.find(CString(to));
		if (foundTo != foundFrom->second.end())
		{
			return foundTo->second;
		}
	}

	return NULL;
}

CCastPolicyRegistry::CCastPolicyRegistry(const CCastPolicyRegistry&)
{

}

CCastPolicyRegistry::~CCastPolicyRegistry()
{

}