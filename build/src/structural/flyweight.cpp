#include "flyweight.h"
#include <iostream>

namespace design_patterns::structural {

void flyweight_demo() {
	std::cout << "\n========== Flyweight Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] Flyweight Pattern: Share objects to support large numbers efficiently\n" << std::endl;

	std::unique_ptr<flyweight::TextEditor> editor = std::make_unique<flyweight::TextEditor>();

	std::cout << "[Demo] --- Adding Characters ---" << std::endl;

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

	std::cout << "\n[Demo] --- Statistics ---" << std::endl;
	editor->showStatistics();
	std::cout << "[TextEditor] Total characters displayed: 10" << std::endl;
	std::cout << "[TextEditor] Unique characters created: " << editor->getUniqueCharacterCount() << std::endl;

	std::cout << "\n[Demo] Memory saved: Only 7 objects created instead of 10" << std::endl;

	std::cout << "==========================================\n" << std::endl;
}

}
