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
    cmake -DDEBUG_MODE=ON .. -G Ninja
else
    cmake -DDEBUG_MODE=OFF .. -G Ninja
fi


ninja

mv game ../
mv test ../

