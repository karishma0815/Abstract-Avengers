#ifndef GARDENER_H
#define GARDENER_H

#include "Command.h"
#include <vector>

class Gardener {
private:
    std::vector<Command*> commandHistory;
    Command* fexecuteCommand;
    Command* fundoCommand;

public:

    Gardener();
    ~Gardener();
    void executeCommand(Command* cmd);
    void undoCommand();
    std::vector<Command*> getCommandHistory();
};

#endif 