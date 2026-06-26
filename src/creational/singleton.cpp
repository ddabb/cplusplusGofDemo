#include "creational/singleton.h"
#include <iostream>
#include <mutex>

namespace design_patterns::creational {

/**
 * @brief 私有构造函数
 */
Singleton::Singleton() : message_("你好, 单例模式!") {
    std::cout << "[单例模式] 构造函数被调用" << std::endl;
}

/**
 * @brief 私有析构函数
 */
Singleton::~Singleton() {
    std::cout << "[单例模式] 析构函数被调用" << std::endl;
}

/**
 * @brief 设置消息内容
 * @param message 消息字符串
 */
void Singleton::setMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    message_ = message;
}

/**
 * @brief 获取消息内容
 * @return 消息字符串
 */
std::string Singleton::getMessage() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return message_;
}

/**
 * @brief 显示单例信息
 */
void Singleton::display() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[单例模式] 消息内容: " << message_ << std::endl;
    std::cout << "[单例模式] 实例地址: " << this << std::endl;
}

/**
 * @brief 单例模式演示函数
 *
 * 演示单例模式的核心特性：确保一个类只有一个实例，并提供全局访问点。
 */
void singleton_demo() {
    std::cout << "\n========== 单例模式演示 ==========" << std::endl;

    // 获取单例实例
    Singleton& instance1 = Singleton::getInstance();
    instance1.display();

    // 获取同一个单例实例
    Singleton& instance2 = Singleton::getInstance();
    instance2.display();

    // 验证两个引用指向同一个对象
    std::cout << "\n[单例模式] 两个实例是否指向同一个地址: " 
              << (&instance1 == &instance2 ? "是" : "否") << std::endl;

    // 修改单例的消息内容
    instance1.setMessage("从 instance1 修改的消息");
    instance2.display();

    std::cout << "=============================================\n" << std::endl;
}

}

