#pragma once

#include <map>
#include "slCClass.h"
#include <le/core/debug/slDebug.h>

namespace sokira
{
	namespace le
	{

class CClassFactory
{
	public:
		template <class THierarchyRoot>
		static TCPointer<THierarchyRoot> create(const CBasicString& className)
		{
			LE_ENTER_LOG;

			IClassImpl* classImpl = _classWithName(className);
			if (classImpl)
				return CClass(classImpl).create<THierarchyRoot>();

			return NULL;
		}

		static bool isClassRegistered(const CBasicString& className);
		static CClass classWithName(const CBasicString& className)
		{
			return CClass(_classWithName(className));
		}

	private:
		static IClassImpl* _classWithName(const CBasicString& name);
		static IClassImpl* _classWithStdName(const char* name);
};

	} // namespace le
} // namespace sokira
