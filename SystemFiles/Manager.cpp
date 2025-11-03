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
        std::cout << " Manager " << getName() << ": ";
        if(query.type == CustomerQuery::COMPLAINT) {
            if(query.question.find("dont have") != std::string::npos ||
               query.question.find("don't have") != std::string::npos ||
               query.question.find("do not have") != std::string::npos ||
               query.question.find("why don't you have") != std::string::npos ||
               query.question.find("specific plant") != std::string::npos ||
               query.question.find("out of stock") != std::string::npos ||
               query.question.find("not available") != std::string::npos) {
                std::cout << " I apologize but we only have a limited range of plants" << std::endl;
            } else {
                std::cout << " I apologize but we only have a limited range of plants" << std::endl;
            }
        } else if(query.type == CustomerQuery::SPECIAL_REQUEST) {
            if(query.question.find("after hours") != std::string::npos ||
               query.question.find("deliver after hours") != std::string::npos) {
                std::cout << " I can not authorize that special arrangement for you as we have no delivery staff available after hours" << std::endl;
            } else {
                std::cout << " I can not authorize that special arrangement for you as we have no delivery staff available after hours" << std::endl;
            }
        }
    } else if(nextHandler != nullptr){
        std::cout << " Manager " << getName() << ": \"This is beyond my authority. Let me check with higher management.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << " Manager " << getName() << ": \"I apologize but i can not authorize that.\"" << std::endl;
    }
}

bool Manager::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::COMPLAINT || query.type == CustomerQuery::SPECIAL_REQUEST;
}
