#include"Context.h"
/**
 * @file Context.cpp
 * @brief Implementation of the Context class for the strategy design patterns
 */

Context::Context(RecommStrategy* recommStrategy, PricingStrategy* pricingStrategy):recommStrategy(recommStrategy), pricingStrategy(pricingStrategy) {}

Context::~Context() {
    delete recommStrategy;
    delete pricingStrategy;
}   

void Context::setRecommStrategy(RecommStrategy* strategy) {
    if (recommStrategy != nullptr) {
        delete recommStrategy;
    }
    recommStrategy = strategy;
}

void Context::setPricingStrategy(PricingStrategy* strategy) {
    if (pricingStrategy != nullptr) {
        delete pricingStrategy;
    }
    pricingStrategy = strategy;
}

void Context::executeRecommStrategy() {
    if (recommStrategy != nullptr) {
        recommStrategy->recommend();
    }
}

double Context::executePricingStrategy(int numberOfPlants,double basePrice,std::string coupon) {
    if (pricingStrategy != nullptr) {
        return pricingStrategy->calculatePrice(numberOfPlants,basePrice,coupon);
    }
    return basePrice;
}

