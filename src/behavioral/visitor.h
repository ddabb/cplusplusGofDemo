#pragma once
// 文件: src/behavioral/visitor.h
// 说明: 访问者模式示例，展示如何将操作与数据结构分离
// 建议: 演示中仅包含两个元素类型，生产项目可扩展更多元素。

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::visitor {

class Element;

/**
 * @brief 访问者接口
 *
 * 定义访问不同元素的方法。
 */
class Visitor {
public:
    virtual ~Visitor() = default;
    /**
     * @brief 访问具体元素 A
     * @param element 元素对象
     */
    virtual void visitConcreteElementA(Element* element) = 0;
    /**
     * @brief 访问具体元素 B
     * @param element 元素对象
     */
    virtual void visitConcreteElementB(Element* element) = 0;
    /**
     * @brief 获取访问者名称
     * @return 访问者名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 元素接口
 *
 * 定义接受访问者的方法。
 */
class Element {
public:
    virtual ~Element() = default;
    /**
     * @brief 接受访问者
     * @param visitor 访问者对象
     */
    virtual void accept(Visitor& visitor) = 0;
    /**
     * @brief 获取元素名称
     * @return 元素名称
     */
    virtual std::string getName() const = 0;
    /**
     * @brief 获取元素值
     * @return 元素值
     */
    virtual int getValue() const = 0;
};

/**
 * @brief 具体元素 A
 */
class ConcreteElementA : public Element {
public:
    ConcreteElementA(int value) : value_(value) {
        std::cout << "[具体元素A] 创建，值: " << value_ << std::endl;
    }

    void accept(Visitor& visitor) override {
        visitor.visitConcreteElementA(this);
    }

    std::string getName() const override {
        return "具体元素A";
    }

    int getValue() const override {
        return value_;
    }

    /**
     * @brief 执行特定操作 A
     */
    void specificOperationA() {
        std::cout << "[具体元素A] 执行特定操作 A" << std::endl;
    }

private:
    int value_;
};

/**
 * @brief 具体元素 B
 */
class ConcreteElementB : public Element {
public:
    ConcreteElementB(int value) : value_(value) {
        std::cout << "[具体元素B] 创建，值: " << value_ << std::endl;
    }

    void accept(Visitor& visitor) override {
        visitor.visitConcreteElementB(this);
    }

    std::string getName() const override {
        return "具体元素B";
    }

    int getValue() const override {
        return value_;
    }

    /**
     * @brief 执行特定操作 B
     */
    void specificOperationB() {
        std::cout << "[具体元素B] 执行特定操作 B" << std::endl;
    }

private:
    int value_;
};

/**
 * @brief 具体访问者 1
 */
class ConcreteVisitor1 : public Visitor {
public:
    void visitConcreteElementA(Element* element) override {
        std::cout << "[访问者1] 访问 " << element->getName() 
                  << "，值为 " << element->getValue() << std::endl;
        std::cout << "[访问者1] 计算结果: " << element->getValue() * 2 << std::endl;
    }

    void visitConcreteElementB(Element* element) override {
        std::cout << "[访问者1] 访问 " << element->getName() 
                  << "，值为 " << element->getValue() << std::endl;
        std::cout << "[访问者1] 计算结果: " << element->getValue() + 10 << std::endl;
    }

    std::string getName() const override {
        return "访问者1";
    }
};

/**
 * @brief 具体访问者 2
 */
class ConcreteVisitor2 : public Visitor {
public:
    void visitConcreteElementA(Element* element) override {
        std::cout << "[访问者2] 访问 " << element->getName() 
                  << "，值为 " << element->getValue() << std::endl;
        std::cout << "[访问者2] 计算结果: " << element->getValue() * element->getValue() << std::endl;
    }

    void visitConcreteElementB(Element* element) override {
        std::cout << "[访问者2] 访问 " << element->getName() 
                  << "，值为 " << element->getValue() << std::endl;
        std::cout << "[访问者2] 计算结果: " << element->getValue() / 2 << std::endl;
    }

    std::string getName() const override {
        return "访问者2";
    }
};

/**
 * @brief 对象结构类
 *
 * 管理元素集合，提供接受访问者的接口。
 */
class ObjectStructure {
public:
    /**
     * @brief 添加元素
     * @param element 元素对象
     */
    void addElement(std::unique_ptr<Element> element) {
        elements_.push_back(std::move(element));
        std::cout << "[对象结构] 添加元素: " << elements_.back()->getName() << std::endl;
    }

    /**
     * @brief 移除元素
     * @param name 元素名称
     */
    void removeElement(const std::string& name) {
        auto it = std::remove_if(elements_.begin(), elements_.end(),
            [&name](const std::unique_ptr<Element>& e) {
                return e->getName() == name;
            });
        if (it != elements_.end()) {
            std::cout << "[对象结构] 移除元素" << std::endl;
            elements_.erase(it, elements_.end());
        }
    }

    /**
     * @brief 接受访问者
     * @param visitor 访问者对象
     */
    void accept(Visitor& visitor) {
        std::cout << "[对象结构] 接受访问者: " << visitor.getName() << std::endl;
        for (const auto& element : elements_) {
            element->accept(visitor);
        }
    }

    /**
     * @brief 获取元素数量
     * @return 元素数量
     */
    size_t getElementCount() const {
        return elements_.size();
    }

private:
    std::vector<std::unique_ptr<Element>> elements_;
};

}

namespace design_patterns::behavioral {
void visitor_demo();

}