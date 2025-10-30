#include "Tree.h"
#include <string>


Tree::Tree(std::string name, double price, std::string species)
    : Plant(name, false, "TREE_" + name, 8, 4, price), // initialize Plant
      TreeProduct(name, price),                         // initialize TreeProduct
      species(species), name(name), price(price) {     // initialize own members
}

Tree::~Tree() {
}

// Implement pure virtual functions from Plant
std::string Tree::getName() {
    return name;
}

bool Tree::isFertilized() {
    return Plant::isFertilized();
}

std::string Tree::getPlantID() {
    return Plant::getPlantID();
}

int Tree::getExposureSunlightHours() {
    return Plant::getExposureSunlightHours();
}

int Tree::getLastWaterLevel() {
    return Plant::getLastWaterLevel();
}

void Tree::setName(const std::string& n) {
    name = n;
    Plant::setName(n);
}

void Tree::setFertilized(bool fert) {
    Plant::setFertilized(fert);
}

void Tree::setPlantID(const std::string& id) {
    Plant::setPlantID(id);
}

void Tree::setExposureSunlightHours(int hours) {
    Plant::setExposureSunlightHours(hours);
}

void Tree::setLastWaterLevel(int level) {
    Plant::setLastWaterLevel(level);
}

// Tree-specific methods
std::string Tree::getPlantType() const {
    return "Tree";
}

int Tree::getCount() const {
    return 1;
}

std::string Tree::getSpecies() const {
    return species;
}

double Tree::getTotalValue() const {
    return price;
}