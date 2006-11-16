#pragma once

#include <typeinfo>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/slCString.h>

LE_NAMESPACE_START

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
		void stop();
		bool isRunning() const;
		CString name() const;

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


LE_NAMESPACE_END
