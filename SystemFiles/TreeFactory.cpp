#include "TreeFactory.h"

TreeFactory::TreeFactory() : productionCounter(0) {
}

TreeFactory::~TreeFactory() {
}

SucculentProduct* TreeFactory::createSucculent(std::string name, double price, int stock) {
    return nullptr;
}

TreeProduct* TreeFactory::createTree(std::string name, double price, int stock) {
    productionCounter++;
    std::string species;
    switch (productionCounter % 3) {
        case 0:
            species = "Lemon Tree";
            break;
        case 1:
            species = "Jacaranda";
            break;
        case 2:
            species = "Baobab";
            break;
        default:
            species = "Generic Tree";
    }
    
    return new Tree(name, price, species);
}

FlowerProduct* TreeFactory::createFlower(std::string name, double price, int stock) {
    return nullptr;
}

SucculentGroup* TreeFactory::createSucculentGroup(std::string groupName) {
    return nullptr;
}

FlowerGroup* TreeFactory::createFlowerGroup(std::string groupName) {
    return nullptr;
}

TreeGroup* TreeFactory::createTreeGroup(std::string groupName) {
    return new TreeGroup(groupName);
}