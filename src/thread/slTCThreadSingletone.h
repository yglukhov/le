#pragma once

#include "slCThread.h"

LE_NAMESPACE_START

template <class T>
class TCThreadSingletone
{
	public:
		static T* instance()
		{
			return CThread::thread().singletone<T>();
		}
};

LE_NAMESPACE_END
