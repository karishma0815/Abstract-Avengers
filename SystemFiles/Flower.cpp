#include "Flower.h"
#include <string>

Flower::Flower(std::string name, double price, std::string species)
    : Plant(name, false, "FLOWER_" + name, 6, 3, price), // initialize Plant
      FlowerProduct(name, price),                        // initialize FlowerProduct
      species(species), name(name), price(price) {      // initialize members
}


Flower::~Flower() {
}

// Implement pure virtual functions from Plant
std::string Flower::getName() {
    return name;
}

bool Flower::isFertilized() {
    return Plant::isFertilized();
}

std::string Flower::getPlantID() {
    return Plant::getPlantID();
}

int Flower::getExposureSunlightHours() {
    return Plant::getExposureSunlightHours();
}

int Flower::getLastWaterLevel() {
    return Plant::getLastWaterLevel();
}

void Flower::setName(const std::string& n) {
    name = n;
    Plant::setName(n);
}

void Flower::setFertilized(bool fert) {
    Plant::setFertilized(fert);
}

void Flower::setPlantID(const std::string& id) {
    Plant::setPlantID(id);
}

void Flower::setExposureSunlightHours(int hours) {
    Plant::setExposureSunlightHours(hours);
}

void Flower::setLastWaterLevel(int level) {
    Plant::setLastWaterLevel(level);
}

// Flower-specific methods
std::string Flower::getPlantType() const {
    return "Flower";
}

int Flower::getCount() const {
    return 1;
}

std::string Flower::getSpecies() const {
    return species;
}

double Flower::getTotalValue() const {
    return price;
}