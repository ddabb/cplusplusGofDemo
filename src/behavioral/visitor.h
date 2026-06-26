#pragma once
// 文件: src/behavioral/visitor.h
// 说明: 访问者模式示例，展示如何将操作与数据结构分离
// 建议: 演示中仅包含两个元素类型，生产项目可扩展更多元素。

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
    ConcreteElementA(int value);

    void accept(Visitor& visitor) override;
    std::string getName() const override;
    int getValue() const override;

    /**
     * @brief 执行特定操作 A
     */
    void specificOperationA();

private:
    int value_;
};

/**
 * @brief 具体元素 B
 */
class ConcreteElementB : public Element {
public:
    ConcreteElementB(int value);

    void accept(Visitor& visitor) override;
    std::string getName() const override;
    int getValue() const override;

    /**
     * @brief 执行特定操作 B
     */
    void specificOperationB();

private:
    int value_;
};

/**
 * @brief 具体访问者 1
 */
class ConcreteVisitor1 : public Visitor {
public:
    void visitConcreteElementA(Element* element) override;
    void visitConcreteElementB(Element* element) override;
    std::string getName() const override;
};

/**
 * @brief 具体访问者 2
 */
class ConcreteVisitor2 : public Visitor {
public:
    void visitConcreteElementA(Element* element) override;
    void visitConcreteElementB(Element* element) override;
    std::string getName() const override;
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
    void addElement(std::unique_ptr<Element> element);

    /**
     * @brief 移除元素
     * @param name 元素名称
     */
    void removeElement(const std::string& name);

    /**
     * @brief 接受访问者
     * @param visitor 访问者对象
     */
    void accept(Visitor& visitor);

    /**
     * @brief 获取元素数量
     * @return 元素数量
     */
    size_t getElementCount() const;

private:
    std::vector<std::unique_ptr<Element>> elements_;
};

}

namespace design_patterns::behavioral {
void visitor_demo();

}