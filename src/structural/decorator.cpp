#include "structural/decorator.h"
#include <iostream>

namespace design_patterns::structural {

/**
 * @brief 装饰器模式演示函数
 *
 * 演示装饰器模式的核心特性：动态地给对象添加额外职责。
 */
void decorator_demo() {
	std::cout << "\n========== 装饰器模式演示 ==========" << std::endl;
	std::cout << "[演示] 装饰器模式核心：动态地给对象添加额外职责\n" << std::endl;

	std::cout << "[演示] --- 基础咖啡 ---" << std::endl;
	std::unique_ptr<decorator::Coffee> espresso = std::make_unique<decorator::Espresso>();
	std::cout << "描述: " << espresso->getDescription() << std::endl;
	std::cout << "价格: ¥" << espresso->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[演示] --- 浓缩咖啡 + 牛奶 ---" << std::endl;
	std::unique_ptr<decorator::Coffee> milkCoffee = std::make_unique<decorator::MilkDecorator>(std::make_unique<decorator::Espresso>());
	std::cout << "描述: " << milkCoffee->getDescription() << std::endl;
	std::cout << "价格: ¥" << milkCoffee->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[演示] --- 浓缩咖啡 + 牛奶 + 糖 ---" << std::endl;
	std::unique_ptr<decorator::Coffee> milkSugarCoffee = 
		std::make_unique<decorator::SugarDecorator>(
			std::make_unique<decorator::MilkDecorator>(std::make_unique<decorator::Espresso>()));
	std::cout << "描述: " << milkSugarCoffee->getDescription() << std::endl;
	std::cout << "价格: ¥" << milkSugarCoffee->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[演示] --- 浓缩咖啡 + 牛奶 + 糖 + 巧克力 ---" << std::endl;
	std::unique_ptr<decorator::Coffee> fullyLoadedCoffee = 
		std::make_unique<decorator::ChocolateDecorator>(
			std::make_unique<decorator::SugarDecorator>(
				std::make_unique<decorator::MilkDecorator>(std::make_unique<decorator::Espresso>())));
	std::cout << "描述: " << fullyLoadedCoffee->getDescription() << std::endl;
	std::cout << "价格: ¥" << fullyLoadedCoffee->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[演示] --- 美式咖啡 + 巧克力 ---" << std::endl;
	std::unique_ptr<decorator::Coffee> americanoChocolate = 
		std::make_unique<decorator::ChocolateDecorator>(std::make_unique<decorator::Americano>());
	std::cout << "描述: " << americanoChocolate->getDescription() << std::endl;
	std::cout << "价格: ¥" << americanoChocolate->getCost() << std::endl;

	std::cout << "============================================\n" << std::endl;
}

}
