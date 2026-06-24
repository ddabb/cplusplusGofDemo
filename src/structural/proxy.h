#pragma once
// 文件: src/structural/proxy.h
// 说明: 代理模式示例（虚拟代理/受保护代理/日志代理）
// 建议: 保护代理示例中存储密码为示例用法，生产环境请使用安全存储与哈希比较。

#include <iostream>
#include <memory>
#include <string>
#include <mutex>

namespace design_patterns::structural::proxy {

/**
 * @brief 图像接口
 *
 * 定义图像对象的通用接口。
 */
class Image {
public:
    virtual ~Image() = default;
    /**
     * @brief 显示图像
     */
    virtual void display() const = 0;
    /**
     * @brief 获取图像名称
     * @return 图像名称
     */
    virtual std::string getName() const = 0;
};

/**
 * @brief 真实图像
 *
 * 实际的图像实现类，负责加载和显示图像。
 */
class RealImage : public Image {
public:
    explicit RealImage(const std::string& filename) : filename_(filename) {
        loadFromDisk();
    }

    /**
     * @brief 从磁盘加载图像
     */
    void loadFromDisk() const {
        std::cout << "[真实图像] 加载图像: " << filename_ << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "[真实图像] 加载中..." << (i + 1) << "/3" << std::endl;
        }
        std::cout << "[真实图像] 图像加载成功！" << std::endl;
    }

    void display() const override {
        std::cout << "[真实图像] 显示图像: " << filename_ << std::endl;
    }

    std::string getName() const override {
        return filename_;
    }

private:
    std::string filename_;
};

/**
 * @brief 虚拟代理图像
 *
 * 延迟加载真实图像，只有在需要时才创建真实对象。
 */
class ProxyImage : public Image {
public:
    explicit ProxyImage(const std::string& filename) 
        : filename_(filename), realImage_(nullptr) {
        std::cout << "[虚拟代理] 创建代理: " << filename_ << std::endl;
    }

    void display() const override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!realImage_) {
            std::cout << "[虚拟代理] 创建真实图像: " << filename_ << std::endl;
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        std::cout << "[虚拟代理] 委托显示给真实图像" << std::endl;
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

/**
 * @brief 受保护代理图像
 *
 * 提供访问控制，只有通过认证才能访问真实图像。
 */
class ProtectedImage : public Image {
public:
    ProtectedImage(std::unique_ptr<Image> image, const std::string& password)
        : image_(std::move(image)), password_(password) {
        std::cout << "[受保护代理] 创建保护代理: " << image_->getName() << std::endl;
    }

    void display() const override {
        std::cout << "[受保护代理] 检查访问权限..." << std::endl;
        if (authenticated_) {
            std::cout << "[受保护代理] 访问已授权" << std::endl;
            image_->display();
        } else {
            std::cout << "[受保护代理] 访问被拒绝！请先进行认证。" << std::endl;
        }
    }

    /**
     * @brief 进行认证
     * @param password 密码
     * @return 是否认证成功
     */
    bool authenticate(const std::string& password) {
        std::cout << "[受保护代理] 进行认证..." << std::endl;
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

/**
 * @brief 日志代理图像
 *
 * 在访问真实图像时记录日志。
 */
class LoggingImage : public Image {
public:
    explicit LoggingImage(std::unique_ptr<Image> image)
        : image_(std::move(image)) {
        std::cout << "[日志代理] 创建日志代理: " << image_->getName() << std::endl;
    }

    void display() const override {
        std::cout << "[日志代理] [LOG] 显示前: " << image_->getName() << std::endl;
        image_->display();
        std::cout << "[日志代理] [LOG] 显示后: " << image_->getName() << std::endl;
    }

    std::string getName() const override {
        return image_->getName();
    }

private:
    std::unique_ptr<Image> image_;
};

}

namespace design_patterns::structural {
// demo implementation moved to src/structural/proxy.cpp
void proxy_demo();

}
