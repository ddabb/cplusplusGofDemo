#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

namespace design_patterns::behavioral::observer {

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
    virtual std::string getName() const = 0;
};

class Subject {
public:
    virtual ~Subject() = default;

    virtual void attach(std::unique_ptr<Observer> observer) {
        observers_.push_back(std::move(observer));
        std::cout << "[Subject] Observer attached: " << observers_.back()->getName() << std::endl;
    }

    virtual void detach(const std::string& name) {
        auto it = std::remove_if(observers_.begin(), observers_.end(),
            [&name](const std::unique_ptr<Observer>& obs) {
                return obs->getName() == name;
            });
        if (it != observers_.end()) {
            std::cout << "[Subject] Observer detached: " << (*it)->getName() << std::endl;
            observers_.erase(it, observers_.end());
        }
    }

    virtual void notify(const std::string& message) const {
        std::cout << "[Subject] Notifying " << observers_.size() << " observers..." << std::endl;
        for (const auto& observer : observers_) {
            observer->update(message);
        }
    }

    size_t getObserverCount() const {
        return observers_.size();
    }

private:
    std::vector<std::unique_ptr<Observer>> observers_;
};

class NewsPublisher : public Subject {
public:
    std::string getName() const {
        return "News Publisher";
    }

    void publishNews(const std::string& news) {
        std::cout << "\n[NewsPublisher] Publishing news: " << news << std::endl;
        currentNews_ = news;
        notify(news);
    }

    std::string getCurrentNews() const {
        return currentNews_;
    }

private:
    std::string currentNews_;
};

class EmailSubscriber : public Observer {
public:
    EmailSubscriber(const std::string& name, const std::string& email)
        : name_(name), email_(email) {
        std::cout << "[EmailSubscriber] Created: " << name_ << " (" << email_ << ")" << std::endl;
    }

    void update(const std::string& message) override {
        std::cout << "[EmailSubscriber] " << name_ << " received email: " << message << std::endl;
        std::cout << "[EmailSubscriber] Sending to: " << email_ << std::endl;
    }

    std::string getName() const override {
        return name_;
    }

private:
    std::string name_;
    std::string email_;
};

class SMSSubscriber : public Observer {
public:
    SMSSubscriber(const std::string& name, const std::string& phone)
        : name_(name), phone_(phone) {
        std::cout << "[SMSSubscriber] Created: " << name_ << " (" << phone_ << ")" << std::endl;
    }

    void update(const std::string& message) override {
        std::cout << "[SMSSubscriber] " << name_ << " received SMS: " << message << std::endl;
        std::cout << "[SMSSubscriber] Sending to: " << phone_ << std::endl;
    }

    std::string getName() const override {
        return name_;
    }

private:
    std::string name_;
    std::string phone_;
};

class WebsiteSubscriber : public Observer {
public:
    WebsiteSubscriber(const std::string& name, const std::string& url)
        : name_(name), url_(url) {
        std::cout << "[WebsiteSubscriber] Created: " << name_ << " (" << url_ << ")" << std::endl;
    }

    void update(const std::string& message) override {
        std::cout << "[WebsiteSubscriber] " << name_ << " received push: " << message << std::endl;
        std::cout << "[WebsiteSubscriber] Publishing to: " << url_ << std::endl;
    }

    std::string getName() const override {
        return name_;
    }

private:
    std::string name_;
    std::string url_;
};

}

namespace design_patterns::behavioral {

void observer_demo() {
    std::cout << "\n========== Observer Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] 观察者模式核心：一对多依赖，状态改变时自动通知所有观察者\n" << std::endl;

    std::unique_ptr<observer::NewsPublisher> publisher = std::make_unique<observer::NewsPublisher>();

    std::cout << "[Demo] --- Adding Subscribers ---" << std::endl;
    publisher->attach(std::make_unique<observer::EmailSubscriber>("Alice", "alice@example.com"));
    publisher->attach(std::make_unique<observer::SMSSubscriber>("Bob", "+1234567890"));
    publisher->attach(std::make_unique<observer::WebsiteSubscriber>("NewsSite", "www.newssite.com"));

    std::cout << "\n[Demo] --- Publishing First News ---" << std::endl;
    publisher->publishNews("Breaking News: C++20 Released!");

    std::cout << "\n[Demo] --- Removing Subscriber ---" << std::endl;
    publisher->detach("Bob");

    std::cout << "\n[Demo] --- Publishing Second News ---" << std::endl;
    publisher->publishNews("New Design Patterns Book Available!");

    std::cout << "\n[Demo] --- Adding New Subscriber ---" << std::endl;
    publisher->attach(std::make_unique<observer::EmailSubscriber>("Charlie", "charlie@example.com"));

    std::cout << "\n[Demo] --- Publishing Third News ---" << std::endl;
    publisher->publishNews("Tech Conference 2026 Dates Announced!");

    std::cout << "============================================\n" << std::endl;
}

}
