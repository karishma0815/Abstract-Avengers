// Orchid.cpp
#include "Orchid.h"
#include "Plant.h"

Orchid::Orchid(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
        // plant = new Plant(name, false, "ORCHID_" + std::to_string(rand() % 1000), 7, 4);

}

Orchid::~Orchid() {
    delete plant;
}

std::string Orchid::getPlantType() const {
    return "Orchid";
}


Plant* Orchid::getPlant() const {
    return plant;
}