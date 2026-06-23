#include "structural/decorator.h"
#include <iostream>

namespace design_patterns::structural {

void decorator_demo() {
	std::cout << "\n========== Decorator Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 装饰器模式核心：动态地给对象添加额外职责\n" << std::endl;

	std::cout << "[Demo] --- Basic Coffee ---" << std::endl;
	std::unique_ptr<decorator::Coffee> espresso = std::make_unique<decorator::Espresso>();
	std::cout << "Description: " << espresso->getDescription() << std::endl;
	std::cout << "Cost: $" << espresso->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[Demo] --- Espresso + Milk ---" << std::endl;
	std::unique_ptr<decorator::Coffee> milkCoffee = std::make_unique<decorator::MilkDecorator>(std::make_unique<decorator::Espresso>());
	std::cout << "Description: " << milkCoffee->getDescription() << std::endl;
	std::cout << "Cost: $" << milkCoffee->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[Demo] --- Espresso + Milk + Sugar ---" << std::endl;
	std::unique_ptr<decorator::Coffee> milkSugarCoffee = 
		std::make_unique<decorator::SugarDecorator>(
			std::make_unique<decorator::MilkDecorator>(std::make_unique<decorator::Espresso>()));
	std::cout << "Description: " << milkSugarCoffee->getDescription() << std::endl;
	std::cout << "Cost: $" << milkSugarCoffee->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[Demo] --- Espresso + Milk + Sugar + Chocolate ---" << std::endl;
	std::unique_ptr<decorator::Coffee> fullyLoadedCoffee = 
		std::make_unique<decorator::ChocolateDecorator>(
			std::make_unique<decorator::SugarDecorator>(
				std::make_unique<decorator::MilkDecorator>(std::make_unique<decorator::Espresso>())));
	std::cout << "Description: " << fullyLoadedCoffee->getDescription() << std::endl;
	std::cout << "Cost: $" << fullyLoadedCoffee->getCost() << std::endl;

	std::cout << std::endl;

	std::cout << "[Demo] --- Americano + Chocolate ---" << std::endl;
	std::unique_ptr<decorator::Coffee> americanoChocolate = 
		std::make_unique<decorator::ChocolateDecorator>(std::make_unique<decorator::Americano>());
	std::cout << "Description: " << americanoChocolate->getDescription() << std::endl;
	std::cout << "Cost: $" << americanoChocolate->getCost() << std::endl;

	std::cout << "============================================\n" << std::endl;
}

}
