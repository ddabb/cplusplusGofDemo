#include <iostream>
#include <string>

#include "src/creational/singleton.h"
#include "src/creational/factory_method.h"
#include "src/creational/abstract_factory.h"
#include "src/creational/builder.h"
#include "src/creational/prototype.h"

#include "src/structural/adapter.h"
#include "src/structural/bridge.h"
#include "src/structural/composite.h"
#include "src/structural/decorator.h"
#include "src/structural/facade.h"
#include "src/structural/flyweight.h"
#include "src/structural/proxy.h"

#include "src/behavioral/observer.h"
#include "src/behavioral/template_method.h"
#include "src/behavioral/strategy.h"
#include "src/behavioral/chain_of_responsibility.h"
#include "src/behavioral/command.h"
#include "src/behavioral/iterator.h"
#include "src/behavioral/state.h"
#include "src/behavioral/memento.h"
#include "src/behavioral/visitor.h"
#include "src/behavioral/mediator.h"
#include "src/behavioral/interpreter.h"

#ifdef USE_SFML
#include "src/gui/main_window.h"
#endif

void printMenu() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "    C++设计模式示例项目" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "\n【创建型模式】" << std::endl;
    std::cout << "  1. 单例模式 (Singleton)" << std::endl;
    std::cout << "  2. 工厂方法模式 (Factory Method)" << std::endl;
    std::cout << "  3. 抽象工厂模式 (Abstract Factory)" << std::endl;
    std::cout << "  4. 建造者模式 (Builder)" << std::endl;
    std::cout << "  5. 原型模式 (Prototype)" << std::endl;
    std::cout << "\n【结构型模式】" << std::endl;
    std::cout << "  6. 适配器模式 (Adapter)" << std::endl;
    std::cout << "  7. 桥接模式 (Bridge)" << std::endl;
    std::cout << "  8. 组合模式 (Composite)" << std::endl;
    std::cout << "  9. 装饰器模式 (Decorator)" << std::endl;
    std::cout << " 10. 外观模式 (Facade)" << std::endl;
    std::cout << " 11. 享元模式 (Flyweight)" << std::endl;
    std::cout << " 12. 代理模式 (Proxy)" << std::endl;
    std::cout << "\n【行为型模式】" << std::endl;
    std::cout << " 13. 观察者模式 (Observer)" << std::endl;
    std::cout << " 14. 模板方法模式 (Template Method)" << std::endl;
    std::cout << " 15. 策略模式 (Strategy)" << std::endl;
    std::cout << " 16. 责任链模式 (Chain of Responsibility)" << std::endl;
    std::cout << " 17. 命令模式 (Command)" << std::endl;
    std::cout << " 18. 迭代器模式 (Iterator)" << std::endl;
    std::cout << " 19. 状态模式 (State)" << std::endl;
    std::cout << " 20. 备忘录模式 (Memento)" << std::endl;
    std::cout << " 21. 访问者模式 (Visitor)" << std::endl;
    std::cout << " 22. 中介者模式 (Mediator)" << std::endl;
    std::cout << " 23. 解释器模式 (Interpreter)" << std::endl;
    std::cout << "\n【其他】" << std::endl;
    std::cout << " 99. 运行所有模式" << std::endl;
    std::cout << "  0. 退出" << std::endl;
    std::cout << "\n请选择要演示的模式 (输入数字): ";
}

void runConsoleMode() {
    std::cout << "欢迎使用 C++设计模式示例项目!" << std::endl;
    std::cout << "本项目包含23种经典GoF设计模式的C++20实现" << std::endl;

    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: design_patterns::creational::singleton_demo(); break;
            case 2: design_patterns::creational::factory_method_demo(); break;
            case 3: design_patterns::creational::abstract_factory_demo(); break;
            case 4: design_patterns::creational::builder_demo(); break;
            case 5: design_patterns::creational::prototype_demo(); break;
            
            case 6: design_patterns::structural::adapter_demo(); break;
            case 7: design_patterns::structural::bridge_demo(); break;
            case 8: design_patterns::structural::composite_demo(); break;
            case 9: design_patterns::structural::decorator_demo(); break;
            case 10: design_patterns::structural::facade_demo(); break;
            case 11: design_patterns::structural::flyweight_demo(); break;
            case 12: design_patterns::structural::proxy_demo(); break;
            
            case 13: design_patterns::behavioral::observer_demo(); break;
            case 14: design_patterns::behavioral::template_method_demo(); break;
            case 15: design_patterns::behavioral::strategy_demo(); break;
            case 16: design_patterns::behavioral::chain_of_responsibility_demo(); break;
            case 17: design_patterns::behavioral::command_demo(); break;
            case 18: design_patterns::behavioral::iterator_demo(); break;
            case 19: design_patterns::behavioral::state_demo(); break;
            case 20: design_patterns::behavioral::memento_demo(); break;
            case 21: design_patterns::behavioral::visitor_demo(); break;
            case 22: design_patterns::behavioral::mediator_demo(); break;
            case 23: design_patterns::behavioral::interpreter_demo(); break;
            
            case 99:
                design_patterns::creational::singleton_demo();
                design_patterns::creational::factory_method_demo();
                design_patterns::creational::abstract_factory_demo();
                design_patterns::creational::builder_demo();
                design_patterns::creational::prototype_demo();
                design_patterns::structural::adapter_demo();
                design_patterns::structural::bridge_demo();
                design_patterns::structural::composite_demo();
                design_patterns::structural::decorator_demo();
                design_patterns::structural::facade_demo();
                design_patterns::structural::flyweight_demo();
                design_patterns::structural::proxy_demo();
                design_patterns::behavioral::observer_demo();
                design_patterns::behavioral::template_method_demo();
                design_patterns::behavioral::strategy_demo();
                design_patterns::behavioral::chain_of_responsibility_demo();
                design_patterns::behavioral::command_demo();
                design_patterns::behavioral::iterator_demo();
                design_patterns::behavioral::state_demo();
                design_patterns::behavioral::memento_demo();
                design_patterns::behavioral::visitor_demo();
                design_patterns::behavioral::mediator_demo();
                design_patterns::behavioral::interpreter_demo();
                break;
                
            case 0:
                std::cout << "\n感谢使用 C++设计模式示例项目!" << std::endl;
                break;
                
            default:
                std::cout << "\n无效的选择，请重新输入!" << std::endl;
                break;
        }
    }
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "    C++设计模式示例项目" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "\n请选择运行模式:" << std::endl;
    std::cout << "  1. GUI图形界面模式" << std::endl;
    std::cout << "  2. 控制台模式" << std::endl;
    std::cout << "\n请输入选择 (1或2): ";

    int modeChoice;
    std::cin >> modeChoice;

    if (modeChoice == 1) {
#ifdef USE_SFML
        try {
            design_patterns::gui::DesignPatternWindow window;
            window.run();
        } catch (const std::exception& e) {
            std::cerr << "GUI模式启动失败: " << e.what() << std::endl;
            std::cout << "自动切换到控制台模式..." << std::endl;
            runConsoleMode();
        }
#else
        std::cout << "GUI模式不可用，SFML库未配置" << std::endl;
        std::cout << "自动切换到控制台模式..." << std::endl;
        runConsoleMode();
#endif
    } else {
        runConsoleMode();
    }

    return 0;
}
