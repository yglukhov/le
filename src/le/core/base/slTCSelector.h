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
struct TCSelectorArgumentsSetter
{
	template <class Tuple, typename T>
	static inline void setThisToFunction(Tuple& t, T thisObject)
	{
		t.template setValue<0>(thisObject);
	}
};

template <>
struct TCSelectorArgumentsSetter<false>
{
	template <class Tuple, typename T>
	static inline void setThisToFunction(Tuple& t, T thisObject)
	{
	}
};

template <bool isVoid>
struct TSSelectorCaller
{
	template <class Tuple, typename FuncType>
	static inline CBasicAny call(Tuple& t, FuncType func)
	{
		return CBasicAny(TSFunctionTraits<FuncType>::callWithTuple(func, t));
	}
};

template <>
struct TSSelectorCaller<true>
{
	template <class Tuple, typename FuncType>
	static inline CBasicAny call(Tuple& t, FuncType func)
	{
		TSFunctionTraits<FuncType>::callWithTuple(func, t);
		return CBasicAny();
	}
};


template <typename FuncType>
class TCSelector : public ISelector
{
	enum
	{
		isClassFunc = !TSTypesEqual<typename TSFunctionTraits<FuncType>::OwnerClass, _SNullType>::value,
		argsCount = TSFunctionTraits<FuncType>::ParamList::length,
		isVoidFunc = TSTypesEqual<typename TSFunctionTraits<FuncType>::RetType, void>::value
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
			TCSelectorArgumentsSetter<isClassFunc>::setThisToFunction(t, static_cast<typename Traits::OwnerClass*>(object));
			ParamList::template Enumerate<TSFillTupleWithAnyArray, _SNullType, TSFillTupleWithAnyArrayTerminator>::f(t, arguments);
//			return call(t, TSTypeToType<typename Traits::RetType>());
			return TSSelectorCaller<isVoidFunc>::call(t, mFunc);
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
			return isVoidFunc;
		}

	private:
		FuncType mFunc;
};

	} // namespace le
} // namespace sokira
