#pragma once
// 文件: src/creational/abstract_factory.h
// 说明: 抽象工厂模式示例实现（包含产品与工厂实现及 demo 函数）。
// 建议: 演示代码可以保留在头文件，但若需生产级库应将实现移到 .cpp 文件以减少编译耦合。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::creational::abstract_factory {

/**
 * @brief 抽象产品 A
 */
class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual std::string getName() const = 0;
    virtual void operation() const = 0;
};

/**
 * @brief 抽象产品 B
 */
class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual std::string getName() const = 0;
    virtual void operation() const = 0;
};

/**
 * @brief 具体产品 A1
 */
class ProductA1 : public AbstractProductA {
public:
    std::string getName() const override {
        return "产品 A1";
    }

    void operation() const override {
        std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
    }
};

/**
 * @brief 具体产品 A2
 */
class ProductA2 : public AbstractProductA {
public:
    std::string getName() const override {
        return "产品 A2";
    }

    void operation() const override {
        std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
    }
};

/**
 * @brief 具体产品 B1
 */
class ProductB1 : public AbstractProductB {
public:
    std::string getName() const override {
        return "产品 B1";
    }

    void operation() const override {
        std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
    }
};

/**
 * @brief 具体产品 B2
 */
class ProductB2 : public AbstractProductB {
public:
    std::string getName() const override {
        return "产品 B2";
    }

    void operation() const override {
        std::cout << "[产品] " << getName() << " 正在执行操作" << std::endl;
    }
};

/**
 * @brief 抽象工厂接口
 *
 * 定义创建一系列相关产品的接口。
 */
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
};

/**
 * @brief 具体工厂 1
 *
 * 创建产品族 1（ProductA1 + ProductB1）。
 */
class ConcreteFactory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        std::cout << "[工厂] 创建 ProductA1" << std::endl;
        return std::make_unique<ProductA1>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        std::cout << "[工厂] 创建 ProductB1" << std::endl;
        return std::make_unique<ProductB1>();
    }
};

/**
 * @brief 具体工厂 2
 *
 * 创建产品族 2（ProductA2 + ProductB2）。
 */
class ConcreteFactory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        std::cout << "[工厂] 创建 ProductA2" << std::endl;
        return std::make_unique<ProductA2>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        std::cout << "[工厂] 创建 ProductB2" << std::endl;
        return std::make_unique<ProductB2>();
    }
};

}

namespace design_patterns::creational {

// 声明: abstract_factory_demo 的实现已移至 src/creational/abstract_factory.cpp
void abstract_factory_demo();

}
