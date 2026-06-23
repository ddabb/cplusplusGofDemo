#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::strategy {

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(double amount) const = 0;
    virtual std::string getName() const = 0;
};

class CreditCardPayment : public PaymentStrategy {
public:
    CreditCardPayment(const std::string& cardNumber, const std::string& expiryDate, const std::string& cvv)
        : cardNumber_(cardNumber), expiryDate_(expiryDate), cvv_(cvv) {
        std::cout << "[CreditCardPayment] Created for card: ****" << cardNumber.substr(cardNumber.size() - 4) << std::endl;
    }

    void pay(double amount) const override {
        std::cout << "[CreditCardPayment] Paying $" << amount << " with credit card" << std::endl;
        std::cout << "[CreditCardPayment] Card: ****" << cardNumber_.substr(cardNumber_.size() - 4) << std::endl;
        std::cout << "[CreditCardPayment] Expiry: " << expiryDate_ << std::endl;
        std::cout << "[CreditCardPayment] Payment successful!" << std::endl;
    }

    std::string getName() const override {
        return "Credit Card";
    }

private:
    std::string cardNumber_;
    std::string expiryDate_;
    std::string cvv_;
};

class PayPalPayment : public PaymentStrategy {
public:
    PayPalPayment(const std::string& email, const std::string& password)
        : email_(email), password_(password) {
        std::cout << "[PayPalPayment] Created for email: " << email_ << std::endl;
    }

    void pay(double amount) const override {
        std::cout << "[PayPalPayment] Paying $" << amount << " with PayPal" << std::endl;
        std::cout << "[PayPalPayment] Email: " << email_ << std::endl;
        std::cout << "[PayPalPayment] Password: ********" << std::endl;
        std::cout << "[PayPalPayment] Payment successful!" << std::endl;
    }

    std::string getName() const override {
        return "PayPal";
    }

private:
    std::string email_;
    std::string password_;
};

class AlipayPayment : public PaymentStrategy {
public:
    explicit AlipayPayment(const std::string& account)
        : account_(account) {
        std::cout << "[AlipayPayment] Created for account: " << account_ << std::endl;
    }

    void pay(double amount) const override {
        std::cout << "[AlipayPayment] Paying $" << amount << " with Alipay" << std::endl;
        std::cout << "[AlipayPayment] Account: " << account_ << std::endl;
        std::cout << "[AlipayPayment] Scanning QR code..." << std::endl;
        std::cout << "[AlipayPayment] Payment successful!" << std::endl;
    }

    std::string getName() const override {
        return "Alipay";
    }

private:
    std::string account_;
};

class ShoppingCart {
public:
    ShoppingCart() : totalAmount_(0.0) {
        std::cout << "[ShoppingCart] Created" << std::endl;
    }

    void addItem(const std::string& name, double price) {
        items_.push_back({name, price});
        totalAmount_ += price;
        std::cout << "[ShoppingCart] Added: " << name << " ($" << price << ")" << std::endl;
    }

    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy_ = std::move(strategy);
        std::cout << "[ShoppingCart] Payment strategy set to: " << paymentStrategy_->getName() << std::endl;
    }

    void checkout() const {
        std::cout << "\n[ShoppingCart] Checkout:" << std::endl;
        std::cout << "[ShoppingCart] Items in cart:" << std::endl;
        for (const auto& item : items_) {
            std::cout << "  - " << item.first << ": $" << item.second << std::endl;
        }
        std::cout << "[ShoppingCart] Total amount: $" << totalAmount_ << std::endl;
        
        if (paymentStrategy_) {
            paymentStrategy_->pay(totalAmount_);
        } else {
            std::cout << "[ShoppingCart] Error: No payment strategy set!" << std::endl;
        }
    }

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

}
