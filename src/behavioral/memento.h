#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral {

class Memento {
    friend class Originator;

public:
    std::string getStateDescription() const {
        return "Level: " + std::to_string(level_) + ", Score: " + std::to_string(score_) + ", Health: " + std::to_string(health_);
    }

private:
    Memento(int level, int score, int health)
        : level_(level), score_(score), health_(health) {
        std::cout << "[Memento] Created - " << getStateDescription() << std::endl;
    }

    int level_;
    int score_;
    int health_;
};

class Originator {
public:
    Originator(int level = 1, int score = 0, int health = 100)
        : level_(level), score_(score), health_(health) {
        std::cout << "[Originator] Created - " << getStateDescription() << std::endl;
    }

    void setLevel(int level) {
        level_ = level;
        std::cout << "[Originator] Level changed to: " << level_ << std::endl;
    }

    void setScore(int score) {
        score_ = score;
        std::cout << "[Originator] Score changed to: " << score_ << std::endl;
    }

    void setHealth(int health) {
        health_ = health;
        std::cout << "[Originator] Health changed to: " << health_ << std::endl;
    }

    std::string getStateDescription() const {
        return "Level: " + std::to_string(level_) + ", Score: " + std::to_string(score_) + ", Health: " + std::to_string(health_);
    }

    std::unique_ptr<Memento> createMemento() {
        std::cout << "[Originator] Creating memento..." << std::endl;
        return std::unique_ptr<Memento>(new Memento(level_, score_, health_));
    }

    void restoreFromMemento(const std::unique_ptr<Memento>& memento) {
        level_ = memento->level_;
        score_ = memento->score_;
        health_ = memento->health_;
        std::cout << "[Originator] Restored from memento - " << getStateDescription() << std::endl;
    }

    void playGame(int levelDelta, int scoreDelta, int healthDelta) {
        level_ += levelDelta;
        score_ += scoreDelta;
        health_ += healthDelta;
        if (health_ < 0) health_ = 0;
        std::cout << "[Originator] After playing - " << getStateDescription() << std::endl;
    }

private:
    int level_;
    int score_;
    int health_;
};

class Caretaker {
public:
    Caretaker() {
        std::cout << "[Caretaker] Created" << std::endl;
    }

    void saveMemento(std::unique_ptr<Memento> memento) {
        mementos_.push_back(std::move(memento));
        std::cout << "[Caretaker] Memento saved, total: " << mementos_.size() << std::endl;
    }

    std::unique_ptr<Memento> getMemento(size_t index) {
        if (index < mementos_.size()) {
            std::cout << "[Caretaker] Retrieving memento at index: " << index << std::endl;
            auto memento = std::move(mementos_[index]);
            mementos_.erase(mementos_.begin() + index);
            return memento;
        }
        std::cout << "[Caretaker] Memento not found at index: " << index << std::endl;
        return nullptr;
    }

    std::unique_ptr<Memento> getLatestMemento() {
        if (!mementos_.empty()) {
            auto memento = std::move(mementos_.back());
            mementos_.pop_back();
            std::cout << "[Caretaker] Retrieving latest memento" << std::endl;
            return memento;
        }
        std::cout << "[Caretaker] No mementos available" << std::endl;
        return nullptr;
    }

    size_t getMementoCount() const {
        return mementos_.size();
    }

private:
    std::vector<std::unique_ptr<Memento>> mementos_;
};

// Demo function declaration
void memento_demo();

}