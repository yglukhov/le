#pragma once

#include <config/slPrefix.h>
#include "slTIFunction.h"
#include "slTSFunctionTraits.h"

LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
template <typename RetType, class TypeList, unsigned paramCount, typename FuncType>
class TCFreeFunctionBase;

////////////////////////////////////////////////////////////////////////////////
// TCFreeFunction class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename FunctionType, typename RetType = typename TSFunctionTraits<FunctionType>::RetType,
						typename ParamList = typename TSFunctionTraits<FunctionType>::ParamList>
class TCFreeFunction :
	public TCFreeFunctionBase<RetType, ParamList, ParamList::length, FunctionType>
{
	public:
		inline TCFreeFunction(FunctionType func) :
			TCFreeFunctionBase<RetType, ParamList, ParamList::length, FunctionType>(func)
		{

		}
};






////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Shortcuts to make the code nicer.
#define f_declare_start(paramCount)										\
template <typename RetType, class TypeList, typename FuncType>			\
class TCFreeFunctionBase <RetType, TypeList, paramCount, FuncType> :	\
	public TIFunction<RetType, TypeList>								\
{																		\
	protected:															\
		FuncType mFunction;												\
		inline TCFreeFunctionBase(FuncType func) : mFunction(func)		\
		{																\
																		\
		}																\
																		\
	public:																\
		RetType operator()

#define t_declare
#define p_declare			const										\
		{																\
			return mFunction

#define f_declare_end													\
										;								\
		}																\
};


#define p(index) param##index
#define t(index) typename TypeList::template TypeAt<index>::result p(index)

////////////////////////////////////////////////////////////////////////////////
// TCFreeFunctionBase specialization. Limitations are equal to LE_PP_FREEFUNCTION_LIMIT
f_declare_start(0)
t_declare()
p_declare()
f_declare_end;

f_declare_start(1)
t_declare(t(0))
p_declare(p(0))
f_declare_end;

f_declare_start(2)
t_declare(t(0), t(1))
p_declare(p(0), p(1))
f_declare_end;

f_declare_start(3)
t_declare(t(0), t(1), t(2))
p_declare(p(0), p(1), p(2))
f_declare_end;

f_declare_start(4)
t_declare(t(0), t(1), t(2), t(3))
p_declare(p(0), p(1), p(2), p(3))
f_declare_end;

#undef f_declare_start
#undef t_declare
#undef p_declare
#undef f_declare_end
#undef p
#undef t

////////////////////////////////////////////////////////////////////////////////
// Maximum number of parameters for TCFreeFunction
#define LE_PP_FREEFUNCTION_LIMIT 4


LE_NAMESPACE_END
