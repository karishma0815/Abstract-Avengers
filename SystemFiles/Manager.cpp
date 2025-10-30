#include "Manager.h"
#include "CustomerQuery.h"
#include <iostream>

Manager::Manager(const std::string &name, int id, InventoryMediator *med, const std::string &dept) : Staff(name, id, med), department(dept){

}

std::string Manager::getRole() const{
    return "Manager (" + department + ")";
}

void Manager::careForPlants(){
    std::cout<<getName()<<" is overseeing nursery operations in "<<department<<std::endl;
}

void Manager::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout << "Manager " << getName() << ": ";
        if(query.type == CustomerQuery::COMPLAINT) {
            std::cout << "I'll personally ensure this is resolved to your satisfaction." << std::endl;
        } else if(query.type == CustomerQuery::SPECIAL_REQUEST) {
            std::cout << "I can authorize that special arrangement for you..." << std::endl;
        }
    } else if(nextHandler != nullptr){
        std::cout << "Manager " << getName() << ": \"This is beyond my authority. Let me check with higher management.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << "Manager " << getName() << ": \"I'm unable to escalate this further, but I'll make note of your concern.\"" << std::endl;
    }
}

bool Manager::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::COMPLAINT || query.type == CustomerQuery::SPECIAL_REQUEST;
}
