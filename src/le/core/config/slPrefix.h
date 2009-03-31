////////////////////////////////////////////////////////////////////////////////
//  PROJECT: le					DOCTYPE: public c/c++ header, doxygen source.
//
/// \file   common/config/slPrefix.h		Common project settings definitions.
///
/// Defines most common macros, such as LE_FLAG_DEBUG, LE_FLAG_UNICODE, etc.
//
//  Copyright (c) 2008 by  S.O.K.I.R.A. labs.
////////////////////////////////////////////////////////////////////////////////
#if !defined H_slPrefix_included
#define H_slPrefix_included


////////////////////////////////////////////////////////////////////////////////
#define LE_TRUE 1	///< Use this macro to turn macro flags on.
#define LE_FALSE 0	///< Use this macro to turn macro flags off.


/// This flag is set to \ref LE_TRUE when building with \b debug configuration.
#ifdef _DEBUG
#define LE_FLAG_DEBUG LE_TRUE
#else
#define LE_FLAG_DEBUG LE_FALSE
#endif // defined _DEBUG

#define LE_PP_STRINGIZE(x) __LE_PP_STRINGIZE__(x)
#define __LE_PP_STRINGIZE__(x) #x


////////////////////////////////////////////////////////////////////////////////
// Module linkage workaround
////////////////////////////////////////////////////////////////////////////////
#define _LE_DEFINE_LINK_MODULE_STRUCt(module)								\
struct _le_module_lnk_workaraound_##module									\
{																			\
	_le_module_lnk_workaraound_##module();									\
};

#define LE_DEFINE_LINK_MODULE(module)										\
_LE_DEFINE_LINK_MODULE_STRUCt(module)										\
_le_module_lnk_workaraound_##module::_le_module_lnk_workaraound_##module()	\
{																			\
}

#define LE_LINK_MODULE_DEPENDENCY(module)									\
_LE_DEFINE_LINK_MODULE_STRUCt(module)										\
static const _le_module_lnk_workaraound_##module _le_module_lnk_workaraound_##module##_;

#endif // not defined H_slPrefix_included
////////////////////////////////////////////////////////////////////////////////
// Revision history:
////////////////////////////////////////////////////////////////////////////////
