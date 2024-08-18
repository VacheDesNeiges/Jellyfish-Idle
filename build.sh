#!/bin/bash


DEBUG_MODE=false
BUILD_GAME=false
BUILD_TESTS=false

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug)
            DEBUG_MODE=true
            shift
            ;;
        --game)
            BUILD_GAME=true
            shift
            ;;
        --tests)
            BUILD_TESTS=true
            shift
            ;;
        --all)
            BUILD_TESTS=true
            BUILD_GAME=true
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

if [ "$BUILD_GAME" = false ] && [ "$BUILD_TESTS" = false ]; then
    echo "Error: you must specify at least one of --game or --tests"
    exit 1
fi

mkdir -p build
cd build

cmake_options="-G Ninja"

if [ "$DEBUG_MODE" = true ]; then
    cmake_options="$cmake_options -DDEBUG_MODE=ON"
else
    cmake_options="$cmake_options -DDEBUG_MODE=OFF"
fi

cmake $cmake_options ..

if [ "$BUILD_TESTS" = true ] && [ "$BUILD_GAME" = true ]; then
    ninja all
    mv game ../
    mv test ../
    exit 0
fi

if [ "$BUILD_GAME" = true ]; then
    ninja game
    mv game ../
fi

if [ "$BUILD_TESTS" = true ]; then
    ninja test
    mv test ../
fi
