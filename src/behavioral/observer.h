#pragma once
// 文件: src/behavioral/observer.h
// 说明: 观察者模式示例，展示主题与观察者之间的一对多依赖关系
// 建议: 演示中使用 unique_ptr 管理观察者生命周期，适合教学用途。

#include <memory>
#include <string>
#include <vector>

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
    virtual void attach(std::unique_ptr<Observer> observer);

    /**
     * @brief 移除观察者
     * @param name 观察者名称
     */
    virtual void detach(const std::string& name);

    /**
     * @brief 通知所有观察者
     * @param message 通知消息
     */
    virtual void notify(const std::string& message) const;

    /**
     * @brief 获取观察者数量
     * @return 观察者数量
     */
    size_t getObserverCount() const;

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
    std::string getName() const;

    /**
     * @brief 发布新闻
     * @param news 新闻内容
     */
    void publishNews(const std::string& news);

    /**
     * @brief 获取当前新闻
     * @return 当前新闻内容
     */
    std::string getCurrentNews() const;

private:
    std::string currentNews_;
};

/**
 * @brief 邮件订阅者
 */
class EmailSubscriber : public Observer {
public:
    EmailSubscriber(const std::string& name, const std::string& email);

    void update(const std::string& message) override;
    std::string getName() const override;

private:
    std::string name_;
    std::string email_;
};

/**
 * @brief 短信订阅者
 */
class SMSSubscriber : public Observer {
public:
    SMSSubscriber(const std::string& name, const std::string& phone);

    void update(const std::string& message) override;
    std::string getName() const override;

private:
    std::string name_;
    std::string phone_;
};

/**
 * @brief 网站订阅者
 */
class WebsiteSubscriber : public Observer {
public:
    WebsiteSubscriber(const std::string& name, const std::string& url);

    void update(const std::string& message) override;
    std::string getName() const override;

private:
    std::string name_;
    std::string url_;
};

}

namespace design_patterns::behavioral {
void observer_demo();

}
