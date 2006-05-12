#include "slCAutoreleasePool.h"
#include <common/debug/slDebug.h>


void _le_TCPointer_release(void*, void(*)(void*)); // defined in TCPointer.cpp


LE_NAMESPACE_START

static CAutoreleasePool* _currentPool = NULL;

CAutoreleasePool::CAutoreleasePool() : mPrevPool(_currentPool)
{
	_currentPool = this;
}

CAutoreleasePool::~CAutoreleasePool()
{
	CPointerList::iterator end = mPointerList.end();
	for (CPointerList::iterator iter = mPointerList.begin(); iter != end; ++iter)
	{
		_le_TCPointer_release(iter->first, iter->second);
	}

	_currentPool = mPrevPool;
}

inline void _CAutoreleasePool_addObject(void* obj, void(*deleteFunc)(void*))
{
	if(_currentPool && obj)
	{
		_currentPool->mPointerList.push_back(
						CAutoreleasePool::CListValue(obj, deleteFunc));
	}
}

LE_NAMESPACE_END


void _le_CAutoreleasePool_addObject(void* obj, void(*deleteFunc)(void*))
{
	LE_NESTED_NAMESPACE _CAutoreleasePool_addObject(obj, deleteFunc);
}
