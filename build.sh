#!/usr/bin/env bash

set -e

mkdir -p build

cd build
export PKG_CONFIG_PATH="/opt/local/lib/pkgconfig:$PKG_CONFIG_PATH"
cmake -DCMAKE_CXX_COMPILER=clang++-mp-19 -DCMAKE_CXX_FLAGS="-I/opt/local/include" -DCMAKE_EXE_LINKER_FLAGS="-L/opt/local/lib -L/usr/local/lib -lcrypto -lssl" ..
make
./rest_server -c ../config.json
