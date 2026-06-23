#include "behavioral/observer.h"

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

} // namespace design_patterns::behavioral
