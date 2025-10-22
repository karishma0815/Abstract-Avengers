/**
 * @file Invoker.cpp
 * @brief Implementation of the Invoker class
 */
#include "Invoker.h"

Invoker::Invoker(CustomerCommand* cmd){
    if (cmd != nullptr) {
        this->cmd.push_back(cmd);
    }
}

Invoker::~Invoker() {
    //We do not delete the command here as it may be managed elsewhere
    cmd.clear();
}

void Invoker::execute(Plant* plant, PlantInventory* cartInven) {
    if (!cmd.empty() && cmd.back() != nullptr) {
        cmd.back()->execute(plant,cartInven);
    }
}

void Invoker::setCommand(CustomerCommand* cmd) {
    if (!this->cmd.empty()) {
        this->cmd.back() = cmd;
    } else {
        this->cmd.push_back(cmd);
    }
}

void Invoker::clearCommand() {
    this->cmd.clear();
}

void Invoker::executeALL() {
    for (CustomerCommand* cmd : this->cmd) {
        if (cmd!=nullptr) {
            std::cout<<"Executing stored command: "<<std::endl;
            cmd->execute(nullptr,nullptr);
        }
    }
}

void Invoker::storeCommand(CustomerCommand* cmd) {
    if (cmd!=nullptr) {
        this->cmd.push_back(cmd);
    }
}



