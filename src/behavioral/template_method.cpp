#include "behavioral/template_method.h"

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

	std::cout << "==================================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
