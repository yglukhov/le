#ifndef slPPif_h_included
#define slPPif_h_included

#include "slPPbool.h"
#include "slPPbit_if.h"

#define LE_PP_IF(cond, t, f) LE_PP_BIT_IF(LE_PP_BOOL(cond), t, f)

#define LE_PP_IF_LIMITATION LE_PP_BOOL_LIMITATION

#endif // slPPif_h_included
