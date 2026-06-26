#include "structural/proxy.h"
#include <iostream>

namespace design_patterns::structural::proxy {

RealImage::RealImage(const std::string& filename) : filename_(filename) {
    loadFromDisk();
}

void RealImage::loadFromDisk() const {
    std::cout << "[真实图像] 加载图像: " << filename_ << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "[真实图像] 加载中..." << (i + 1) << "/3" << std::endl;
    }
    std::cout << "[真实图像] 图像加载成功！" << std::endl;
}

void RealImage::display() const {
    std::cout << "[真实图像] 显示图像: " << filename_ << std::endl;
}

std::string RealImage::getName() const {
    return filename_;
}

ProxyImage::ProxyImage(const std::string& filename) 
    : filename_(filename), realImage_(nullptr) {
    std::cout << "[虚拟代理] 创建代理: " << filename_ << std::endl;
}

void ProxyImage::display() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!realImage_) {
        std::cout << "[虚拟代理] 创建真实图像: " << filename_ << std::endl;
        realImage_ = std::make_unique<RealImage>(filename_);
    }
    std::cout << "[虚拟代理] 委托显示给真实图像" << std::endl;
    realImage_->display();
}

std::string ProxyImage::getName() const {
    return filename_;
}

ProtectedImage::ProtectedImage(std::unique_ptr<Image> image, const std::string& password)
    : image_(std::move(image)), password_(password) {
    std::cout << "[受保护代理] 创建保护代理: " << image_->getName() << std::endl;
}

void ProtectedImage::display() const {
    std::cout << "[受保护代理] 检查访问权限..." << std::endl;
    if (authenticated_) {
        std::cout << "[受保护代理] 访问已授权" << std::endl;
        image_->display();
    } else {
        std::cout << "[受保护代理] 访问被拒绝！请先进行认证。" << std::endl;
    }
}

bool ProtectedImage::authenticate(const std::string& password) {
    std::cout << "[受保护代理] 进行认证..." << std::endl;
    authenticated_ = (password == password_);
    return authenticated_;
}

std::string ProtectedImage::getName() const {
    return image_->getName();
}

LoggingImage::LoggingImage(std::unique_ptr<Image> image)
    : image_(std::move(image)) {
    std::cout << "[日志代理] 创建日志代理: " << image_->getName() << std::endl;
}

void LoggingImage::display() const {
    std::cout << "[日志代理] [LOG] 显示前: " << image_->getName() << std::endl;
    image_->display();
    std::cout << "[日志代理] [LOG] 显示后: " << image_->getName() << std::endl;
}

std::string LoggingImage::getName() const {
    return image_->getName();
}

}

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
