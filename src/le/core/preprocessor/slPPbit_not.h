#ifndef slPPbit_not_h_included
#define slPPbit_not_h_included

#include "slPPcat.h"

#define LE_PP_BIT_NOT(bit) LE_PP_CAT(_LE_PP_BIT_NOT_, bit)

#define _LE_PP_BIT_NOT_0 1
#define _LE_PP_BIT_NOT_1 0

#endif // slPPbit_not_h_included
