#pragma once
// 文件: src/behavioral/strategy.h
// 说明: 策略模式示例，展示支付策略的可替换性
// 建议: 演示中密码存储为示例，生产环境请使用安全存储与加密。

#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::strategy {

/**
 * @brief 支付策略接口
 *
 * 定义支付策略的通用接口。
 */
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    /**
     * @brief 支付方法
     * @param amount 支付金额
     */
    virtual void pay(double amount) const = 0;
    /**
     * @brief 获取策略名称
     * @return 策略名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 信用卡支付策略
 */
class CreditCardPayment : public PaymentStrategy {
public:
    CreditCardPayment(const std::string& cardNumber, const std::string& expiryDate, const std::string& cvv);

    void pay(double amount) const override;
    std::string getName() const override;

private:
    std::string cardNumber_;
    std::string expiryDate_;
    std::string cvv_;
};

/**
 * @brief PayPal 支付策略
 */
class PayPalPayment : public PaymentStrategy {
public:
    PayPalPayment(const std::string& email, const std::string& password);

    void pay(double amount) const override;
    std::string getName() const override;

private:
    std::string email_;
    std::string password_;
};

/**
 * @brief 支付宝支付策略
 */
class AlipayPayment : public PaymentStrategy {
public:
    explicit AlipayPayment(const std::string& account);

    void pay(double amount) const override;
    std::string getName() const override;

private:
    std::string account_;
};

/**
 * @brief 购物车
 *
 * 使用策略模式支持多种支付方式。
 */
class ShoppingCart {
public:
    ShoppingCart();

    /**
     * @brief 添加商品
     * @param name 商品名称
     * @param price 商品价格
     */
    void addItem(const std::string& name, double price);

    /**
     * @brief 设置支付策略
     * @param strategy 支付策略
     */
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy);

    /**
     * @brief 结算
     */
    void checkout() const;

    /**
     * @brief 获取总金额
     * @return 总金额
     */
    double getTotalAmount() const;

private:
    std::vector<std::pair<std::string, double>> items_;
    double totalAmount_;
    std::unique_ptr<PaymentStrategy> paymentStrategy_;
};

}

namespace design_patterns::behavioral {
void strategy_demo();

}
