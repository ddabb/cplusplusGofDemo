#pragma once
// 文件: src/behavioral/mediator.h
// 说明: 中介者模式示例，展示对象间通信的集中协调
// 建议: 演示中使用指针管理同事对象，生产环境需注意生命周期管理。

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace design_patterns::behavioral::mediator {

class Colleague;

/**
 * @brief 中介者接口
 *
 * 定义中介者的通用接口：注册同事、发送消息、广播消息。
 */
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void registerColleague(const std::string& name, Colleague* colleague) = 0;
    virtual void sendMessage(const std::string& from, const std::string& to, const std::string& message) = 0;
    virtual void broadcastMessage(const std::string& from, const std::string& message) = 0;
    virtual std::string getName() const = 0;
};

/**
 * @brief 同事类
 *
 * 通过中介者与其他同事通信。
 */
class Colleague {
public:
    Colleague(Mediator* mediator, const std::string& name);
    virtual ~Colleague() = default;

    virtual void send(const std::string& to, const std::string& message);
    virtual void receive(const std::string& from, const std::string& message);
    virtual std::string getName() const;

protected:
    Mediator* mediator_;
    std::string name_;
};

/**
 * @brief 具体同事类
 */
class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* mediator, const std::string& name);

    void send(const std::string& to, const std::string& message) override;
    void receive(const std::string& from, const std::string& message) override;
};

/**
 * @brief 具体中介者类
 *
 * 协调所有同事之间的通信。
 */
class ConcreteMediator : public Mediator {
public:
    explicit ConcreteMediator(const std::string& name);

    void registerColleague(const std::string& name, Colleague* colleague) override;
    void sendMessage(const std::string& from, const std::string& to, const std::string& message) override;
    void broadcastMessage(const std::string& from, const std::string& message) override;
    std::string getName() const override;

    /**
     * @brief 获取同事数量
     * @return 同事数量
     */
    size_t getColleagueCount() const;

private:
    std::unordered_map<std::string, Colleague*> colleagues_;
    std::string name_;
};

}

namespace design_patterns::behavioral {
void mediator_demo();

}
