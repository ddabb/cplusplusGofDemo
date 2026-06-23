#include "strategy.h"

namespace design_patterns::behavioral {

void strategy_demo() {
	std::cout << "\n========== Strategy Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 策略模式核心：定义一系列算法，封装并使它们相互替换\n" << std::endl;

	std::unique_ptr<strategy::ShoppingCart> cart = std::make_unique<strategy::ShoppingCart>();

	std::cout << "[Demo] --- Adding Items to Cart ---" << std::endl;
	cart->addItem("Laptop", 999.99);
	cart->addItem("Mouse", 29.99);
	cart->addItem("Keyboard", 49.99);

	std::cout << "\n[Demo] --- Paying with Credit Card ---" << std::endl;
	cart->setPaymentStrategy(std::make_unique<strategy::CreditCardPayment>("1234-5678-9012-3456", "12/26", "123"));
	cart->checkout();

	std::cout << "\n[Demo] --- Creating New Cart & Paying with PayPal ---" << std::endl;
	std::unique_ptr<strategy::ShoppingCart> cart2 = std::make_unique<strategy::ShoppingCart>();
	cart2->addItem("Phone", 699.99);
	cart2->addItem("Case", 19.99);
	cart2->setPaymentStrategy(std::make_unique<strategy::PayPalPayment>("user@example.com", "password"));
	cart2->checkout();

	std::cout << "\n[Demo] --- Paying with Alipay ---" << std::endl;
	cart2->addItem("Screen Protector", 9.99);
	cart2->setPaymentStrategy(std::make_unique<strategy::AlipayPayment>("zhifubao@example.com"));
	cart2->checkout();

	std::cout << "==========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
