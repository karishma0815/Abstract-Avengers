#ifndef BULKDISCOUNT_H
#define BULKDISCOUNT_H

#include"PricingStrategy.h"

class BulkDiscount: public PricingStrategy{
    public:
    BulkDiscount();
    ~BulkDiscount();
    virtual double calculatePrice(int numberOfPlants,double basePrice,std::string coupon) override;
};
#endif