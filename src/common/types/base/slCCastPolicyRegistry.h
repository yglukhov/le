#pragma once

#include <common/types/slBasic.h>
#include <common/types/slCString.h>
#include <memory>
#include <map>
#include <typeinfo>

LE_NAMESPACE_START

class ICastPolicy;


class CCastPolicyRegistry
{
	public:
		template <typename To>
		To performCast(const void* from, const NChar* type);

		bool castAvailable(const NChar* from, const NChar* to);

		static CCastPolicyRegistry* instance();

	private:
		ICastPolicy* findCaster(const NChar*, const NChar*);
		typedef std::map<CString, std::map<CString, ICastPolicy*> > CPolicyMap;
		CPolicyMap mPolicyMap;
		CCastPolicyRegistry();
		CCastPolicyRegistry(const CCastPolicyRegistry&);
		~CCastPolicyRegistry();
};


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

class ICastPolicy
{
	public:
		virtual void* _performCast(const void* from) const
		{
			return NULL;
		}
};

template <typename To>
To CCastPolicyRegistry::performCast(const void* from, const NChar* type)
{
	ICastPolicy* caster = findCaster(type, typeid(To).name());
	if (!caster)
	{
		return To();
	}
	std::auto_ptr<To> result(static_cast<To*>(caster->_performCast(from)));
	return *result;
}

LE_NAMESPACE_END
