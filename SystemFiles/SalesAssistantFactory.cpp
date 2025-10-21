#include "SalesAssistantFactory.h"
#include "SalesAssistant.h"

Staff *SalesAssistantFactory::createStaff(){
    return new SalesAssistant("Sales Assistant Name", 0, nullptr, 0.05);
}

std::string SalesAssistantFactory::getRoleName() const{
    return "Sales Assistant";
}
