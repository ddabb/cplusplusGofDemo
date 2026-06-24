# =============================================================================
# CMakeLists.txt - C++ 设计模式演示项目
# =============================================================================
# 说明: 本文件是项目构建配置的唯一权威来源（single source of truth）。
#       项目采用"外部构建"（out-of-source build）方式，
#       所有构建产物（.slnx, .vcxproj, .obj, .exe）都会生成到 build/ 目录，
#       不会污染源码目录。
#
# 使用方法:
#   1. 在项目根目录创建 build 子目录:  mkdir build
#   2. 进入 build 目录:                cd build
#   3. 生成构建文件:                    cmake ..
#   4. 编译项目:                        cmake --build . --config Release
# =============================================================================

# 要求 CMake 最低版本为 3.16（支持 C++20 所需的现代特性）
cmake_minimum_required(VERSION 3.16)

# 定义项目名称
project(DesignPatternDemo)

# 设置 C++ 标准为 C++20（如果编译器不支持则报错）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的输出目录为 build/bin/
# 避免与 .vcxproj 等构建文件混在一起
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SRC_ROOT 表示项目根目录（即本 CMakeLists.txt 所在目录）
# 使用 CMAKE_CURRENT_SOURCE_DIR 获取当前 CMakeLists.txt 的绝对路径
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

# 统一的头文件搜索路径
# 所有头文件都使用相对 src/ 的路径，例如：#include "creational/singleton.h"
include_directories(
    ${SRC_ROOT}/src            # 编译器会到 src/ 目录下查找头文件
)

# =============================================================================
# 测试程序构建（可选，默认开启）
# =============================================================================
if(BUILD_TESTS)
    # 启用 CTest 测试功能
    enable_testing()
    # 设置测试程序的源文件
    set(TEST_SRCS "${SRC_ROOT}/tests/run_smoke.cpp")
    # 创建测试可执行文件
    add_executable(DesignPatternDemoTests ${TEST_SRCS})

    # 根据不同编译器设置编译选项
    if(MSVC)
        # Windows MSVC 编译器选项
        # /W4    - 警告级别 4（较高）
        # /EHsc  - 标准 C++ 异常处理模型
        target_compile_options(DesignPatternDemoTests PRIVATE /W4 /EHsc)
    else()
        # Linux/Mac GCC/Clang 编译器选项
        # -Wall      - 打开所有常见警告
        # -Wextra    - 打开额外警告
        # -pedantic  - 严格遵循 ISO C++ 标准
        target_compile_options(DesignPatternDemoTests PRIVATE -Wall -Wextra -pedantic)
    endif()

    # 注册一个名为 "smoke" 的测试，运行 `ctest` 时会自动执行
    add_test(NAME smoke COMMAND DesignPatternDemoTests)
endif()

# =============================================================================
# 主程序构建 - 包含 23 种 GoF 设计模式
# =============================================================================
add_executable(DesignPatternDemo
    ${SRC_ROOT}/main_console.cpp
    # ---------- 创建型模式（5 种） ----------
    ${SRC_ROOT}/src/creational/singleton.cpp          # 单例模式
    ${SRC_ROOT}/src/creational/factory_method.cpp     # 工厂方法模式
    ${SRC_ROOT}/src/creational/abstract_factory.cpp   # 抽象工厂模式
    ${SRC_ROOT}/src/creational/builder.cpp            # 建造者模式
    ${SRC_ROOT}/src/creational/prototype.cpp          # 原型模式
    # ---------- 结构型模式（7 种） ----------
    ${SRC_ROOT}/src/structural/adapter.cpp            # 适配器模式
    ${SRC_ROOT}/src/structural/bridge.cpp             # 桥接模式
    ${SRC_ROOT}/src/structural/composite.cpp          # 组合模式
    ${SRC_ROOT}/src/structural/decorator.cpp          # 装饰器模式
    ${SRC_ROOT}/src/structural/facade.cpp             # 外观模式
    ${SRC_ROOT}/src/structural/flyweight.cpp          # 享元模式
    ${SRC_ROOT}/src/structural/proxy.cpp              # 代理模式
    # ---------- 行为型模式（11 种） ----------
    ${SRC_ROOT}/src/behavioral/observer.cpp           # 观察者模式
    ${SRC_ROOT}/src/behavioral/template_method.cpp    # 模板方法模式
    ${SRC_ROOT}/src/behavioral/strategy.cpp           # 策略模式
    ${SRC_ROOT}/src/behavioral/chain_of_responsibility.cpp  # 责任链模式
    ${SRC_ROOT}/src/behavioral/command.cpp            # 命令模式
    ${SRC_ROOT}/src/behavioral/iterator_demo_impl.cpp # 迭代器模式
    ${SRC_ROOT}/src/behavioral/state.cpp              # 状态模式
    ${SRC_ROOT}/src/behavioral/memento.cpp            # 备忘录模式
    ${SRC_ROOT}/src/behavioral/visitor.cpp            # 访问者模式
    ${SRC_ROOT}/src/behavioral/mediator.cpp           # 中介者模式
    ${SRC_ROOT}/src/behavioral/interpreter.cpp        # 解释器模式
)

# 为可执行文件设置编译选项
if(MSVC)
    target_compile_options(DesignPatternDemo PRIVATE /W4 /EHsc /utf-8)
    # /utf-8: 告诉 MSVC 编译器将源文件视为 UTF-8 编码（解决中文注释乱码问题）
else()
    target_compile_options(DesignPatternDemo PRIVATE -Wall -Wextra -pedantic)
endif()

# 为可执行文件显式设置头文件搜索路径（与全局 include_directories 重复保险）
target_include_directories(DesignPatternDemo PRIVATE
    ${SRC_ROOT}/src
)

# =============================================================================
# 配置完成提示信息
# =============================================================================
message(STATUS "============================================")
message(STATUS "  C++ 设计模式演示项目 - 控制台版本")
message(STATUS "============================================")
message(STATUS "C++ 标准: C++20")
message(STATUS "包含模式: 23 种经典 GoF 设计模式")
message(STATUS "图形依赖: 无（纯控制台程序）")
message(STATUS "============================================")