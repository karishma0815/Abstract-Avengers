// Apple.cpp
#include "Apple.h"
#include "Plant.h"

Apple::Apple(std::string name, double price, std::string species)
    : Tree(name, price, species) {
                // plant = new Plant(name, false, "APPLE_" + std::to_string(rand() % 1000), 15, 2);

}

Apple::~Apple() {
    delete plant;
}

std::string Apple::getPlantType() const{
    return "Apple Tree";
}

Plant* Apple::getPlant() const {
    return plant;
}