#!/bin/bash

BUILD_TYPE="Debug"

test -d build || mkdir build
cd build

# build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../source
cmake --build . --config $BUILD_TYPE

# install
cmake --install . --config $BUILD_TYPE --prefix "../install"

cd ..