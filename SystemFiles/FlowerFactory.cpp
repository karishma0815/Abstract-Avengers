#include "FlowerFactory.h"
#include "Flower.h"
#include "Rose.h"
#include "Lotus.h"
#include "Protea.h"

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
    switch (productionCounter % 4) {
        case 0:
            return new Rose(name + " Rose", price, "Hybrid Tea Rose");
        case 1:
            return new Flower(name, price, "Lavender");
        case 2:
            return new Lotus(name + " Lotus", price, "Sacred Lotus");
        case 3:
            return new Protea(name + " Protea", price, "King Protea");
        default:
            return new Flower(name, price, "Generic Flower");
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