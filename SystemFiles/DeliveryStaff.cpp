#include "DeliveryStaff.h"
#include <iostream>

DeliveryStaff::DeliveryStaff(const std::string &name, int id, InventoryMediator *med, const std::string &vehicle) : Staff(name, id, med), vehicleType(vehicle){

}

std::string DeliveryStaff::getRole() const{
    return "Delivery Staff (" + vehicleType + ")";
}

void DeliveryStaff::careForPlants(){
    std::cout<<getName()<<" is handling plant deliveries using "<<vehicleType<<std::endl;
}
