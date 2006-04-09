#pragma once

#include <debug/Debug.h>

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

		inline T& operator*();
		inline const T& operator*() const;
		inline T* operator->();
		inline const T* operator->() const;

		//////////////////////////////////////////////////////////////////////////
		// Release
		inline void retain();
		inline void release();
		inline void autorelease();
		void dump(std::ostream& ostream);

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
T& TCPointer<T>::operator*()
{
	ASSERT(mObj != NULL);
	return *mObj;
}

template <typename T>
const T& TCPointer<T>::operator*() const
{
	ASSERT(mObj != NULL);
	return *mObj;
}

template <typename T>
T* TCPointer<T>::operator->()
{
	ASSERT(mObj != NULL);
	return mObj;
}

template <typename T>
const T* TCPointer<T>::operator->() const
{
	ASSERT(mObj != NULL);
	return mObj;
}

template <typename T>
T* TCPointer<T>::reset(T* toValue)
{
	void _TCPointer_reset(void*);
	_TCPointer_reset(static_cast<void*>(mObj));
	T* retValue = mObj;
	operator=(toValue);
	return retValue;
}

template <typename T>
void TCPointer<T>::retain()
{
	void _TCPointer_retain(void*);
	_TCPointer_retain(static_cast<void*>(mObj));
}

template <typename T>
void TCPointer<T>::release()
{
	if(mObj)
	{
		void _TCPointer_release(void*, void(*)(void*));
		_TCPointer_release(static_cast<void*>(mObj), deleteFunc);
	}
}

template <typename T>
void TCPointer<T>::autorelease()
{
	void _CAutoreleasePool_addObject(void*, void(*)(void*));
	_CAutoreleasePool_addObject(static_cast<void*>(mObj), deleteFunc);
}

template <typename T>
void TCPointer<T>::deleteFunc(void* obj)
{
	delete static_cast<T*>(obj);
}
