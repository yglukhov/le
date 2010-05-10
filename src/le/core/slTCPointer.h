#pragma once

#include <le/core/debug/slDebug.h>
#include <le/core/slTypes.h>

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
//		T* reset(T* toValue = NULL);


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

		//////////////////////////////////////////////////////////////////////////
		// Private section
	private:
		template <typename Any> friend class TCPointer;
		T* mObj;
		TRefCountType* mRefCount;
};



////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template <typename T>
TCPointer<T>::TCPointer() :
	mObj(NULL),
	mRefCount(NULL)
{

}

template <typename T>
TCPointer<T>::TCPointer(T* obj) :
	mObj(obj),
	mRefCount(NULL)
{
	retain();
}

template <typename T>
TCPointer<T>::TCPointer(const TCPointer& copy) :
	mObj(copy.mObj),
	mRefCount(copy.mRefCount)
{
	LE_ASSERT(mRefCount);
	retain();
}

template <typename T>
template <typename CastedFrom>
TCPointer<T>::TCPointer(const TCPointer<CastedFrom>& copy) :
	mObj(copy.mObj),
	mRefCount(copy.mRefCount)
{
	LE_ASSERT(mRefCount);
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


//template <typename T>
//T* TCPointer<T>::reset(T* toValue)
//{
//	T* retValue = mObj;
//	operator=(toValue);
//	return retValue;
//}

template <typename T>
void TCPointer<T>::retain()
{
	if (mObj)
	{
		if (!mRefCount)
		{
			mRefCount = new TRefCountType(0);
		}
		++(*mRefCount);
	}
}

template <typename T>
void TCPointer<T>::release()
{
	if(mObj)
	{
		LE_ASSERT(mRefCount != NULL);
		--(*mRefCount);
		if (!(*mRefCount))
		{
			delete mObj;
			delete mRefCount;
		}
		mObj = NULL;
		mRefCount = NULL;
	}
}

	} // namespace le
} // namespace sokira
