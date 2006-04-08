#include "TCPointer.h"
#include <map>

typedef std::map<void*, unsigned long> CPointerMap;

static inline CPointerMap& pointerMapSingleton()
{
	static CPointerMap* map = new CPointerMap();
	return *map;
}

void _TCPointer_retain(void* obj)
{
	if(obj)
	{
		++(pointerMapSingleton()[obj]);
	}
}

void _TCPointer_release(void* obj, void(*deleteFunc)(void*))
{
	CPointerMap::mapped_type& refCnt = pointerMapSingleton()[obj];
	--refCnt;
	if(!refCnt)
	{
		pointerMapSingleton().erase(obj);
		deleteFunc(obj);
	}
}

void _TCPointer_reset(void* obj)
{
	if(obj)
	{
		CPointerMap::mapped_type& refCnt = pointerMapSingleton()[obj];
		--refCnt;
		if(!refCnt)
		{
			pointerMapSingleton().erase(obj);
		}
	}
}
