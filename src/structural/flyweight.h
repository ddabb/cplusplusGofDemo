#pragma once
// 文件: src/structural/flyweight.h
// 说明: 享元模式示例，使用 CharacterFactory 复用字符对象
// 建议: 演示中统计信息为示例，实际统计請根据真实数据源计算。

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace design_patterns::structural::flyweight {

class Character {
public:
    virtual ~Character() = default;
    virtual void display(const std::string& font, int size, int x, int y) const = 0;
    virtual char getSymbol() const = 0;
};

class LetterCharacter : public Character {
public:
    explicit LetterCharacter(char symbol) : symbol_(symbol) {
        std::cout << "[LetterCharacter] Creating: '" << symbol_ << "'" << std::endl;
    }

    void display(const std::string& font, int size, int x, int y) const override {
        std::cout << "[LetterCharacter] Displaying '" << symbol_ 
                  << "' at (" << x << "," << y << ") with font '" 
                  << font << "' and size " << size << std::endl;
    }

    char getSymbol() const override {
        return symbol_;
    }

private:
    char symbol_;
};

class CharacterFactory {
public:
    Character* getCharacter(char symbol) {
        auto it = characters_.find(symbol);
        if (it == characters_.end()) {
            characters_[symbol] = std::make_unique<LetterCharacter>(symbol);
        }
        return characters_[symbol].get();
    }

    size_t getCharacterCount() const {
        return characters_.size();
    }

    void displayAllCharacters() const {
        std::cout << "[CharacterFactory] Created " << characters_.size() << " unique characters: ";
        for (const auto& pair : characters_) {
            std::cout << "'" << pair.first << "' ";
        }
        std::cout << std::endl;
    }

private:
    std::unordered_map<char, std::unique_ptr<Character>> characters_;
};

class TextEditor {
public:
    TextEditor() : factory_(std::make_unique<CharacterFactory>()) {
        std::cout << "[TextEditor] Created" << std::endl;
    }

    void addCharacter(char symbol, const std::string& font, int size, int x, int y) {
        Character* character = factory_->getCharacter(symbol);
        character->display(font, size, x, y);
    }

    size_t getUniqueCharacterCount() const {
        return factory_->getCharacterCount();
    }

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
