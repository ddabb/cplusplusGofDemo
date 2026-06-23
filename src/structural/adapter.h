#pragma once
// 文件: src/structural/adapter.h
// 说明: 适配器模式示例实现（Object/ Class/ Advanced 三种变体）
// 建议: 保持注释用于教学，生产代码可将实现移至 .cpp，以减少头文件膨胀。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::structural::adapter {

class Target {
public:
    virtual ~Target() = default;
    virtual void request() const = 0;
};

class Adaptee {
public:
    void specificRequest() const {
        std::cout << "[Adaptee] Specific request: This is the legacy interface" << std::endl;
    }

    std::string specificRequestWithData(const std::string& data) const {
        std::cout << "[Adaptee] Processing data: " << data << std::endl;
        return "Processed: " + data;
    }
};

class ObjectAdapter : public Target {
public:
    explicit ObjectAdapter(std::unique_ptr<Adaptee> adaptee)
        : adaptee_(std::move(adaptee)) {
        std::cout << "[ObjectAdapter] Constructor called" << std::endl;
    }

    void request() const override {
        std::cout << "[ObjectAdapter] Adapting request to specificRequest" << std::endl;
        adaptee_->specificRequest();
    }

private:
    std::unique_ptr<Adaptee> adaptee_;
};

class ClassAdapter : public Target, public Adaptee {
public:
    void request() const override {
        std::cout << "[ClassAdapter] Adapting request to specificRequest" << std::endl;
        specificRequest();
    }
};

class AdvancedAdapter : public Target {
public:
    explicit AdvancedAdapter(std::unique_ptr<Adaptee> adaptee)
        : adaptee_(std::move(adaptee)) {}

    void request() const override {
        std::cout << "[AdvancedAdapter] Performing complex adaptation" << std::endl;
        std::string result = adaptee_->specificRequestWithData("adapter_input");
        std::cout << "[AdvancedAdapter] Result: " << result << std::endl;
        std::cout << "[AdvancedAdapter] Additional processing..." << std::endl;
    }

private:
    std::unique_ptr<Adaptee> adaptee_;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/adapter.cpp
void adapter_demo();

}
