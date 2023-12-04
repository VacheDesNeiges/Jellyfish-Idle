cmake_minimum_required(VERSION 3.22.1)
project(JellyfishIdle)

set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
-Wall \
-Wextra \
-pedantic \
-Wshadow \
-Wconversion \
-O3 \
-fPIC \
-g \
-fprofile-instr-generate=build/default.profraw \
-fcoverage-mapping")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}\
-lgtest \
-lpthread \
-lstdc++ \
-lm \
-lSDL2 \
-lfmt")

    include_directories(
        ${CMAKE_SOURCE_DIR}/../
        ${CMAKE_SOURCE_DIR}/imgui/
        ${CMAKE_SOURCE_DIR}/imgui/backends/
        ${CMAKE_SOURCE_DIR}/src/UI
        ${CMAKE_SOURCE_DIR}/src/Ressources
        ${CMAKE_SOURCE_DIR}/src/GameData
        ${CMAKE_SOURCE_DIR}/src/Buildings
        ${CMAKE_SOURCE_DIR}/src/Jellyfishs
        ${CMAKE_SOURCE_DIR}/src/Abilities
    )
    
# Source files for your main application
file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/imgui/*.cpp)
list(FILTER SRCS EXCLUDE REGEX "Main.cpp|TestsMain.cpp")

# Specify the build directory
set(BUILD_DIR ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${BUILD_DIR})

add_executable(game ${SRCS} ${CMAKE_SOURCE_DIR}/src/Main.cpp)
target_link_libraries(game ${CMAKE_EXE_LINKER_FLAGS})
set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)

# Source files for your tests
file(GLOB_RECURSE TEST_SRCS ${CMAKE_SOURCE_DIR}/tests/*.cpp)
list(FILTER TEST_SRCS EXCLUDE REGEX "Main.cpp|TestsMain.cpp")

# Specify the test build directory
set(TEST_BUILD_DIR ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${TEST_BUILD_DIR})

add_executable(test ${TEST_SRCS} ${SRCS} ${CMAKE_SOURCE_DIR}/tests/TestsMain.cpp)
target_link_libraries(test ${CMAKE_EXE_LINKER_FLAGS})
set_target_properties(test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_BUILD_DIR}
)
    
    
    # Custom target for coverage
add_custom_target(coverage
    COMMAND llvm-profdata merge -o build/default.profdata build/default.profraw
    COMMAND llvm-cov show --show-branches=count --instr-profile=build/default.profdata $<TARGET_FILE:test> > build/coverage.txt
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)