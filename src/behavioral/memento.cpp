#include "behavioral/memento.h"
#include <iostream>

namespace design_patterns::behavioral {

void memento_demo() {
    std::cout << "\n========== Memento Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] Memento Pattern: capture and restore object state\n" << std::endl;

    std::cout << "[Demo] --- Creating Game Character ---" << std::endl;
    Originator gameCharacter(1, 0, 100);

    Caretaker caretaker;

    std::cout << "\n[Demo] --- Playing Game ---" << std::endl;
    
    std::cout << "\n[Demo] Save point 1" << std::endl;
    caretaker.saveMemento(gameCharacter.createMemento());

    gameCharacter.playGame(1, 100, -20);

    std::cout << "\n[Demo] Save point 2" << std::endl;
    caretaker.saveMemento(gameCharacter.createMemento());

    gameCharacter.playGame(2, 200, -50);

    std::cout << "\n[Demo] Save point 3" << std::endl;
    caretaker.saveMemento(gameCharacter.createMemento());

    std::cout << "\n[Demo] --- Character Dies ---" << std::endl;
    gameCharacter.playGame(0, 0, -40);
    std::cout << "[Demo] Game Over! Current state: " << gameCharacter.getStateDescription() << std::endl;

    std::cout << "\n[Demo] --- Restoring from latest save ---" << std::endl;
    auto latestMemento = caretaker.getLatestMemento();
    if (latestMemento) {
        gameCharacter.restoreFromMemento(latestMemento);
    }

    std::cout << "\n[Demo] --- Restoring to save point 1 ---" << std::endl;
    auto memento1 = caretaker.getMemento(0);
    if (memento1) {
        gameCharacter.restoreFromMemento(memento1);
    }

    std::cout << "\n==========================================\n" << std::endl;
}

}
