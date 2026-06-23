#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::creational::builder {

class Product {
public:
    void addPart(const std::string& part) {
        parts_.push_back(part);
    }

    void show() const {
        std::cout << "[Product] Parts: ";
        for (size_t i = 0; i < parts_.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << parts_[i];
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::string> parts_;
};

class Builder {
public:
    virtual ~Builder() = default;
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual std::unique_ptr<Product> getResult() = 0;
};

class ConcreteBuilder1 : public Builder {
public:
    ConcreteBuilder1() : product_(std::make_unique<Product>()) {}

    void buildPartA() override {
        std::cout << "[Builder1] Building Part A" << std::endl;
        product_->addPart("Part A1");
    }

    void buildPartB() override {
        std::cout << "[Builder1] Building Part B" << std::endl;
        product_->addPart("Part B1");
    }

    void buildPartC() override {
        std::cout << "[Builder1] Building Part C" << std::endl;
        product_->addPart("Part C1");
    }

    std::unique_ptr<Product> getResult() override {
        return std::move(product_);
    }

private:
    std::unique_ptr<Product> product_;
};

class ConcreteBuilder2 : public Builder {
public:
    ConcreteBuilder2() : product_(std::make_unique<Product>()) {}

    void buildPartA() override {
        std::cout << "[Builder2] Building Part A" << std::endl;
        product_->addPart("Part A2");
    }

    void buildPartB() override {
        std::cout << "[Builder2] Building Part B" << std::endl;
        product_->addPart("Part B2");
    }

    void buildPartC() override {
        std::cout << "[Builder2] Building Part C" << std::endl;
        product_->addPart("Part C2");
    }

    std::unique_ptr<Product> getResult() override {
        return std::move(product_);
    }

private:
    std::unique_ptr<Product> product_;
};

class Director {
public:
    std::unique_ptr<Product> construct(Builder& builder) {
        std::cout << "[Director] Starting construction" << std::endl;
        builder.buildPartA();
        builder.buildPartB();
        builder.buildPartC();
        std::cout << "[Director] Construction completed" << std::endl;
        return builder.getResult();
    }
};

}

namespace design_patterns::creational {
namespace design_patterns::creational {

// 声明: builder_demo 的实现已移至 src/creational/builder.cpp
void builder_demo();

}
