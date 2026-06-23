#pragma once
// 文件: src/creational/abstract_factory.h
// 说明: 抽象工厂模式示例实现（包含产品与工厂实现及 demo 函数）。
// 建议: 演示代码可以保留在头文件，但若需生产级库应将实现移到 .cpp 文件以减少编译耦合。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::creational::abstract_factory {

class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual std::string getName() const = 0;
    virtual void operation() const = 0;
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual std::string getName() const = 0;
    virtual void operation() const = 0;
};

class ProductA1 : public AbstractProductA {
public:
    std::string getName() const override {
        return "Product A1";
    }

    void operation() const override {
        std::cout << "[Product] " << getName() << " doing operation" << std::endl;
    }
};

class ProductA2 : public AbstractProductA {
public:
    std::string getName() const override {
        return "Product A2";
    }

    void operation() const override {
        std::cout << "[Product] " << getName() << " doing operation" << std::endl;
    }
};

class ProductB1 : public AbstractProductB {
public:
    std::string getName() const override {
        return "Product B1";
    }

    void operation() const override {
        std::cout << "[Product] " << getName() << " doing operation" << std::endl;
    }
};

class ProductB2 : public AbstractProductB {
public:
    std::string getName() const override {
        return "Product B2";
    }

    void operation() const override {
        std::cout << "[Product] " << getName() << " doing operation" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        std::cout << "[Factory] Creating ProductA1" << std::endl;
        return std::make_unique<ProductA1>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        std::cout << "[Factory] Creating ProductB1" << std::endl;
        return std::make_unique<ProductB1>();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        std::cout << "[Factory] Creating ProductA2" << std::endl;
        return std::make_unique<ProductA2>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        std::cout << "[Factory] Creating ProductB2" << std::endl;
        return std::make_unique<ProductB2>();
    }
};

}

namespace design_patterns::creational {
namespace design_patterns::creational {

// 声明: abstract_factory_demo 的实现已移至 src/creational/abstract_factory.cpp
void abstract_factory_demo();

}
