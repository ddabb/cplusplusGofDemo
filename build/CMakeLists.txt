cmake_minimum_required(VERSION 3.16)

project(DesignPatternDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJ_ROOT "${CMAKE_SOURCE_DIR}/..")

include_directories(
	${PROJ_ROOT}
)

# Option to build tests
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
	enable_testing()
	add_executable(DesignPatternDemoTests
		${PROJ_ROOT}/tests/run_smoke.cpp
		${PROJ_ROOT}/src/creational/singleton.h
		${PROJ_ROOT}/src/creational/factory_method.h
		${PROJ_ROOT}/src/structural/adapter.h
		${PROJ_ROOT}/src/behavioral/observer.h
	)

	if(MSVC)
		target_compile_options(DesignPatternDemoTests PRIVATE /W4 /EHsc)
	else()
		target_compile_options(DesignPatternDemoTests PRIVATE -Wall -Wextra -pedantic)
	endif()

	add_test(NAME smoke COMMAND DesignPatternDemoTests)
endif()


add_executable(DesignPatternDemo
	${PROJ_ROOT}/main_console.cpp
	# Creational pattern implementations (moved to .cpp)
	${PROJ_ROOT}/src/creational/singleton.cpp
	${PROJ_ROOT}/src/creational/factory_method.cpp
	${PROJ_ROOT}/src/creational/abstract_factory.cpp
	${PROJ_ROOT}/src/creational/builder.cpp
	${PROJ_ROOT}/src/creational/prototype.cpp

	# Structural pattern implementations (moved to .cpp)
	${PROJ_ROOT}/src/structural/adapter.cpp
	${PROJ_ROOT}/src/structural/bridge.cpp
	${PROJ_ROOT}/src/structural/composite.cpp
	${PROJ_ROOT}/src/structural/decorator.cpp
	${PROJ_ROOT}/src/structural/facade.cpp
	${PROJ_ROOT}/src/structural/flyweight.cpp
	${PROJ_ROOT}/src/structural/proxy.cpp
	# Behavioral pattern implementations (moved to .cpp where applicable)
	${PROJ_ROOT}/src/behavioral/observer.cpp
	${PROJ_ROOT}/src/behavioral/template_method.cpp
	${PROJ_ROOT}/src/behavioral/strategy.cpp
	${PROJ_ROOT}/src/behavioral/chain_of_responsibility.cpp
	${PROJ_ROOT}/src/behavioral/command.cpp
	# iterator is a header-only template; keep as header
	${PROJ_ROOT}/src/behavioral/iterator.h
	${PROJ_ROOT}/src/behavioral/iterator_demo_impl.cpp
	${PROJ_ROOT}/src/behavioral/state.cpp
	${PROJ_ROOT}/src/behavioral/memento.cpp
	${PROJ_ROOT}/src/behavioral/visitor.cpp
	${PROJ_ROOT}/src/behavioral/mediator.cpp
	${PROJ_ROOT}/src/behavioral/interpreter.cpp
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
