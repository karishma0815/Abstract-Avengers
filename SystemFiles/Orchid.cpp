#include "Orchid.h"
#include <iostream>

const double Orchid::OPTIMAL_WATER = 0.8;
const double Orchid::MIN_WATER = 0.3;
const int Orchid::OPTIMAL_SUNLIGHT = 4;
const int Orchid::MAX_SUNLIGHT = 6;
const int Orchid::OPTIMAL_PRUNE_INTENSITY = 2;
const std::string Orchid::OPTIMAL_FERTILIZER = "orchid-mix";

Orchid::Orchid(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
}

Orchid::~Orchid() {
}

std::string Orchid::getPlantType() const {
    return "Orchid";
}

void Orchid::water(double amount){
    if (isAlive) {
        if (amount < MIN_WATER) {
            std::cout << "ORCHID CARE: Orchids need consistent moisture. Minimum is " << MIN_WATER << "L." << std::endl;
        } else if (amount == OPTIMAL_WATER) {
            std::cout << "ORCHID CARE: Perfect watering amount for orchids!" << std::endl;
        }
        lastWaterLevel += amount;
        std::cout << "Watered " << name << " (Orchid) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - orchid is not alive!" << std::endl;
    }
}

void Orchid::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType != OPTIMAL_FERTILIZER) {
            std::cout << "ORCHID CARE: Use orchid-specific fertilizer for best flowering." << std::endl;
        } else {
            std::cout << "ORCHID CARE: Perfect fertilizer for orchids!" << std::endl;
        }
        fertilized = true;
        std::cout << "Fertilized " << name << " (Orchid) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - orchid is not alive!" << std::endl;
    }
}

void Orchid::prune(int intensity){
    if (isAlive) {
        if (intensity > OPTIMAL_PRUNE_INTENSITY) {
            std::cout << "ORCHID CARE: Prune flower spikes after blooming gently. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << "Pruned " << name << " (Orchid) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - orchid is not alive!" << std::endl;
    }
}

void Orchid::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours > MAX_SUNLIGHT && intensity == "direct") {
            std::cout << "ORCHID CARE: Orchids prefer indirect light! Direct sun can burn leaves. Maximum direct sun is " << MAX_SUNLIGHT << " hours." << std::endl;
        } else if (hours <= OPTIMAL_SUNLIGHT && intensity == "indirect") {
            std::cout << "ORCHID CARE: Perfect light conditions for orchids!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << "Provided " << hours << " hours of " << intensity 
                  << " sunlight to " << name << " (Orchid)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - orchid is not alive!" << std::endl;
    }
}

std::string Orchid::getCareInstructions() const{
    return "ORCHID CARE: Water consistently (" + std::to_string(OPTIMAL_WATER) + "L). Indirect light (" + 
           std::to_string(OPTIMAL_SUNLIGHT) + " hours). Use " + OPTIMAL_FERTILIZER + " fertilizer. Prune gently (intensity " +
           std::to_string(OPTIMAL_PRUNE_INTENSITY) + "). Avoid direct sun.";
}
