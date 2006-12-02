#ifndef slPPand_h_included
#define slPPand_h_included

#include "slPPbit_and.h"
#include "slPPbool.h"

#define LE_PP_AND(first, second) LE_PP_BIT_AND(LE_PP_BOOL(first), LE_PP_BOOL(second))

#define LE_PP_AND_LIMITATION LE_PP_BOOL_LIMITATION

#endif // slPPand_h_included
