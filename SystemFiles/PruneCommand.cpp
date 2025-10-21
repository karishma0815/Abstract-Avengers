#include "PruneCommand.h"
#include "Plant.h"
#include <iostream>

PruneCommand::PruneCommand(Plant *plant, int intensity) : plant(plant), intensity(intensity){

}

void PruneCommand::execute(){
    if (plant != nullptr && plant->getIsAlive()) {
        plant->prune(intensity);
        logAction();
    }
}

std::string PruneCommand::getDescription() const{
    return "Prune " + (plant ? plant->getName() : "Unknown Plant") + " with intensity " + std::to_string(intensity);
}

void PruneCommand::logAction() const{
    std::cout<<"[LOG] PruneCommand executed: "<<getDescription()<<" | Plant: "<<(plant ? plant->getName() : "Unknown Plant")<<" | Intensity: "<<intensity<<std::endl;
}
