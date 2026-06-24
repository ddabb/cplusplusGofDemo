#include "behavioral/observer.h"

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
