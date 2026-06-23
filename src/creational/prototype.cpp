#include "creational/prototype.h"
#include <iostream>

namespace design_patterns::creational {

void prototype_demo() {
	std::cout << "\n========== Prototype Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 原型模式核心：通过拷贝原型创建新对象，避免重复初始化\n" << std::endl;

	prototype::ShapePrototype circle("Circle", "Red");
	prototype::ShapePrototype rectangle("Rectangle", "Blue");

	std::unique_ptr<prototype::Prototype> clonedCircle(circle.clone());
	std::unique_ptr<prototype::Prototype> clonedRectangle(rectangle.clone());

	prototype::ShapePrototype* castedCircle = dynamic_cast<prototype::ShapePrototype*>(clonedCircle.get());
	if (castedCircle) {
		castedCircle->setColor("Green");
	}

	std::cout << "\n[Demo] Original objects:" << std::endl;
	circle.show();
	rectangle.show();

	std::cout << "\n[Demo] Cloned objects (modified):" << std::endl;
	clonedCircle->show();
	clonedRectangle->show();

	std::cout << "\n[Demo] Using PrototypeManager:" << std::endl;
	prototype::PrototypeManager manager;
	manager.registerPrototype("circle", &circle);
	manager.registerPrototype("rectangle", &rectangle);

	std::unique_ptr<prototype::Prototype> newCircle(manager.create("circle"));
	std::unique_ptr<prototype::Prototype> newRectangle(manager.create("rectangle"));

	if (newCircle) newCircle->show();
	if (newRectangle) newRectangle->show();

	std::cout << "=============================================\n" << std::endl;
}

}
