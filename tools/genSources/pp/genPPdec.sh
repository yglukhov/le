#!/bin/sh


FILE_PATH=le/core/preprocessor/slPPdec.h
NAMESPACE_PREFIX=SL_LE

genSource()
{
	cat << SOURCE_TEXT
#define LE_PP_DEC(param) _LE_PP_DEC(param)

#define _LE_PP_DEC(x) _LE_PP_DEC_##x

#define _LE_PP_DEC_0 0
SOURCE_TEXT

	COUNTER=1

	while [ $COUNTER -le $LIMITATION ]
	do
		echo "#define _LE_PP_DEC_$COUNTER $(($COUNTER - 1))"
		COUNTER=$(($COUNTER + 1))
	done

	cat << SOURCE_TEXT

#define LE_PP_DEC_LIMITATION $LIMITATION
SOURCE_TEXT
}

. $(dirname ${0})/../genSource.sh
