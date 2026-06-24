#include "behavioral/iterator.h"

namespace design_patterns::behavioral {

/**
 * @brief 迭代器模式演示函数
 *
 * 演示迭代器模式的核心特性：顺序访问聚合对象元素，不暴露内部表示。
 */
void iterator_demo() {
	std::cout << "\n========== 迭代器模式演示 ==========" << std::endl;
	std::cout << "[演示] 迭代器模式核心：顺序访问聚合对象元素，不暴露内部表示\n" << std::endl;

	std::cout << "[演示] --- 创建列表 ---" << std::endl;
	iterator::ListAggregate<std::string> list;
	list.add("苹果");
	list.add("香蕉");
	list.add("樱桃");
	list.add("椰枣");
	list.add("接骨木果");

	std::cout << "\n[演示] --- 正向遍历 ---" << std::endl;
	auto forwardIterator = list.createIterator();
	while (forwardIterator->hasNext()) {
		std::cout << "元素: " << forwardIterator->next() << std::endl;
	}

	std::cout << "\n[演示] --- 反向遍历 ---" << std::endl;
	auto reverseIterator = list.createReverseIterator();
	while (reverseIterator->hasNext()) {
		std::cout << "元素: " << reverseIterator->next() << std::endl;
	}

	std::cout << "\n[演示] --- 整数列表 ---" << std::endl;
	iterator::ListAggregate<int> intList;
	intList.add(10);
	intList.add(20);
	intList.add(30);
	intList.add(40);
	intList.add(50);

	std::cout << "\n[演示] --- 遍历整数列表 ---" << std::endl;
	auto intIterator = intList.createIterator();
	while (intIterator->hasNext()) {
		std::cout << "数字: " << intIterator->next() << std::endl;
	}

	std::cout << "\n==========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
