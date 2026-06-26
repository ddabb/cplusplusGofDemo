#include "behavioral/strategy.h"
#include <iostream>

namespace design_patterns::behavioral::strategy {

CreditCardPayment::CreditCardPayment(const std::string& cardNumber, const std::string& expiryDate, const std::string& cvv)
    : cardNumber_(cardNumber), expiryDate_(expiryDate), cvv_(cvv) {}

void CreditCardPayment::pay(double amount) const {
    std::cout << "[信用卡支付] 支付 " << amount << " 元" << std::endl;
    std::cout << "[信用卡支付] 卡号: " << cardNumber_.substr(0, 4) << "****" << cardNumber_.substr(12) << std::endl;
    std::cout << "[信用卡支付] 有效期: " << expiryDate_ << std::endl;
    std::cout << "[信用卡支付] 支付成功！" << std::endl;
}

std::string CreditCardPayment::getName() const {
    return "信用卡支付";
}

PayPalPayment::PayPalPayment(const std::string& email, const std::string& password)
    : email_(email), password_(password) {}

void PayPalPayment::pay(double amount) const {
    std::cout << "[PayPal支付] 支付 " << amount << " 元" << std::endl;
    std::cout << "[PayPal支付] 邮箱: " << email_ << std::endl;
    std::cout << "[PayPal支付] 支付成功！" << std::endl;
}

std::string PayPalPayment::getName() const {
    return "PayPal支付";
}

AlipayPayment::AlipayPayment(const std::string& account) : account_(account) {}

void AlipayPayment::pay(double amount) const {
    std::cout << "[支付宝支付] 支付 " << amount << " 元" << std::endl;
    std::cout << "[支付宝支付] 账号: " << account_ << std::endl;
    std::cout << "[支付宝支付] 支付成功！" << std::endl;
}

std::string AlipayPayment::getName() const {
    return "支付宝支付";
}

ShoppingCart::ShoppingCart() : totalAmount_(0.0) {}

void ShoppingCart::addItem(const std::string& name, double price) {
    items_.emplace_back(name, price);
    totalAmount_ += price;
    std::cout << "[购物车] 添加商品: " << name << "，价格: " << price << " 元" << std::endl;
}

void ShoppingCart::setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
    paymentStrategy_ = std::move(strategy);
}

void ShoppingCart::checkout() const {
    std::cout << "[购物车] 结算金额: " << totalAmount_ << " 元" << std::endl;
    if (paymentStrategy_) {
        paymentStrategy_->pay(totalAmount_);
    } else {
        std::cout << "[购物车] 请先设置支付策略！" << std::endl;
    }
}

double ShoppingCart::getTotalAmount() const {
    return totalAmount_;
}

}

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

	std::cout << "\n==========================================\n" << std::endl;
}

}
