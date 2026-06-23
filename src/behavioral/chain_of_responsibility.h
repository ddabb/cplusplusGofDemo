#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::behavioral::chain_of_responsibility {

class Request {
public:
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

    std::string getTypeName() const {
        switch (type_) {
            case Type::LEAVE: return "Leave";
            case Type::PURCHASE: return "Purchase";
            case Type::REFUND: return "Refund";
            default: return "Unknown";
        }
    }

private:
    Type type_;
    double amount_;
    std::string description_;
};

class Approver {
public:
    virtual ~Approver() = default;

    void setSuccessor(std::unique_ptr<Approver> successor) {
        successor_ = std::move(successor);
        std::cout << "[Approver] " << getName() << " set successor to " << successor_->getName() << std::endl;
    }

    virtual void processRequest(const Request& request) const {
        if (successor_) {
            std::cout << "[Approver] " << getName() << " cannot handle, passing to " << successor_->getName() << std::endl;
            successor_->processRequest(request);
        } else {
            std::cout << "[Approver] Request cannot be handled by anyone!" << std::endl;
        }
    }

    virtual std::string getName() const = 0;
    virtual double getApprovalLimit() const = 0;

protected:
    std::unique_ptr<Approver> successor_;
};

class Supervisor : public Approver {
public:
    explicit Supervisor(const std::string& name) : name_(name) {
        std::cout << "[Supervisor] Created: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[Supervisor] " << name_ << " processing request..." << std::endl;
        std::cout << "[Supervisor] Request: " << request.getTypeName() 
                  << ", Amount: $" << request.getAmount() << std::endl;

        if (request.getAmount() < 1000) {
            std::cout << "[Supervisor] " << name_ << " approved the request!" << std::endl;
        } else {
            Approver::processRequest(request);
        }
    }

    std::string getName() const override {
        return "Supervisor " + name_;
    }

    double getApprovalLimit() const override {
        return 1000;
    }

private:
    std::string name_;
};

class Manager : public Approver {
public:
    explicit Manager(const std::string& name) : name_(name) {
        std::cout << "[Manager] Created: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[Manager] " << name_ << " processing request..." << std::endl;
        std::cout << "[Manager] Request: " << request.getTypeName() 
                  << ", Amount: $" << request.getAmount() << std::endl;

        if (request.getAmount() < 5000) {
            std::cout << "[Manager] " << name_ << " approved the request!" << std::endl;
        } else {
            Approver::processRequest(request);
        }
    }

    std::string getName() const override {
        return "Manager " + name_;
    }

    double getApprovalLimit() const override {
        return 5000;
    }

private:
    std::string name_;
};

class Director : public Approver {
public:
    explicit Director(const std::string& name) : name_(name) {
        std::cout << "[Director] Created: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[Director] " << name_ << " processing request..." << std::endl;
        std::cout << "[Director] Request: " << request.getTypeName() 
                  << ", Amount: $" << request.getAmount() << std::endl;

        if (request.getAmount() < 10000) {
            std::cout << "[Director] " << name_ << " approved the request!" << std::endl;
        } else {
            Approver::processRequest(request);
        }
    }

    std::string getName() const override {
        return "Director " + name_;
    }

    double getApprovalLimit() const override {
        return 10000;
    }

private:
    std::string name_;
};

class CEO : public Approver {
public:
    explicit CEO(const std::string& name) : name_(name) {
        std::cout << "[CEO] Created: " << name_ << std::endl;
    }

    void processRequest(const Request& request) const override {
        std::cout << "\n[CEO] " << name_ << " processing request..." << std::endl;
        std::cout << "[CEO] Request: " << request.getTypeName() 
                  << ", Amount: $" << request.getAmount() << std::endl;

        std::cout << "[CEO] " << name_ << " approved the request!" << std::endl;
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
