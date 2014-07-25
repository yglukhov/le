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

static inline Bool typeInfosEqual(const std::type_info& lhs, const std::type_info& rhs)
{
	return !strcmp(lhs.name(), rhs.name());
}

template <class T, int ParentType> // 1 - public, 2 - private, 4 - protected
struct TSParentDeclarator
{};

template <int TypeMask>
struct TSParentCollector
{
	template <typename T>
	struct collector : public TSFalse
	{};

	template <class T, int Type>
	struct collector<TSParentDeclarator<T, Type> > : public TSBoolTypeFromInt<Type & TypeMask>
	{
		typedef T result;
	};
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

#define LE_RTTI_PUBLIC_PARENT(name) _LE_RTTI_PARENT_WITH_TYPE(name, 1)
#define LE_RTTI_PRIVATE_PARENT(name) _LE_RTTI_PARENT_WITH_TYPE(name, 2)
#define LE_RTTI_PROTECTED_PARENT(name) _LE_RTTI_PARENT_WITH_TYPE(name, 4)

#define _LE_RTTI_PARENT_WITH_TYPE(name, type)	\
	::sokira::le::base::TSParentDeclarator<name, type> >::result::PushBack<

struct _SSelectorDeclarator
{
	protected:
		template <typename SelType>
		static inline ISelector *_selector(SelType sel, const CBasicString& name)
		{
			return new TCSelector<SelType>(sel, name);
		}
};

#define _LE_NOTHING

#define LE_RTTI_SELECTOR_WITH_NAME(sel, name)							\
	_LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, name, _LE_NOTHING)

#define LE_RTTI_SELECTOR(sel) LE_RTTI_SELECTOR_WITH_NAME(sel, sel)

#define _LE_RTTI_SELECTOR_WITH_TYPE_NAME(sel, name, type)	\
	::sokira::le::_SNullType>::result _LE_RTTI_SEL_DECLARATOR_##name##_break;	\
	struct _TSSel_##name##_declarator : public ::sokira::le::base::_SSelectorDeclarator \
	{																	\
		static inline ISelector *selector()								\
		{																\
			return _selector(type &__LE_temp_Self::sel, LESTR(#name));	\
		}																\
	};																	\
	typedef _LE_RTTI_SEL_DECLARATOR_##name##_break::PushBack<_TSSel_##name##_declarator>::result::PushBack<



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
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSParentCollector<1 | 2 | 4>::collector>::result leParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSParentCollector<1>::collector>::result lePublicParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSParentCollector<2>::collector>::result lePrivateParents;	\
	typedef _le_RTTI_INFO::CollectMutantsIf< ::sokira::le::base::TSParentCollector<4>::collector>::result leProtectedParents;	\
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

class CDictionary;

////////////////////////////////////////////////////////////////////////////////
// class CClass
////////////////////////////////////////////////////////////////////////////////
class CClass
{
		CClass() {}
	public:
		CBasicString name() const;
		bool operator == (const CClass rhs) const;
		template <class TCastTo>
		TCPointer<TCastTo> create() const;

		std::vector<CClass> parents() const;

		std::set<ISelector*> selectors() const;
		std::set<ISelector*> ownSelectors() const;

		ISelector* selectorWithName(const CBasicString& name) const;

		inline bool isChildOfClass(const CClass& otherClass) const
		{
			return isChildOfStdClass(otherClass.stdType());
		}

		inline bool isKindOfClass(const CClass& otherClass) const
		{
			return *this == otherClass || isChildOfClass(otherClass);
		}

		bool instanceRespondsToSelector(const CBasicString& name) const;

	// Private:
		CClass(base::IClassImpl* impl);

		inline const std::type_info& stdType() const;
		inline bool isChildOfStdClass(const std::type_info& stdClass) const;
		inline Float32 priorityForParameters(const CDictionary& paramters) const;
	private:
		base::IClassImpl* mImpl;
};


////////////////////////////////////////////////////////////////////////////////
// RTTI implementation
////////////////////////////////////////////////////////////////////////////////
#define LE_IMPLEMENT_RUNTIME_CLASS(Class)													\
	static ::sokira::le::base::TCClassImpl<Class> _le_##Class##_ClassInfo_(LESTR(#Class));	\
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
		IClassImpl(const CBasicString&);
		virtual ~IClassImpl()
		{
			for (std::set<ISelector*>::iterator it = mSelectors.begin(); it != mSelectors.end(); ++it)
			{
				(*it)->release();
			}
		}

		template <class TTypeList>
		inline void registerSelectors()
		{
			TTypeList::template Enumerate<TSSelectorRegistrator, _SNullType, TSSelectorRegistratorTerminator>::addSelector(mSelectors);
		}

		virtual Float32 priorityForParameters(const CDictionary& parameters) const = 0;
	private:
		IClassImpl();
		CBasicString mName;
		std::set<ISelector*> mSelectors;

		template <class TContext>
		struct TSSelectorRegistrator
		{
			struct TSActualRegister
			{
				static inline void addSelector(std::set<ISelector*>& selectors)
				{
					selectors.insert(TContext::T::selector());
				}
			};

			static inline void addSelector(std::set<ISelector*>& selectors)
			{
				TSSelect
				<
					TSStrictCastAvailable<typename TContext::T, _SSelectorDeclarator>,
					TSActualRegister,
					TSSelectorRegistratorTerminator
				>::result::addSelector(selectors);
				TContext::Next::addSelector(selectors);
			}
		};

		struct TSSelectorRegistratorTerminator
		{
			static inline void addSelector(std::set<ISelector*>& selectors) { }
		};

		friend class ::sokira::le::CClass;
		friend struct ::sokira::le::SByNameFinder;
};

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

Float32 CClass::priorityForParameters(const CDictionary& paramters) const
{
	return mImpl->priorityForParameters(paramters);
}

		namespace base
		{

template <class T>
class TCClassImpl : public IClassImpl
{
	LE_DECLARE_MEMBER_FUNCTION_CHECKER(priorityForParameters, TSPriorityForParametersFunctionExists);

	public:
		TCClassImpl(const CBasicString& typeName) : IClassImpl(typeName)
		{
			registerSelectors<typename T::_le_RTTI_INFO>();
		}

		virtual void* create(const std::type_info& type) const
		{
			return (typeInfosEqual(typeid(T), type))?
				(static_cast<void*>(new T()))
				:
				(T::leParents::template Enumerate<TSForTypeListParentCreate, _SNullType, TSForTypeListParentCreateTerminator>::create(type));
		}

		virtual bool isChildOfStdClass(const std::type_info& type) const
		{
			return T::leParents::template Enumerate<TSChildOf, _SNullType, TSChildOfTerminator>::f(type);
		}

		virtual const std::type_info& stdType() const
		{
			return typeid(T);
		}

		virtual std::vector<CClass> parents() const
		{
			std::vector<CClass> result;
			result.reserve(T::leParents::length);
			T::leParents::template Enumerate<TSAddParent, _SNullType, TSAddParentTerminator>::addParent(result);
			return result;
		}

		virtual Float32 priorityForParameters(const CDictionary& parameters) const
		{
			return TSSelect<TSPriorityForParametersFunctionExists<T, Float32(*)(const CDictionary&)>, TSActualGetPriorityForParameters, TSStubGetPriorityForParameters>::result::f(parameters);
		}

	private:
		template <class TContext>
		struct TSForTypeListParentCreate
		{
			static void* create(const std::type_info& type)
			{
				if (typeInfosEqual(typeid(typename TContext::T), type))
				{
					return static_cast<void*>(dynamic_cast<typename TContext::T*>(new T()));
				}

				void* result = TContext::T::leParents::template Enumerate<TContext::template TEnumerator, _SNullType, TSForTypeListParentCreateTerminator>::create(type);

				return result ? result :(TContext::Next::create(type));
			}
		};

		struct TSForTypeListParentCreateTerminator
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
				typedef typename TContext::T CurType;
				return typeInfosEqual(typeid(CurType), stdType) ||
				CurType::leParents::template Enumerate<TContext::template TEnumerator, _SNullType, TSChildOfTerminator>::f(stdType) ||
				TContext::Next::f(stdType);
			}
		};

		struct TSChildOfTerminator
		{
			static inline bool f(const std::type_info&)
			{
				return false;
			}
		};

		template <class TContext>
		struct TSAddParent
		{
			static inline void addParent(std::vector<CClass>& res)
			{
				res.push_back(TContext::T::staticClass());
				TContext::Next::addParent(res);
			}
		};

		struct TSAddParentTerminator
		{
			static inline void addParent(std::vector<CClass>& res) { }
		};

		struct TSActualGetPriorityForParameters
		{
			static inline Float32 f(const CDictionary& params)
			{
				return T::priorityForParameters(params);
			}
		};

		struct TSStubGetPriorityForParameters
		{
			static inline Float32 f(const CDictionary& params)
			{
				return 0;
			}
		};
};

		} // namespace base
	} // namespace le
} // namespace sokira

#endif // !defined _slTCClass_h_included_
