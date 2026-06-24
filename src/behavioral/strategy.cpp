#include "behavioral/strategy.h"

namespace design_patterns::behavioral {

/**
 * @brief 策略模式演示函数
 *
 * 演示策略模式的核心特性：定义一系列算法，封装并使它们相互替换。
 */
void strategy_demo() {
	std::cout << "\n========== 策略模式演示 ==========" << std::endl;
	std::cout << "[演示] 策略模式核心：定义一系列算法，封装并使它们相互替换\n" << std::endl;

	std::unique_ptr<strategy::ShoppingCart> cart = std::make_unique<strategy::ShoppingCart>();

	std::cout << "[演示] --- 添加商品到购物车 ---" << std::endl;
	cart->addItem("笔记本电脑", 9999.99);
	cart->addItem("鼠标", 299.99);
	cart->addItem("键盘", 499.99);

	std::cout << "\n[演示] --- 使用信用卡支付 ---" << std::endl;
	cart->setPaymentStrategy(std::make_unique<strategy::CreditCardPayment>("1234-5678-9012-3456", "12/26", "123"));
	cart->checkout();

	std::cout << "\n[演示] --- 创建新车并使用 PayPal 支付 ---" << std::endl;
	std::unique_ptr<strategy::ShoppingCart> cart2 = std::make_unique<strategy::ShoppingCart>();
	cart2->addItem("手机", 6999.99);
	cart2->addItem("手机壳", 199.99);
	cart2->setPaymentStrategy(std::make_unique<strategy::PayPalPayment>("user@example.com", "password"));
	cart2->checkout();

	std::cout << "\n[演示] --- 使用支付宝支付 ---" << std::endl;
	cart2->addItem("屏幕保护膜", 99.99);
	cart2->setPaymentStrategy(std::make_unique<strategy::AlipayPayment>("zhifubao@example.com"));
	cart2->checkout();

	std::cout << "==========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
