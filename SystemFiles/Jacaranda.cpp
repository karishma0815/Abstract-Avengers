#include "Jacaranda.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Jacaranda::OPTIMAL_WATER = 1.5;
const double Jacaranda::MIN_WATER = 1.0;
const double Jacaranda::MAX_WATER = 3.0;
const int Jacaranda::OPTIMAL_SUNLIGHT = 8;
const int Jacaranda::MIN_SUNLIGHT = 6;
const int Jacaranda::MAX_SUNLIGHT = 12;
const int Jacaranda::OPTIMAL_PRUNE_INTENSITY = 3;
const int Jacaranda::MAX_PRUNE_INTENSITY = 4;

Jacaranda::Jacaranda(std::string name, double price, std::string species)
    : Tree(name, price, species) {
}

Jacaranda::~Jacaranda() {
}

std::string Jacaranda::getPlantType() const {
    return "Jacaranda";
}

void Jacaranda::water(double amount){
    if (isAlive) {
        if (amount > MAX_WATER) {
            std::cout << " JACARANDA CARE: Too much water! Maximum is " << static_cast<int>(MAX_WATER) << "L. Optimal is 1.5L." << std::endl;
            return;
        } else if (amount < MIN_WATER) {
            std::cout << " JACARANDA CARE: Needs at least " << static_cast<int>(MIN_WATER) << "L! Optimal is 1.5L." << std::endl;
            return;
        } 
        
        lastWaterLevel += amount;
        std::cout << " Watered " << Plant::name << " (Jacaranda) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << Plant::name << " - jacaranda tree is not alive!" << std::endl;
    }
}

void Jacaranda::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        std::string optimalFertilizer = getOptimalFertilizer();
        
        if (fertilizerType != optimalFertilizer) {
            std::cout << " JACARANDA CARE: Consider using '" << optimalFertilizer << "' fertilizer for best growth and flowering." << std::endl;
        } else {
            std::cout << " JACARANDA CARE: Perfect fertilizer choice for flowering!" << std::endl;
        }
        
        fertilized = true;
        std::cout << " Fertilized " << Plant::name << " (Jacaranda) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << Plant::name << " - jacaranda tree is not alive!" << std::endl;
    }
}

void Jacaranda::prune(int intensity){
    if (isAlive) {
        if (intensity > MAX_PRUNE_INTENSITY) {
            std::cout << " JACARANDA CARE: Too aggressive! Maximum pruning intensity is " << MAX_PRUNE_INTENSITY << ". Optimal is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        } else if (intensity < OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " JACARANDA CARE: Light pruning is good for maintenance. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        } else if (intensity == OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " JACARANDA CARE: Perfect pruning intensity!" << std::endl;
        }
        
        std::cout << " JACARANDA CARE: Prune lightly after flowering to maintain shape." << std::endl;
        std::cout << " Pruned " << Plant::name << " (Jacaranda) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << Plant::name << " - jacaranda tree is not alive!" << std::endl;
    }
}

void Jacaranda::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " JACARANDA CARE: Needs more sun! Minimum " << MIN_SUNLIGHT << " hours daily. Optimal is " << OPTIMAL_SUNLIGHT << " hours." << std::endl;
        } else if (hours > MAX_SUNLIGHT) {
            std::cout << " JACARANDA CARE: Too much direct sun! Maximum " << MAX_SUNLIGHT << " hours. Optimal is " << OPTIMAL_SUNLIGHT << " hours." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << " JACARANDA CARE: Perfect sunlight amount for flowering!" << std::endl;
        }
        
        if (intensity == "low") {
            std::cout << " JACARANDA CARE: Prefers medium to high intensity sunlight for best growth." << std::endl;
        }
        
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << Plant::name << " (Jacaranda)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << Plant::name << " - jacaranda tree is not alive!" << std::endl;
    }
}

std::string Jacaranda::getCareInstructions() const{
    std::stringstream ss;
        ss << " JACARANDA TREE CARE: \n";
        ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L regularly (min " << MIN_WATER << "L, max " << MAX_WATER << "L)\n";
        ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << " hours daily (min " << MIN_SUNLIGHT << " hours)\n";
        ss << "• Fertilizer: " << getOptimalFertilizer() << " fertilizer regularly when young\n";
        ss << "• Pruning: Light pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ") after flowering for shape";
        return ss.str();
}
