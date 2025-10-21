#include "PlantExpert.h"
#include "CustomerQuery.h"
#include <iostream>

void PlantExpert::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout<<"Plant Expert handling: "<<query.question<<std::endl;
        std::cout<<"Providing expert plant care advice and recommendations..."<<std::endl;
    } else if(nextHandler != nullptr){
        std::cout<<"Plant Expert escalating to manager..."<<std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout<<"No manager available for: "<<query.question<<std::endl;
    }
}

bool PlantExpert::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::CARE_ADVICE;
}
