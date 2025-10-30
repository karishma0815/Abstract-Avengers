// Orchid.cpp
#include "Orchid.h"

Orchid::Orchid(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
}

Orchid::~Orchid() {
}

std::string Orchid::getPlantType() const {
    return "Orchid";
}