#include "behavioral/interpreter.h"
#include <iostream>

namespace design_patterns::behavioral {

Context::Context() {
    std::cout << "[上下文] 创建" << std::endl;
}

void Context::setVariable(const std::string& name, int value) {
    variables_[name] = value;
    std::cout << "[上下文] 设置变量: " << name << " = " << value << std::endl;
}

int Context::getVariable(const std::string& name) const {
    auto it = variables_.find(name);
    if (it != variables_.end()) {
        return it->second;
    }
    throw std::runtime_error("变量未找到: " + name);
}

bool Context::hasVariable(const std::string& name) const {
    return variables_.contains(name);
}

VariableExpression::VariableExpression(const std::string& name)
    : name_(name) {
    std::cout << "[变量表达式] 创建: " << name_ << std::endl;
}

int VariableExpression::interpret(const Context& context) const {
    std::cout << "[变量表达式] 解释: " << name_ << std::endl;
    return context.getVariable(name_);
}

std::string VariableExpression::getDescription() const {
    return name_;
}

ConstantExpression::ConstantExpression(int value)
    : value_(value) {
    std::cout << "[常量表达式] 创建: " << value_ << std::endl;
}

int ConstantExpression::interpret(const Context& context) const {
    std::cout << "[常量表达式] 解释: " << value_ << std::endl;
    return value_;
}

std::string ConstantExpression::getDescription() const {
    return std::to_string(value_);
}

AddExpression::AddExpression(std::unique_ptr<AbstractExpression> left,
                              std::unique_ptr<AbstractExpression> right)
    : left_(std::move(left)), right_(std::move(right)) {
    std::cout << "[加法表达式] 创建" << std::endl;
}

int AddExpression::interpret(const Context& context) const {
    std::cout << "[加法表达式] 解释: (" << left_->getDescription() 
              << " + " << right_->getDescription() << ")" << std::endl;
    int leftValue = left_->interpret(context);
    int rightValue = right_->interpret(context);
    int result = leftValue + rightValue;
    std::cout << "[加法表达式] 结果: " << leftValue << " + " << rightValue << " = " << result << std::endl;
    return result;
}

std::string AddExpression::getDescription() const {
    return "(" + left_->getDescription() + " + " + right_->getDescription() + ")";
}

SubtractExpression::SubtractExpression(std::unique_ptr<AbstractExpression> left,
                                         std::unique_ptr<AbstractExpression> right)
    : left_(std::move(left)), right_(std::move(right)) {
    std::cout << "[减法表达式] 创建" << std::endl;
}

int SubtractExpression::interpret(const Context& context) const {
    std::cout << "[减法表达式] 解释: (" << left_->getDescription() 
              << " - " << right_->getDescription() << ")" << std::endl;
    int leftValue = left_->interpret(context);
    int rightValue = right_->interpret(context);
    int result = leftValue - rightValue;
    std::cout << "[减法表达式] 结果: " << leftValue << " - " << rightValue << " = " << result << std::endl;
    return result;
}

std::string SubtractExpression::getDescription() const {
    return "(" + left_->getDescription() + " - " + right_->getDescription() + ")";
}

MultiplyExpression::MultiplyExpression(std::unique_ptr<AbstractExpression> left,
                                         std::unique_ptr<AbstractExpression> right)
    : left_(std::move(left)), right_(std::move(right)) {
    std::cout << "[乘法表达式] 创建" << std::endl;
}

int MultiplyExpression::interpret(const Context& context) const {
    std::cout << "[乘法表达式] 解释: (" << left_->getDescription() 
              << " * " << right_->getDescription() << ")" << std::endl;
    int leftValue = left_->interpret(context);
    int rightValue = right_->interpret(context);
    int result = leftValue * rightValue;
    std::cout << "[乘法表达式] 结果: " << leftValue << " * " << rightValue << " = " << result << std::endl;
    return result;
}

std::string MultiplyExpression::getDescription() const {
    return "(" + left_->getDescription() + " * " + right_->getDescription() + ")";
}

/**
 * @brief 解释器模式演示函数
 *
 * 演示解释器模式的核心特性：定义文法表示，解释语言句子。
 */
void interpreter_demo() {
    std::cout << "\n========== 解释器模式演示 ==========" << std::endl;
    std::cout << "[演示] 解释器模式核心：定义文法表示，解释语言句子\n" << std::endl;

    std::cout << "[演示] --- 创建上下文 ---" << std::endl;
    Context context;
    context.setVariable("x", 10);
    context.setVariable("y", 5);

    std::cout << "\n[演示] --- 构建表达式: x + y * 2 ---" << std::endl;
    auto expression = std::make_unique<AddExpression>(
        std::make_unique<VariableExpression>("x"),
        std::make_unique<MultiplyExpression>(
            std::make_unique<VariableExpression>("y"),
            std::make_unique<ConstantExpression>(2)
        )
    );

    std::cout << "\n[演示] --- 解释表达式 ---" << std::endl;
    int result = expression->interpret(context);
    std::cout << "[演示] 最终结果: " << expression->getDescription() << " = " << result << std::endl;

    std::cout << "\n[演示] --- 构建表达式: (x - y) * (x + y) ---" << std::endl;
    auto expression2 = std::make_unique<MultiplyExpression>(
        std::make_unique<SubtractExpression>(
            std::make_unique<VariableExpression>("x"),
            std::make_unique<VariableExpression>("y")
        ),
        std::make_unique<AddExpression>(
            std::make_unique<VariableExpression>("x"),
            std::make_unique<VariableExpression>("y")
        )
    );

    std::cout << "\n[演示] --- 解释表达式 ---" << std::endl;
    int result2 = expression2->interpret(context);
    std::cout << "[演示] 最终结果: " << expression2->getDescription() << " = " << result2 << std::endl;

    std::cout << "\n[演示] --- 修改变量值 ---" << std::endl;
    context.setVariable("x", 20);
    context.setVariable("y", 10);

    std::cout << "\n[演示] --- 重新解释第一个表达式 ---" << std::endl;
    int result3 = expression->interpret(context);
    std::cout << "[演示] 最终结果: " << expression->getDescription() << " = " << result3 << std::endl;

    std::cout << "\n==============================================\n" << std::endl;
}

}
