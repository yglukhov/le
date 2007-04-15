#!/bin/sh

LE_LIBRARY_NAME="$1"

# Generate a temporary file for a script.
TMP_FILE="/tmp/`uuidgen`"

while [ -e "$RESULT" ]
do
	TMP_FILE="/tmp/`uuidgen`"
done

# Generate a script to copy one file from src root to build location.
cat > "$TMP_FILE" << COPY_ONE_FILE
#!/bin/sh

DEST="$BUILD_DIR/$CONFIGURATION/le/include/le/$LE_LIBRARY_NAME/\`dirname \$1\`"

mkdir -p "\$DEST"
cp "\$1" "\$DEST"

COPY_ONE_FILE

# Make it executable
chmod +x "$TMP_FILE"

# Find all headers in src root and copy them to build location.
cd "$leSrcRoot/le/$LE_LIBRARY_NAME"

find -E . \( -not -regex ".*/\.svn(/.*)?" \) -and \( -not -regex ".*/CVS(/.*)?" \) -and \( -not \( -type f -and \( -iname "*.c*" -or -iname "*.hp" \) \) \) -and -not -type d \
	-exec "$TMP_FILE" {} \;

# Remove the script
rm "$TMP_FILE"
