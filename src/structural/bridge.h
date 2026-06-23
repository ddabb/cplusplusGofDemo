#pragma once
// 文件: src/structural/bridge.h
// 说明: 桥接模式示例，展示 Abstraction 与 Implementor 的分离
// 建议: 头文件包含完整实现方便教学，但生产项目可将实现拆到 .cpp 减少编译影响。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::structural::bridge {

class Implementor {
public:
    virtual ~Implementor() = default;
    virtual std::string operationImpl(const std::string& data) const = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    std::string operationImpl(const std::string& data) const override {
        std::cout << "[ConcreteImplementorA] Processing data using Method A" << std::endl;
        return "[Method A Result] " + data;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    std::string operationImpl(const std::string& data) const override {
        std::cout << "[ConcreteImplementorB] Processing data using Method B" << std::endl;
        return "[Method B Result] " + data;
    }
};

class Abstraction {
public:
    explicit Abstraction(std::unique_ptr<Implementor> implementor)
        : implementor_(std::move(implementor)) {
        std::cout << "[Abstraction] Constructor called" << std::endl;
    }

    virtual ~Abstraction() = default;

    virtual void operation(const std::string& data) const {
        std::cout << "[Abstraction] Calling implementor..." << std::endl;
        std::string result = implementor_->operationImpl(data);
        std::cout << "[Abstraction] Result: " << result << std::endl;
    }

protected:
    std::unique_ptr<Implementor> implementor_;
};

class RefinedAbstraction : public Abstraction {
public:
    explicit RefinedAbstraction(std::unique_ptr<Implementor> implementor)
        : Abstraction(std::move(implementor)) {
        std::cout << "[RefinedAbstraction] Constructor called" << std::endl;
    }

    void operation(const std::string& data) const override {
        std::cout << "[RefinedAbstraction] Pre-processing..." << std::endl;
        Abstraction::operation(data);
        std::cout << "[RefinedAbstraction] Post-processing..." << std::endl;
    }

    void extraOperation(const std::string& data) const {
        std::cout << "[RefinedAbstraction] Extra operation with: " << data << std::endl;
        std::string result = implementor_->operationImpl("EXTRA: " + data);
        std::cout << "[RefinedAbstraction] Extra result: " << result << std::endl;
    }
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/bridge.cpp
void bridge_demo();

}
