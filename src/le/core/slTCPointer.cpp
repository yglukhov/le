#include "slTCPointer.h"

#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART

#include <map>

namespace sokira
{
	namespace le
	{

typedef std::map<void*, unsigned long> CPointerMap;

static inline CPointerMap& pointerMapSingleton()
{
	static CPointerMap* map = new CPointerMap();
	return *map;
}


	} // namespace le
} // namespace sokira


void _le_TCPointer_retain(void* obj)
{
	if(obj)
	{
		++(::sokira::le::pointerMapSingleton()[obj]);
	}
}

void _le_TCPointer_release(void* obj, void(*deleteFunc)(void*))
{
	::sokira::le::CPointerMap::mapped_type& refCnt =
			::sokira::le::pointerMapSingleton()[obj];
	--refCnt;
	if(!refCnt)
	{
		::sokira::le::pointerMapSingleton().erase(obj);
		deleteFunc(obj);
	}
}

void _le_TCPointer_reset(void* obj)
{
	if(obj)
	{
		::sokira::le::CPointerMap::mapped_type& refCnt =
			::sokira::le::pointerMapSingleton()[obj];
		--refCnt;
		if(!refCnt)
		{
			::sokira::le::pointerMapSingleton().erase(obj);
		}
	}
}

#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART

