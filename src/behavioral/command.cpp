#include "behavioral/command.h"

namespace design_patterns::behavioral {

/**
 * @brief 命令模式演示函数
 *
 * 演示命令模式的核心特性：将请求封装成对象，支持执行、撤销和重做。
 */
void command_demo() {
	std::cout << "\n========== 命令模式演示 ==========" << std::endl;
	std::cout << "[演示] 命令模式核心：将请求封装成对象，支持执行、撤销和重做\n" << std::endl;

	command::TextEditor editor;
	command::CommandManager manager;

	std::cout << "\n[演示] --- 输入文本 ---" << std::endl;
	manager.executeCommand(std::make_unique<command::TypeCommand>(editor, "你好"));
	manager.executeCommand(std::make_unique<command::TypeCommand>(editor, " 世界"));

	std::cout << "\n[演示] --- 复制文本 ---" << std::endl;
	manager.executeCommand(std::make_unique<command::CopyCommand>(editor));

	std::cout << "\n[演示] --- 粘贴文本 ---" << std::endl;
	manager.executeCommand(std::make_unique<command::PasteCommand>(editor, "你好 世界"));

	std::cout << "\n[演示] --- 撤销 ---" << std::endl;
	manager.undo();

	std::cout << "\n[演示] --- 再次撤销 ---" << std::endl;
	manager.undo();

	std::cout << "\n[演示] --- 重做 ---" << std::endl;
	manager.redo();

	std::cout << "\n[演示] --- 删除文本 ---" << std::endl;
	manager.executeCommand(std::make_unique<command::DeleteCommand>(editor, 6, "世界"));

	std::cout << "\n[演示] --- 撤销删除 ---" << std::endl;
	manager.undo();

	std::cout << "\n==========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
