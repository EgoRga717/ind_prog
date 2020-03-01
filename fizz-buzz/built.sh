#!/bin/sh
CXX_COMPILER_FLAGS="-Wall -Wextra -pedantic -std=c++17"
c++ $CXX_COMPILER_FLAGS solution.cpp -o prog