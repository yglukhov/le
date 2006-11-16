#pragma once

#include <map>
#include <common/types/base/slCBasicString.h>
#include <common/pointer/slTCPointer.h>
#include <common/debug/slDebug.h>

LE_NAMESPACE_START

template <class THierarchyRoot> class TIClass;
class CObject;

template <class THierarchyRoot>
class TCClassFactory
{
	public:
		static TCPointer<THierarchyRoot> create(const CBasicString& className);

		template <class TCastTo>
		static TCPointer<TCastTo> create(const CBasicString& className)
		{
			return TCPointer<TCastTo>(dynamic_cast<TCastTo*>(create(className).get()));
		}

		static void registerClass(TIClass<THierarchyRoot>* classDescription);

	private:
		typedef std::map<CBasicString, TIClass<THierarchyRoot>* > CClassMap;
		static CClassMap& classMap()
		{
			static CClassMap* map = new CClassMap();
			return *map;
		}
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
template <class THierarchyRoot>
void TCClassFactory<THierarchyRoot>::registerClass(TIClass<THierarchyRoot>* theClass)
{
	LE_ENTER_LOG_SILENT;

	typename CClassMap::iterator it = classMap().find(theClass->name());
	if(it != classMap().end())
	{
		IF_LOG(log << "WARNING: Class \"" << theClass->name() <<
						"\" is already registered in class registry." << std::endl);
		return;
	}

	IF_LOG(log << "Registering class \"" << theClass->name() << "\"" << std::endl);
	classMap().insert(typename CClassMap::value_type(theClass->name(), theClass));
}


template <class THierarchyRoot>
TCPointer<THierarchyRoot> TCClassFactory<THierarchyRoot>::create(const CBasicString& className)
{
	LE_ENTER_LOG;

	typename CClassMap::iterator it = classMap().find(className);
	if(it == classMap().end())
	{
		IF_LOG(log << "WARNING: Class \"" << className <<
							"\" is not registered in class registry." << std::endl);
		return NULL;
	}

	return (it->second)->create();
}

LE_NAMESPACE_END
