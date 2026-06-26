#pragma once
// 文件: src/structural/bridge.h
// 说明: 桥接模式示例，展示 Abstraction 与 Implementor 的分离
// 建议: 头文件包含完整实现方便教学，但生产项目可将实现拆到 .cpp 减少编译影响。

#include <memory>
#include <string>

namespace design_patterns::structural::bridge {

/**
 * @brief 实现接口
 *
 * 定义实现层的接口，供具体实现类实现。
 */
class Implementor {
public:
    virtual ~Implementor() = default;
    virtual std::string operationImpl(const std::string& data) const = 0;
};

/**
 * @brief 具体实现 A
 */
class ConcreteImplementorA : public Implementor {
public:
    std::string operationImpl(const std::string& data) const override;
};

/**
 * @brief 具体实现 B
 */
class ConcreteImplementorB : public Implementor {
public:
    std::string operationImpl(const std::string& data) const override;
};

/**
 * @brief 抽象类
 *
 * 定义抽象层的接口，持有实现对象的引用。
 */
class Abstraction {
public:
    explicit Abstraction(std::unique_ptr<Implementor> implementor);
    virtual ~Abstraction() = default;

    /**
     * @brief 操作方法
     * @param data 输入数据
     */
    virtual void operation(const std::string& data) const;

protected:
    std::unique_ptr<Implementor> implementor_;
};

/**
 * @brief 扩展抽象类
 *
 * 对抽象层进行扩展，添加额外功能。
 */
class RefinedAbstraction : public Abstraction {
public:
    explicit RefinedAbstraction(std::unique_ptr<Implementor> implementor);

    void operation(const std::string& data) const override;

    /**
     * @brief 额外操作
     * @param data 输入数据
     */
    void extraOperation(const std::string& data) const;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/bridge.cpp
void bridge_demo();

}
