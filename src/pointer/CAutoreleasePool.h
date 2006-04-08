#pragma once

#include <list>

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