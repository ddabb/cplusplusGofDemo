#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::command {

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void undo() const = 0;
    virtual std::string getName() const = 0;
};

class TextEditor {
public:
    TextEditor() : content_("") {
        std::cout << "[TextEditor] Created" << std::endl;
    }

    void type(const std::string& text) {
        std::cout << "[TextEditor] Typing: " << text << std::endl;
        content_ += text;
        std::cout << "[TextEditor] Content: " << content_ << std::endl;
    }

    void deleteText(int length) {
        std::cout << "[TextEditor] Deleting " << length << " characters" << std::endl;
        if (length >= static_cast<int>(content_.size())) {
            content_ = "";
        } else {
            content_.erase(content_.size() - length, length);
        }
        std::cout << "[TextEditor] Content: " << content_ << std::endl;
    }

    void copy() {
        std::cout << "[TextEditor] Copying: " << content_ << std::endl;
        clipboard_ = content_;
        std::cout << "[TextEditor] Clipboard: " << clipboard_ << std::endl;
    }

    void paste() {
        std::cout << "[TextEditor] Pasting from clipboard" << std::endl;
        content_ += clipboard_;
        std::cout << "[TextEditor] Content: " << content_ << std::endl;
    }

    std::string getContent() const {
        return content_;
    }

private:
    std::string content_;
    std::string clipboard_;
};

class TypeCommand : public Command {
public:
    TypeCommand(TextEditor& editor, const std::string& text)
        : editor_(editor), text_(text) {
        std::cout << "[TypeCommand] Created for: " << text_ << std::endl;
    }

    void execute() const override {
        editor_.type(text_);
    }

    void undo() const override {
        editor_.deleteText(text_.size());
    }

    std::string getName() const override {
        return "TypeCommand";
    }

private:
    TextEditor& editor_;
    std::string text_;
};

class DeleteCommand : public Command {
public:
    DeleteCommand(TextEditor& editor, int length, const std::string& deletedText)
        : editor_(editor), length_(length), deletedText_(deletedText) {
        std::cout << "[DeleteCommand] Created for length: " << length_ << std::endl;
    }

    void execute() const override {
        editor_.deleteText(length_);
    }

    void undo() const override {
        editor_.type(deletedText_);
    }

    std::string getName() const override {
        return "DeleteCommand";
    }

private:
    TextEditor& editor_;
    int length_;
    std::string deletedText_;
};

class CopyCommand : public Command {
public:
    explicit CopyCommand(TextEditor& editor) : editor_(editor) {
        std::cout << "[CopyCommand] Created" << std::endl;
    }

    void execute() const override {
        editor_.copy();
    }

    void undo() const override {
        std::cout << "[CopyCommand] Copy cannot be undone" << std::endl;
    }

    std::string getName() const override {
        return "CopyCommand";
    }

private:
    TextEditor& editor_;
};

class PasteCommand : public Command {
public:
    PasteCommand(TextEditor& editor, const std::string& pastedText)
        : editor_(editor), pastedText_(pastedText) {
        std::cout << "[PasteCommand] Created for: " << pastedText_ << std::endl;
    }

    void execute() const override {
        editor_.paste();
    }

    void undo() const override {
        editor_.deleteText(pastedText_.size());
    }

    std::string getName() const override {
        return "PasteCommand";
    }

private:
    TextEditor& editor_;
    std::string pastedText_;
};

class CommandManager {
public:
    CommandManager() : undoIndex_(-1) {
        std::cout << "[CommandManager] Created" << std::endl;
    }

    void executeCommand(std::unique_ptr<Command> command) {
        commands_.resize(undoIndex_ + 1);
        commands_.push_back(std::move(command));
        undoIndex_++;
        commands_[undoIndex_]->execute();
        std::cout << "[CommandManager] Command executed: " << commands_[undoIndex_]->getName() << std::endl;
    }

    void undo() {
        if (undoIndex_ >= 0) {
            std::cout << "\n[CommandManager] Undoing: " << commands_[undoIndex_]->getName() << std::endl;
            commands_[undoIndex_]->undo();
            undoIndex_--;
        } else {
            std::cout << "[CommandManager] Nothing to undo" << std::endl;
        }
    }

    void redo() {
        if (undoIndex_ < static_cast<int>(commands_.size()) - 1) {
            undoIndex_++;
            std::cout << "\n[CommandManager] Redoing: " << commands_[undoIndex_]->getName() << std::endl;
            commands_[undoIndex_]->execute();
        } else {
            std::cout << "[CommandManager] Nothing to redo" << std::endl;
        }
    }

    size_t getCommandCount() const {
        return commands_.size();
    }

private:
    std::vector<std::unique_ptr<Command>> commands_;
    int undoIndex_;
};

}

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

}
