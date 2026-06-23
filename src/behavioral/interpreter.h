#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace design_patterns::behavioral {

class Context;

/**
 * @brief 抽象表达式类
 * 
 * 定义表达式的接口，声明解释方法。
 */
class AbstractExpression {
public:
    /**
     * @brief 虚析构函数
     */
    virtual ~AbstractExpression() = default;

    /**
     * @brief 解释方法
     * 
     * @param context 上下文对象
     * @return int 解释结果
     */
    virtual int interpret(const Context& context) const = 0;

    /**
     * @brief 获取表达式描述
     * 
     * @return std::string 表达式描述
     */
    virtual std::string getDescription() const = 0;
};

/**
 * @brief 上下文类
 * 
 * 存储解释器需要的信息，如变量值映射。
 */
class Context {
public:
    /**
     * @brief 构造函数
     */
    Context() {
        std::cout << "[Context] Created" << std::endl;
    }

    /**
     * @brief 设置变量值
     * 
     * @param name 变量名称
     * @param value 变量值
     */
    void setVariable(const std::string& name, int value) {
        variables_[name] = value;
        std::cout << "[Context] Set variable: " << name << " = " << value << std::endl;
    }

    /**
     * @brief 获取变量值
     * 
     * @param name 变量名称
     * @return int 变量值
     */
    int getVariable(const std::string& name) const {
        auto it = variables_.find(name);
        if (it != variables_.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable not found: " + name);
    }

    /**
     * @brief 检查变量是否存在
     * 
     * @param name 变量名称
     * @return bool 是否存在
     */
    bool hasVariable(const std::string& name) const {
        return variables_.contains(name);
    }

private:
    std::unordered_map<std::string, int> variables_;  ///< 变量值映射
};

/**
 * @brief 终结符表达式类 - 变量表达式
 * 
 * 解释变量的值。
 */
class VariableExpression : public AbstractExpression {
public:
    /**
     * @brief 构造函数
     * 
     * @param name 变量名称
     */
    explicit VariableExpression(const std::string& name)
        : name_(name) {
        std::cout << "[VariableExpression] Created: " << name_ << std::endl;
    }

    /**
     * @brief 解释方法
     * 
     * 从上下文中获取变量的值。
     * 
     * @param context 上下文对象
     * @return int 变量值
     */
    int interpret(const Context& context) const override {
        std::cout << "[VariableExpression] Interpreting: " << name_ << std::endl;
        return context.getVariable(name_);
    }

    /**
     * @brief 获取表达式描述
     * 
     * @return std::string 表达式描述
     */
    std::string getDescription() const override {
        return name_;
    }

private:
    std::string name_;  ///< 变量名称
};

/**
 * @brief 终结符表达式类 - 常量表达式
 * 
 * 解释常量的值。
 */
class ConstantExpression : public AbstractExpression {
public:
    /**
     * @brief 构造函数
     * 
     * @param value 常量值
     */
    explicit ConstantExpression(int value)
        : value_(value) {
        std::cout << "[ConstantExpression] Created: " << value_ << std::endl;
    }

    /**
     * @brief 解释方法
     * 
     * 返回常量的值。
     * 
     * @param context 上下文对象
     * @return int 常量值
     */
    int interpret(const Context& context) const override {
        std::cout << "[ConstantExpression] Interpreting: " << value_ << std::endl;
        return value_;
    }

    /**
     * @brief 获取表达式描述
     * 
     * @return std::string 表达式描述
     */
    std::string getDescription() const override {
        return std::to_string(value_);
    }

private:
    int value_;  ///< 常量值
};

/**
 * @brief 非终结符表达式类 - 加法表达式
 * 
 * 解释加法运算。
 */
class AddExpression : public AbstractExpression {
public:
    /**
     * @brief 构造函数
     * 
     * @param left 左子表达式
     * @param right 右子表达式
     */
    AddExpression(std::unique_ptr<AbstractExpression> left,
                  std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[AddExpression] Created" << std::endl;
    }

    /**
     * @brief 解释方法
     * 
     * 计算左右子表达式的和。
     * 
     * @param context 上下文对象
     * @return int 加法结果
     */
    int interpret(const Context& context) const override {
        std::cout << "[AddExpression] Interpreting: (" << left_->getDescription() 
                  << " + " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue + rightValue;
        std::cout << "[AddExpression] Result: " << leftValue << " + " << rightValue << " = " << result << std::endl;
        return result;
    }

    /**
     * @brief 获取表达式描述
     * 
     * @return std::string 表达式描述
     */
    std::string getDescription() const override {
        return "(" + left_->getDescription() + " + " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;   ///< 左子表达式
    std::unique_ptr<AbstractExpression> right_;  ///< 右子表达式
};

/**
 * @brief 非终结符表达式类 - 减法表达式
 * 
 * 解释减法运算。
 */
class SubtractExpression : public AbstractExpression {
public:
    /**
     * @brief 构造函数
     * 
     * @param left 左子表达式
     * @param right 右子表达式
     */
    SubtractExpression(std::unique_ptr<AbstractExpression> left,
                       std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[SubtractExpression] Created" << std::endl;
    }

    /**
     * @brief 解释方法
     * 
     * 计算左子表达式减去右子表达式的结果。
     * 
     * @param context 上下文对象
     * @return int 减法结果
     */
    int interpret(const Context& context) const override {
        std::cout << "[SubtractExpression] Interpreting: (" << left_->getDescription() 
                  << " - " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue - rightValue;
        std::cout << "[SubtractExpression] Result: " << leftValue << " - " << rightValue << " = " << result << std::endl;
        return result;
    }

    /**
     * @brief 获取表达式描述
     * 
     * @return std::string 表达式描述
     */
    std::string getDescription() const override {
        return "(" + left_->getDescription() + " - " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;   ///< 左子表达式
    std::unique_ptr<AbstractExpression> right_;  ///< 右子表达式
};

/**
 * @brief 非终结符表达式类 - 乘法表达式
 * 
 * 解释乘法运算。
 */
class MultiplyExpression : public AbstractExpression {
public:
    /**
     * @brief 构造函数
     * 
     * @param left 左子表达式
     * @param right 右子表达式
     */
    MultiplyExpression(std::unique_ptr<AbstractExpression> left,
                       std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[MultiplyExpression] Created" << std::endl;
    }

    /**
     * @brief 解释方法
     * 
     * 计算左右子表达式的乘积。
     * 
     * @param context 上下文对象
     * @return int 乘法结果
     */
    int interpret(const Context& context) const override {
        std::cout << "[MultiplyExpression] Interpreting: (" << left_->getDescription() 
                  << " * " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue * rightValue;
        std::cout << "[MultiplyExpression] Result: " << leftValue << " * " << rightValue << " = " << result << std::endl;
        return result;
    }

    /**
     * @brief 获取表达式描述
     * 
     * @return std::string 表达式描述
     */
    std::string getDescription() const override {
        return "(" + left_->getDescription() + " * " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;   ///< 左子表达式
    std::unique_ptr<AbstractExpression> right_;  ///< 右子表达式
};

/**
 * @brief 解释器模式演示函数
 * 
 * 演示解释器模式的核心思想：定义语言的文法表示，并使用解释器来解释语言中的句子。
 */
void interpreter_demo() {
    std::cout << "\n========== Interpreter Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] 解释器模式核心：定义文法表示，解释语言句子\n" << std::endl;

    // 创建上下文
    std::cout << "[Demo] --- Creating Context ---" << std::endl;
    Context context;
    context.setVariable("x", 10);
    context.setVariable("y", 5);

    // 构建表达式: x + y * 2
    std::cout << "\n[Demo] --- Building Expression: x + y * 2 ---" << std::endl;
    auto expression = std::make_unique<AddExpression>(
        std::make_unique<VariableExpression>("x"),
        std::make_unique<MultiplyExpression>(
            std::make_unique<VariableExpression>("y"),
            std::make_unique<ConstantExpression>(2)
        )
    );

    // 解释表达式
    std::cout << "\n[Demo] --- Interpreting Expression ---" << std::endl;
    int result = expression->interpret(context);
    std::cout << "[Demo] Final result: " << expression->getDescription() << " = " << result << std::endl;

    // 构建另一个表达式: (x - y) * (x + y)
    std::cout << "\n[Demo] --- Building Expression: (x - y) * (x + y) ---" << std::endl;
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

    // 解释表达式
    std::cout << "\n[Demo] --- Interpreting Expression ---" << std::endl;
    int result2 = expression2->interpret(context);
    std::cout << "[Demo] Final result: " << expression2->getDescription() << " = " << result2 << std::endl;

    // 修改变量值后重新解释
    std::cout << "\n[Demo] --- Changing Variables ---" << std::endl;
    context.setVariable("x", 20);
    context.setVariable("y", 10);

    std::cout << "\n[Demo] --- Re-interpreting First Expression ---" << std::endl;
    int result3 = expression->interpret(context);
    std::cout << "[Demo] Final result: " << expression->getDescription() << " = " << result3 << std::endl;

    std::cout << "\n==============================================\n" << std::endl;
}

}
