#!/bin/bash

apt-get update
apt-get install -y g++ build-essential libgtest-dev cmake
cd /usr/src/gtest
cmake CMakeLists.txt
make

# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
cp *.a /usr/lib
ldconfig
