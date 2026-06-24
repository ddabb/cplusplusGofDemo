#include "structural/proxy.h"
#include <iostream>

namespace design_patterns::structural {

/**
 * @brief 代理模式演示函数
 *
 * 演示代理模式的三种变体：虚拟代理（延迟加载）、受保护代理（访问控制）、日志代理。
 */
void proxy_demo() {
	std::cout << "\n========== 代理模式演示 ==========" << std::endl;
	std::cout << "[演示] 代理模式核心：为对象提供代理以控制对其的访问\n" << std::endl;

	std::cout << "[演示] --- 虚拟代理（延迟加载）---" << std::endl;
	std::unique_ptr<proxy::Image> proxy1 = std::make_unique<proxy::ProxyImage>("photo1.jpg");
	std::cout << "\n[演示] 第一次显示（创建真实图像）:" << std::endl;
	proxy1->display();
	std::cout << "\n[演示] 第二次显示（使用已存在的真实图像）:" << std::endl;
	proxy1->display();

	std::cout << std::endl;

	std::cout << "[演示] --- 受保护代理（访问控制）---" << std::endl;
	auto protectedImage = std::make_unique<proxy::ProtectedImage>(
		std::make_unique<proxy::RealImage>("secret.jpg"), "password123");

	std::cout << "\n[演示] 未认证时显示:" << std::endl;
	protectedImage->display();

	std::cout << "\n[演示] 使用错误密码认证:" << std::endl;
	bool success = protectedImage->authenticate("wrong");
	std::cout << "[受保护代理] 认证结果: " << (success ? "成功" : "失败") << std::endl;
	protectedImage->display();

	std::cout << "\n[演示] 使用正确密码认证:" << std::endl;
	success = protectedImage->authenticate("password123");
	std::cout << "[受保护代理] 认证结果: " << (success ? "成功" : "失败") << std::endl;
	protectedImage->display();

	std::cout << std::endl;

	std::cout << "[演示] --- 日志代理 ---" << std::endl;
	std::unique_ptr<proxy::Image> loggingImage = std::make_unique<proxy::LoggingImage>(
		std::make_unique<proxy::RealImage>("public.jpg"));
	loggingImage->display();

	std::cout << "==========================================\n" << std::endl;
}

}
