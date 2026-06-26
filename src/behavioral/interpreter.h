#pragma once
// 文件: src/behavioral/interpreter.h
// 说明: 解释器模式示例，展示如何定义和解释语言文法
// 建议: 演示中仅支持四则运算，生产项目可扩展更多运算符。

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace design_patterns::behavioral {

class Context;

/**
 * @brief 抽象表达式接口
 *
 * 定义表达式的通用接口。
 */
class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;
    /**
     * @brief 解释表达式
     * @param context 上下文对象
     * @return 解释结果
     */
    virtual int interpret(const Context& context) const = 0;
    /**
     * @brief 获取描述
     * @return 表达式描述
     */
    virtual std::string getDescription() const = 0;
};

/**
 * @brief 上下文类
 *
 * 存储变量和值的映射。
 */
class Context {
public:
    Context();

    /**
     * @brief 设置变量
     * @param name 变量名
     * @param value 变量值
     */
    void setVariable(const std::string& name, int value);

    /**
     * @brief 获取变量值
     * @param name 变量名
     * @return 变量值
     */
    int getVariable(const std::string& name) const;

    /**
     * @brief 检查变量是否存在
     * @param name 变量名
     * @return 是否存在
     */
    bool hasVariable(const std::string& name) const;

private:
    std::unordered_map<std::string, int> variables_;
};

/**
 * @brief 变量表达式
 */
class VariableExpression : public AbstractExpression {
public:
    explicit VariableExpression(const std::string& name);

    int interpret(const Context& context) const override;
    std::string getDescription() const override;

private:
    std::string name_;
};

/**
 * @brief 常量表达式
 */
class ConstantExpression : public AbstractExpression {
public:
    explicit ConstantExpression(int value);

    int interpret(const Context& context) const override;
    std::string getDescription() const override;

private:
    int value_;
};

/**
 * @brief 加法表达式
 */
class AddExpression : public AbstractExpression {
public:
    AddExpression(std::unique_ptr<AbstractExpression> left,
                  std::unique_ptr<AbstractExpression> right);

    int interpret(const Context& context) const override;
    std::string getDescription() const override;

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

/**
 * @brief 减法表达式
 */
class SubtractExpression : public AbstractExpression {
public:
    SubtractExpression(std::unique_ptr<AbstractExpression> left,
                       std::unique_ptr<AbstractExpression> right);

    int interpret(const Context& context) const override;
    std::string getDescription() const override;

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

/**
 * @brief 乘法表达式
 */
class MultiplyExpression : public AbstractExpression {
public:
    MultiplyExpression(std::unique_ptr<AbstractExpression> left,
                       std::unique_ptr<AbstractExpression> right);

    int interpret(const Context& context) const override;
    std::string getDescription() const override;

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

void interpreter_demo();

}
