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
#include <common/config/slPrefix.h>

LE_NAMESPACE_START
////////////////////////////////////////////////////////////////////////////////

/// 1-byte signed integer. Value range: <tt>-128 - +127</tt>
typedef signed char					SInt1;
/// 1-byte unsigned integer. Value range: <tt>0 - +255</tt>
typedef unsigned char				UInt1;

/// 2-byte signed integer. Value range: <tt>-32768 - +32767</tt>
typedef signed short int			SInt2;
/// 2-byte unsigned integer. Value range: <tt>0 - +65535</tt>
typedef unsigned short int			UInt2;

/// 4-byte signed integer. Value range: <tt>-2147483648 - +2147483647</tt>
typedef signed long int				SInt4;
/// 4-byte unsigned integer. Value range: <tt>0 - +4294967295</tt>
typedef unsigned long int			UInt4;

/// 8-byte signed integer. Value range: <tt>-2^63 - +(2^63 - 1)</tt>
typedef signed long long int		SInt8;
/// 8-byte unsigned integer. Value range: <tt>0 - +(2^64 - 1)</tt>
typedef unsigned long long int		UInt8;

/// 4-byte float. 6 valuable digits.
typedef float						Float4;
/// 8-byte float. 10 valuable digits.
typedef double						Float8;

/// Boolean type. Values: \c true or \c false. Size is not guaranteed.
typedef bool						Bool;

/// Narrow character type. Used for 1-byte encodings. It is not recommended
/// to use this type, when \ref Char can be used instead.
typedef char						NChar;
/// Wide character type. Used for multi-byte encodings. It is not
/// recommended to use this type, when \ref Char can be used instead.
typedef wchar_t						WChar;

/// Character type (narrow or wide), depending on \ref LE_FLAG_UNICODE macro.
#if LE_FLAG_UNICODE
typedef WChar						Char;
#else
typedef NChar						Char;
#endif // defined LE_FLAG_UNICODE

////////////////////////////////////////////////////////////////////////////////
LE_NAMESPACE_END

#endif // not defined H_slBasic_included
////////////////////////////////////////////////////////////////////////////////
// Revision history:
////////////////////////////////////////////////////////////////////////////////
