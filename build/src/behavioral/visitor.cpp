#include "visitor.h"

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

} // namespace design_patterns::behavioral
