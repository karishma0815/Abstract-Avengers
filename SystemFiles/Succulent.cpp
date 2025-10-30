#include "Succulent.h"
#include <string>

Succulent::Succulent(std::string name, double price, std::string species)
    : Plant(name, false, "SUCCULENT_" + name, 5, 2, price), // initialize Plant
      SucculentProduct(name, price),                          // initialize SucculentProduct
      species(species), name(name), price(price) {            // initialize own members
}


Succulent::~Succulent() {
}

// Implement pure virtual functions from Plant
std::string Succulent::getName() {
    return name;
}

bool Succulent::isFertilized() {
    return Plant::isFertilized();
}

std::string Succulent::getPlantID() {
    return Plant::getPlantID();
}

int Succulent::getExposureSunlightHours() {
    return Plant::getExposureSunlightHours();
}

int Succulent::getLastWaterLevel() {
    return Plant::getLastWaterLevel();
}

void Succulent::setName(const std::string& n) {
    name = n;
    Plant::setName(n);
}

void Succulent::setFertilized(bool fert) {
    Plant::setFertilized(fert);
}

void Succulent::setPlantID(const std::string& id) {
    Plant::setPlantID(id);
}

void Succulent::setExposureSunlightHours(int hours) {
    Plant::setExposureSunlightHours(hours);
}

void Succulent::setLastWaterLevel(int level) {
    Plant::setLastWaterLevel(level);
}

// Succulent-specific methods
std::string Succulent::getPlantType() const {
    return "Succulent";
}

int Succulent::getCount() const {
    return 1;
}

std::string Succulent::getSpecies() const {
    return species;
}

double Succulent::getTotalValue() const {
    return price;
}