#include "WaterCommand.h"
#include "Plant.h"
#include <iostream>

WaterCommand::WaterCommand(Plant *plant, double amount) : plant(plant), amount(amount){

}

void WaterCommand::execute(){
    if (plant != nullptr && plant->getIsAlive()) {
        plant->water(amount);
        logAction();
    }
}

std::string WaterCommand::getDescription() const{
    return "Water " + (plant ? plant->getName() : "Unknown Plant") + " with " + std::to_string(amount) + "L";
}

void WaterCommand::logAction() const{
    std::cout<<"[LOG] WaterCommand executed: "<<getDescription()<<" | Plant: "<<(plant ? plant->getName() : "Unknown plant")<<" | Amount: "<<amount<<"L"<<std::endl;
}
