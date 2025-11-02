#include "Staff.h"
#include <iostream>

Staff::Staff(const std::string &staffName, int staffId, InventoryMediator *med) : name(staffName), id(staffId), inventoryCoordinator(med){

}

Staff::~Staff(){
    for(size_t i=0; i<taskQueue.size();i++){
        delete taskQueue[i];
    }

    taskQueue.clear();
}

void Staff::addTask(CareCommand *task){
    if (task != nullptr) {
        std::cout<<"Task queued: "<<task->getDescription()<<std::endl;
        taskQueue.push_back(task);
    }
}

void Staff::performTasks(){
    std::cout<<"Executing "<<taskQueue.size()<<" tasks..."<<std::endl;
    
    for(size_t i=0; i<taskQueue.size(); i++){
        CareCommand* task = taskQueue[i];

        if (task != nullptr) {
            std::cout<<"Executing: "<<task->getDescription()<<std::endl;
            task->execute();
            std::cout<<std::endl;
            delete task;
        }
    }

    taskQueue.clear();
    std::cout<<"All tasks completed!"<<std::endl;
}

void Staff::clearTasks(){
    std::cout<<" Cleared "<<taskQueue.size()<<" pending tasks"<<std::endl;
    
    for(size_t i=0; i<taskQueue.size(); i++){
        delete taskQueue[i];
    }

    taskQueue.clear();
}

void Staff::setInventoryCoordinator(InventoryMediator *coordinator){
    inventoryCoordinator = coordinator;
}

void Staff::notify(const std::string &event, Plant *plant, int quantity){
    if(inventoryCoordinator != nullptr){
        inventoryCoordinator->notify(this, event, plant, quantity);
    } else {
        std::cout<<"Error: No mediator set for staff member"<<std::endl;
    }
}

std::string Staff::getName() const{
    return name;
}

int Staff::getId() const{
    return id;
}


void Staff::clearTask(int index) {
    if (index >= 0 && index < static_cast<int>(taskQueue.size())) {
        std::cout << " Clearing task: " << taskQueue[index]->getDescription() << std::endl;
        delete taskQueue[index];
        taskQueue.erase(taskQueue.begin() + index);
    } else {
        std::cout << " Invalid task index!" << std::endl;
    }
}

void Staff::listTasks() const {
    if (taskQueue.empty()) {
        std::cout << " No pending tasks." << std::endl;
        return;
    }
    
    std::cout << "Pending tasks:" << std::endl;
    for (size_t i = 0; i < taskQueue.size(); i++) {
        std::cout << " " << (i + 1) << ". " << taskQueue[i]->getDescription() << std::endl;
    }
}