
LE_LIBRARY_NAME="$1"
cd "$leSrcRoot/le"

if [ "x$2" = "x" ]
then
	DESTINATION_DIR="$BUILD_DIR/$CONFIGURATION/le/include/le"
else
	DESTINATION_DIR="$2"
fi

mkdir -p "$DESTINATION_DIR"

find -E "$LE_LIBRARY_NAME"			\
	-not							\
	\(								\
		-regex ".*/\.svn(/.*)?"		\
		-or							\
		-regex ".*/CVS(/.*)?"		\
		-or							\
		-type d						\
		-or							\
		\(							\
			-type f					\
			\(						\
				-iname "*.c*"		\
				-or					\
				-iname "*.hp"		\
				-or					\
				-iname "*.m*"		\
			\)						\
		\)							\
	\)								\
	| cpio -p -du "$DESTINATION_DIR"
