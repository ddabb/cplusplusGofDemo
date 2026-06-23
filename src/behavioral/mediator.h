#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace design_patterns::behavioral::mediator {

class Colleague;

class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void registerColleague(const std::string& name, Colleague* colleague) = 0;
    virtual void sendMessage(const std::string& from, const std::string& to, const std::string& message) = 0;
    virtual void broadcastMessage(const std::string& from, const std::string& message) = 0;
    virtual std::string getName() const = 0;
};

class Colleague {
public:
    Colleague(Mediator* mediator, const std::string& name)
        : mediator_(mediator), name_(name) {
        std::cout << "[Colleague] Created: " << name_ << std::endl;
    }

    virtual ~Colleague() = default;

    virtual void send(const std::string& to, const std::string& message) {
        std::cout << "[Colleague] " << name_ << " sending to " << to << ": " << message << std::endl;
        mediator_->sendMessage(name_, to, message);
    }

    virtual void receive(const std::string& from, const std::string& message) {
        std::cout << "[Colleague] " << name_ << " received from " << from << ": " << message << std::endl;
    }

    virtual std::string getName() const {
        return name_;
    }

protected:
    Mediator* mediator_;
    std::string name_;
};

class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* mediator, const std::string& name)
        : Colleague(mediator, name) {}

    void send(const std::string& to, const std::string& message) override {
        std::cout << "[ConcreteColleague] " << name_ << " sending to " << to << ": " << message << std::endl;
        mediator_->sendMessage(name_, to, message);
    }

    void receive(const std::string& from, const std::string& message) override {
        std::cout << "[ConcreteColleague] " << name_ << " received from " << from << ": " << message << std::endl;
    }
};

class ConcreteMediator : public Mediator {
public:
    ConcreteMediator(const std::string& name) : name_(name) {
        std::cout << "[ConcreteMediator] Created: " << name_ << std::endl;
    }

    void registerColleague(const std::string& name, Colleague* colleague) override {
        colleagues_[name] = colleague;
        std::cout << "[ConcreteMediator] Registered colleague: " << name << std::endl;
    }

    void sendMessage(const std::string& from, const std::string& to, const std::string& message) override {
        std::cout << "[ConcreteMediator] Forwarding message from " << from << " to " << to << std::endl;
        auto it = colleagues_.find(to);
        if (it != colleagues_.end()) {
            it->second->receive(from, message);
        } else {
            std::cout << "[ConcreteMediator] Colleague " << to << " not found" << std::endl;
        }
    }

    void broadcastMessage(const std::string& from, const std::string& message) override {
        std::cout << "[ConcreteMediator] Broadcasting message from " << from << std::endl;
        for (const auto& pair : colleagues_) {
            if (pair.first != from) {
                pair.second->receive(from, message);
            }
        }
    }

    std::string getName() const override {
        return name_;
    }

    size_t getColleagueCount() const {
        return colleagues_.size();
    }

private:
    std::unordered_map<std::string, Colleague*> colleagues_;
    std::string name_;
};

}

namespace design_patterns::behavioral {

void mediator_demo() {
    std::cout << "\n========== Mediator Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] Mediator Pattern: encapsulate communication between objects\n" << std::endl;

    std::unique_ptr<mediator::ConcreteMediator> chatRoom = std::make_unique<mediator::ConcreteMediator>("ChatRoom");

    std::cout << "[Demo] --- Creating Colleagues ---" << std::endl;
    mediator::ConcreteColleague alice(chatRoom.get(), "Alice");
    mediator::ConcreteColleague bob(chatRoom.get(), "Bob");
    mediator::ConcreteColleague charlie(chatRoom.get(), "Charlie");

    std::cout << "\n[Demo] --- Registering Colleagues ---" << std::endl;
    chatRoom->registerColleague("Alice", &alice);
    chatRoom->registerColleague("Bob", &bob);
    chatRoom->registerColleague("Charlie", &charlie);

    std::cout << "\n[Demo] --- Alice sends private message to Bob ---" << std::endl;
    alice.send("Bob", "Hey Bob, how are you?");

    std::cout << "\n[Demo] --- Bob sends private message to Alice ---" << std::endl;
    bob.send("Alice", "Hi Alice, I'm doing great!");

    std::cout << "\n[Demo] --- Charlie broadcasts a message ---" << std::endl;
    chatRoom->broadcastMessage("Charlie", "Hello everyone!");

    std::cout << "\n[Demo] --- Alice sends to non-existent colleague ---" << std::endl;
    alice.send("Dave", "Hello Dave!");

    std::cout << "\n============================================\n" << std::endl;
}

}