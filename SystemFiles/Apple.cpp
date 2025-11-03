#include "Apple.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Apple::OPTIMAL_WATER = 2.0;
const double Apple::MIN_WATER = 1.5;
const double Apple::MAX_WATER = 4.0;
const int Apple::OPTIMAL_SUNLIGHT = 8;
const int Apple::MIN_SUNLIGHT = 6;
const int Apple::MAX_SUNLIGHT = 12;
const int Apple::OPTIMAL_PRUNE_INTENSITY = 5;
const int Apple::MAX_PRUNE_INTENSITY = 7;

Apple::Apple(std::string name, double price, std::string species)
    : Tree(name, price, species) {
}

Apple::~Apple() {
}

std::string Apple::getPlantType() const {
    return "Apple";
}

void Apple::water(double amount){
    if (isAlive) {
        if (amount < MIN_WATER) {
            std::cout << " APPLE CARE: Apple trees need regular watering! Minimum is " << MIN_WATER << "L. Optimal is " << OPTIMAL_WATER << "L." << std::endl;
            return;
        } else if (amount > MAX_WATER) {
            std::cout << " APPLE CARE: Too much water can cause root rot! Maximum is " << MAX_WATER << "L. Optimal is " << OPTIMAL_WATER << "L." << std::endl;
            return;
        }
    
    lastWaterLevel += amount;
    std::cout << " Watered " << Plant::name << " (Apple) with " << amount << "L." << std::endl;
} else {
    std::cout << "Cannot water " << Plant::name << " - apple tree is not alive!" << std::endl;
}
}

void Apple::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType.find("fruit-tree") == std::string::npos) {
            std::cout << " APPLE CARE: Consider using fruit-tree specific fertilizer for better yield." << std::endl;
        } else {
            std::cout << " APPLE CARE: Perfect fertilizer for fruit production!" << std::endl;
        }
        fertilized = true;
        std::cout << " Fertilized " << Plant::name << " (Apple) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << Plant::name << " - apple tree is not alive!" << std::endl;
    }
}

void Apple::prune(int intensity){
    if (isAlive) {
        if (intensity < OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " APPLE CARE: Regular heavy pruning improves fruit production! Optimal is " 
                      << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        } else if (intensity == OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " APPLE CARE: Perfect pruning intensity for fruit trees!" << std::endl;
        }
        std::cout << " Pruned " << Plant::name << " (Apple) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << Plant::name << " - apple tree is not alive!" << std::endl;
    }
}

void Apple::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " APPLE CARE: Apple trees need full sun for best fruit production! Minimum " << MIN_SUNLIGHT << " hours. Optimal is " << OPTIMAL_SUNLIGHT << " hours." << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << Plant::name << " (Apple)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << Plant::name << " - apple tree is not alive!" << std::endl;
    }
}

std::string Apple::getCareInstructions() const{
    std::stringstream ss;
        ss << " APPLE TREE CARE: \n";
        ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L regularly for fruit production\n";
        ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << " hours full sun daily\n";
        ss << "• Fertilizer: " << getOptimalFertilizer() << " specific fertilizer\n";
        ss << "• Pruning: Heavy pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ") in winter";
        return ss.str();
}
