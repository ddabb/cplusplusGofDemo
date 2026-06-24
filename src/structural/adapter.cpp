#include "structural/adapter.h"
#include <iostream>

namespace design_patterns::structural {

/**
 * @brief 适配器模式演示函数
 *
 * 演示适配器模式的三种变体：对象适配器、类适配器、高级适配器。
 */
void adapter_demo() {
	std::cout << "\n========== 适配器模式演示 ==========" << std::endl;
	std::cout << "[演示] 适配器模式核心：将不兼容的接口转换为兼容的接口\n" << std::endl;

	std::cout << "[演示] --- 对象适配器 ---" << std::endl;
	std::unique_ptr<adapter::Target> objectAdapter = 
		std::make_unique<adapter::ObjectAdapter>(std::make_unique<adapter::Adaptee>());
	objectAdapter->request();

	std::cout << std::endl;

	std::cout << "[演示] --- 类适配器 ---" << std::endl;
	std::unique_ptr<adapter::Target> classAdapter = std::make_unique<adapter::ClassAdapter>();
	classAdapter->request();

	std::cout << std::endl;

	std::cout << "[演示] --- 高级适配器 ---" << std::endl;
	std::unique_ptr<adapter::Target> advancedAdapter = 
		std::make_unique<adapter::AdvancedAdapter>(std::make_unique<adapter::Adaptee>());
	advancedAdapter->request();

	std::cout << "==========================================\n" << std::endl;
}

}
