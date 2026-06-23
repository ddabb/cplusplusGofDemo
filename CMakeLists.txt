cmake_minimum_required(VERSION 3.16)

project(DesignPatternDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

# Option to build tests
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_executable(DesignPatternDemoTests
        tests/run_smoke.cpp
        src/creational/singleton.h
        src/creational/factory_method.h
        src/structural/adapter.h
        src/behavioral/observer.h
    )

    if(MSVC)
        target_compile_options(DesignPatternDemoTests PRIVATE /W4 /EHsc)
    else()
        target_compile_options(DesignPatternDemoTests PRIVATE -Wall -Wextra -pedantic)
    endif()

    add_test(NAME smoke COMMAND DesignPatternDemoTests)
endif()


add_executable(DesignPatternDemo
    main_console.cpp
    # 注意: 目前各模式实现直接放在头文件中以便教学演示。
    # 如需优化编译时间，可将实现拆分到对应的 .cpp 文件，并仅在此处列出 .cpp。
    # Creational pattern implementations (moved to .cpp)
    src/creational/singleton.cpp
    src/creational/factory_method.cpp
    src/creational/abstract_factory.cpp
    src/creational/builder.cpp
    src/creational/prototype.cpp

    src/structural/adapter.h
    src/structural/bridge.h
    src/structural/composite.h
    src/structural/decorator.h
    src/structural/facade.h
    src/structural/flyweight.h
    src/structural/proxy.h

    src/behavioral/observer.h
    src/behavioral/template_method.h
    src/behavioral/strategy.h
    src/behavioral/chain_of_responsibility.h
    src/behavioral/command.h
    src/behavioral/iterator.h
    src/behavioral/state.h
    src/behavioral/memento.h
    src/behavioral/visitor.h
    src/behavioral/mediator.h
    src/behavioral/interpreter.h
)

if(MSVC)
    target_compile_options(DesignPatternDemo PRIVATE /W4 /EHsc)
else()
    target_compile_options(DesignPatternDemo PRIVATE -Wall -Wextra -pedantic)
endif()

message(STATUS "============================================")
message(STATUS " C++设计模式示例项目 - 控制台版本")
message(STATUS "============================================")
message(STATUS "C++ Standard: C++20")
message(STATUS "SFML Dependency: None (Console Only)")
message(STATUS "============================================")