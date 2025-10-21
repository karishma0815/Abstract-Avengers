#include "JuniorStaff.h"
#include "CustomerQuery.h"
#include <iostream>

void JuniorStaff::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout<<"Junior Staff handling: "<<query.question<<std::endl;
        std::cout<<"Providing basic assistance and pricing information..."<<std::endl;
    } else if(nextHandler != nullptr){
        std::cout<<"Junior Staff escalating to specialist..."<<std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout<<"No specialist available for: "<<query.question<<std::endl;
    }
}

bool JuniorStaff::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::GENERAL || query.type == CustomerQuery::PRICING;
}
