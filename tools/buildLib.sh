#!/bin/sh

PLATFORM=macos
MACOS_MIN_VERSION=10.5
ARCH_FLAGS="-arch ppc -arch i386 -arch x86_64"

cd "$(dirname "$0")"
LIBS_DIR=$(pwd)/../libs
cd -

buildLibJpeg()
{
	cd "$1";
	export CFLAGS="-mmacosx-version-min=$MACOS_MIN_VERSION $ARCH_FLAGS"
	export LDFLAGS="$ARCH_FLAGS"
	./configure --disable-dependency-tracking
	make clean
	make
	cp .libs/libgif.a "$LIBS_DIR/gif/$PLATFORM/"
}

buildLibGif()
{
	cd "$1";
	export CFLAGS="-mmacosx-version-min=$MACOS_MIN_VERSION $ARCH_FLAGS"
	export LDFLAGS="$ARCH_FLAGS"
	./configure --disable-dependency-tracking
	make clean
	make
	cp lib/.libs/libgif.a "$LIBS_DIR/gif/$PLATFORM/"
}

buildLibGif "$1"
