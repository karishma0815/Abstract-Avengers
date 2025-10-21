#ifndef WATERCOMMAND_H
#define WATERCOMMAND_H

#include "Command.h"
#include "Plant.h"

class WaterCommand : public Command {
private:
    Plant* plant;
    int amount;

public:
    WaterCommand(Plant* plant, int amt);
    ~WaterCommand();
    
    void execute() ;
    void undo() ;
    bool isCommand() ;
};

#endif