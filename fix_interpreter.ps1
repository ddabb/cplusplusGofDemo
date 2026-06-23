$content = @"
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace design_patterns::behavioral::interpreter {

class Context;

class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;
    virtual int interpret(const Context& context) const = 0;
    virtual std::string getDescription() const = 0;
};

class Context {
public:
    Context() {
        std::cout << "[Context] Created" << std::endl;
    }

    void setVariable(const std::string& name, int value) {
        variables_[name] = value;
        std::cout << "[Context] Set variable: " << name << " = " << value << std::endl;
    }

    int getVariable(const std::string& name) const {
        auto it = variables_.find(name);
        if (it != variables_.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable not found: " + name);
    }

    bool hasVariable(const std::string& name) const {
        return variables_.contains(name);
    }

private:
    std::unordered_map<std::string, int> variables_;
};

class VariableExpression : public AbstractExpression {
public:
    explicit VariableExpression(const std::string& name)
        : name_(name) {
        std::cout << "[VariableExpression] Created: " << name_ << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[VariableExpression] Interpreting: " << name_ << std::endl;
        return context.getVariable(name_);
    }

    std::string getDescription() const override {
        return name_;
    }

private:
    std::string name_;
};

class ConstantExpression : public AbstractExpression {
public:
    explicit ConstantExpression(int value)
        : value_(value) {
        std::cout << "[ConstantExpression] Created: " << value_ << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[ConstantExpression] Interpreting: " << value_ << std::endl;
        return value_;
    }

    std::string getDescription() const override {
        return std::to_string(value_);
    }

private:
    int value_;
};

class AddExpression : public AbstractExpression {
public:
    AddExpression(std::unique_ptr<AbstractExpression> left,
                  std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[AddExpression] Created" << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[AddExpression] Interpreting: (" << left_->getDescription() 
                  << " + " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue + rightValue;
        std::cout << "[AddExpression] Result: " << leftValue << " + " << rightValue << " = " << result << std::endl;
        return result;
    }

    std::string getDescription() const override {
        return "(" + left_->getDescription() + " + " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

class SubtractExpression : public AbstractExpression {
public:
    SubtractExpression(std::unique_ptr<AbstractExpression> left,
                       std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[SubtractExpression] Created" << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[SubtractExpression] Interpreting: (" << left_->getDescription() 
                  << " - " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue - rightValue;
        std::cout << "[SubtractExpression] Result: " << leftValue << " - " << rightValue << " = " << result << std::endl;
        return result;
    }

    std::string getDescription() const override {
        return "(" + left_->getDescription() + " - " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

class MultiplyExpression : public AbstractExpression {
public:
    MultiplyExpression(std::unique_ptr<AbstractExpression> left,
                       std::unique_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {
        std::cout << "[MultiplyExpression] Created" << std::endl;
    }

    int interpret(const Context& context) const override {
        std::cout << "[MultiplyExpression] Interpreting: (" << left_->getDescription() 
                  << " * " << right_->getDescription() << ")" << std::endl;
        int leftValue = left_->interpret(context);
        int rightValue = right_->interpret(context);
        int result = leftValue * rightValue;
        std::cout << "[MultiplyExpression] Result: " << leftValue << " * " << rightValue << " = " << result << std::endl;
        return result;
    }

    std::string getDescription() const override {
        return "(" + left_->getDescription() + " * " + right_->getDescription() + ")";
    }

private:
    std::unique_ptr<AbstractExpression> left_;
    std::unique_ptr<AbstractExpression> right_;
};

}

namespace design_patterns::behavioral {

void interpreter_demo() {
    std::cout << "\n========== Interpreter Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] Interpreter Pattern: define grammar representation and interpret sentences\n" << std::endl;

    std::cout << "[Demo] --- Creating Context ---" << std::endl;
    interpreter::Context context;
    context.setVariable("x", 10);
    context.setVariable("y", 5);

    std::cout << "\n[Demo] --- Building Expression: x + y * 2 ---" << std::endl;
    auto expression = std::make_unique<interpreter::AddExpression>(
        std::make_unique<interpreter::VariableExpression>("x"),
        std::make_unique<interpreter::MultiplyExpression>(
            std::make_unique<interpreter::VariableExpression>("y"),
            std::make_unique<interpreter::ConstantExpression>(2)
        )
    );

    std::cout << "\n[Demo] --- Interpreting Expression ---" << std::endl;
    int result = expression->interpret(context);
    std::cout << "[Demo] Final result: " << expression->getDescription() << " = " << result << std::endl;

    std::cout << "\n[Demo] --- Building Expression: (x - y) * (x + y) ---" << std::endl;
    auto expression2 = std::make_unique<interpreter::MultiplyExpression>(
        std::make_unique<interpreter::SubtractExpression>(
            std::make_unique<interpreter::VariableExpression>("x"),
            std::make_unique<interpreter::VariableExpression>("y")
        ),
        std::make_unique<interpreter::AddExpression>(
            std::make_unique<interpreter::VariableExpression>("x"),
            std::make_unique<interpreter::VariableExpression>("y")
        )
    );

    std::cout << "\n[Demo] --- Interpreting Expression ---" << std::endl;
    int result2 = expression2->interpret(context);
    std::cout << "[Demo] Final result: " << expression2->getDescription() << " = " << result2 << std::endl;

    std::cout << "\n[Demo] --- Changing Variables ---" << std::endl;
    context.setVariable("x", 20);
    context.setVariable("y", 10);

    std::cout << "\n[Demo] --- Re-interpreting First Expression ---" << std::endl;
    int result3 = expression->interpret(context);
    std::cout << "[Demo] Final result: " << expression->getDescription() << " = " << result3 << std::endl;

    std::cout << "\n==============================================\n" << std::endl;
}

}
"@
$tempFile = "f:\SelfJob\CPlusPlusDesignModeDemo\src\behavioral\interpreter_temp.h"
Set-Content -Path $tempFile -Value $content -Encoding UTF8 -Force
Write-Output "Temp file created: $tempFile"
