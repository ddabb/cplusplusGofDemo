#include "structural/facade.h"
#include <iostream>

namespace design_patterns::structural::facade {

void CPU::startup() const {
    std::cout << "[CPU] 启动 CPU..." << std::endl;
    std::cout << "[CPU] 加载 BIOS..." << std::endl;
    std::cout << "[CPU] CPU 准备就绪" << std::endl;
}

void CPU::shutdown() const {
    std::cout << "[CPU] 关闭 CPU..." << std::endl;
    std::cout << "[CPU] CPU 已关闭" << std::endl;
}

void Memory::initialize() const {
    std::cout << "[内存] 初始化 RAM..." << std::endl;
    std::cout << "[内存] 分配内存块..." << std::endl;
    std::cout << "[内存] 内存准备就绪" << std::endl;
}

void Memory::release() const {
    std::cout << "[内存] 释放内存..." << std::endl;
    std::cout << "[内存] 内存已释放" << std::endl;
}

void HardDrive::spinUp() const {
    std::cout << "[硬盘] 旋转硬盘..." << std::endl;
    std::cout << "[硬盘] 加载引导扇区..." << std::endl;
    std::cout << "[硬盘] 硬盘准备就绪" << std::endl;
}

void HardDrive::spinDown() const {
    std::cout << "[硬盘] 停止硬盘旋转..." << std::endl;
    std::cout << "[硬盘] 硬盘已关闭" << std::endl;
}

void OperatingSystem::load() const {
    std::cout << "[操作系统] 加载操作系统..." << std::endl;
    std::cout << "[操作系统] 初始化系统服务..." << std::endl;
    std::cout << "[操作系统] 加载设备驱动..." << std::endl;
    std::cout << "[操作系统] 操作系统准备就绪" << std::endl;
}

void OperatingSystem::unload() const {
    std::cout << "[操作系统] 保存系统状态..." << std::endl;
    std::cout << "[操作系统] 关闭应用程序..." << std::endl;
    std::cout << "[操作系统] 操作系统已关闭" << std::endl;
}

Computer::Computer() 
    : cpu_(std::make_unique<CPU>()),
      memory_(std::make_unique<Memory>()),
      hardDrive_(std::make_unique<HardDrive>()),
      os_(std::make_unique<OperatingSystem>()) {
    std::cout << "[计算机] 计算机组装完成" << std::endl;
}

void Computer::start() const {
    std::cout << "\n[计算机] 正在启动计算机..." << std::endl;
    
    cpu_->startup();
    memory_->initialize();
    hardDrive_->spinUp();
    os_->load();
    
    std::cout << "[计算机] 计算机启动成功！" << std::endl;
}

void Computer::shutdown() const {
    std::cout << "\n[计算机] 正在关闭计算机..." << std::endl;
    
    os_->unload();
    hardDrive_->spinDown();
    memory_->release();
    cpu_->shutdown();
    
    std::cout << "[计算机] 计算机关闭成功！" << std::endl;
}

}

namespace design_patterns::structural {

/**
 * @brief 外观模式演示函数
 *
 * 演示外观模式的核心特性：为复杂子系统提供统一的高层接口。
 */
void facade_demo() {
	std::cout << "\n========== 外观模式演示 ==========" << std::endl;
	std::cout << "[演示] 外观模式核心：为复杂子系统提供统一的高层接口\n" << std::endl;

	std::unique_ptr<facade::Computer> computer = std::make_unique<facade::Computer>();

	std::cout << "\n[演示] --- 启动计算机 ---" << std::endl;
	computer->start();

	std::cout << "\n[演示] --- 使用计算机 ---" << std::endl;
	std::cout << "[用户] 处理文档..." << std::endl;
	std::cout << "[用户] 浏览网页..." << std::endl;

	std::cout << "\n[演示] --- 关闭计算机 ---" << std::endl;
	computer->shutdown();

	std::cout << "\n==========================================\n" << std::endl;
}

}
