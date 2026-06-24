#pragma once
// 文件: src/behavioral/interpreter.h
// 说明: 解释器模式示例，展示如何定义和解释语言文法
// 建议: 演示中仅支持四则运算，生产项目可扩展更多运算符。

#include <iostream>
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
    Context() {
        std::cout << "[上下文] 创建" << std::endl;
    }

    /**
     * @brief 设置变量
     * @param name 变量名
     * @param value 变量值
     */
    void setVariable(const std::string& name, int value) {
        variables_[name] = value;
        std::cout << "[上下文] 设置变量: " << name << " = " << value << std::endl;
    }

    /**
     * @brief 获取变量值
     * @param name 变量名
     * @return 变量值
     */
    int getVariable(const std::string& name) const {
        auto it = variables_.find(name);
        if (it != variables_.end()) {
            return it->second;
        }
        throw std::runtime_error("变量未找到: " + name);
    }

    /**
     * @brief 检查变量是否存在
     * @param name 变量名
     * @return 是否存在
     */
    bool hasVariable(const std::string& name) const {
        return variables_.contains(name);
    }

private:
    std::unordered_map<std::string, int> variables_;
};

/**
 * @brief 变量表达式
 */
class VariableExpression : public AbstractExpression {
public:
    explicit VariableExpression(const std::string& name)
        : name_(name) {
        std::cout << "[变量表达式] 创建: " << name_ << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[变量表达式] 解释: " << name_ << std::endl;
        return context.getVariable(name_);
    }

    std::string getDescription() const override {
        return name_;
    }

private:
    std::string name_;
};

/**
 * @brief 常量表达式
 */
class ConstantExpression : public AbstractExpression {
public:
    explicit ConstantExpression(int value)
        : value_(value) {
        std::cout << "[常量表达式] 创建: " << value_ << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[常量表达式] 解释: " << value_ << std::endl;
        return value_;
    }

    std::string getDescription() const override {
        return std::to_string(value_);
    }

private:
    int value_;
};

/**
 * @brief 加法表达式
 */
class AddExpression : public AbstractExpression {
public:
    AddExpression(std::unique_ptr<AbstractExpression> left,
                  std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[加法表达式] 创建" << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[加法表达式] 解释: (" << left_->getDescription() 
                  << " + " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue + rightValue;
        std::cout << "[加法表达式] 结果: " << leftValue << " + " << rightValue << " = " << result << std::endl;
        return result;
    }

    std::string getDescription() const override {
        return "(" + left_->getDescription() + " + " + right_->getDescription() + ")";
    }

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
                       std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[减法表达式] 创建" << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[减法表达式] 解释: (" << left_->getDescription() 
                  << " - " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue - rightValue;
        std::cout << "[减法表达式] 结果: " << leftValue << " - " << rightValue << " = " << result << std::endl;
        return result;
    }

    std::string getDescription() const override {
        return "(" + left_->getDescription() + " - " + right_->getDescription() + ")";
    }

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
                       std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[乘法表达式] 创建" << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[乘法表达式] 解释: (" << left_->getDescription() 
                  << " * " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue * rightValue;
        std::cout << "[乘法表达式] 结果: " << leftValue << " * " << rightValue << " = " << result << std::endl;
        return result;
    }

    std::string getDescription() const override {
        return "(" + left_->getDescription() + " * " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

void interpreter_demo();

}