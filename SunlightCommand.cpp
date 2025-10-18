#include "SunlightCommand.h"
#include <iostream>

SunlightCommand::SunlightCommand(Plant* plant, int hours) 
    : plant(plant), exposureHours(hours) {}

SunlightCommand::~SunlightCommand() {}

void SunlightCommand::execute() {
    std::cout << "Exposing plant '" << plant->getName() 
              << "' to " << exposureHours << " hours of sunlight" << std::endl;

    int previousExposure = plant->getExposureSunlightHours();
    int newExposure = previousExposure + exposureHours;
    plant->setExposureSunlightHours(newExposure);
    
    std::cout << "Sunlight exposure increased from " << previousExposure 
              << " to " << newExposure << " hours" << std::endl;
}

void SunlightCommand::undo() {
    std::cout << "Undoing sunlight command for plant '" << plant->getName() << "'" << std::endl;
    
    int newExposure = plant->getExposureSunlightHours() - exposureHours;
    if (newExposure < 0) newExposure = 0;
    plant->setExposureSunlightHours(newExposure);
    
    std::cout << "Sunlight exposure restored to " << newExposure << " hours" << std::endl;
}

bool SunlightCommand::isCommand() {
    return true;
}