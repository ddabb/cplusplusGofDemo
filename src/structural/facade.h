#pragma once
// 文件: src/structural/facade.h
// 说明: 外观模式示例，将复杂子系统封装为简单接口（Computer）
// 建议: 演示代码可保留，若需扩展子系统建议为每个子系统添加单元测试。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::structural::facade {

class CPU {
public:
    void startup() const {
        std::cout << "[CPU] Starting CPU..." << std::endl;
        std::cout << "[CPU] Loading BIOS..." << std::endl;
        std::cout << "[CPU] CPU Ready" << std::endl;
    }

    void shutdown() const {
        std::cout << "[CPU] Shutting down CPU..." << std::endl;
        std::cout << "[CPU] CPU Off" << std::endl;
    }
};

class Memory {
public:
    void initialize() const {
        std::cout << "[Memory] Initializing RAM..." << std::endl;
        std::cout << "[Memory] Allocating memory blocks..." << std::endl;
        std::cout << "[Memory] Memory Ready" << std::endl;
    }

    void release() const {
        std::cout << "[Memory] Releasing memory..." << std::endl;
        std::cout << "[Memory] Memory Released" << std::endl;
    }
};

class HardDrive {
public:
    void spinUp() const {
        std::cout << "[HardDrive] Spinning up hard drive..." << std::endl;
        std::cout << "[HardDrive] Loading boot sector..." << std::endl;
        std::cout << "[HardDrive] Hard Drive Ready" << std::endl;
    }

    void spinDown() const {
        std::cout << "[HardDrive] Spinning down hard drive..." << std::endl;
        std::cout << "[HardDrive] Hard Drive Off" << std::endl;
    }
};

class OperatingSystem {
public:
    void load() const {
        std::cout << "[OS] Loading operating system..." << std::endl;
        std::cout << "[OS] Initializing system services..." << std::endl;
        std::cout << "[OS] Loading device drivers..." << std::endl;
        std::cout << "[OS] Operating System Ready" << std::endl;
    }

    void unload() const {
        std::cout << "[OS] Saving system state..." << std::endl;
        std::cout << "[OS] Closing applications..." << std::endl;
        std::cout << "[OS] Operating System Closed" << std::endl;
    }
};

class Computer {
public:
    Computer() 
        : cpu_(std::make_unique<CPU>()),
          memory_(std::make_unique<Memory>()),
          hardDrive_(std::make_unique<HardDrive>()),
          os_(std::make_unique<OperatingSystem>()) {
        std::cout << "[Computer] Computer assembled" << std::endl;
    }

    void start() const {
        std::cout << "\n[Computer] Starting computer..." << std::endl;
        
        cpu_->startup();
        memory_->initialize();
        hardDrive_->spinUp();
        os_->load();
        
        std::cout << "[Computer] Computer started successfully!" << std::endl;
    }

    void shutdown() const {
        std::cout << "\n[Computer] Shutting down computer..." << std::endl;
        
        os_->unload();
        hardDrive_->spinDown();
        memory_->release();
        cpu_->shutdown();
        
        std::cout << "[Computer] Computer shut down successfully!" << std::endl;
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
