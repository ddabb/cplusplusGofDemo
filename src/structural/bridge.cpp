#include "structural/bridge.h"
#include <iostream>

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
