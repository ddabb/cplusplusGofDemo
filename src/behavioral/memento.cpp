#include "behavioral/memento.h"
#include <iostream>

namespace design_patterns::behavioral {

Memento::Memento(int level, int score, int health)
    : level_(level), score_(score), health_(health) {}

std::string Memento::getStateDescription() const {
    return "等级: " + std::to_string(level_) + ", 分数: " + std::to_string(score_) + ", 生命值: " + std::to_string(health_);
}

Originator::Originator(int level, int score, int health)
    : level_(level), score_(score), health_(health) {
    std::cout << "[发起者] 创建，状态: " << getStateDescription() << std::endl;
}

void Originator::setLevel(int level) {
    level_ = level;
}

void Originator::setScore(int score) {
    score_ = score;
}

void Originator::setHealth(int health) {
    health_ = health;
}

std::string Originator::getStateDescription() const {
    return "等级: " + std::to_string(level_) + ", 分数: " + std::to_string(score_) + ", 生命值: " + std::to_string(health_);
}

std::unique_ptr<Memento> Originator::createMemento() {
    std::cout << "[发起者] 创建备忘录，状态: " << getStateDescription() << std::endl;
    return std::unique_ptr<Memento>(new Memento(level_, score_, health_));
}

void Originator::restoreFromMemento(const std::unique_ptr<Memento>& memento) {
    level_ = memento->level_;
    score_ = memento->score_;
    health_ = memento->health_;
    std::cout << "[发起者] 从备忘录恢复，状态: " << getStateDescription() << std::endl;
}

void Originator::playGame(int levelDelta, int scoreDelta, int healthDelta) {
    level_ += levelDelta;
    score_ += scoreDelta;
    health_ += healthDelta;
    std::cout << "[发起者] 游戏进行中，等级变化: " << levelDelta 
              << ", 分数变化: " << scoreDelta 
              << ", 生命值变化: " << healthDelta 
              << ", 当前状态: " << getStateDescription() << std::endl;
}

Caretaker::Caretaker() {}

void Caretaker::saveMemento(std::unique_ptr<Memento> memento) {
    mementos_.push_back(std::move(memento));
    std::cout << "[管理者] 保存备忘录，当前存档数量: " << mementos_.size() << std::endl;
}

std::unique_ptr<Memento> Caretaker::getMemento(size_t index) {
    if (index < mementos_.size()) {
        return std::move(mementos_[index]);
    }
    return nullptr;
}

std::unique_ptr<Memento> Caretaker::getLatestMemento() {
    if (!mementos_.empty()) {
        return std::move(mementos_.back());
    }
    return nullptr;
}

size_t Caretaker::getMementoCount() const {
    return mementos_.size();
}

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
