#include "Rose.h"

Rose::Rose(std::string name, double price, std::string species)
    : Flower(name, price, species) {
}

Rose::~Rose() {
}

std::string Rose::getPlantType() const {
    return "Rose";
}