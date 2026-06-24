#pragma once
// 文件: src/behavioral/observer.h
// 说明: 观察者模式示例，展示主题与观察者之间的一对多依赖关系
// 建议: 演示中使用 unique_ptr 管理观察者生命周期，适合教学用途。

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

namespace design_patterns::behavioral::observer {

/**
 * @brief 观察者接口
 *
 * 定义观察者需要实现的更新方法。
 */
class Observer {
public:
    virtual ~Observer() = default;
    /**
     * @brief 更新方法
     * @param message 收到的消息
     */
    virtual void update(const std::string& message) = 0;
    /**
     * @brief 获取名称
     * @return 观察者名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 主题接口
 *
 * 定义主题的基本操作：添加/移除观察者、通知观察者。
 */
class Subject {
public:
    virtual ~Subject() = default;

    /**
     * @brief 添加观察者
     * @param observer 观察者对象
     */
    virtual void attach(std::unique_ptr<Observer> observer) {
        observers_.push_back(std::move(observer));
        std::cout << "[主题] 添加观察者: " << observers_.back()->getName() << std::endl;
    }

    /**
     * @brief 移除观察者
     * @param name 观察者名称
     */
    virtual void detach(const std::string& name) {
        auto it = std::find_if(observers_.begin(), observers_.end(),
            [&name](const std::unique_ptr<Observer>& obs) {
                return obs->getName() == name;
            });
        if (it != observers_.end()) {
            std::cout << "[主题] 移除观察者: " << (*it)->getName() << std::endl;
            observers_.erase(it);
        }
    }

    /**
     * @brief 通知所有观察者
     * @param message 通知消息
     */
    virtual void notify(const std::string& message) const {
        std::cout << "[主题] 正在通知 " << observers_.size() << " 个观察者..." << std::endl;
        for (const auto& observer : observers_) {
            observer->update(message);
        }
    }

    /**
     * @brief 获取观察者数量
     * @return 观察者数量
     */
    size_t getObserverCount() const {
        return observers_.size();
    }

private:
    std::vector<std::unique_ptr<Observer>> observers_;
};

/**
 * @brief 新闻发布者
 *
 * 具体的主题实现，发布新闻并通知订阅者。
 */
class NewsPublisher : public Subject {
public:
    std::string getName() const {
        return "新闻发布者";
    }

    /**
     * @brief 发布新闻
     * @param news 新闻内容
     */
    void publishNews(const std::string& news) {
        std::cout << "\n[新闻发布者] 发布新闻: " << news << std::endl;
        currentNews_ = news;
        notify(news);
    }

    /**
     * @brief 获取当前新闻
     * @return 当前新闻内容
     */
    std::string getCurrentNews() const {
        return currentNews_;
    }

private:
    std::string currentNews_;
};

/**
 * @brief 邮件订阅者
 */
class EmailSubscriber : public Observer {
public:
    EmailSubscriber(const std::string& name, const std::string& email)
        : name_(name), email_(email) {
        std::cout << "[邮件订阅者] 创建: " << name_ << " (" << email_ << ")" << std::endl;
    }

    void update(const std::string& message) override {
        std::cout << "[邮件订阅者] " << name_ << " 收到邮件: " << message << std::endl;
        std::cout << "[邮件订阅者] 发送至: " << email_ << std::endl;
    }

    std::string getName() const override {
        return name_;
    }

private:
    std::string name_;
    std::string email_;
};

/**
 * @brief 短信订阅者
 */
class SMSSubscriber : public Observer {
public:
    SMSSubscriber(const std::string& name, const std::string& phone)
        : name_(name), phone_(phone) {
        std::cout << "[短信订阅者] 创建: " << name_ << " (" << phone_ << ")" << std::endl;
    }

    void update(const std::string& message) override {
        std::cout << "[短信订阅者] " << name_ << " 收到短信: " << message << std::endl;
        std::cout << "[短信订阅者] 发送至: " << phone_ << std::endl;
    }

    std::string getName() const override {
        return name_;
    }

private:
    std::string name_;
    std::string phone_;
};

/**
 * @brief 网站订阅者
 */
class WebsiteSubscriber : public Observer {
public:
    WebsiteSubscriber(const std::string& name, const std::string& url)
        : name_(name), url_(url) {
        std::cout << "[网站订阅者] 创建: " << name_ << " (" << url_ << ")" << std::endl;
    }

    void update(const std::string& message) override {
        std::cout << "[网站订阅者] " << name_ << " 收到推送: " << message << std::endl;
        std::cout << "[网站订阅者] 发布至: " << url_ << std::endl;
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
void observer_demo();

}
