#include <iostream>
// main_console.cpp
// 说明: 控制台入口，展示项目中各设计模式的 demo 菜单与调用流程。
// 建议: 保持简洁，将具体模式实现保留在各自头文件中，避免将演示逻辑混入实现文件。
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <limits>

#include "creational/singleton.h"
#include "creational/factory_method.h"
#include "creational/abstract_factory.h"
#include "creational/builder.h"
#include "creational/prototype.h"

#include "structural/adapter.h"
#include "structural/bridge.h"
#include "structural/composite.h"
#include "structural/decorator.h"
#include "structural/facade.h"
#include "structural/flyweight.h"
#include "structural/proxy.h"

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

struct PatternInfo {
    int id;
    std::string name;
    std::string nameEn;
    std::string category;
    std::string description;
};

std::vector<PatternInfo> getPatternList() {
    return {
        {1, "Singleton", "Singleton", "Creational", "Ensure a class has only one instance"},
        {2, "Factory Method", "Factory Method", "Creational", "Define interface for creating objects"},
        {3, "Abstract Factory", "Abstract Factory", "Creational", "Create families of related objects"},
        {4, "Builder", "Builder", "Creational", "Construct complex objects step by step"},
        {5, "Prototype", "Prototype", "Creational", "Create objects by copying prototypes"},
        
        {6, "Adapter", "Adapter", "Structural", "Convert incompatible interfaces"},
        {7, "Bridge", "Bridge", "Structural", "Separate abstraction from implementation"},
        {8, "Composite", "Composite", "Structural", "Tree structure for part-whole hierarchy"},
        {9, "Decorator", "Decorator", "Structural", "Dynamically add responsibilities"},
        {10, "Facade", "Facade", "Structural", "Unified simplified interface"},
        {11, "Flyweight", "Flyweight", "Structural", "Share fine-grained objects"},
        {12, "Proxy", "Proxy", "Structural", "Control access to objects"},
        
        {13, "Observer", "Observer", "Behavioral", "One-to-many dependency notification"},
        {14, "Template Method", "Template Method", "Behavioral", "Algorithm skeleton template"},
        {15, "Strategy", "Strategy", "Behavioral", "Encapsulate interchangeable algorithms"},
        {16, "Chain of Responsibility", "Chain of Responsibility", "Behavioral", "Request passing chain"},
        {17, "Command", "Command", "Behavioral", "Encapsulate requests as objects"},
        {18, "Iterator", "Iterator", "Behavioral", "Sequential access to collection"},
        {19, "State", "State", "Behavioral", "State changes behavior"},
        {20, "Memento", "Memento", "Behavioral", "Save and restore object state"},
        {21, "Visitor", "Visitor", "Behavioral", "Separate operations from data structure"},
        {22, "Mediator", "Mediator", "Behavioral", "Encapsulate object communication"},
        {23, "Interpreter", "Interpreter", "Behavioral", "Grammar interpretation"}
    };
}

void printMenu() {
    std::cout << "\n";
    std::cout << "============================================" << std::endl;
    std::cout << "         C++ Design Patterns Demo" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\n[Creational Patterns] (5)" << std::endl;
    std::cout << "  1. Singleton" << std::endl;
    std::cout << "  2. Factory Method" << std::endl;
    std::cout << "  3. Abstract Factory" << std::endl;
    std::cout << "  4. Builder" << std::endl;
    std::cout << "  5. Prototype" << std::endl;
    
    std::cout << "\n[Structural Patterns] (7)" << std::endl;
    std::cout << "  6. Adapter" << std::endl;
    std::cout << "  7. Bridge" << std::endl;
    std::cout << "  8. Composite" << std::endl;
    std::cout << "  9. Decorator" << std::endl;
    std::cout << " 10. Facade" << std::endl;
    std::cout << " 11. Flyweight" << std::endl;
    std::cout << " 12. Proxy" << std::endl;
    
    std::cout << "\n[Behavioral Patterns] (11)" << std::endl;
    std::cout << " 13. Observer" << std::endl;
    std::cout << " 14. Template Method" << std::endl;
    std::cout << " 15. Strategy" << std::endl;
    std::cout << " 16. Chain of Responsibility" << std::endl;
    std::cout << " 17. Command" << std::endl;
    std::cout << " 18. Iterator" << std::endl;
    std::cout << " 19. State" << std::endl;
    std::cout << " 20. Memento" << std::endl;
    std::cout << " 21. Visitor" << std::endl;
    std::cout << " 22. Mediator" << std::endl;
    std::cout << " 23. Interpreter" << std::endl;
    
    std::cout << "\n[Others]" << std::endl;
    std::cout << " 99. Run all patterns" << std::endl;
    std::cout << "  0. Exit" << std::endl;
    std::cout << "\nSelect pattern to demo (enter number): ";
}

void printPatternInfo(const PatternInfo& pattern) {
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "[" << pattern.id << "] " << pattern.name << std::endl;
    std::cout << "English: " << pattern.nameEn << std::endl;
    std::cout << "Category: " << pattern.category << std::endl;
    std::cout << "Description: " << pattern.description << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

void runPattern(int choice) {
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
        
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
    }
}

void runAllPatterns() {
    std::cout << "\n============================================" << std::endl;
    std::cout << "       Running all design patterns..." << std::endl;
    std::cout << "============================================" << std::endl;
    
    for (int i = 1; i <= 23; ++i) {
        auto patterns = getPatternList();
        auto it = std::find_if(patterns.begin(), patterns.end(),
            [i](const PatternInfo& p) { return p.id == i; });
        if (it != patterns.end()) {
            printPatternInfo(*it);
            runPattern(i);
        }
    }
    
    std::cout << "\n============================================" << std::endl;
    std::cout << "       All design patterns demo complete!" << std::endl;
    std::cout << "============================================" << std::endl;
}

int main(int argc, char** argv) {
    // 命令行支持：
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
                    std::cerr << "Invalid pattern number. Use 1-23." << std::endl;
                }
            } catch (...) {
                std::cerr << "Failed to parse pattern number." << std::endl;
            }
            return 0;
        }
    }

    // 交互模式
    std::cout << "\n";
    std::cout << "============================================" << std::endl;
    std::cout << "    Welcome to C++ Design Patterns Demo!" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\nThis project contains 23 classic GoF design patterns" << std::endl;
    std::cout << "implemented in C++20 with detailed comments\n" << std::endl;

    auto patterns = getPatternList();
    int choice = -1;

    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nPlease enter a valid number!" << std::endl;
            continue;
        }

        if (choice == 0) {
            std::cout << "\nThank you for using C++ Design Patterns Demo!" << std::endl;
            std::cout << "Goodbye!\n" << std::endl;
            break;
        }

        if (choice == 99) {
            runAllPatterns();
            continue;
        }

        if (choice >= 1 && choice <= 23) {
            auto it = std::find_if(patterns.begin(), patterns.end(),
                [choice](const PatternInfo& p) { return p.id == choice; });
            if (it != patterns.end()) {
                printPatternInfo(*it);
                runPattern(choice);
            }
        } else {
            std::cout << "\nInvalid choice, please enter a number between 0-99!" << std::endl;
        }
    }

    return 0;
}
