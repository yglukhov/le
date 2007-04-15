#if !defined _slTCClass_h_included_
#define _slTCClass_h_included_

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>
#include "base/slCBasicString.h"
#include "slTCPointer.h"
#include "template/typelist/slTSTypeList.h"

#define _LE_STD_TYPENAME_COMPARISON_IS_TRIVIAL_

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// Forward declaraions
class IClassImpl;

////////////////////////////////////////////////////////////////////////////////
// class CClass
////////////////////////////////////////////////////////////////////////////////
class CClass
{
		CClass() {}
	public:
		CBasicString name() const;
		bool operator == (const CClass rhs);
		template <class TCastTo>
		TCPointer<TCastTo> create() const;
//		{
//			return TCPointer<TCastTo>(static_cast<TCastTo*>(mImpl->create(typeid(TCastTo).name())));
//		}

	// Private:
		CClass(IClassImpl* impl);

	private:
		IClassImpl* mImpl;
};


////////////////////////////////////////////////////////////////////////////////
// Hierarchy root declaration
////////////////////////////////////////////////////////////////////////////////
#define LE_DECLARE_HIERARCHY_ROOT(Class)						\
	public:														\
		typedef TSTypeList<> leParents;							\
	_LE_DECLARE_RUNTIME_CLASS(Class)

#define LE_IMPLEMENT_HIERARCHY_ROOT(Class)						\
	LE_IMPLEMENT_RUNTIME_CLASS(Class)

////////////////////////////////////////////////////////////////////////////////
// Runtime class declaration
////////////////////////////////////////////////////////////////////////////////
#define LE_DECLARE_RUNTIME_CLASS(Class)							\
	public:														\
		typedef TSTypeList<leSelf> leParents;					\
	_LE_DECLARE_RUNTIME_CLASS(Class)

#define LE_IMPLEMENT_RUNTIME_CLASS(Class)						\
	static TCClassImpl<Class> _le_##Class##_ClassInfo_(#Class);	\
	_LE_IMPLEMENT_RUNTIME_CLASS(Class)

////////////////////////////////////////////////////////////////////////////////
// Internal helper macros
////////////////////////////////////////////////////////////////////////////////
#define _LE_DECLARE_RUNTIME_CLASS(Class)						\
	protected:													\
		typedef Class leSelf;									\
	public:														\
		static CClass staticClass();							\
		virtual CClass objectClass() const;						\
		typedef TCPointer<Class> Ptr;							\
	private:

#define _LE_IMPLEMENT_RUNTIME_CLASS(Class)						\
	CClass Class::staticClass()									\
	{															\
		return CClass(&_le_##Class##_ClassInfo_);				\
	}															\
																\
	CClass Class::objectClass() const							\
	{															\
		return CClass(&_le_##Class##_ClassInfo_);				\
	}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
class IClassImpl
{
	public:
		virtual void* create(const char* type) const = 0;
		virtual const char* stdName() const = 0;
	protected:
		IClassImpl(const char*);
	private:
		IClassImpl() {}
		const char* mName;
		friend class CClass;
		friend struct SByNameFinder;
};

template <class TCastTo>
TCPointer<TCastTo> CClass::create() const
{
	return TCPointer<TCastTo>(static_cast<TCastTo*>(mImpl->create(typeid(TCastTo).name())));
}


template <class TListNode, class T>
struct TSForTypeListParentCreate
{
	static void* create(const char* typeName)
	{
#ifdef _LE_STD_TYPENAME_COMPARISON_IS_TRIVIAL_
		if (typeid(typename TListNode::Head).name() == typeName)
#else
		error
#endif
		{
			return static_cast<void*>(dynamic_cast<typename TListNode::Head*>(new T()));
		}

		void* result = TSForTypeListParentCreate<typename TListNode::Head::leParents::_headNode, T>::create(typeName);

		if (result)
			return result;

		return TSForTypeListParentCreate<typename TListNode::Tail, T>::create(typeName);
	}
};

template <class T>
struct TSForTypeListParentCreate<_SNullType, T>
{
	static void* create(const char* typeName)
	{
		return NULL;
	}
};

template <class T>
struct TSCreator
{
	static void* create(const char* typeName)
	{
		return NULL;
	}
};

template <class T>
class TCClassImpl : public IClassImpl
{
	public:
		TCClassImpl(const char* typeName) : IClassImpl(typeName) {}

		virtual void* create(const char* typeName) const
		{
#ifdef _LE_STD_TYPENAME_COMPARISON_IS_TRIVIAL_
			if (typeid(T).name() == typeName)
#else
			error
#endif
			{
				return static_cast<void*>(new T());
			}
			else
			{
				return TSForTypeListParentCreate<typename T::leParents::_headNode, T>::create(typeName);
			}
		}

		virtual const char* stdName() const
		{
			return typeid(T).name();
		}
};

	} // namespace le
} // namespace sokira

#endif // !defined _slTCClass_h_included_
