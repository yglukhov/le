#pragma once

#include <le/core/template/tuple/slTCTuple.h>
#include <le/core/template/function/slTSFunctionTraits.h>
#include "slCBasicAny.h"

namespace sokira
{
	namespace le
	{

class ISelector
{
	public:
		ISelector(const char* name) :
			mName(name)
		{

		}

		virtual ~ISelector() {}

		inline const char* name() const
		{
			return mName;
		}

		virtual CBasicAny operator() (void* object, const std::vector<CBasicAny>& arguments) const = 0;
		virtual UInt32 argumentsCount() const = 0;

		virtual Bool isConst() const = 0;
	private:
		const char* mName;
};

template <typename FuncType>
class TCSelector : public ISelector
{
	template <class TContext>
	struct TSFillTupleWithAnyArray
	{
		template <class Tuple>
		static inline void f(Tuple& t, const std::vector<CBasicAny>& a)
		{
			t.template setValue<TContext::I + 1>(a[TContext::I].template value<typename TContext::T>());
			TContext::Next::f(t, a);
		}
	};

	struct TSFillTupleWithAnyArrayTerminator
	{
		template <class Tuple>
		static inline void f(Tuple& t, const std::vector<CBasicAny>& a)
		{ }
	};

	public:
		TCSelector(FuncType func, const char* name) :
			ISelector(name),
			mFunc(func)
		{

		}

		virtual CBasicAny operator() (void* object, const std::vector<CBasicAny>& arguments) const
		{
			typedef TSFunctionTraits<FuncType> Traits;
			typedef typename Traits::TupleParamList TupleParamList;
			typedef typename Traits::ParamList ParamList;
			TCTuple<TupleParamList> t;
			t.template setValue<0>(static_cast<typename Traits::OwnerClass*>(object));
			ParamList::template Enumerate<TSFillTupleWithAnyArray, _SNullType, TSFillTupleWithAnyArrayTerminator>::f(t, arguments);
			std::cout << "In tcselector:" << &t.template value<0>() << std::endl;
			return call(t, TSTypeToType<typename Traits::RetType>());
		}

		virtual UInt32 argumentsCount() const
		{
			return TSFunctionTraits<FuncType>::ParamList::length;
		}

		virtual Bool isConst() const
		{
			return TSFunctionTraits<FuncType>::IsConst::value;
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
