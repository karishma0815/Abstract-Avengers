#include "GardenerFactory.h"
#include "Gardener.h"

Staff *GardenerFactory::createStaff(){
    static int counterForId = 1000;
    static int counterForName = 1;
    return new Gardener("Gardener " + std::to_string(counterForName++), counterForId++, nullptr, "general");
}

std::string GardenerFactory::getRoleName() const{
    return "Gardener";
}
