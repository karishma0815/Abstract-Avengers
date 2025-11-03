#include "SalesExpert.h"
#include "CustomerQuery.h"
#include "Promotional.h"
#include <iostream>

void SalesExpert::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout << " Sales Expert: ";
        if(query.type == CustomerQuery::PRICING) {
            if (query.question.find("rose") != std::string::npos) {
                std::cout << " Roses start at R30 each, or R150 for a bouquet of six." << std::endl;
            } else if (query.question.find("orchid") != std::string::npos) {
                std::cout << " Orchids range from R250 to R1500 depending on the variety." << std::endl;    
            } else if(query.question.find("promotions") != std::string::npos || query.question.find("coupons") != std::string::npos) {
                Promotional promoCalculator;
                
                std::cout << " We have promotional codes available! Examples:" << std::endl;
                double orderTotal = 2000.0;
                
                double noPromoPrice = promoCalculator.calculatePrice(0, orderTotal, "INVALID");
                std::cout<<std::endl;
                std::cout << "   Without valid promo: R" << orderTotal << " → R" << noPromoPrice << std::endl;
                
                double withPromoPrice = promoCalculator.calculatePrice(0, orderTotal, "Nursery1@:)");
                std::cout<<std::endl;
                std::cout << "   With promo 'Nursery1@:)': R" << orderTotal << " → R" << withPromoPrice << std::endl;
                
                std::cout << " Valid promo codes: 'Nusery1@:)', 'Nusery1@;)' for 10% off!" << std::endl;
            } else {
                std::cout << " I can provide you with our best pricing options..." << std::endl;
            }
        }
    } else if(nextHandler != nullptr){
        std::cout << " Sales Expert: \"This requires plant care expertise. Let me transfer you.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << " Sales Expert: \"I'm unable to handle this specific inquiry at the moment.\"" << std::endl;
    }
}

bool SalesExpert::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::PRICING;
}