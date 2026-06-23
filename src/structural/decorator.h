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
// demo implementation moved to src/structural/decorator.cpp
void decorator_demo();

}
