#pragma once
// 文件: src/behavioral/memento.h
// 说明: 备忘录模式示例，展示状态的捕获与恢复
// 建议: 演示中状态存储在内存中，生产项目可考虑持久化到文件。

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
    std::string getStateDescription() const;

private:
    Memento(int level, int score, int health);

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
    Originator(int level = 1, int score = 0, int health = 100);

    /**
     * @brief 设置等级
     * @param level 等级
     */
    void setLevel(int level);

    /**
     * @brief 设置分数
     * @param score 分数
     */
    void setScore(int score);

    /**
     * @brief 设置生命值
     * @param health 生命值
     */
    void setHealth(int health);

    /**
     * @brief 获取状态描述
     * @return 状态描述
     */
    std::string getStateDescription() const;

    /**
     * @brief 创建备忘录
     * @return 备忘录对象
     */
    std::unique_ptr<Memento> createMemento();

    /**
     * @brief 从备忘录恢复状态
     * @param memento 备忘录对象
     */
    void restoreFromMemento(const std::unique_ptr<Memento>& memento);

    /**
     * @brief 进行游戏
     * @param levelDelta 等级变化
     * @param scoreDelta 分数变化
     * @param healthDelta 生命值变化
     */
    void playGame(int levelDelta, int scoreDelta, int healthDelta);

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
    Caretaker();

    /**
     * @brief 保存备忘录
     * @param memento 备忘录对象
     */
    void saveMemento(std::unique_ptr<Memento> memento);

    /**
     * @brief 获取指定索引的备忘录
     * @param index 索引
     * @return 备忘录对象
     */
    std::unique_ptr<Memento> getMemento(size_t index);

    /**
     * @brief 获取最新的备忘录
     * @return 最新的备忘录对象
     */
    std::unique_ptr<Memento> getLatestMemento();

    /**
     * @brief 获取备忘录数量
     * @return 备忘录数量
     */
    size_t getMementoCount() const;

private:
    std::vector<std::unique_ptr<Memento>> mementos_;
};

void memento_demo();

}