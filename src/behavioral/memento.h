#pragma once
// 文件: src/behavioral/memento.h
// 说明: 备忘录模式示例，展示状态的捕获与恢复
// 建议: 演示中状态存储在内存中，生产项目可考虑持久化到文件。

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral {

/**
 * @brief 备忘录类
 *
 * 存储发起者的内部状态。
 */
class Memento {
    friend class Originator;

public:
    /**
     * @brief 获取状态描述
     * @return 状态描述
     */
    std::string getStateDescription() const {
        return "等级: " + std::to_string(level_) + ", 分数: " + std::to_string(score_) + ", 生命值: " + std::to_string(health_);
    }

private:
    Memento(int level, int score, int health)
        : level_(level), score_(score), health_(health) {
        std::cout << "[备忘录] 创建 - " << getStateDescription() << std::endl;
    }

    int level_;
    int score_;
    int health_;
};

/**
 * @brief 发起者类
 *
 * 创建和恢复备忘录。
 */
class Originator {
public:
    Originator(int level = 1, int score = 0, int health = 100)
        : level_(level), score_(score), health_(health) {
        std::cout << "[发起者] 创建 - " << getStateDescription() << std::endl;
    }

    /**
     * @brief 设置等级
     * @param level 等级
     */
    void setLevel(int level) {
        level_ = level;
        std::cout << "[发起者] 等级变为: " << level_ << std::endl;
    }

    /**
     * @brief 设置分数
     * @param score 分数
     */
    void setScore(int score) {
        score_ = score;
        std::cout << "[发起者] 分数变为: " << score_ << std::endl;
    }

    /**
     * @brief 设置生命值
     * @param health 生命值
     */
    void setHealth(int health) {
        health_ = health;
        std::cout << "[发起者] 生命值变为: " << health_ << std::endl;
    }

    /**
     * @brief 获取状态描述
     * @return 状态描述
     */
    std::string getStateDescription() const {
        return "等级: " + std::to_string(level_) + ", 分数: " + std::to_string(score_) + ", 生命值: " + std::to_string(health_);
    }

    /**
     * @brief 创建备忘录
     * @return 备忘录对象
     */
    std::unique_ptr<Memento> createMemento() {
        std::cout << "[发起者] 创建备忘录..." << std::endl;
        return std::unique_ptr<Memento>(new Memento(level_, score_, health_));
    }

    /**
     * @brief 从备忘录恢复状态
     * @param memento 备忘录对象
     */
    void restoreFromMemento(const std::unique_ptr<Memento>& memento) {
        level_ = memento->level_;
        score_ = memento->score_;
        health_ = memento->health_;
        std::cout << "[发起者] 从备忘录恢复 - " << getStateDescription() << std::endl;
    }

    /**
     * @brief 进行游戏
     * @param levelDelta 等级变化
     * @param scoreDelta 分数变化
     * @param healthDelta 生命值变化
     */
    void playGame(int levelDelta, int scoreDelta, int healthDelta) {
        level_ += levelDelta;
        score_ += scoreDelta;
        health_ += healthDelta;
        if (health_ < 0) health_ = 0;
        std::cout << "[发起者] 游戏后 - " << getStateDescription() << std::endl;
    }

private:
    int level_;
    int score_;
    int health_;
};

/**
 * @brief 管理者类
 *
 * 保存和管理备忘录。
 */
class Caretaker {
public:
    Caretaker() {
        std::cout << "[管理者] 创建" << std::endl;
    }

    /**
     * @brief 保存备忘录
     * @param memento 备忘录对象
     */
    void saveMemento(std::unique_ptr<Memento> memento) {
        mementos_.push_back(std::move(memento));
        std::cout << "[管理者] 备忘录已保存，总数: " << mementos_.size() << std::endl;
    }

    /**
     * @brief 获取指定索引的备忘录
     * @param index 索引
     * @return 备忘录对象
     */
    std::unique_ptr<Memento> getMemento(size_t index) {
        if (index < mementos_.size()) {
            std::cout << "[管理者] 获取索引 " << index << " 的备忘录" << std::endl;
            auto memento = std::move(mementos_[index]);
            mementos_.erase(mementos_.begin() + index);
            return memento;
        }
        std::cout << "[管理者] 索引 " << index << " 的备忘录不存在" << std::endl;
        return nullptr;
    }

    /**
     * @brief 获取最新的备忘录
     * @return 最新的备忘录对象
     */
    std::unique_ptr<Memento> getLatestMemento() {
        if (!mementos_.empty()) {
            auto memento = std::move(mementos_.back());
            mementos_.pop_back();
            std::cout << "[管理者] 获取最新备忘录" << std::endl;
            return memento;
        }
        std::cout << "[管理者] 没有可用的备忘录" << std::endl;
        return nullptr;
    }

    /**
     * @brief 获取备忘录数量
     * @return 备忘录数量
     */
    size_t getMementoCount() const {
        return mementos_.size();
    }

private:
    std::vector<std::unique_ptr<Memento>> mementos_;
};

void memento_demo();

}