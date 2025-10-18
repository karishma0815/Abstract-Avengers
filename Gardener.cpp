#include "Gardener.h"
#include <iostream>

Gardener::Gardener() 
    : fexecuteCommand(nullptr), fundoCommand(nullptr) {}

Gardener::~Gardener() {
    for (Command* cmd : commandHistory) {
        delete cmd;
    }
    commandHistory.clear();
}

void Gardener::executeCommand(Command* cmd) {
    if (cmd != nullptr) {
        std::cout << "\n[Gardener] Executing command..." << std::endl;
        cmd->execute();
        commandHistory.push_back(cmd);
        std::cout << "[Gardener] Command executed and added to history\n" << std::endl;
    }
}

void Gardener::undoCommand() {
    if (!commandHistory.empty()) {
        std::cout << "\n[Gardener] Undoing last command..." << std::endl;
        Command* lastCommand = commandHistory.back();
        lastCommand->undo();
        commandHistory.pop_back();
        delete lastCommand;
        std::cout << "[Gardener] Command undone and removed from history\n" << std::endl;
    } else {
        std::cout << "\n[Gardener] No commands to undo!\n" << std::endl;
    }
}

std::vector<Command*> Gardener::getCommandHistory() {
    return commandHistory;
}