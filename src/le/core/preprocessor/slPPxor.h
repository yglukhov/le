#ifndef slPPxor_h_included
#define slPPxor_h_included

#include "slPPbit_xor.h"
#include "slPPbool.h"

#define LE_PP_XOR(first, second) LE_PP_BIT_XOR(LE_PP_BOOL(first), LE_PP_BOOL(second))

#define LE_PP_XOR_LIMITATION LE_PP_BOOL_LIMITATION

#endif // slPPxor_h_included
