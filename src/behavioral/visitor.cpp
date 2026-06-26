#include "behavioral/visitor.h"
#include <iostream>
#include <algorithm>

namespace design_patterns::behavioral::visitor {

ConcreteElementA::ConcreteElementA(int value) : value_(value) {
    std::cout << "[具体元素A] 创建，值: " << value_ << std::endl;
}

void ConcreteElementA::accept(Visitor& visitor) {
    visitor.visitConcreteElementA(this);
}

std::string ConcreteElementA::getName() const {
    return "元素A";
}

int ConcreteElementA::getValue() const {
    return value_;
}

void ConcreteElementA::specificOperationA() {
    std::cout << "[具体元素A] 执行特定操作A，值: " << value_ << std::endl;
}

ConcreteElementB::ConcreteElementB(int value) : value_(value) {
    std::cout << "[具体元素B] 创建，值: " << value_ << std::endl;
}

void ConcreteElementB::accept(Visitor& visitor) {
    visitor.visitConcreteElementB(this);
}

std::string ConcreteElementB::getName() const {
    return "元素B";
}

int ConcreteElementB::getValue() const {
    return value_;
}

void ConcreteElementB::specificOperationB() {
    std::cout << "[具体元素B] 执行特定操作B，值: " << value_ << std::endl;
}

void ConcreteVisitor1::visitConcreteElementA(Element* element) {
    auto* e = dynamic_cast<ConcreteElementA*>(element);
    if (e) {
        std::cout << "[访问者1] 访问 " << e->getName() << "，值: " << e->getValue() << std::endl;
        e->specificOperationA();
    }
}

void ConcreteVisitor1::visitConcreteElementB(Element* element) {
    auto* e = dynamic_cast<ConcreteElementB*>(element);
    if (e) {
        std::cout << "[访问者1] 访问 " << e->getName() << "，值: " << e->getValue() << std::endl;
        e->specificOperationB();
    }
}

std::string ConcreteVisitor1::getName() const {
    return "访问者1";
}

void ConcreteVisitor2::visitConcreteElementA(Element* element) {
    auto* e = dynamic_cast<ConcreteElementA*>(element);
    if (e) {
        std::cout << "[访问者2] 访问 " << e->getName() << "，值的平方: " << e->getValue() * e->getValue() << std::endl;
    }
}

void ConcreteVisitor2::visitConcreteElementB(Element* element) {
    auto* e = dynamic_cast<ConcreteElementB*>(element);
    if (e) {
        std::cout << "[访问者2] 访问 " << e->getName() << "，值的两倍: " << e->getValue() * 2 << std::endl;
    }
}

std::string ConcreteVisitor2::getName() const {
    return "访问者2";
}

void ObjectStructure::addElement(std::unique_ptr<Element> element) {
    elements_.push_back(std::move(element));
    std::cout << "[对象结构] 添加元素: " << elements_.back()->getName() << std::endl;
}

void ObjectStructure::removeElement(const std::string& name) {
    auto it = std::find_if(elements_.begin(), elements_.end(),
        [&name](const std::unique_ptr<Element>& e) {
            return e->getName() == name;
        });
    if (it != elements_.end()) {
        std::cout << "[对象结构] 移除元素: " << (*it)->getName() << std::endl;
        elements_.erase(it);
    }
}

void ObjectStructure::accept(Visitor& visitor) {
    std::cout << "[对象结构] 接受访问者: " << visitor.getName() << std::endl;
    for (auto& element : elements_) {
        element->accept(visitor);
    }
}

size_t ObjectStructure::getElementCount() const {
    return elements_.size();
}

}

namespace design_patterns::behavioral {

/**
 * @brief 访问者模式演示函数
 *
 * 演示访问者模式的核心特性：将操作与数据结构分离。
 */
void visitor_demo() {
	std::cout << "\n========== 访问者模式演示 ==========" << std::endl;
	std::cout << "[演示] 访问者模式核心：将操作与数据结构分离\n" << std::endl;

	std::unique_ptr<visitor::ObjectStructure> structure = std::make_unique<visitor::ObjectStructure>();

	std::cout << "[演示] --- 添加元素 ---" << std::endl;
	structure->addElement(std::make_unique<visitor::ConcreteElementA>(10));
	structure->addElement(std::make_unique<visitor::ConcreteElementB>(20));
	structure->addElement(std::make_unique<visitor::ConcreteElementA>(15));

	std::cout << "\n[演示] --- 应用访问者1 ---" << std::endl;
	visitor::ConcreteVisitor1 visitor1;
	structure->accept(visitor1);

	std::cout << "\n[演示] --- 应用访问者2 ---" << std::endl;
	visitor::ConcreteVisitor2 visitor2;
	structure->accept(visitor2);

	std::cout << "\n[演示] --- 添加新元素 ---" << std::endl;
	structure->addElement(std::make_unique<visitor::ConcreteElementB>(5));

	std::cout << "\n[演示] --- 再次应用访问者1 ---" << std::endl;
	structure->accept(visitor1);

	std::cout << "\n==========================================\n" << std::endl;
}

}
