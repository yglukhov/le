#include "CAutoreleasePool.h"
#include "Debug.h"

static CAutoreleasePool* _currentPool = NULL;

CAutoreleasePool::CAutoreleasePool() : mPrevPool(_currentPool)
{
	_currentPool = this;
}

CAutoreleasePool::~CAutoreleasePool()
{
	void _TCPointer_release(void*, void(*)(void*)); // defined in TCPointer.cpp

	CPointerList::iterator end = mPointerList.end();
	for (CPointerList::iterator iter = mPointerList.begin(); iter != end; ++iter)
	{
		_TCPointer_release(iter->first, iter->second);
	}

	_currentPool = mPrevPool;
}

void _CAutoreleasePool_addObject(void* obj, void(*deleteFunc)(void*))
{
	if(_currentPool && obj)
	{
		_currentPool->mPointerList.push_back(CAutoreleasePool::CListValue(obj, deleteFunc));
	}
}
