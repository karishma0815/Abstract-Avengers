#include "Jade.h"

Jade::Jade(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
}

Jade::~Jade() {
}

std::string Jade::getPlantType() const {
    return "Jade";
}