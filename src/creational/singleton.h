#pragma once
// 文件: src/creational/singleton.h
// 说明: 单例模式示例，实现线程安全的局部静态实例（C++11 及以上安全）
// 建议: 仅用于演示，生产环境应谨慎使用单例以避免全局状态副作用。

#include <iostream>
#include <string>
#include <mutex>

namespace design_patterns::creational {

/**
 * @brief 单例模式类
 *
 * 使用 C++11 局部静态变量实现线程安全的单例。
 * 局部静态变量的初始化是线程安全的，无需额外的互斥锁保护。
 */
class Singleton {
public:
    /**
     * @brief 获取单例实例
     * @return 单例对象的引用
     */
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    // 禁用拷贝构造和赋值操作
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    /**
     * @brief 设置消息内容
     * @param message 消息字符串
     */
    void setMessage(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        message_ = message;
    }

    /**
     * @brief 获取消息内容
     * @return 消息字符串
     */
    std::string getMessage() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return message_;
    }

    /**
     * @brief 显示单例信息
     */
    void display() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "[单例模式] 消息内容: " << message_ << std::endl;
        std::cout << "[单例模式] 实例地址: " << this << std::endl;
    }

private:
    /**
     * @brief 私有构造函数
     */
    Singleton() : message_("你好, 单例模式!") {
        std::cout << "[单例模式] 构造函数被调用" << std::endl;
    }

    /**
     * @brief 私有析构函数
     */
    ~Singleton() {
        std::cout << "[单例模式] 析构函数被调用" << std::endl;
    }

    mutable std::mutex mutex_;  // 互斥锁，保护共享资源
    std::string message_;       // 消息内容
};

// Demo 函数声明
void singleton_demo();

}
