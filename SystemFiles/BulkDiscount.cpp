#include"BulkDiscount.h"

BulkDiscount::BulkDiscount(){}

BulkDiscount::~BulkDiscount(){}

double BulkDiscount::calculatePrice(int numberOfPlants,double basePrice,std::string coupon){
    if (numberOfPlants>=5)
    {
        std::cout<<"Bulk discount applied (75'%'off): ";
        double totalPrice= basePrice*numberOfPlants;
        double discount=totalPrice*0.75;
        return (totalPrice - discount);
    }
    return basePrice;
}