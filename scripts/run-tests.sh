#!/bin/bash

# Always expecting a clean build
if [ ! -d "build" ]; then
    echo "No build folder found."
    exit 1
fi

cmake --build build --target chip8_tests -- -j
./build/tests/chip8_tests --gtest_color=yes
