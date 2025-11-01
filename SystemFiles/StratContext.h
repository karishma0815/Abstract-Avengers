/**
 * @file StratContext.h
 * @brief StratContext class for Strategy design pattern 
 * Holds a reference to a Strategy object and delegates execution to it
 * This allows dynamic switching of algorithms at runtime. 
 */
#ifndef STRATCONTEXT_H
#define STRATCONTEXT_H

#include"RecommStrategy.h"
#include"PricingStrategy.h"
#include<string>
#include<vector>
#include <memory>

class StratContext{

    public:
    /**
     * @brief Constructs a StratContext with given strategies
     * @param recommStrategy Pointer to a RecommStrategy object
     * @param pricingStrategy Pointer to a PricingStrategy object
     */
    StratContext(RecommStrategy* recommStrategy, PricingStrategy* pricingStrategy);
    ~StratContext();
    /**
     * @brief Sets a new recommendation strategy
     * @param strategy Pointer to the new RecommStrategy object
     */
    // Takes ownership of the passed pointer (will delete previous strategy)
    void setRecommStrategy(RecommStrategy* strategy);
    /**
     * @brief Sets a new pricing strategy
     * @param strategy Pointer to the new PricingStrategy object
     */
    // Takes ownership of the passed pointer (will delete previous strategy)
    void setPricingStrategy(PricingStrategy* strategy);
    /**
     * @brief Executes the recommendation strategy
     */
    void executeRecommStrategy();
    /**
     * @brief Executes the pricing strategy
     * @param basePrice The base price to calculate from
     * @return The calculated price based on the strategy
     */
    double executePricingStrategy(int numberOfPlants,double basePrice,std::string coupon);
   
    private:
    std::unique_ptr<RecommStrategy> recommStrategy;
    std::unique_ptr<PricingStrategy> pricingStrategy;


};
#endif