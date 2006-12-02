#ifndef slPPnot_h_included
#define slPPnot_h_included

#include "slPPbool.h"
#include "slPPbit_not.h"

#define LE_PP_NOT(bit) LE_PP_BIT_NOT(LE_PP_BOOL(bit))

#define LE_PP_NOT_LIMITATION LE_PP_BOOL_LIMITATION

#endif // slPPnot_h_included
