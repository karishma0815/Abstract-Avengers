#include "SalesExpert.h"
#include "CustomerQuery.h"
#include <iostream>

void SalesExpert::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout << "Sales Expert: ";
        if(query.type == CustomerQuery::PRICING) {
            if(query.question.find("bulk discount") != std::string::npos || query.question.find("100 plants") != std::string::npos) {
                std::cout << "For orders of 100 plants or more, we offer a 15% bulk discount plus free delivery!" << std::endl;
            } else if(query.question.find("corporate") != std::string::npos) {
                std::cout << "We have special corporate rates starting at 20% off for business accounts." << std::endl;
            } else {
                std::cout << "I can provide you with our best pricing options..." << std::endl;
            }
        } else if(query.type == CustomerQuery::SPECIAL_REQUEST) {
            if(query.question.find("deliver on Sunday") != std::string::npos) {
                std::cout << "We can arrange Sunday delivery for an additional $25 service fee." << std::endl;
            } else if(query.question.find("install") != std::string::npos) {
                std::cout << "Yes, we offer professional installation services starting at $75 per hour." << std::endl;
            } else {
                std::cout << "I can help arrange that special request for you..." << std::endl;
            }
        }
    } else if(nextHandler != nullptr){
        std::cout << "Sales Expert: \"This requires plant care expertise. Let me transfer you.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << "Sales Expert: \"I'm unable to handle this specific inquiry at the moment.\"" << std::endl;
    }
}

bool SalesExpert::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::PRICING;
}
