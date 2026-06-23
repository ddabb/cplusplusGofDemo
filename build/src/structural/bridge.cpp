#include "bridge.h"
#include <iostream>

namespace design_patterns::structural {

void bridge_demo() {
	std::cout << "\n========== Bridge Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 桥接模式核心：将抽象部分与实现部分分离，独立变化\n" << std::endl;

	std::cout << "[Demo] --- Abstraction + ImplementorA ---" << std::endl;
	std::unique_ptr<bridge::Abstraction> abstraction1 = 
		std::make_unique<bridge::Abstraction>(std::make_unique<bridge::ConcreteImplementorA>());
	abstraction1->operation("Hello Bridge");

	std::cout << std::endl;

	std::cout << "[Demo] --- Abstraction + ImplementorB ---" << std::endl;
	std::unique_ptr<bridge::Abstraction> abstraction2 = 
		std::make_unique<bridge::Abstraction>(std::make_unique<bridge::ConcreteImplementorB>());
	abstraction2->operation("Hello Bridge");

	std::cout << std::endl;

	std::cout << "[Demo] --- RefinedAbstraction + ImplementorA ---" << std::endl;
	std::unique_ptr<bridge::RefinedAbstraction> refinedAbstraction1 = 
		std::make_unique<bridge::RefinedAbstraction>(std::make_unique<bridge::ConcreteImplementorA>());
	refinedAbstraction1->operation("Hello Refined Bridge");
	refinedAbstraction1->extraOperation("Extra Data");

	std::cout << std::endl;

	std::cout << "[Demo] --- RefinedAbstraction + ImplementorB ---" << std::endl;
	std::unique_ptr<bridge::RefinedAbstraction> refinedAbstraction2 = 
		std::make_unique<bridge::RefinedAbstraction>(std::make_unique<bridge::ConcreteImplementorB>());
	refinedAbstraction2->operation("Hello Refined Bridge");
	refinedAbstraction2->extraOperation("Extra Data");

	std::cout << "==========================================\n" << std::endl;
}

}
