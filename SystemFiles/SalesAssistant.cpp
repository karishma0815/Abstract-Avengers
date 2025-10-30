#include "SalesAssistant.h"
#include "CustomerQuery.h"
#include <iostream>

SalesAssistant::SalesAssistant(const std::string &name, int id, InventoryMediator *med, double commission) : Staff(name, id, med), commissionRate(commission){

}

std::string SalesAssistant::getRole() const{
    return "Sales Assistant";
}

void SalesAssistant::careForPlants(){
    std::cout<<getName()<<" is assisting customers with plant purchases"<<std::endl;
}

void SalesAssistant::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout<<"Sales Assistant "<<getName()<<" handling: "<<query.question<<std::endl;
        if(query.type == CustomerQuery::PRICING){
            std::cout<<"Providing pricing information and discounts..."<<std::endl;
        } else{
            std::cout<<"Assisting with general inquiry..."<<std::endl;
        }
    } else if(nextHandler != nullptr){
        std::cout<<"Sales Assistant escalating to specialist..."<<std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout<<"No specialist available for: "<<query.question<<std::endl;
    }
}

bool SalesAssistant::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::GENERAL || query.type == CustomerQuery::PRICING;
}
