#include "SalesExpert.h"
#include "CustomerQuery.h"
#include <iostream>

void SalesExpert::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout<<"Sales Expert handling: "<<query.question<<std::endl;
        std::cout<<"Providing advanced pricing, discounts, and special arrangements..."<<std::endl;
    } else if(nextHandler != nullptr){
        std::cout<<"Sales Expert escalating query..."<<std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout<<"No further expertise available for: "<<query.question<<std::endl;
    }
}

bool SalesExpert::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::PRICING || query.type == CustomerQuery::SPECIAL_REQUEST;
}
