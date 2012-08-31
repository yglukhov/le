#pragma once

#include <string.h>
#include <le/core/config/slPrefix.h>
#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/slTCPointer.h>

namespace sokira
{
	namespace le
	{

template <typename FuncType> struct TSFunctionTraits;

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
	typedef TRetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};

template <typename FuncType, class TypeList>
struct TSFunctionTraits<TCBind<FuncType, TypeList> > :
	public TSFreeFunctionCallWithTuple<
		typename TSFunctionTraits<FuncType>::RetType,
		TypeList::length>
{
	typedef typename TSFunctionTraits<FuncType>::RetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
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
				
				TSFunctionDescriptor(TFuncType f)
				{
					desc.f = f;
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

	} // namespace le
} // namespace sokira
