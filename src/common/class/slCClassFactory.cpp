#include "slCClassFactory.h"
#include <common/slCObject.h>
#include <common/debug/slDebug.h>

#include <map>
#include <string>

LE_NAMESPACE_START

typedef std::map<const std::string, IClass*> CClassMap;

static inline CClassMap& classMap()
{
	static CClassMap map;
	return map;
}

CObject::Ptr CClassFactory::create(const char* className)
{
	LE_ENTER_LOG;

	CClassMap::iterator it = classMap().find(std::string(className));
	if(it == classMap().end())
	{
		IF_LOG(log << "WARNING: Class \"" << className << "\" is not registered in class registry." << std::endl);
		return NULL;
	}

	return (it->second)->create();
}

LE_NAMESPACE_END


void _le_register_class(const std::string& name, LE_NESTED_NAMESPACE IClass* theClass)
{
	LE_ENTER_LOG_SILENT;

	LE_NESTED_NAMESPACE CClassMap::iterator it = LE_NESTED_NAMESPACE classMap().find(name);
	if(it != LE_NESTED_NAMESPACE classMap().end())
	{
		IF_LOG(log << "WARNING: Class \"" << name << "\" is already registered in class registry."
				 << std::endl);
		return;
	}

	IF_LOG(log << "Registering class \"" << theClass->name() << '\"' << std::endl);
	LE_NESTED_NAMESPACE classMap().insert(std::pair<const std::string, LE_NESTED_NAMESPACE IClass*>(name, theClass));
}
