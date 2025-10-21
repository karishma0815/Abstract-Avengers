#ifndef REGULARPRICE
#define REGULARPRICE

#include"PricingStrategy.h"

class RegularPrice: public PricingStrategy{
    public:
    RegularPrice();
    virtual double calculatePrice(int numberOfPlants,double basePrice,std::string coupon) override;
    ~RegularPrice();
};
#endif