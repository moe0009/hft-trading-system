#!/bin/bash
# build.sh
# author: mohammad bazrouk
# script to build the hft trading system using cmake

set -e

echo "starting build process..."
mkdir -p build && cd build
cmake ..
make -j$(nproc)
echo "build completed successfully."
