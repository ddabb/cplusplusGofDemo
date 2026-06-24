#pragma once
// 文件: src/behavioral/strategy.h
// 说明: 策略模式示例，展示支付策略的可替换性
// 建议: 演示中密码存储为示例，生产环境请使用安全存储与加密。

#include <iostream>
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
    CreditCardPayment(const std::string& cardNumber, const std::string& expiryDate, const std::string& cvv)
        : cardNumber_(cardNumber), expiryDate_(expiryDate), cvv_(cvv) {
        std::cout << "[信用卡支付] 创建，卡号: ****" << cardNumber.substr(cardNumber.size() - 4) << std::endl;
    }

    void pay(double amount) const override {
        std::cout << "[信用卡支付] 使用信用卡支付 ¥" << amount << std::endl;
        std::cout << "[信用卡支付] 卡号: ****" << cardNumber_.substr(cardNumber_.size() - 4) << std::endl;
        std::cout << "[信用卡支付] 有效期: " << expiryDate_ << std::endl;
        std::cout << "[信用卡支付] 支付成功！" << std::endl;
    }

    std::string getName() const override {
        return "信用卡";
    }

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
    PayPalPayment(const std::string& email, const std::string& password)
        : email_(email), password_(password) {
        std::cout << "[PayPal支付] 创建，邮箱: " << email_ << std::endl;
    }

    void pay(double amount) const override {
        std::cout << "[PayPal支付] 使用 PayPal 支付 ¥" << amount << std::endl;
        std::cout << "[PayPal支付] 邮箱: " << email_ << std::endl;
        std::cout << "[PayPal支付] 密码: ********" << std::endl;
        std::cout << "[PayPal支付] 支付成功！" << std::endl;
    }

    std::string getName() const override {
        return "PayPal";
    }

private:
    std::string email_;
    std::string password_;
};

/**
 * @brief 支付宝支付策略
 */
class AlipayPayment : public PaymentStrategy {
public:
    explicit AlipayPayment(const std::string& account)
        : account_(account) {
        std::cout << "[支付宝支付] 创建，账户: " << account_ << std::endl;
    }

    void pay(double amount) const override {
        std::cout << "[支付宝支付] 使用支付宝支付 ¥" << amount << std::endl;
        std::cout << "[支付宝支付] 账户: " << account_ << std::endl;
        std::cout << "[支付宝支付] 扫描二维码..." << std::endl;
        std::cout << "[支付宝支付] 支付成功！" << std::endl;
    }

    std::string getName() const override {
        return "支付宝";
    }

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
    ShoppingCart() : totalAmount_(0.0) {
        std::cout << "[购物车] 创建" << std::endl;
    }

    /**
     * @brief 添加商品
     * @param name 商品名称
     * @param price 商品价格
     */
    void addItem(const std::string& name, double price) {
        items_.push_back({name, price});
        totalAmount_ += price;
        std::cout << "[购物车] 添加: " << name << " (¥" << price << ")" << std::endl;
    }

    /**
     * @brief 设置支付策略
     * @param strategy 支付策略
     */
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy_ = std::move(strategy);
        std::cout << "[购物车] 支付策略设置为: " << paymentStrategy_->getName() << std::endl;
    }

    /**
     * @brief 结算
     */
    void checkout() const {
        std::cout << "\n[购物车] 结算:" << std::endl;
        std::cout << "[购物车] 购物车中的商品:" << std::endl;
        for (const auto& item : items_) {
            std::cout << "  - " << item.first << ": ¥" << item.second << std::endl;
        }
        std::cout << "[购物车] 总金额: ¥" << totalAmount_ << std::endl;
        
        if (paymentStrategy_) {
            paymentStrategy_->pay(totalAmount_);
        } else {
            std::cout << "[购物车] 错误：未设置支付策略！" << std::endl;
        }
    }

    /**
     * @brief 获取总金额
     * @return 总金额
     */
    double getTotalAmount() const {
        return totalAmount_;
    }

private:
    std::vector<std::pair<std::string, double>> items_;
    double totalAmount_;
    std::unique_ptr<PaymentStrategy> paymentStrategy_;
};

}

namespace design_patterns::behavioral {
void strategy_demo();

}
