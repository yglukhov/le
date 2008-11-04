#!/bin/sh

FILE_PATH=le/core/preprocessor/slPPfor.h
NAMESPACE_PREFIX=SL_LE

genSource()
{
	cat << SOURCE_TEXT
// predicate - macro of type PREDICATE(current) must expand to 1 or 0
// action - macro of type ACTION(current)

#include "slPPbit_if.h"

#define LE_PP_FOR(initial, predicate, action) _LE_PP_FOR_(initial, predicate, action)

#define _LE_PP_FOR_(initial, predicate, action) _LE_PP_FOR_##initial(predicate, action)

#define _LE_PP_NOTHING

SOURCE_TEXT

	COUNTER=0

	while [ $COUNTER -lt $LIMITATION ]
	do
		printf "#define _LE_PP_FOR_$COUNTER(_p, _a) LE_PP_BIT_IF(_p($COUNTER), _a($COUNTER) "
		COUNTER=$(($COUNTER + 1))
		echo "_LE_PP_FOR_$COUNTER(_p, _a), _LE_PP_NOTHING)"
	done

	cat << SOURCE_TEXT
#define _LE_PP_FOR_$COUNTER(_p, _a) LE_PP_BIT_IF(_p($COUNTER), _a($COUNTER), _LE_PP_NOTHING)


#define LE_PP_FOR_LIMITATION $LIMITATION
SOURCE_TEXT
}

. $(dirname ${0})/../genSource.sh
