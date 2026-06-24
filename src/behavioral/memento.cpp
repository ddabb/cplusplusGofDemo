#include "behavioral/memento.h"
#include <iostream>

namespace design_patterns::behavioral {

/**
 * @brief 备忘录模式演示函数
 *
 * 演示备忘录模式的核心特性：捕获和恢复对象状态。
 */
void memento_demo() {
    std::cout << "\n========== 备忘录模式演示 ==========" << std::endl;
    std::cout << "[演示] 备忘录模式核心：捕获和恢复对象状态\n" << std::endl;

    std::cout << "[演示] --- 创建游戏角色 ---" << std::endl;
    Originator gameCharacter(1, 0, 100);

    Caretaker caretaker;

    std::cout << "\n[演示] --- 进行游戏 ---" << std::endl;
    
    std::cout << "\n[演示] 存档点 1" << std::endl;
    caretaker.saveMemento(gameCharacter.createMemento());

    gameCharacter.playGame(1, 100, -20);

    std::cout << "\n[演示] 存档点 2" << std::endl;
    caretaker.saveMemento(gameCharacter.createMemento());

    gameCharacter.playGame(2, 200, -50);

    std::cout << "\n[演示] 存档点 3" << std::endl;
    caretaker.saveMemento(gameCharacter.createMemento());

    std::cout << "\n[演示] --- 角色死亡 ---" << std::endl;
    gameCharacter.playGame(0, 0, -40);
    std::cout << "[演示] 游戏结束！当前状态: " << gameCharacter.getStateDescription() << std::endl;

    std::cout << "\n[演示] --- 从最新存档恢复 ---" << std::endl;
    auto latestMemento = caretaker.getLatestMemento();
    if (latestMemento) {
        gameCharacter.restoreFromMemento(latestMemento);
    }

    std::cout << "\n[演示] --- 恢复到存档点 1 ---" << std::endl;
    auto memento1 = caretaker.getMemento(0);
    if (memento1) {
        gameCharacter.restoreFromMemento(memento1);
    }

    std::cout << "\n==========================================\n" << std::endl;
}

}
