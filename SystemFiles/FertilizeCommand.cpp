#include "FertilizeCommand.h"
#include "Plant.h"
#include <iostream>

FertilizeCommand::FertilizeCommand(Plant *plant, const std::string &type) : plant(plant), fertilizerType(type){

}

void FertilizeCommand::execute(){
    if (plant != nullptr && plant->getIsAlive()) {
        plant->fertilize(fertilizerType);
        logAction();
    }
}

std::string FertilizeCommand::getDescription() const{
    return "Fertilize " + (plant ? plant->getName() : "Unknown plant") + " with " + fertilizerType;
}

void FertilizeCommand::logAction() const{
    std::cout<<" [LOG] FertilizeCommand executed: "<<getDescription()<<" | Plant: "<<(plant ? plant->getName() : "Unknown Plant")<<" | Fertilizer: "<<fertilizerType<<std::endl;
}
