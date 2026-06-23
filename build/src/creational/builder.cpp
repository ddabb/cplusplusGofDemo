#include "builder.h"
#include <iostream>

namespace design_patterns::creational {

void builder_demo() {
	std::cout << "\n========== Builder Pattern Demo ==========" << std::endl;

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
