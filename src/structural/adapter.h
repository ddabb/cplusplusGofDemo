#pragma once
// 文件: src/structural/adapter.h
// 说明: 适配器模式示例实现（Object/ Class/ Advanced 三种变体）
// 建议: 保持注释用于教学，生产代码可将实现移至 .cpp，以减少头文件膨胀。

#include <memory>
#include <string>

namespace design_patterns::structural::adapter {

/**
 * @brief 目标接口
 *
 * 定义客户端期望的接口。
 */
class Target {
public:
    virtual ~Target() = default;
    virtual void request() const = 0;
};

/**
 * @brief 被适配者（原有接口）
 *
 * 包含与目标接口不兼容的方法。
 */
class Adaptee {
public:
    void specificRequest() const;
    std::string specificRequestWithData(const std::string& data) const;
};

/**
 * @brief 对象适配器
 *
 * 通过组合方式适配被适配者。
 */
class ObjectAdapter : public Target {
public:
    explicit ObjectAdapter(std::unique_ptr<Adaptee> adaptee);
    void request() const override;

private:
    std::unique_ptr<Adaptee> adaptee_;
};

/**
 * @brief 类适配器
 *
 * 通过继承方式适配被适配者。
 */
class ClassAdapter : public Target, public Adaptee {
public:
    void request() const override;
};

/**
 * @brief 高级适配器
 *
 * 包含复杂适配逻辑的适配器。
 */
class AdvancedAdapter : public Target {
public:
    explicit AdvancedAdapter(std::unique_ptr<Adaptee> adaptee);
    void request() const override;

private:
    std::unique_ptr<Adaptee> adaptee_;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/adapter.cpp
void adapter_demo();

}
