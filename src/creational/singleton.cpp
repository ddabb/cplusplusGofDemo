#include "creational/singleton.h"
#include <iostream>

namespace design_patterns::creational {

void singleton_demo() {
    std::cout << "\n========== Singleton Pattern Demo ==========" << std::endl;

    Singleton& instance1 = Singleton::getInstance();
    instance1.display();

    Singleton& instance2 = Singleton::getInstance();
    instance2.display();

    std::cout << "\n[Singleton] Both instances point to the same address: " 
              << (&instance1 == &instance2 ? "YES" : "NO") << std::endl;

    instance1.setMessage("Modified message from instance1");
    instance2.display();

    std::cout << "=============================================\n" << std::endl;
}

}

