#include "structural/facade.h"
#include <iostream>

namespace design_patterns::structural {

void facade_demo() {
	std::cout << "\n========== Facade Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 外观模式核心：为复杂子系统提供统一的高层接口\n" << std::endl;

	std::unique_ptr<facade::Computer> computer = std::make_unique<facade::Computer>();

	std::cout << "\n[Demo] --- Starting Computer ---" << std::endl;
	computer->start();

	std::cout << "\n[Demo] --- Using Computer ---" << std::endl;
	std::cout << "[User] Working on documents..." << std::endl;
	std::cout << "[User] Browsing the internet..." << std::endl;

	std::cout << "\n[Demo] --- Shutting Down Computer ---" << std::endl;
	computer->shutdown();

	std::cout << "\n==========================================\n" << std::endl;
}

}
