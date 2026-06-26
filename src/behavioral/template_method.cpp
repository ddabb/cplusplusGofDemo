#include "behavioral/template_method.h"
#include <iostream>

namespace design_patterns::behavioral::template_method {

void Game::play() const {
    std::cout << "[游戏] 开始 " << getName() << "..." << std::endl;
    
    if (wantToPlay()) {
        initialize();
        startPlay();
        playGame();
        endPlay();
    } else {
        std::cout << "[游戏] 玩家不想玩 " << getName() << std::endl;
    }
}

bool Game::wantToPlay() const {
    return true;
}

void FootballGame::initialize() const {
    std::cout << "[足球] 初始化：设置球场..." << std::endl;
    std::cout << "[足球] 初始化：双方队员入场..." << std::endl;
}

void FootballGame::startPlay() const {
    std::cout << "[足球] 开始比赛：裁判鸣哨..." << std::endl;
}

void FootballGame::playGame() const {
    std::cout << "[足球] 比赛进行中：传球..." << std::endl;
    std::cout << "[足球] 比赛进行中：射门..." << std::endl;
    std::cout << "[足球] 比赛进行中：进球！" << std::endl;
}

void FootballGame::endPlay() const {
    std::cout << "[足球] 比赛结束：双方队员握手..." << std::endl;
}

std::string FootballGame::getName() const {
    return "足球";
}

void ChessGame::initialize() const {
    std::cout << "[象棋] 初始化：摆放棋子..." << std::endl;
    std::cout << "[象棋] 初始化：红方先行..." << std::endl;
}

void ChessGame::startPlay() const {
    std::cout << "[象棋] 开始对弈..." << std::endl;
}

void ChessGame::playGame() const {
    std::cout << "[象棋] 对弈中：红方走棋..." << std::endl;
    std::cout << "[象棋] 对弈中：黑方走棋..." << std::endl;
    std::cout << "[象棋] 对弈中：将军！" << std::endl;
}

void ChessGame::endPlay() const {
    std::cout << "[象棋] 对弈结束：一方认输..." << std::endl;
}

std::string ChessGame::getName() const {
    return "象棋";
}

void GameWithHook::initialize() const {
    std::cout << "[带钩子游戏] 初始化..." << std::endl;
}

void GameWithHook::startPlay() const {
    std::cout << "[带钩子游戏] 开始..." << std::endl;
}

void GameWithHook::playGame() const {
    std::cout << "[带钩子游戏] 进行中..." << std::endl;
}

void GameWithHook::endPlay() const {
    std::cout << "[带钩子游戏] 结束..." << std::endl;
}

bool GameWithHook::wantToPlay() const {
    std::cout << "[带钩子游戏] 钩子方法：玩家不想玩" << std::endl;
    return false;
}

std::string GameWithHook::getName() const {
    return "带钩子游戏";
}

}

namespace design_patterns::behavioral {

/**
 * @brief 模板方法模式演示函数
 *
 * 演示模板方法模式的核心特性：定义算法骨架，延迟步骤到子类实现。
 */
void template_method_demo() {
	std::cout << "\n========== 模板方法模式演示 ==========" << std::endl;
	std::cout << "[演示] 模板方法模式核心：定义算法骨架，延迟步骤到子类实现\n" << std::endl;

	std::cout << "[演示] --- 踢足球 ---" << std::endl;
	std::unique_ptr<template_method::Game> football = std::make_unique<template_method::FootballGame>();
	football->play();

	std::cout << std::endl;

	std::cout << "[演示] --- 下象棋 ---" << std::endl;
	std::unique_ptr<template_method::Game> chess = std::make_unique<template_method::ChessGame>();
	chess->play();

	std::cout << std::endl;

	std::cout << "[演示] --- 带钩子的游戏 ---" << std::endl;
	std::unique_ptr<template_method::Game> gameWithHook = std::make_unique<template_method::GameWithHook>();
	gameWithHook->play();

	std::cout << "\n==================================================\n" << std::endl;
}

}
