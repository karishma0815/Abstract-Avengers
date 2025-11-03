#include "Protea.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Protea::OPTIMAL_WATER = 0.5;
const double Protea::MIN_WATER = 0.3;
const double Protea::MAX_WATER = 1.0;
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
            std::cout << " PROTEA CARE: Proteas are drought-tolerant but need some water. Minimum is " << MIN_WATER << "L." << std::endl;
            return;
        } else if (amount > MAX_WATER) {
            std::cout << " PROTEA CARE: Warning! Overwatering can cause root rot in proteas. Maximum is " << MAX_WATER << "L." << std::endl;
            return; 
        }
        
        lastWaterLevel += amount;
        std::cout << " Watered " << name << " (Protea) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - protea is not alive!" << std::endl;
    }
}

void Protea::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType.find("phosphorus") != std::string::npos) {
            std::cout << " PROTEA CARE: Warning! Proteas are sensitive to phosphorus." << std::endl;
        } else if (fertilizerType == OPTIMAL_FERTILIZER) {
            std::cout << " PROTEA CARE: Perfect fertilizer choice for proteas!" << std::endl;
        }
        fertilized = true;
        std::cout << " Fertilized " << name << " (Protea) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - protea is not alive!" << std::endl;
    }
}

void Protea::prune(int intensity){
    if (isAlive) {
        if (intensity > OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " PROTEA CARE: Prune lightly after flowering. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << " Pruned " << name << " (Protea) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - protea is not alive!" << std::endl;
    }
}

void Protea::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " PROTEA CARE: Proteas need at least " << MIN_SUNLIGHT << " hours of sun." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << " PROTEA CARE: Perfect sunlight for protea growth!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << name << " (Protea)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - protea is not alive!" << std::endl;
    }
}

std::string Protea::getCareInstructions() const{
    std::stringstream ss;
    ss << " PROTEA CARE: \n";
    ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L sparingly (drought-tolerant)\n";
    ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << "+ hours full sun daily\n";
    ss << "• Fertilizer: " << OPTIMAL_FERTILIZER << " fertilizer\n";
    ss << "• Pruning: Light pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ")";
    return ss.str();
}
