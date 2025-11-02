#include "Pine.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Pine::OPTIMAL_WATER = 1.0;
const double Pine::MIN_WATER = 0.5;
const double Pine::MAX_WATER = 2.0;
const int Pine::OPTIMAL_SUNLIGHT = 10;
const int Pine::MIN_SUNLIGHT = 6;
const int Pine::MAX_SUNLIGHT = 14;
const int Pine::OPTIMAL_PRUNE_INTENSITY = 2;
const int Pine::MAX_PRUNE_INTENSITY = 3;

Pine::Pine(std::string name, double price, std::string species)
    : Tree(name, price, species) {
}

Pine::~Pine() {
}

std::string Pine::getPlantType() const {
    return "Pine";
}

void Pine::water(double amount){
    if (isAlive) {
        if (amount < MIN_WATER) {
            std::cout << " PINE CARE: Pine trees need some water even if drought-tolerant! Minimum is " << MIN_WATER << "L. Optimal is " << OPTIMAL_WATER << "L." << std::endl;
            return;
        } else if (amount > MAX_WATER) {
            std::cout << " PINE CARE: Warning! " << amount << "L is too much for drought-tolerant pine. " << "Maximum is " << MAX_WATER << "L. Optimal is " << OPTIMAL_WATER << "L." << std::endl;
            return;
        }
        
        lastWaterLevel += amount;
        std::cout << " Watered " << Plant::name << " (Pine) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << Plant::name << " - pine tree is not alive!" << std::endl;
    }
}

void Pine::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType.find("high-nitrogen") != std::string::npos) {
            std::cout << " PINE CARE: Caution! Pine trees prefer low-nitrogen fertilizer." << std::endl;
        }
        fertilized = true;
        std::cout << " Fertilized " << Plant::name << " (Pine) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << Plant::name << " - pine tree is not alive!" << std::endl;
    }
}

void Pine::prune(int intensity){
    if (isAlive) {
        if (intensity > MAX_PRUNE_INTENSITY) {
            std::cout << " PINE CARE: Minimal pruning recommended! Maximum intensity is " 
                      << MAX_PRUNE_INTENSITY << ". Optimal is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        }
        std::cout << " Pruned " << Plant::name << " (Pine) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << Plant::name << " - pine tree is not alive!" << std::endl;
    }
}

void Pine::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " PINE CARE: Pine trees need full sun! Minimum " << MIN_SUNLIGHT << " hours. Optimal is " << OPTIMAL_SUNLIGHT << " hours." << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << Plant::name << " (Pine)" << std::endl;
    } else {
        std::cout << " Cannot provide sunlight to " << Plant::name << " - pine tree is not alive!" << std::endl;
    }
}

std::string Pine::getCareInstructions() const{
    std::stringstream ss;
    ss << " PINE TREE CARE: \n";
    ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L sparingly (drought-tolerant)\n";
    ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << " hours full sun daily\n";
    ss << "• Fertilizer: " << getOptimalFertilizer() << " fertilizer in spring\n";
    ss << "• Pruning: Minimal pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ") only";
    return ss.str();
}
