#pragma once
// 文件: src/structural/decorator.h
// 说明: 装饰器模式示例，展示如何动态组合功能（Coffee/Decorator）
// 建议: 演示中使用 unique_ptr 来管理装饰链，风格适合教学用途。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::structural::decorator {

/**
 * @brief 咖啡接口
 *
 * 定义咖啡的基本接口。
 */
class Coffee {
public:
    virtual ~Coffee() = default;
    /**
     * @brief 获取咖啡描述
     * @return 咖啡描述
     */
    virtual std::string getDescription() const = 0;
    /**
     * @brief 获取咖啡价格
     * @return 咖啡价格
     */
    virtual double getCost() const = 0;
};

/**
 * @brief 浓缩咖啡
 */
class Espresso : public Coffee {
public:
    std::string getDescription() const override {
        return "浓缩咖啡";
    }

    double getCost() const override {
        return 19.9;
    }
};

/**
 * @brief 美式咖啡
 */
class Americano : public Coffee {
public:
    std::string getDescription() const override {
        return "美式咖啡";
    }

    double getCost() const override {
        return 24.9;
    }
};

/**
 * @brief 咖啡装饰器基类
 *
 * 所有装饰器的基类，持有咖啡对象的引用。
 */
class CoffeeDecorator : public Coffee {
public:
    explicit CoffeeDecorator(std::unique_ptr<Coffee> coffee)
        : coffee_(std::move(coffee)) {
        std::cout << "[咖啡装饰器] 创建" << std::endl;
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

/**
 * @brief 牛奶装饰器
 */
class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(std::unique_ptr<Coffee> coffee)
        : CoffeeDecorator(std::move(coffee)) {
        std::cout << "[牛奶装饰器] 添加牛奶" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription() + " + 牛奶";
    }

    double getCost() const override {
        return coffee_->getCost() + 5.0;
    }
};

/**
 * @brief 糖装饰器
 */
class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(std::unique_ptr<Coffee> coffee)
        : CoffeeDecorator(std::move(coffee)) {
        std::cout << "[糖装饰器] 添加糖" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription() + " + 糖";
    }

    double getCost() const override {
        return coffee_->getCost() + 2.0;
    }
};

/**
 * @brief 巧克力装饰器
 */
class ChocolateDecorator : public CoffeeDecorator {
public:
    explicit ChocolateDecorator(std::unique_ptr<Coffee> coffee)
        : CoffeeDecorator(std::move(coffee)) {
        std::cout << "[巧克力装饰器] 添加巧克力" << std::endl;
    }

    std::string getDescription() const override {
        return coffee_->getDescription() + " + 巧克力";
    }

    double getCost() const override {
        return coffee_->getCost() + 7.0;
    }
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/decorator.cpp
void decorator_demo();

}
