#include "creational/abstract_factory.h"
#include <iostream>

namespace design_patterns::creational::abstract_factory {

std::string ProductA1::getName() const {
    return "产品 A1";
}

void ProductA1::operation() const {
    std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
}

std::string ProductA2::getName() const {
    return "产品 A2";
}

void ProductA2::operation() const {
    std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
}

std::string ProductB1::getName() const {
    return "产品 B1";
}

void ProductB1::operation() const {
    std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
}

std::string ProductB2::getName() const {
    return "产品 B2";
}

void ProductB2::operation() const {
    std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
}

std::unique_ptr<AbstractProductA> ConcreteFactory1::createProductA() const {
    std::cout << "[工厂] 创建 ProductA1" << std::endl;
    return std::make_unique<ProductA1>();
}

std::unique_ptr<AbstractProductB> ConcreteFactory1::createProductB() const {
    std::cout << "[工厂] 创建 ProductB1" << std::endl;
    return std::make_unique<ProductB1>();
}

std::unique_ptr<AbstractProductA> ConcreteFactory2::createProductA() const {
    std::cout << "[工厂] 创建 ProductA2" << std::endl;
    return std::make_unique<ProductA2>();
}

std::unique_ptr<AbstractProductB> ConcreteFactory2::createProductB() const {
    std::cout << "[工厂] 创建 ProductB2" << std::endl;
    return std::make_unique<ProductB2>();
}

}

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
