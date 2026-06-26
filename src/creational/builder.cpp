#include "creational/builder.h"
#include <iostream>

namespace design_patterns::creational::builder {

void Product::addPart(const std::string& part) {
    parts_.push_back(part);
}

void Product::show() const {
    std::cout << "[产品] 部件: ";
    for (size_t i = 0; i < parts_.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << parts_[i];
    }
    std::cout << std::endl;
}

ConcreteBuilder1::ConcreteBuilder1() : product_(std::make_unique<Product>()) {}

void ConcreteBuilder1::buildPartA() {
    std::cout << "[建造者1] 构建部件 A" << std::endl;
    product_->addPart("部件 A1");
}

void ConcreteBuilder1::buildPartB() {
    std::cout << "[建造者1] 构建部件 B" << std::endl;
    product_->addPart("部件 B1");
}

void ConcreteBuilder1::buildPartC() {
    std::cout << "[建造者1] 构建部件 C" << std::endl;
    product_->addPart("部件 C1");
}

std::unique_ptr<Product> ConcreteBuilder1::getResult() {
    return std::move(product_);
}

ConcreteBuilder2::ConcreteBuilder2() : product_(std::make_unique<Product>()) {}

void ConcreteBuilder2::buildPartA() {
    std::cout << "[建造者2] 构建部件 A" << std::endl;
    product_->addPart("部件 A2");
}

void ConcreteBuilder2::buildPartB() {
    std::cout << "[建造者2] 构建部件 B" << std::endl;
    product_->addPart("部件 B2");
}

void ConcreteBuilder2::buildPartC() {
    std::cout << "[建造者2] 构建部件 C" << std::endl;
    product_->addPart("部件 C2");
}

std::unique_ptr<Product> ConcreteBuilder2::getResult() {
    return std::move(product_);
}

std::unique_ptr<Product> Director::construct(Builder& builder) {
    std::cout << "[指挥者] 开始构建" << std::endl;
    builder.buildPartA();
    builder.buildPartB();
    builder.buildPartC();
    std::cout << "[指挥者] 构建完成" << std::endl;
    return builder.getResult();
}

}

namespace design_patterns::creational {

/**
 * @brief 建造者模式演示函数
 *
 * 演示建造者模式的核心特性：分步骤构建复杂对象，分离构建过程与表示。
 */
void builder_demo() {
	std::cout << "\n========== 建造者模式演示 ==========" << std::endl;

	builder::Director director;

	builder::ConcreteBuilder1 builder1;
	std::unique_ptr<builder::Product> product1 = director.construct(builder1);
	product1->show();

	std::cout << std::endl;

	builder::ConcreteBuilder2 builder2;
	std::unique_ptr<builder::Product> product2 = director.construct(builder2);
	product2->show();

	std::cout << "==========================================\n" << std::endl;
}

}
