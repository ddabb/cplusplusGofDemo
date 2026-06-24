#pragma once
// 文件: src/creational/factory_method.h
// 说明: 工厂方法模式示例实现（包含 Creator/Product 及具体实现）
// 建议: 当前为教学/demo 用法，若用于库请拆分头/源文件。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::creational::factory_method {

/**
 * @brief 产品抽象类
 *
 * 定义产品的通用接口，所有具体产品必须实现此接口。
 */
class Product {
public:
    virtual ~Product() = default;

    /**
     * @brief 获取产品名称
     * @return 产品名称字符串
     */
    virtual std::string getName() const = 0;

    /**
     * @brief 使用产品
     */
    virtual void use() const = 0;
};

/**
 * @brief 具体产品 A
 */
class ConcreteProductA : public Product {
public:
    std::string getName() const override {
        return "产品 A";
    }

    void use() const override {
        std::cout << "[产品] 正在使用 " << getName() << std::endl;
    }
};

/**
 * @brief 具体产品 B
 */
class ConcreteProductB : public Product {
public:
    std::string getName() const override {
        return "产品 B";
    }

    void use() const override {
        std::cout << "[产品] 正在使用 " << getName() << std::endl;
    }
};

/**
 * @brief 创造者抽象类
 *
 * 定义工厂方法接口，由子类实现具体的产品创建逻辑。
 */
class Creator {
public:
    virtual ~Creator() = default;

    /**
     * @brief 工厂方法（抽象）
     * @return 创建的产品对象
     */
    virtual std::unique_ptr<Product> factoryMethod() const = 0;

    /**
     * @brief 业务操作
     *
     * 使用工厂方法创建产品并执行操作。
     */
    void anOperation() const {
        std::unique_ptr<Product> product = factoryMethod();
        std::cout << "[创造者] 创建了: " << product->getName() << std::endl;
        product->use();
    }
};

/**
 * @brief 具体创造者 A
 */
class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        std::cout << "[创造者] 创建 ConcreteProductA" << std::endl;
        return std::make_unique<ConcreteProductA>();
    }
};

/**
 * @brief 具体创造者 B
 */
class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        std::cout << "[创造者] 创建 ConcreteProductB" << std::endl;
        return std::make_unique<ConcreteProductB>();
    }
};

}

namespace design_patterns::creational {

// 声明: demo 函数实现移至 src/creational/factory_method.cpp
void factory_method_demo();

}
