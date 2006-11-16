#pragma once

#include <le/core/config/slPrefix.h>
#include <le/core/debug/slDebug.h>

LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// TCPointer class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TCPointer
{
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

		//////////////////////////////////////////////////////////////////////////
		// Release
		inline void retain();
		inline void release();
		inline void autorelease();

		//////////////////////////////////////////////////////////////////////////
		// Private section
	private:

		static void deleteFunc(void*);
		template <typename Any> friend class TCPointer;
		T* mObj;
};



////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template <typename T>
TCPointer<T>::TCPointer() : mObj(NULL)
{

}

template <typename T>
TCPointer<T>::TCPointer(T* obj) : mObj(obj)
{
	retain();
}

template <typename T>
TCPointer<T>::TCPointer(const TCPointer& copy) : mObj(copy.mObj)
{
	retain();
}

template <typename T>
template <typename CastedFrom>
TCPointer<T>::TCPointer(const TCPointer<CastedFrom>& copy) : mObj(copy.mObj)
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

LE_NAMESPACE_END


void _le_TCPointer_reset(void*);
void _le_TCPointer_retain(void*);
void _le_CAutoreleasePool_addObject(void*, void(*)(void*));
void _le_TCPointer_release(void*, void(*)(void*));


LE_NAMESPACE_START

template <typename T>
T* TCPointer<T>::reset(T* toValue)
{
	_le_TCPointer_reset(static_cast<void*>(mObj));
	T* retValue = mObj;
	operator=(toValue);
	return retValue;
}

template <typename T>
void TCPointer<T>::retain()
{
	_le_TCPointer_retain(static_cast<void*>(mObj));
}

template <typename T>
void TCPointer<T>::release()
{
	if(mObj)
	{
		_le_TCPointer_release(static_cast<void*>(mObj), deleteFunc);
	}
}

template <typename T>
void TCPointer<T>::autorelease()
{
	_le_CAutoreleasePool_addObject(static_cast<void*>(mObj), deleteFunc);
}

template <typename T>
void TCPointer<T>::deleteFunc(void* obj)
{
	delete static_cast<T*>(obj);
}


LE_NAMESPACE_END
