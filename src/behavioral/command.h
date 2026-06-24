#pragma once
// 文件: src/behavioral/command.h
// 说明: 命令模式示例，展示请求封装与撤销/重做功能
// 建议: 演示中删除操作记录被删除内容，生产环境需注意内存管理。

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::command {

/**
 * @brief 命令接口
 *
 * 定义命令的通用接口：执行、撤销、获取名称。
 */
class Command {
public:
    virtual ~Command() = default;
    /**
     * @brief 执行命令
     */
    virtual void execute() const = 0;
    /**
     * @brief 撤销命令
     */
    virtual void undo() const = 0;
    /**
     * @brief 获取命令名称
     * @return 命令名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 文本编辑器
 *
 * 命令模式的接收者，提供文本编辑操作。
 */
class TextEditor {
public:
    TextEditor() : content_("") {
        std::cout << "[文本编辑器] 创建" << std::endl;
    }

    /**
     * @brief 输入文本
     * @param text 要输入的文本
     */
    void type(const std::string& text) {
        std::cout << "[文本编辑器] 输入: " << text << std::endl;
        content_ += text;
        std::cout << "[文本编辑器] 内容: " << content_ << std::endl;
    }

    /**
     * @brief 删除文本
     * @param length 删除长度
     */
    void deleteText(int length) {
        std::cout << "[文本编辑器] 删除 " << length << " 个字符" << std::endl;
        if (length >= static_cast<int>(content_.size())) {
            content_ = "";
        } else {
            content_.erase(content_.size() - length, length);
        }
        std::cout << "[文本编辑器] 内容: " << content_ << std::endl;
    }

    /**
     * @brief 复制文本
     */
    void copy() {
        std::cout << "[文本编辑器] 复制: " << content_ << std::endl;
        clipboard_ = content_;
        std::cout << "[文本编辑器] 剪贴板: " << clipboard_ << std::endl;
    }

    /**
     * @brief 粘贴文本
     */
    void paste() {
        std::cout << "[文本编辑器] 从剪贴板粘贴" << std::endl;
        content_ += clipboard_;
        std::cout << "[文本编辑器] 内容: " << content_ << std::endl;
    }

    /**
     * @brief 获取内容
     * @return 当前内容
     */
    std::string getContent() const {
        return content_;
    }

private:
    std::string content_;
    std::string clipboard_;
};

/**
 * @brief 输入命令
 */
class TypeCommand : public Command {
public:
    TypeCommand(TextEditor& editor, const std::string& text)
        : editor_(editor), text_(text) {
        std::cout << "[输入命令] 创建，内容: " << text_ << std::endl;
    }

    void execute() const override {
        editor_.type(text_);
    }

    void undo() const override {
        editor_.deleteText(text_.size());
    }

    std::string getName() const override {
        return "输入命令";
    }

private:
    TextEditor& editor_;
    std::string text_;
};

/**
 * @brief 删除命令
 */
class DeleteCommand : public Command {
public:
    DeleteCommand(TextEditor& editor, int length, const std::string& deletedText)
        : editor_(editor), length_(length), deletedText_(deletedText) {
        std::cout << "[删除命令] 创建，长度: " << length_ << std::endl;
    }

    void execute() const override {
        editor_.deleteText(length_);
    }

    void undo() const override {
        editor_.type(deletedText_);
    }

    std::string getName() const override {
        return "删除命令";
    }

private:
    TextEditor& editor_;
    int length_;
    std::string deletedText_;
};

/**
 * @brief 复制命令
 */
class CopyCommand : public Command {
public:
    explicit CopyCommand(TextEditor& editor) : editor_(editor) {
        std::cout << "[复制命令] 创建" << std::endl;
    }

    void execute() const override {
        editor_.copy();
    }

    void undo() const override {
        std::cout << "[复制命令] 复制操作无法撤销" << std::endl;
    }

    std::string getName() const override {
        return "复制命令";
    }

private:
    TextEditor& editor_;
};

/**
 * @brief 粘贴命令
 */
class PasteCommand : public Command {
public:
    PasteCommand(TextEditor& editor, const std::string& pastedText)
        : editor_(editor), pastedText_(pastedText) {
        std::cout << "[粘贴命令] 创建，内容: " << pastedText_ << std::endl;
    }

    void execute() const override {
        editor_.paste();
    }

    void undo() const override {
        editor_.deleteText(pastedText_.size());
    }

    std::string getName() const override {
        return "粘贴命令";
    }

private:
    TextEditor& editor_;
    std::string pastedText_;
};

/**
 * @brief 命令管理器
 *
 * 管理命令的执行、撤销和重做。
 */
class CommandManager {
public:
    CommandManager() : undoIndex_(-1) {
        std::cout << "[命令管理器] 创建" << std::endl;
    }

    /**
     * @brief 执行命令
     * @param command 命令对象
     */
    void executeCommand(std::unique_ptr<Command> command) {
        commands_.resize(undoIndex_ + 1);
        commands_.push_back(std::move(command));
        undoIndex_++;
        commands_[undoIndex_]->execute();
        std::cout << "[命令管理器] 命令执行: " << commands_[undoIndex_]->getName() << std::endl;
    }

    /**
     * @brief 撤销命令
     */
    void undo() {
        if (undoIndex_ >= 0) {
            std::cout << "\n[命令管理器] 撤销: " << commands_[undoIndex_]->getName() << std::endl;
            commands_[undoIndex_]->undo();
            undoIndex_--;
        } else {
            std::cout << "[命令管理器] 没有可撤销的操作" << std::endl;
        }
    }

    /**
     * @brief 重做命令
     */
    void redo() {
        if (undoIndex_ < static_cast<int>(commands_.size()) - 1) {
            undoIndex_++;
            std::cout << "\n[命令管理器] 重做: " << commands_[undoIndex_]->getName() << std::endl;
            commands_[undoIndex_]->execute();
        } else {
            std::cout << "[命令管理器] 没有可重做的操作" << std::endl;
        }
    }

    /**
     * @brief 获取命令数量
     * @return 命令数量
     */
    size_t getCommandCount() const {
        return commands_.size();
    }

private:
    std::vector<std::unique_ptr<Command>> commands_;
    int undoIndex_;
};

}

namespace design_patterns::behavioral {
void command_demo();

}
