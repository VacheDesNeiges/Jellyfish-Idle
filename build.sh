#!/bin/bash


DEBUG_MODE=false

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug)
            DEBUG_MODE=true
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

mkdir -p build
cd build


if [ "$DEBUG_MODE" = true ]; then
    cmake -DDEBUG_MODE=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
else
    cmake -DDEBUG_MODE=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
fi


make -j

mv game ../
mv test ../

