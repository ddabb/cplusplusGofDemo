#pragma once
// 文件: src/structural/composite.h
// 说明: 组合模式示例实现（Component/Leaf/Composite）
// 建议: 用于演示递归树结构；如需复用建议将接口与实现拆分并增加单元测试。

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::structural::composite {

class Component {
public:
    virtual ~Component() = default;
    virtual void operation(int depth = 0) const = 0;
    virtual void add(std::unique_ptr<Component> child) {}
    virtual void remove(size_t index) {}
    virtual Component* getChild(size_t index) const {
        return nullptr;
    }
    virtual std::string getName() const = 0;
};

class Leaf : public Component {
public:
    explicit Leaf(const std::string& name) : name_(name) {
        std::cout << "[Leaf] Created: " << name_ << std::endl;
    }

    void operation(int depth = 0) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << "- " << name_ << std::endl;
    }

    std::string getName() const override {
        return name_;
    }

private:
    std::string name_;
};

class Composite : public Component {
public:
    explicit Composite(const std::string& name) : name_(name) {
        std::cout << "[Composite] Created: " << name_ << std::endl;
    }

    void operation(int depth = 0) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << "+ " << name_ << std::endl;

        for (const auto& child : children_) {
            child->operation(depth + 1);
        }
    }

    void add(std::unique_ptr<Component> child) override {
        std::cout << "[Composite] Adding " << child->getName() << " to " << name_ << std::endl;
        children_.push_back(std::move(child));
    }

    void remove(size_t index) override {
        if (index < children_.size()) {
            std::cout << "[Composite] Removing " << children_[index]->getName() << " from " << name_ << std::endl;
            children_.erase(children_.begin() + index);
        }
    }

    Component* getChild(size_t index) const override {
        if (index < children_.size()) {
            return children_[index].get();
        }
        return nullptr;
    }

    std::string getName() const override {
        return name_;
    }

    size_t getChildCount() const {
        return children_.size();
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<Component>> children_;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/composite.cpp
void composite_demo();

}
