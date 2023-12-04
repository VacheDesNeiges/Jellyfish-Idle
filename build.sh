#!/bin/bash

mkdir -p build
cd build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

make -j

mv game ../
mv test ../

