#include "structural/flyweight.h"
#include <iostream>

namespace design_patterns::structural {

/**
 * @brief 享元模式演示函数
 *
 * 演示享元模式的核心特性：共享对象以高效支持大量细粒度对象。
 */
void flyweight_demo() {
	std::cout << "\n========== 享元模式演示 ==========" << std::endl;
	std::cout << "[演示] 享元模式核心：共享对象以高效支持大量细粒度对象\n" << std::endl;

	std::unique_ptr<flyweight::TextEditor> editor = std::make_unique<flyweight::TextEditor>();

	std::cout << "[演示] --- 添加字符 ---" << std::endl;

	editor->addCharacter('H', "Arial", 12, 0, 0);
	editor->addCharacter('e', "Arial", 12, 10, 0);
	editor->addCharacter('l', "Arial", 12, 20, 0);
	editor->addCharacter('l', "Arial", 12, 30, 0);
	editor->addCharacter('o', "Arial", 12, 40, 0);

	editor->addCharacter('W', "Times", 14, 0, 20);
	editor->addCharacter('o', "Times", 14, 15, 20);
	editor->addCharacter('r', "Times", 14, 30, 20);
	editor->addCharacter('l', "Times", 14, 45, 20);
	editor->addCharacter('d', "Times", 14, 60, 20);

	std::cout << "\n[演示] --- 统计信息 ---" << std::endl;
	editor->showStatistics();
	std::cout << "[文本编辑器] 显示的字符总数: 10" << std::endl;
	std::cout << "[文本编辑器] 创建的唯一字符数: " << editor->getUniqueCharacterCount() << std::endl;

	std::cout << "\n[演示] 节省内存: 只创建了 7 个对象，而不是 10 个" << std::endl;

	std::cout << "==========================================\n" << std::endl;
}

}
