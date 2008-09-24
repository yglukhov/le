#ifndef slPPcat_h_included
#define slPPcat_h_included

#include <le/core/config/slPrefix.h>

#define LE_PP_CAT(first, second) _LE_PP_CAT(first, second)

#define _LE_PP_CAT(x, y) x##y

#endif // slPPcat_h_included
