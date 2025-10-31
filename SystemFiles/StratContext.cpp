#include"StratContext.h"
/**
 * @file StratContext.cpp
 * @brief Implementation of the StratContext class for the strategy design patterns
 */

StratContext::StratContext(RecommStrategy* recommStrategy, PricingStrategy* pricingStrategy)
    : recommStrategy(recommStrategy), pricingStrategy(pricingStrategy) {}

StratContext::~StratContext() {
    // unique_ptr members will automatically clean up owned strategies
}

void StratContext::setRecommStrategy(RecommStrategy* strategy) {
    // take ownership of the new strategy and delete the previous one automatically
    recommStrategy.reset(strategy);
}

void StratContext::setPricingStrategy(PricingStrategy* strategy) {
    // take ownership of the new strategy and delete the previous one automatically
    pricingStrategy.reset(strategy);
}

void StratContext::executeRecommStrategy() {
    if (recommStrategy) {
        recommStrategy->recommend();
    }
}

double StratContext::executePricingStrategy(int numberOfPlants,double basePrice,std::string coupon) {
    if (pricingStrategy) {
        return pricingStrategy->calculatePrice(numberOfPlants,basePrice,coupon);
    }
    return basePrice;
}

