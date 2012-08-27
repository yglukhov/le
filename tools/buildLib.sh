#!/bin/sh

PLATFORM=macos
MACOS_MIN_VERSION=10.5

if /usr/bin/defaults read /System/Library/CoreServices/SystemVersion ProductVersion | grep 10.7 > /dev/null
then
	ARCH_FLAGS="-arch i386 -arch x86_64"
else
	ARCH_FLAGS="-arch ppc -arch i386 -arch x86_64"
fi

cd "$(dirname "$0")"
LIBS_DIR=$(pwd)/../libs
cd - > /dev/null

if [ $# -ne 2 ]
then
	echo "USAGE:"
	echo "$0 codename rootDir"
	echo "codename is one of the following: jpeg, gif, ogg, vorbis, freetype"
	echo "rootDir is the directory of the library source distribution where 'configure' file resides"
	exit 1
fi

LIBRARY_NAME=$1
LIBRARY_SRC_ROOT=$2
SRC_PRODUCT_PATH=
DEST_PRODUCT_PATH=
ADDITIONAL_CONFIGURE_FLAGS=
ADDITIONAL_MAC_CONFIGURE_FLAGS=
ADDITIONAL_IOS_CONFIGURE_FLAGS=
SHARED_CONFIGURE_FLAGS="--enable-static=yes --enable-shared=no"

performBuildIos()
{
	IOS_PLATFORM=$1
	IOS_VERSION=$2
	PLATFORM_CODE=$3
	ARCH_FLAGS=$4

	PLATFORM_PATH="/Developer/Platforms/$IOS_PLATFORM.platform"
	SDK_ROOT="$PLATFORM_PATH/Developer/SDKs/$IOS_PLATFORM$IOS_VERSION.sdk"

	./configure --prefix=/usr/local/iphone --host=arm-apple-darwin $SHARED_CONFIGURE_FLAGS $ADDITIONAL_CONFIGURE_FLAGS $ADDITIONAL_IOS_CONFIGURE_FLAGS CC=$PLATFORM_PATH/Developer/usr/bin/gcc CFLAGS="$ARCH_FLAGS -pipe -mdynamic-no-pic -std=c99 -Wno-trigraphs -fpascal-strings -fasm-blocks -O0 -Wreturn-type -Wunused-variable -fmessage-length=0 -fvisibility=hidden -miphoneos-version-min=$IOS_VERSION -I$SDK_ROOT/usr/include/ -isysroot $SDK_ROOT" CPP=$PLATFORM_PATH/Developer/usr/bin/cpp AR=$PLATFORM_PATH/Developer/usr/bin/ar LDFLAGS="$ARCH_FLAGS -isysroot $SDK_ROOT -Wl,-dead_strip -miphoneos-version-min=$IOS_VERSION"
	make clean
	make

	mkdir -p "$LIBS_DIR/$DEST_PRODUCT_PATH/$PLATFORM_CODE"
	cp $SRC_PRODUCT_PATH "$LIBS_DIR/$DEST_PRODUCT_PATH/$PLATFORM_CODE/"
}

performBuild()
{
	if [ \! "$DEST_PRODUCT_PATH" ]
	then
		DEST_PRODUCT_PATH=$LIBRARY_NAME
	fi

	echo build macos
	./configure --disable-dependency-tracking $SHARED_CONFIGURE_FLAGS $ADDITIONAL_CONFIGURE_FLAGS $ADDITIONAL_MAC_CONFIGURE_FLAGS "CFLAGS=-mmacosx-version-min=$MACOS_MIN_VERSION $ARCH_FLAGS" "LDFLAGS=$ARCH_FLAGS"
	make clean
	make
	mkdir -p "$LIBS_DIR/$DEST_PRODUCT_PATH/macos"
	cp $SRC_PRODUCT_PATH "$LIBS_DIR/$DEST_PRODUCT_PATH/macos/"

	IOS_VERSION=4.0
	ARCH_FLAGS="-arch i386"
	echo build iosSimulator
	performBuildIos iPhoneSimulator $IOS_VERSION iosSimulator
	echo build ios
	ARCH_FLAGS="-arch armv7"
	performBuildIos iPhone $IOS_VERSION ios
}

buildLib_jpeg()
{
	SRC_PRODUCT_PATH=.libs/libjpeg.a
	performBuild
}

buildLib_gif()
{
	SRC_PRODUCT_PATH=lib/.libs/libgif.a
	performBuild
}

buildLib_freetype()
{
	SRC_PRODUCT_PATH=objs/.libs/libfreetype.a
	performBuild
}

buildLib_ogg()
{
	SRC_PRODUCT_PATH=src/.libs/libogg.a
	DEST_PRODUCT_PATH=vorbis
	performBuild
}

buildLib_vorbis()
{
	if [ \! -d "$LIBS_DIR/vorbis/include/ogg" ]
	then
		echo "Ogg headers not found in '$LIBS_DIR/vorbis/include/ogg'"
		exit 1
	fi

	if [ \! -f "$LIBS_DIR/vorbis/macos/libogg.a" ]
	then
		echo "Ogg library not found in '$LIBS_DIR/vorbis/macos/libogg.a'"
		exit 1
	fi

	if [ \! -f "$LIBS_DIR/vorbis/ios/libogg.a" ]
	then
		echo "Ogg library not found in '$LIBS_DIR/vorbis/ios/libogg.a'"
		exit 1
	fi

	ADDITIONAL_CONFIGURE_FLAGS="--with-ogg-includes=$LIBS_DIR/vorbis/include"
	ADDITIONAL_MAC_CONFIGURE_FLAGS="--with-ogg-libraries=$LIBS_DIR/vorbis/macos"
	ADDITIONAL_IOS_CONFIGURE_FLAGS="--with-ogg-libraries=$LIBS_DIR/vorbis/ios"
	export "SRC_PRODUCT_PATH=lib/.libs/libvorbis.a lib/.libs/libvorbisfile.a lib/.libs/libvorbisenc.a"
	performBuild
}

cd "$LIBRARY_SRC_ROOT";

buildLib_$LIBRARY_NAME
