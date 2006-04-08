#pragma once

////////////////////////////////////////////////////////////////////////////////
// TSBindToIndexedParam - helper struct to bind a real function parameter
// to parameter at call.
template <int bindIndex>
struct TSBindToIndexedParam
{

};


////////////////////////////////////////////////////////////////////////////////
// Param traits
template <typename T>
struct TSParamTraits
{
	enum
	{
		bind = -1 // binding value toParam. -1 = no binding
	};
};

template <int bindIndex>
struct TSParamTraits<TSBindToIndexedParam<bindIndex> >
{
	enum
	{
		bind = bindIndex // binding value toParam. -1 = no binding
	};
};
