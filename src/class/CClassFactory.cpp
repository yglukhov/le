#include "CClassFactory.h"
#include "CObject.h"
#include <debug/Debug.h>

#include <map>
#include <string>


typedef std::map<const std::string, IClass*> CClassMap;

static inline CClassMap& classMap()
{
	static CClassMap map;
	return map;
}

CObject::Ptr CClassFactory::create(const char* className)
{
	ENTER_LOG;

	CClassMap::iterator it = classMap().find(std::string(className));
	if(it == classMap().end())
	{
		IF_LOG(log << "WARNING: Class \"" << className << "\" is not registered in class registry." << std::endl);
		return NULL;
	}

	return (it->second)->create();
}

void _register_class(const std::string& name, IClass* theClass)
{
	ENTER_LOG;

	CClassMap::iterator it = classMap().find(name);
	if(it != classMap().end())
	{
		IF_LOG(log << "WARNING: Class \"" << name << "\" is already registered in class registry."
				 << std::endl);
		return;
	}

	IF_LOG(log << "Registering class " << theClass->name() << std::endl);
	classMap().insert(std::pair<const std::string, IClass*>(name, theClass));
}