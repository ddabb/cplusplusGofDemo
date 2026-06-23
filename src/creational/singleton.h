#pragma once
// 文件: src/creational/singleton.h
// 说明: 单例模式示例，实现线程安全的局部静态实例（C++11 及以上安全）
// 建议: 仅用于演示，生产环境应谨慎使用单例以避免全局状态副作用。

#include <iostream>
#include <string>
#include <mutex>

namespace design_patterns::creational {

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    void setMessage(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        message_ = message;
    }

    std::string getMessage() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return message_;
    }

    void display() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "[Singleton] Message: " << message_ << std::endl;
        std::cout << "[Singleton] Instance address: " << this << std::endl;
    }

private:
    Singleton() : message_("Hello, Singleton!") {
        std::cout << "[Singleton] Constructor called" << std::endl;
    }

    ~Singleton() {
        std::cout << "[Singleton] Destructor called" << std::endl;
    }

    mutable std::mutex mutex_;
    std::string message_;
};

// Demo function declaration
void singleton_demo();

}
