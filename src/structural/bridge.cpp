#include "structural/bridge.h"
#include <iostream>

namespace design_patterns::structural::bridge {

std::string ConcreteImplementorA::operationImpl(const std::string& data) const {
    std::cout << "[具体实现A] 使用方法 A 处理数据" << std::endl;
    return "[方法A结果] " + data;
}

std::string ConcreteImplementorB::operationImpl(const std::string& data) const {
    std::cout << "[具体实现B] 使用方法 B 处理数据" << std::endl;
    return "[方法B结果] " + data;
}

Abstraction::Abstraction(std::unique_ptr<Implementor> implementor)
    : implementor_(std::move(implementor)) {
    std::cout << "[抽象类] 构造函数被调用" << std::endl;
}

void Abstraction::operation(const std::string& data) const {
    std::cout << "[抽象类] 调用实现对象..." << std::endl;
    std::string result = implementor_->operationImpl(data);
    std::cout << "[抽象类] 结果: " << result << std::endl;
}

RefinedAbstraction::RefinedAbstraction(std::unique_ptr<Implementor> implementor)
    : Abstraction(std::move(implementor)) {
    std::cout << "[扩展抽象类] 构造函数被调用" << std::endl;
}

void RefinedAbstraction::operation(const std::string& data) const {
    std::cout << "[扩展抽象类] 预处理..." << std::endl;
    Abstraction::operation(data);
    std::cout << "[扩展抽象类] 后处理..." << std::endl;
}

void RefinedAbstraction::extraOperation(const std::string& data) const {
    std::cout << "[扩展抽象类] 额外操作: " << data << std::endl;
    std::string result = implementor_->operationImpl("额外: " + data);
    std::cout << "[扩展抽象类] 额外结果: " << result << std::endl;
}

}

namespace design_patterns::structural {

/**
 * @brief 桥接模式演示函数
 *
 * 演示桥接模式的核心特性：将抽象部分与实现部分分离，使它们可以独立变化。
 */
void bridge_demo() {
	std::cout << "\n========== 桥接模式演示 ==========" << std::endl;
	std::cout << "[演示] 桥接模式核心：将抽象部分与实现部分分离，独立变化\n" << std::endl;

	std::cout << "[演示] --- 抽象类 + 实现A ---" << std::endl;
	std::unique_ptr<bridge::Abstraction> abstraction1 = 
		std::make_unique<bridge::Abstraction>(std::make_unique<bridge::ConcreteImplementorA>());
	abstraction1->operation("你好 桥接");

	std::cout << std::endl;

	std::cout << "[演示] --- 抽象类 + 实现B ---" << std::endl;
	std::unique_ptr<bridge::Abstraction> abstraction2 = 
		std::make_unique<bridge::Abstraction>(std::make_unique<bridge::ConcreteImplementorB>());
	abstraction2->operation("你好 桥接");

	std::cout << std::endl;

	std::cout << "[演示] --- 扩展抽象类 + 实现A ---" << std::endl;
	std::unique_ptr<bridge::RefinedAbstraction> refinedAbstraction1 = 
		std::make_unique<bridge::RefinedAbstraction>(std::make_unique<bridge::ConcreteImplementorA>());
	refinedAbstraction1->operation("你好 扩展桥接");
	refinedAbstraction1->extraOperation("额外数据");

	std::cout << std::endl;

	std::cout << "[演示] --- 扩展抽象类 + 实现B ---" << std::endl;
	std::unique_ptr<bridge::RefinedAbstraction> refinedAbstraction2 = 
		std::make_unique<bridge::RefinedAbstraction>(std::make_unique<bridge::ConcreteImplementorB>());
	refinedAbstraction2->operation("你好 扩展桥接");
	refinedAbstraction2->extraOperation("额外数据");

	std::cout << "==========================================\n" << std::endl;
}

}
