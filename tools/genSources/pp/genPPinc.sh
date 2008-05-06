#!/bin/sh

LIMITATION=255

cat << SOURCE_TEXT
#ifndef H_slPPinc_included
#define H_slPPinc_included

#define LE_PP_INC(param) _LE_PP_INC(param)

#define _LE_PP_INC(x) _LE_PP_INC_##x

SOURCE_TEXT

if [[ $# > 0 ]]
then
	LIMITATION=$1
fi

COUNTER=0

while [[ $COUNTER < $LIMITATION ]]
do
	printf "#define _LE_PP_INC_$COUNTER "
	COUNTER=$(($COUNTER + 1))
	echo "$COUNTER"
done

cat << SOURCE_TEXT

#define LE_PP_INC_LIMITATION $LIMITATION

#endif // H_slPPinc_included
SOURCE_TEXT
