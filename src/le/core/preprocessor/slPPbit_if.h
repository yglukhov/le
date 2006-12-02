#ifndef slPPbit_if_h_included
#define slPPbit_if_h_included

#define LE_PP_BIT_IF(cond, t, f) _LE_PP_BIT_IF(cond, t, f)
#define _LE_PP_BIT_IF(bit, t, f) _LE_PP_BIT_IF_##bit(t, f)

#define _LE_PP_BIT_IF_0(t, f) f
#define _LE_PP_BIT_IF_1(t, f) t

#endif // slPPbit_if_h_included
