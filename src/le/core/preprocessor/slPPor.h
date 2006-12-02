#ifndef slPPor_h_included
#define slPPor_h_included

#include "slPPbit_or.h"
#include "slPPbool.h"

#define LE_PP_OR(first, second) LE_PP_BIT_OR(LE_PP_BOOL(first), LE_PP_BOOL(second))

#define LE_PP_OR_LIMITATION LE_PP_BOOL_LIMITATION

#endif // slPPor_h_included
