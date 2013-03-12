#pragma once

#include <string.h>
#include <le/core/config/slPrefix.h>
#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/slTCPointer.h>
#include <le/core/template/typelist/slTSTypeList.h>

namespace sokira
{
	namespace le
	{

template <typename FuncType> struct TSFunctionTraits
{
	typedef TSFalse IsFunction;
};

	} // namespace le
} // namespace sokira

#include "base/slTSFunctionCallWithTuple.h"
#include "base/slTSFreeFunctionTraits.h"
#include "base/slTSMemberFunctionTraits.h"

namespace sokira
{
	namespace le
	{

template <typename RetType, class TypeList> class TCFunction;
template <typename FunctionType, class RealTypeList> class TCBind;

template <typename TRetType, class TypeList>
struct TSFunctionTraits<TCFunction<TRetType, TypeList> > :
	public TSFreeFunctionCallWithTuple<TRetType, TypeList::length>
{
	typedef TSTrue IsFunction;
	typedef TRetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
	typedef TSFalse IsConst;
};

template <typename FuncType, class TypeList>
struct TSFunctionTraits<TCBind<FuncType, TypeList> > :
	public TSFreeFunctionCallWithTuple<
		typename TSFunctionTraits<FuncType>::RetType,
		TypeList::length>
{
	typedef TSTrue IsFunction;
	typedef typename TSFunctionTraits<FuncType>::RetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
	typedef TSFalse IsConst;
};


class CFunctionDescriptor
{
	struct IFunctionDescriptor : CSimpleRefCountable
	{
		virtual UInt32 size() const = 0;
		virtual const void* pointer() const = 0;
	};

	TCPointer<IFunctionDescriptor> mData;

	public:
		CFunctionDescriptor() { }

		template <typename TFuncType>
		CFunctionDescriptor(TFuncType f)
		{
			struct TSFunctionDescriptor : public IFunctionDescriptor
			{
				struct Desc
				{
					TFuncType f;
				} desc;
				
				TSFunctionDescriptor(TFuncType func)
				{
					desc.f = func;
				}
				
				virtual UInt32 size() const
				{
					return sizeof(desc);
				}
				
				virtual const void* pointer() const
				{
					return &desc;
				}
			};

			mData.reset(new TSFunctionDescriptor(f));
			mData.release();
		}

		template <typename TRetType, class TypeList>
		CFunctionDescriptor(const TCBind<TRetType, TypeList>& b)
		{
			*this = b.functionDescriptor();
		}

		template <typename TRetType, class TypeList>
		CFunctionDescriptor(const TCFunction<TRetType, TypeList>& b)
		{
			*this = b.functionDescriptor();
		}

		Bool operator == (const CFunctionDescriptor& rhs) const
		{
			UInt32 mySize = mData->size();
			return mySize == rhs.mData->size() && !memcmp(mData->pointer(), rhs.mData->pointer(), mySize);
		}
};

// TODO Move TSRef2 to base
template <typename T>
struct TSRef2
{
	typedef typename TSSelect<typename TSFunctionTraits<T>::IsFunction, T, T&>::result result;
};

template <typename T>
struct TSRef2<T&>
{
	typedef T& result;
};

	} // namespace le
} // namespace sokira
