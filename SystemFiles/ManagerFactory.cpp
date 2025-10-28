#include "ManagerFactory.h"
#include "Manager.h"

Staff *ManagerFactory::createStaff(){
    static int counterForId = 3000; 
    static int counterForName = 1;
    return new Manager("Manager " + std::to_string(counterForName++), counterForId++, nullptr, "operations");
}

std::string ManagerFactory::getRoleName() const{
    return "Manager";
}
