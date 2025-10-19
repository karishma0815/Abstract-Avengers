/**
 * @file Context.h
 * @brief Context class for Strategy design pattern 
 * Holds a reference to a Strategy object and delegates execution to it
 * This allows dynamic switching of algorithms at runtime. 
 */
#ifndef CONTEXT_H
#define CONTEXT_H

#include"RecommStrategy.h"
#include"PricingStrategy.h"
#include<string>
#include<vector>

class Context{

    public:
    /**
     * @brief Constructs a Context with given strategies
     * @param recommStrategy Pointer to a RecommStrategy object
     * @param pricingStrategy Pointer to a PricingStrategy object
     */
    Context(RecommStrategy* recommStrategy, PricingStrategy* pricingStrategy);
    ~Context();
    /**
     * @brief Sets a new recommendation strategy
     * @param strategy Pointer to the new RecommStrategy object
     */
    void setRecommStrategy(RecommStrategy* strategy);
    /**
     * @brief Sets a new pricing strategy
     * @param strategy Pointer to the new PricingStrategy object
     */
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
    RecommStrategy* recommStrategy;
    PricingStrategy* pricingStrategy;


};
#endif