#include "behavioral/state.h"
#include <iostream>

namespace design_patterns::behavioral::state {

void PendingPaymentState::handle(Context& context) const {
    std::cout << "[待支付状态] 订单待支付" << std::endl;
    std::cout << "[待支付状态] 处理支付..." << std::endl;
    std::cout << "[待支付状态] 支付成功！" << std::endl;
    context.setState(std::make_unique<PaidState>());
}

void PaidState::handle(Context& context) const {
    std::cout << "[已支付状态] 订单已支付" << std::endl;
    std::cout << "[已支付状态] 准备发货..." << std::endl;
    std::cout << "[已支付状态] 发货准备完成！" << std::endl;
    context.setState(std::make_unique<ShippedState>());
}

void ShippedState::handle(Context& context) const {
    std::cout << "[已发货状态] 订单已发货" << std::endl;
    std::cout << "[已发货状态] 配送中..." << std::endl;
    std::cout << "[已发货状态] 订单已送达！" << std::endl;
    context.setState(std::make_unique<CompletedState>());
}

void CompletedState::handle(Context& context) const {
    std::cout << "[已完成状态] 订单已完成" << std::endl;
    std::cout << "[已完成状态] 感谢您的购买！" << std::endl;
}

/**
 * @brief 状态模式演示函数
 *
 * 演示状态模式的核心特性：对象行为随状态变化而改变。
 */
void state_demo() {
    std::cout << "\n========== 状态模式演示 ==========" << std::endl;
    std::cout << "[演示] 状态模式核心：对象行为随状态变化而改变\n" << std::endl;

    std::cout << "[演示] --- 创建待支付状态的订单 ---" << std::endl;
    Context order(std::make_unique<PendingPaymentState>());

    std::cout << "\n[演示] --- 处理订单 ---" << std::endl;
    order.request();
    order.request();
    order.request();
    order.request();

    std::cout << "\n=========================================\n" << std::endl;
}

}
