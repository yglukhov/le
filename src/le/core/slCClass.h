#if !defined _slTCClass_h_included_
#define _slTCClass_h_included_

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>
#include "base/slCBasicString.h"
#include "slTCPointer.h"
#include "template/typelist/slTSTypeList.h"

#define _LE_STD_TYPENAME_COMPARISON_IS_TRIVIAL_

#if ! defined _LE_STD_TYPENAME_COMPARISON_IS_TRIVIAL_
#include <cstring> // for strcmp

#define _le_stdNamesEqual(n1, n2) (!strcmp((n1), (n2)))
#else
#define _le_stdNamesEqual(n1, n2) ((n1) == (n2))
#endif

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

	// Private:
		CClass(IClassImpl* impl);

		inline const char* stdName() const;
	private:
		IClassImpl* mImpl;
};


////////////////////////////////////////////////////////////////////////////////
// Hierarchy root declaration
////////////////////////////////////////////////////////////////////////////////
#define LE_DECLARE_HIERARCHY_ROOT(Class)						\
	public:														\
		typedef sokira::le::TSTypeList<> leParents;				\
	_LE_DECLARE_RUNTIME_CLASS(Class)

#define LE_IMPLEMENT_HIERARCHY_ROOT(Class)						\
	LE_IMPLEMENT_RUNTIME_CLASS(Class)

////////////////////////////////////////////////////////////////////////////////
// Runtime class declaration
////////////////////////////////////////////////////////////////////////////////
#define LE_DECLARE_RUNTIME_CLASS(Class)							\
	public:														\
		typedef sokira::le::TSTypeList<leSelf> leParents;		\
	_LE_DECLARE_RUNTIME_CLASS(Class)

#define LE_IMPLEMENT_RUNTIME_CLASS(Class)						\
	static sokira::le::TCClassImpl<Class> _le_##Class##_ClassInfo_(#Class);	\
	_LE_IMPLEMENT_RUNTIME_CLASS(Class)

////////////////////////////////////////////////////////////////////////////////
// Internal helper macros
////////////////////////////////////////////////////////////////////////////////
#define _LE_DECLARE_RUNTIME_CLASS(Class)						\
	protected:													\
		typedef Class leSelf;									\
	public:														\
		static sokira::le::CClass staticClass();				\
		virtual sokira::le::CClass objectClass() const;			\
		typedef sokira::le::TCPointer<Class> Ptr;				\
	private:

#define _LE_IMPLEMENT_RUNTIME_CLASS(Class)						\
	sokira::le::CClass Class::staticClass()						\
	{															\
		return sokira::le::CClass(&_le_##Class##_ClassInfo_);	\
	}															\
																\
	sokira::le::CClass Class::objectClass() const				\
	{															\
		return sokira::le::CClass(&_le_##Class##_ClassInfo_);	\
	}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
class IClassImpl
{
	public:
		virtual void* create(const char* type) const = 0;
		virtual const char* stdName() const = 0;
		virtual bool isChildOfStdNamedClass(const char* name) = 0;

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

const char* CClass::stdName() const
{
	return mImpl->stdName();
}

template <class TListNode, class T>
struct TSForTypeListParentCreate
{
	static void* create(const char* typeName)
	{
		if (_le_stdNamesEqual(typeid(typename TListNode::Head).name(), typeName))
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

template <class TSTypeListNode>
struct TSChildOf
{
};

template <class U, class V>
struct TSChildOf<_TSTypeListNode<U, V> >
{
	static inline bool f(const char* stdName)
	{
		return _le_stdNamesEqual(typeid(U).name(), stdName) || TSChildOf<typename U::leParents::_headNode>::f(stdName) || TSChildOf<V>::f(stdName);
	}
};

template <>
struct TSChildOf<_SNullType>
{
	static inline bool f(const char*)
	{
		return false;
	}
};


template <class T>
class TCClassImpl : public IClassImpl
{
	public:
		TCClassImpl(const char* typeName) : IClassImpl(typeName) {}

		virtual void* create(const char* typeName) const
		{
			if (_le_stdNamesEqual(typeid(T).name(), typeName))
			{
				return static_cast<void*>(new T());
			}
			else
			{
				return TSForTypeListParentCreate<typename T::leParents::_headNode, T>::create(typeName);
			}
		}

		virtual bool isChildOfStdNamedClass(const char* name)
		{
			return TSChildOf<typename T::leParents::_headNode>::f(name);
		}

		virtual const char* stdName() const
		{
			return typeid(T).name();
		}
};

	} // namespace le
} // namespace sokira

#endif // !defined _slTCClass_h_included_
