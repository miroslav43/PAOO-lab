#!/bin/bash

echo " Cleaning build directory..."
rm -rf build

mkdir -p build/bin

echo " Configuring with CMake..."
cmake -B build

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

echo " Building project..."
cmake --build build

if [ $? -ne 0 ]; then
    echo " Build failed!"
    exit 1
fi

echo " Build complete! Run: ./build/bin/StartupAccelerator"

