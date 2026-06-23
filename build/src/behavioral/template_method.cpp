#include "template_method.h"

namespace design_patterns::behavioral {

void template_method_demo() {
	std::cout << "\n========== Template Method Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 模板方法模式核心：定义算法骨架，延迟步骤到子类实现\n" << std::endl;

	std::cout << "[Demo] --- Playing Football ---" << std::endl;
	std::unique_ptr<template_method::Game> football = std::make_unique<template_method::FootballGame>();
	football->play();

	std::cout << std::endl;

	std::cout << "[Demo] --- Playing Chess ---" << std::endl;
	std::unique_ptr<template_method::Game> chess = std::make_unique<template_method::ChessGame>();
	chess->play();

	std::cout << std::endl;

	std::cout << "[Demo] --- Game with Hook ---" << std::endl;
	std::unique_ptr<template_method::Game> gameWithHook = std::make_unique<template_method::GameWithHook>();
	gameWithHook->play();

	std::cout << "==================================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
