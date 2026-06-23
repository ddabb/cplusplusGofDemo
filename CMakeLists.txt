# Basic CMake for DesignPatternDemo (project root CMakeLists)
cmake_minimum_required(VERSION 3.16)

project(DesignPatternDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Resolve SRC_ROOT robustly: prefer the directory that contains both src/ and tests/
set(_candidates
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/build"
    "${CMAKE_SOURCE_DIR}/.."
)

set(SRC_ROOT "${CMAKE_SOURCE_DIR}")
foreach(_cand IN LISTS _candidates)
    if(EXISTS "${_cand}/src/creational/singleton.cpp" AND EXISTS "${_cand}/tests/run_smoke.cpp")
        set(SRC_ROOT "${_cand}")
        break()
    endif()
endforeach()

# Unified include directories for all targets
# All headers are relative to SRC_ROOT/src/ directory
include_directories(
    ${SRC_ROOT}/src            # For #include "creational/xxx.h"
)

if(BUILD_TESTS)
    enable_testing()
    # Prefer explicit files if present, otherwise fall back to discovered PROJECT_SRCS
    set(TEST_SRCS "${SRC_ROOT}/tests/run_smoke.cpp")
    if(NOT EXISTS "${SRC_ROOT}/tests/run_smoke.cpp")
        # try to find in discovered project sources
        foreach(_f IN LISTS PROJECT_SRCS)
            if(_f MATCHES "/tests/run_smoke.cpp$")
                list(APPEND TEST_SRCS ${_f})
            endif()
        endforeach()
    endif()

    add_executable(DesignPatternDemoTests ${TEST_SRCS})

    if(MSVC)
        target_compile_options(DesignPatternDemoTests PRIVATE /W4 /EHsc)
    else()
        target_compile_options(DesignPatternDemoTests PRIVATE -Wall -Wextra -pedantic)
    endif()

    add_test(NAME smoke COMMAND DesignPatternDemoTests)
endif()


# Determine main source file: prefer ${SRC_ROOT}/main_console.cpp, otherwise
# fall back to any discovered main_console.cpp in PROJECT_SRCS
set(MAIN_SRC "")
if(EXISTS "${SRC_ROOT}/main_console.cpp")
    set(MAIN_SRC "${SRC_ROOT}/main_console.cpp")
else()
    foreach(_f IN LISTS PROJECT_SRCS)
        if(_f MATCHES "/main_console.cpp$")
            set(MAIN_SRC ${_f})
            break()
        endif()
    endforeach()
endif()

if(MAIN_SRC STREQUAL "")
    message(FATAL_ERROR "Cannot locate main_console.cpp in SRC_ROOT or discovered sources. Checked: ${SRC_ROOT} and PROJECT_SRCS")
endif()

add_executable(DesignPatternDemo
    ${MAIN_SRC}
    # 注意: 目前各模式实现直接放在头文件中以便教学演示。
    # 如需优化编译时间，可将实现拆分到对应的 .cpp 文件，并仅在此处列出 .cpp。
    # Creational pattern implementations (moved to .cpp)
    ${SRC_ROOT}/src/creational/singleton.cpp
    ${SRC_ROOT}/src/creational/factory_method.cpp
    ${SRC_ROOT}/src/creational/abstract_factory.cpp
    ${SRC_ROOT}/src/creational/builder.cpp
    ${SRC_ROOT}/src/creational/prototype.cpp

    # Structural pattern implementations (moved to .cpp)
    ${SRC_ROOT}/src/structural/adapter.cpp
    ${SRC_ROOT}/src/structural/bridge.cpp
    ${SRC_ROOT}/src/structural/composite.cpp
    ${SRC_ROOT}/src/structural/decorator.cpp
    ${SRC_ROOT}/src/structural/facade.cpp
    ${SRC_ROOT}/src/structural/flyweight.cpp
    ${SRC_ROOT}/src/structural/proxy.cpp
    # Behavioral pattern implementations (moved to .cpp where applicable)
    ${SRC_ROOT}/src/behavioral/observer.cpp
    ${SRC_ROOT}/src/behavioral/template_method.cpp
    ${SRC_ROOT}/src/behavioral/strategy.cpp
    ${SRC_ROOT}/src/behavioral/chain_of_responsibility.cpp
    ${SRC_ROOT}/src/behavioral/command.cpp
    # iterator is a header-only template; don't list headers as sources
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
message(STATUS " C++设计模式示例项目 - 控制台版本")
message(STATUS "============================================")
message(STATUS "C++ Standard: C++20")
message(STATUS "SFML Dependency: None (Console Only)")
message(STATUS "============================================")