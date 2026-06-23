#include "state.h"

namespace design_patterns::behavioral {

void state_demo() {
	std::cout << "\n========== State Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] State Pattern: behavior changes when internal state changes\n" << std::endl;

	std::unique_ptr<state::Context> order = std::make_unique<state::Context>(std::make_unique<state::PendingPaymentState>());

	std::cout << "\n[Demo] --- Processing Order ---" << std::endl;

	std::cout << "\nStep 1: Current state - " << order->getCurrentStateName() << std::endl;
	order->request();

	std::cout << "\nStep 2: Current state - " << order->getCurrentStateName() << std::endl;
	order->request();

	std::cout << "\nStep 3: Current state - " << order->getCurrentStateName() << std::endl;
	order->request();

	std::cout << "\nStep 4: Current state - " << order->getCurrentStateName() << std::endl;
	order->request();

	std::cout << "\n[Demo] --- Trying to process completed order ---" << std::endl;
	order->request();

	std::cout << "\n========================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
