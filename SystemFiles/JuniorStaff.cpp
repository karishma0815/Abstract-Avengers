#include "JuniorStaff.h"
#include "CustomerQuery.h"
#include "BulkDiscount.h"
#include <iostream>
#include <string>

void JuniorStaff::handleQuery(const CustomerQuery &query) {
    if (canHandle(query)) {
        std::cout << " Junior Staff: ";
        if (query.type == CustomerQuery::GENERAL) {
            if (query.question.find("opening hours") != std::string::npos) {
                std::cout << " We're open Monday to Saturday, 9 AM to 6 PM, and Sunday 10 AM to 4 PM." << std::endl;
            } else if (query.question.find("location") != std::string::npos) {
                std::cout << " We're located at 123 Garden Street." << std::endl;
            } else if (query.question.find("gift wrapping") != std::string::npos) {
                std::cout << " Yes, we offer free gift wrapping for all purchases (for free)!" << std::endl;
            } else {
                std::cout << " I can help with that! Let me check our information..." << std::endl;
            }
        } else if (query.type == CustomerQuery::PRICING) {
            if (query.question.find("student discount") != std::string::npos) {
                std::cout << " Will be coming soon!!!" << std::endl;
            } else if (query.question.find("bulk") != std::string::npos || query.question.find("discount") != std::string::npos) {
                
                BulkDiscount discountCalculator;
                
                std::cout << " We offer bulk discounts for 10+ plants! Examples:" << std::endl;
                
                double smallOrderPrice = discountCalculator.calculatePrice(5, 2500.0, "");
                std::cout << "   5 plants: R2500 → R" << smallOrderPrice << " (no discount)" << std::endl;
                
                double largeOrderPrice = discountCalculator.calculatePrice(15, 7500.0, "");
                std::cout << "   15 plants: R7500 → R" << largeOrderPrice << " (10% discount)" << std::endl;
                
                std::cout << " Get 10% off when you buy 10 or more plants!" << std::endl;
            } else {
                std::cout << " Let me check the pricing for you..." << std::endl;
            }
        }
    } else if (nextHandler != nullptr) {
        std::cout << " Junior Staff: \"Let me connect you with a specialist who can better assist you.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else {
        std::cout << " Junior Staff: \"I apologize, but no specialists are currently available for this type of inquiry.\"" << std::endl;
    }
}

bool JuniorStaff::canHandle(const CustomerQuery &query) const {
    if (query.type == CustomerQuery::GENERAL) {
        return query.question.find("opening hours") != std::string::npos || 
               query.question.find("location") != std::string::npos || 
               query.question.find("gift wrapping") != std::string::npos;
    } else if (query.type == CustomerQuery::PRICING) {
        return query.question.find("discount") != std::string::npos ||
               query.question.find("bulk") != std::string::npos ||
               query.question.find("student discount") != std::string::npos;
    } 
    return false;
}