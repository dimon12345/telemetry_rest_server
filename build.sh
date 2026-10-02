#!/usr/bin/env bash

set -e

mkdir -p build

cmake -B build
cmake --build build

if [ -z "$DISABLE_START_SERVER" ] || [ "$DISABLE_START_SERVER" == "0" ]; then
    build/rest_server
fi
