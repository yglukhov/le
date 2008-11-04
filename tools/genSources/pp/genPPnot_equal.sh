#!/bin/sh

FILE_PATH=le/core/preprocessor/slPPnot_equal.h
NAMESPACE_PREFIX=SL_LE

genSource()
{
	cat << SOURCE_TEXT
#include "slPPbit_if.h"

#define LE_PP_NOT_EQUAL(first, second) _LE_PP_NOT_EQUAL(first, second)


#define _LE_PP_NOT_EQUAL(x, y) LE_PP_CAT(_LE_PP_NOT_EQUAL_CHECK_, _LE_PP_NOT_EQUAL_ ## x(0, _LE_PP_NOT_EQUAL_ ## y))

#define _LE_PP_NOT_EQUAL_CHECK_LE_PP_NIL 1

SOURCE_TEXT

	COUNTER=0
	while [ $COUNTER -le $LIMITATION ]
	do
		echo "#define _LE_PP_NOT_EQUAL_CHECK__LE_PP_NOT_EQUAL_$COUNTER(c, y) 0"
		COUNTER=$(($COUNTER + 1))
	done

	echo
	echo

	COUNTER=0
	while [ $COUNTER -le $LIMITATION ]
	do
		echo "#define _LE_PP_NOT_EQUAL_$COUNTER(c, y) LE_PP_BIT_IF(c, LE_PP_NIL, y(1, LE_PP_NIL))"
		COUNTER=$(($COUNTER + 1))
	done

	cat << SOURCE_TEXT


#define LE_PP_NOT_EQUAL_LIMITATION $LIMITATION
SOURCE_TEXT
}

. $(dirname ${0})/../genSource.sh
