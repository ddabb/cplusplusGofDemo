# Basic CMake for DesignPatternDemo (project root CMakeLists)
# This CMakeLists.txt lives in the project root and is the single source of truth.
# Build artifacts (.slnx, .vcxproj, .obj, .exe) are generated into build/ via out-of-source build.
cmake_minimum_required(VERSION 3.16)

project(DesignPatternDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SRC_ROOT is the project root (where this CMakeLists.txt lives)
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

# Unified include directories for all targets
# All headers are relative to ${SRC_ROOT}/src/ directory
include_directories(
    ${SRC_ROOT}/src            # For #include "creational/xxx.h"
)

if(BUILD_TESTS)
    enable_testing()
    set(TEST_SRCS "${SRC_ROOT}/tests/run_smoke.cpp")
    add_executable(DesignPatternDemoTests ${TEST_SRCS})

    if(MSVC)
        target_compile_options(DesignPatternDemoTests PRIVATE /W4 /EHsc)
    else()
        target_compile_options(DesignPatternDemoTests PRIVATE -Wall -Wextra -pedantic)
    endif()

    add_test(NAME smoke COMMAND DesignPatternDemoTests)
endif()

add_executable(DesignPatternDemo
    ${SRC_ROOT}/main_console.cpp
    # Creational pattern implementations
    ${SRC_ROOT}/src/creational/singleton.cpp
    ${SRC_ROOT}/src/creational/factory_method.cpp
    ${SRC_ROOT}/src/creational/abstract_factory.cpp
    ${SRC_ROOT}/src/creational/builder.cpp
    ${SRC_ROOT}/src/creational/prototype.cpp
    # Structural pattern implementations
    ${SRC_ROOT}/src/structural/adapter.cpp
    ${SRC_ROOT}/src/structural/bridge.cpp
    ${SRC_ROOT}/src/structural/composite.cpp
    ${SRC_ROOT}/src/structural/decorator.cpp
    ${SRC_ROOT}/src/structural/facade.cpp
    ${SRC_ROOT}/src/structural/flyweight.cpp
    ${SRC_ROOT}/src/structural/proxy.cpp
    # Behavioral pattern implementations
    ${SRC_ROOT}/src/behavioral/observer.cpp
    ${SRC_ROOT}/src/behavioral/template_method.cpp
    ${SRC_ROOT}/src/behavioral/strategy.cpp
    ${SRC_ROOT}/src/behavioral/chain_of_responsibility.cpp
    ${SRC_ROOT}/src/behavioral/command.cpp
    ${SRC_ROOT}/src/behavioral/iterator_demo_impl.cpp
    ${SRC_ROOT}/src/behavioral/state.cpp
    ${SRC_ROOT}/src/behavioral/memento.cpp
    ${SRC_ROOT}/src/behavioral/visitor.cpp
    ${SRC_ROOT}/src/behavioral/mediator.cpp
    ${SRC_ROOT}/src/behavioral/interpreter.cpp
)

if(MSVC)
    target_compile_options(DesignPatternDemo PRIVATE /W4 /EHsc)
else()
    target_compile_options(DesignPatternDemo PRIVATE -Wall -Wextra -pedantic)
endif()

# Ensure target has explicit include paths (absolute) so compiler finds headers
target_include_directories(DesignPatternDemo PRIVATE
    ${SRC_ROOT}/src
)

message(STATUS "============================================")
message(STATUS " C++ Design Patterns Demo - Console Version")
message(STATUS "============================================")
message(STATUS "C++ Standard: C++20")
message(STATUS "SFML Dependency: None (Console Only)")
message(STATUS "============================================")