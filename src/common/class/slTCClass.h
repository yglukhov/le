#pragma once


////////////////////////////////////////////////////////////////////////////////
// Includes
#include <common/config/slPrefix.h>
#include <common/pointer/slTCPointer.h>
#include <common/types/slCString.h>
#include <typeinfo>

LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// Forward declaraions
class CObject;


////////////////////////////////////////////////////////////////////////////////
// IClass interface declaration
////////////////////////////////////////////////////////////////////////////////
class IClass
{
	public:
		CString name() const;
		virtual TCPointer<CObject> create() const = 0;

		virtual const NChar* stdTypeInfoName() const = 0;

		bool operator == (const IClass& rhs) const;

	protected:
		IClass(const CString name);
		CString mName;
};


////////////////////////////////////////////////////////////////////////////////
// Class registration macros
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// The DECLARE_RUNTIME_CLASS macro must be used in class declaration section.
// The class must be inherited from CObject.
#define DECLARE_RUNTIME_CLASS(Class)			\
template <typename T> friend class TCClass;		\
public:											\
	static IClass* staticClass();				\
	virtual IClass* objectClass() const;		\
												\
	typedef TCPointer<Class> Ptr;				\
private:


////////////////////////////////////////////////////////////////////////////////
// The IMPLEMENT_RUNTIME_CLASS macro must be used in class implementation
// section in global namespace. The class must be inherited from CObject.
#define IMPLEMENT_RUNTIME_CLASS(Class)								\
																	\
static TCClass<Class> _##Class##_class_description_(LESTR(#Class));	\
																	\
IClass* Class::staticClass()										\
{																	\
	return &_##Class##_class_description_;							\
}																	\
																	\
IClass* Class::objectClass() const									\
{																	\
	return &_##Class##_class_description_;							\
}


////////////////////////////////////////////////////////////////////////////////
// TCClass class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TCClass : public IClass
{
	public:
		virtual TCPointer<CObject> create() const;
		virtual const NChar* stdTypeInfoName() const;
	
	// Private
	TCClass(CString);
	private:
		TCClass(const TCClass& copy) {}
};


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
LE_NAMESPACE_END

void _le_register_class(LE_NESTED_NAMESPACE IClass*);

LE_NAMESPACE_START


template <typename T>
TCClass<T>::TCClass(CString name) :
	IClass(name)
{
	_le_register_class(this);
}


template <typename T>
TCPointer<CObject> TCClass<T>::create() const
{
	return TCPointer<CObject>(dynamic_cast<CObject*>(new T()));
}

template <typename T>
const NChar* TCClass<T>::stdTypeInfoName() const
{
	return typeid(T).name();
}

LE_NAMESPACE_END
