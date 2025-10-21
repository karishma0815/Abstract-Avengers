#include "Manager.h"
#include "CustomerQuery.h"
#include <iostream>

Manager::Manager(const std::string &name, int id, InventoryMediator *med, const std::string &dept) : Staff(name, id, med), department(dept){

}

std::string Manager::getRole() const{
    return "Manager (" + department + ")"
}

void Manager::careForPlants(){
    std::cout<<getName()<<" is overseeing nursery operations in "<<department<<std::endl;
}

void Manager::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout<<"Manager "<<getName()<<" handling: "<<query.question<<std::endl;
        if(query.type == CustomerQuery::COMPLAINT){
            std::cout<<"Resolving customer complaint with authority..."<<std::endl;
        } else{
            std::cout<<"Approving special customer request..."<<std::endl;
        }
    } else if(nextHandler != nullptr){
        std::cout<<"Manager escalating query..."<<std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout<<"No further escalation possible for: "<<query.question<<std::endl;
    }
}

bool Manager::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::COMPLAINT || query.type == CustomerQuery::SPECIAL_REQUEST;
}
