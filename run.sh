#!/bin/bash

BUILD_TYPE="Debug"
if [[ "$1" == "--release" ]]; then
    BUILD_TYPE="Release"
fi

# Compile shaders
shaders/compile.sh

# Build
cmake -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build

# Run
build/VulkanTest
