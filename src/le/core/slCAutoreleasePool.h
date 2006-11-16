#pragma once

#include <le/core/config/slPrefix.h>
#include <list>

LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// CAutoreleasePool
////////////////////////////////////////////////////////////////////////////////
class CAutoreleasePool
{
	public:
		CAutoreleasePool();
		~CAutoreleasePool();

	private:
		typedef std::pair<void*, void(*)(void*)> CListValue;
		typedef std::list<CListValue> CPointerList;
		friend void _CAutoreleasePool_addObject(void*, void(*)(void*));
		CPointerList mPointerList;
		CAutoreleasePool* mPrevPool;
};

LE_NAMESPACE_END
