#include "interpreter.h"

namespace design_patterns::behavioral {

void interpreter_demo() {
	std::cout << "\n========== Interpreter Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 解释器模式核心：定义文法表示，解释语言句子\n" << std::endl;

	// 创建上下文
	std::cout << "[Demo] --- Creating Context ---" << std::endl;
	Context context;
	context.setVariable("x", 10);
	context.setVariable("y", 5);

	// 构建表达式: x + y * 2
	std::cout << "\n[Demo] --- Building Expression: x + y * 2 ---" << std::endl;
	auto expression = std::make_unique<AddExpression>(
		std::make_unique<VariableExpression>("x"),
		std::make_unique<MultiplyExpression>(
			std::make_unique<VariableExpression>("y"),
			std::make_unique<ConstantExpression>(2)
		)
	);

	// 解释表达式
	std::cout << "\n[Demo] --- Interpreting Expression ---" << std::endl;
	int result = expression->interpret(context);
	std::cout << "[Demo] Final result: " << expression->getDescription() << " = " << result << std::endl;

	// 构建另一个表达式: (x - y) * (x + y)
	std::cout << "\n[Demo] --- Building Expression: (x - y) * (x + y) ---" << std::endl;
	auto expression2 = std::make_unique<MultiplyExpression>(
		std::make_unique<SubtractExpression>(
			std::make_unique<VariableExpression>("x"),
			std::make_unique<VariableExpression>("y")
		),
		std::make_unique<AddExpression>(
			std::make_unique<VariableExpression>("x"),
			std::make_unique<VariableExpression>("y")
		)
	);

	// 解释表达式
	std::cout << "\n[Demo] --- Interpreting Expression ---" << std::endl;
	int result2 = expression2->interpret(context);
	std::cout << "[Demo] Final result: " << expression2->getDescription() << " = " << result2 << std::endl;

	// 修改变量值后重新解释
	std::cout << "\n[Demo] --- Changing Variables ---" << std::endl;
	context.setVariable("x", 20);
	context.setVariable("y", 10);

	std::cout << "\n[Demo] --- Re-interpreting First Expression ---" << std::endl;
	int result3 = expression->interpret(context);
	std::cout << "[Demo] Final result: " << expression->getDescription() << " = " << result3 << std::endl;

	std::cout << "\n==============================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
