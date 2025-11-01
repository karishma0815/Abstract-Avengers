#include "Cacti.h"
#include <iostream>

const double Cacti::OPTIMAL_WATER = 0.3;
const double Cacti::MAX_WATER = 1.0;
const int Cacti::OPTIMAL_SUNLIGHT = 12;
const int Cacti::MIN_SUNLIGHT = 8;
const int Cacti::OPTIMAL_PRUNE_INTENSITY = 1;
const std::string Cacti::OPTIMAL_FERTILIZER = "cactus-mix";

Cacti::Cacti(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
}

Cacti::~Cacti() {
}

std::string Cacti::getPlantType() const {
    return "Cacti";
}

void Cacti::water(double amount){
    if (isAlive) {
        if (amount > MAX_WATER) {
            std::cout << "CACTI CARE: Warning! Cacti are very drought-tolerant. Maximum is " << MAX_WATER << "L." << std::endl;
        } else if (amount == OPTIMAL_WATER) {
            std::cout << "CACTI CARE: Perfect watering amount for cacti!" << std::endl;
        }
        lastWaterLevel += amount;
        std::cout << "Watered " << name << " (Cacti) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - cacti is not alive!" << std::endl;
    }
}

void Cacti::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType != OPTIMAL_FERTILIZER) {
            std::cout << "CACTI CARE: Use cactus-specific fertilizer during growing season." << std::endl;
        } else {
            std::cout << "CACTI CARE: Perfect fertilizer for cacti!" << std::endl;
        }
        fertilized = true;
        std::cout << "Fertilized " << name << " (Cacti) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - cacti is not alive!" << std::endl;
    }
}

void Cacti::prune(int intensity){
    if (isAlive) {
        if (intensity > OPTIMAL_PRUNE_INTENSITY) {
            std::cout << "CACTI CARE: Be careful when pruning cacti! Use gloves and proper tools. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << "Pruned " << name << " (Cacti) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - cacti is not alive!" << std::endl;
    }
}

void Cacti::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << "CACTI CARE: Cacti need at least " << MIN_SUNLIGHT << " hours of sun." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << "CACTI CARE: Perfect sunlight for cacti growth!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << "Provided " << hours << " hours of " << intensity 
                  << " sunlight to " << name << " (Cacti)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - cacti is not alive!" << std::endl;
    }
}

std::string Cacti::getCareInstructions() const{
     return "CACTI CARE: Water very sparingly (" + std::to_string(OPTIMAL_WATER) + "L). Full sun (" + 
           std::to_string(OPTIMAL_SUNLIGHT) + "+ hours). Use " + OPTIMAL_FERTILIZER + " fertilizer. Minimal pruning (intensity " +
           std::to_string(OPTIMAL_PRUNE_INTENSITY) + ").";
}
