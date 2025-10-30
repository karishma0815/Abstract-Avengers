#include "Plant.h"
#include <iostream>
#include <iomanip>

Plant::Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel,int price)
    : name(name), fertilized(fert), plantID(id), 
      exposureSunlightHours(sunHours), lastWaterLevel(waterLevel),price(price), isAlive(true) {}


std::string Plant::getCareInstructions() const {
    // If explicit care instructions were set, return them (preferred).
    if (!careInstruc.empty()) {
        return careInstruc;
    }

    // Otherwise build a default care description from internal fields.
    std::string careInstruc2 = "Water level be maintained at " + std::to_string(lastWaterLevel) +
        " and sunlight exposure should be around " + std::to_string(exposureSunlightHours) + " hours daily.";
    if (fertilized) {
        careInstruc2 += " This plant is fertilized.";
    } else {
        careInstruc2 += " This plant is not fertilized.";
    }
    return careInstruc2;
}

void Plant::setCareInstructions(const std::string& instructions) {
    // Assuming careInstruc is a member variable of Plant
    careInstruc = instructions;
}

double Plant::getPrice() const {
    return price;
}

void Plant::setPrice(double price) {
    this->price = price;
}

bool Plant::getIsAlive() const{
    return isAlive;
}

std::string Plant::getName() const{
    return name;
}

void Plant::water(double amount){
    if (isAlive) {
        lastWaterLevel += amount;
        std::cout << "Watered " << name << " with " <<std::fixed << std::setprecision(2)<< amount << "L. New water level: " << lastWaterLevel << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - plant is not alive!" << std::endl;
    }
}

void Plant::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        fertilized = true;
        std::cout << "Fertilized " << name << " with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - plant is not alive!" << std::endl;
    }
}

void Plant::prune(int intensity){
    if (isAlive) {
        std::cout << "Pruned " << name << " with intensity " << intensity << std::endl;
        if (intensity > 5) {
            std::cout << "Warning: High pruning intensity might stress the plant!" << std::endl;
        }
    } else {
        std::cout << "Cannot prune " << name << " - plant is not alive!" << std::endl;
    }
}

void Plant::provideSunlight(int hours, const std::string& intensity){
    if (isAlive) {
        if (hours > 0) {
            exposureSunlightHours += hours;
            std::cout << "Provided " << hours << " hours of " << intensity 
                      << " sunlight to " << name << ". Total sunlight hours: " 
                      << exposureSunlightHours << std::endl;
            
            if (exposureSunlightHours > 12) {
                std::cout << "Warning: " << name << " might be getting too much sunlight!" << std::endl;
            } else if (exposureSunlightHours < 4) {
                std::cout << "Note: " << name << " might need more sunlight." << std::endl;
            }
            
            if (intensity == "intense" && hours > 4) {
                std::cout << "Caution: Intense sunlight for extended periods!" << std::endl;
            }
        } else {
            std::cout << "No sunlight provided to " << name 
                      << " (0 hours requested). Current sunlight hours remain at: " 
                      << exposureSunlightHours << std::endl;
        }
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - plant is not alive!" << std::endl;
    }
}
