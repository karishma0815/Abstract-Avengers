#include "DeliveryStaffFactory.h"
#include "DeliveryStaff.h"

Staff *DeliveryStaffFactory::createStaff(){
    static int idCounter = 4000;  // Different range
    static int nameCounter = 1;
    return new DeliveryStaff("Delivery Staff " + std::to_string(nameCounter++), idCounter++, nullptr, "truck");
}

std::string DeliveryStaffFactory::getRoleName() const{
    return "Delivery Staff";
}
