#pragma once
// 文件: src/behavioral/template_method.h
// 说明: 模板方法模式示例，展示算法骨架与具体步骤分离
// 建议: 钩子方法可用于扩展，实际项目可增加更多钩子点。

#include <iostream>
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
    void play() const {
        std::cout << "[游戏] 开始游戏流程..." << std::endl;
        
        initialize();
        
        if (wantToPlay()) {
            startPlay();
            playGame();
            endPlay();
        } else {
            std::cout << "[游戏] 玩家不想玩" << std::endl;
        }
        
        std::cout << "[游戏] 游戏流程完成" << std::endl;
    }

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
    virtual bool wantToPlay() const {
        return true;
    }

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
    void initialize() const override {
        std::cout << "[足球] 初始化足球游戏..." << std::endl;
        std::cout << "[足球] 设置场地..." << std::endl;
        std::cout << "[足球] 球队准备就绪！" << std::endl;
    }

    void startPlay() const override {
        std::cout << "[足球] 开球！" << std::endl;
        std::cout << "[足球] 比赛开始！" << std::endl;
    }

    void playGame() const override {
        std::cout << "[足球] 进行比赛..." << std::endl;
        std::cout << "[足球] A队进球！" << std::endl;
        std::cout << "[足球] B队进球！" << std::endl;
        std::cout << "[足球] 比赛继续..." << std::endl;
    }

    void endPlay() const override {
        std::cout << "[足球] 终场哨响！" << std::endl;
        std::cout << "[足球] 比赛以 1-1 平局结束" << std::endl;
    }

    std::string getName() const override {
        return "足球";
    }
};

/**
 * @brief 象棋游戏
 */
class ChessGame : public Game {
protected:
    void initialize() const override {
        std::cout << "[象棋] 初始化象棋游戏..." << std::endl;
        std::cout << "[象棋] 设置棋盘..." << std::endl;
        std::cout << "[象棋] 棋子摆放完毕！" << std::endl;
    }

    void startPlay() const override {
        std::cout << "[象棋] 红方先走！" << std::endl;
        std::cout << "[象棋] 游戏开始！" << std::endl;
    }

    void playGame() const override {
        std::cout << "[象棋] 进行对弈..." << std::endl;
        std::cout << "[象棋] 红方走: 炮二平五" << std::endl;
        std::cout << "[象棋] 黑方走: 马8进7" << std::endl;
        std::cout << "[象棋] 游戏继续..." << std::endl;
    }

    void endPlay() const override {
        std::cout << "[象棋] 将死！" << std::endl;
        std::cout << "[象棋] 红方获胜！" << std::endl;
    }

    std::string getName() const override {
        return "象棋";
    }
};

/**
 * @brief 带钩子的游戏
 *
 * 演示钩子方法的使用，玩家可以选择不玩。
 */
class GameWithHook : public Game {
protected:
    void initialize() const override {
        std::cout << "[带钩子游戏] 初始化..." << std::endl;
    }

    void startPlay() const override {
        std::cout << "[带钩子游戏] 开始..." << std::endl;
    }

    void playGame() const override {
        std::cout << "[带钩子游戏] 进行中..." << std::endl;
    }

    void endPlay() const override {
        std::cout << "[带钩子游戏] 结束..." << std::endl;
    }

    bool wantToPlay() const override {
        std::cout << "[带钩子游戏] 钩子：玩家今天不想玩" << std::endl;
        return false;
    }

    std::string getName() const override {
        return "带钩子游戏";
    }
};

}

namespace design_patterns::behavioral {
void template_method_demo();

}
