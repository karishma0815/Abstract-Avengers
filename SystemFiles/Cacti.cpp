#include "Cacti.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Cacti::OPTIMAL_WATER = 0.1;
const double Cacti::MIN_WATER = 0.05;
const double Cacti::MAX_WATER = 0.2;
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
        if (amount < MIN_WATER) {
            std::cout << " CACTI CARE: Even cacti need some water! Minimum is " << MIN_WATER << "L." << std::endl;
            return;
        } else if (amount > MAX_WATER) {
            std::cout << " CACTI CARE: Warning! Cacti are very drought-tolerant. Maximum is " << MAX_WATER << "L." << std::endl;
            return; 
        }
        
        lastWaterLevel += amount;
        std::cout << " Watered " << name << " (Cacti) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - cacti is not alive!" << std::endl;
    }
}

void Cacti::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType != OPTIMAL_FERTILIZER) {
            std::cout << " CACTI CARE: Use cactus-specific fertilizer during growing season." << std::endl;
        } else {
            std::cout << " CACTI CARE: Perfect fertilizer for cacti!" << std::endl;
        }
        fertilized = true;
        std::cout << " Fertilized " << name << " (Cacti) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - cacti is not alive!" << std::endl;
    }
}

void Cacti::prune(int intensity){
    if (isAlive) {
        if (intensity > OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " CACTI CARE: Be careful when pruning cacti! Use gloves and proper tools. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << " Pruned " << name << " (Cacti) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - cacti is not alive!" << std::endl;
    }
}

void Cacti::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " CACTI CARE: Cacti need at least " << MIN_SUNLIGHT << " hours of sun." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << " CACTI CARE: Perfect sunlight for cacti growth!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << name << " (Cacti)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - cacti is not alive!" << std::endl;
    }
}

std::string Cacti::getCareInstructions() const{
    std::stringstream ss;
    ss << " CACTI CARE: \n";
    ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L very sparingly\n";
    ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << "+ hours full sun daily\n";
    ss << "• Fertilizer: " << OPTIMAL_FERTILIZER << " fertilizer\n";
    ss << "• Pruning: Minimal pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ")";
    return ss.str();
}
