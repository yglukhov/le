#!/bin/sh

FILE_PATH=le/core/preprocessor/slPPbool.h
NAMESPACE_PREFIX=SL_LE

genSource()
{
	cat << SOURCE_TEXT
#include "slPPcat.h"

#define LE_PP_BOOL(num) LE_PP_CAT(_LE_PP_BOOL_, num)


#define _LE_PP_BOOL_0 0
SOURCE_TEXT

	COUNTER=1

	while [ $COUNTER -le $LIMITATION ]
	do
		echo "#define _LE_PP_BOOL_$COUNTER 1"
		COUNTER=$(($COUNTER + 1))
	done

	cat << SOURCE_TEXT


#define LE_PP_BOOL_LIMITATION $LIMITATION
SOURCE_TEXT
}

. $(dirname ${0})/../genSource.sh
