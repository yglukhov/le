#!/bin/sh

DEFAULT_LIMITATION=255

cat << SOURCE_TEXT
#ifndef H_slPPbool_included
#define H_slPPbool_included

#include "slPPcat.h"

#define LE_PP_BOOL(num) LE_PP_CAT(_LE_PP_BOOL_, num)


#define _LE_PP_BOOL_0 0
SOURCE_TEXT

if [[ $# > 0 ]]
then
	LIMITATION=$1
fi

COUNTER=1

while [[ $COUNTER < $LIMITATION ]]
do
	echo "#define _LE_PP_BOOL_$COUNTER 1"
	COUNTER=$(($COUNTER + 1))
done


cat << SOURCE_TEXT


#define LE_PP_BOOL_LIMITATION $LIMITATION

#endif // H_slPPbool_included
SOURCE_TEXT
