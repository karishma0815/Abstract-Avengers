#include "Tree.h"
#include <string>
#include <iostream>

Tree::Tree(std::string name, double price, std::string species)
    : Plant(name, false, "TREE_" + name, 8, 4, price), 
      TreeProduct(name, price),                         
      species(species){
}

Tree::~Tree() {
}

// Implement pure virtual functions from Plant
std::string Tree::getName() {
    return Plant::name;
}

bool Tree::isFertilized() {
    return Plant::fertilized;;
}

std::string Tree::getPlantID() {
    return Plant::plantID;
}

int Tree::getExposureSunlightHours() {
    return Plant::exposureSunlightHours;
}

int Tree::getLastWaterLevel() {
    return static_cast<int>(Plant::lastWaterLevel);
}

void Tree::setName(const std::string& n) {
    Plant::name = n;
    TreeProduct::name = n;
}

void Tree::setFertilized(bool fert) {
    Plant::fertilized = fert;
}

void Tree::setPlantID(const std::string& id) {
    Plant::plantID = id;
}

void Tree::setExposureSunlightHours(int hours) {
    Plant::exposureSunlightHours = hours;
}

void Tree::setLastWaterLevel(int level) {
    Plant::lastWaterLevel = static_cast<double>(level);
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
    return TreeProduct::price;
}

void Tree::water(double amount){
    if (isAlive) {
        lastWaterLevel += amount;
        std::cout << "Watered " << Plant::name << " (Generic Tree) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << Plant::name << " - tree is not alive!" << std::endl;  // ✅ Add this
    }
}

void Tree::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        fertilized = true;
        std::cout << "Fertilized " << Plant::name << " (Generic Tree) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << Plant::name << " - tree is not alive!" << std::endl;  // ✅ Add this
    }
}

void Tree::prune(int intensity){
    if (isAlive) {
        std::cout << "Pruned " << Plant::name << " (Generic Tree) with intensity " << intensity << std::endl;
        if (intensity > 5) {
            std::cout << "Warning: High pruning intensity might stress the tree!" << std::endl;
        }
    } else {
        std::cout << "Cannot prune " << Plant::name << " - tree is not alive!" << std::endl;
    }
}

void Tree::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours > 0) {
            exposureSunlightHours += hours;
            std::cout << "Provided " << hours << " hours of " << intensity 
                      << " sunlight to " << Plant::name << " (Generic Tree). Total sunlight hours: " 
                      << exposureSunlightHours << std::endl;
            
            if (exposureSunlightHours > 12) {
                std::cout << "Warning: " << Plant::name << " might be getting too much sunlight!" << std::endl;
            } else if (exposureSunlightHours < 4) {
                std::cout << "Note: " << Plant::name << " might need more sunlight." << std::endl;
            }
            
            if (intensity == "intense" && hours > 4) {
                std::cout << "Caution: Intense sunlight for extended periods!" << std::endl;
            }
        } else {
            std::cout << "No sunlight provided to " << Plant::name 
                      << " (0 hours requested). Current sunlight hours remain at: " 
                      << exposureSunlightHours << std::endl;
        }
    } else {
        std::cout << "Cannot provide sunlight to " << Plant::name << " - tree is not alive!" << std::endl;
    }
}

std::string Tree::getCareInstructions() const{
    std::string instructions = "GENERIC TREE CARE: ";
    instructions += "Water regularly. Provide 6-8 hours of sunlight daily. ";
    instructions += "Fertilize in spring with balanced fertilizer. ";
    instructions += "Prune as needed to maintain shape and remove dead branches.";
    return instructions;
}
