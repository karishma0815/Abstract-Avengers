/**
 * @file PricingStrategy.h
 * @brief Abstract Strategy interface for pricing algorithms
 */
#ifndef PRICINGSTRATEGY_H
#define PRICINGSTRATEGY_H

#include<string>
#include<iostream>

class PricingStrategy {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PricingStrategy();
    /**
     * @brief Calculates price based on the implemented strategy
     */
    virtual double calculatePrice(int numberOfPlants,double basePrice,std::string coupon) = 0;
};
#endif