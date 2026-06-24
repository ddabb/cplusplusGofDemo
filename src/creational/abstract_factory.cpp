#include "creational/abstract_factory.h"
#include <iostream>

namespace design_patterns::creational {

/**
 * @brief 抽象工厂模式演示函数
 *
 * 演示抽象工厂模式的核心特性：创建一系列相关或相互依赖的对象族。
 */
void abstract_factory_demo() {
	std::cout << "\n========== 抽象工厂模式演示 ==========" << std::endl;

	std::unique_ptr<abstract_factory::AbstractFactory> factory1 = std::make_unique<abstract_factory::ConcreteFactory1>();
	std::unique_ptr<abstract_factory::AbstractProductA> productA1 = factory1->createProductA();
	std::unique_ptr<abstract_factory::AbstractProductB> productB1 = factory1->createProductB();
	productA1->operation();
	productB1->operation();

	std::cout << std::endl;

	std::unique_ptr<abstract_factory::AbstractFactory> factory2 = std::make_unique<abstract_factory::ConcreteFactory2>();
	std::unique_ptr<abstract_factory::AbstractProductA> productA2 = factory2->createProductA();
	std::unique_ptr<abstract_factory::AbstractProductB> productB2 = factory2->createProductB();
	productA2->operation();
	productB2->operation();

	std::cout << "=============================================\n" << std::endl;
}

}
