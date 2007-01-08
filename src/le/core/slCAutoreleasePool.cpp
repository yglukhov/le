#include "slCAutoreleasePool.h"
#include <le/core/debug/slDebug.h>
#include "slTCPointer.h"


void _le_TCPointer_release(void*, void(*)(void*)); // defined in TCPointer.cpp


namespace sokira
{
	namespace le
	{

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
#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART
		_le_TCPointer_release(iter->first, iter->second);
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART
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

	} // namespace le
} // namespace sokira


void _le_CAutoreleasePool_addObject(void* obj, void(*deleteFunc)(void*))
{
	::sokira::le::_CAutoreleasePool_addObject(obj, deleteFunc);
}
