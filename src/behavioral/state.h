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

// Leave demo declaration here; implementation moved to .cpp to reduce header bloat
void state_demo();
}

// Make state_demo available under design_patterns::behavioral namespace
namespace design_patterns::behavioral {
    using state::state_demo;
}