#include"StratContext.h"
/**
 * @file StratContext.cpp
 * @brief Implementation of the StratContext class for the strategy design patterns
 */

StratContext::StratContext(RecommStrategy* recommStrategy, PricingStrategy* pricingStrategy):recommStrategy(recommStrategy), pricingStrategy(pricingStrategy) {}

StratContext::~StratContext() {
    delete recommStrategy;
    delete pricingStrategy;
}   

void StratContext::setRecommStrategy(RecommStrategy* strategy) {
    if (recommStrategy != nullptr) {
        delete recommStrategy;
    }
    recommStrategy = strategy;
}

void StratContext::setPricingStrategy(PricingStrategy* strategy) {
    if (pricingStrategy != nullptr) {
        delete pricingStrategy;
    }
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

