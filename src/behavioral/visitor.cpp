#include "behavioral/visitor.h"
#include <iostream>

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

} // namespace design_patterns::behavioral
