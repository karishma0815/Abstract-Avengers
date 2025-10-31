#include"CustomerQuery.h"
#include<iostream>
#include"CustomerQueryHandler.h"
#include"Customer.h"
#include"PricingQueryHandler.h"
#include"PlantRecommendationHandler.h"
#include"JuniorStaff.h"
void testIntegratedPatternsScenario() {
    printHeader("Testing Integrated Patterns: Chain of Responsibility with Strategy");

    // Create the chain of responsibility
    CustomerQueryHandler* pricingHandler = new PricingQueryHandler();
    CustomerQueryHandler* recommendationHandler = new PlantRecommendationHandler();
    CustomerQueryHandler* juniorStaff = new JuniorStaff();

    // Set up the chain
    pricingHandler->setNext(recommendationHandler);
    recommendationHandler->setNext(juniorStaff);

    // Create a customer
    Customer* customer = new Customer("John");

    // Test pricing queries
    std::cout << "\nTesting Pricing Queries:" << std::endl;
    CustomerQuery bulkQuery(CustomerQuery::PRICING, "I want to buy 10 roses in bulk", customer);
    CustomerQuery regularQuery(CustomerQuery::PRICING, "How much is one rose?", customer);

    pricingHandler->handleQuery(bulkQuery);
    pricingHandler->handleQuery(regularQuery);

    // Test plant recommendations
    std::cout << "\nTesting Plant Recommendations:" << std::endl;
    CustomerQuery waterQuery(CustomerQuery::CARE_ADVICE, "Which plants need less water?", customer);
    CustomerQuery lightQuery(CustomerQuery::CARE_ADVICE, "What plants grow well in sunlight?", customer);
    CustomerQuery generalQuery(CustomerQuery::CARE_ADVICE, "Can you recommend some plants?", customer);

    pricingHandler->handleQuery(waterQuery);
    pricingHandler->handleQuery(lightQuery);
    pricingHandler->handleQuery(generalQuery);

    // Cleanup
    delete customer;
    delete pricingHandler;
    delete recommendationHandler;
    delete juniorStaff;
}