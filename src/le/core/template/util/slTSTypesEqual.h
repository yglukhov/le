#pragma once

template <typename T1, typename T2>
struct TSTypesEqual
{
	enum { result = 0 };
};

template <typename T>
struct TSTypesEqual<T, T>
{
	enum { result = 1 };
};
 