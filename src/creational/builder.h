#pragma once
// 文件: src/creational/builder.h
// 说明: 建造者模式示例实现（包含 Product/Builder/Director）
// 建议: 头文件包含完整实现方便教学，但生产项目可将实现拆到 .cpp 减少编译影响。

#include <memory>
#include <string>
#include <vector>

namespace design_patterns::creational::builder {

/**
 * @brief 产品类
 *
 * 包含多个部件，由建造者逐步构建。
 */
class Product {
public:
    /**
     * @brief 添加部件
     * @param part 部件名称
     */
    void addPart(const std::string& part);

    /**
     * @brief 展示产品
     */
    void show() const;

private:
    std::vector<std::string> parts_;
};

/**
 * @brief 建造者抽象类
 *
 * 定义构建产品各个部件的接口。
 */
class Builder {
public:
    virtual ~Builder() = default;
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual std::unique_ptr<Product> getResult() = 0;
};

/**
 * @brief 具体建造者 1
 *
 * 构建类型 1 的产品。
 */
class ConcreteBuilder1 : public Builder {
public:
    ConcreteBuilder1();

    void buildPartA() override;
    void buildPartB() override;
    void buildPartC() override;
    std::unique_ptr<Product> getResult() override;

private:
    std::unique_ptr<Product> product_;
};

/**
 * @brief 具体建造者 2
 *
 * 构建类型 2 的产品。
 */
class ConcreteBuilder2 : public Builder {
public:
    ConcreteBuilder2();

    void buildPartA() override;
    void buildPartB() override;
    void buildPartC() override;
    std::unique_ptr<Product> getResult() override;

private:
    std::unique_ptr<Product> product_;
};

/**
 * @brief 指挥者类
 *
 * 控制建造过程，调用建造者构建产品。
 */
class Director {
public:
    /**
     * @brief 构建产品
     * @param builder 建造者对象
     * @return 构建完成的产品
     */
    std::unique_ptr<Product> construct(Builder& builder);
};

}

namespace design_patterns::creational {

// 声明: builder_demo 的实现已移至 src/creational/builder.cpp
void builder_demo();

}
