#include <iostream>

#include "../src/creational/singleton.h"
#include "../src/creational/factory_method.h"
#include "../src/structural/adapter.h"
#include "../src/behavioral/observer.h"

int main() {
	std::cout << "Running smoke tests..." << std::endl;

	// 调用少量 demo 函数以验证链接/运行
	design_patterns::creational::singleton_demo();
	design_patterns::creational::factory_method_demo();
	design_patterns::structural::adapter_demo();
	design_patterns::behavioral::observer_demo();

	std::cout << "Smoke tests completed." << std::endl;
	return 0;
}
