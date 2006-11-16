#pragma once

#include <common/config/slPrefix.h>
LE_NAMESPACE_START

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

LE_NAMESPACE_END
