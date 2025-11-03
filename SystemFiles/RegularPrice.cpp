#include"RegularPrice.h"

RegularPrice::RegularPrice(){}

RegularPrice::~RegularPrice(){}

double RegularPrice::calculatePrice(int numberOfPlants,double basePrice,std::string coupon){
    std::cout<<"Regular Price applied: ";
    return numberOfPlants*basePrice;
}

