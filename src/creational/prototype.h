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

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual Prototype* clone() const = 0;
    virtual void show() const = 0;
};

class ShapePrototype : public Prototype {
public:
    ShapePrototype(const std::string& name, const std::string& color)
        : name_(name), color_(color) {
        std::cout << "[ShapePrototype] Constructor called: " << name_ << " (" << color_ << ")" << std::endl;
    }

    ShapePrototype(const ShapePrototype& other)
        : name_(other.name_), color_(other.color_) {
        std::cout << "[ShapePrototype] Copy constructor called: " << name_ << " (" << color_ << ")" << std::endl;
    }

    Prototype* clone() const override {
        std::cout << "[ShapePrototype] Cloning..." << std::endl;
        return new ShapePrototype(*this);
    }

    void show() const override {
        std::cout << "[ShapePrototype] Shape: " << name_ << ", Color: " << color_ << std::endl;
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

class DocumentPrototype : public Prototype {
public:
    DocumentPrototype(const std::string& title)
        : title_(title) {
        std::cout << "[DocumentPrototype] Constructor called: " << title_ << std::endl;
    }

    DocumentPrototype(const DocumentPrototype& other)
        : title_(other.title_), contents_(other.contents_) {
        std::cout << "[DocumentPrototype] Copy constructor called: " << title_ << std::endl;
    }

    Prototype* clone() const override {
        std::cout << "[DocumentPrototype] Cloning..." << std::endl;
        return new DocumentPrototype(*this);
    }

    void show() const override {
        std::cout << "[DocumentPrototype] Document: " << title_ << std::endl;
        std::cout << "[DocumentPrototype] Contents:" << std::endl;
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

class PrototypeManager {
public:
    void registerPrototype(const std::string& id, Prototype* prototype) {
        prototypes_[id] = prototype;
        std::cout << "[PrototypeManager] Registered prototype: " << id << std::endl;
    }

    Prototype* create(const std::string& id) {
        auto it = prototypes_.find(id);
        if (it != prototypes_.end()) {
            return it->second->clone();
        }
        std::cout << "[PrototypeManager] Prototype not found: " << id << std::endl;
        return nullptr;
    }

private:
    std::unordered_map<std::string, Prototype*> prototypes_;
};

}

namespace design_patterns::creational {

void prototype_demo() {
    std::cout << "\n========== Prototype Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] 原型模式核心：通过拷贝原型创建新对象，避免重复初始化\n" << std::endl;

    prototype::ShapePrototype circle("Circle", "Red");
    prototype::ShapePrototype rectangle("Rectangle", "Blue");

    std::unique_ptr<prototype::Prototype> clonedCircle(circle.clone());
    std::unique_ptr<prototype::Prototype> clonedRectangle(rectangle.clone());

    prototype::ShapePrototype* castedCircle = dynamic_cast<prototype::ShapePrototype*>(clonedCircle.get());
    if (castedCircle) {
        castedCircle->setColor("Green");
    }

    std::cout << "\n[Demo] Original objects:" << std::endl;
    circle.show();
    rectangle.show();

    std::cout << "\n[Demo] Cloned objects (modified):" << std::endl;
    clonedCircle->show();
    clonedRectangle->show();

    std::cout << "\n[Demo] Using PrototypeManager:" << std::endl;
    prototype::PrototypeManager manager;
    manager.registerPrototype("circle", &circle);
    manager.registerPrototype("rectangle", &rectangle);

    std::unique_ptr<prototype::Prototype> newCircle(manager.create("circle"));
    std::unique_ptr<prototype::Prototype> newRectangle(manager.create("rectangle"));

    if (newCircle) newCircle->show();
    if (newRectangle) newRectangle->show();

    std::cout << "=============================================\n" << std::endl;
}

}
