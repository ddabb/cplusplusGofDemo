#include "creational/prototype.h"
#include <iostream>

namespace design_patterns::creational::prototype {

ShapePrototype::ShapePrototype(const std::string& name, const std::string& color)
    : name_(name), color_(color) {
    std::cout << "[形状原型] 构造函数被调用: " << name_ << " (" << color_ << ")" << std::endl;
}

ShapePrototype::ShapePrototype(const ShapePrototype& other)
    : name_(other.name_), color_(other.color_) {
    std::cout << "[形状原型] 拷贝构造函数被调用: " << name_ << " (" << color_ << ")" << std::endl;
}

Prototype* ShapePrototype::clone() const {
    std::cout << "[形状原型] 正在克隆..." << std::endl;
    return new ShapePrototype(*this);
}

void ShapePrototype::show() const {
    std::cout << "[形状原型] 形状: " << name_ << ", 颜色: " << color_ << std::endl;
}

void ShapePrototype::setColor(const std::string& color) {
    color_ = color;
}

std::string ShapePrototype::getName() const {
    return name_;
}

DocumentPrototype::DocumentPrototype(const std::string& title)
    : title_(title) {
    std::cout << "[文档原型] 构造函数被调用: " << title_ << std::endl;
}

DocumentPrototype::DocumentPrototype(const DocumentPrototype& other)
    : title_(other.title_), contents_(other.contents_) {
    std::cout << "[文档原型] 拷贝构造函数被调用: " << title_ << std::endl;
}

Prototype* DocumentPrototype::clone() const {
    std::cout << "[文档原型] 正在克隆..." << std::endl;
    return new DocumentPrototype(*this);
}

void DocumentPrototype::show() const {
    std::cout << "[文档原型] 文档: " << title_ << std::endl;
    std::cout << "[文档原型] 内容:" << std::endl;
    for (size_t i = 0; i < contents_.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << contents_[i] << std::endl;
    }
}

void DocumentPrototype::addContent(const std::string& content) {
    contents_.push_back(content);
}

void PrototypeManager::registerPrototype(const std::string& id, Prototype* prototype) {
    prototypes_[id] = prototype;
    std::cout << "[原型管理器] 注册原型: " << id << std::endl;
}

Prototype* PrototypeManager::create(const std::string& id) {
    auto it = prototypes_.find(id);
    if (it != prototypes_.end()) {
        return it->second->clone();
    }
    std::cout << "[原型管理器] 未找到原型: " << id << std::endl;
    return nullptr;
}

}

namespace design_patterns::creational {

/**
 * @brief 原型模式演示函数
 *
 * 演示原型模式的核心特性：通过拷贝原型创建新对象，避免重复初始化。
 */
void prototype_demo() {
	std::cout << "\n========== 原型模式演示 ==========" << std::endl;
	std::cout << "[演示] 原型模式核心：通过拷贝原型创建新对象，避免重复初始化\n" << std::endl;

	prototype::ShapePrototype circle("圆形", "红色");
	prototype::ShapePrototype rectangle("矩形", "蓝色");

	std::unique_ptr<prototype::Prototype> clonedCircle(circle.clone());
	std::unique_ptr<prototype::Prototype> clonedRectangle(rectangle.clone());

	prototype::ShapePrototype* castedCircle = dynamic_cast<prototype::ShapePrototype*>(clonedCircle.get());
	if (castedCircle) {
		castedCircle->setColor("绿色");
	}

	std::cout << "\n[演示] 原始对象:" << std::endl;
	circle.show();
	rectangle.show();

	std::cout << "\n[演示] 克隆对象(已修改):" << std::endl;
	clonedCircle->show();
	clonedRectangle->show();

	std::cout << "\n[演示] 使用原型管理器:" << std::endl;
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
