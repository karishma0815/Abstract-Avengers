#include "ManagerFactory.h"
#include "Manager.h"

Staff *ManagerFactory::createStaff(){
    return new Manager("Manager Name", 0, nullptr, "operations");
}

std::string ManagerFactory::getRoleName() const{
    return "Manager";
}
