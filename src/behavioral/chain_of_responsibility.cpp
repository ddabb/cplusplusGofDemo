#include "behavioral/chain_of_responsibility.h"

namespace design_patterns::behavioral {

/**
 * @brief 责任链模式演示函数
 *
 * 演示责任链模式的核心特性：多个对象处理请求，沿链传递直到被处理。
 */
void chain_of_responsibility_demo() {
	std::cout << "\n========== 责任链模式演示 ==========" << std::endl;
	std::cout << "[演示] 责任链模式核心：多个对象处理请求，沿链传递直到被处理\n" << std::endl;

	std::cout << "[演示] --- 创建审批者 ---" << std::endl;

	auto fullChain = std::make_unique<chain_of_responsibility::Supervisor>("Alice");
	auto m = std::make_unique<chain_of_responsibility::Manager>("Bob");
	auto d = std::make_unique<chain_of_responsibility::Director>("Charlie");
	auto c = std::make_unique<chain_of_responsibility::CEO>("David");
	d->setSuccessor(std::move(c));
	m->setSuccessor(std::move(d));
	fullChain->setSuccessor(std::move(m));

	std::cout << "\n[演示] --- 处理请求 ---" << std::endl;

	chain_of_responsibility::Request smallRequest(chain_of_responsibility::Request::Type::PURCHASE, 500, "办公用品");
	fullChain->processRequest(smallRequest);

	chain_of_responsibility::Request mediumRequest(chain_of_responsibility::Request::Type::REFUND, 3000, "客户退款");
	fullChain->processRequest(mediumRequest);

	chain_of_responsibility::Request largeRequest(chain_of_responsibility::Request::Type::PURCHASE, 8000, "新设备");
	fullChain->processRequest(largeRequest);

	chain_of_responsibility::Request hugeRequest(chain_of_responsibility::Request::Type::PURCHASE, 50000, "公司用车");
	fullChain->processRequest(hugeRequest);

	std::cout << "\n==========================================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
