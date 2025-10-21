#include "SucculentFactory.h"

SucculentFactory::SucculentFactory() : productionCounter(0) {
}

SucculentFactory::~SucculentFactory() {
}

SucculentProduct* SucculentFactory::createSucculent(std::string name, double price, int stock) {
    productionCounter++;
    // Create succulent with species based on counter for variety
    std::string species;
    switch (productionCounter % 3) {
        case 0:
            species = "Echeveria";
            break;
        case 1:
            species = "Jade Plant";
            break;
        case 2:
            species = "Aloe Vera";
            break;
        default:
            species = "Generic Succulent";
    }
    
    return new Succulent(name, price, species);
}

TreeProduct* SucculentFactory::createTree(std::string name, double price, int stock) {
    // SucculentFactory doesn't create trees
    return nullptr;
}

FlowerProduct* SucculentFactory::createFlower(std::string name, double price, int stock) {
    // SucculentFactory doesn't create flowers
    return nullptr;
}

SucculentGroup* SucculentFactory::createSucculentGroup(std::string groupName) {
    return new SucculentGroup(groupName);
}

FlowerGroup* SucculentFactory::createFlowerGroup(std::string groupName) {
    // SucculentFactory doesn't create flower groups
    return nullptr;
}

TreeGroup* SucculentFactory::createTreeGroup(std::string groupName) {
    // SucculentFactory doesn't create tree groups
    return nullptr;
}