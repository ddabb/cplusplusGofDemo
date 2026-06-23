#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::visitor {

class Element;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visitConcreteElementA(Element* element) = 0;
    virtual void visitConcreteElementB(Element* element) = 0;
    virtual std::string getName() const = 0;
};

class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor& visitor) = 0;
    virtual std::string getName() const = 0;
    virtual int getValue() const = 0;
};

class ConcreteElementA : public Element {
public:
    ConcreteElementA(int value) : value_(value) {
        std::cout << "[ConcreteElementA] Created with value: " << value_ << std::endl;
    }

    void accept(Visitor& visitor) override {
        visitor.visitConcreteElementA(this);
    }

    std::string getName() const override {
        return "ConcreteElementA";
    }

    int getValue() const override {
        return value_;
    }

    void specificOperationA() {
        std::cout << "[ConcreteElementA] Performing specific operation A" << std::endl;
    }

private:
    int value_;
};

class ConcreteElementB : public Element {
public:
    ConcreteElementB(int value) : value_(value) {
        std::cout << "[ConcreteElementB] Created with value: " << value_ << std::endl;
    }

    void accept(Visitor& visitor) override {
        visitor.visitConcreteElementB(this);
    }

    std::string getName() const override {
        return "ConcreteElementB";
    }

    int getValue() const override {
        return value_;
    }

    void specificOperationB() {
        std::cout << "[ConcreteElementB] Performing specific operation B" << std::endl;
    }

private:
    int value_;
};

class ConcreteVisitor1 : public Visitor {
public:
    void visitConcreteElementA(Element* element) override {
        std::cout << "[ConcreteVisitor1] Visiting " << element->getName() 
                  << " with value " << element->getValue() << std::endl;
        std::cout << "[ConcreteVisitor1] Calculating: " << element->getValue() * 2 << std::endl;
    }

    void visitConcreteElementB(Element* element) override {
        std::cout << "[ConcreteVisitor1] Visiting " << element->getName() 
                  << " with value " << element->getValue() << std::endl;
        std::cout << "[ConcreteVisitor1] Calculating: " << element->getValue() + 10 << std::endl;
    }

    std::string getName() const override {
        return "ConcreteVisitor1";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void visitConcreteElementA(Element* element) override {
        std::cout << "[ConcreteVisitor2] Visiting " << element->getName() 
                  << " with value " << element->getValue() << std::endl;
        std::cout << "[ConcreteVisitor2] Calculating: " << element->getValue() * element->getValue() << std::endl;
    }

    void visitConcreteElementB(Element* element) override {
        std::cout << "[ConcreteVisitor2] Visiting " << element->getName() 
                  << " with value " << element->getValue() << std::endl;
        std::cout << "[ConcreteVisitor2] Calculating: " << element->getValue() / 2 << std::endl;
    }

    std::string getName() const override {
        return "ConcreteVisitor2";
    }
};

class ObjectStructure {
public:
    void addElement(std::unique_ptr<Element> element) {
        elements_.push_back(std::move(element));
        std::cout << "[ObjectStructure] Element added: " << elements_.back()->getName() << std::endl;
    }

    void removeElement(const std::string& name) {
        auto it = std::remove_if(elements_.begin(), elements_.end(),
            [&name](const std::unique_ptr<Element>& e) {
                return e->getName() == name;
            });
        if (it != elements_.end()) {
            std::cout << "[ObjectStructure] Element removed" << std::endl;
            elements_.erase(it, elements_.end());
        }
    }

    void accept(Visitor& visitor) {
        std::cout << "[ObjectStructure] Accepting visitor: " << visitor.getName() << std::endl;
        for (const auto& element : elements_) {
            element->accept(visitor);
        }
    }

    size_t getElementCount() const {
        return elements_.size();
    }

private:
    std::vector<std::unique_ptr<Element>> elements_;
};

}

namespace design_patterns::behavioral {

void visitor_demo() {
    std::cout << "\n========== Visitor Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] Visitor Pattern: separate operations from data structure\n" << std::endl;

    std::unique_ptr<visitor::ObjectStructure> structure = std::make_unique<visitor::ObjectStructure>();

    std::cout << "[Demo] --- Adding Elements ---" << std::endl;
    structure->addElement(std::make_unique<visitor::ConcreteElementA>(10));
    structure->addElement(std::make_unique<visitor::ConcreteElementB>(20));
    structure->addElement(std::make_unique<visitor::ConcreteElementA>(15));

    std::cout << "\n[Demo] --- Applying Visitor1 ---" << std::endl;
    visitor::ConcreteVisitor1 visitor1;
    structure->accept(visitor1);

    std::cout << "\n[Demo] --- Applying Visitor2 ---" << std::endl;
    visitor::ConcreteVisitor2 visitor2;
    structure->accept(visitor2);

    std::cout << "\n[Demo] --- Adding New Element ---" << std::endl;
    structure->addElement(std::make_unique<visitor::ConcreteElementB>(5));

    std::cout << "\n[Demo] --- Applying Visitor1 Again ---" << std::endl;
    structure->accept(visitor1);

    std::cout << "\n==========================================\n" << std::endl;
}

}