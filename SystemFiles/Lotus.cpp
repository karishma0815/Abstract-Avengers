// Lotus.cpp
#include "Lotus.h"

Lotus::Lotus(std::string name, double price, std::string species)
    : Flower(name, price, species) {
}

Lotus::~Lotus() {
}

std::string Lotus::getPlantType() const {
    return "Lotus";
}