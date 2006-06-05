#pragma once

#include <common/config/slPrefix.h>

LE_NAMESPACE_START

typedef signed char					SInt1;
typedef unsigned char				UInt1;

typedef signed short int			SInt2;
typedef unsigned short int			UInt2;

typedef signed long int				SInt4;
typedef unsigned long int			UInt4;

typedef signed long long int		SInt8;
typedef unsigned long long int	UInt8;


typedef float							Float4;
typedef double							Float8;


typedef bool							Bool;


typedef char							NChar;
typedef wchar_t						WChar;

#if !defined LE_UNICODE
typedef NChar							Char;
#else
typedef WChar							Char;
#endif // defined LE_UNICODE

LE_NAMESPACE_END
