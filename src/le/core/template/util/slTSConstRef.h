#pragma once

#include "slTSSelect.h"

namespace sokira
{
	namespace le
	{

template <typename T>
struct TSConstRef
{
	typedef typename TSSelect<(sizeof(T) > sizeof(const T&)), const T&, const T>::result result;
};

	} // namespace le
} // namespace sokira

/*
template <typename T>
struct TSConstRef<const T&>
{
	typedef const T& result;
};

template <typename T>
struct TSConstRef<T*>
{
	typedef const T* result;
};

template <typename T>
struct TS

*/