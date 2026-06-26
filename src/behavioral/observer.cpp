#include "behavioral/observer.h"
#include <iostream>
#include <algorithm>

namespace design_patterns::behavioral::observer {

void Subject::attach(std::unique_ptr<Observer> observer) {
    observers_.push_back(std::move(observer));
    std::cout << "[主题] 添加观察者: " << observers_.back()->getName() << std::endl;
}

void Subject::detach(const std::string& name) {
    auto it = std::find_if(observers_.begin(), observers_.end(),
        [&name](const std::unique_ptr<Observer>& obs) {
            return obs->getName() == name;
        });
    if (it != observers_.end()) {
        std::cout << "[主题] 移除观察者: " << (*it)->getName() << std::endl;
        observers_.erase(it);
    }
}

void Subject::notify(const std::string& message) const {
    std::cout << "[主题] 通知所有观察者..." << std::endl;
    for (const auto& observer : observers_) {
        observer->update(message);
    }
}

size_t Subject::getObserverCount() const {
    return observers_.size();
}

std::string NewsPublisher::getName() const {
    return "新闻发布者";
}

void NewsPublisher::publishNews(const std::string& news) {
    currentNews_ = news;
    std::cout << "[新闻发布者] 发布新闻: " << news << std::endl;
    notify(news);
}

std::string NewsPublisher::getCurrentNews() const {
    return currentNews_;
}

EmailSubscriber::EmailSubscriber(const std::string& name, const std::string& email)
    : name_(name), email_(email) {
    std::cout << "[邮件订阅者] 创建: " << name_ << " (" << email_ << ")" << std::endl;
}

void EmailSubscriber::update(const std::string& message) {
    std::cout << "[邮件订阅者] " << name_ << " 收到邮件: " << message << std::endl;
}

std::string EmailSubscriber::getName() const {
    return name_;
}

SMSSubscriber::SMSSubscriber(const std::string& name, const std::string& phone)
    : name_(name), phone_(phone) {
    std::cout << "[短信订阅者] 创建: " << name_ << " (" << phone_ << ")" << std::endl;
}

void SMSSubscriber::update(const std::string& message) {
    std::cout << "[短信订阅者] " << name_ << " 收到短信: " << message << std::endl;
}

std::string SMSSubscriber::getName() const {
    return name_;
}

WebsiteSubscriber::WebsiteSubscriber(const std::string& name, const std::string& url)
    : name_(name), url_(url) {
    std::cout << "[网站订阅者] 创建: " << name_ << " (" << url_ << ")" << std::endl;
}

void WebsiteSubscriber::update(const std::string& message) {
    std::cout << "[网站订阅者] " << name_ << " 更新内容: " << message << std::endl;
}

std::string WebsiteSubscriber::getName() const {
    return name_;
}

}

namespace design_patterns::behavioral {

/**
 * @brief 观察者模式演示函数
 *
 * 演示观察者模式的核心特性：一对多依赖，状态改变时自动通知所有观察者。
 */
void observer_demo() {
	std::cout << "\n========== 观察者模式演示 ==========" << std::endl;
	std::cout << "[演示] 观察者模式核心：一对多依赖，状态改变时自动通知所有观察者\n" << std::endl;

	std::unique_ptr<observer::NewsPublisher> publisher = std::make_unique<observer::NewsPublisher>();

	std::cout << "[演示] --- 添加订阅者 ---" << std::endl;
	publisher->attach(std::make_unique<observer::EmailSubscriber>("Alice", "alice@example.com"));
	publisher->attach(std::make_unique<observer::SMSSubscriber>("Bob", "+1234567890"));
	publisher->attach(std::make_unique<observer::WebsiteSubscriber>("NewsSite", "www.newssite.com"));

	std::cout << "\n[演示] --- 发布第一条新闻 ---" << std::endl;
	publisher->publishNews("突发新闻：C++20 发布！");

	std::cout << "\n[演示] --- 移除订阅者 ---" << std::endl;
	publisher->detach("Bob");

	std::cout << "\n[演示] --- 发布第二条新闻 ---" << std::endl;
	publisher->publishNews("新设计模式书籍上市！");

	std::cout << "\n[演示] --- 添加新订阅者 ---" << std::endl;
	publisher->attach(std::make_unique<observer::EmailSubscriber>("Charlie", "charlie@example.com"));

	std::cout << "\n[演示] --- 发布第三条新闻 ---" << std::endl;
	publisher->publishNews("2026 技术大会日期公布！");

	std::cout << "============================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
