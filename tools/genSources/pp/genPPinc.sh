#!/bin/sh

DEFAULT_LIMITATION=255

echo '#ifndef H_slPPinc_included'
echo '#define H_slPPinc_included'
echo
echo '#define LE_PP_INC(param) _LE_PP_INC(param)'
echo
echo '#define _LE_PP_INC(x) _LE_PP_INC_##x'
echo

if [ $# -ne 1 ]
then
	LIMITATION=$DEFAULT_LIMITATION
else
	LIMITATION=$1
fi

COUNTER=0

while [ $COUNTER -le $LIMITATION ]
do
	echo -n "#define _LE_PP_INC_$COUNTER "
	COUNTER=`expr $COUNTER + 1`
	echo "$COUNTER"
done

echo
echo "#define LE_PP_INC_LIMITATION $LIMITATION"
echo
echo '#endif // H_slPPinc_included'
