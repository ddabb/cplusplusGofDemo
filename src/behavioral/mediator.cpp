#include "behavioral/mediator.h"
#include <iostream>

namespace design_patterns::behavioral::mediator {

Colleague::Colleague(Mediator* mediator, const std::string& name)
    : mediator_(mediator), name_(name) {
    std::cout << "[同事] 创建: " << name_ << std::endl;
}

void Colleague::send(const std::string& to, const std::string& message) {
    std::cout << "[同事] " << name_ << " 发送给 " << to << ": " << message << std::endl;
    mediator_->sendMessage(name_, to, message);
}

void Colleague::receive(const std::string& from, const std::string& message) {
    std::cout << "[同事] " << name_ << " 收到来自 " << from << ": " << message << std::endl;
}

std::string Colleague::getName() const {
    return name_;
}

ConcreteColleague::ConcreteColleague(Mediator* mediator, const std::string& name)
    : Colleague(mediator, name) {}

void ConcreteColleague::send(const std::string& to, const std::string& message) {
    std::cout << "[具体同事] " << name_ << " 发送给 " << to << ": " << message << std::endl;
    mediator_->sendMessage(name_, to, message);
}

void ConcreteColleague::receive(const std::string& from, const std::string& message) {
    std::cout << "[具体同事] " << name_ << " 收到来自 " << from << ": " << message << std::endl;
}

ConcreteMediator::ConcreteMediator(const std::string& name) : name_(name) {
    std::cout << "[具体中介者] 创建: " << name_ << std::endl;
}

void ConcreteMediator::registerColleague(const std::string& name, Colleague* colleague) {
    colleagues_[name] = colleague;
    std::cout << "[具体中介者] 注册同事: " << name << std::endl;
}

void ConcreteMediator::sendMessage(const std::string& from, const std::string& to, const std::string& message) {
    std::cout << "[具体中介者] 转发消息从 " << from << " 到 " << to << std::endl;
    auto it = colleagues_.find(to);
    if (it != colleagues_.end()) {
        it->second->receive(from, message);
    } else {
        std::cout << "[具体中介者] 同事 " << to << " 未找到" << std::endl;
    }
}

void ConcreteMediator::broadcastMessage(const std::string& from, const std::string& message) {
    std::cout << "[具体中介者] 广播消息从 " << from << std::endl;
    for (const auto& pair : colleagues_) {
        if (pair.first != from) {
            pair.second->receive(from, message);
        }
    }
}

std::string ConcreteMediator::getName() const {
    return name_;
}

size_t ConcreteMediator::getColleagueCount() const {
    return colleagues_.size();
}

}

namespace design_patterns::behavioral {

/**
 * @brief 中介者模式演示函数
 *
 * 演示中介者模式的核心特性：封装对象之间的通信。
 */
void mediator_demo() {
	std::cout << "\n========== 中介者模式演示 ==========" << std::endl;
	std::cout << "[演示] 中介者模式核心：封装对象之间的通信\n" << std::endl;

	std::unique_ptr<mediator::ConcreteMediator> chatRoom = std::make_unique<mediator::ConcreteMediator>("聊天室");

	std::cout << "[演示] --- 创建同事 ---" << std::endl;
	mediator::ConcreteColleague alice(chatRoom.get(), "Alice");
	mediator::ConcreteColleague bob(chatRoom.get(), "Bob");
	mediator::ConcreteColleague charlie(chatRoom.get(), "Charlie");

	std::cout << "\n[演示] --- 注册同事 ---" << std::endl;
	chatRoom->registerColleague("Alice", &alice);
	chatRoom->registerColleague("Bob", &bob);
	chatRoom->registerColleague("Charlie", &charlie);

	std::cout << "\n[演示] --- Alice 发送私信给 Bob ---" << std::endl;
	alice.send("Bob", "嘿 Bob, 你好吗？");

	std::cout << "\n[演示] --- Bob 发送私信给 Alice ---" << std::endl;
	bob.send("Alice", "嗨 Alice, 我很好！");

	std::cout << "\n[演示] --- Charlie 广播消息 ---" << std::endl;
	chatRoom->broadcastMessage("Charlie", "大家好！");

	std::cout << "\n[演示] --- Alice 发送给不存在的同事 ---" << std::endl;
	alice.send("Dave", "你好 Dave！");

	std::cout << "\n==========================================\n" << std::endl;
}

}
