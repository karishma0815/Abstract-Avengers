#ifndef PROMOTIONAL_H
#define PROMOTIONAL_H

#include"PricingStrategy.h"


class Promotional: public PricingStrategy{
    public:
    Promotional();
    ~Promotional();
    virtual double calculatePrice(int numberOfPlants,double basePrice,std::string coupon) override;
};
#endif