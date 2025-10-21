#include "FertilizeCommand.h"
#include <iostream>

FertilizeCommand::FertilizeCommand(Plant* plant, std::string type) 
    : plant(plant), fertilizeType(type) {}

FertilizeCommand::~FertilizeCommand() {}

void FertilizeCommand::execute() {
    std::cout << "Fertilizing plant '" << plant->getName() 
              << "' with " << fertilizeType << " fertilizer" << std::endl;
    
    plant->setFertilized(true);
    
    std::cout << "Plant has been fertilized with " << fertilizeType << std::endl;
}

void FertilizeCommand::undo() {
    std::cout << "Undoing fertilize command for plant '" << plant->getName() << "'" << std::endl;
   
    plant->setFertilized(false);
    
    std::cout << "Fertilizer removed from plant" << std::endl;
}

bool FertilizeCommand::isCommand() {
    return true;
}