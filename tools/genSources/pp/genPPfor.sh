#!/bin/sh

DEFAULT_LIMITATION=255

echo '#ifndef H_slPPfor_included'
echo '#define H_slPPfor_included'
echo
echo '// predicate - macro of type PREDICATE(current) must expand to 1 or 0'
echo '// action - macro of type ACTION(current)'
echo
echo '#include "slPPbit_if.h"'
echo
echo '#define LE_PP_FOR(initial, predicate, action) _LE_PP_FOR_(initial, predicate, action)'
echo
echo '#define _LE_PP_FOR_(initial, predicate, action) _LE_PP_FOR_##initial(predicate, action)'
echo
echo '#define _LE_PP_NOTHING'
echo
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
	echo -n "#define _LE_PP_FOR_$COUNTER(_p, _a) LE_PP_BIT_IF(_p($COUNTER), _a($COUNTER) "
	COUNTER=`expr $COUNTER + 1`
	echo "_LE_PP_FOR_$COUNTER(_p, _a), _LE_PP_NOTHING)"
done

echo "#define _LE_PP_FOR_$LIMITATION(_p, _a) LE_PP_BIT_IF(_p($LIMITATION), _a($LIMITATION), _LE_PP_NOTHING)"
echo
echo
echo "#define LE_PP_FOR_LIMITATION $LIMITATION"
echo
echo '#endif // H_slPPfor_included'
