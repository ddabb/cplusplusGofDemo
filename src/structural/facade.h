#pragma once
// 文件: src/structural/facade.h
// 说明: 外观模式示例，将复杂子系统封装为简单接口（Computer）
// 建议: 演示代码可保留，若需扩展子系统建议为每个子系统添加单元测试。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::structural::facade {

/**
 * @brief CPU 子系统
 */
class CPU {
public:
    void startup() const {
        std::cout << "[CPU] 启动 CPU..." << std::endl;
        std::cout << "[CPU] 加载 BIOS..." << std::endl;
        std::cout << "[CPU] CPU 准备就绪" << std::endl;
    }

    void shutdown() const {
        std::cout << "[CPU] 关闭 CPU..." << std::endl;
        std::cout << "[CPU] CPU 已关闭" << std::endl;
    }
};

/**
 * @brief 内存子系统
 */
class Memory {
public:
    void initialize() const {
        std::cout << "[内存] 初始化 RAM..." << std::endl;
        std::cout << "[内存] 分配内存块..." << std::endl;
        std::cout << "[内存] 内存准备就绪" << std::endl;
    }

    void release() const {
        std::cout << "[内存] 释放内存..." << std::endl;
        std::cout << "[内存] 内存已释放" << std::endl;
    }
};

/**
 * @brief 硬盘子系统
 */
class HardDrive {
public:
    void spinUp() const {
        std::cout << "[硬盘] 旋转硬盘..." << std::endl;
        std::cout << "[硬盘] 加载引导扇区..." << std::endl;
        std::cout << "[硬盘] 硬盘准备就绪" << std::endl;
    }

    void spinDown() const {
        std::cout << "[硬盘] 停止硬盘旋转..." << std::endl;
        std::cout << "[硬盘] 硬盘已关闭" << std::endl;
    }
};

/**
 * @brief 操作系统子系统
 */
class OperatingSystem {
public:
    void load() const {
        std::cout << "[操作系统] 加载操作系统..." << std::endl;
        std::cout << "[操作系统] 初始化系统服务..." << std::endl;
        std::cout << "[操作系统] 加载设备驱动..." << std::endl;
        std::cout << "[操作系统] 操作系统准备就绪" << std::endl;
    }

    void unload() const {
        std::cout << "[操作系统] 保存系统状态..." << std::endl;
        std::cout << "[操作系统] 关闭应用程序..." << std::endl;
        std::cout << "[操作系统] 操作系统已关闭" << std::endl;
    }
};

/**
 * @brief 计算机外观类
 *
 * 为复杂的计算机子系统提供统一的高层接口。
 */
class Computer {
public:
    Computer() 
        : cpu_(std::make_unique<CPU>()),
          memory_(std::make_unique<Memory>()),
          hardDrive_(std::make_unique<HardDrive>()),
          os_(std::make_unique<OperatingSystem>()) {
        std::cout << "[计算机] 计算机组装完成" << std::endl;
    }

    /**
     * @brief 启动计算机
     */
    void start() const {
        std::cout << "\n[计算机] 正在启动计算机..." << std::endl;
        
        cpu_->startup();
        memory_->initialize();
        hardDrive_->spinUp();
        os_->load();
        
        std::cout << "[计算机] 计算机启动成功！" << std::endl;
    }

    /**
     * @brief 关闭计算机
     */
    void shutdown() const {
        std::cout << "\n[计算机] 正在关闭计算机..." << std::endl;
        
        os_->unload();
        hardDrive_->spinDown();
        memory_->release();
        cpu_->shutdown();
        
        std::cout << "[计算机] 计算机关闭成功！" << std::endl;
    }

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
