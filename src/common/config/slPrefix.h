////////////////////////////////////////////////////////////////////////////////
//  PROJECT: le					DOCTYPE: public c/c++ header, doxygen source.
//
/// \file   common/config/slPrefix.h		Common project settings definitions.
///
/// Defines most common macros, such as LE_FLAG_DEBUG, LE_NAMESPACE,
/// LE_FLAG_UNICODE, etc.
//
//  Copyright (c) 2006 by  S.O.K.I.R.A. labs.
////////////////////////////////////////////////////////////////////////////////
#if !defined H_slPrefix_included
#define H_slPrefix_included


////////////////////////////////////////////////////////////////////////////////
#define LE_TRUE 1	///< Use this macro to turn macro flags on.
#define LE_FALSE 0	///< Use this macro to turn macro flags off.

/// Select if le project belongs to <tt>"sokira"</tt> namespace.
#define LE_FLAG_LE_IN_OWN_NAMESPACE LE_FALSE

/// Select if le project belongs to <tt>"le"</tt> namespace. If
/// \ref LE_IN_OWN_NAMESPACE is set to \ref LE_TRUE, then <tt>"le"</tt>
/// namespace will be nested in <tt>"sokira"</tt> namespace.
#define LE_FLAG_LE_IN_SOKIRA_NAMESPACE LE_FALSE


///\def SOKIRA_NAMESPACE_START
/// Used to mark the start of <tt>"sokira"</tt> namespace, if
/// \ref LE_FLAG_LE_IN_SOKIRA_NAMESPACE is set to \ref LE_TRUE.

///\def SOKIRA_NAMESPACE_END
/// Used to mark the end of <tt>"sokira"</tt> namespace, if
/// \ref LE_FLAG_LE_IN_SOKIRA_NAMESPACE is set to \ref LE_TRUE.

///\def SOKIRA_NESTED_NAMESPACE
/// Expands to <tt>"sokira::"</tt>, if \ref LE_FLAG_LE_IN_SOKIRA_NAMESPACE
/// macro is set to \ref LE_TRUE.

#if LE_FLAG_LE_IN_SOKIRA_NAMESPACE
	#define SOKIRA_NAMESPACE_START namespace sokira {
	#define SOKIRA_NAMESPACE_END };
	#define SOKIRA_NESTED_NAMESPACE sokira::
#else
	#define SOKIRA_NAMESPACE_START
	#define SOKIRA_NAMESPACE_END
	#define SOKIRA_NESTED_NAMESPACE
#endif // not LE_FLAG_LE_IN_SOKIRA_NAMESPACE

///\def LE_NAMESPACE_START
/// Used to mark the start of <tt>"le"</tt> namespace, if
/// \ref LE_FLAG_LE_IN_OWN_NAMESPACE is set to \ref LE_TRUE.

///\def LE_NAMESPACE_END
/// Used to mark the end of <tt>"le"</tt> namespace, if
/// \ref LE_FLAG_LE_IN_OWN_NAMESPACE is set to \ref LE_TRUE.

///\def LE_NESTED_NAMESPACE
/// Expands to <tt>"\ref SOKIRA_NESTED_NAMESPACE le::"</tt>,
/// if \ref LE_FLAG_LE_IN_OWN_NAMESPACE  macro is set to \ref LE_TRUE.

#if LE_FLAG_LE_IN_OWN_NAMESPACE
	#define LE_NAMESPACE_START SOKIRA_NAMESPACE_START namespace le {
	#define LE_NAMESPACE_END }; SOKIRA_NAMESPACE_END
	#define LE_NESTED_NAMESPACE SOKIRA_NESTED_NAMESPACE le::
#else
	#define LE_NAMESPACE_START SOKIRA_NAMESPACE_START
	#define LE_NAMESPACE_END SOKIRA_NAMESPACE_END
	#define LE_NESTED_NAMESPACE SOKIRA_NESTED_NAMESPACE
#endif // not LE_FLAG_LE_IN_OWN_NAMESPACE

/// This flag is set to \ref LE_TRUE when building with \b debug configuration.
#ifdef _DEBUG
#define LE_FLAG_DEBUG LE_TRUE
#else
#define LE_FLAG_DEBUG LE_FALSE
#endif // defined _DEBUG

/// Define this macro to compile as unicode sources.
#define LE_FLAG_UNICODE LE_FALSE

#define LE_PP_STRINGIZE(x) __LE_PP_STRINGIZE__(x)
#define __LE_PP_STRINGIZE__(x) #x


#endif // not defined H_slPrefix_included
////////////////////////////////////////////////////////////////////////////////
// Revision history:
////////////////////////////////////////////////////////////////////////////////
