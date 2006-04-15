#pragma once

#include <config/slPrefix.h>
LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// TSSelect utility struct to select 1 of 2 types depending on bool.
template <bool, typename T, typename F>
struct TSSelect
{
	typedef T result;
};

template <typename T, typename F>
struct TSSelect<false, T, F>
{
	typedef F result;
};


LE_NAMESPACE_END
