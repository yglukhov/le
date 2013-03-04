#if !defined SL_LE_core_thread_slCThread_h
#define SL_LE_core_thread_slCThread_h


#include <typeinfo>
#include <le/core/config/slCompiler.h>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/slCString.h>
#include <le/core/auxiliary/slCRunLoop.h>

namespace sokira
{
	namespace le
	{

#define LE_TLS_DEFINITION(type, name) __thread type name;
#define LE_TLS_STATIC_DEFINITION(type, name) static __thread type name;
#define LE_TLS_REFERENCE(name) name;

class CThreadImplBase;

class CThread
{
	public:
		CThread(const CThread& copy);
		CThread(const TCFunction<>& threadProc, const CString& threadName = CString(),
				bool startImmediately = true);
		~CThread();

		static CThread thread();
		void start();
//		void stop();
//		bool isRunning() const;
		CString name() const;
		CRunLoop& runLoop();

		static void sleep(UInt32 milliSeconds);
		static UInt32 milliSeconds();

		const CThread& operator = (const CThread& copy);

		template <class T>
		T* singletone()
		{
			return static_cast<T*>(_singletone(typeid(T).name(), create_singletone<T>, delete_singletone<T>));
		}

	private:
		CThread();
		inline CThread(CThreadImplBase*);

		template <class T>
		static void* create_singletone()
		{
			return static_cast<void*>(new T());
		}

		template <class T>
		static void delete_singletone(void* ptr)
		{
			delete static_cast<T*>(ptr);
		}

		void* _singletone(const char* stdTypeName, void*(*)(), void (*)(void*));

		CThreadImplBase* mImpl;
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_thread_slCThread_h
