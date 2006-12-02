#!/bin/sh

DEFAULT_LIMITATION=255

echo '#ifndef H_slPPdec_included'
echo '#define H_slPPdec_included'
echo
echo '#define LE_PP_DEC(param) _LE_PP_DEC(param)'
echo
echo '#define _LE_PP_DEC(x) _LE_PP_DEC_##x'
echo

if [ $# -ne 1 ]
then
	LIMITATION=$DEFAULT_LIMITATION
else
	LIMITATION=$1
fi

COUNTER=1

echo '#define _LE_PP_DEC_0 0'

while [ $COUNTER -le $LIMITATION ]
do
	echo "#define _LE_PP_DEC_$COUNTER `expr $COUNTER - 1`"
	COUNTER=`expr $COUNTER + 1`
done

echo
echo "#define LE_PP_DEC_LIMITATION $LIMITATION"
echo
echo '#endif // H_slPPdec_included'
