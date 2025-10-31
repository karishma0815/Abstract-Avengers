#include "Succulent.h"
#include <string>
#include <iostream>

Succulent::Succulent(std::string name, double price, std::string species)
    : Plant(name, false, "SUCC_" + name, 8, 1, price),
      SucculentProduct(name, price),
      species(species) {
}


Succulent::~Succulent() {
}

// Implement pure virtual functions from Plant
std::string Succulent::getName() {
    return Plant::name;
}

bool Succulent::isFertilized() {
    return Plant::fertilized;
}

std::string Succulent::getPlantID() {
    return Plant::plantID;
}

int Succulent::getExposureSunlightHours() {
    return Plant::exposureSunlightHours;
}

int Succulent::getLastWaterLevel() {
    return static_cast<int>(Plant::lastWaterLevel);
}

void Succulent::setName(const std::string& n) {
    Plant::name = n;
    SucculentProduct::name = n;
}

void Succulent::setFertilized(bool fert) {
    Plant::fertilized = fert;
}

void Succulent::setPlantID(const std::string& id) {
    Plant::plantID = id;
}

void Succulent::setExposureSunlightHours(int hours) {
    Plant::exposureSunlightHours = hours;
}

void Succulent::setLastWaterLevel(int level) {
    Plant::lastWaterLevel = static_cast<double>(level);
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
    return SucculentProduct::price;
}

void Succulent::water(double amount){
    if (isAlive) {
        lastWaterLevel += amount;
        std::cout << "Watered " << Plant::name << " (Generic Succulent) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << Plant::name << " - succulent is not alive!" << std::endl;
    }
}

void Succulent::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        fertilized = true;
        std::cout << "Fertilized " << Plant::name << " (Generic Succulent) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << Plant::name << " - succulent is not alive!" << std::endl;
    }
}

void Succulent::prune(int intensity){
    if (isAlive) {
        std::cout << "Pruned " << Plant::name << " (Generic Succulent) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << Plant::name << " - succulent is not alive!" << std::endl;
    }
}

void Succulent::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        exposureSunlightHours += hours;
        std::cout << "Provided " << hours << " hours of " << intensity 
                  << " sunlight to " << Plant::name << " (Generic Succulent)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << Plant::name << " - succulent is not alive!" << std::endl;
    }
}

std::string Succulent::getCareInstructions() const{
    return "GENERIC SUCCULENT CARE: Water sparingly. Provide bright light. Well-draining soil.";
}
