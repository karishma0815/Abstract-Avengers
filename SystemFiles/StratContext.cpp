#include"StratContext.h"
/**
 * @file StratContext.cpp
 * @brief Implementation of the StratContext class for the strategy design patterns
 */

StratContext::StratContext(RecommStrategy* recommStrategy, PricingStrategy* pricingStrategy):recommStrategy(recommStrategy), pricingStrategy(pricingStrategy) {}

StratContext::~StratContext() {
    // Don't delete the strategy pointers - they're owned by unique_ptr
}   

void StratContext::setRecommStrategy(RecommStrategy* strategy) {
    // Just update the pointer without deleting
    recommStrategy = strategy;
}

void StratContext::setPricingStrategy(PricingStrategy* strategy) {
    // Just update the pointer without deleting
    pricingStrategy = strategy;
}

void StratContext::executeRecommStrategy() {
    if (recommStrategy != nullptr) {
        recommStrategy->recommend();
    }
}

double StratContext::executePricingStrategy(int numberOfPlants,double basePrice,std::string coupon) {
    if (pricingStrategy != nullptr) {
        return pricingStrategy->calculatePrice(numberOfPlants,basePrice,coupon);
    }
    return basePrice;
}

