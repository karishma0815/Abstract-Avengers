#include "Protea.h"

Protea::Protea(std::string name, double price, std::string species)
    : Flower(name, price, species) {
}

Protea::~Protea() {
}

std::string Protea::getPlantType() const {
    return "Protea";
}