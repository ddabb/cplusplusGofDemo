#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::behavioral::state {

class Context;

class State {
public:
    virtual ~State() = default;
    virtual void handle(Context& context) const = 0;
    virtual std::string getName() const = 0;
};

class Context {
public:
    explicit Context(std::unique_ptr<State> state)
        : state_(std::move(state)) {
        std::cout << "[Context] Created with state: " << state_->getName() << std::endl;
    }

    void setState(std::unique_ptr<State> state) {
        std::cout << "[Context] Changing state from " << state_->getName() 
                  << " to " << state->getName() << std::endl;
        state_ = std::move(state);
    }

    void request() {
        state_->handle(*this);
    }

    std::string getCurrentStateName() const {
        return state_->getName();
    }

private:
    std::unique_ptr<State> state_;
};

class PendingPaymentState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "PendingPayment";
    }
};

class PaidState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "Paid";
    }
};

class ShippedState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "Shipped";
    }
};

class CompletedState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "Completed";
    }
};

void PendingPaymentState::handle(Context& context) const {
    std::cout << "[PendingPaymentState] Order is pending payment" << std::endl;
    std::cout << "[PendingPaymentState] Processing payment..." << std::endl;
    std::cout << "[PendingPaymentState] Payment successful!" << std::endl;
    context.setState(std::make_unique<PaidState>());
}

void PaidState::handle(Context& context) const {
    std::cout << "[PaidState] Order has been paid" << std::endl;
    std::cout << "[PaidState] Preparing shipment..." << std::endl;
    std::cout << "[PaidState] Shipment prepared!" << std::endl;
    context.setState(std::make_unique<ShippedState>());
}

void ShippedState::handle(Context& context) const {
    std::cout << "[ShippedState] Order has been shipped" << std::endl;
    std::cout << "[ShippedState] Delivering to customer..." << std::endl;
    std::cout << "[ShippedState] Order delivered!" << std::endl;
    context.setState(std::make_unique<CompletedState>());
}

void CompletedState::handle(Context& context) const {
    std::cout << "[CompletedState] Order has been completed" << std::endl;
    std::cout << "[CompletedState] Thank you for your purchase!" << std::endl;
}

}

namespace design_patterns::behavioral {

void state_demo() {
    std::cout << "\n========== State Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] State Pattern: behavior changes when internal state changes\n" << std::endl;

    std::unique_ptr<state::Context> order = std::make_unique<state::Context>(std::make_unique<state::PendingPaymentState>());

    std::cout << "\n[Demo] --- Processing Order ---" << std::endl;
    
    std::cout << "\nStep 1: Current state - " << order->getCurrentStateName() << std::endl;
    order->request();

    std::cout << "\nStep 2: Current state - " << order->getCurrentStateName() << std::endl;
    order->request();

    std::cout << "\nStep 3: Current state - " << order->getCurrentStateName() << std::endl;
    order->request();

    std::cout << "\nStep 4: Current state - " << order->getCurrentStateName() << std::endl;
    order->request();

    std::cout << "\n[Demo] --- Trying to process completed order ---" << std::endl;
    order->request();

    std::cout << "\n========================================\n" << std::endl;
}

}