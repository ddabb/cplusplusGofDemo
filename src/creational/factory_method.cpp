#include "creational/factory_method.h"
#include <iostream>

namespace design_patterns::creational::factory_method {

std::string ConcreteProductA::getName() const {
    return "产品 A";
}

void ConcreteProductA::use() const {
    std::cout << "[产品] 正在使用 " << getName() << std::endl;
}

std::string ConcreteProductB::getName() const {
    return "产品 B";
}

void ConcreteProductB::use() const {
    std::cout << "[产品] 正在使用 " << getName() << std::endl;
}

void Creator::anOperation() const {
    std::unique_ptr<Product> product = factoryMethod();
    std::cout << "[创造者] 创建了: " << product->getName() << std::endl;
    product->use();
}

std::unique_ptr<Product> ConcreteCreatorA::factoryMethod() const {
    std::cout << "[创造者] 创建 ConcreteProductA" << std::endl;
    return std::make_unique<ConcreteProductA>();
}

std::unique_ptr<Product> ConcreteCreatorB::factoryMethod() const {
    std::cout << "[创造者] 创建 ConcreteProductB" << std::endl;
    return std::make_unique<ConcreteProductB>();
}

}

namespace design_patterns::creational {

/**
 * @brief 工厂方法模式演示函数
 *
 * 演示工厂方法模式的核心特性：定义创建对象的接口，由子类决定实例化哪个类。
 */
void factory_method_demo() {
	std::cout << "\n========== 工厂方法模式演示 ==========" << std::endl;

	std::unique_ptr<factory_method::Creator> creatorA = std::make_unique<factory_method::ConcreteCreatorA>();
	creatorA->anOperation();

	std::cout << std::endl;

	std::unique_ptr<factory_method::Creator> creatorB = std::make_unique<factory_method::ConcreteCreatorB>();
	creatorB->anOperation();

	std::cout << "===========================================\n" << std::endl;
}

}
