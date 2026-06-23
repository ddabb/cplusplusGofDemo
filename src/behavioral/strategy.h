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
void strategy_demo();

}
