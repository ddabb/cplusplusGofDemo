#include "structural/facade.h"
#include <iostream>

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
