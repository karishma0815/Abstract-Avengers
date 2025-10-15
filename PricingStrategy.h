/**
 * @file PricingStrategy.h
 * @brief Abstract Strategy interface for pricing algorithms
 */
#ifndef PRICINGSTRATEGY_H
#define PRICINGSTRATEGY_H

class PricingStrategy {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PricingStrategy() {}
    /**
     * @brief Calculates price based on the implemented strategy
     */
    virtual double calculatePrice(double basePrice) = 0;
};
#endif