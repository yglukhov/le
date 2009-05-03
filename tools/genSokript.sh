#!/bin/sh

SOKRIPT_BASE_SOURCE_DIR="$leSrcRoot/le/core/script/base"

BISON_FILE_NAME=slCSokriptBisonParser
LEXER_FILE_NAME=slCSokriptFlexLexer

BISON_CP="$SOKRIPT_BASE_SOURCE_DIR/$BISON_FILE_NAME.cp"
BISON_HP="$SOKRIPT_BASE_SOURCE_DIR/$BISON_FILE_NAME.hp"
BISON_YY="$SOKRIPT_BASE_SOURCE_DIR/$BISON_FILE_NAME.yy"

LEXER_LL="$SOKRIPT_BASE_SOURCE_DIR/$LEXER_FILE_NAME.ll"
LEXER_CP="$SOKRIPT_BASE_SOURCE_DIR/$LEXER_FILE_NAME.cp"

log_bison_error()
{
	while read STRING
	do
		# Produce an XCode friendly message
		LINE_NO=`expr "$STRING" : ".*:\(.*\)\..*:.*"`
		MESSAGE=`expr "$STRING" : ".*:.*:\(.*\)"`
		echo "$BISON_YY:$LINE_NO:$MESSAGE"
	done
}

if [	\( \! -e "$BISON_CP" \) -o		\
		\( \! -e "$BISON_HP" \) -o		\
		"$BISON_YY" -nt "$BISON_HP"	-o	\
		"$BISON_YY" -nt "$BISON_CP"	]
then
	if ! ERROR_STRING=`bison "--output-file=$BISON_CP" "$BISON_YY" 2>&1`
	then
		echo $ERROR_STRING | log_bison_error
		exit 1
	fi
fi


if [ \! -e "$LEXER_CP" -o				\
	"$LEXER_LL" -nt "$LEXER_CP" ]
then
	echo Running flex
	flex "--outfile=$LEXER_CP" "$LEXER_LL"
fi
