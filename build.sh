#!/bin/bash

BUILD_TYPE="Debug"

# build
cmake --build build --config $BUILD_TYPE

# install
cmake --install build --config $BUILD_TYPE --prefix "install"
