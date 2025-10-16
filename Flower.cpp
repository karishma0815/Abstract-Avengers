#include "Flower.h"

Flower::Flower(std::string name, double price, std::string species)
    : FlowerProduct(name, price), species(species) {
}

Flower::~Flower() {
}

int Flower::getCount() const {
    return 1;
}

std::string Flower::getSpecies() const {
    return species;
}

double Flower::getTotalValue() const {
    return price;
}