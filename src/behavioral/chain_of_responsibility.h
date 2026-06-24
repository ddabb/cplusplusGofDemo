#pragma once
// 文件: src/behavioral/chain_of_responsibility.h
// 说明: 责任链模式示例，展示请求沿链传递直到被处理
// 建议: 演示中金额阈值为示例，实际项目可通过配置动态调整。

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::behavioral::chain_of_responsibility {

/**
 * @brief 请求类
 *
 * 封装请求的类型、金额和描述信息。
 */
class Request {
public:
    /**
     * @brief 请求类型枚举
     */
    enum class Type {
        LEAVE,
        PURCHASE,
        REFUND
    };

    Request(Type type, double amount, const std::string& description)
        : type_(type), amount_(amount), description_(description) {}

    Type getType() const {
        return type_;
    }

    double getAmount() const {
        return amount_;
    }

    std::string getDescription() const {
        return description_;
    }

    /**
     * @brief 获取请求类型名称
     * @return 请求类型名称
     */
    std::string getTypeName() const {
        switch (type_) {
            case Type::LEAVE: return "请假";
            case Type::PURCHASE: return "采购";
            case Type::REFUND: return "退款";
            default: return "未知";
        }
    }

private:
    Type type_;
    double amount_;
    std::string description_;
};

/**
 * @brief 审批者抽象类
 *
 * 定义审批者的通用接口，维护后继者链。
 */
class Approver {
public:
    virtual ~Approver() = default;

    /**
     * @brief 设置后继审批者
     * @param successor 后继审批者
     */
    void setSuccessor(std::unique_ptr<Approver> successor) {
        successor_ = std::move(successor);
        std::cout << "[审批者] " << getName() << " 设置后继为 " << successor_->getName() << std::endl;
    }

    /**
     * @brief 处理请求
     * @param request 请求对象
     */
    virtual void processRequest(const Request& request) const {
        if (successor_) {
            std::cout << "[审批者] " << getName() << " 无法处理，传递给 " << successor_->getName() << std::endl;
            successor_->processRequest(request);
        } else {
            std::cout << "[审批者] 请求无人能处理！" << std::endl;
        }
    }

    /**
     * @brief 获取名称
     * @return 审批者名称
     */
    virtual std::string getName() const = 0;
    /**
     * @brief 获取审批限额
     * @return 审批限额
     */
    virtual double getApprovalLimit() const = 0;

protected:
    std::unique_ptr<Approver> successor_;
};

/**
 * @brief 主管
 */
class Supervisor : public Approver {
public:
    explicit Supervisor(const std::string& name) : name_(name) {
        std::cout << "[主管] 创建: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[主管] " << name_ << " 处理请求..." << std::endl;
        std::cout << "[主管] 请求: " << request.getTypeName() 
                  << ", 金额: ¥" << request.getAmount() << std::endl;

        if (request.getAmount() < 1000) {
            std::cout << "[主管] " << name_ << " 批准了请求！" << std::endl;
        } else {
            Approver::processRequest(request);
        }
    }

    std::string getName() const override {
        return "主管 " + name_;
    }

    double getApprovalLimit() const override {
        return 1000;
    }

private:
    std::string name_;
};

/**
 * @brief 经理
 */
class Manager : public Approver {
public:
    explicit Manager(const std::string& name) : name_(name) {
        std::cout << "[经理] 创建: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[经理] " << name_ << " 处理请求..." << std::endl;
        std::cout << "[经理] 请求: " << request.getTypeName() 
                  << ", 金额: ¥" << request.getAmount() << std::endl;

        if (request.getAmount() < 5000) {
            std::cout << "[经理] " << name_ << " 批准了请求！" << std::endl;
        } else {
            Approver::processRequest(request);
        }
    }

    std::string getName() const override {
        return "经理 " + name_;
    }

    double getApprovalLimit() const override {
        return 5000;
    }

private:
    std::string name_;
};

/**
 * @brief 总监
 */
class Director : public Approver {
public:
    explicit Director(const std::string& name) : name_(name) {
        std::cout << "[总监] 创建: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[总监] " << name_ << " 处理请求..." << std::endl;
        std::cout << "[总监] 请求: " << request.getTypeName() 
                  << ", 金额: ¥" << request.getAmount() << std::endl;

        if (request.getAmount() < 10000) {
            std::cout << "[总监] " << name_ << " 批准了请求！" << std::endl;
        } else {
            Approver::processRequest(request);
        }
    }

    std::string getName() const override {
        return "总监 " + name_;
    }

    double getApprovalLimit() const override {
        return 10000;
    }

private:
    std::string name_;
};

/**
 * @brief 首席执行官
 */
class CEO : public Approver {
public:
    explicit CEO(const std::string& name) : name_(name) {
        std::cout << "[CEO] 创建: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[CEO] " << name_ << " 处理请求..." << std::endl;
        std::cout << "[CEO] 请求: " << request.getTypeName() 
                  << ", 金额: ¥" << request.getAmount() << std::endl;

        std::cout << "[CEO] " << name_ << " 批准了请求！" << std::endl;
    }

    std::string getName() const override {
        return "CEO " + name_;
    }

    double getApprovalLimit() const override {
        return 1000000;
    }

private:
    std::string name_;
};

}

namespace design_patterns::behavioral {
void chain_of_responsibility_demo();

}
