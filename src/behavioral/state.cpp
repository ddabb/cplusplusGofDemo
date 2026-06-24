#include "behavioral/state.h"
#include <iostream>

namespace design_patterns::behavioral::state {

void PendingPaymentState::handle(Context& context) const {
    std::cout << "[PendingPaymentState] Order is pending payment" << std::endl;
    std::cout << "[PendingPaymentState] Processing payment..." << std::endl;
    std::cout << "[PendingPaymentState] Payment successful!" << std::endl;
    context.setState(std::make_unique<PaidState>());
}

void PaidState::handle(Context& context) const {
    std::cout << "[PaidState] Order has been paid" << std::endl;
    std::cout << "[PaidState] Preparing shipment..." << std::endl;
    std::cout << "[PaidState] Shipment prepared!" << std::endl;
    context.setState(std::make_unique<ShippedState>());
}

void ShippedState::handle(Context& context) const {
    std::cout << "[ShippedState] Order has been shipped" << std::endl;
    std::cout << "[ShippedState] Delivering to customer..." << std::endl;
    std::cout << "[ShippedState] Order delivered!" << std::endl;
    context.setState(std::make_unique<CompletedState>());
}

void CompletedState::handle(Context& context) const {
    std::cout << "[CompletedState] Order has been completed" << std::endl;
    std::cout << "[CompletedState] Thank you for your purchase!" << std::endl;
}

void state_demo() {
    std::cout << "\n========== State Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] State Pattern: object behavior changes based on state\n" << std::endl;

    std::cout << "[Demo] --- Creating Order with PendingPayment state ---" << std::endl;
    Context order(std::make_unique<PendingPaymentState>());

    std::cout << "\n[Demo] --- Processing Order ---" << std::endl;
    order.request();
    order.request();
    order.request();
    order.request();

    std::cout << "\n=========================================\n" << std::endl;
}

}
