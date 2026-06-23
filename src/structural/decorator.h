#pragma once
// 文件: src/structural/decorator.h
// 说明: 装饰器模式示例，展示如何动态组合功能（Coffee/Decorator）
// 建议: 演示中使用 unique_ptr 来管理装饰链，风格适合教学用途。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::structural::decorator {

class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
};

class Espresso : public Coffee {
public:
    std::string getDescription() const override {
        return "Espresso";
    }

    double getCost() const override {
        return 1.99;
    }
};

class Americano : public Coffee {
public:
    std::string getDescription() const override {
        return "Americano";
    }

    double getCost() const override {
        return 2.49;
    }
};

class CoffeeDecorator : public Coffee {
public:
    explicit CoffeeDecorator(std::unique_ptr<Coffee> coffee)
        : coffee_(std::move(coffee)) {
        std::cout << "[CoffeeDecorator] Created" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription();
    }

    double getCost() const override {
        return coffee_->getCost();
    }

protected:
    std::unique_ptr<Coffee> coffee_;
};

class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(std::unique_ptr<Coffee> coffee)
        : CoffeeDecorator(std::move(coffee)) {
        std::cout << "[MilkDecorator] Adding milk" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription() + ", Milk";
    }

    double getCost() const override {
        return coffee_->getCost() + 0.50;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(std::unique_ptr<Coffee> coffee)
        : CoffeeDecorator(std::move(coffee)) {
        std::cout << "[SugarDecorator] Adding sugar" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription() + ", Sugar";
    }

    double getCost() const override {
        return coffee_->getCost() + 0.20;
    }
};

class ChocolateDecorator : public CoffeeDecorator {
public:
    explicit ChocolateDecorator(std::unique_ptr<Coffee> coffee)
        : CoffeeDecorator(std::move(coffee)) {
        std::cout << "[ChocolateDecorator] Adding chocolate" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription() + ", Chocolate";
    }

    double getCost() const override {
        return coffee_->getCost() + 0.70;
    }
};

}

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
