#if !defined SL_LE_core_thread_slCThreadSingletone_h
#define SL_LE_core_thread_slCThreadSingletone_h

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
#ifdef LE_TLS_STATIC_DEFINITION
			LE_TLS_STATIC_DEFINITION(T, result);
			return &result;
#else
			return CThread::thread().singletone<T>();
#endif
		}
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_thread_slCThreadSingletone_h
