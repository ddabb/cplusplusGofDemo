#pragma once
// 文件: src/behavioral/state.h
// 说明: 状态模式示例，展示对象行为随状态变化而改变
// 建议: 演示中订单状态流转为示例，生产项目可增加状态校验。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::behavioral::state {

class Context;

/**
 * @brief 状态接口
 *
 * 定义状态的通用接口。
 */
class State {
public:
    virtual ~State() = default;
    /**
     * @brief 处理方法
     * @param context 上下文对象
     */
    virtual void handle(Context& context) const = 0;
    /**
     * @brief 获取状态名称
     * @return 状态名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 上下文类
 *
 * 维护当前状态，委托状态处理请求。
 */
class Context {
public:
    explicit Context(std::unique_ptr<State> state)
        : state_(std::move(state)) {
        std::cout << "[上下文] 创建，当前状态: " << state_->getName() << std::endl;
    }

    /**
     * @brief 设置状态
     * @param state 新状态
     */
    void setState(std::unique_ptr<State> state) {
        std::cout << "[上下文] 状态从 " << state_->getName() 
                  << " 变为 " << state->getName() << std::endl;
        state_ = std::move(state);
    }

    /**
     * @brief 请求处理
     */
    void request() {
        state_->handle(*this);
    }

    /**
     * @brief 获取当前状态名称
     * @return 当前状态名称
     */
    std::string getCurrentStateName() const {
        return state_->getName();
    }

private:
    std::unique_ptr<State> state_;
};

/**
 * @brief 待支付状态
 */
class PendingPaymentState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "待支付";
    }
};

/**
 * @brief 已支付状态
 */
class PaidState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "已支付";
    }
};

/**
 * @brief 已发货状态
 */
class ShippedState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "已发货";
    }
};

/**
 * @brief 已完成状态
 */
class CompletedState : public State {
public:
    void handle(Context& context) const override;
    std::string getName() const override {
        return "已完成";
    }
};

void state_demo();
}

namespace design_patterns::behavioral {
    using state::state_demo;
}