#pragma once
// 文件: src/behavioral/command.h
// 说明: 命令模式示例，展示请求封装与撤销/重做功能
// 建议: 演示中删除操作记录被删除内容，生产环境需注意内存管理。

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
    TextEditor();

    /**
     * @brief 输入文本
     * @param text 要输入的文本
     */
    void type(const std::string& text);

    /**
     * @brief 删除文本
     * @param length 删除长度
     */
    void deleteText(int length);

    /**
     * @brief 复制文本
     */
    void copy();

    /**
     * @brief 粘贴文本
     */
    void paste();

    /**
     * @brief 获取内容
     * @return 当前内容
     */
    std::string getContent() const;

private:
    std::string content_;
    std::string clipboard_;
};

/**
 * @brief 输入命令
 */
class TypeCommand : public Command {
public:
    TypeCommand(TextEditor& editor, const std::string& text);

    void execute() const override;
    void undo() const override;
    std::string getName() const override;

private:
    TextEditor& editor_;
    std::string text_;
};

/**
 * @brief 删除命令
 */
class DeleteCommand : public Command {
public:
    DeleteCommand(TextEditor& editor, int length, const std::string& deletedText);

    void execute() const override;
    void undo() const override;
    std::string getName() const override;

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
    explicit CopyCommand(TextEditor& editor);

    void execute() const override;
    void undo() const override;
    std::string getName() const override;

private:
    TextEditor& editor_;
};

/**
 * @brief 粘贴命令
 */
class PasteCommand : public Command {
public:
    PasteCommand(TextEditor& editor, const std::string& pastedText);

    void execute() const override;
    void undo() const override;
    std::string getName() const override;

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
    CommandManager();

    /**
     * @brief 执行命令
     * @param command 命令对象
     */
    void executeCommand(std::unique_ptr<Command> command);

    /**
     * @brief 撤销命令
     */
    void undo();

    /**
     * @brief 重做命令
     */
    void redo();

    /**
     * @brief 获取命令数量
     * @return 命令数量
     */
    size_t getCommandCount() const;

private:
    std::vector<std::unique_ptr<Command>> commands_;
    int undoIndex_;
};

}

namespace design_patterns::behavioral {
void command_demo();

}
