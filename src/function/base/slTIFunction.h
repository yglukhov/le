#pragma once

#include <config/slPrefix.h>
LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
template <typename RetType, class TList, unsigned TListLength> class TIFunctionBase;


////////////////////////////////////////////////////////////////////////////////
// TIFunction class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename RetType, class TypeList>
class TIFunction :
		public TIFunctionBase<RetType, TypeList, TypeList::length>
{

};





////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _CFunctionInterfaceBase needed just for virtual destructor.
class _CFunctionInterfaceBase
{
	public:
		virtual ~_CFunctionInterfaceBase()
		{
			// no op
		}
};

////////////////////////////////////////////////////////////////////////////////
// Shortcut to make the code nicer.
#define t(index) typename TList::template TypeAt<index>::result


////////////////////////////////////////////////////////////////////////////////
// TIFunctionBase specialization. Limitations are equal to LE_PP_IFUNCTION_LIMIT
template <typename RetType, class TList>
class TIFunctionBase<RetType, TList, 0> : public _CFunctionInterfaceBase
{
	public: virtual RetType operator()() const = 0;
};

template <typename RetType, class TList>
class TIFunctionBase<RetType, TList, 1> : public _CFunctionInterfaceBase
{
	public: virtual RetType operator()(t(0)) const = 0;
};

template <typename RetType, class TList>
class TIFunctionBase<RetType, TList, 2> : public _CFunctionInterfaceBase
{
	public: virtual RetType operator()(t(0), t(1)) const = 0;
};

template <typename RetType, class TList>
class TIFunctionBase<RetType, TList, 3> : public _CFunctionInterfaceBase
{
	public: virtual RetType operator()(t(0), t(1), t(2)) const = 0;
};

#undef t

////////////////////////////////////////////////////////////////////////////////
// Maximum number of parameters for TIFunction
#define LE_PP_IFUNCTION_LIMIT 3


LE_NAMESPACE_END
