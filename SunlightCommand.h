#ifndef SUNLIGHTCOMMAND_H
#define SUNLIGHTCOMMAND_H

#include "Command.h"
#include "Plant.h"

class SunlightCommand : public Command {
private:
    Plant* plant;
    int exposureHours;

public:
    SunlightCommand(Plant* plant, int hours);
    ~SunlightCommand();
    
    void execute();
    void undo() ;
    bool isCommand();
};

#endif