#include "WaterCommand.h"
#include "Plant.h"
#include <iostream>
#include <sstream>
#include <iomanip>

WaterCommand::WaterCommand(Plant *plant, double amount) : plant(plant), amount(amount){

}

void WaterCommand::execute(){
    if (plant != nullptr && plant->getIsAlive()) {
        plant->water(amount);
        logAction();
    }
}

std::string WaterCommand::getDescription() const{
    std::stringstream stringstream;
    stringstream<<"Water "<<(plant ? plant->getName() : "Unknown Plant")<<" with "<<std::fixed<<std::setprecision(2)<<amount<<"L";
    
    return stringstream.str();
}

void WaterCommand::logAction() const{
    std::cout<<"[LOG] WaterCommand executed: "<<getDescription()<<" | Plant: "<<(plant ? plant->getName() : "Unknown plant")<<" | Amount: "<<amount<<"L"<<std::endl;
}
