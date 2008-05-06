#pragma once

#include <le/core/config/slPrefix.h>

namespace sokira
{
	namespace le
	{

template <bool boolValue>
struct TSBoolToType
{

};

template <int intValue>
struct TSIntToType
{

};

template <unsigned uintValue>
struct TSUIntToType
{

};

template <typename T>
struct TSTypeToType
{

};

	} // namespace le
} // namespace sokira
