#ifndef slPPbit_xor_h_included
#define slPPbit_xor_h_included

#define LE_PP_BIT_XOR(first, second) _LE_PP_BIT_XOR(first, second)


#define _LE_PP_BIT_XOR(f, s) _LE_PP_BIT_XOR_##f##s

#define _LE_PP_BIT_XOR_00 0
#define _LE_PP_BIT_XOR_10 1
#define _LE_PP_BIT_XOR_01 1
#define _LE_PP_BIT_XOR_11 0

#endif // slPPbit_xor_h_included
