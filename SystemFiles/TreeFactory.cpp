#include "TreeFactory.h"
#include "Tree.h"
#include "Pine.h"
#include "Apple.h"
#include "Jacaranda.h"

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
     switch (productionCounter % 4) {
        case 0:
            return new Pine(name + " Pine", price, "Scotch Pine");
        case 1:
            return new Jacaranda(name + " Jacaranda", price, "Blue Jacaranda");
        case 2:
            return new Apple(name + " Apple", price, "Fuji Apple");
        case 3:
            return new Tree(name, price, "Lemon Tree");
        default:
            return new Tree(name, price, "Generic Tree");
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