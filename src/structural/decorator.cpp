#include "structural/decorator.h"
#include <iostream>

namespace design_patterns::structural::decorator {

std::string Espresso::getDescription() const {
    return "浓缩咖啡";
}

double Espresso::getCost() const {
    return 19.9;
}

std::string Americano::getDescription() const {
    return "美式咖啡";
}

double Americano::getCost() const {
    return 24.9;
}

CoffeeDecorator::CoffeeDecorator(std::unique_ptr<Coffee> coffee)
    : coffee_(std::move(coffee)) {
    std::cout << "[咖啡装饰器] 创建" << std::endl;
}

std::string CoffeeDecorator::getDescription() const {
    return coffee_->getDescription();
}

double CoffeeDecorator::getCost() const {
    return coffee_->getCost();
}

MilkDecorator::MilkDecorator(std::unique_ptr<Coffee> coffee)
    : CoffeeDecorator(std::move(coffee)) {
    std::cout << "[牛奶装饰器] 添加牛奶" << std::endl;
}

std::string MilkDecorator::getDescription() const {
    return coffee_->getDescription() + " + 牛奶";
}

double MilkDecorator::getCost() const {
    return coffee_->getCost() + 5.0;
}

SugarDecorator::SugarDecorator(std::unique_ptr<Coffee> coffee)
    : CoffeeDecorator(std::move(coffee)) {
    std::cout << "[糖装饰器] 添加糖" << std::endl;
}

std::string SugarDecorator::getDescription() const {
    return coffee_->getDescription() + " + 糖";
}

double SugarDecorator::getCost() const {
    return coffee_->getCost() + 2.0;
}

ChocolateDecorator::ChocolateDecorator(std::unique_ptr<Coffee> coffee)
    : CoffeeDecorator(std::move(coffee)) {
    std::cout << "[巧克力装饰器] 添加巧克力" << std::endl;
}

std::string ChocolateDecorator::getDescription() const {
    return coffee_->getDescription() + " + 巧克力";
}

double ChocolateDecorator::getCost() const {
    return coffee_->getCost() + 7.0;
}

}

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
