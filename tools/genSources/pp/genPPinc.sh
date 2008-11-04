#!/bin/sh

FILE_PATH=le/core/preprocessor/slPPinc.h
NAMESPACE_PREFIX=SL_LE

genSource()
{
	cat << SOURCE_TEXT
#define LE_PP_INC(param) _LE_PP_INC(param)

#define _LE_PP_INC(x) _LE_PP_INC_##x

SOURCE_TEXT

	COUNTER=0

	while [ $COUNTER -lt $LIMITATION ]
	do
		printf "#define _LE_PP_INC_$COUNTER "
		COUNTER=$(($COUNTER + 1))
		echo "$COUNTER"
	done

	cat << SOURCE_TEXT
#define _LE_PP_INC_$COUNTER $COUNTER
	
#define LE_PP_INC_LIMITATION $LIMITATION
SOURCE_TEXT
}

. $(dirname ${0})/../genSource.sh
