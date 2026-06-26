#pragma once
// 文件: src/creational/prototype.h
// 说明: 原型模式示例（包含 Shape/Document 原型与管理器）
// 建议: 注意 clone 返回裸指针，实际项目中建议使用智能指针或工厂以避免内存泄露。

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace design_patterns::creational::prototype {

/**
 * @brief 原型抽象类
 *
 * 定义克隆接口，所有具体原型必须实现此接口。
 */
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual Prototype* clone() const = 0;
    virtual void show() const = 0;
};

/**
 * @brief 形状原型
 */
class ShapePrototype : public Prototype {
public:
    ShapePrototype(const std::string& name, const std::string& color);
    ShapePrototype(const ShapePrototype& other);

    Prototype* clone() const override;
    void show() const override;

    void setColor(const std::string& color);
    std::string getName() const;

private:
    std::string name_;
    std::string color_;
};

/**
 * @brief 文档原型
 */
class DocumentPrototype : public Prototype {
public:
    DocumentPrototype(const std::string& title);
    DocumentPrototype(const DocumentPrototype& other);

    Prototype* clone() const override;
    void show() const override;

    void addContent(const std::string& content);

private:
    std::string title_;
    std::vector<std::string> contents_;
};

/**
 * @brief 原型管理器
 *
 * 管理原型对象的注册和创建。
 */
class PrototypeManager {
public:
    /**
     * @brief 注册原型
     * @param id 原型标识
     * @param prototype 原型对象
     */
    void registerPrototype(const std::string& id, Prototype* prototype);

    /**
     * @brief 创建原型实例
     * @param id 原型标识
     * @return 克隆的原型实例，未找到返回 nullptr
     */
    Prototype* create(const std::string& id);

private:
    std::unordered_map<std::string, Prototype*> prototypes_;
};

}

namespace design_patterns::creational {

// 声明: prototype_demo 已移至 src/creational/prototype.cpp
void prototype_demo();

}
