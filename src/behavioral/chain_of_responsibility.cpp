#include "behavioral/chain_of_responsibility.h"
#include <iostream>

namespace design_patterns::behavioral::chain_of_responsibility {

Request::Request(Type type, double amount, const std::string& description)
    : type_(type), amount_(amount), description_(description) {}

Request::Type Request::getType() const {
    return type_;
}

double Request::getAmount() const {
    return amount_;
}

std::string Request::getDescription() const {
    return description_;
}

std::string Request::getTypeName() const {
    switch (type_) {
        case Type::LEAVE: return "请假";
        case Type::PURCHASE: return "采购";
        case Type::REFUND: return "退款";
        default: return "未知";
    }
}

void Approver::setSuccessor(std::unique_ptr<Approver> successor) {
    successor_ = std::move(successor);
}

void Approver::processRequest(const Request& request) const {
    if (successor_) {
        successor_->processRequest(request);
    } else {
        std::cout << "[审批者] 请求无法处理: " << request.getTypeName() 
                  << "，金额: " << request.getAmount() << "，描述: " << request.getDescription() << std::endl;
    }
}

Supervisor::Supervisor(const std::string& name) : name_(name) {}

void Supervisor::processRequest(const Request& request) const {
    if (request.getAmount() <= 1000) {
        std::cout << "[主管] " << name_ << " 审批通过: " << request.getTypeName() 
                  << "，金额: " << request.getAmount() << "，描述: " << request.getDescription() << std::endl;
    } else {
        std::cout << "[主管] " << name_ << " 无法审批，转发给上级..." << std::endl;
        Approver::processRequest(request);
    }
}

std::string Supervisor::getName() const {
    return name_;
}

double Supervisor::getApprovalLimit() const {
    return 1000.0;
}

Manager::Manager(const std::string& name) : name_(name) {}

void Manager::processRequest(const Request& request) const {
    if (request.getAmount() <= 5000) {
        std::cout << "[经理] " << name_ << " 审批通过: " << request.getTypeName() 
                  << "，金额: " << request.getAmount() << "，描述: " << request.getDescription() << std::endl;
    } else {
        std::cout << "[经理] " << name_ << " 无法审批，转发给上级..." << std::endl;
        Approver::processRequest(request);
    }
}

std::string Manager::getName() const {
    return name_;
}

double Manager::getApprovalLimit() const {
    return 5000.0;
}

Director::Director(const std::string& name) : name_(name) {}

void Director::processRequest(const Request& request) const {
    if (request.getAmount() <= 20000) {
        std::cout << "[总监] " << name_ << " 审批通过: " << request.getTypeName() 
                  << "，金额: " << request.getAmount() << "，描述: " << request.getDescription() << std::endl;
    } else {
        std::cout << "[总监] " << name_ << " 无法审批，转发给上级..." << std::endl;
        Approver::processRequest(request);
    }
}

std::string Director::getName() const {
    return name_;
}

double Director::getApprovalLimit() const {
    return 20000.0;
}

CEO::CEO(const std::string& name) : name_(name) {}

void CEO::processRequest(const Request& request) const {
    std::cout << "[CEO] " << name_ << " 审批通过: " << request.getTypeName() 
              << "，金额: " << request.getAmount() << "，描述: " << request.getDescription() << std::endl;
}

std::string CEO::getName() const {
    return name_;
}

double CEO::getApprovalLimit() const {
    return 1000000.0;
}

}

namespace design_patterns::behavioral {

/**
 * @brief 责任链模式演示函数
 *
 * 演示责任链模式的核心特性：多个对象处理请求，沿链传递直到被处理。
 */
void chain_of_responsibility_demo() {
	std::cout << "\n========== 责任链模式演示 ==========" << std::endl;
	std::cout << "[演示] 责任链模式核心：多个对象处理请求，沿链传递直到被处理\n" << std::endl;

	std::cout << "[演示] --- 创建审批者 ---" << std::endl;

	auto fullChain = std::make_unique<chain_of_responsibility::Supervisor>("Alice");
	auto m = std::make_unique<chain_of_responsibility::Manager>("Bob");
	auto d = std::make_unique<chain_of_responsibility::Director>("Charlie");
	auto c = std::make_unique<chain_of_responsibility::CEO>("David");
	d->setSuccessor(std::move(c));
	m->setSuccessor(std::move(d));
	fullChain->setSuccessor(std::move(m));

	std::cout << "\n[演示] --- 处理请求 ---" << std::endl;

	chain_of_responsibility::Request smallRequest(chain_of_responsibility::Request::Type::PURCHASE, 500, "办公用品");
	fullChain->processRequest(smallRequest);

	chain_of_responsibility::Request mediumRequest(chain_of_responsibility::Request::Type::REFUND, 3000, "客户退款");
	fullChain->processRequest(mediumRequest);

	chain_of_responsibility::Request largeRequest(chain_of_responsibility::Request::Type::PURCHASE, 8000, "新设备");
	fullChain->processRequest(largeRequest);

	chain_of_responsibility::Request hugeRequest(chain_of_responsibility::Request::Type::PURCHASE, 50000, "公司用车");
	fullChain->processRequest(hugeRequest);

	std::cout << "\n==========================================================\n" << std::endl;
}

}
