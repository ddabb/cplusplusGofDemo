#include "composite.h"
#include <iostream>

namespace design_patterns::structural {

void composite_demo() {
	std::cout << "\n========== Composite Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 组合模式核心：将对象组合成树形结构，统一处理单个和组合对象\n" << std::endl;

	std::cout << "[Demo] --- Building Tree Structure ---" << std::endl;
	auto root = std::make_unique<composite::Composite>("Root");
	auto branch1 = std::make_unique<composite::Composite>("Branch 1");
	auto branch2 = std::make_unique<composite::Composite>("Branch 2");

	auto leaf1 = std::make_unique<composite::Leaf>("Leaf 1");
	auto leaf2 = std::make_unique<composite::Leaf>("Leaf 2");
	auto leaf3 = std::make_unique<composite::Leaf>("Leaf 3");
	auto leaf4 = std::make_unique<composite::Leaf>("Leaf 4");

	branch1->add(std::move(leaf1));
	branch1->add(std::move(leaf2));

	branch2->add(std::move(leaf3));
	branch2->add(std::move(leaf4));

	root->add(std::move(branch1));
	root->add(std::move(branch2));

	std::cout << "\n[Demo] --- Tree Structure ---" << std::endl;
	root->operation();

	std::cout << "\n[Demo] --- Adding New Leaf ---" << std::endl;
	auto newLeaf = std::make_unique<composite::Leaf>("New Leaf");
	root->add(std::move(newLeaf));

	std::cout << "\n[Demo] --- Updated Tree Structure ---" << std::endl;
	root->operation();

	std::cout << "\n[Demo] --- Removing Branch 2 ---" << std::endl;
	root->remove(1);

	std::cout << "\n[Demo] --- Final Tree Structure ---" << std::endl;
	root->operation();

	std::cout << "============================================\n" << std::endl;
}

}
