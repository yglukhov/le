#!/bin/sh

LIMITATION=255

cat << SOURCE_TEXT
#ifndef H_slPPdec_included
#define H_slPPdec_included

#define LE_PP_DEC(param) _LE_PP_DEC(param)

#define _LE_PP_DEC(x) _LE_PP_DEC_##x

#define _LE_PP_DEC_0 0
SOURCE_TEXT

if [[ $# > 0 ]]
then
	LIMITATION=$1
fi

COUNTER=1

while [[ $COUNTER < $LIMITATION ]]
do
	echo "#define _LE_PP_DEC_$COUNTER $(($COUNTER - 1))"
	COUNTER=$(($COUNTER + 1))
done

cat << SOURCE_TEXT

#define LE_PP_DEC_LIMITATION $LIMITATION

#endif // H_slPPdec_included
SOURCE_TEXT
