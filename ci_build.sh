#!/usr/bin/env bash
export CC=$(which clang)
export CXX=$(which clang++)

cd build
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG ..
cmake --build .

valgrind test/raytracerchallenge-test
