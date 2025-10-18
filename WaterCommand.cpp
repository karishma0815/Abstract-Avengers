#include "WaterCommand.h"
#include <iostream>

WaterCommand::WaterCommand(Plant* plant, int amt) 
    : plant(plant), amount(amt) {}

WaterCommand::~WaterCommand() {}

void WaterCommand::execute() {
    std::cout << "Watering plant '" << plant->getName() 
              << "' with " << amount << " units of water" << std::endl;

    int previousLevel = plant->getLastWaterLevel();
    int newLevel = previousLevel + amount;
    plant->setLastWaterLevel(newLevel);
    
    std::cout << "Water level increased from " << previousLevel 
              << " to " << newLevel << std::endl;
}

void WaterCommand::undo() {
    std::cout << "Undoing water command for plant '" << plant->getName() << "'" << std::endl;
    
    int newLevel = plant->getLastWaterLevel() - amount;
    if (newLevel < 0) newLevel = 0;
    plant->setLastWaterLevel(newLevel);
    
    std::cout << "Water level restored to " << newLevel << std::endl;
}

bool WaterCommand::isCommand() {
    return true;
}