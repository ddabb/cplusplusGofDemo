#pragma once
// 文件: src/structural/composite.h
// 说明: 组合模式示例实现（Component/Leaf/Composite）
// 建议: 用于演示递归树结构；如需复用建议将接口与实现拆分并增加单元测试。

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::structural::composite {

/**
 * @brief 组件接口
 *
 * 定义组合中对象的通用接口，使叶子节点和组合节点可以统一处理。
 */
class Component {
public:
    virtual ~Component() = default;
    /**
     * @brief 执行操作（显示）
     * @param depth 层级深度（用于缩进显示）
     */
    virtual void operation(int depth = 0) const = 0;
    /**
     * @brief 添加子组件
     * @param child 子组件
     */
    virtual void add(std::unique_ptr<Component> child) {}
    /**
     * @brief 移除子组件
     * @param index 子组件索引
     */
    virtual void remove(size_t index) {}
    /**
     * @brief 获取子组件
     * @param index 子组件索引
     * @return 子组件指针
     */
    virtual Component* getChild(size_t index) const {
        return nullptr;
    }
    /**
     * @brief 获取名称
     * @return 组件名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 叶子节点
 *
 * 组合中的最小单位，不能包含子节点。
 */
class Leaf : public Component {
public:
    explicit Leaf(const std::string& name) : name_(name) {
        std::cout << "[叶子节点] 创建: " << name_ << std::endl;
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

/**
 * @brief 组合节点
 *
 * 可以包含子组件的容器节点。
 */
class Composite : public Component {
public:
    explicit Composite(const std::string& name) : name_(name) {
        std::cout << "[组合节点] 创建: " << name_ << std::endl;
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
        std::cout << "[组合节点] 将 " << child->getName() << " 添加到 " << name_ << std::endl;
        children_.push_back(std::move(child));
    }

    void remove(size_t index) override {
        if (index < children_.size()) {
            std::cout << "[组合节点] 从 " << name_ << " 移除 " << children_[index]->getName() << std::endl;
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

    /**
     * @brief 获取子组件数量
     * @return 子组件数量
     */
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
