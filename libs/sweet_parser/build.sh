#!/bin/sh
cd sweet
chmod ug+x build/build
build/build install
build/build xcodeproj
cd ..