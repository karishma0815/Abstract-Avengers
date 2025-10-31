#include "Flower.h"
#include <string>
#include <iostream>

Flower::Flower(std::string name, double price, std::string species)
    : Plant(name, false, "FLWR_" + name, 6, 3, price),
      FlowerProduct(name, price),
      species(species) {
}


Flower::~Flower() {
}

// Implement pure virtual functions from Plant
std::string Flower::getName() {
    return Plant::name;
}

bool Flower::isFertilized() {
    return Plant::fertilized;
}

std::string Flower::getPlantID() {
    return Plant::plantID;
}

int Flower::getExposureSunlightHours() {
    return Plant::exposureSunlightHours;
}

int Flower::getLastWaterLevel() {
    return static_cast<int>(Plant::lastWaterLevel);
}

void Flower::setName(const std::string& n) {
    Plant::name = n;
    FlowerProduct::name = n;
}

void Flower::setFertilized(bool fert) {
    Plant::fertilized = fert;
}

void Flower::setPlantID(const std::string& id) {
    Plant::plantID = id;
}

void Flower::setExposureSunlightHours(int hours) {
    Plant::exposureSunlightHours = hours;
}

void Flower::setLastWaterLevel(int level) {
    Plant::lastWaterLevel = static_cast<double>(level);
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
    return FlowerProduct::price;
}

void Flower::water(double amount){
    if (isAlive) {
        lastWaterLevel += amount;
        std::cout << "Watered " << Plant::name << " (Flower) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << Plant::name << " - flower is not alive!" << std::endl;
    }
}

void Flower::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        fertilized = true;
        std::cout << "Fertilized " << Plant::name << " (Flower) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << Plant::name << " - flower is not alive!" << std::endl;
    }
}

void Flower::prune(int intensity){
    if (isAlive) {
        std::cout << "Pruned " << Plant::name << " (Flower) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << Plant::name << " - flower is not alive!" << std::endl;
    }
}

void Flower::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        exposureSunlightHours += hours;
        std::cout << "Provided " << hours << " hours of " << intensity 
                  << " sunlight to " << Plant::name << " (Flower)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << Plant::name << " - flower is not alive!" << std::endl;
    }
}

std::string Flower::getCareInstructions() const{
    return "FLOWER CARE: Water regularly. Provide adequate sunlight. Fertilize during growing season.";
}
