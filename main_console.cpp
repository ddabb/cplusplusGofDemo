// Windows 平台头文件:用于设置控制台输出代码页为 UTF-8
// 注意: 必须在所有 C++ 标准库头文件之前包含,
// 并用 NOMINMAX 宏避免 windows.h 中的 min/max 宏与 std::numeric_limits 冲突
#ifdef _WIN32
#define NOMINMAX  // 禁用 windows.h 中的 min/max 宏定义
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <limits>

// 创建型模式头文件
#include "creational/singleton.h"
#include "creational/factory_method.h"
#include "creational/abstract_factory.h"
#include "creational/builder.h"
#include "creational/prototype.h"

// 结构型模式头文件
#include "structural/adapter.h"
#include "structural/bridge.h"
#include "structural/composite.h"
#include "structural/decorator.h"
#include "structural/facade.h"
#include "structural/flyweight.h"
#include "structural/proxy.h"

// 行为型模式头文件
#include "behavioral/observer.h"
#include "behavioral/template_method.h"
#include "behavioral/strategy.h"
#include "behavioral/chain_of_responsibility.h"
#include "behavioral/command.h"
#include "behavioral/iterator.h"
#include "behavioral/state.h"
#include "behavioral/memento.h"
#include "behavioral/visitor.h"
#include "behavioral/mediator.h"
#include "behavioral/interpreter.h"

/**
 * @brief 设计模式信息结构体
 *
 * 用于在菜单中展示每个设计模式的基本信息。
 */
struct PatternInfo {
    int id;                  // 编号
    std::string name;        // 中文名称
    std::string nameEn;      // 英文名称
    std::string category;    // 分类(创建型/结构型/行为型)
    std::string description; // 模式描述
};

/**
 * @brief 获取所有设计模式列表
 * @return 包含 23 种经典 GoF 设计模式信息的列表
 */
std::vector<PatternInfo> getPatternList() {
    return {
        // 【创建型模式 - 5 种】
        {1, "单例模式",       "Singleton",                "创建型", "确保一个类只有一个实例,并提供全局访问点"},
        {2, "工厂方法模式",   "Factory Method",           "创建型", "定义创建对象的接口,由子类决定实例化哪个类"},
        {3, "抽象工厂模式",   "Abstract Factory",         "创建型", "创建一系列相关或相互依赖的对象族"},
        {4, "建造者模式",     "Builder",                  "创建型", "分步骤构建复杂对象,分离构建过程与表示"},
        {5, "原型模式",       "Prototype",                "创建型", "通过克隆原型实例来创建新对象,避免重复初始化"},

        // 【结构型模式 - 7 种】
        {6,  "适配器模式",    "Adapter",                  "结构型", "将一个类的接口转换为客户端期望的另一种接口"},
        {7,  "桥接模式",      "Bridge",                   "结构型", "将抽象部分与实现部分分离,使它们可以独立变化"},
        {8,  "组合模式",      "Composite",                "结构型", "将对象组合成树形结构以表示『部分-整体』层次"},
        {9,  "装饰器模式",    "Decorator",                "结构型", "动态地给对象添加额外职责,比继承更灵活"},
        {10, "外观模式",      "Facade",                   "结构型", "为子系统中的一组接口提供统一的高层接口"},
        {11, "享元模式",      "Flyweight",                "结构型", "通过共享技术有效地支持大量细粒度对象"},
        {12, "代理模式",      "Proxy",                    "结构型", "为其他对象提供一种代理以控制对这个对象的访问"},

        // 【行为型模式 - 11 种】
        {13, "观察者模式",    "Observer",                 "行为型", "定义对象间一对多的依赖关系,状态变化时自动通知"},
        {14, "模板方法模式",  "Template Method",          "行为型", "在父类中定义算法骨架,将某些步骤延迟到子类实现"},
        {15, "策略模式",      "Strategy",                 "行为型", "定义一系列算法,将每个算法封装起来并使它们可互换"},
        {16, "责任链模式",    "Chain of Responsibility",  "行为型", "将请求沿处理者链传递,直到有对象处理它为止"},
        {17, "命令模式",      "Command",                  "行为型", "将请求封装为对象,从而支持撤销、日志、队列等操作"},
        {18, "迭代器模式",    "Iterator",                 "行为型", "提供一种方法顺序访问聚合对象中的各个元素"},
        {19, "状态模式",      "State",                    "行为型", "允许对象在其内部状态改变时改变其行为"},
        {20, "备忘录模式",    "Memento",                  "行为型", "在不破坏封装性的前提下,捕获并保存对象的内部状态"},
        {21, "访问者模式",    "Visitor",                  "行为型", "将算法与其所作用的对象结构分离,便于新增操作"},
        {22, "中介者模式",    "Mediator",                 "行为型", "用一个中介对象封装一系列对象的交互,降低耦合"},
        {23, "解释器模式",    "Interpreter",              "行为型", "定义语言的文法表示,并提供解释器解释语言中的句子"}
    };
}

/**
 * @brief 打印主菜单
 *
 * 显示所有 23 种设计模式的分类菜单,供用户选择。
 */
void printMenu() {
    std::cout << "\n";
    std::cout << "============================================" << std::endl;
    std::cout << "         C++ 设计模式演示程序" << std::endl;
    std::cout << "============================================" << std::endl;

    // 创建型模式
    std::cout << "\n【创建型模式】(共 5 种)" << std::endl;
    std::cout << "  1. 单例模式 (Singleton)" << std::endl;
    std::cout << "  2. 工厂方法模式 (Factory Method)" << std::endl;
    std::cout << "  3. 抽象工厂模式 (Abstract Factory)" << std::endl;
    std::cout << "  4. 建造者模式 (Builder)" << std::endl;
    std::cout << "  5. 原型模式 (Prototype)" << std::endl;

    // 结构型模式
    std::cout << "\n【结构型模式】(共 7 种)" << std::endl;
    std::cout << "  6. 适配器模式 (Adapter)" << std::endl;
    std::cout << "  7. 桥接模式 (Bridge)" << std::endl;
    std::cout << "  8. 组合模式 (Composite)" << std::endl;
    std::cout << "  9. 装饰器模式 (Decorator)" << std::endl;
    std::cout << " 10. 外观模式 (Facade)" << std::endl;
    std::cout << " 11. 享元模式 (Flyweight)" << std::endl;
    std::cout << " 12. 代理模式 (Proxy)" << std::endl;

    // 行为型模式
    std::cout << "\n【行为型模式】(共 11 种)" << std::endl;
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

    // 其他选项
    std::cout << "\n【其他选项】" << std::endl;
    std::cout << " 99. 运行所有模式" << std::endl;
    std::cout << "  0. 退出程序" << std::endl;
    std::cout << "\n请输入要演示的模式编号: ";
}

/**
 * @brief 打印指定模式的信息
 * @param pattern 模式信息结构体
 */
void printPatternInfo(const PatternInfo& pattern) {
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "【" << pattern.id << "】 " << pattern.name
              << "  (" << pattern.nameEn << ")" << std::endl;
    std::cout << "分    类: " << pattern.category << std::endl;
    std::cout << "模式描述: " << pattern.description << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

/**
 * @brief 根据用户选择运行对应的模式演示
 * @param choice 模式编号(1-23)
 */
void runPattern(int choice) {
    switch (choice) {
        // 创建型模式
        case 1: design_patterns::creational::singleton_demo(); break;
        case 2: design_patterns::creational::factory_method_demo(); break;
        case 3: design_patterns::creational::abstract_factory_demo(); break;
        case 4: design_patterns::creational::builder_demo(); break;
        case 5: design_patterns::creational::prototype_demo(); break;

        // 结构型模式
        case 6:  design_patterns::structural::adapter_demo(); break;
        case 7:  design_patterns::structural::bridge_demo(); break;
        case 8:  design_patterns::structural::composite_demo(); break;
        case 9:  design_patterns::structural::decorator_demo(); break;
        case 10: design_patterns::structural::facade_demo(); break;
        case 11: design_patterns::structural::flyweight_demo(); break;
        case 12: design_patterns::structural::proxy_demo(); break;

        // 行为型模式
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

        default:
            std::cout << "无效的选择!" << std::endl;
            break;
    }
}

/**
 * @brief 依次运行所有 23 种设计模式演示
 */
void runAllPatterns() {
    std::cout << "\n============================================" << std::endl;
    std::cout << "       正在依次运行所有 23 种设计模式..." << std::endl;
    std::cout << "============================================" << std::endl;

    for (int i = 1; i <= 23; ++i) {
        auto patterns = getPatternList();
        // 在模式列表中查找当前编号
        auto it = std::find_if(patterns.begin(), patterns.end(),
            [i](const PatternInfo& p) { return p.id == i; });
        if (it != patterns.end()) {
            printPatternInfo(*it);  // 打印模式信息
            runPattern(i);          // 运行模式演示
        }
    }

    std::cout << "\n============================================" << std::endl;
    std::cout << "       全部 23 种设计模式演示完成!" << std::endl;
    std::cout << "============================================" << std::endl;
}

/**
 * @brief 程序主入口
 *
 * 支持两种运行模式:
 * 1. 命令行模式: 通过参数指定要运行的模式
 * 2. 交互模式: 显示菜单供用户选择
 *
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 程序退出码
 */
int main(int argc, char** argv) {
    // 在 Windows 上设置控制台输出为 UTF-8 编码,确保中文正确显示
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);     // 设置控制台输出代码页为 UTF-8
        SetConsoleCP(CP_UTF8);           // 设置控制台输入代码页为 UTF-8
    #endif

    // 命令行支持:
    // --all            : 运行所有 demo
    // --pattern <N>    : 运行指定编号的 demo (1-23)
    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "--all") {
            runAllPatterns();
            return 0;
        }
        if (arg1 == "--pattern" && argc > 2) {
            try {
                int p = std::stoi(argv[2]);
                if (p >= 1 && p <= 23) {
                    auto patterns = getPatternList();
                    auto it = std::find_if(patterns.begin(), patterns.end(),
                        [p](const PatternInfo& pp) { return pp.id == p; });
                    if (it != patterns.end()) {
                        printPatternInfo(*it);
                        runPattern(p);
                    }
                } else {
                    std::cerr << "无效的模式编号,请使用 1-23 之间的数字。" << std::endl;
                }
            } catch (...) {
                std::cerr << "解析模式编号失败,请检查输入是否为有效数字。" << std::endl;
            }
            return 0;
        }
    }

    // 交互模式:显示欢迎信息
    std::cout << "\n";
    std::cout << "============================================" << std::endl;
    std::cout << "    欢迎使用 C++ 设计模式演示程序!" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\n本项目包含 23 种经典的 GoF 设计模式," << std::endl;
    std::cout << "使用 C++20 标准实现,并附带详细的中文注释。\n" << std::endl;

    auto patterns = getPatternList();
    int choice = -1;

    // 主循环:持续接收用户输入直到选择退出
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        // 处理无效输入(非数字)
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n输入无效,请输入正确的数字!" << std::endl;
            continue;
        }

        // 退出选项
        if (choice == 0) {
            std::cout << "\n感谢使用 C++ 设计模式演示程序!" << std::endl;
            std::cout << "再见!\n" << std::endl;
            break;
        }

        // 运行所有模式
        if (choice == 99) {
            runAllPatterns();
            continue;
        }

        // 运行指定编号的模式
        if (choice >= 1 && choice <= 23) {
            auto it = std::find_if(patterns.begin(), patterns.end(),
                [choice](const PatternInfo& p) { return p.id == choice; });
            if (it != patterns.end()) {
                printPatternInfo(*it);
                runPattern(choice);
            }
        } else {
            std::cout << "\n无效选择,请输入 0-99 之间的数字!" << std::endl;
        }
    }

    return 0;
}
