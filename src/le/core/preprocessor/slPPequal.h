#ifndef slPPequal_h_included
#define slPPequal_h_included

#include "slPPbit_not.h"
#include "slPPnot_equal.h"

#define LE_PP_EQUAL(first, second) LE_PP_NOT(LE_PP_NOT_EQUAL(first, second))

#define LE_PP_EQUAL_LIMITATION LE_PP_NOT_EQUAL_LIMITATION

#endif // slPPequal_h_included
