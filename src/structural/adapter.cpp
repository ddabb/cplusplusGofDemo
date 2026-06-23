#include "structural/adapter.h"
#include <iostream>

namespace design_patterns::structural {

void adapter_demo() {
	std::cout << "\n========== Adapter Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 适配器模式核心：将不兼容的接口转换为兼容的接口\n" << std::endl;

	std::cout << "[Demo] --- Object Adapter ---" << std::endl;
	std::unique_ptr<adapter::Target> objectAdapter = 
		std::make_unique<adapter::ObjectAdapter>(std::make_unique<adapter::Adaptee>());
	objectAdapter->request();

	std::cout << std::endl;

	std::cout << "[Demo] --- Class Adapter ---" << std::endl;
	std::unique_ptr<adapter::Target> classAdapter = std::make_unique<adapter::ClassAdapter>();
	classAdapter->request();

	std::cout << std::endl;

	std::cout << "[Demo] --- Advanced Adapter ---" << std::endl;
	std::unique_ptr<adapter::Target> advancedAdapter = 
		std::make_unique<adapter::AdvancedAdapter>(std::make_unique<adapter::Adaptee>());
	advancedAdapter->request();

	std::cout << "==========================================\n" << std::endl;
}

}
