#include "iterator.h"

namespace design_patterns::behavioral {

void iterator_demo() {
	std::cout << "\n========== Iterator Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 迭代器模式核心：顺序访问聚合对象元素，不暴露内部表示\n" << std::endl;

	std::cout << "[Demo] --- Creating List ---" << std::endl;
	iterator::ListAggregate<std::string> list;
	list.add("Apple");
	list.add("Banana");
	list.add("Cherry");
	list.add("Date");
	list.add("Elderberry");

	std::cout << "\n[Demo] --- Forward Iteration ---" << std::endl;
	auto forwardIterator = list.createIterator();
	while (forwardIterator->hasNext()) {
		std::cout << "Element: " << forwardIterator->next() << std::endl;
	}

	std::cout << "\n[Demo] --- Reverse Iteration ---" << std::endl;
	auto reverseIterator = list.createReverseIterator();
	while (reverseIterator->hasNext()) {
		std::cout << "Element: " << reverseIterator->next() << std::endl;
	}

	std::cout << "\n[Demo] --- Integer List ---" << std::endl;
	iterator::ListAggregate<int> intList;
	intList.add(10);
	intList.add(20);
	intList.add(30);
	intList.add(40);
	intList.add(50);

	std::cout << "\n[Demo] --- Iterating Integer List ---" << std::endl;
	auto intIterator = intList.createIterator();
	while (intIterator->hasNext()) {
		std::cout << "Number: " << intIterator->next() << std::endl;
	}

	std::cout << "\n==========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
