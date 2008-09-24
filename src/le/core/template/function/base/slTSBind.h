#pragma once

#include <le/core/config/slPrefix.h>
namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// bindTo - helper struct to bind a real function parameter
// to parameter at call.
template <int bindIndex>
struct bindTo
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
struct TSParamTraits<bindTo<bindIndex> >
{
	enum
	{
		bind = bindIndex // binding value toParam. -1 = no binding
	};
};


	} // namespace le
} // namespace sokira
