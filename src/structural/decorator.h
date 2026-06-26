#pragma once
// 文件: src/structural/decorator.h
// 说明: 装饰器模式示例，展示如何动态组合功能（Coffee/Decorator）
// 建议: 演示中使用 unique_ptr 来管理装饰链，风格适合教学用途。

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
    std::string getDescription() const override;
    double getCost() const override;
};

/**
 * @brief 美式咖啡
 */
class Americano : public Coffee {
public:
    std::string getDescription() const override;
    double getCost() const override;
};

/**
 * @brief 咖啡装饰器基类
 *
 * 所有装饰器的基类，持有咖啡对象的引用。
 */
class CoffeeDecorator : public Coffee {
public:
    explicit CoffeeDecorator(std::unique_ptr<Coffee> coffee);
    std::string getDescription() const override;
    double getCost() const override;

protected:
    std::unique_ptr<Coffee> coffee_;
};

/**
 * @brief 牛奶装饰器
 */
class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(std::unique_ptr<Coffee> coffee);
    std::string getDescription() const override;
    double getCost() const override;
};

/**
 * @brief 糖装饰器
 */
class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(std::unique_ptr<Coffee> coffee);
    std::string getDescription() const override;
    double getCost() const override;
};

/**
 * @brief 巧克力装饰器
 */
class ChocolateDecorator : public CoffeeDecorator {
public:
    explicit ChocolateDecorator(std::unique_ptr<Coffee> coffee);
    std::string getDescription() const override;
    double getCost() const override;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/decorator.cpp
void decorator_demo();

}
