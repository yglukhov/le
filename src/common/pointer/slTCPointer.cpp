#include "slTCPointer.h"
#include <map>

LE_NAMESPACE_START

typedef std::map<void*, unsigned long> CPointerMap;

static inline CPointerMap& pointerMapSingleton()
{
	static CPointerMap* map = new CPointerMap();
	return *map;
}


LE_NAMESPACE_END


void _le_TCPointer_retain(void* obj)
{
	if(obj)
	{
		++(LE_NESTED_NAMESPACE pointerMapSingleton()[obj]);
	}
}

void _le_TCPointer_release(void* obj, void(*deleteFunc)(void*))
{
	LE_NESTED_NAMESPACE CPointerMap::mapped_type& refCnt =
			LE_NESTED_NAMESPACE pointerMapSingleton()[obj];
	--refCnt;
	if(!refCnt)
	{
		LE_NESTED_NAMESPACE pointerMapSingleton().erase(obj);
		deleteFunc(obj);
	}
}

void _le_TCPointer_reset(void* obj)
{
	if(obj)
	{
		LE_NESTED_NAMESPACE CPointerMap::mapped_type& refCnt =
			LE_NESTED_NAMESPACE pointerMapSingleton()[obj];
		--refCnt;
		if(!refCnt)
		{
			LE_NESTED_NAMESPACE pointerMapSingleton().erase(obj);
		}
	}
}



