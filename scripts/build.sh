#!/bin/bash


# Arguments
while getopts b:t: flag
do
    case "${flag}" in
        b) CMAKE_BUILD_TYPE=${OPTARG};;
        t) TARGET=${OPTARG};;
    esac
done

if [ ! -v CMAKE_BUILD_TYPE ]; then
    echo "You need to supply a build type!"
    exit 1
elif [ ! -v TARGET ]; then
    echo "You need to supply a target!"
    exit 1
fi

# Always expecting a clean build
if [ -d "build" ]; then
    rm -r build
fi

mkdir build
cmake . -Bbuild -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
cmake --build build --target "${TARGET}" -- -j
