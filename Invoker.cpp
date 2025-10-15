/**
 * @file Invoker.cpp
 * @brief Implementation of the Invoker class
 */
#include "Invoker.h"

Invoker::Invoker(Command* command){
}

Invoker::~Invoker() {
    //We do not delete the command here as it may be managed elsewhere
    command.clear();
}

void Invoker::execute(State& state) {
    if (!command.empty() && command.back() != nullptr) {
        command.back()->execute();
        state.handle(); // Assuming State has a handle method to manage state transitions
    }
}

void Invoker::setCommand(Command* command) {
    if (!this->command.empty()) {
        this->command.back() = command;
    } else {
        this->command.push_back(command);
    }
}

void Invoker::clearCommand() {
    command.clear();
}

void Invoker::executeALL() {
    for (Command* cmd : command) {
        if (cmd!=nullptr) {
            cmd->execute();
        }
    }
}

void Invoker::storeCommand(Command* command) {
    if (command!=nullptr) {
        this->command.push_back(command);
    }
}



