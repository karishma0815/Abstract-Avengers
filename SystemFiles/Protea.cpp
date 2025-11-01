#include "Protea.h"
#include <iostream>

const double Protea::OPTIMAL_WATER = 0.8;
const double Protea::MIN_WATER = 0.3;
const int Protea::OPTIMAL_SUNLIGHT = 10;
const int Protea::MIN_SUNLIGHT = 6;
const int Protea::OPTIMAL_PRUNE_INTENSITY = 3;
const std::string Protea::OPTIMAL_FERTILIZER = "low-phosphorus";

Protea::Protea(std::string name, double price, std::string species)
    : Flower(name, price, species) {
}

Protea::~Protea() {
}

std::string Protea::getPlantType() const {
    return "Protea";
}

void Protea::water(double amount){
    if (isAlive) {
        if (amount < MIN_WATER) {
            std::cout << "PROTEA CARE: Proteas are drought-tolerant but need some water. Minimum is " << MIN_WATER << "L." << std::endl;
        }
        lastWaterLevel += amount;
        std::cout << "Watered " << name << " (Protea) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - protea is not alive!" << std::endl;
    }
}

void Protea::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType.find("phosphorus") != std::string::npos) {
            std::cout << "PROTEA CARE: Warning! Proteas are sensitive to phosphorus." << std::endl;
        } else if (fertilizerType == OPTIMAL_FERTILIZER) {
            std::cout << "PROTEA CARE: Perfect fertilizer choice for proteas!" << std::endl;
        }
        fertilized = true;
        std::cout << "Fertilized " << name << " (Protea) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - protea is not alive!" << std::endl;
    }
}

void Protea::prune(int intensity){
    if (isAlive) {
        if (intensity > OPTIMAL_PRUNE_INTENSITY) {
            std::cout << "PROTEA CARE: Prune lightly after flowering. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << "Pruned " << name << " (Protea) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - protea is not alive!" << std::endl;
    }
}

void Protea::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << "PROTEA CARE: Proteas need at least " << MIN_SUNLIGHT << " hours of sun." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << "PROTEA CARE: Perfect sunlight for protea growth!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << "Provided " << hours << " hours of " << intensity 
                  << " sunlight to " << name << " (Protea)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - protea is not alive!" << std::endl;
    }
}

std::string Protea::getCareInstructions() const{
    return "PROTEA CARE: Water sparingly (" + std::to_string(OPTIMAL_WATER) + "L). Full sun (" + 
           std::to_string(OPTIMAL_SUNLIGHT) + "+ hours). Use " + OPTIMAL_FERTILIZER + " fertilizer. Prune lightly (intensity " +
           std::to_string(OPTIMAL_PRUNE_INTENSITY) + ").";
}
