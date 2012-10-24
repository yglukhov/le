#pragma once

#include <le/core/template/tuple/slTCTuple.h>
#include <le/core/template/function/slTSFunctionTraits.h>
#include "slCBasicAny.h"

namespace sokira
{
	namespace le
	{

class ISelector : public CSimpleRefCountable
{
	public:
		ISelector(const CBasicString& name) :
			mName(name)
		{

		}

		virtual ~ISelector() {}

		inline CBasicString name() const
		{
			return mName;
		}

		virtual CBasicAny operator() (void* object, const std::vector<CBasicReferenceAny>& arguments) const = 0;
		virtual UInt32 argumentsCount() const = 0;

		virtual Bool isConst() const = 0;
		virtual Bool isVoid() const = 0;

	private:
		CBasicString mName;
};

template <bool IsClass>
struct TCSelectorBase
{
	enum { _isClass = IsClass };
	template <class Tuple, typename T>
	static inline void setThisToFunction(Tuple& t, T thisObject)
	{
		t.template setValue<0>(thisObject);
	}
};

template <>
struct TCSelectorBase<false>
{
	enum { _isClass = false };
	template <class Tuple, typename T>
	static inline void setThisToFunction(Tuple& t, T thisObject)
	{
	}
};

template <typename FuncType>
class TCSelector : public ISelector
{
	enum
	{
		isClassFunc = !TSTypesEqual<typename TSFunctionTraits<FuncType>::OwnerClass, _SNullType>::value,
		argsCount = TSFunctionTraits<FuncType>::ParamList::length
	};

	template <class TContext>
	struct TSFillTupleWithAnyArray
	{
		template <class Tuple>
		static inline void f(Tuple& t, const std::vector<CBasicReferenceAny>& a)
		{
			t.template setValue<TContext::I + isClassFunc>(a[TContext::I].template value<typename TContext::T>());
			TContext::Next::f(t, a);
		}
	};

	struct TSFillTupleWithAnyArrayTerminator
	{
		template <class Tuple>
		static inline void f(Tuple& t, const std::vector<CBasicReferenceAny>& a)
		{ }
	};

	public:
		TCSelector(FuncType func, const CBasicString& name) :
			ISelector(name),
			mFunc(func)
		{

		}

		virtual CBasicAny operator() (void* object, const std::vector<CBasicReferenceAny>& arguments) const
		{
			LE_ASSERT(arguments.size() >= argsCount);
			typedef TSFunctionTraits<FuncType> Traits;
			typedef typename Traits::TupleParamList TupleParamList;
			typedef typename Traits::ParamList ParamList;
			TCTuple<TupleParamList> t;
			TCSelectorBase<isClassFunc>::setThisToFunction(t, static_cast<typename Traits::OwnerClass*>(object));
			ParamList::template Enumerate<TSFillTupleWithAnyArray, _SNullType, TSFillTupleWithAnyArrayTerminator>::f(t, arguments);
			return call(t, TSTypeToType<typename Traits::RetType>());
		}

		virtual UInt32 argumentsCount() const
		{
			return argsCount;
		}

		virtual Bool isConst() const
		{
			return TSFunctionTraits<FuncType>::IsConst::value;
		}

		virtual Bool isVoid() const
		{
			return TSTypesEqual<typename TSFunctionTraits<FuncType>::RetType, void>::value;
		}

	private:
		template <class Tuple, typename T>
		CBasicAny call(Tuple& t, TSTypeToType<T>) const
		{
			return CBasicAny(TSFunctionTraits<FuncType>::callWithTuple(mFunc, t));
		}

		template <class Tuple>
		CBasicAny call(Tuple& t, TSTypeToType<void>) const
		{
			TSFunctionTraits<FuncType>::callWithTuple(mFunc, t);
			return CBasicAny();
		}

		FuncType mFunc;
};

	} // namespace le
} // namespace sokira
