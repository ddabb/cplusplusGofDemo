#include "creational/builder.h"
#include <iostream>

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
