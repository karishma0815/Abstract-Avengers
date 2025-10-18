#ifndef FERTILIZECOMMAND_H
#define FERTILIZECOMMAND_H

#include "Command.h"
#include "Plant.h"
#include <string>

class FertilizeCommand : public Command {
private:
    Plant* plant;
    std::string fertilizeType;

public:
    FertilizeCommand(Plant* plant, std::string type);
    ~FertilizeCommand();
    
    void execute() override;
    void undo() override;
    bool isCommand() override;
};

#endif