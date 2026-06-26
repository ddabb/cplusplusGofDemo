#pragma once
// 文件: src/structural/facade.h
// 说明: 外观模式示例，将复杂子系统封装为简单接口（Computer）
// 建议: 演示代码可保留，若需扩展子系统建议为每个子系统添加单元测试。

#include <memory>
#include <string>

namespace design_patterns::structural::facade {

/**
 * @brief CPU 子系统
 */
class CPU {
public:
    void startup() const;
    void shutdown() const;
};

/**
 * @brief 内存子系统
 */
class Memory {
public:
    void initialize() const;
    void release() const;
};

/**
 * @brief 硬盘子系统
 */
class HardDrive {
public:
    void spinUp() const;
    void spinDown() const;
};

/**
 * @brief 操作系统子系统
 */
class OperatingSystem {
public:
    void load() const;
    void unload() const;
};

/**
 * @brief 计算机外观类
 *
 * 为复杂的计算机子系统提供统一的高层接口。
 */
class Computer {
public:
    Computer();

    /**
     * @brief 启动计算机
     */
    void start() const;

    /**
     * @brief 关闭计算机
     */
    void shutdown() const;

private:
    std::unique_ptr<CPU> cpu_;
    std::unique_ptr<Memory> memory_;
    std::unique_ptr<HardDrive> hardDrive_;
    std::unique_ptr<OperatingSystem> os_;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/facade.cpp
void facade_demo();

}
