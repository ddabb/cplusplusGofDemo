#include "behavioral/command.h"
#include <iostream>

namespace design_patterns::behavioral::command {

TextEditor::TextEditor() : content_(""), clipboard_("") {
    std::cout << "[文本编辑器] 创建" << std::endl;
}

void TextEditor::type(const std::string& text) {
    content_ += text;
    std::cout << "[文本编辑器] 输入: \"" << text << "\"，当前内容: \"" << content_ << "\"" << std::endl;
}

void TextEditor::deleteText(int length) {
    if (length <= 0) return;
    if (length > static_cast<int>(content_.size())) {
        length = static_cast<int>(content_.size());
    }
    std::string deleted = content_.substr(content_.size() - length);
    content_.resize(content_.size() - length);
    std::cout << "[文本编辑器] 删除 " << length << " 个字符，删除内容: \"" << deleted << "\"，当前内容: \"" << content_ << "\"" << std::endl;
}

void TextEditor::copy() {
    clipboard_ = content_;
    std::cout << "[文本编辑器] 复制到剪贴板: \"" << clipboard_ << "\"" << std::endl;
}

void TextEditor::paste() {
    content_ += clipboard_;
    std::cout << "[文本编辑器] 粘贴: \"" << clipboard_ << "\"，当前内容: \"" << content_ << "\"" << std::endl;
}

std::string TextEditor::getContent() const {
    return content_;
}

TypeCommand::TypeCommand(TextEditor& editor, const std::string& text)
    : editor_(editor), text_(text) {}

void TypeCommand::execute() const {
    editor_.type(text_);
}

void TypeCommand::undo() const {
    editor_.deleteText(static_cast<int>(text_.size()));
}

std::string TypeCommand::getName() const {
    return "输入命令";
}

DeleteCommand::DeleteCommand(TextEditor& editor, int length, const std::string& deletedText)
    : editor_(editor), length_(length), deletedText_(deletedText) {}

void DeleteCommand::execute() const {
    editor_.deleteText(length_);
}

void DeleteCommand::undo() const {
    editor_.type(deletedText_);
}

std::string DeleteCommand::getName() const {
    return "删除命令";
}

CopyCommand::CopyCommand(TextEditor& editor) : editor_(editor) {}

void CopyCommand::execute() const {
    editor_.copy();
}

void CopyCommand::undo() const {
    std::cout << "[复制命令] 撤销复制" << std::endl;
}

std::string CopyCommand::getName() const {
    return "复制命令";
}

PasteCommand::PasteCommand(TextEditor& editor, const std::string& pastedText)
    : editor_(editor), pastedText_(pastedText) {}

void PasteCommand::execute() const {
    editor_.type(pastedText_);
}

void PasteCommand::undo() const {
    editor_.deleteText(static_cast<int>(pastedText_.size()));
}

std::string PasteCommand::getName() const {
    return "粘贴命令";
}

CommandManager::CommandManager() : undoIndex_(-1) {}

void CommandManager::executeCommand(std::unique_ptr<Command> command) {
    commands_.resize(undoIndex_ + 1);
    commands_.push_back(std::move(command));
    undoIndex_++;
    std::cout << "[命令管理器] 执行命令: " << commands_[undoIndex_]->getName() << std::endl;
    commands_[undoIndex_]->execute();
}

void CommandManager::undo() {
    if (undoIndex_ >= 0) {
        std::cout << "[命令管理器] 撤销命令: " << commands_[undoIndex_]->getName() << std::endl;
        commands_[undoIndex_]->undo();
        undoIndex_--;
    } else {
        std::cout << "[命令管理器] 没有可撤销的命令" << std::endl;
    }
}

void CommandManager::redo() {
    if (undoIndex_ < static_cast<int>(commands_.size()) - 1) {
        undoIndex_++;
        std::cout << "[命令管理器] 重做命令: " << commands_[undoIndex_]->getName() << std::endl;
        commands_[undoIndex_]->execute();
    } else {
        std::cout << "[命令管理器] 没有可重做的命令" << std::endl;
    }
}

size_t CommandManager::getCommandCount() const {
    return commands_.size();
}

}

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

}
