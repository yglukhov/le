#pragma once

#include "slTSSelect.h"

LE_NAMESPACE_START

template <typename T>
struct TSConstRef
{
	typedef typename TSSelect<(sizeof(T) > sizeof(const T&)), const T&, const T>::result result;
};

LE_NAMESPACE_END

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