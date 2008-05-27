////////////////////////////////////////////////////////////////////////////////
//  PROJECT: le					DOCTYPE: public c/c++ header, doxygen source.
//
/// \file   common/types/slBasic.h			Declarations of basic types.
///
/// Contains declarations of basic types.
/// Basic types are defined to guarantee their size, independent from platform
/// and/or compiler.
//
//	Copyright (c) 2006 by  S.O.K.I.R.A. labs.
////////////////////////////////////////////////////////////////////////////////
#if !defined H_slBasic_included
#define H_slBasic_included

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <le/core/config/slCompiler.h>

namespace sokira
{
	namespace le
	{

// Type: SInt8
// 1-byte signed integer. Value range: -128 - +127
typedef signed char					SInt8;

// Type: UInt8
// 1-byte unsigned integer. Value range: 0 - +255
typedef unsigned char				UInt8;

// Type: SInt16
// 2-byte signed integer. Value range: -32768 - +32767
typedef signed short int			SInt16;

// Type: UInt16
// 2-byte unsigned integer. Value range: 0 - +65535
typedef unsigned short int			UInt16;

// Type: SInt32
// 4-byte signed integer. Value range: -2147483648 - +2147483647
typedef int							SInt32;

// Type: UInt32
// 4-byte unsigned integer. Value range: 0 - +4294967295
typedef unsigned int				UInt32;

// Type: SInt64
// 8-byte signed integer. Value range: -2^63 - +(2^63 - 1)
typedef signed long long int		SInt64;

// Type: UInt64
// 8-byte unsigned integer. Value range: 0 - +(2^64 - 1)
typedef unsigned long long int		UInt64;


// Type: Float32
// 4-byte float. 6 valuable digits.
typedef float						Float32;

// Type: Float64
// 8-byte float. 10 valuable digits.
typedef double						Float64;

// Type: Bool
// Boolean type. Values: true or false. Size is not guaranteed.
typedef bool						Bool;

// Type: NChar
// Narrow character type. Used for 1-byte encodings.
typedef char						NChar;

// Type: WChar
// Wide character type. Used for multi-byte encodings.
typedef wchar_t						WChar;


////////////////////////////////////////////////////////////////////////////////
// Platform dependent types
////////////////////////////////////////////////////////////////////////////////

// Type: SInt
// Platform dependent signed integer.
typedef int							SInt;

// Type: UInt
// Platform dependent unsigned integer
typedef unsigned int				UInt;

// Type: SIntS
// Platform dependent signed short integer
typedef short int					SIntS;

// Type: UIntS
// Platform dependent unsigned short integer
typedef unsigned short int			UIntS;

// Type: SIntL
// Platform dependent signed long integer
typedef long int			SIntL;

// Type: UIntL
// Platform dependent unsigned long integer
typedef unsigned long int			UIntL;

// Type: SIntLL
// Platform dependent signed very long integer
typedef long long int				SIntLL;

// Type: UIntLL
// Platform dependent unsigned very long integer
typedef unsigned long long int		UIntLL;

#define LE_SET_BIT(x) (1 << (x))

enum EStatus
{
	eStatusOK = 0, // Not an error
	eStatusOpenFailed
};

////////////////////////////////////////////////////////////////////////////////
#define _LE_BOOL_CAST(x) ((x)?(true):(false))

////////////////////////////////////////////////////////////////////////////////
	} // namespace le
} // namespace sokira

#endif // not defined H_slBasic_included
////////////////////////////////////////////////////////////////////////////////
// Revision history:
////////////////////////////////////////////////////////////////////////////////
