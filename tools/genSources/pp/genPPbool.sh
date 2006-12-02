#!/bin/sh

DEFAULT_LIMITATION=255

echo '#ifndef H_slPPbool_included'
echo '#define H_slPPbool_included'
echo
echo '#include "slPPcat.h"'
echo
echo '#define LE_PP_BOOL(num) LE_PP_CAT(_LE_PP_BOOL_, num)'

if [ $# -ne 1 ]
then
	LIMITATION=$DEFAULT_LIMITATION
else
	LIMITATION=$1
fi

COUNTER=1
echo
echo
echo "#define _LE_PP_BOOL_0 0"

while [ $COUNTER -le $LIMITATION ]
do
	echo "#define _LE_PP_BOOL_$COUNTER 1"
	COUNTER=`expr $COUNTER + 1`
done

echo
echo
echo "#define LE_PP_BOOL_LIMITATION $LIMITATION"
echo
echo "#endif // H_slPPbool_included"
