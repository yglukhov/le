#ifndef slPPbit_or_h_included
#define slPPbit_or_h_included

#include <le/core/config/slPrefix.h>

#define LE_PP_BIT_OR(first, second) _LE_PP_BIT_OR(first, second)


#define _LE_PP_BIT_OR(f, s) _LE_PP_BIT_OR_##f##s

#define _LE_PP_BIT_OR_00 0
#define _LE_PP_BIT_OR_10 1
#define _LE_PP_BIT_OR_01 1
#define _LE_PP_BIT_OR_11 1

#endif // slPPbit_or_h_included
