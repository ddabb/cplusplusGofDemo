#include "structural/flyweight.h"
#include <iostream>

namespace design_patterns::structural::flyweight {

LetterCharacter::LetterCharacter(char symbol) : symbol_(symbol) {
    std::cout << "[字母字符] 创建: '" << symbol_ << "'" << std::endl;
}

void LetterCharacter::display(const std::string& font, int size, int x, int y) const {
    std::cout << "[字母字符] 在 (" << x << "," << y << ") 显示 '" << symbol_ 
              << "'，字体 '" << font << "'，大小 " << size << std::endl;
}

char LetterCharacter::getSymbol() const {
    return symbol_;
}

Character* CharacterFactory::getCharacter(char symbol) {
    auto it = characters_.find(symbol);
    if (it == characters_.end()) {
        characters_[symbol] = std::make_unique<LetterCharacter>(symbol);
    }
    return characters_[symbol].get();
}

size_t CharacterFactory::getCharacterCount() const {
    return characters_.size();
}

void CharacterFactory::displayAllCharacters() const {
    std::cout << "[字符工厂] 创建了 " << characters_.size() << " 个唯一字符: ";
    for (const auto& pair : characters_) {
        std::cout << "'" << pair.first << "' ";
    }
    std::cout << std::endl;
}

TextEditor::TextEditor() : factory_(std::make_unique<CharacterFactory>()) {
    std::cout << "[文本编辑器] 创建" << std::endl;
}

void TextEditor::addCharacter(char symbol, const std::string& font, int size, int x, int y) {
    Character* character = factory_->getCharacter(symbol);
    character->display(font, size, x, y);
}

size_t TextEditor::getUniqueCharacterCount() const {
    return factory_->getCharacterCount();
}

void TextEditor::showStatistics() const {
    factory_->displayAllCharacters();
}

}

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
