#if !defined _slTCClass_h_included_
#define _slTCClass_h_included_

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>
#include <set>
#include "base/slCBasicString.h"
#include "base/slTCSelector.h"
#include "slTCPointer.h"
#include "template/typelist/slTSTypeList.h"

namespace sokira
{
	namespace le
	{

struct _TSStubDeclarator
{};

template <class T>
struct TSPublicParentDeclarator
{};

template <class T>
struct TSPrivateParentDeclarator
{};

template <class T>
struct TSProtectedParentDeclarator
{};

typedef _SNullType Self;

template <class T>
struct TSParentCollector
{
	enum { value = false };
};

template <class T>
struct TSParentCollector<TSPublicParentDeclarator<T> >
{
	enum { value = true };
	typedef T result;
};

template <class T>
struct TSParentCollector<TSPrivateParentDeclarator<T> >
{
	enum { value = true };
	typedef T result;
};

template <class T>
struct TSParentCollector<TSProtectedParentDeclarator<T> >
{
	enum { value = true };
	typedef T result;
};

template <class T>
struct TSPublicParentCollector
{
	enum { value = false };
};

template <class T>
struct TSPublicParentCollector<TSPublicParentDeclarator<T> >
{
	enum { value = true };
	typedef T result;
};

template <class T>
struct TSPrivateParentCollector
{
	enum { value = false };
};

template <class T>
struct TSPrivateParentCollector<TSPrivateParentDeclarator<T> >
{
	enum { value = true };
	typedef T result;
};

template <class T>
struct TSProtectedParentCollector
{
	enum { value = false };
};

template <class T>
struct TSProtectedParentCollector<TSProtectedParentDeclarator<T> >
{
	enum { value = true };
	typedef T result;
};

#define LE_DECLARE_RUNTIME_CLASS(name)		\
	LE_RTTI_BEGIN						\
		LE_RTTI_SINGLE_PUBLIC_PARENT	\
		LE_RTTI_SELF(name)				\
	LE_RTTI_END

#define LE_RTTI_BEGIN	\
	private:				\
	typedef sokira::le::TSTypeList<>::PushBack<

#define LE_RTTI_SELF(name)	\
	_TSStubDeclarator>::result _LE_RTTI_SELF_DECLARATOR_##name##_break; \
	typedef name __LE_temp_Self; \
	typedef _LE_RTTI_SELF_DECLARATOR_##name##_break::PushBack<

#define LE_RTTI_PUBLIC_PARENT(name)		\
	TSPublicParentDeclarator<name> >::result::PushBack<

#define LE_RTTI_PRIVATE_PARENT(name)	\
	TSPrivateParentDeclarator<name> >::result::PushBack<

#define LE_RTTI_PROTECTED_PARENT(name)	\
	TSProtectedParentDeclarator<name> >::result::PushBack<

struct _SSelectorDeclarator {};

#define LE_RTTI_SELECTOR_WITH_NAME(sel, name)							\
	_TSStubDeclarator>::result _LE_RTTI_SEL_DECLARATOR_##sel##_##name##_break;	\
	struct _TSSel_##sel##_##name##_declarator : public _SSelectorDeclarator \
	{																	\
		static inline ISelector *selector()								\
		{																\
			return _selector(&__LE_temp_Self::sel);						\
		}																\
	private:															\
		template <typename SelType>										\
		static inline ISelector *_selector(SelType sel)					\
		{																\
			return new TCSelector<SelType>(sel, #name);					\
		}																\
	};																	\
	typedef _LE_RTTI_SEL_DECLARATOR_##sel##_##name##_break::PushBack<_TSSel_##sel##_##name##_declarator>::result::PushBack<

#define LE_RTTI_SELECTOR(sel) LE_RTTI_SELECTOR_WITH_NAME(sel, sel)

#define LE_RTTI_SINGLE_PUBLIC_PARENT \
	TSPublicParentDeclarator<leSelf> >::result::PushBack<
#define LE_RTTI_SINGLE_PRIVATE_PARENT \
	TSPrivateParentDeclarator<leSelf> >::result::PushBack<
#define LE_RTTI_SINGLE_PROTECTED_PARENT \
	TSProtectedParentDeclarator<leSelf> >::result::PushBack<

#define LE_RTTI_END _TSStubDeclarator>::result \
	_le_RTTI_INFO; \
	template<typename> friend  class TCClassImpl;	\
	protected:		\
	typedef __LE_temp_Self leSelf;					\
	public:	\
	typedef _le_RTTI_INFO::CollectMutantsIf<sokira::le::TSParentCollector>	leParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf<sokira::le::TSPublicParentCollector> lePublicParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf<sokira::le::TSPrivateParentCollector> lePrivateParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf<sokira::le::TSProtectedParentCollector> leProtectedParents;	\
	typedef leParents::TypeAtNonStrict<0>::result leFirstParent;	\
	typedef lePublicParents::TypeAtNonStrict<0>::result leFirstPublicParent;	\
	typedef lePrivateParents::TypeAtNonStrict<0>::result leFirstPrivateParent;	\
	typedef leProtectedParents::TypeAtNonStrict<0>::result leFirstProtectedParent;	\
		static sokira::le::CClass staticClass();				\
		virtual sokira::le::CClass objectClass() const;			\
		typedef sokira::le::TCPointer<leSelf> Ptr;				\


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

		inline const std::type_info& stdType() const;
	private:
		IClassImpl* mImpl;
};


////////////////////////////////////////////////////////////////////////////////
// RTTI implementation
////////////////////////////////////////////////////////////////////////////////
#define LE_IMPLEMENT_RUNTIME_CLASS(Class)									\
	static sokira::le::TCClassImpl<Class> _le_##Class##_ClassInfo_(#Class);	\
	_LE_IMPLEMENT_RUNTIME_CLASS(Class);

////////////////////////////////////////////////////////////////////////////////
// Internal helper macros
////////////////////////////////////////////////////////////////////////////////
#define _LE_IMPLEMENT_RUNTIME_CLASS(Class)						\
	sokira::le::CClass Class::staticClass()						\
	{															\
		return sokira::le::CClass(&_le_##Class##_ClassInfo_);	\
	}															\
																\
	sokira::le::CClass Class::objectClass() const				\
	{															\
		return staticClass();									\
	}

class ISelector;

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
class IClassImpl
{
	public:
		virtual void* create(const std::type_info& type) const = 0;
		virtual const std::type_info& stdType() const = 0;
		virtual bool isChildOfStdClass(const std::type_info& type) const = 0;

	protected:
		IClassImpl(const char*);
		~IClassImpl()
		{
			for (std::set<ISelector*>::iterator it = mSelectors.begin(); it != mSelectors.end(); ++it)
			{
				delete *it;
			}
		}

		template <class TListNode>
		inline void registerSelectors()
		{
			processDeclarator
				<
					TSSelect
					<
						TSStrictCastAvailable<typename TListNode::Head, _SSelectorDeclarator>,
						typename TListNode::Head,
						_SNullType
					>::result
				>();
			registerSelectors<typename TListNode::Tail>();
		}

	private:
		IClassImpl();
		const char* mName;
		std::set<ISelector*> mSelectors;
		template <typename T>
		inline void processDeclarator()
		{
			mSelectors.insert(T::selector());
		}

		friend class CClass;
		friend struct SByNameFinder;
};

template <>
inline void IClassImpl::registerSelectors<_SNullType>()
{

}

template <>
inline void IClassImpl::processDeclarator<_SNullType>()
{

}

template <class TCastTo>
TCPointer<TCastTo> CClass::create() const
{
	return TCPointer<TCastTo>(static_cast<TCastTo*>(mImpl->create(typeid(TCastTo))));
}

const std::type_info& CClass::stdType() const
{
	return mImpl->stdType();
}

template <class TListNode, class T>
struct TSForTypeListParentCreate
{
	static void* create(const std::type_info& type)
	{
		if (typeid(typename TListNode::Head) == type)
		{
			return static_cast<void*>(dynamic_cast<typename TListNode::Head*>(new T()));
		}

		void* result = TSForTypeListParentCreate<typename TListNode::Head::leParents::_headNode, T>::create(type);

		return (result)?(result):(TSForTypeListParentCreate<typename TListNode::Tail, T>::create(type));
	}
};

template <class T>
struct TSForTypeListParentCreate<_SNullType, T>
{
	static void* create(const std::type_info& type)
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
	static inline bool f(const std::type_info& stdType)
	{
		return (typeid(U) == stdType) || TSChildOf<typename U::leParents::_headNode>::f(stdType) || TSChildOf<V>::f(stdType);
	}
};

template <>
struct TSChildOf<_SNullType>
{
	static inline bool f(const std::type_info&)
	{
		return false;
	}
};


template <class T>
class TCClassImpl : public IClassImpl
{
	public:
		TCClassImpl(const char* typeName) : IClassImpl(typeName)
		{
			registerSelectors<T::_le_RTTI_INFO::_headNode>();
		}

		virtual void* create(const std::type_info& type) const
		{
			return (typeid(T) == type)?
				(static_cast<void*>(new T()))
				:
				(TSForTypeListParentCreate<typename T::leParents::_headNode, T>::create(type));
		}

		virtual bool isChildOfStdClass(const std::type_info& type) const
		{
			return TSChildOf<typename T::leParents::_headNode>::f(type);
		}

		virtual const std::type_info& stdType() const
		{
			return typeid(T);
		}
};

	} // namespace le
} // namespace sokira

#endif // !defined _slTCClass_h_included_
