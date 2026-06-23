#include "structural/proxy.h"
#include <iostream>

namespace design_patterns::structural {

void proxy_demo() {
	std::cout << "\n========== Proxy Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] 代理模式核心：为对象提供代理以控制对其的访问\n" << std::endl;

	std::cout << "[Demo] --- Virtual Proxy (Lazy Loading) ---" << std::endl;
	std::unique_ptr<proxy::Image> proxy1 = std::make_unique<proxy::ProxyImage>("photo1.jpg");
	std::cout << "\n[Demo] First display (creates RealImage):" << std::endl;
	proxy1->display();
	std::cout << "\n[Demo] Second display (uses existing RealImage):" << std::endl;
	proxy1->display();

	std::cout << std::endl;

	std::cout << "[Demo] --- Protected Proxy (Access Control) ---" << std::endl;
	auto protectedImage = std::make_unique<proxy::ProtectedImage>(
		std::make_unique<proxy::RealImage>("secret.jpg"), "password123");

	std::cout << "\n[Demo] Display without authentication:" << std::endl;
	protectedImage->display();

	std::cout << "\n[Demo] Authenticating with wrong password:" << std::endl;
	bool success = protectedImage->authenticate("wrong");
	std::cout << "[ProtectedImage] Authentication: " << (success ? "SUCCESS" : "FAILED") << std::endl;
	protectedImage->display();

	std::cout << "\n[Demo] Authenticating with correct password:" << std::endl;
	success = protectedImage->authenticate("password123");
	std::cout << "[ProtectedImage] Authentication: " << (success ? "SUCCESS" : "FAILED") << std::endl;
	protectedImage->display();

	std::cout << std::endl;

	std::cout << "[Demo] --- Logging Proxy ---" << std::endl;
	std::unique_ptr<proxy::Image> loggingImage = std::make_unique<proxy::LoggingImage>(
		std::make_unique<proxy::RealImage>("public.jpg"));
	loggingImage->display();

	std::cout << "==========================================\n" << std::endl;
}

}
