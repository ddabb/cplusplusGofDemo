#include "behavioral/command.h"

namespace design_patterns::behavioral {

void command_demo() {
	std::cout << "\n========== Command Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 命令模式核心：将请求封装成对象，支持执行、撤销和重做\n" << std::endl;

	command::TextEditor editor;
	command::CommandManager manager;

	std::cout << "\n[Demo] --- Typing Text ---" << std::endl;
	manager.executeCommand(std::make_unique<command::TypeCommand>(editor, "Hello"));
	manager.executeCommand(std::make_unique<command::TypeCommand>(editor, " World"));

	std::cout << "\n[Demo] --- Copying Text ---" << std::endl;
	manager.executeCommand(std::make_unique<command::CopyCommand>(editor));

	std::cout << "\n[Demo] --- Pasting Text ---" << std::endl;
	manager.executeCommand(std::make_unique<command::PasteCommand>(editor, "Hello World"));

	std::cout << "\n[Demo] --- Undo ---" << std::endl;
	manager.undo();

	std::cout << "\n[Demo] --- Undo Again ---" << std::endl;
	manager.undo();

	std::cout << "\n[Demo] --- Redo ---" << std::endl;
	manager.redo();

	std::cout << "\n[Demo] --- Deleting Text ---" << std::endl;
	manager.executeCommand(std::make_unique<command::DeleteCommand>(editor, 6, "World"));

	std::cout << "\n[Demo] --- Undo Delete ---" << std::endl;
	manager.undo();

	std::cout << "\n==========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
