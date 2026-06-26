#pragma once
// 文件: src/behavioral/chain_of_responsibility.h
// 说明: 责任链模式示例，展示请求沿链传递直到被处理
// 建议: 演示中金额阈值为示例，实际项目可通过配置动态调整。

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

    Request(Type type, double amount, const std::string& description);

    Type getType() const;
    double getAmount() const;
    std::string getDescription() const;

    /**
     * @brief 获取请求类型名称
     * @return 请求类型名称
     */
    std::string getTypeName() const;

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
    void setSuccessor(std::unique_ptr<Approver> successor);

    /**
     * @brief 处理请求
     * @param request 请求对象
     */
    virtual void processRequest(const Request& request) const;

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
    explicit Supervisor(const std::string& name);

    void processRequest(const Request& request) const override;
    std::string getName() const override;
    double getApprovalLimit() const override;

private:
    std::string name_;
};

/**
 * @brief 经理
 */
class Manager : public Approver {
public:
    explicit Manager(const std::string& name);

    void processRequest(const Request& request) const override;
    std::string getName() const override;
    double getApprovalLimit() const override;

private:
    std::string name_;
};

/**
 * @brief 总监
 */
class Director : public Approver {
public:
    explicit Director(const std::string& name);

    void processRequest(const Request& request) const override;
    std::string getName() const override;
    double getApprovalLimit() const override;

private:
    std::string name_;
};

/**
 * @brief 首席执行官
 */
class CEO : public Approver {
public:
    explicit CEO(const std::string& name);

    void processRequest(const Request& request) const override;
    std::string getName() const override;
    double getApprovalLimit() const override;

private:
    std::string name_;
};

}

namespace design_patterns::behavioral {
void chain_of_responsibility_demo();

}
