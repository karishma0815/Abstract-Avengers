#include "DeliveryStaffFactory.h"
#include "DeliveryStaff.h"

Staff *DeliveryStaffFactory::createStaff(){
    return new DeliveryStaff("Delivery Staff Name", 0, nullptr, "truck");
}

std::string DeliveryStaffFactory::getRoleName() const{
    return "Delivery Staff";
}
