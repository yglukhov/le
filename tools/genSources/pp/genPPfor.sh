#!/bin/sh

LIMITATION=255

cat << SOURCE_TEXT
#ifndef H_slPPfor_included
#define H_slPPfor_included

// predicate - macro of type PREDICATE(current) must expand to 1 or 0
// action - macro of type ACTION(current)

#include "slPPbit_if.h"

#define LE_PP_FOR(initial, predicate, action) _LE_PP_FOR_(initial, predicate, action)

#define _LE_PP_FOR_(initial, predicate, action) _LE_PP_FOR_##initial(predicate, action)

#define _LE_PP_NOTHING

SOURCE_TEXT

if [[ $# > 0 ]]
then
	LIMITATION=$1
fi

COUNTER=0

while [[ $COUNTER < $LIMITATION ]]
do
	printf "#define _LE_PP_FOR_$COUNTER(_p, _a) LE_PP_BIT_IF(_p($COUNTER), _a($COUNTER) "
	COUNTER=$(($COUNTER + 1))
	echo "_LE_PP_FOR_$COUNTER(_p, _a), _LE_PP_NOTHING)"
done

cat << SOURCE_TEXT
#define _LE_PP_FOR_$COUNTER(_p, _a) LE_PP_BIT_IF(_p($COUNTER), _a($COUNTER), _LE_PP_NOTHING)


#define LE_PP_FOR_LIMITATION $LIMITATION

#endif // H_slPPfor_included
SOURCE_TEXT
