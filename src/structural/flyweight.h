#pragma once
// 文件: src/structural/flyweight.h
// 说明: 享元模式示例，使用 CharacterFactory 复用字符对象
// 建议: 演示中统计信息为示例，实际统计請根据真实数据源计算。

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace design_patterns::structural::flyweight {

/**
 * @brief 字符接口
 *
 * 定义字符对象的通用接口。
 */
class Character {
public:
    virtual ~Character() = default;
    /**
     * @brief 显示字符
     * @param font 字体
     * @param size 大小
     * @param x x坐标
     * @param y y坐标
     */
    virtual void display(const std::string& font, int size, int x, int y) const = 0;
    /**
     * @brief 获取符号
     * @return 字符符号
     */
    virtual char getSymbol() const = 0;
};

/**
 * @brief 字母字符
 *
 * 具体的字符实现类。
 */
class LetterCharacter : public Character {
public:
    explicit LetterCharacter(char symbol) : symbol_(symbol) {
        std::cout << "[字母字符] 创建: '" << symbol_ << "'" << std::endl;
    }

    void display(const std::string& font, int size, int x, int y) const override {
        std::cout << "[字母字符] 在 (" << x << "," << y << ") 显示 '" << symbol_ 
                  << "'，字体 '" << font << "'，大小 " << size << std::endl;
    }

    char getSymbol() const override {
        return symbol_;
    }

private:
    char symbol_;
};

/**
 * @brief 字符工厂
 *
 * 负责创建和管理共享的字符对象。
 */
class CharacterFactory {
public:
    /**
     * @brief 获取字符对象（复用已创建的对象）
     * @param symbol 字符符号
     * @return 字符对象指针
     */
    Character* getCharacter(char symbol) {
        auto it = characters_.find(symbol);
        if (it == characters_.end()) {
            characters_[symbol] = std::make_unique<LetterCharacter>(symbol);
        }
        return characters_[symbol].get();
    }

    /**
     * @brief 获取字符数量
     * @return 唯一字符数量
     */
    size_t getCharacterCount() const {
        return characters_.size();
    }

    /**
     * @brief 显示所有字符
     */
    void displayAllCharacters() const {
        std::cout << "[字符工厂] 创建了 " << characters_.size() << " 个唯一字符: ";
        for (const auto& pair : characters_) {
            std::cout << "'" << pair.first << "' ";
        }
        std::cout << std::endl;
    }

private:
    std::unordered_map<char, std::unique_ptr<Character>> characters_;
};

/**
 * @brief 文本编辑器
 *
 * 使用享元模式管理字符对象。
 */
class TextEditor {
public:
    TextEditor() : factory_(std::make_unique<CharacterFactory>()) {
        std::cout << "[文本编辑器] 创建" << std::endl;
    }

    /**
     * @brief 添加字符
     * @param symbol 字符符号
     * @param font 字体
     * @param size 大小
     * @param x x坐标
     * @param y y坐标
     */
    void addCharacter(char symbol, const std::string& font, int size, int x, int y) {
        Character* character = factory_->getCharacter(symbol);
        character->display(font, size, x, y);
    }

    /**
     * @brief 获取唯一字符数量
     * @return 唯一字符数量
     */
    size_t getUniqueCharacterCount() const {
        return factory_->getCharacterCount();
    }

    /**
     * @brief 显示统计信息
     */
    void showStatistics() const {
        factory_->displayAllCharacters();
    }

private:
    std::unique_ptr<CharacterFactory> factory_;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/flyweight.cpp
void flyweight_demo();

}
