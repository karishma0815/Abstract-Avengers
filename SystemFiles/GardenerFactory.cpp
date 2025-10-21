#include "GardenerFactory.h"
#include "Gardener.h"

Staff *GardenerFactory::createStaff(){
    return new Gardener("Gardener Name", 0, nullptr, "general");
}

std::string GardenerFactory::getRoleName() const{
    return "Gardener";
}
