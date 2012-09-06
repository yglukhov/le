#if !defined _slTCClass_h_included_
#define _slTCClass_h_included_

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>
#include <set>
#include <vector>
#include "base/slCBasicString.h"
#include "base/slTCSelector.h"
#include "slTCPointer.h"
#include "template/typelist/slTSTypeList.h"

namespace sokira
{
	namespace le
	{
		namespace base
		{

template <class T>
struct TSPublicParentDeclarator
{};

template <class T>
struct TSPrivateParentDeclarator
{};

template <class T>
struct TSProtectedParentDeclarator
{};

//typedef _SNullType Self;

template <class T>
struct TSParentCollector : public TSFalse
{ };

template <class T>
struct TSParentCollector<TSPublicParentDeclarator<T> > : public TSTrue
{
	typedef T result;
};

template <class T>
struct TSParentCollector<TSPrivateParentDeclarator<T> > : public TSTrue
{
	typedef T result;
};

template <class T>
struct TSParentCollector<TSProtectedParentDeclarator<T> > : public TSTrue
{
	typedef T result;
};

template <class T>
struct TSPublicParentCollector : public TSFalse
{ };

template <class T>
struct TSPublicParentCollector<TSPublicParentDeclarator<T> > : public TSTrue
{
	typedef T result;
};

template <class T>
struct TSPrivateParentCollector : public TSFalse
{ };

template <class T>
struct TSPrivateParentCollector<TSPrivateParentDeclarator<T> > : public TSTrue
{
	typedef T result;
};

template <class T>
struct TSProtectedParentCollector : public TSFalse
{ };

template <class T>
struct TSProtectedParentCollector<TSProtectedParentDeclarator<T> > : public TSTrue
{
	typedef T result;
};

#define LE_DECLARE_RUNTIME_CLASS(name)	\
	LE_RTTI_BEGIN						\
		LE_RTTI_SINGLE_PUBLIC_PARENT	\
		LE_RTTI_SELF(name)				\
	LE_RTTI_END

#define LE_RTTI_BEGIN	\
	private:				\
	typedef ::sokira::le::TSTypeList<>::PushBack<

#define LE_RTTI_SELF(name)	\
	::sokira::le::_SNullType>::result _LE_RTTI_SELF_DECLARATOR_##name##_break; \
	typedef name __LE_temp_Self; \
	typedef _LE_RTTI_SELF_DECLARATOR_##name##_break::PushBack<

#define LE_RTTI_PUBLIC_PARENT(name)		\
	::sokira::le::base::TSPublicParentDeclarator<name> >::result::PushBack<

#define LE_RTTI_PRIVATE_PARENT(name)	\
	::sokira::le::base::TSPrivateParentDeclarator<name> >::result::PushBack<

#define LE_RTTI_PROTECTED_PARENT(name)	\
	::sokira::le::base::TSProtectedParentDeclarator<name> >::result::PushBack<

struct _SSelectorDeclarator
{
	protected:
		template <typename SelType>
		static inline ISelector *_selector(SelType sel, const char* name)
		{
			return new TCSelector<SelType>(sel, name);
		}
};

#define _LE_NOTHING

#define LE_RTTI_SELECTOR_WITH_NAME(sel, name)							\
	_LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, name, _LE_NOTHING)

#define LE_RTTI_SELECTOR(sel) LE_RTTI_SELECTOR_WITH_NAME(sel, sel)

#define _LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, name, type)	\
	::sokira::le::_SNullType>::result _LE_RTTI_SEL_DECLARATOR_##sel##_##name##_break;	\
	struct _TSSel_##sel##_##name##_declarator : public ::sokira::le::base::_SSelectorDeclarator \
	{																	\
		static inline ISelector *selector()								\
		{																\
			return _selector(type &__LE_temp_Self::sel, #name);			\
		}																\
	};																	\
	typedef _LE_RTTI_SEL_DECLARATOR_##sel##_##name##_break::PushBack<_TSSel_##sel##_##name##_declarator>::result::PushBack<



#define LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, name, ret, args) \
	_LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, name, (ret (__LE_temp_Self::*) args))


#define LE_RTTI_SELECTOR_WITH_TYPE(sel, ret, args) \
	LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, sel, ret, args)


#define LE_RTTI_SINGLE_PUBLIC_PARENT LE_RTTI_PUBLIC_PARENT(leSelf)
#define LE_RTTI_SINGLE_PRIVATE_PARENT LE_RTTI_PRIVATE_PARENT(leSelf)
#define LE_RTTI_SINGLE_PROTECTED_PARENT LE_RTTI_PROTECTED_PARENT(leSelf)


#define LE_RTTI_END ::sokira::le::_SNullType>::result \
	_le_RTTI_INFO; \
	template<typename> friend  class ::sokira::le::base::TCClassImpl;	\
	protected:		\
	typedef __LE_temp_Self leSelf;					\
	public:	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSParentCollector>	leParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSPublicParentCollector> lePublicParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSPrivateParentCollector> lePrivateParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSProtectedParentCollector> leProtectedParents;	\
	typedef leParents::TypeAtNonStrict<0>::result leFirstParent;	\
	typedef lePublicParents::TypeAtNonStrict<0>::result leFirstPublicParent;	\
	typedef lePrivateParents::TypeAtNonStrict<0>::result leFirstPrivateParent;	\
	typedef leProtectedParents::TypeAtNonStrict<0>::result leFirstProtectedParent;	\
		static ::sokira::le::CClass staticClass();				\
		virtual ::sokira::le::CClass objectClass() const;			\
		typedef ::sokira::le::TCPointer<leSelf> Ptr;


////////////////////////////////////////////////////////////////////////////////
// Forward declaraions
class IClassImpl;

} // namespace base

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

		std::vector<CClass> parents() const;

		std::set<ISelector*> selectors() const;
		std::set<ISelector*> ownSelectors() const;

	// Private:
		CClass(base::IClassImpl* impl);

		inline const std::type_info& stdType() const;
		inline bool isChildOfStdClass(const std::type_info& stdClass) const;
	private:
		base::IClassImpl* mImpl;
};


////////////////////////////////////////////////////////////////////////////////
// RTTI implementation
////////////////////////////////////////////////////////////////////////////////
#define LE_IMPLEMENT_RUNTIME_CLASS(Class)									\
	static ::sokira::le::base::TCClassImpl<Class> _le_##Class##_ClassInfo_(#Class);	\
	_LE_IMPLEMENT_RUNTIME_CLASS(Class);

////////////////////////////////////////////////////////////////////////////////
// Internal helper macros
////////////////////////////////////////////////////////////////////////////////
#define _LE_IMPLEMENT_RUNTIME_CLASS(Class)						\
	::sokira::le::CClass Class::staticClass()					\
	{															\
		return ::sokira::le::CClass(&_le_##Class##_ClassInfo_);	\
	}															\
																\
	::sokira::le::CClass Class::objectClass() const				\
	{															\
		return staticClass();									\
	}

class ISelector;

struct SByNameFinder;

			namespace base
			{


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
class IClassImpl
{
	public:
		virtual void* create(const std::type_info& type) const = 0;
		virtual const std::type_info& stdType() const = 0;
		virtual bool isChildOfStdClass(const std::type_info& type) const = 0;
		virtual std::vector<CClass> parents() const = 0;

	protected:
		IClassImpl(const char*);
		virtual ~IClassImpl()
		{
			for (std::set<ISelector*>::iterator it = mSelectors.begin(); it != mSelectors.end(); ++it)
			{
				delete *it;
			}
		}

		template <class TTypeList>
		inline void registerSelectors()
		{
			processDeclarator
				<
					typename TSSelect
					<
						TSStrictCastAvailable<typename TTypeList::Front, _SSelectorDeclarator>,
						typename TTypeList::Front,
						_SNullType
					>::result
				>();
			registerSelectors<typename TTypeList::PopFront>();
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

		friend class ::sokira::le::CClass;
		friend struct ::sokira::le::SByNameFinder;
};

template <>
inline void IClassImpl::registerSelectors<TSTypeList<> >()
{

}

template <>
inline void IClassImpl::processDeclarator<_SNullType>()
{

}

			} // namespace base

template <class TCastTo>
TCPointer<TCastTo> CClass::create() const
{
	return TCPointer<TCastTo>(static_cast<TCastTo*>(mImpl->create(typeid(TCastTo))));
}

const std::type_info& CClass::stdType() const
{
	return mImpl->stdType();
}

bool CClass::isChildOfStdClass(const std::type_info& stdClass) const
{
	return mImpl->isChildOfStdClass(stdClass);
}

		namespace base
		{

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

		return result ? result :(TSForTypeListParentCreate<typename TListNode::Tail, T>::create(type));
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

template <class TContext>
struct TSChildOf
{
	static inline bool f(const std::type_info& stdType)
	{
		typedef typename TContext::T T;
		return (typeid(T) == stdType) ||
			T::leParents::template Enumerate<TContext::template TEnumerator>::f(stdType) ||
			TContext::Next::f(stdType);
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

template <class TListNode>
struct TSForTypeListParentFind
{
	static void addParent(std::vector<CClass>& res)
	{
		res.push_back(TListNode::Head::staticClass());
		TSForTypeListParentFind<typename TListNode::Tail>::addParent(res);
	}
};

template <>
struct TSForTypeListParentFind<_SNullType>
{
	static void addParent(std::vector<CClass>& res)
	{

	}
};


template <class T>
class TCClassImpl : public IClassImpl
{
	public:
		TCClassImpl(const char* typeName) : IClassImpl(typeName)
		{
			registerSelectors<typename T::_le_RTTI_INFO>();
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
			return T::leParents::template Enumerate<TSChildOf>::f(type);
		}

		virtual const std::type_info& stdType() const
		{
			return typeid(T);
		}

		virtual std::vector<CClass> parents() const
		{
			std::vector<CClass> result;
			TSForTypeListParentFind<typename T::leParents::_headNode>::addParent(result);
			return result;
		}
};

		} // namespace base
	} // namespace le
} // namespace sokira

#endif // !defined _slTCClass_h_included_
