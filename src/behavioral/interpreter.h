#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace design_patterns::behavioral {

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

void interpreter_demo();

}