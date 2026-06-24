#pragma once
// 文件: src/creational/prototype.h
// 说明: 原型模式示例（包含 Shape/Document 原型与管理器）
// 建议: 注意 clone 返回裸指针，实际项目中建议使用智能指针或工厂以避免内存泄露。

#include <iostream>
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
    ShapePrototype(const std::string& name, const std::string& color)
        : name_(name), color_(color) {
        std::cout << "[形状原型] 构造函数被调用: " << name_ << " (" << color_ << ")" << std::endl;
    }

    ShapePrototype(const ShapePrototype& other)
        : name_(other.name_), color_(other.color_) {
        std::cout << "[形状原型] 拷贝构造函数被调用: " << name_ << " (" << color_ << ")" << std::endl;
    }

    Prototype* clone() const override {
        std::cout << "[形状原型] 正在克隆..." << std::endl;
        return new ShapePrototype(*this);
    }

    void show() const override {
        std::cout << "[形状原型] 形状: " << name_ << ", 颜色: " << color_ << std::endl;
    }

    void setColor(const std::string& color) {
        color_ = color;
    }

    std::string getName() const {
        return name_;
    }

private:
    std::string name_;
    std::string color_;
};

/**
 * @brief 文档原型
 */
class DocumentPrototype : public Prototype {
public:
    DocumentPrototype(const std::string& title)
        : title_(title) {
        std::cout << "[文档原型] 构造函数被调用: " << title_ << std::endl;
    }

    DocumentPrototype(const DocumentPrototype& other)
        : title_(other.title_), contents_(other.contents_) {
        std::cout << "[文档原型] 拷贝构造函数被调用: " << title_ << std::endl;
    }

    Prototype* clone() const override {
        std::cout << "[文档原型] 正在克隆..." << std::endl;
        return new DocumentPrototype(*this);
    }

    void show() const override {
        std::cout << "[文档原型] 文档: " << title_ << std::endl;
        std::cout << "[文档原型] 内容:" << std::endl;
        for (size_t i = 0; i < contents_.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << contents_[i] << std::endl;
        }
    }

    void addContent(const std::string& content) {
        contents_.push_back(content);
    }

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
    void registerPrototype(const std::string& id, Prototype* prototype) {
        prototypes_[id] = prototype;
        std::cout << "[原型管理器] 注册原型: " << id << std::endl;
    }

    /**
     * @brief 创建原型实例
     * @param id 原型标识
     * @return 克隆的原型实例，未找到返回 nullptr
     */
    Prototype* create(const std::string& id) {
        auto it = prototypes_.find(id);
        if (it != prototypes_.end()) {
            return it->second->clone();
        }
        std::cout << "[原型管理器] 未找到原型: " << id << std::endl;
        return nullptr;
    }

private:
    std::unordered_map<std::string, Prototype*> prototypes_;
};

}

namespace design_patterns::creational {

// 声明: prototype_demo 已移至 src/creational/prototype.cpp
void prototype_demo();

}
