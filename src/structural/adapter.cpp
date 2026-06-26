#include "structural/adapter.h"
#include <iostream>

namespace design_patterns::structural::adapter {

void Adaptee::specificRequest() const {
    std::cout << "[被适配者] 特定请求：这是遗留系统的接口" << std::endl;
}

std::string Adaptee::specificRequestWithData(const std::string& data) const {
    std::cout << "[被适配者] 处理数据: " << data << std::endl;
    return "处理完成: " + data;
}

ObjectAdapter::ObjectAdapter(std::unique_ptr<Adaptee> adaptee)
    : adaptee_(std::move(adaptee)) {
    std::cout << "[对象适配器] 构造函数被调用" << std::endl;
}

void ObjectAdapter::request() const {
    std::cout << "[对象适配器] 将请求适配为 specificRequest" << std::endl;
    adaptee_->specificRequest();
}

void ClassAdapter::request() const {
    std::cout << "[类适配器] 将请求适配为 specificRequest" << std::endl;
    specificRequest();
}

AdvancedAdapter::AdvancedAdapter(std::unique_ptr<Adaptee> adaptee)
    : adaptee_(std::move(adaptee)) {}

void AdvancedAdapter::request() const {
    std::cout << "[高级适配器] 执行复杂适配..." << std::endl;
    std::string result = adaptee_->specificRequestWithData("适配器输入");
    std::cout << "[高级适配器] 结果: " << result << std::endl;
    std::cout << "[高级适配器] 额外处理..." << std::endl;
}

}

namespace design_patterns::structural {

/**
 * @brief 适配器模式演示函数
 *
 * 演示适配器模式的三种变体：对象适配器、类适配器、高级适配器。
 */
void adapter_demo() {
	std::cout << "\n========== 适配器模式演示 ==========" << std::endl;
	std::cout << "[演示] 适配器模式核心：将不兼容的接口转换为兼容的接口\n" << std::endl;

	std::cout << "[演示] --- 对象适配器 ---" << std::endl;
	std::unique_ptr<adapter::Target> objectAdapter = 
		std::make_unique<adapter::ObjectAdapter>(std::make_unique<adapter::Adaptee>());
	objectAdapter->request();

	std::cout << std::endl;

	std::cout << "[演示] --- 类适配器 ---" << std::endl;
	std::unique_ptr<adapter::Target> classAdapter = std::make_unique<adapter::ClassAdapter>();
	classAdapter->request();

	std::cout << std::endl;

	std::cout << "[演示] --- 高级适配器 ---" << std::endl;
	std::unique_ptr<adapter::Target> advancedAdapter = 
		std::make_unique<adapter::AdvancedAdapter>(std::make_unique<adapter::Adaptee>());
	advancedAdapter->request();

	std::cout << "==========================================\n" << std::endl;
}

}
