#pragma once
// 文件: src/behavioral/template_method.h
// 说明: 模板方法模式示例，展示算法骨架与具体步骤分离
// 建议: 钩子方法可用于扩展，实际项目可增加更多钩子点。

#include <memory>
#include <string>

namespace design_patterns::behavioral::template_method {

/**
 * @brief 游戏抽象类
 *
 * 定义游戏的模板方法（算法骨架），具体步骤由子类实现。
 */
class Game {
public:
    virtual ~Game() = default;

    /**
     * @brief 游戏模板方法（算法骨架）
     */
    void play() const;

protected:
    /**
     * @brief 初始化游戏
     */
    virtual void initialize() const = 0;
    /**
     * @brief 开始游戏
     */
    virtual void startPlay() const = 0;
    /**
     * @brief 进行游戏
     */
    virtual void playGame() const = 0;
    /**
     * @brief 结束游戏
     */
    virtual void endPlay() const = 0;

    /**
     * @brief 钩子方法：玩家是否想玩
     * @return 是否想玩
     */
    virtual bool wantToPlay() const;

    /**
     * @brief 获取游戏名称
     * @return 游戏名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 足球游戏
 */
class FootballGame : public Game {
protected:
    void initialize() const override;
    void startPlay() const override;
    void playGame() const override;
    void endPlay() const override;
    std::string getName() const override;
};

/**
 * @brief 象棋游戏
 */
class ChessGame : public Game {
protected:
    void initialize() const override;
    void startPlay() const override;
    void playGame() const override;
    void endPlay() const override;
    std::string getName() const override;
};

/**
 * @brief 带钩子的游戏
 *
 * 演示钩子方法的使用，玩家可以选择不玩。
 */
class GameWithHook : public Game {
protected:
    void initialize() const override;
    void startPlay() const override;
    void playGame() const override;
    void endPlay() const override;
    bool wantToPlay() const override;
    std::string getName() const override;
};

}

namespace design_patterns::behavioral {
void template_method_demo();

}
