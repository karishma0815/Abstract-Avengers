#include "SunlightCommand.h"
#include "Plant.h"
#include <iostream>

SunlightCommand::SunlightCommand(Plant *plant, int hours, const std::string &intensity) : plant(plant), hours(hours), intensity(intensity){

}

void SunlightCommand::execute(){
    if (plant != nullptr && plant->getIsAlive()) {
        plant->provideSunlight(hours, intensity);
        logAction();
    }
}

std::string SunlightCommand::getDescription() const{
    return "Provide " + std::to_string(hours) + " hours of " + intensity + " sunlight to " + (plant ? plant->getName() : "Unknown plant");
}

void SunlightCommand::logAction() const{
    std::cout<<"[LOG] SunlightCommand executed: "<<getDescription()<<" | Plant: " << (plant ? plant->getName() : "unknown")<<" | Hours: " << hours<<" | Intensity: " << intensity << std::endl;
}
