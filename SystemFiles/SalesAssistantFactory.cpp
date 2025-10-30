#include "SalesAssistantFactory.h"
#include "SalesAssistant.h"

Staff *SalesAssistantFactory::createStaff(){
    static int counterForId = 2000;
    static int counterForName = 1;
    return new SalesAssistant("Sales Assistant " + std::to_string(counterForName++), counterForId++, nullptr, 0.05);
}

std::string SalesAssistantFactory::getRoleName() const{
    return "Sales Assistant";
}
