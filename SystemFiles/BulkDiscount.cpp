#include"BulkDiscount.h"

BulkDiscount::BulkDiscount(){}

BulkDiscount::~BulkDiscount(){}

double BulkDiscount::calculatePrice(int numberOfPlants,double basePrice,std::string coupon){
    if (numberOfPlants>=5)
    {
        std::cout<<"Bulk discount applied (75'%'off): ";
        return basePrice*0.75;
    }
    return basePrice;
}