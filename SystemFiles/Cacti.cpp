#include "Cacti.h"

Cacti::Cacti(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
}

Cacti::~Cacti() {
}

std::string Cacti::getPlantType() const {
    return "Cacti";
}