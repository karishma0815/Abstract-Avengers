#include "JuniorStaff.h"
#include "CustomerQuery.h"
#include <iostream>

void JuniorStaff::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout << "Junior Staff: ";
        if(query.type == CustomerQuery::GENERAL) {
            if(query.question.find("opening hours") != std::string::npos) {
                std::cout << " We're open Monday to Saturday, 9 AM to 6 PM, and Sunday 10 AM to 4 PM." << std::endl;
            } else if(query.question.find("location") != std::string::npos) {
                std::cout << " We're located at 123 Garden Street, right next to the city park." << std::endl;
            } else if(query.question.find("gift wrapping") != std::string::npos) {
                std::cout << " Yes, we offer free gift wrapping for all purchases over R800!" << std::endl;
            } else {
                std::cout << " I can help with that! Let me check our information..." << std::endl;
            }
        } else if(query.type == CustomerQuery::PRICING) {
            if(query.question.find("rose") != std::string::npos) {
                std::cout << " Roses start at R450 each, or R2200 for a bouquet of six." << std::endl;
            } else if(query.question.find("orchid") != std::string::npos) {
                std::cout << " Orchids range from R650 to R1500 depending on the variety." << std::endl;    
            } else if(query.question.find("student discount") != std::string::npos) {
                std::cout << " We offer 10% student discount with valid ID!" << std::endl;
            } else {
                std::cout << "Let me check the pricing for you..." << std::endl;
            }
        }
    } else if(nextHandler != nullptr){
        std::cout << " Junior Staff: \"Let me connect you with a specialist who can better assist you.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << " Junior Staff: \"I apologize, but no specialists are currently available for this type of inquiry.\"" << std::endl;
    }
}

bool JuniorStaff::canHandle(const CustomerQuery &query) const{
    if (query.type == CustomerQuery::GENERAL) {
        return query.question.find("opening hours") != std::string::npos || 
               query.question.find("location") != std::string::npos || 
               query.question.find("gift wrapping") != std::string::npos;
    } else if (query.type == CustomerQuery::PRICING) {
        return query.question.find("rose") != std::string::npos || 
               query.question.find("orchid") != std::string::npos || 
               query.question.find("discount") != std::string::npos ||
               query.question.find("bulk") != std::string::npos ||
               query.question.find("student discount") != std::string::npos;
    } 
    return false;
}
