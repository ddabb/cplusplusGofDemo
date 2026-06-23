#pragma once
// 文件: src/structural/proxy.h
// 说明: 代理模式示例（虚拟代理/受保护代理/日志代理）
// 建议: 保护代理示例中存储密码为示例用法，生产环境请使用安全存储与哈希比较。

#include <iostream>
#include <memory>
#include <string>
#include <mutex>

namespace design_patterns::structural::proxy {

class Image {
public:
    virtual ~Image() = default;
    virtual void display() const = 0;
    virtual std::string getName() const = 0;
};

class RealImage : public Image {
public:
    explicit RealImage(const std::string& filename) : filename_(filename) {
        loadFromDisk();
    }

    void loadFromDisk() const {
        std::cout << "[RealImage] Loading image: " << filename_ << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "[RealImage] Loading..." << (i + 1) << "/3" << std::endl;
        }
        std::cout << "[RealImage] Image loaded successfully!" << std::endl;
    }

    void display() const override {
        std::cout << "[RealImage] Displaying image: " << filename_ << std::endl;
    }

    std::string getName() const override {
        return filename_;
    }

private:
    std::string filename_;
};

class ProxyImage : public Image {
public:
    explicit ProxyImage(const std::string& filename) 
        : filename_(filename), realImage_(nullptr) {
        std::cout << "[ProxyImage] Created proxy for: " << filename_ << std::endl;
    }

    void display() const override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!realImage_) {
            std::cout << "[ProxyImage] Creating RealImage for: " << filename_ << std::endl;
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        std::cout << "[ProxyImage] Delegating display to RealImage" << std::endl;
        realImage_->display();
    }

    std::string getName() const override {
        return filename_;
    }

private:
    mutable std::mutex mutex_;
    std::string filename_;
    mutable std::unique_ptr<RealImage> realImage_;
};

class ProtectedImage : public Image {
public:
    ProtectedImage(std::unique_ptr<Image> image, const std::string& password)
        : image_(std::move(image)), password_(password) {
        std::cout << "[ProtectedImage] Created protected proxy for: " << image_->getName() << std::endl;
    }

    void display() const override {
        std::cout << "[ProtectedImage] Checking access..." << std::endl;
        if (authenticated_) {
            std::cout << "[ProtectedImage] Access granted" << std::endl;
            image_->display();
        } else {
            std::cout << "[ProtectedImage] Access denied! Please authenticate first." << std::endl;
        }
    }

    bool authenticate(const std::string& password) {
        std::cout << "[ProtectedImage] Authenticating..." << std::endl;
        authenticated_ = (password == password_);
        return authenticated_;
    }

    std::string getName() const override {
        return image_->getName();
    }

private:
    std::unique_ptr<Image> image_;
    std::string password_;
    mutable bool authenticated_ = false;
};

class LoggingImage : public Image {
public:
    explicit LoggingImage(std::unique_ptr<Image> image)
        : image_(std::move(image)) {
        std::cout << "[LoggingImage] Created logging proxy for: " << image_->getName() << std::endl;
    }

    void display() const override {
        std::cout << "[LoggingImage] [LOG] Before display: " << image_->getName() << std::endl;
        image_->display();
        std::cout << "[LoggingImage] [LOG] After display: " << image_->getName() << std::endl;
    }

    std::string getName() const override {
        return image_->getName();
    }

private:
    std::unique_ptr<Image> image_;
};

}

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
