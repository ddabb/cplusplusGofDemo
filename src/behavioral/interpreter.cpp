#include "behavioral/interpreter.h"
#include <iostream>

namespace design_patterns::behavioral {

/**
 * @brief 解释器模式演示函数
 *
 * 演示解释器模式的核心特性：定义文法表示，解释语言句子。
 */
void interpreter_demo() {
    std::cout << "\n========== 解释器模式演示 ==========" << std::endl;
    std::cout << "[演示] 解释器模式核心：定义文法表示，解释语言句子\n" << std::endl;

    std::cout << "[演示] --- 创建上下文 ---" << std::endl;
    Context context;
    context.setVariable("x", 10);
    context.setVariable("y", 5);

    std::cout << "\n[演示] --- 构建表达式: x + y * 2 ---" << std::endl;
    auto expression = std::make_unique<AddExpression>(
        std::make_unique<VariableExpression>("x"),
        std::make_unique<MultiplyExpression>(
            std::make_unique<VariableExpression>("y"),
            std::make_unique<ConstantExpression>(2)
        )
    );

    std::cout << "\n[演示] --- 解释表达式 ---" << std::endl;
    int result = expression->interpret(context);
    std::cout << "[演示] 最终结果: " << expression->getDescription() << " = " << result << std::endl;

    std::cout << "\n[演示] --- 构建表达式: (x - y) * (x + y) ---" << std::endl;
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

    std::cout << "\n[演示] --- 解释表达式 ---" << std::endl;
    int result2 = expression2->interpret(context);
    std::cout << "[演示] 最终结果: " << expression2->getDescription() << " = " << result2 << std::endl;

    std::cout << "\n[演示] --- 修改变量值 ---" << std::endl;
    context.setVariable("x", 20);
    context.setVariable("y", 10);

    std::cout << "\n[演示] --- 重新解释第一个表达式 ---" << std::endl;
    int result3 = expression->interpret(context);
    std::cout << "[演示] 最终结果: " << expression->getDescription() << " = " << result3 << std::endl;

    std::cout << "\n==============================================\n" << std::endl;
}

}
