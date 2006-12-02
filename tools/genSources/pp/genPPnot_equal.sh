#!/bin/sh

DEFAULT_LIMITATION=255

echo '#ifndef H_slPPnot_equal_included'
echo '#define H_slPPnot_equal_included'
echo
echo '#include "slPPbit_if.h"'
echo
echo '#define LE_PP_NOT_EQUAL(first, second) _LE_PP_NOT_EQUAL(first, second)'
echo
echo
echo '#define _LE_PP_NOT_EQUAL(x, y) LE_PP_CAT(_LE_PP_NOT_EQUAL_CHECK_, _LE_PP_NOT_EQUAL_ ## x(0, _LE_PP_NOT_EQUAL_ ## y))'
echo
echo '#define _LE_PP_NOT_EQUAL_CHECK_LE_PP_NIL 1'
echo


if [ $# -ne 1 ]
then
	LIMITATION=$DEFAULT_LIMITATION
else
	LIMITATION=$1
fi

COUNTER=0
while [ $COUNTER -le $LIMITATION ]
do
	echo "#define _LE_PP_NOT_EQUAL_CHECK__LE_PP_NOT_EQUAL_$COUNTER(c, y) 0"
	COUNTER=`expr $COUNTER + 1`
done

echo
echo

COUNTER=0
while [ $COUNTER -le $LIMITATION ]
do
	echo "#define _LE_PP_NOT_EQUAL_$COUNTER(c, y) LE_PP_BIT_IF(c, LE_PP_NIL, y(1, LE_PP_NIL))"
	COUNTER=`expr $COUNTER + 1`
done

echo
echo
echo "#define LE_PP_NOT_EQUAL_LIMITATION $LIMITATION"
echo
echo '#endif // H_slPPnot_equal_included'
