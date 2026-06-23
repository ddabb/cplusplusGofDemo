#pragma once
// 文件: src/creational/factory_method.h
// 说明: 工厂方法模式示例实现（包含 Creator/Product 及具体实现）
// 建议: 当前为教学/demo 用法，若用于库请拆分头/源文件。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::creational::factory_method {

class Product {
public:
    virtual ~Product() = default;
    virtual std::string getName() const = 0;
    virtual void use() const = 0;
};

class ConcreteProductA : public Product {
public:
    std::string getName() const override {
        return "Product A";
    }

    void use() const override {
        std::cout << "[Product] Using " << getName() << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    std::string getName() const override {
        return "Product B";
    }

    void use() const override {
        std::cout << "[Product] Using " << getName() << std::endl;
    }
};

class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> factoryMethod() const = 0;

    void anOperation() const {
        std::unique_ptr<Product> product = factoryMethod();
        std::cout << "[Creator] Created: " << product->getName() << std::endl;
        product->use();
    }
};

class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        std::cout << "[Creator] Creating ConcreteProductA" << std::endl;
        return std::make_unique<ConcreteProductA>();
    }
};

class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        std::cout << "[Creator] Creating ConcreteProductB" << std::endl;
        return std::make_unique<ConcreteProductB>();
    }
};

}

namespace design_patterns::creational {

void factory_method_demo() {
    std::cout << "\n========== Factory Method Pattern Demo ==========" << std::endl;

    std::unique_ptr<factory_method::Creator> creatorA = std::make_unique<factory_method::ConcreteCreatorA>();
    creatorA->anOperation();

    std::cout << std::endl;

    std::unique_ptr<factory_method::Creator> creatorB = std::make_unique<factory_method::ConcreteCreatorB>();
    creatorB->anOperation();

    std::cout << "=================================================\n" << std::endl;
}

}
