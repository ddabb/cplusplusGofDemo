#include "structural/composite.h"
#include <iostream>

namespace design_patterns::structural {

/**
 * @brief 组合模式演示函数
 *
 * 演示组合模式的核心特性：将对象组合成树形结构，统一处理单个对象和组合对象。
 */
void composite_demo() {
	std::cout << "\n========== 组合模式演示 ==========" << std::endl;
	std::cout << "[演示] 组合模式核心：将对象组合成树形结构，统一处理单个和组合对象\n" << std::endl;

	std::cout << "[演示] --- 构建树形结构 ---" << std::endl;
	auto root = std::make_unique<composite::Composite>("根节点");
	auto branch1 = std::make_unique<composite::Composite>("分支 1");
	auto branch2 = std::make_unique<composite::Composite>("分支 2");

	auto leaf1 = std::make_unique<composite::Leaf>("叶子 1");
	auto leaf2 = std::make_unique<composite::Leaf>("叶子 2");
	auto leaf3 = std::make_unique<composite::Leaf>("叶子 3");
	auto leaf4 = std::make_unique<composite::Leaf>("叶子 4");

	branch1->add(std::move(leaf1));
	branch1->add(std::move(leaf2));

	branch2->add(std::move(leaf3));
	branch2->add(std::move(leaf4));

	root->add(std::move(branch1));
	root->add(std::move(branch2));

	std::cout << "\n[演示] --- 树形结构 ---" << std::endl;
	root->operation();

	std::cout << "\n[演示] --- 添加新叶子 ---" << std::endl;
	auto newLeaf = std::make_unique<composite::Leaf>("新叶子");
	root->add(std::move(newLeaf));

	std::cout << "\n[演示] --- 更新后的树形结构 ---" << std::endl;
	root->operation();

	std::cout << "\n[演示] --- 移除分支 2 ---" << std::endl;
	root->remove(1);

	std::cout << "\n[演示] --- 最终树形结构 ---" << std::endl;
	root->operation();

	std::cout << "============================================\n" << std::endl;
}

}
