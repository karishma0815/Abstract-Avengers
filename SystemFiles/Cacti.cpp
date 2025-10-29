// Cacti.cpp
#include "Cacti.h"
#include "Plant.h"

Cacti::Cacti(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
                // plant = new Plant(name, false, "CACTI_" + std::to_string(rand() % 1000), 10, 1);

}

Cacti::~Cacti() {
    delete plant;
}

std::string Cacti::getPlantType() const {
    return "Cacti";
}

Plant* Cacti::getPlant() const {
    return plant;
}