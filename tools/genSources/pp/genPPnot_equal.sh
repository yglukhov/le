#!/bin/sh

LIMITATION=255

cat << SOURCE_TEXT
#ifndef H_slPPnot_equal_included
#define H_slPPnot_equal_included

#include "slPPbit_if.h"

#define LE_PP_NOT_EQUAL(first, second) _LE_PP_NOT_EQUAL(first, second)


#define _LE_PP_NOT_EQUAL(x, y) LE_PP_CAT(_LE_PP_NOT_EQUAL_CHECK_, _LE_PP_NOT_EQUAL_ ## x(0, _LE_PP_NOT_EQUAL_ ## y))

#define _LE_PP_NOT_EQUAL_CHECK_LE_PP_NIL 1

SOURCE_TEXT

if [[ $# > 0 ]]
then
	LIMITATION=$1
fi

COUNTER=0
while [[ $COUNTER < $LIMITATION ]]
do
	echo "#define _LE_PP_NOT_EQUAL_CHECK__LE_PP_NOT_EQUAL_$COUNTER(c, y) 0"
	COUNTER=$(($COUNTER + 1))
done

echo
echo

COUNTER=0
while [[ $COUNTER < $LIMITATION ]]
do
	echo "#define _LE_PP_NOT_EQUAL_$COUNTER(c, y) LE_PP_BIT_IF(c, LE_PP_NIL, y(1, LE_PP_NIL))"
	COUNTER=$(($COUNTER + 1))
done

cat << SOURCE_TEXT


#define LE_PP_NOT_EQUAL_LIMITATION $LIMITATION

#endif // H_slPPnot_equal_included
SOURCE_TEXT
