#!/bin/sh

DOXYGEN=`which doxygen`

if [ -z "$DOXYGEN" ]
then
	DOXYGEN='/Applications/Doxygen.app/Contents/Resources/doxygen'
	if [ \! -f "$DOXYGEN" ]
	then
		echo "doxygen not found" >&2
		exit 1
	fi
fi

DIR=`dirname "$0"`
cd "$DIR/../doc"
$DOXYGEN

if [ "$1" = "--open-browser" ]
then
	open html/index.html
fi
