#!/bin/sh

if [[ $# > 0 ]]
then
	LIMITATION=$1
else
	LIMITATION=${DEFAULT_LIMITATION:-255}
fi

HEADER_GUARD=$NAMESPACE_PREFIX\_$(echo "$FILE_PATH" | sed 's/[\\\./]/_/g')
cd "$(dirname ${0})"
SRCDEST="$(pwd)/../../../src/$FILE_PATH"

__genSource()
{
	echo "#if !defined $HEADER_GUARD"
	echo "#define $HEADER_GUARD"
	echo

	genSource

	echo
	echo "#endif // not defined $HEADER_GUARD"
}


__genSource > "$SRCDEST"
