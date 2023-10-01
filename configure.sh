#!/bin/bash

BUILD_TYPE="Debug"
cmake -B build -S . -DCMAKE_BUILD_TYPE=$BUILD_TYPE
