#pragma once

#include <le/core/debug/slDebug.h>
#include <le/core/slTypes.h>

#define LE_SMART_POINTER_IS_NOT_SO_SMART

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// TCPointer class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TCPointer
{
	typedef UInt32 TRefCountType;

	public:
		//////////////////////////////////////////////////////////////////////////
		// Construction
		inline TCPointer();
		inline TCPointer(T* obj);
		inline TCPointer(const TCPointer& copy);

		template <typename CastedFrom>
		inline TCPointer(const TCPointer<CastedFrom>& copy);

		//////////////////////////////////////////////////////////////////////////
		// Destruction
		inline ~TCPointer();

		//////////////////////////////////////////////////////////////////////////
		// Assignment
		const TCPointer& operator=(T* copy);
		inline const TCPointer& operator=(const TCPointer& copy);

		template <typename CastedFrom>
		const TCPointer& operator=(const TCPointer<CastedFrom>& copy);

		// Reset the pointer to other value without killing the object.
		// Returns the pointer to previosly referenced object.
		T* reset(T* toValue = NULL);


		//////////////////////////////////////////////////////////////////////////
		// Pointer operations
		inline operator const T*() const;
		inline T* get();
		inline const T* get() const;

		inline T& operator*();
		inline const T& operator*() const;
		inline T* operator->();
		inline const T* operator->() const;

		inline operator Bool() const
		{
			return _LE_BOOL_CAST(mObj);
		}

		//////////////////////////////////////////////////////////////////////////
		// Release
		inline void retain();
		inline void release();
		inline void autorelease();

		//////////////////////////////////////////////////////////////////////////
		// Private section
	private:
#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART
		static void deleteFunc(void*);
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART
		template <typename Any> friend class TCPointer;
		T* mObj;
		TRefCountType* mRefCount;
};



////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template <typename T>
TCPointer<T>::TCPointer() : mObj(NULL)
#if defined LE_SMART_POINTER_IS_NOT_SO_SMART
	, mRefCount(NULL)
#endif // defined LE_SMART_POINTER_IS_NOT_SO_SMART
{

}

template <typename T>
TCPointer<T>::TCPointer(T* obj) : mObj(obj)
#if defined LE_SMART_POINTER_IS_NOT_SO_SMART
	, mRefCount(NULL)
#endif // defined LE_SMART_POINTER_IS_NOT_SO_SMART
{
	retain();
}

template <typename T>
TCPointer<T>::TCPointer(const TCPointer& copy) : mObj(copy.mObj)
#if defined LE_SMART_POINTER_IS_NOT_SO_SMART
	, mRefCount(copy.mRefCount)
#endif // defined LE_SMART_POINTER_IS_NOT_SO_SMART
{
	retain();
}

template <typename T>
template <typename CastedFrom>
TCPointer<T>::TCPointer(const TCPointer<CastedFrom>& copy) : mObj(copy.mObj)
#if defined LE_SMART_POINTER_IS_NOT_SO_SMART
	, mRefCount(copy.mRefCount)
#endif // defined LE_SMART_POINTER_IS_NOT_SO_SMART
{
	retain();
}

template <typename T>
TCPointer<T>::~TCPointer()
{
	release();
}

template <typename T>
const TCPointer<T>& TCPointer<T>::operator = (T* copy)
{
	if(mObj != copy)
	{
		release();
	}

	mObj = copy;

	retain();

	return *this;
}

template <typename T>
const TCPointer<T>& TCPointer<T>::operator = (const TCPointer& copy)
{
	return operator = <T>(copy);
}

template <typename T>
template <typename CastedFrom>
const TCPointer<T>& TCPointer<T>::operator = (const TCPointer<CastedFrom>& copy)
{
	if(mObj != copy.mObj)
	{
		release();
	}

	mObj = copy.mObj;
	mRefCount = copy.mRefCount;

	retain();

	return *this;
}

template <typename T>
TCPointer<T>::operator const T*() const
{
	return mObj;
}

template <typename T>
T* TCPointer<T>::get()
{
	return mObj;
}

template <typename T>
const T* TCPointer<T>::get() const
{
	return mObj;
}

template <typename T>
T& TCPointer<T>::operator*()
{
	LE_ASSERT(mObj != NULL);
	return *mObj;
}

template <typename T>
const T& TCPointer<T>::operator*() const
{
	LE_ASSERT(mObj != NULL);
	return *mObj;
}

template <typename T>
T* TCPointer<T>::operator->()
{
	LE_ASSERT(mObj != NULL);
	return mObj;
}

template <typename T>
const T* TCPointer<T>::operator->() const
{
	LE_ASSERT(mObj != NULL);
	return mObj;
}

#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART

	} // namespace le
} // namespace sokira


void _le_TCPointer_reset(void*);
void _le_TCPointer_retain(void*);
void _le_CAutoreleasePool_addObject(void*, void(*)(void*));
void _le_TCPointer_release(void*, void(*)(void*));


namespace sokira
{
	namespace le
	{

#endif // !LE_SMART_POINTER_IS_NOT_SO_SMART

template <typename T>
T* TCPointer<T>::reset(T* toValue)
{
#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART
	_le_TCPointer_reset(static_cast<void*>(mObj));
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART
	T* retValue = mObj;
	operator=(toValue);
	return retValue;
}

template <typename T>
void TCPointer<T>::retain()
{
#if defined LE_SMART_POINTER_IS_NOT_SO_SMART
	if (mObj)
	{
		if (!mRefCount)
		{
			mRefCount = new TRefCountType(1);
		}
		++(*mRefCount);
	}
#else // defined LE_SMART_POINTER_IS_NOT_SO_SMART
	_le_TCPointer_retain(static_cast<void*>(mObj));
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART
}

template <typename T>
void TCPointer<T>::release()
{
	if(mObj)
	{
#if defined LE_SMART_POINTER_IS_NOT_SO_SMART
		LE_ASSERT(mRefCount != NULL);
		--(*mRefCount);
		if (!(*mRefCount))
		{
			delete mObj;
			delete mRefCount;
		}
		mObj = NULL;
		mRefCount = NULL;
#else // defined LE_SMART_POINTER_IS_NOT_SO_SMART
		_le_TCPointer_release(static_cast<void*>(mObj), deleteFunc);
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART
	}
}

template <typename T>
void TCPointer<T>::autorelease()
{
#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART
	_le_CAutoreleasePool_addObject(static_cast<void*>(mObj), deleteFunc);
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART
}

#if !defined LE_SMART_POINTER_IS_NOT_SO_SMART
template <typename T>
void TCPointer<T>::deleteFunc(void* obj)
{
	delete static_cast<T*>(obj);
}
#endif // !defined LE_SMART_POINTER_IS_NOT_SO_SMART

	} // namespace le
} // namespace sokira
