#include "creational/prototype.h"
#include <iostream>

namespace design_patterns::creational {

/**
 * @brief 原型模式演示函数
 *
 * 演示原型模式的核心特性：通过拷贝原型创建新对象，避免重复初始化。
 */
void prototype_demo() {
	std::cout << "\n========== 原型模式演示 ==========" << std::endl;
	std::cout << "[演示] 原型模式核心：通过拷贝原型创建新对象，避免重复初始化\n" << std::endl;

	prototype::ShapePrototype circle("圆形", "红色");
	prototype::ShapePrototype rectangle("矩形", "蓝色");

	std::unique_ptr<prototype::Prototype> clonedCircle(circle.clone());
	std::unique_ptr<prototype::Prototype> clonedRectangle(rectangle.clone());

	prototype::ShapePrototype* castedCircle = dynamic_cast<prototype::ShapePrototype*>(clonedCircle.get());
	if (castedCircle) {
		castedCircle->setColor("绿色");
	}

	std::cout << "\n[演示] 原始对象:" << std::endl;
	circle.show();
	rectangle.show();

	std::cout << "\n[演示] 克隆对象(已修改):" << std::endl;
	clonedCircle->show();
	clonedRectangle->show();

	std::cout << "\n[演示] 使用原型管理器:" << std::endl;
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
