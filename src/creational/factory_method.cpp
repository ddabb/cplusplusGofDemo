#include "creational/factory_method.h"
#include <iostream>

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
