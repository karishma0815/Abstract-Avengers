#include "Succulent.h"

Succulent::Succulent(std::string name, double price, std::string species)
    : SucculentProduct(name, price), species(species) {
}

Succulent::~Succulent() {
}

int Succulent::getCount() const {
    return 1;
}

std::string Succulent::getSpecies() const {
    return species;
}

double Succulent::getTotalValue() const {
    return price;
}