// Lotus.cpp
#include "Lotus.h"
#include "Plant.h"

Lotus::Lotus(std::string name, double price, std::string species)
    : Flower(name, price, species) {
        //plant = new Plant(name, false, "LOTUS_" + std::to_string(rand() % 1000), 8, 5);

}

Lotus::~Lotus() {
    delete plant;
}

std::string Lotus::getPlantType() const {
    return "Lotus";
}

Plant* Lotus::getPlant() const {
    return plant;
}