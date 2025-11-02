#include "Rose.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double Rose::OPTIMAL_WATER = 1.0;
const double Rose::MIN_WATER = 0.5;
const double Rose::MAX_WATER = 2.0;
const int Rose::OPTIMAL_SUNLIGHT = 8;
const int Rose::MIN_SUNLIGHT = 6;
const int Rose::OPTIMAL_PRUNE_INTENSITY = 4;
const std::string Rose::OPTIMAL_FERTILIZER = "rose specific";

Rose::Rose(std::string name, double price, std::string species)
    : Flower(name, price, species) {
}

Rose::~Rose() {
}

std::string Rose::getPlantType() const {
    return "Rose";
}

void Rose::water(double amount){
    if (isAlive) {
        if (amount < MIN_WATER) {
            std::cout << " ROSE CARE: Roses need regular watering! Minimum is " << MIN_WATER << "L." << std::endl;
            return;
        } else if (amount > MAX_WATER) {
            std::cout << " ROSE CARE: Too much water can cause root rot! Maximum is " << MAX_WATER << "L." << std::endl;
            return;
        } else{
        lastWaterLevel += amount;
        std::cout << " Watered " << name << " (Rose) with " << amount << "L." << std::endl;}
    } else {
        std::cout << "Cannot water " << name << " - rose is not alive!" << std::endl;
    }
}

void Rose::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType != OPTIMAL_FERTILIZER) {
            std::cout << " ROSE CARE: Consider using " << OPTIMAL_FERTILIZER << " fertilizer for best blooms." << std::endl;
            return;
        } else {
            std::cout << " ROSE CARE: Perfect fertilizer choice for roses!" << std::endl;
            fertilized = true;
            std::cout << " Fertilized " << name << " (Rose) with " << fertilizerType << std::endl;
        }
    } else {
        std::cout << "Cannot fertilize " << name << " - rose is not alive!" << std::endl;
    }
}

void Rose::prune(int intensity){
    if (isAlive) {
        if (intensity < OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " ROSE CARE: Regular pruning encourages new blooms. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        } else if (intensity == OPTIMAL_PRUNE_INTENSITY) {
            std::cout << " ROSE CARE: Perfect pruning intensity for roses!" << std::endl;
        }
        std::cout << " Pruned " << name << " (Rose) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - rose is not alive!" << std::endl;
    }
}

void Rose::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << " ROSE CARE: Roses need at least " << MIN_SUNLIGHT << " hours of sun daily for best blooms." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << " ROSE CARE: Perfect sunlight amount for rose growth!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << " Provided " << hours << " hours of " << intensity << " sunlight to " << name << " (Rose)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - rose is not alive!" << std::endl;
    }
}

std::string Rose::getCareInstructions() const{
    std::stringstream ss;
    ss << " ROSE CARE: \n";
    ss << "• Water: " << std::fixed << std::setprecision(2) << OPTIMAL_WATER << "L regularly for best blooms\n";
    ss << "• Sunlight: " << OPTIMAL_SUNLIGHT << "+ hours full sun daily\n";
    ss << "• Fertilizer: " << OPTIMAL_FERTILIZER << " fertilizer\n";
    ss << "• Pruning: Regular pruning (intensity " << OPTIMAL_PRUNE_INTENSITY << ")";
    return ss.str();
}
