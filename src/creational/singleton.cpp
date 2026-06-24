#include "creational/singleton.h"
#include <iostream>

namespace design_patterns::creational {

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

