#include "Jade.h"
#include <iostream>

const double Jade::OPTIMAL_WATER = 0.5;
const double Jade::MAX_WATER = 1.5;
const int Jade::OPTIMAL_SUNLIGHT = 6;
const int Jade::MIN_SUNLIGHT = 4;
const int Jade::OPTIMAL_PRUNE_INTENSITY = 3;
const std::string Jade::OPTIMAL_FERTILIZER = "succulent-mix";

Jade::Jade(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
}

Jade::~Jade() {
}

std::string Jade::getPlantType() const {
    return "Jade";
}

void Jade::water(double amount){
    if (isAlive) {
        if (amount > MAX_WATER) {
            std::cout << "JADE CARE: Jade plants store water in leaves. Maximum is " << MAX_WATER << "L." << std::endl;
        } else if (amount == OPTIMAL_WATER) {
            std::cout << "JADE CARE: Perfect watering amount for jade plant!" << std::endl;
        }
        lastWaterLevel += amount;
        std::cout << "Watered " << name << " (Jade) with " << amount << "L." << std::endl;
    } else {
        std::cout << "Cannot water " << name << " - jade plant is not alive!" << std::endl;
    }
}

void Jade::fertilize(const std::string &fertilizerType){
    if (isAlive) {
        if (fertilizerType != OPTIMAL_FERTILIZER) {
            std::cout << "JADE CARE: Use succulent fertilizer during growing season for best results." << std::endl;
        } else {
            std::cout << "JADE CARE: Perfect fertilizer for jade plants!" << std::endl;
        }
        fertilized = true;
        std::cout << "Fertilized " << name << " (Jade) with " << fertilizerType << std::endl;
    } else {
        std::cout << "Cannot fertilize " << name << " - jade plant is not alive!" << std::endl;
    }
}

void Jade::prune(int intensity){
    if (isAlive) {
        if (intensity < OPTIMAL_PRUNE_INTENSITY) {
            std::cout << "JADE CARE: Prune to maintain shape and encourage bushiness. Optimal intensity is " << OPTIMAL_PRUNE_INTENSITY << "." << std::endl;
        } else if (intensity == OPTIMAL_PRUNE_INTENSITY) {
            std::cout << "JADE CARE: Perfect pruning intensity for jade plant!" << std::endl;
        }
        std::cout << "Pruned " << name << " (Jade) with intensity " << intensity << std::endl;
    } else {
        std::cout << "Cannot prune " << name << " - jade plant is not alive!" << std::endl;
    }
}

void Jade::provideSunlight(int hours, const std::string &intensity){
    if (isAlive) {
        if (hours < MIN_SUNLIGHT) {
            std::cout << "JADE CARE: Jade plants need at least " << MIN_SUNLIGHT << " hours of bright light." << std::endl;
        } else if (hours >= OPTIMAL_SUNLIGHT) {
            std::cout << "JADE CARE: Perfect sunlight for jade plant growth!" << std::endl;
        }
        exposureSunlightHours += hours;
        std::cout << "Provided " << hours << " hours of " << intensity 
                  << " sunlight to " << name << " (Jade)" << std::endl;
    } else {
        std::cout << "Cannot provide sunlight to " << name << " - jade plant is not alive!" << std::endl;
    }
}

std::string Jade::getCareInstructions() const{
    return "JADE PLANT CARE: Water when soil is dry (" + std::to_string(OPTIMAL_WATER) + "L). Bright light (" + 
           std::to_string(OPTIMAL_SUNLIGHT) + " hours). Use " + OPTIMAL_FERTILIZER + " fertilizer. Prune for shape (intensity " +
           std::to_string(OPTIMAL_PRUNE_INTENSITY) + ").";
}
