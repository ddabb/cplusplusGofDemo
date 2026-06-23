#include "factory_method.h"
#include <iostream>

namespace design_patterns::creational {

void factory_method_demo() {
	std::cout << "\n========== Factory Method Pattern Demo ==========" << std::endl;

	std::unique_ptr<factory_method::Creator> creatorA = std::make_unique<factory_method::ConcreteCreatorA>();
	creatorA->anOperation();

	std::cout << std::endl;

	std::unique_ptr<factory_method::Creator> creatorB = std::make_unique<factory_method::ConcreteCreatorB>();
	creatorB->anOperation();

	std::cout << "=================================================\n" << std::endl;
}

}
