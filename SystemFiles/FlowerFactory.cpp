#include "FlowerFactory.h"

FlowerFactory::FlowerFactory() : productionCounter(0) {
}

FlowerFactory::~FlowerFactory() {
}

SucculentProduct* FlowerFactory::createSucculent(std::string name, double price, int stock) {
    return nullptr;
}

TreeProduct* FlowerFactory::createTree(std::string name, double price, int stock) {
    return nullptr;
}

FlowerProduct* FlowerFactory::createFlower(std::string name, double price, int stock) {
    productionCounter++;
    std::string species;
    switch (productionCounter % 3) {
        case 0:
            species = "Rose";
            break;
        case 1:
            species = "Lavender";
            break;
        case 2:
            species = "Marigold";
            break;
        default:
            species = "Generic Flower";
    }
    
    return new Flower(name, price, species);
}

SucculentGroup* FlowerFactory::createSucculentGroup(std::string groupName) {
    return nullptr;
}

FlowerGroup* FlowerFactory::createFlowerGroup(std::string groupName) {
    return new FlowerGroup(groupName);
}

TreeGroup* FlowerFactory::createTreeGroup(std::string groupName) {
    return nullptr;
}