#pragma once


////////////////////////////////////////////////////////////////////////////////
// Includes
#include "slTCClassFactory.h"
#include <typeinfo>

LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// Forward declaraions
class CObject;

////////////////////////////////////////////////////////////////////////////////
// TIClass
////////////////////////////////////////////////////////////////////////////////
template <class THierarchyRoot>
class TIClass
{
	public:
		inline CBasicString name() const;

		virtual TCPointer<THierarchyRoot> create() const = 0;

		virtual const NChar* stdTypeInfoName() const = 0;

		bool operator == (const TIClass<THierarchyRoot>& rhs) const;

	protected:
		inline TIClass(const CBasicString& name);
		CBasicString mName;
};

template <class THierarchyRoot>
TIClass<THierarchyRoot>::TIClass(const CBasicString& name) :
	mName(name)
{
	TCClassFactory<THierarchyRoot>::registerClass(this);
}

template <class THierarchyRoot>
CBasicString TIClass<THierarchyRoot>::name() const
{
	return mName;
}

typedef TIClass<CObject> IClass;


////////////////////////////////////////////////////////////////////////////////
// Class registration macros
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// The DECLARE_RUNTIME_CLASS macro must be used in class declaration section.
// The class must be inherited from CObject.
#define DECLARE_RUNTIME_CLASS(Class)			\
template <class, class> friend class TCClass;	\
public:											\
	static IClass* staticClass();				\
	virtual IClass* objectClass() const;		\
												\
	typedef TCPointer<Class> Ptr;				\
private:


////////////////////////////////////////////////////////////////////////////////
// The IMPLEMENT_RUNTIME_CLASS macro must be used in class implementation
// section in namespace of class definition. The class must be inherited
// from CObject.
#define IMPLEMENT_RUNTIME_CLASS(Class)										\
																			\
static TCClass<CObject, Class> _##Class##_class_description_(LESTR(#Class));\
																			\
IClass* Class::staticClass()												\
{																			\
	return &_##Class##_class_description_;									\
}																			\
																			\
IClass* Class::objectClass() const											\
{																			\
	return &_##Class##_class_description_;									\
}

////////////////////////////////////////////////////////////////////////////////
// TCClass class declaration
////////////////////////////////////////////////////////////////////////////////
template <class THierarchyRoot, class T>
class TCClass : public TIClass<THierarchyRoot>
{
	public:
		virtual TCPointer<THierarchyRoot> create() const
		{
			return TCPointer<THierarchyRoot>(dynamic_cast<THierarchyRoot*>(new T()));
		}

		virtual const NChar* stdTypeInfoName() const;

	// Private
		TCClass(const CBasicString& name) :
			TIClass<THierarchyRoot>(name)
		{
			
		}
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
template <class THierarchyRoot, class T>
const NChar* TCClass<THierarchyRoot, T>::stdTypeInfoName() const
{
	return typeid(T).name();
}

LE_NAMESPACE_END
