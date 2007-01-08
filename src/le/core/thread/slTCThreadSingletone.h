#pragma once

#include "slCThread.h"

namespace sokira
{
	namespace le
	{

template <class T>
class TCThreadSingletone
{
	public:
		static T* instance()
		{
			return CThread::thread().singletone<T>();
		}
};

	} // namespace le
} // namespace sokira
