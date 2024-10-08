cmake_minimum_required(VERSION 3.22.1)
project(JellyfishIdle)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
-Wall \
-Wextra \
-pedantic \
-Wshadow \
-Wconversion \
-fPIE")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(DEBUG_MODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

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
    ${CMAKE_SOURCE_DIR}/src/Achievements
    ${CMAKE_SOURCE_DIR}/src/Upgrades
    ${CMAKE_SOURCE_DIR}/src/Crafting
    ${CMAKE_SOURCE_DIR}/src/Multipliers
    ${CMAKE_SOURCE_DIR}/src/Depth
    ${CMAKE_SOURCE_DIR}/src/Garden
    ${CMAKE_SOURCE_DIR}/src/Quests
    ${CMAKE_SOURCE_DIR}/src/BackendRenderer
)


file(GLOB_RECURSE TEST_SRCS
    ${CMAKE_SOURCE_DIR}/tests/*.cpp
    ${CMAKE_SOURCE_DIR}/tests/jsonTests/*.cpp)
list(FILTER TEST_SRCS EXCLUDE REGEX "Main.cpp|TestsMain.cpp")

set(TEST_BUILD_DIR ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${TEST_BUILD_DIR})



file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/imgui/*.cpp)
list(FILTER SRCS EXCLUDE REGEX "Main.cpp|TestsMain.cpp")

file(GLOB_RECURSE IMGUI_DIR "imgui/*.c*" "imgui/*.h*")
set_source_files_properties(${IMGUI_DIR} PROPERTIES COMPILE_FLAGS "-w")

set(BUILD_DIR ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${BUILD_DIR})



add_executable(test ${TEST_SRCS} ${SRCS} ${CMAKE_SOURCE_DIR}/tests/TestsMain.cpp)
target_link_libraries(test ${CMAKE_EXE_LINKER_FLAGS})
set_target_properties(test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_BUILD_DIR})



add_executable(game ${SRCS} ${CMAKE_SOURCE_DIR}/src/Main.cpp)
target_link_libraries(game ${CMAKE_EXE_LINKER_FLAGS})
set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)
