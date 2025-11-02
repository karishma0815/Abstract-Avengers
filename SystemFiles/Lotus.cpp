#include "Lotus.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Lotus::OPTIMAL_WATER = 15.0;
const double Lotus::MIN_WATER = 10.0;
const double Lotus::MAX_WATER = 25.0;
const int Lotus::OPTIMAL_SUNLIGHT = 12;
const int Lotus::MIN_SUNLIGHT = 8;
const int Lotus::OPTIMAL_PRUNE_INTENSITY = 2;
const std::string Lotus::OPTIMAL_FERTILIZER = "aquatic-plant";

Lotus::Lotus(std::string name, double price, std::string species)
    : Flower(name, price, species) {
}

Lotus::~Lotus() {
}

std::string Lotus::getPlantType() const {
    return "Lotus";
}

void Lotus::water(double amount){
    if (isAlive) {
        if (amount < MIN_WATER) {
            std::cout << " LOTUS CARE: Lotuses are aquatic plants! They need at least " << MIN_WATER << "L of water." << std::endl;
            return;
        } else if (amount > MAX_WATER) {
            std::cout << " LOTUS CARE: Warning! " << amount << "L may be excessive even for aquatic lotus. Maximum recommended is " << MAX_WATER << "L." << std::endl;
            return;
        }
        
        lastWaterLevel += amount;
        std::cout << " Watered " << name << " (Lotus) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - lotus is not alive!" << std::endl;
    }
}

void Lotus::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType != OPTIMAL_FERTILIZER) {
            std::cout << " LOTUS CARE: Use aquatic plant fertilizer for best results." << std::endl;
        } else {
            std::cout << " LOTUS CARE: Perfect fertilizer for lotus plants!" << std::endl;
        }
        fertilized = true;
        std::cout << " Fertilized " << name << " (Lotus) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - lotus is not alive!" << std::endl;
    }
}

void Lotus::prune(int intensity){
    if (isAlive) {
        if (intensity > OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " LOTUS CARE: Remove yellow leaves gently. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << " Pruned " << name << " (Lotus) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - lotus is not alive!" << std::endl;
    }
}

void Lotus::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " LOTUS CARE: Lotuses need at least " << MIN_SUNLIGHT << " hours of sun daily." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << " LOTUS CARE: Perfect sunlight for lotus growth and flowering!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << name << " (Lotus)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - lotus is not alive!" << std::endl;
    }
}

std::string Lotus::getCareInstructions() const{
    std::stringstream ss;
    ss << " LOTUS CARE: \n";
    ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L+ (aquatic plant)\n";
    ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << " hours full sun daily\n";
    ss << "• Fertilizer: " << OPTIMAL_FERTILIZER << " fertilizer\n";
    ss << "• Pruning: Gentle pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ")";
    return ss.str();
}
