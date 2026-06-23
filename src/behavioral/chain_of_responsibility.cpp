#include "behavioral/chain_of_responsibility.h"

namespace design_patterns::behavioral {

void chain_of_responsibility_demo() {
	std::cout << "\n========== Chain of Responsibility Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 责任链模式核心：多个对象处理请求，沿链传递直到被处理\n" << std::endl;

	std::cout << "[Demo] --- Creating Approvers ---" << std::endl;

	auto fullChain = std::make_unique<chain_of_responsibility::Supervisor>("Alice");
	auto m = std::make_unique<chain_of_responsibility::Manager>("Bob");
	auto d = std::make_unique<chain_of_responsibility::Director>("Charlie");
	auto c = std::make_unique<chain_of_responsibility::CEO>("David");
	d->setSuccessor(std::move(c));
	m->setSuccessor(std::move(d));
	fullChain->setSuccessor(std::move(m));

	std::cout << "\n[Demo] --- Processing Requests ---" << std::endl;

	chain_of_responsibility::Request smallRequest(chain_of_responsibility::Request::Type::PURCHASE, 500, "Office supplies");
	fullChain->processRequest(smallRequest);

	chain_of_responsibility::Request mediumRequest(chain_of_responsibility::Request::Type::REFUND, 3000, "Customer refund");
	fullChain->processRequest(mediumRequest);

	chain_of_responsibility::Request largeRequest(chain_of_responsibility::Request::Type::PURCHASE, 8000, "New equipment");
	fullChain->processRequest(largeRequest);

	chain_of_responsibility::Request hugeRequest(chain_of_responsibility::Request::Type::PURCHASE, 50000, "Company car");
	fullChain->processRequest(hugeRequest);

	std::cout << "\n==========================================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
