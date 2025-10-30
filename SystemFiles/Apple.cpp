// Apple.cpp
#include "Apple.h"

Apple::Apple(std::string name, double price, std::string species)
    : Tree(name, price, species) {
}

Apple::~Apple() {
}

std::string Apple::getPlantType() const{
    return "Apple Tree";
}