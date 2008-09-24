#ifndef slPPbit_and_h_included
#define slPPbit_and_h_included

#include <le/core/config/slPrefix.h>

#define LE_PP_BIT_AND(first, second) _LE_PP_BIT_AND(first, second)


#define _LE_PP_BIT_AND(f, s) _LE_PP_BIT_AND_##f##s

#define _LE_PP_BIT_AND_00 0
#define _LE_PP_BIT_AND_10 0
#define _LE_PP_BIT_AND_01 0
#define _LE_PP_BIT_AND_11 1

#endif // slPPbit_and_h_included
